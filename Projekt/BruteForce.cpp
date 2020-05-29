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

std::thread threads[15];

void BruteForce::paralellAlgorithm(int a, int roadTemp[], int drogaTemp) {
	int roadTempT[20] = {0};
	int drogaTempT = drogaTemp;
	bool visited[20] = { false };
	visited[0] = true;
	int i;
	int ptrT = 1;
	roadTempT[0] = 0;
	roadTempT[ptrT] = a;
	ptrT++;

	if (ptrT < cityCount) {
		visited[a] = true;
		for (int i = 0; i < cityCount; i++) {
			if (!visited[i]) {
				drogaTempT += wagiArray[a][i];
				algorithmWithThreads(i,ptrT, visited,roadTempT,drogaTempT);
				drogaTempT -= wagiArray[a][i];
			}
		}
		visited[a] = false;
	}

	else {
		drogaTempT += wagiArray[a][startCity];

		if (drogaTempT < droga) {
			droga = drogaTempT;
			for (i = 0; i < ptrT; i++) {
				road[i] = roadTemp[i];
			}
		}
		drogaTempT -= wagiArray[a][startCity];
	}
	ptrT--;

	threadsFinished++;
	condition.notify_one();
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
				road[i] = roadTemp[i];
			}
		}
		drogaTempT -= wagiArray[a][startCity];
	}
	ptrT--;
}

void BruteForce::algorithm(int a,int wybor)
{
	if (wybor == 2) {
		roadTemp[ptr] = a;
		ptr++;
		visited1[a] = true;

		for (int i = 0; i < cityCount; i++) {
			if (!visited1[i]) {
				drogaTemp += wagiArray[a][i];
				threadNumber++;
				threads[threadNumber] = std::thread(&BruteForce::paralellAlgorithm, this, i, roadTemp, drogaTemp);

			}
		}

		cout << "CZEKAM..." << endl;
		std::unique_lock<std::mutex> lock(searchingMutex);
		condition.wait(lock, [this] { return (threadsFinished == threadsCount - 1); });
		lock.unlock();

		for (int i = 0; i < cityCount; i++) {
			if (threads[i].joinable())
			{
				threads[i].join();
			}
		}
	}
	else if (wybor == 1) {
		int i;

		//USTAWIENIE ELEMENTU DROGI NA WARTOSC PRZEKAZANA DO FUNKCJI
		roadTemp[ptr] = a;
		//ZWIEKSZAMY LICZNIK ODWIEDZONYCH MIAST
		ptr++;

		//JESLI NIE ODWIEDZILISMY WSZYSTKICH MIAST
		if (ptr < cityCount) {
			//USTAWIAMY MIASTO JAKO ODWIEDZONE
			visited1[a] = true;

			//SZUKAMY NIEODWIEDZONEGO MIASTA
			for (i = 0; i < cityCount; i++) {
				if (!visited1[i]) {
					drogaTemp += wagiArray[a][i];
					//WYKONUJEMY FUNKCJE PONOWNIE DLA KOLEJNEGO MIASTA
					algorithm(i,1);
					//COFAMY SIE DO POPRZEDNIEGO MIASTA
					drogaTemp -= wagiArray[a][i];
				}
			}
			//PRZYWRACAMY STAN MIASTA NA NIEODWIEDZONE
			visited1[a] = false;
		}
		//JESLI DOTARLISMY DO OSTATNIEGO MIASTA
		else {
			//DODAJEMY DLUGOSC DROGI POMIEDZY PIERWSZYM A OSTATNIM MIASTEM
			drogaTemp += wagiArray[a][startCity];
			//JEZELI ZNALEZIONA DROGA JEST KROTSZA OD WCZESNIEJSZYCH ZNALEZIONYCH TO ZAPAMIETUJEMY JA
			if (drogaTemp < droga) {
				droga = drogaTemp;
				for (i = 0; i < ptr; i++) {
					road[i] = roadTemp[i];
				}
			}
			drogaTemp -= wagiArray[a][startCity];
		}
		ptr--;
	}
	else {
		cout << "WYBRALES ZLA OPCJE!" << endl;
	}
}

void BruteForce::run(int wybor2)
{
	while (BruteForce::wykPrzejsc <= count) {
		droga = INT_MAX;
		//POCZATEK POMIARU CZASU
		auto starttime = std::chrono::high_resolution_clock::now();
		//POCZATEK ALGORYTMU
		threadNumber = 0;
		threadsFinished = 0;
		algorithm(startCity, wybor2);
	
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
		//USUNIECIE TABEL
		delete[] visited1;
		delete[] wagiArray;
		delete[] road;
		delete[] roadTemp;
		delete readMachine;
		ptr = 0;

		//JESLI NIE ZAKONCZONO OSTATNIEGO POWTORZENIA TO PONOWNE WCZYTANIE DANYCH
		if (wykPrzejsc <= count) {
			readMachine = new ReadFromFile(fileName);
			cityCount = readMachine->getSizeArray();
			visited1 = readMachine->getArrayVisited();
			wagiArray = readMachine->getArray2DValues();
			road = new int[cityCount];
			roadTemp = new int[cityCount];
		}
	}
}

BruteForce::BruteForce(std::string name, int count, int wybor)
{
	std::string par;
	fileName = name;
	this->wybor = wybor;
	this->count = count;
	readMachine = new ReadFromFile(fileName);
	if (wybor == 1)
		par = "NonParalell";
	else
		par = "Paralell";
	saveMachine = new SaveToFile("Brute_force", this->count,par);
	cityCount = readMachine->getSizeArray();
	visited1 = readMachine->getArrayVisited();
	wagiArray = readMachine->getArray2DValues();
	road = new int[cityCount];
	roadTemp = new int[cityCount];
	drogaTemp = city = startCity = ptr = 0;
	threadsCount = cityCount;
}

BruteForce::~BruteForce()
{
}
