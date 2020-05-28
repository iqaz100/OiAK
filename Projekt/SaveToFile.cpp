#include "SaveToFile.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include "BruteForce.h"
#include "BranchAndBound.h"



void SaveToFile::createFileName(int size)
{
	std::stringstream ss;
	ss << mode << "_" << size << "miast_" << count << "powtorzen.txt";
	ss >> fileName;
}

SaveToFile::SaveToFile(std::string mode, int count)
{
	this->mode = mode;
	this->count = count;
}

void SaveToFile::write(std::string path, int droga, int time, int size)
{
	std::ofstream file;
	createFileName(size);
	file.open(fileName, std::ios::trunc);
	if (file.good()) {
		file << "Sciezka:" << path << std::endl;
		file << "Dlugosc drogi: " << droga << std::endl;
		file << std::endl;
		file << "Pomiary czasu" << std::endl;

		if (mode.compare("Branch_and_bound") == 0) {
			file << BranchAndBound::wykPrzejsc << ". " << time;
		}
		else if (mode.compare("Brute_force")==0 && BruteForce::wykPrzejsc < count) {
			file << BruteForce::wykPrzejsc << ". " << time;
		}
		file.close();
	}
	else {
		std::cout << "Nie udalo sie uzyskac dostepu do pliku!" << std::endl;
	}
		
}

void SaveToFile::write(int time)
{
	std::ofstream file;
	file.open(fileName, std::ios::app);
	if (file.good()) {
		file << std::endl;
		if (mode.compare("Branch_and_bound") == 0) {
			file<<BranchAndBound::wykPrzejsc<<". "<<time;
		}
		else if (mode.compare("Brute_force")==0) {
			file << BruteForce::wykPrzejsc << ". " << time;
		}
		file.close();
	}
	else {
		std::cout << "Nie udalo sie uzyskac dostepu do pliku!" << std::endl;
	}
}


SaveToFile::~SaveToFile()
{
}
