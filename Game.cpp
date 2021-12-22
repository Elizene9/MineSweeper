#include "Game.h"
Game::Game()
{
	finished = false;
	width = 32;
	height = 32;
	rows = 1;
	columns = 1;
	GameOver = false;
	numMines = 0;
	spaces = 0;
	debug = false;
	test1 = false;
	test2 = false;
	test3 = false;
	givenMines = 0;
	numFlags = 0;
	setMines = 0;
}

Game::Game(bool term, int wid, int hei, int numrows, int cols, int given)
{
	numFlags = 0;
	finished = false;
	test1 = false;
	test2 = false;
	test3 = false;
	width = wid;
	height = hei;
	rows = numrows;
	columns = cols;
	GameOver = false;
	debug = false;
	numMines = 0;
	spaces = 0;
	givenMines = given;
	setMines = given;
}

void Game::test1Pressed()
{
	givenMines = 0;
	numFlags = 0;
	allGameTiles.clear();
	finished = false;
	GameOver = false;
	debug = false;
	numMines = 0;
	spaces = 0;
	fstream file1;
	file1.open("boards/testboard1.brd");

	for (int i = 0; i < height - 88; i += 32)
	{
		for (int j = 0; j < width; j += 32)
		{
			char create;
			file1.read((char*)&create, 1);
			if (i > height - 88 || j > width)
				return;
			Tile newTile(j, i, create);
			newTile.index = allGameTiles.size();

			if (create == '1')
			{
				givenMines++;
				newTile.mine = true;
				numMines++;
			}

			else
			{
				newTile.mine = false;
				spaces++;
			}

			allGameTiles.push_back(newTile);
		}
	}
	setAdjacents();
	for (int g = 0; g < allGameTiles.size(); g++)
	{
		for (int f = 0; f < allGameTiles.at(g).adjacent.size(); f++)
		{
			if (allGameTiles.at(g).adjacent.at(f)->mine == true)
				allGameTiles.at(g).surroundCount += 1;
		}
	}
	test1 = true;
	file1.close();
}

void Game::test2Pressed()
{
	givenMines = 0;
	numFlags = 0;
	allGameTiles.clear();
	finished = false;
	GameOver = false;
	debug = false;
	numMines = 0;
	spaces = 0;

	fstream file1;
	file1.open("boards/testboard2.brd");

	for (int i = 0; i < height - 88; i += 32)
	{
		for (int j = 0; j < width; j += 32)
		{
			char create;
			file1.read((char*)&create, 1);
			if (i > height - 88 || j > width)
				return;

			Tile newTile(j, i, create);
			newTile.index = allGameTiles.size();

			if (create == '1')
			{
				givenMines++;
				newTile.mine = true;
				numMines++;
			}

			else
			{
				newTile.mine = false;
				spaces++;
			}
			newTile.index = allGameTiles.size();

			allGameTiles.push_back(newTile);
		}
		char newline;
		file1.read((char*)&newline, 1);
	}
	setAdjacents();
	for (int g = 0; g < allGameTiles.size(); g++)
	{
		for (int f = 0; f < allGameTiles.at(g).adjacent.size(); f++)
		{
			if (allGameTiles.at(g).adjacent.at(f)->mine == true)
				allGameTiles.at(g).surroundCount += 1;
		}
	}
	test2 = true;
	file1.close();
}

void Game::test3Pressed()
{
	givenMines = 0;
	numFlags = 0;
	allGameTiles.clear();
	finished = false;
	GameOver = false;
	debug = false;
	numMines = 0;
	spaces = 0;
	fstream file1;
	file1.open("boards/testboard3.brd");

	for (int i = 0; i < height - 88; i += 32)
	{
		for (int j = 0; j < width; j += 32)
		{
			char create;
			file1.read((char*)&create, 1);
			if (i > height - 88 || j > width)
				return;
			Tile newTile(j, i, create);
			newTile.index = allGameTiles.size();

			if (create == '1')
			{
				givenMines++;
				newTile.mine = true;
				numMines++;
			}

			else
			{
				newTile.mine = false;
				spaces++;
			}

			allGameTiles.push_back(newTile);
		}
	}
	setAdjacents();
	for (int g = 0; g < allGameTiles.size(); g++)
	{
		for (int f = 0; f < allGameTiles.at(g).adjacent.size(); f++)
		{
			if (allGameTiles.at(g).adjacent.at(f)->mine == true)
				allGameTiles.at(g).surroundCount += 1;
		}
	}
	test3 = true;
	file1.close();
}

bool Game::debugPressed()
{
	if (debug == false)
		debug = true;

	else
		debug = false;

	return debug;
}

void Game::newBoard()
{
	srand(time(NULL));
	trueMines.clear();
	givenMines = setMines;
	allGameTiles.clear();
	test1 = false;
	test2 = false;
	test3 = false;
	finished = false;
	GameOver = false;
	debug = false;
	numMines = 0;
	spaces = 0;

	for (int i = 0; i < height - 88; i += 32)
	{
		for (int j = 0; j < width; j += 32)
		{
			if (i > height - 88 || j > width)
				return;

			Tile newTile(j, i, '0');
			newTile.index = allGameTiles.size();
			newTile.mine = false;
			spaces++;
			allGameTiles.push_back(newTile);

		}
	}

	for (int f = 0; f < setMines; f++)
	{
		int mine = rand() % allGameTiles.size();
		if (allGameTiles.at(mine).mine == true)
		{
			while (allGameTiles.at(mine).mine == true)
			{
				mine = rand() % allGameTiles.size();
			}
		}
		allGameTiles.at(mine).mine = true;
		numMines++;
		spaces--;


	}
	setAdjacents();

	for (int g = 0; g < allGameTiles.size(); g++)
	{
		for (int f = 0; f < allGameTiles.at(g).adjacent.size(); f++)
			if (allGameTiles.at(g).adjacent.at(f)->mine == true)
				allGameTiles.at(g).surroundCount += 1;
	}
}
void Game::setAdjacents()
{
	for (int h = 0; h < allGameTiles.size(); h++)
	{
		if (allGameTiles.at(h).xPos != 0 && allGameTiles.at(h).yPos != 0 && allGameTiles.at(h).xPos != width - 32 && allGameTiles.at(h).yPos != height - 120)
		{
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h + 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h + columns));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h + columns + 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h + columns - 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - columns - 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - columns));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - columns + 1));
		}
		else if (allGameTiles.at(h).yPos == 0 && allGameTiles.at(h).xPos == 0)
		{
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(columns));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(columns + 1));
		}

		else if (allGameTiles.at(h).yPos == 0 && allGameTiles.at(h).xPos != 0 && allGameTiles.at(h).xPos != width - 32)
		{
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h + 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(columns + h));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(columns + h + 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(columns + h - 1));
		}

		else if (allGameTiles.at(h).yPos != 0 && allGameTiles.at(h).yPos != height - 120 && allGameTiles.at(h).xPos == 0)
		{
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h + 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h + columns));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(columns + h + 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - columns));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - columns + 1));
		}

		else if (allGameTiles.at(h).yPos == height - 120 && allGameTiles.at(h).xPos != 0 && allGameTiles.at(h).xPos != width - 32)
		{
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h + 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - columns));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - columns + 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - columns - 1));
		}

		else if (allGameTiles.at(h).yPos != height - 120 && allGameTiles.at(h).yPos != 0 && allGameTiles.at(h).xPos == width - 32)
		{
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h + columns));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - columns));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h + columns - 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - columns - 1));
		}

		else if (allGameTiles.at(h).yPos == height - 120 && allGameTiles.at(h).xPos == width - 32)
		{
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - columns - 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - columns));
		}

		else if (allGameTiles.at(h).yPos == 0 && allGameTiles.at(h).xPos == width - 32)
		{
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h + columns));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h + columns - 1));
		}

		else if (allGameTiles.at(h).yPos == height - 120 && allGameTiles.at(h).xPos == 0)
		{
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h + 1));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - columns));
			allGameTiles.at(h).adjacent.push_back(&allGameTiles.at(h - columns + 1));
		}
	}
}

int Game::mineCounter(char number)
{
	return ((int)number - 48) * 21;
}
