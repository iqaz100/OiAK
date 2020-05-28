#include "ReadFromFile.h"
#include <sstream>
#include <fstream>
#include <iostream>


ReadFromFile::ReadFromFile(std::string filename) : size(getArraySize(filename))
{
	fileName = filename;
	setArrays2D();
}


ReadFromFile::~ReadFromFile()
{
}

int * ReadFromFile::stringToInt(std::string line)
{
	int *tabtemp = new int[size];
	std::stringstream ss(line);
	std::stringstream stringtoint;
	int count = 0;
	while (ss >> tabtemp[count]) {
		count++;
	}
	return tabtemp;
}

int ReadFromFile::getArraySize(std::string filename)
{
	size_t tempSize;
	std::ifstream file(filename);
	std::string temp;
	while (std::getline(file,temp))
	{
		break;
	}
	file.close();
	std::stringstream ss(temp);
	ss >> tempSize;
	return tempSize;
}

void ReadFromFile::setArrays2D()
{
	array2DStates = new bool *[size];
	array2DValues = new int *[size];

	for (size_t i = 0; i < size; i++) {
		array2DStates[i] = new bool[size];
		array2DValues[i] = new int[size];
	}

	for (size_t x = 0; x < size; x++) {
		for (size_t y = 0; y < size; y++) {
			array2DStates[x][y] = false;
		}
	}
	std::ifstream file(fileName);
	std::string temp;
	int count = 0;
	bool firstline = true;
	while (std::getline(file, temp)) {
		if (firstline) {
			firstline = false;
			continue;
		}
		array2DValues[count] = stringToInt(temp);
		count++;
	}
	file.close();
}

bool ** ReadFromFile::getArray2DStates()
{
	return array2DStates;
}

int ** ReadFromFile::getArray2DValues()
{
	return array2DValues;
}

int ReadFromFile::getSizeArray()
{
	return size;
}

bool * ReadFromFile::getArrayVisited()
{
	arrayVisited = new bool[size];
	for (size_t i = 0; i < size; i++) {
		arrayVisited[i] = false;
	}
	return arrayVisited;
}

void ReadFromFile::showReadFile()
{
	std::ifstream file(fileName);
	std::string temp;
	int count = 0;
	bool firstline = true;
	while (std::getline(file, temp)) {
		if (firstline) {
			firstline = false;
			continue;
		}
		std::cout << temp << std::endl;
		count++;
	}
	file.close();
}
