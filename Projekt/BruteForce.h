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
	//int drogaTemp;
	ReadFromFile *readMachine;
	SaveToFile *saveMachine;
	//bool *visited;
	int **wagiArray;
	int *road;
	//int *roadTemp;
	void algorithm(int);
	void algorithmWithThreads(int, int, bool visited[], int roadTemp[], int drogaTemp);
	void testMethod(int a, int roadTemp1[], int drogaTemp);
	int threadNumber = 0;
	int threadCount = 8;
	std::atomic<int> threadsFinished = 0;
	std::mutex searchingMutex;
	std::condition_variable condition;
public:
	static int wykPrzejsc;
	void run();
	BruteForce(std::string, int);
	~BruteForce();
};

