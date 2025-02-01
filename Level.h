#pragma once
#include "Point.h"
#include <iostream>
#include "GameConfig.h"
#include "Ladder.h"
#include <cstring>
#include <stdlib.h>
#include "Barrel.h"
#include "Ghost.h"
#include "Hammer.h"
#include <vector>
#include "ClimbingGhost.h"

using namespace std;

//Class and its data were given by CHATGPT
class Level {

    char board[8][GameConfig::WIDTH - 2];
    Ladder* ladders;
    int numLadders;
    Point startPosMario;
    Point startPosPauline;
    Point startPosDonkeyKong;
    Hammer hammer;
    Point legendPos;
    LevelSettings barrelsSets;
    vector <Ghost*> ghosts;

public:

    Level() 
    {
        initLevel();
    }
    ~Level();
    void setBoardValue(int row, int col, char value);
    char getBoardValue(int row, int col) const;
    void addLadder(Ladder ladder);
    Ladder getLadder(int index) const;
    Ladder* getLadders() const { return ladders; }
    vector<Ghost*>& getGhosts()  { return ghosts;}
    void addGhost(Ghost* g) { ghosts.push_back(g); }
    int getNumLadders() const;
    void printBoard() const;
    void printLadders()const;
    void initializeBoard1();
    void initializeBoard2();
    char(*getBoardPointer())[GameConfig::WIDTH - 2];
    void setstartPosMario(Point p) { startPosMario.setX(p.getX());startPosMario.setY(p.getY()); }
    void setHammer(const Hammer& p) { hammer=p; }
    Hammer getHammer() { return hammer; }
    Point getstartPosMario() { return startPosMario; }
    void setstartPosPauline(Point p) { startPosPauline.setX(p.getX());startPosPauline.setY(p.getY()); }
    Point getLegendPos() { return legendPos; }
    void setLegendPos(Point p) { legendPos.setX(p.getX());legendPos.setY(p.getY()); }
    Point getstartPosPauline() { return startPosPauline; }
    void setstartPosDonkeyKong(Point p) { startPosDonkeyKong.setX(p.getX());startPosDonkeyKong.setY(p.getY()); }
    Point getstartPosDonkeyKong() { return startPosDonkeyKong; }
    LevelSettings& getLevelSettings() { return barrelsSets; }
    void initLevel();

    const Level& operator =(const Level& other) ;
};
