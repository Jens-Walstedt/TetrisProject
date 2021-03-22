#include <iostream>
#include <stdio.h>
#include "Highscore.h"

using namespace std;

Highscore::Highscore() : m_ScoreText() {
	m_TotalScore = 0;
	m_Score = 0;
	m_LinesCleared = 0;

	m_ScoreText.setStyle(sf::Text::Bold);
	m_ScoreText.setCharacterSize(15);
	m_ScoreText.setPosition(sf::Vector2f{0,0});
}

void Highscore::reset() {
	m_LinesCleared = 0;
	m_Score = 0;
}

void Highscore::addScore(int m_Score) {
	m_TotalScore += m_Score;
}

void Highscore::draw(sf::RenderWindow& window) {
	window.draw(m_ScoreText);
}

//void Highscore::sumScore() {}
//void Highscore::scoreSystem(int num) {}

void Highscore::update(const sf::Time& dt) {
	m_ScoreText.setString(std::string{ "Score:\n" + std::to_string(m_TotalScore) });
}


int Highscore::getLvl() const {
	int x = 1;
	return x;
}