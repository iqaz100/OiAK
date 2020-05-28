#include "GenerateRandom.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iostream>

void GenerateRandom::run(std::string path, int count)
{
	std::string temp;
	std::ofstream file;

	file.open(path, std::ios::trunc);

	if (file.good()) {
		file << count << std::endl;
		for (int i = 0; i < count; i++) {
			for (int j = 0; j < count; j++) {
				if (i == j)
					file << "-1 ";
				else
					file << rand() % 100 + 1 << " ";
			}
			file << std::endl;
		}
		file.close();
	}
	else
		std::cout << "Nieudany dostep do pliku!" << std::endl;
}


GenerateRandom::GenerateRandom(std::string path, std::string count)
{
	srand(time(NULL));
	run(path,stoi(count));
}


GenerateRandom::~GenerateRandom()
{
}
