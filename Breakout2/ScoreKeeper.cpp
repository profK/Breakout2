#include "ScoreKeeper.h"
#include <string>
using namespace std;

ScoreKeeper::ScoreKeeper(Font& fnt)
{
	setFont(fnt);
	setScore(0);
}

int ScoreKeeper::getScore()
{
	return score;
}

void ScoreKeeper::setScore(int s)
{
	score = s;
	string txt("");
	for(int i=6;i>=0;i--){
		int digit = s / pow(10, i);
		txt.append(to_string(digit));
		s -= s * pow(10, i);
	}
	setString(txt);
	FloatRect tbounds = getGlobalBounds();
	Vector2f pos = Vector2f(400, 50) -
		Vector2f(tbounds.width / 2, tbounds.height / 2);
	setPosition(pos);
}
