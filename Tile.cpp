#include "Tile.h"

Tile::Tile()
{
	surroundCount = 0;
	mine = false;
	xPos = 0;
	yPos = 0;
	status = "";
	flip = false;
	curBit = '0';
}

Tile::Tile(int x, int y, char mybit)
{
	xPos = x;
	yPos = y;
	surroundCount = 0;
	flag = false;
	status = "unrevealed";
	mine = false;
	curBit = mybit;
	flip = false;
	click = false;
}


bool Tile::Flip()
{
	status = "revealed";

	if (mine == false)
		return false;

	else
		return true;
}

void Tile::setFlag()
{
	if (flag == false)
		flag = true;

	else
		flag = false;
}

void Tile::setBit(char bit)
{
	curBit = bit;
}

string Tile::Reveal()
{
	if (surroundCount == 0)
		myTexture = "images/tile_revealed.png";

	else if (surroundCount == 1)
		myTexture = "images/number_1.png";

	else if (surroundCount == 2)
		myTexture = "images/number_2.png";

	else if (surroundCount == 3)
		myTexture = "images/number_3.png";

	else if (surroundCount == 4)
		myTexture = "images/number_4.png";

	else if (surroundCount == 5)
		myTexture = "images/number_5.png";

	else if (surroundCount == 6)
		myTexture = "images/number_6.png";

	else if (surroundCount == 7)
		myTexture = "images/number_7.png";

	else if (surroundCount == 8)
		myTexture = "images/number_8.png";

	return myTexture;
}