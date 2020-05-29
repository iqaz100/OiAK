#include "BruteForce.h"
#include "ReadFromFile.h"
#include "SaveToFile.h"
#include "GenerateRandom.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

bool doesFileExist(const std::string& name) {
	std::ifstream f(name.c_str());
	if (f.good()) {
		f.close();
		return true;
	}
	else {
		f.close();
		return false;
	}
}

int main() {
	int wybor;
	std::cout << "1. Przeglad zupelny - jeden watek\n2. Przeglad zupelny - wiele watkow\n"; std::cin >> wybor;
	BruteForce * bruteforce = new BruteForce("tsp_12.txt", 2,wybor); //przegl¹d zupe³ny
	bruteforce->run(wybor);

	system("pause");
}