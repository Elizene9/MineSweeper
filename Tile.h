#pragma once
#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <map>
#include <iostream>

using namespace std;
class Tile
{
public:
	Tile();
	Tile(int x, int y, char mybit);
	int xPos;
	int yPos;
	int index;
	int surroundCount;
	bool mine;
	bool flip;
	void setBit(char bit);
	char curBit;
	bool flag;
	string status;
	string Reveal();
	vector<Tile*> adjacent;
	bool Flip();
	void setFlag();
	string myTexture;
	bool click;
};


