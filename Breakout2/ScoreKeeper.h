#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class ScoreKeeper :
    public Text
{
private:
    int score;
public:
    ScoreKeeper(Font& fnt);
    int getScore();
    void setScore(int s);
};

