// Breakout2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include <list>
#include "Ball.h"
#include <chrono>
#include "Brick.h"
#include "Paddle.h"
#include "BottomBorder.h"

using namespace std;
using namespace sf;
using namespace sfp;
using namespace std::chrono;

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
#pragma region MakeBricks
    Brick bricks[BRICKROWS * BRICKCOLUMNS];
    Vector2f brickAndBorderSize = BRICKSIZE + BRICKBORDER;
    int originX = (WINDOWSIZE.x/2) - ((brickAndBorderSize.x * (float)BRICKCOLUMNS))/2;
    int originY = 100;
    for (int y = 0; y < BRICKROWS; y++) {
        for (int x = 0; x < BRICKCOLUMNS; x++) {
            Brick& brick = bricks[x + (y * BRICKCOLUMNS)];
            Vector2f topLeft = Vector2f(
                originX + ((BRICKSIZE.x + BRICKBORDER.x) * x),
                originY + ((BRICKSIZE.y + BRICKBORDER.y) * y));
            brick.setSize(BRICKSIZE);
            brick.setCenter((topLeft + (BRICKSIZE + BRICKBORDER) / 2.0f));
            brick.setFillColor(Color::Green);
            brick.setStatic(true);
            world.AddPhysicsBody(brick);
        }
    }
#pragma endregion Makes the brick wall

#pragma region MakeBall
    PhysicsCircle ball(Vector2f(400,550));
    ball.setRadius(5);
    ball.setCenter(Vector2f(400,550));
    ball.applyImpulse(Vector2f(0.05, -0.1)*5.0f);
    world.AddPhysicsBody(ball);
#pragma endregion

#pragma MakePaddle
    Paddle paddle;
    world.AddPhysicsBody(paddle);
#pragma 

#pragma region borders
    PhysicsRectangle leftBorder(Vector2f(6, 300), Vector2f(10, 600),true);
    world.AddPhysicsBody(leftBorder);
    PhysicsRectangle rightBorder(Vector2f(794, 300), Vector2f(10, 600),true);
    world.AddPhysicsBody(rightBorder);
    PhysicsRectangle topBorder(Vector2f(400, 6), Vector2f(800, 10),true);
    world.AddPhysicsBody(topBorder);
    BottomBorder bottomBorder(ball);
    world.AddPhysicsBody(bottomBorder);
#pragma endregion
#pragma region GameLoop
    Clock clock;
    Time lastTime = clock.getElapsedTime();
    while (!bottomBorder.collided) {
        Time current = clock.getElapsedTime();
        unsigned int deltaMs =
            (current - lastTime).asMilliseconds();
        if (deltaMs == 0) {
            // skip frame
            continue;
        }
        lastTime = current;
        world.UpdatePhysics(deltaMs);
        window.clear();
        for (auto& brick : bricks) {
            switch (brick.state) {
            case Brick::STATE::ACTIVE:
                window.draw(brick);
                break;
            case Brick::STATE::COLLIDED:
                world.RemovePhysicsBody(brick);
                brick.state = Brick::STATE::REMOVED;
                break;
            
            }           
        }
        window.draw(ball);
        window.draw(paddle);
        window.draw(leftBorder);
        window.draw(rightBorder);
        window.draw(topBorder);
        world.VisualizeAllBounds(window);
        window.display();
    }
    return 0;
#pragma endregion The update/render loop
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
