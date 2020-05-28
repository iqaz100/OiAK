#pragma once
#include <string>

class SaveToFile
{
private:
	std::string fileName;
	std::string mode;
	int count;
	int size;
	void createFileName(int size);

public:
	SaveToFile(std::string, int);
	void write(std::string path, int droga, int time, int size);
	void write(int time);
	~SaveToFile();
};

