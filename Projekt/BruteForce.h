#pragma once
#include <string>
#include "ReadFromFile.h"
#include "SaveToFile.h"
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>


class BruteForce
{
private:
	std::string fileName;
	int count, cityCount, droga, startCity, city, ptr = 0;
	int wybor;
	int drogaTemp;
	ReadFromFile *readMachine;
	SaveToFile *saveMachine;
	bool *visited1;
	int **wagiArray;
	int *road;
	int *roadTemp;
	void algorithm(int,int);
	void algorithmWithThreads(int, int, bool visited[], int roadTemp[], int drogaTemp);
	void paralellAlgorithm(int a, int roadTemp1[], int drogaTemp);
	int threadNumber = 0;
	int threadsCount;
	std::atomic<int> threadsFinished = 0;
	std::mutex searchingMutex;
	std::condition_variable condition;
public:
	static int wykPrzejsc;
	void run(int);
	BruteForce(std::string, int,int);
	~BruteForce();
};

