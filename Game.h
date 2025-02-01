#pragma once
#include "Player.h"
#include "Hammer.h"
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <math.h>
#include "general.h"
#include "Ladder.h"
#include "Level.h"
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <map>
#include <string>
#include "FileHandler.h"
#include <ctime>
#include <sstream>
#include <cstdlib>   // For srand() and rand()

#define INTERVAL 170
#define SECOND 1000
#define ADDITIONALSCORE 100

class Game
{
 private:
  Level* currLevel;
  int score;

 public:
	 Game() : currLevel(nullptr), score(999){}
	 void updateScore(int points); 
	 void printScore(const Point& legend);  
	 Level* getLevel() { return currLevel; }
	 void setLevel(Level* newlevel) { system("cls");currLevel = newlevel; }
	 void startMenu(bool clearscreen=true);
	 void showInstructions();
	 std::map<int, Level>::iterator lvlSelect(map<int, Level>& levels);
	 void drawBorders();
	 void printLives(int lives, const Point& legend);
	 int showTime(const Point& legend, bool reset);
	 int getFloor(int ycoor); //an index from 0 to 7
     char getSlope(Point currpos, char board[][GameConfig::WIDTH - 2]);
	 bool LeaveLadder(const Point& currPos, const Ladder& lad, GameConfig::ARROWKEYS dir, char board[][GameConfig::WIDTH - 2]);
	 int nearLadder(Player* player, Ladder lad[], int size, GameConfig::ARROWKEYS dir, int* ladderindex, int* climb);
	 bool nearLadder(ClimbingGhost* clgh,const Ladder lad[],const int& size);
	 bool barrelsCheckHits(vector<Barrel>* barrels,const Player& playerPosition);
	 int objectDistanceFloor(const MovableObject& bar, int floor);
	 bool barrelsUpdateDirs(vector<Barrel>* barrels, char board[][GameConfig::WIDTH - 2], Player* mario);
	 bool marioHitsBarrel(vector<Barrel>& barrels, const Player& mario);
	 bool marioHitsGhost(vector<Ghost*>& ghosts, const Player& mario);
	 void ghostsChangeDir(vector<Ghost*> ghosts, char board[][GameConfig::WIDTH - 2],Ladder lad[],int size);
	 GameConfig::ARROWKEYS ghostReachedEdge(Ghost* gh, char board[][GameConfig::WIDTH - 2]);
	 void regularMoveGhost(Ghost* gh);
	 bool outOfBounds(const Point& pos);
	 void printBarrelTraces(vector<Barrel> barrels);
	 void printGhostsTraces(const vector<Ghost*>& ghosts);
	 void printMarioTrace(const Player& mario, const int& climb);
	 void pauseGame(const Player& mario, const vector<Barrel>& barrels, const vector<Ghost*>& ghosts, const int& climb);
	 void restart(Player* mario, Point marioStartPos, vector<Barrel>* barrels, int* timetonextbarrel, int* climb, int* jumpsecs, vector<Ghost*>* ghosts, const vector<Ghost*>& initposesghosts,bool printtrace);
	 void run(bool savemode, bool loadmode, bool silentmode);
	 void saveSeed(unsigned int seed, ofstream& file) { if (file) file << seed; }
	 unsigned int setSeed() { return static_cast<unsigned int>(std::time(nullptr)); };
	 void reduceLivesSaveMode(ofstream& resfile,const int& timePoint,const int& lives);
	 void printFloorTrace(const MovableObject* obj, char board[][GameConfig::WIDTH - 2]);
};