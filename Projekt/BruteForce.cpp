#include "BruteForce.h"
#include <string>
#include <sstream>
#include <chrono>
#include <iostream>
#include <future>
#include <thread>
#include <windows.h>

using namespace std;

int BruteForce::wykPrzejsc = 1;

//std::vector<std::thread> threads(4);
std::thread threads[15];

void BruteForce::testMethod(int a, int roadTemp[], int drogaTemp) {
	//std::unique_lock<std::mutex> lock(searchingMutex);
	//ROADTEMP JAKO LOKALNA ZROBIC
	int roadTempT[20] = {0};
	int drogaTempT = drogaTemp;
	bool visited[20] = { false };
	visited[0] = true;
	int i;
	int ptrT = 1;
	roadTempT[0] = 0;
	roadTempT[ptrT] = a;
	//cout << "USTAWIAM " << a << "dla rodeTemp " << roadTempT[ptrT] << endl;;
	ptrT++;

	if (ptrT < cityCount) {
		visited[a] = true;
		for (int i = 0; i < cityCount; i++) {
			if (!visited[i]) {
				drogaTempT += wagiArray[a][i];
				//cout << "TWORZE WATEK O i rownym " << i << endl;

				algorithmWithThreads(i,ptrT, visited,roadTempT,drogaTempT);

				drogaTempT -= wagiArray[a][i];
			}
		}
		//PRZYWRACAMY STAN MIASTA NA NIEODWIEDZONE
		visited[a] = false;
	}

	else {
		drogaTempT += wagiArray[a][startCity];

		if (drogaTempT < droga) {
			droga = drogaTempT;
			for (i = 0; i < ptrT; i++) {
				road[i] = roadTemp[i];
				//cout << "USTAWIAM DROGIE NA " << roadTemp[i] << " dla i rownego " << i << endl;
			}
		}
		drogaTempT -= wagiArray[a][startCity];
	}
	ptrT--;

	//cout << "JESTEM" << endl;
	//for (int i = 0; i < 1; i++) {
	//	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//	cout << "Zmienna a = " << a << endl;
	//}

	threadsFinished++;
	//lock.unlock();
	condition.notify_one();
	//cout << "THREDY" <<threadsFinished;
}

void BruteForce::algorithmWithThreads(int a, int ptrT, bool visited[], int roadTemp[], int drogaTempT) {
	int i;

	roadTemp[ptrT] = a;
	ptrT++;
	if (ptrT < cityCount) {
		visited[a] = true;


		for (int i = 0; i < cityCount; i++) {
			if (!visited[i]) {
				drogaTempT += wagiArray[a][i];
				algorithmWithThreads(i,ptrT, visited, roadTemp, drogaTempT);
				drogaTempT -= wagiArray[a][i];
			}
		}
		
		visited[a] = false;

	}
	
	else {
		
		drogaTempT += wagiArray[a][startCity];
	
		if (drogaTempT < droga) {
			droga = drogaTempT;
			for (int i = 0; i < ptrT; i++) {
				//cout << "USTAWIAM DROGIE NA " << roadTemp[i] <<" dla i równego " << i << endl;
				road[i] = roadTemp[i];
			}
		}
		drogaTempT -= wagiArray[a][startCity];
	}

	ptrT--;
	//threadsFinished++;
	//cout << "REKURENCJA" << endl;
}

void BruteForce::algorithm(int a)
{
	bool visited1[20] = { false};
	int roadTemp[20] = { 0 };
	int drogaTemp = 0;
	//std::cout << "jestem"<<std::endl;
	int i;

	//std::vector<std::future<void>> futures;

	//USTAWIENIE ELEMENTU DROGI NA WARTO�� PRZEKAZAN� DO FUNKCJI
	roadTemp[ptr] = a;
	//ZWI�KSZAMY LICZNIK ODWIEDZONYCH MIAST
	ptr++;

	//JE�LI NIE ODWIEDZILI�MY WSZYSTKICH MIAST
	if (ptr < cityCount) {
		//USTAWIAMY MIASTO JAKO ODWIEDZONE
		visited1[a] = true;

		//SZUKAMY NIEODWIEDZONEGO MIASTA
		for (i = 0; i < cityCount; i++) {
			//cout << "Przelot numer: " << i << endl;
			if (!visited1[i]) {
				//cout << "Przelot numer: " << i << endl;
				drogaTemp += wagiArray[a][i];
				//WYKONUJEMY FUNKCJ� PONOWNIE DLA KOLEJNEGO MIASTA

				if (threadNumber <= (cityCount-1)) {
					//std::cout << "watek " << i << std::endl;
					threadNumber++;
					//futures.push_back(std::async(std::launch::async, [&, i]() {algorithm(i); }));
					
					//std::thread t(&BruteForce::algorithm, this, i);
					//t.join();
					//threads.push_back(t);
					//threads.emplace_back(std::thread(&BruteForce::algorithm, this, i));
					
					//threads[threadNumber] = std::thread(&BruteForce::algorithmWithThreads,this,i);
					threads[threadNumber] = std::thread(&BruteForce::testMethod, this, i, roadTemp,drogaTemp);
					//threads[threadNumber].detach();
					//threads[threadNumber].join();

					
					//threadNumber--;
					//std::cout << "watek " << a << std::endl;
				}
				else {
					
					//algorithm(i);
				}
				
				//algorithm(i);
				//future<void> fn = async(launch::async, algorithm,i);

				//fn.get();
				//algorithm(i);
				//Sleep(10000);
				//COFAMY SI� DO POPRZEDNIEGO MIASTA
				drogaTemp -= wagiArray[a][i];
			}
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		//PRZYWRACAMY STAN MIASTA NA NIEODWIEDZONE
		visited1[a] = false;
		
	}
	//JE�LI DOTARLI�MY DO OSTATNIEGO MIASTA
	//else {
	//	//DODAJEMY D�UGO�� DROGI POMI�DZY PIERWSZYM A OSTATNIM MIASTEM
	//	drogaTemp += wagiArray[a][startCity];
	//	//JE�ELI ZNALEZIONA DROGA JEST KR�TSZA OD WCZE�NIEJSZYCH ZNALEZIONYCH TO ZAPAMI�TUJEMY J�
	//	if (drogaTemp < droga) {
	//		droga = drogaTemp;
	//		for (i = 0; i < ptr; i++) {
	//			road[i] = roadTemp[i];
	//		}
	//	}
	//	drogaTemp -= wagiArray[a][startCity];
	//}
	ptr--;



}

void BruteForce::run()
{
	while (BruteForce::wykPrzejsc <= count) {
		droga = INT_MAX;
		//POCZ�TEK POMIARU CZASU
		auto starttime = std::chrono::high_resolution_clock::now();
		//POCZ�TEK ALGORYTMU
		threadNumber = 0;
		threadsFinished = 0;
		algorithm(startCity);
		//cout << "Wyszedlem";

		cout << "CZEKAM..." << endl;
		std::unique_lock<std::mutex> lock(searchingMutex);
		condition.wait(lock, [this] { return (threadsFinished == (cityCount - 1)); });
		lock.unlock();

		//cout << "KUKUKU.." << endl;

		for (int i = 0; i < cityCount; i++) {
			if (threads[i].joinable())
			{
				//cout << "J" << endl;
				threads[i].join();
			}
		}
		
		//KONIEC POMIARU CZASU
		auto endtime = std::chrono::high_resolution_clock::now();
		std::cout << "Przejscie numer " << wykPrzejsc << " wykonane poprawnie" << std::endl;
		//ZAPIS DO PLIKU
		if (wykPrzejsc <= 1) {
			std::string temp = "", temp2;
			std::stringstream ss;
			for (int i = 0; i < cityCount; i++) {
				ss << road[i] << " ";
				ss >> temp2;
				temp += temp2;
				temp += " ";
			}
			saveMachine->write(temp,droga,std::chrono::duration_cast<std::chrono::microseconds>(endtime-starttime).count(), cityCount);
			wykPrzejsc++;
		}
		else {
			saveMachine->write(std::chrono::duration_cast<std::chrono::microseconds>(endtime-starttime).count());
			wykPrzejsc++;
		}
		//USUNI�CIE TABEL
		//delete[] visited;
		delete[] wagiArray;
		delete[] road;
		//delete[] roadTemp;
		delete readMachine;

		//JE�LI NIE ZAKO�CZONO OSTATNIEGO POWT�RZENIA TO PONOWNE WCZYTANIE DANYCH
		if (wykPrzejsc <= count) {
			readMachine = new ReadFromFile(fileName);
			cityCount = readMachine->getSizeArray();
			//visited = readMachine->getArrayVisited();
			wagiArray = readMachine->getArray2DValues();
			road = new int[cityCount];
			//roadTemp = new int[cityCount];
		}
	}
}

BruteForce::BruteForce(std::string name, int count)
{
	fileName = name;
	this->count = count;
	readMachine = new ReadFromFile(fileName);
	saveMachine = new SaveToFile("Brute_force", this->count);
	cityCount = readMachine->getSizeArray();
	//visited = readMachine->getArrayVisited();
	wagiArray = readMachine->getArray2DValues();
	road = new int[cityCount];
	//roadTemp = new int[cityCount];
	//drogaTemp = city = startCity = ptr = 0;
}


BruteForce::~BruteForce()
{
}
