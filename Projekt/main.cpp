#include "BruteForce.h"
#include "BranchAndBound.h"
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
	GenerateRandom * random;
	random = new GenerateRandom("random23.txt", "23"); //generuje plik o zadanym rozmiarze i nazwie z losowymi wartoœciami
	ReadFromFile * reader = new ReadFromFile("random23.txt"); //odczytanie pliku
	reader->showReadFile(); //wyœwietla odczytywany plik
	delete reader; //oczyszczenie pamiêci ¿eby nie obci¹¿aæ komputera dodatkowo podczas wykonywania algorytmu
	reader = nullptr; //usuniêcie wskaŸnika
	int wybor;
	std::cout << "Jaki algorytm chcesz wykonac?\n1. Przeglad zupelny\n2. Podzialu i ograniczen\n"; std::cin >> wybor;
	if(wybor==1) {
		BruteForce * bruteforce = new BruteForce("tsp_10.txt", 2); //przegl¹d zupe³ny
		bruteforce->run();
	}
	else if (wybor == 2) {
		BranchAndBound * branchandbound = new BranchAndBound("random23.txt", 1); //algorytm podzia³u i ograniczeñ
		branchandbound->run();
	}
	system("pause");
}