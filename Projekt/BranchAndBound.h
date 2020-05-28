#pragma once
#include <string>
#include <vector>
#include "ReadFromFile.h"
#include "SaveToFile.h"


//STRUKTURY U¯YTE W PROGRAMIE
struct touple2D {
	int *rows;
	int *cols;

	touple2D(int *rows, int *cols) {
		this->rows = rows;
		this->cols = cols;
	}
	~touple2D() {
		delete[] rows;
		delete[] cols;
	}
};

struct way {
	int x, y;
	way() {
		x = -1;
		y = -1;
	}
	way(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

struct finalWay {
	finalWay(way * road = nullptr, int border = 0) {
		this->road = road;
		this->border = border;
	}
	way * road;
	int border;
};

struct bestPrice {
	bestPrice() {
		price = 0;
	}
	bestPrice(way w, int price) {
		this->w = w;
		this->price = price;
	}
	way w;
	int price;
};

struct Element {
	Element(bestPrice cross, int** tab, int border, bool isdeletepoint, size_t size, way whichdelete = way(-1, -1)) {
		this->tab = tab;
		this->border = border;
		this->cross = cross;
		this->isdeletepoint = isdeletepoint;
		this->count = 0;
		this->size = size;
		this->whichdelete = whichdelete;
	}
	~Element() {
		for (int i = 0; i < size; i++) {
			delete[] tab[i];
		}
		delete[] tab;
	}
	int count;
	int **tab;
	int border;
	bestPrice cross;
	way whichdelete;
	bool isdeletepoint;
	size_t size;
};

class BranchAndBound
{
private:
	std::string fileName;
	finalWay finalRoad;
	std::vector<Element*> currentWay;
	ReadFromFile *reader;
	int border;
	bestPrice best;
	int** tempTabCopy;
	size_t size;
	int count;
	SaveToFile *saveMachine;

	void createNextElement(int **, bool, bestPrice, int, way);
	touple2D * findMins(int **);
	void recursiveFun(int, way);
	void subs(int, int **, int *);
	void deleteRowCol(int, int **, way);
	void deleteElement(int **, way);
	int calculateBorder(touple2D *, int);
	bestPrice findAndChooseBestPrice(int **, int);
	int ** copyArrays2D(int **, int, way);
	bool checkCycle(std::vector<Element*>&);
	void deleteAllElements();
public:
	static int wykPrzejsc;

	BranchAndBound(std::string, int);
	~BranchAndBound();

	void run();
};

