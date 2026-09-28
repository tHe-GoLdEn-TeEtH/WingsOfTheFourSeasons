#ifndef SAVELOAD_H
#define SAVELOAD_H
#include <fstream>
#include <cstring>

bool hasSaveData = false;
char savedPlayerName[20] = "";
int savedLevel = 1;
int savedElapsedTime = 0;

void loadSaveData()
{
	std::ifstream file("save.txt");
	if (!file.is_open())
	{
		hasSaveData = false;
		return;
	}

	char name[20];
	int level;
	int elapsed;

	file.getline(name, 20, ',');
	file >> level;
	file.ignore();
	file >> elapsed;

	if (file.fail())
	{
		hasSaveData = false;
		file.close();
		return;
	}

	strcpy_s(savedPlayerName, name);
	savedLevel = level;
	savedElapsedTime = elapsed;
	hasSaveData = true;

	file.close();
}

void writeSaveData(char playerName[], int level, int elapsedSeconds)
{
	std::ofstream file("save.txt");
	file << playerName << "," << level << "," << elapsedSeconds << "\n";
	file.close();

	strcpy_s(savedPlayerName, playerName);
	savedLevel = level;
	savedElapsedTime = elapsedSeconds;
	hasSaveData = true;
}

#endif