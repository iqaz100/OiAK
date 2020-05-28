#include "BranchAndBound.h"
#include <iostream>
#include <sstream>
#include <chrono>

int BranchAndBound::wykPrzejsc = 1;

BranchAndBound::BranchAndBound(std::string filename, int count)
{
	this->count = count;
	this->fileName = filename;
	this->size = 0;
	this->saveMachine = new SaveToFile("Branch_and_bound", this->count);
}


BranchAndBound::~BranchAndBound()
{
	for (size_t i = 0; i < currentWay.size(); i++) {
		delete currentWay.back();
		currentWay.pop_back();
	}
	delete saveMachine;
}

void BranchAndBound::run()
{
	std::stringstream ss;
	std::string droga;

	for (size_t i = 0; i < count; i++) {
		reader = new ReadFromFile(fileName);
		size = reader->getSizeArray();

		if (size > 0) {
			//pocz¹tek pomiaru czasu
			auto starttime = std::chrono::high_resolution_clock::now();
			finalRoad.road = new way[size];
			int border;
			bestPrice best;
			border = calculateBorder(findMins(reader->getArray2DValues()), 0);
			best = findAndChooseBestPrice(reader->getArray2DValues(), size);
			createNextElement(reader->getArray2DValues(), false, best, border, way(-1, -1));
			recursiveFun(border, best.w);
			//koniec pomiaru czasu
			auto endtime = std::chrono::high_resolution_clock::now();

			//zapisanie dróg miêdzy miastami do stringa
			for (size_t x = 0; x < size; x++) {
				ss << "(" << finalRoad.road[x].x << "," << finalRoad.road[x].y << ")";
			}
			ss >> droga;

			//zapis pomiaru czasu do pliku
			if (BranchAndBound::wykPrzejsc <= 1) {
				saveMachine->write(droga, finalRoad.border, std::chrono::duration_cast<std::chrono::microseconds>(endtime - starttime).count(), size);
				wykPrzejsc++;
			}
			else {
				saveMachine->write(std::chrono::duration_cast<std::chrono::microseconds>(endtime - starttime).count());
				wykPrzejsc++;
			}

			//wypisanie wiadomoœci o przejœciu algorytmu
			std::cout << "Przejscie numer " << i + 1 << " wykonane poprawnie" << std::endl;
		}
		else {
			std::cout << "Blad odczytu tablicy" << std::endl;
		}
		//wyczyszczenie pamiêci
		deleteAllElements();
	}
}

void BranchAndBound::createNextElement(int ** tab, bool iscross, bestPrice w, int border, way whichdelete)
{
	currentWay.push_back(new Element(w, tab, border, iscross, size, whichdelete));
}

//znajduje minimum w kolumnie i wierszu
//i usuwa je z kolumny i wiersza
touple2D * BranchAndBound::findMins(int **tab)
{
	int *rows = new int[size];
	int *cols = new int[size];
	int count = 0;
	int min = -1;
	bool first = true;

	//wyszukiwanie w wierszu
	for (size_t x = 0; x < size; x++) {
		first = true;
		for (size_t y = 0; y < size; y++) {
			if ((min > tab[x][y]) || first) {
				if (tab[x][y] != -2 && tab[x][y] != -1) {
					min = tab[x][y];
					first = false;
				}
			}
		}
		rows[count] = min;
		count++;
		min = -1;
	}

	//odjecie wiersza
	subs(0, tab, rows);
	min = -1;
	count = 0;

	//wyszukanie w kolumnie
	for (size_t y = 0; y < size; y++) {
		first = true;
		for (size_t x = 0; x < size; x++) {
			if ((min > tab[x][y]) || first) {
				if (tab[x][y] != -2 && tab[x][y] != -1) {
					min = tab[x][y];
					first = false;
				}
			}
		}
		cols[count] = min;
		count++;
		min = -1;
	}

	//odjêcie kolumn
	subs(1, tab, cols);

	//zwrocenie krotki zawieraj¹cej kolumne i wiersz
	return new touple2D(rows, cols);
}

void BranchAndBound::recursiveFun(int lastborder, way whichdelete)
{
	tempTabCopy = copyArrays2D(currentWay.back()->tab, 0, currentWay.back()->cross.w);
	border = calculateBorder(findMins(tempTabCopy), lastborder);


	//lewe poddrzewo (skreslanie wiersza i kolumny zalicza sie do drogi)
	if ((finalRoad.border == 0 || finalRoad.border == -2 || border < finalRoad.border) && currentWay.back()->count != 1)
	{

		best = findAndChooseBestPrice(tempTabCopy, size);
		currentWay.back()->count++;
		createNextElement(tempTabCopy, false, best, border, whichdelete);
		//znaczy ze jednostkowa macierz koniec drogi
		if (best.price == -2)
		{
			//sprawdzenie czy jest lepsza droga
			if (finalRoad.border == 0 || finalRoad.border == -2 || finalRoad.border > currentWay.back()->border)
			{
				//sprawdzenie czy jest cykl pelny czy sa mniejsze cykle w drodze
				if (checkCycle(currentWay))
				{
					int temp_count = 0;
					//sprawdzenie drogi czy jest calkowita - nie skonczyla sie na prawej stronie
					for (size_t i = 1; i < currentWay.size(); i++)
					{
						if (!currentWay[i]->isdeletepoint)
						{
							temp_count++;
						}
					}
					//przypisanie drogi 
					if (temp_count == size)
					{
						temp_count = 0;
						for (size_t i = 1; i < currentWay.size(); i++)
						{
							if (!currentWay[i]->isdeletepoint)
							{
								finalRoad.road[temp_count] = currentWay[i]->whichdelete;
								temp_count++;

							}
						}

						finalRoad.border = currentWay.back()->border;
					}

				}

			}
			delete currentWay.back();
			currentWay.pop_back();
		}
		else
		{
			recursiveFun(currentWay.back()->border, currentWay.back()->cross.w);
		}
	}
	//prawe poddrzewo skreslony element inny wybor drogi
	else
	{
		for (size_t i = 0; i < size; i++)
		{
			delete[] tempTabCopy[i];
		}
		delete[] tempTabCopy;

		tempTabCopy = copyArrays2D(currentWay.back()->tab, 1, currentWay.back()->cross.w);
		border = calculateBorder(findMins(tempTabCopy), currentWay.back()->border);
		if (currentWay.back()->count != 2 && (border < finalRoad.border || finalRoad.border == -2) && border > -1)
		{
			best = findAndChooseBestPrice(tempTabCopy, size);
			currentWay.back()->count++;
			createNextElement(tempTabCopy, true, best, border, currentWay.back()->cross.w);
			if (best.price != -2)
				recursiveFun(currentWay.back()->border, currentWay.back()->cross.w);
			else
			{
				delete currentWay.back();
				currentWay.pop_back();
			}
		}
		else
		{
			for (size_t i = 0; i < size; i++)
			{
				delete[] tempTabCopy[i];
			}
			delete[] tempTabCopy;

			delete currentWay.back();
			currentWay.pop_back();
		}
	}

	if (currentWay.size() != 0)
	{
		if (currentWay.back()->count != 2)
		{
			recursiveFun(currentWay.back()->border, currentWay.back()->cross.w);
		}
		else
		{
			delete currentWay.back();
			currentWay.pop_back();
		}
	}
}


//odejmujemy - jesli 0 to od wierszy jesli 1 to od kolumn
void BranchAndBound::subs(int which, int **tab, int *temptab)
{
	int count = 0;
	if (which == 0) {
		for (size_t x = 0; x < size; x++) {
			if (temptab[count] == -1 && temptab[count] == 0) {
				count++;
				continue;
			}
			for (size_t y = 0; y < size; y++) {
				if (tab[x][y] != -1 && tab[x][y] != -2) {
					tab[x][y] -= temptab[count];
				}
			}
			count++;
		}
	}
	else {
		for (size_t y = 0; y < size; y++)
		{
			if (temptab[count] == -1 && temptab[count] == 0)
			{
				count++;
				continue;
			}
			for (size_t x = 0; x < size; x++)
			{
				if (tab[x][y] != -1 && tab[x][y] != -2)
				{
					tab[x][y] -= temptab[count];
				}
			}
			count++;
		}
	}
}


//usuwa wiersz i kolumnê i blokuje drogê powrotn¹
void BranchAndBound::deleteRowCol(int size, int **tab, way w)
{
	for (size_t y = 0; y < size; y++) {
		if (tab[w.x][y] != -2) {
			tab[w.x][y] = -2;
		}
	}
	for (size_t x = 0; x < size; x++) {
		if (tab[x][w.y] != -2) {
			tab[x][w.y] = -2;
		}
	}
	
	way temp(w.y, w.x);

	//blokowanie drogi powrotnej
	deleteElement(tab, temp);
}

//usuniêcie i blokada elementu
void BranchAndBound::deleteElement(int ** tab, way w)
{
	if (tab[w.x][w.y] != -2) {
		tab[w.x][w.y] = -1;
	}
}

//oblicza granicê
//jeœli gdzieœ wyjdzie -1 to traktujemy jako nieskoñczonoœæ
//wiêc przerywamy wyszukiwanie drogi dla tej œcie¿ki
int BranchAndBound::calculateBorder(touple2D *t, int border)
{
	int temp = 0, row = 0, col = 0;
	for (size_t i = 0; i < size; i++)
	{
		row = t->rows[i];
		col = t->cols[i];
		if (col != -1 && col != 0)
		{
			temp += col;
		}
		if (row != -1 && row != 0)
		{
			temp += row;
		}
	}

	if (temp != -1) {
		temp += border;
	}
	delete t;
	return temp;
}

//-1 koszt nieskoñczony - najlepsze wy³¹czenie
//-2 brak wiersza i kolumny
bestPrice BranchAndBound::findAndChooseBestPrice(int **tab, int size)
{
	std::vector<bestPrice> bests;
	bestPrice bestmaxprice;
	for (size_t x = 0; x < size; x++) {
		for (size_t y = 0; y < size; y++) {
			if (tab[x][y] == 0) {
				bests.push_back(bestPrice(way(x, y), 0));
			}
		}
	}
	//je¿eli brak zer to znaczy ¿e macierz jednostkowa i koniec drogi
	if (bests.size() > 0) {
		int x1 = 0;
		int y1 = 0;
		int min = 0;
		int tempmin = 0;
		bool first = true;
		for (size_t i = 0; i < bests.size(); i++) {
			//wy³¹czenie punktu posiadaj¹cego koszt 0
			x1 = bests[i].w.x;
			y1 = bests[i].w.y;

			//zerowanie wartoœci
			min = -1;
			tempmin = 0;

			//przeszukanie po kolumnach
			for (size_t y = 0; y < size; y++) {
				if (tab[x1][y] > -1 && y != y1)
				{
					if (min > tab[x1][y] || first)
					{
						min = tab[x1][y];
						first = false;
					}
				}
			}
			tempmin = min;

			//zerowanie wartoœci
			min = -1;
			first = true;
			if (tempmin != -1)
			{
				//przeszukanie po wierszach
				for (size_t x = 0; x < size; x++)
				{
					if (tab[x][y1] > -1 && x != x1)
					{
						if (min > tab[x][y1] || first)
						{
							min = tab[x][y1];
							first = false;
						}
					}
				}
				//jesli -1 w wierszu i kolumnie to jest to  
				//nieskonczonosc i bierzemy jako najlepszy koszt
				if (min == -1)
				{
					tempmin = -1;
				}
				else
				{
					tempmin += min;
				}
			}
			first = true;
			bests[i].price = tempmin;
		}
		//znalezenie najlepszego kosztu wylaczenia wsrod wszystkich kosztow ale bez nieskonczonosci
		//nieskonczonosc rozwazamy jesli innych kosztow nie ma
		int max = 0;
		for (size_t i = 0; i < bests.size(); i++)
		{
			if (bests[i].price != -1)
			{
				if (max <= bests[i].price)
				{
					max = bests[i].price;
					bestmaxprice = bests[i];
				}
			}
			else
			{
				bestmaxprice = bests[i];
				break;
			}
		}
	}
	else
	{
		//jesli macierz jednostkowa to zasygnalizuj to algorytmowi poprzez -2 a way(-1,-1)
		//aby przy debugowaniu ulatwic znalezienie bledu
		bestmaxprice.w = way(-1, -1);
		bestmaxprice.price = -2;
	}
	return bestmaxprice;
}


//kopiowanie i tworzenie nowej tablicy z istniej¹cej
//0 - usuwanie wiersza i kolumny
//1 - usuwanie punktu
//2 - tylko kopiowanie tablicy
int ** BranchAndBound::copyArrays2D(int **tab, int which, way w)
{
	int **temptab = new int*[size];

	for (size_t i=0; i < size; i++) {
		temptab[i] = new int[size];
	}

	for (size_t x=0; x < size; x++) {
		for (size_t y = 0; y < size; y++) {
			temptab[x][y] = tab[x][y];
		}
	}

	//usuwa wiersz i kolumnê
	if (which == 0) {
		deleteRowCol(size, temptab, w);
	}

	//usuwa sam punkt
	else if (which == 1) {
		deleteElement(temptab, w);
	}
	return temptab;
}


//sprawdza czy droga posiada ma³e cykle
//jeœli droga ma ma³e cykle to odrzucamy j¹ jako b³êdn¹
//sam algorytm little tego nie uwzglêdnia i trzeba to dodaæ
bool BranchAndBound::checkCycle(std::vector<Element*> &way)
{
	bool *visited = new bool[size];
	for (size_t i = 0; i < size; i++) {
		visited[i] = false;
	}
	int temp = 0;
	for (size_t i = 0; i < way.size(); i++) {
		if (way[i]->isdeletepoint == false && way[i]->whichdelete.x != -1) {
			temp = i;
			break;
		}
	}
	visited[way[temp]->whichdelete.x] = true;
	visited[way[temp]->whichdelete.y] = true;
	int temp2 = temp;
	int counter = 1;
	for (size_t i = temp; i < way.size(); i++) {
		if (way[i]->isdeletepoint == false && way[i]->whichdelete.x == way[temp]->whichdelete.y)
		{
			if (visited[way[i]->whichdelete.y] == true && counter < size - 1)
			{
				if (finalRoad.border == 0)
					finalRoad.border = -2;

				delete[] visited;
				return false;

			}
			else if (counter == size)
			{
				delete[] visited;
				return true;

			}
			else
			{
				counter++;
				visited[way[i]->whichdelete.y] = true;
				temp = i;
				i = temp2;
			}
		}
	}
}

//usuwa wszystkie elementy
void BranchAndBound::deleteAllElements()
{
	for (size_t i = 0; i < currentWay.size(); i++) {
		delete currentWay.back();
		currentWay.pop_back();
	}
	delete[] finalRoad.road;
	for (size_t x = 0; x < size; x++) {
		delete[] reader->getArray2DStates()[x];
	}
	delete[] reader->getArray2DStates();
	delete reader;
}
