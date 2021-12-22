#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <fstream>
#include "Game.h"
#include "Tile.h"
#include <stdlib.h>

using namespace std;

int main()
{
    string myCol, myRows, myMines;
    bool myClick = false;
    int cols, rows, numMines, width, height, numTiles, winSize, stopX, stopY, myCount = 0;
    ifstream CFG;
    CFG.open("boards/config.cfg");

    getline(CFG, myCol);
    cols = stoi(myCol);
    getline(CFG, myRows);
    rows = stoi(myRows);
    getline(CFG, myMines);
    numMines = stoi(myMines);
    width = cols * 32;
    height = (rows * 32) + 88;
    winSize = width * height;
    numTiles = rows * cols;
    CFG.close();
    Game myGame(false, width, height, rows, cols, numMines);
    myGame.newBoard();
    sf::RenderWindow window(sf::VideoMode(width, height), "MineSweeper");
    sf::Texture texture, texture2, Happy, Debug, Test1, Test2, Test3, Mine, Digits, Current, mywin, myloss, myFlag;
    texture.loadFromFile("images/tile_hidden.png");
    texture2.loadFromFile("images/tile_revealed.png");
    Digits.loadFromFile("images/digits.png");
    Happy.loadFromFile("images/face_happy.png");
    mywin.loadFromFile("images/face_win.png");
    Debug.loadFromFile("images/debug.png");
    Test1.loadFromFile("images/test_1.png");
    Test2.loadFromFile("images/test_2.png");
    Test3.loadFromFile("images/test_3.png");
    Mine.loadFromFile("images/mine.png");
    myloss.loadFromFile("images/face_lose.png");
    myFlag.loadFromFile("images/flag.png");
    vector<sf::Sprite> allSprites;
    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        sf::Sprite happy, one, two, three, dbg, digits;
        float pos = width / 2 + 96;

        // Game Over Conditions
        if (myGame.finished == false && myGame.debug == false && myGame.GameOver == false)
        {
            happy.setTexture(Happy);
            myGame.test1 = false;
            myGame.test2 = false;
            myGame.test3 = false;
        }

        else if (myGame.finished == true && myGame.GameOver == true && myGame.debug != true)
        {
            happy.setTexture(myloss);
            myGame.test1 = false;
            myGame.test2 = false;
            myGame.test3 = false;
        }

        else if (myGame.finished == true && myGame.GameOver == false)
        {
            happy.setTexture(mywin);
            myGame.test1 = false;
            myGame.test2 = false;
            myGame.test3 = false;
        }

        // Debug Conditions
        else if (myGame.debug == true && myGame.finished == false)
        {
            happy.setTexture(Happy);
            myGame.test1 = false;
            myGame.test2 = false;
            myGame.test3 = false;
        }

        happy.setPosition(width / 2 - 32, height - 88);
        window.draw(happy);
        dbg.setTexture(Debug);
        dbg.setPosition(pos, height - 88);
        pos += 64;
        one.setTexture(Test1);
        one.setPosition(pos, height - 88);
        pos += 64;
        two.setTexture(Test2);
        two.setPosition(pos, height - 88);
        pos += 64;
        three.setTexture(Test3);
        three.setPosition(pos, height - 88);
        window.draw(dbg);
        window.draw(one);
        window.draw(two);
        window.draw(three);

        if (myGame.finished == false)
        {
            myGame.numFlags = myGame.givenMines;
            for (int x = 0; x < myGame.allGameTiles.size(); x++)
            {
                sf::Sprite sprite;
                sf::Sprite sprite2;
                sf::Sprite mySprite;

                if (myGame.allGameTiles.at(x).flip == false && myGame.allGameTiles.at(x).flag == false)
                {
                    sprite.setPosition(myGame.allGameTiles.at(x).xPos, myGame.allGameTiles.at(x).yPos);
                    sprite.setTexture(texture);
                    window.draw(sprite);

                    if (myCount == 0)
                        allSprites.push_back(sprite);
                }

                else if (myGame.allGameTiles.at(x).flag == true && myGame.allGameTiles.at(x).flip == false)
                {
                    sprite.setTexture(myFlag);
                    sprite.setPosition(myGame.allGameTiles.at(x).xPos, myGame.allGameTiles.at(x).yPos);
                    sprite2.setTexture(texture2);
                    sprite2.setPosition(myGame.allGameTiles.at(x).xPos, myGame.allGameTiles.at(x).yPos);
                    window.draw(sprite2);
                    window.draw(sprite);
                    myGame.numFlags--;
                }

                else if (myGame.allGameTiles.at(x).flip == true && myGame.allGameTiles.at(x).flag == false)
                {
                    if (myGame.allGameTiles.at(x).mine == true)
                    {
                        sprite.setPosition(myGame.allGameTiles.at(x).xPos, myGame.allGameTiles.at(x).yPos);
                        sprite.setTexture(texture2);
                        sprite2.setPosition(myGame.allGameTiles.at(x).xPos, myGame.allGameTiles.at(x).yPos);
                        sprite2.setTexture(Mine);
                        window.draw(sprite);
                        window.draw(sprite2);
                        myGame.debug = false;
                        myGame.finished = true;
                        myGame.GameOver = true;
                    }

                    else if (myGame.allGameTiles.at(x).mine == false && myGame.allGameTiles.at(x).surroundCount != 0)
                    {
                        Current.loadFromFile(myGame.allGameTiles.at(x).Reveal());
                        sprite.setPosition(myGame.allGameTiles.at(x).xPos, myGame.allGameTiles.at(x).yPos);
                        sprite2.setTexture(texture2);
                        sprite2.setPosition(myGame.allGameTiles.at(x).xPos, myGame.allGameTiles.at(x).yPos);
                        window.draw(sprite2);
                        sprite.setTexture(Current);
                        window.draw(sprite);
                    }

                    else if (myGame.allGameTiles.at(x).mine == false && myGame.allGameTiles.at(x).surroundCount == 0)
                    {
                        sprite2.setTexture(texture2);
                        sprite2.setPosition(myGame.allGameTiles.at(x).xPos, myGame.allGameTiles.at(x).yPos);
                        window.draw(sprite2);
                        for (int v = 0; v < myGame.allGameTiles.at(x).adjacent.size(); v++)
                        {
                            myGame.allGameTiles.at(x).adjacent.at(v)->flip = true;
                            Current.loadFromFile(myGame.allGameTiles.at(x).adjacent.at(v)->Reveal());
                            sprite.setPosition(myGame.allGameTiles.at(x).adjacent.at(v)->xPos, myGame.allGameTiles.at(x).adjacent.at(v)->yPos);
                            sprite.setTexture(texture2);
                            mySprite.setPosition(myGame.allGameTiles.at(x).adjacent.at(v)->xPos, myGame.allGameTiles.at(x).adjacent.at(v)->yPos);
                            mySprite.setTexture(Current);
                            window.draw(sprite);
                            window.draw(mySprite);
                        }
                    }
                }

                if (x == myGame.allGameTiles.size() - 1)
                    myCount = 500;
            }
        }

        else if (myGame.finished == true && myGame.debug == false)
        {
            for (int x = 0; x < myGame.allGameTiles.size(); x++)
            {
                sf::Sprite sprite;
                sf::Sprite sprite2;
                sf::Sprite mySprite;

                if (myGame.allGameTiles.at(x).mine == true)
                {
                    sprite.setPosition(myGame.allGameTiles.at(x).xPos, myGame.allGameTiles.at(x).yPos);
                    sprite.setTexture(texture2);

                    if (myGame.GameOver == false) {
                        sprite2.setPosition(myGame.allGameTiles.at(x).xPos, myGame.allGameTiles.at(x).yPos);
                        sprite2.setTexture(myFlag);
                    }

                    else
                    {
                        sprite2.setPosition(myGame.allGameTiles.at(x).xPos, myGame.allGameTiles.at(x).yPos);
                        sprite2.setTexture(Mine);
                    }
                    window.draw(sprite);
                    window.draw(sprite2);
                }

                else if (myGame.allGameTiles.at(x).mine == false && myGame.allGameTiles.at(x).surroundCount != 0)
                {
                    Current.loadFromFile(myGame.allGameTiles.at(x).Reveal());
                    sprite.setPosition(myGame.allGameTiles.at(x).xPos, myGame.allGameTiles.at(x).yPos);
                    sprite2.setTexture(texture2);
                    sprite2.setPosition(myGame.allGameTiles.at(x).xPos, myGame.allGameTiles.at(x).yPos);
                    sprite.setTexture(Current);
                    window.draw(sprite2);
                    window.draw(sprite);
                }

                else if (myGame.allGameTiles.at(x).mine == false && myGame.allGameTiles.at(x).surroundCount == 0)
                {
                    sprite2.setTexture(texture2);
                    sprite2.setPosition(myGame.allGameTiles.at(x).xPos, myGame.allGameTiles.at(x).yPos);
                    window.draw(sprite2);
                    for (int v = 0; v < myGame.allGameTiles.at(x).adjacent.size(); v++)
                    {
                        Current.loadFromFile(myGame.allGameTiles.at(x).adjacent.at(v)->Reveal());
                        sprite.setPosition(myGame.allGameTiles.at(x).adjacent.at(v)->xPos, myGame.allGameTiles.at(x).adjacent.at(v)->yPos);
                        sprite.setTexture(texture2);
                        mySprite.setTexture(Current);
                        mySprite.setPosition(myGame.allGameTiles.at(x).adjacent.at(v)->xPos, myGame.allGameTiles.at(x).adjacent.at(v)->yPos);
                        window.draw(sprite);
                        window.draw(mySprite);
                    }
                }
            }
        }

        if (myGame.debug == true && myGame.finished == false)
        {
            for (int x = 0; x < myGame.allGameTiles.size(); x++)
            {
                sf::Sprite sprite;
                sf::Sprite sprite2;

                if (myGame.allGameTiles.at(x).mine == true)
                {
                    sprite2.setPosition(myGame.allGameTiles.at(x).xPos, myGame.allGameTiles.at(x).yPos);
                    sprite2.setTexture(Mine);
                    window.draw(sprite2);
                }
            }
        }

        int counter = 0;
        for (int i = 0; i < myGame.allGameTiles.size(); i++)
            if (myGame.allGameTiles.at(i).flip == true && myGame.allGameTiles.at(i).mine == false)
                counter++;

        if (counter == myGame.spaces) {
            myGame.finished = true;
            myGame.debug = false;
        }

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
            {
                sf::Vector2f mymouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (int t = 0; t < allSprites.size(); t++)
                {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        if (allSprites.at(t).getGlobalBounds().contains(mymouse)) {

                            if (myGame.allGameTiles.at(t).flag != true) {
                                myGame.allGameTiles.at(t).flip = true;
                                break;
                            }
                        }
                    }

                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    {
                        if (allSprites.at(t).getGlobalBounds().contains(mymouse)) {
                            if (myGame.allGameTiles.at(t).flip != true) {
                                myGame.allGameTiles.at(t).setFlag();
                                break;
                            }
                        }
                    }
                }
                if (dbg.getGlobalBounds().contains(mymouse) && myGame.finished == false)
                    myGame.debug = myGame.debugPressed();

                else if (one.getGlobalBounds().contains(mymouse) && myGame.test1 == false)
                    myGame.test1Pressed();

                else if (two.getGlobalBounds().contains(mymouse) && myGame.test2 == false)
                    myGame.test2Pressed();

                else if (three.getGlobalBounds().contains(mymouse) && myGame.test3 == false)
                    myGame.test3Pressed();

                else if (happy.getGlobalBounds().contains(mymouse))
                    myGame.newBoard();
            }

            break;

            default:
                break;
            }
        }

        string flagCounter = to_string(myGame.numFlags);

        sf::Sprite counter1, counter2, counter3, counter4;
        counter1.setTexture(Digits);
        counter2.setTexture(Digits);
        counter3.setTexture(Digits);
        counter4.setTexture(Digits);
        counter4.setPosition(0, height - 88);
        counter3.setPosition(96, height - 88);
        counter2.setPosition(64, height - 88);
        counter1.setPosition(32, height - 88);
        sf::Vector2<int> zero(0, 0);
        sf::Vector2<int> tens(0, 0);
        sf::Vector2<int> mySize(21, 32);
        if (myGame.numFlags >= 0)
        {
            if (myGame.numFlags < 10) {
                sf::Vector2<int> vector1(myGame.mineCounter(flagCounter[0]), 0);

                sf::Rect<int> myRect(vector1, mySize);
                sf::Rect<int> myRect2(zero, mySize);
                counter1.setTextureRect(myRect2);
                counter2.setTextureRect(myRect2);
                counter3.setTextureRect(myRect);
                window.draw(counter1);
                window.draw(counter2);
                window.draw(counter3);
            }

            else if (myGame.numFlags >= 10 && myGame.numFlags < 100)
            {
                sf::Vector2<int> vector1(myGame.mineCounter(flagCounter[0]), 0);
                sf::Vector2<int> vector2(myGame.mineCounter(flagCounter[1]), 0);
                sf::Rect<int> myRect(vector2, mySize);
                sf::Rect<int> myRect2(vector1, mySize);
                sf::Rect<int> myRect3(zero, mySize);
                counter1.setTextureRect(myRect3);
                counter2.setTextureRect(myRect2);
                counter3.setTextureRect(myRect);
                window.draw(counter1);
                window.draw(counter2);
                window.draw(counter3);
            }

            else if (myGame.numFlags >= 100 && myGame.numFlags < 1000)
            {
                sf::Vector2<int> vector1(myGame.mineCounter(flagCounter[0]), 0);
                sf::Vector2<int> vector2(myGame.mineCounter(flagCounter[1]), 0);
                sf::Vector2<int> vector3(myGame.mineCounter(flagCounter[2]), 0);
                sf::Rect<int> myRect(vector1, mySize);
                sf::Rect<int> myRect2(vector2, mySize);
                sf::Rect<int> myRect3(vector3, mySize);
                counter1.setTextureRect(myRect);
                counter2.setTextureRect(myRect2);
                counter3.setTextureRect(myRect3);
                window.draw(counter1);
                window.draw(counter2);
                window.draw(counter3);
            }
        }

        else
        {
            if (0 - myGame.numFlags < 10) {
                sf::Vector2<int> vector1(myGame.mineCounter(flagCounter[1]), 0);
                sf::Vector2<int> vector4(21 * 10, 0);
                sf::Rect<int> myRect(vector1, mySize);
                sf::Rect<int> myRect2(zero, mySize);
                sf::Rect<int> myRect4(vector4, mySize);
                counter1.setTextureRect(myRect2);
                counter2.setTextureRect(myRect2);
                counter3.setTextureRect(myRect);
                counter4.setTextureRect(myRect4);
                window.draw(counter1);
                window.draw(counter2);
                window.draw(counter3);
                window.draw(counter4);
            }

            else if (0 - myGame.numFlags >= 10 && 0 - myGame.numFlags < 100)
            {
                sf::Vector2<int> vector2(myGame.mineCounter(flagCounter[1]), 0);
                sf::Vector2<int> vector3(myGame.mineCounter(flagCounter[2]), 0);
                sf::Vector2<int> vector4(21 * 10, 0);
                sf::Rect<int> myRect(zero, mySize);
                sf::Rect<int> myRect2(vector2, mySize);
                sf::Rect<int> myRect3(vector3, mySize);
                sf::Rect<int> myRect4(vector4, mySize);
                counter1.setTextureRect(myRect);
                counter2.setTextureRect(myRect2);
                counter3.setTextureRect(myRect3);
                counter4.setTextureRect(myRect4);
                window.draw(counter1);
                window.draw(counter2);
                window.draw(counter3);
                window.draw(counter4);
            }

            else if (0 - myGame.numFlags >= 100 && 0 - myGame.numFlags < 1000)
            {
                sf::Vector2<int> vector1(myGame.mineCounter(flagCounter[1]), 0);
                sf::Vector2<int> vector2(myGame.mineCounter(flagCounter[2]), 0);
                sf::Vector2<int> vector3(myGame.mineCounter(flagCounter[3]), 0);
                sf::Vector2<int> vector4(21 * 10, 0);
                sf::Rect<int> myRect(vector1, mySize);
                sf::Rect<int> myRect2(vector2, mySize);
                sf::Rect<int> myRect3(vector3, mySize);
                sf::Rect<int> myRect4(vector4, mySize);
                counter1.setTextureRect(myRect);
                counter2.setTextureRect(myRect2);
                counter3.setTextureRect(myRect3);
                counter4.setTextureRect(myRect4);
                window.draw(counter1);
                window.draw(counter2);
                window.draw(counter3);
                window.draw(counter4);
            }
        }
        window.display();
    }

    return 0;
}