#include <iostream>
#include <stdio.h>
#include "Highscore.h"

using namespace std;

Highscore::Highscore(int fieldsize) : m_ScoreText(), m_LvlText(), m_LinesClearedText(), m_Font(), m_Sound()
{
	m_Score = 0;
	m_LinesCleared = 0;
	m_BonusScore = 0;
	m_FieldSize = fieldsize;

	m_Font.loadFromFile("MontserratAlternates-Bold.otf");

	m_ScoreText.setFont(m_Font);
	m_ScoreText.setFillColor(sf::Color::Black);
	m_ScoreText.setCharacterSize(15);
	m_ScoreText.setPosition(sf::Vector2f{ 10 * (float)m_FieldSize + 3, 50.f });

	m_LvlText.setFont(m_Font);
	m_LvlText.setFillColor(sf::Color::Black);
	m_LvlText.setCharacterSize(15);
	m_LvlText.setPosition(sf::Vector2f{ 10 * (float)m_FieldSize + 3, 100.f });

	m_LinesClearedText.setFont(m_Font);
	m_LinesClearedText.setFillColor(sf::Color::Black);
	m_LinesClearedText.setCharacterSize(15);
	m_LinesClearedText.setPosition(sf::Vector2f{ 10 * (float)m_FieldSize + 3, 150.f });
}

void Highscore::reset() {
	m_LinesCleared = 0;
	m_Score = 0;
}

void Highscore::addScore(int score) {
	m_BonusScore += score;
}

void Highscore::draw(sf::RenderWindow& window) 
{
	window.draw(m_ScoreText);
	window.draw(m_LvlText);
	window.draw(m_LinesClearedText);
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

void Highscore::update(const sf::Time& dt)
{
	m_ScoreText.setString(std::string{ "Score:\n" + std::to_string(m_Score) });
	m_LvlText.setString(std::string{ "Level:\n" + std::to_string(m_LinesCleared / 10) });
	m_LinesClearedText.setString(std::string{ "Lines:\n" + std::to_string(m_LinesCleared) });
}


int Highscore::getLvl() const 
{
	return m_LinesCleared / 10;
}