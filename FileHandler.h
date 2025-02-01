#pragma once
#include "Level.h"
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <map>
#include <experimental/filesystem>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <cctype> // for std::isspace




namespace fs = std::experimental::filesystem;
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define FILELEN 15


class FileHandler
{
private:
	 static bool starts_with(const std::string& str, const std::string& prefix);
	 static bool ends_with(const std::string& str, const std::string& suffix);
	 static int containValidNumber(const std::string& str);
	 static int checkFileNameValidity(const string& name);
	 static bool readFileContent(const string& name,Level& tobuild);
	 static int getFloorFile(int numline);
	
	 

public:
	static bool loadAllFiles(map<int, Level>& alllevels);
	static void deleteDocFiles();

};

struct Step {
	int timeStep;                        // The in-game time counter (each iteration)
	GameConfig::ARROWKEYS move;            // The movement key (as defined in GameConfig)
	bool hammerUsed;                     // True if the hammer was used at this time step
};

