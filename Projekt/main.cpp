#include "BruteForce.h"
#include "ReadFromFile.h"
#include "SaveToFile.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

int main() {
	int wybor;
	std::cout << "1. Przeglad zupelny - jeden watek\n2. Przeglad zupelny - wiele watkow\n"; std::cin >> wybor;
	BruteForce * bruteforce = new BruteForce("tsp_12.txt", 2,wybor);
	bruteforce->run(wybor);

	system("pause");
}