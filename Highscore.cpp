#include <iostream>
#include <stdio.h>
#include "Highscore.h"

using namespace std;

Highscore::Highscore() {}



void Highscore::reset() {
	m_LinesCleared = 0;
	m_Score = 0;
}

void Highscore::addScore(int m_Score) {
	m_TotalScore += m_Score;
}

void Highscore::draw(sf::RenderWindow& window) {
	window.draw(m_LvlText);
	window.draw(m_TotalScore);
	window.draw(m_LinesCleared);
}

//void Highscore::sumScore() {}
//void Highscore::scoreSystem(int num) {}

void Highscore::update(const sf::Time& dt) {
	m_ScoreText.setString(std::string{ "Score:\n" + std::to_string(m_TotalScore) });
}


int Highscore::getLvl() {
	int x = 1;
	return x;
}