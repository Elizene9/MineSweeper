#pragma once
#include "Tile.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <random>
#include <string>
class Game
{
public:
	Game();
	Game(bool term, int wid, int hei, int numrows, int cols, int given);
	int width;
	int numMines;
	int spaces;
	int height;
	int rows;
	int columns;
	bool debug;
	bool finished;
	bool GameOver;
	bool test1;
	bool test2;
	bool test3;
	int givenMines;
	int setMines;
	int numFlags;
	vector<Tile> allGameTiles;
	vector<int> trueMines;
	void newBoard();
	void test1Pressed();
	void test2Pressed();
	void test3Pressed();
	bool debugPressed();
	void setAdjacents();
	int mineCounter(char number);
};



