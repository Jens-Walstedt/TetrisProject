#include <iostream>
#include <stdio.h>
#include "Highscore.h"

using namespace std;

Highscore::Highscore() : m_ScoreText() {
	m_TotalScore = 0;
	m_Score = 0;
	m_LinesCleared = 0;
	m_BonusScore = 0;

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

void Highscore::sumScore() 
{
	m_Score += m_BonusScore;
	m_BonusScore = 0;
}
void Highscore::scoreSystem(int num) 
{
	m_LinesCleared += num;
	int lvl = m_LinesCleared / 10;
	switch (num)
	{
	case(1):
		m_Score += 40 * (lvl + 1);
		break;
	case(2):
		m_Score += 100 * (lvl + 1);
		break;
	case(3):
		m_Score += 400 * (lvl + 1);
		break;
	case(4):
		m_Score += 1200 * (lvl + 1);
		break;
	default:
		break;
	}
}

void Highscore::update(const sf::Time& dt) {
	m_ScoreText.setString(std::string{ "Score:\n" + std::to_string(m_TotalScore) });
}


int Highscore::getLvl() const 
{
	return m_LinesCleared / 10;
}