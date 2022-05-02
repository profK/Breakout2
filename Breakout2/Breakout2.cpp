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
#include "ScoreKeeper.h"

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
const int WINDOWBORDER = 20;
const int BALLCOUNT = 5;


int main()
{
    RenderWindow window(VideoMode(WINDOWSIZE.x,WINDOWSIZE.y),"Breakout2");
    World world(Vector2f(0, 0));

#pragma region MakeGameOver
    Font fnt;
    if (!fnt.loadFromFile("arial.ttf")) {
        cout << "Couldnt load arial.ttf" << endl;
        exit(1);
    }
    ScoreKeeper score(fnt);
#pragma endregion

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
            brick.getShape().setFillColor(Color::Green);
            brick.getBody().setStatic(true);
            world.AddPhysicsBody(brick.getBody());
        }
    }
#pragma endregion Makes the brick wall

#pragma region MakeBall
    PhysicsCircle ball;
    ball.setSize(Vector2f(5,5));
    ball.setCenter(Vector2f(400,550));
    ball.getBody().applyImpulse(Vector2f(0.05, -0.1)*3.0f);
    world.AddPhysicsBody(ball.getBody());
#pragma endregion

#pragma region MakePaddle
    Paddle paddle;
    world.AddPhysicsBody(paddle.getBody());
#pragma endregion

#pragma region borders
    PhysicsRectangle leftBorder;
    leftBorder.setCenter(Vector2f(WINDOWBORDER / 2, 300));
    leftBorder.setSize(Vector2f(WINDOWBORDER, 600));
    leftBorder.getBody().setStatic(true);
    world.AddPhysicsBody(leftBorder.getBody());
    PhysicsRectangle rightBorder;
    rightBorder.setCenter(Vector2f(800 - (WINDOWBORDER / 2), 300));
    rightBorder.setSize(Vector2f(WINDOWBORDER, 600));
    rightBorder.getBody().setStatic(true);
    world.AddPhysicsBody(rightBorder.getBody());
    PhysicsRectangle topBorder;
    topBorder.setCenter(Vector2f(400, WINDOWBORDER / 2));
    topBorder.setSize(Vector2f(800, WINDOWBORDER));
    topBorder.getBody().setStatic(true);
    world.AddPhysicsBody(topBorder.getBody());
    BottomBorder bottomBorder(ball.getBody());
    world.AddPhysicsBody(bottomBorder.getBody());
#pragma endregion
#pragma region GameLoop
    Clock clock;
    Time lastTime = clock.getElapsedTime();
    bool done = false;
    int ballCount = BALLCOUNT;
    while (!done) {
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
        done = true;
        for (auto& brick : bricks) {
            switch (brick.state) {
            case Brick::STATE::ACTIVE:
                window.draw(brick.getShape());
                done = false;
                break;
            case Brick::STATE::COLLIDED:
                world.RemovePhysicsBody(brick.getBody());
                brick.state = Brick::STATE::REMOVED;
                score.setScore(score.getScore() + 5);
                break;
            
            }           
        }
        if (bottomBorder.collided) {
            if (ballCount == 1) { // drained last ball
                done = true;
            }else {
                ballCount--;
                ball.setCenter(Vector2f(400, 550));
                ball.getBody().setVelocity(Vector2f(0.05, -0.1) * 3.0f);
                bottomBorder.collided = false; // reset collisio
            }
        }
        window.draw(ball.getShape());
        window.draw(paddle.getShape());
        window.draw(leftBorder.getShape());
        window.draw(rightBorder.getShape());
        window.draw(topBorder.getShape());
        window.draw(score);
        world.VisualizeAllBounds(window);
        window.display();
    }


    //end game loop
    Text endText;
    endText.setFont(fnt);
    endText.setString("GAME OVER");
    FloatRect sz = endText.getGlobalBounds();
    endText.setPosition(Vector2f(400 - (sz.width / 2), 300 - (sz.height / 2)));
    while (true) {
        window.clear();
        window.draw(endText);
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
