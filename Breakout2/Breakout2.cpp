// Breakout2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include <list>

using namespace std;
using namespace sf;
using namespace sfp;

const Vector2f WINDWOSIZE(800, 600);
const Vector2f BRICKSIZE(50, 20);
const Vector2f BRICKBORDER(10, 10);
const Vector2f WINDOWSIZE(800, 600);
const int BRICKROWS = 8;
const int BRICKCOLUMNS = 8;


int main()
{
    RenderWindow window(VideoMode(WINDOWSIZE.x,WINDOWSIZE.y),"Breakout2");
    World world(Vector2f(0, 0));
#pragma section //Make the Brick Wall
    PhysicsRectangle bricks[BRICKROWS * BRICKCOLUMNS];
    Vector2f brickAndBorderSize = BRICKSIZE + BRICKBORDER;
    int originX = (WINDOWSIZE.x/2) - ((brickAndBorderSize.x * (float)BRICKCOLUMNS))/2;
    int originY = 100;
    for (int y = 0; y < BRICKROWS; y++) {
        for (int x = 0; x < BRICKCOLUMNS; x++) {
            PhysicsRectangle& brick = bricks[x + (y * BRICKCOLUMNS)];
            Vector2f topLeft = Vector2f(
                originX + ((BRICKSIZE.x + BRICKBORDER.x) * x),
                originY + ((BRICKSIZE.y + BRICKBORDER.y) * y));
            brick.setCenter((topLeft + (BRICKSIZE + BRICKBORDER) / 2.0f));
            brick.setSize(BRICKSIZE);
            brick.setFillColor(Color::Green);
        }
    }
#pragma endsection
    while (true) {
        window.clear();
        for (auto brick : bricks) {
            window.draw(brick);
        }
        window.display();
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
