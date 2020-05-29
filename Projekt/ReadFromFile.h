#pragma once
#include <string>

class ReadFromFile
{
private:
	std::string fileName;
	const size_t size;
	bool **array2DStates;
	bool *arrayVisited;
	int **array2DValues;
	int *stringToInt(std::string);
	int getArraySize(std::string filename);
	void setArrays2D();

public:
	explicit ReadFromFile(std::string);
	bool **getArray2DStates();
	int **getArray2DValues();
	int getSizeArray();
	bool * getArrayVisited();
	void showReadFile();
	~ReadFromFile();
};

