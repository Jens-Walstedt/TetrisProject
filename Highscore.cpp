#include <iostream>
#include <stdio.h>
#include <string>
#include "Highscore.h"
#include <fstream>
#include <utility>

#include <fstream>
#include <utility>
#include <string>


Highscore::Highscore(int fieldsize, Sound& sound, sf::Font &font) : m_ScoreText(), m_LvlText(), m_LinesClearedText(), m_Font(font), m_Sound(sound)
{
	m_Score = 0;
	score = m_Score;
	m_LinesCleared = 0;
	m_BonusScore = 0;
	m_FieldSize = fieldsize;
	m_currentLevel = 0;

	m_ScoreText.setFont(m_Font);
	m_ScoreText.setFillColor(sf::Color::White);
	m_ScoreText.setCharacterSize(15);
	m_ScoreText.setPosition(sf::Vector2f{ 18 * (float)m_FieldSize + 3, 90.f });

	m_LvlText.setFont(m_Font);
	m_LvlText.setFillColor(sf::Color::White);
	m_LvlText.setCharacterSize(15);
	m_LvlText.setPosition(sf::Vector2f{ 18 * (float)m_FieldSize + 3, 130.f });

	m_LinesClearedText.setFont(m_Font);
	m_LinesClearedText.setFillColor(sf::Color::White);
	m_LinesClearedText.setCharacterSize(15);
	m_LinesClearedText.setPosition(sf::Vector2f{ 18 * (float)m_FieldSize + 3, 180.f });
}

void Highscore::reset() 
{
	writeToFile();
	printHighscore();
	m_LinesCleared = 0;
	m_Score = 0;
	m_Sound.resetSpeed();
}

void Highscore::addScore(int score) 
{
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

	if (m_currentLevel < lvl)
	{
		m_Sound.speedUpMusic(0.1);
		m_currentLevel = lvl;

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

void Highscore::writeToFile()
{
	//check if score is under 3
	if (scores.size() <= 3)
	{
		scores.push_back(m_Score);
	}
	else if (scores.size() >= 3)
	{
		ReplaceHigherScore();
	}

	//check if 3
	
	std::ofstream file;
	file.open("Score.txt");
	for (int score : scores) 
	{
		file << score << std::endl;				
	}
	file.close();
}

void Highscore::ReplaceHigherScore()
{
	//sort vector
	std::sort(scores.begin(), scores.end());
	
	//get lowest value and replace it 
	int current = 0;
	bool isBigger = false;
	for (int i = 0; i < scores.size(); i++)
	{
		if (m_Score > scores[i])
		{
			current++;
			isBigger = true;
		}
	}
	if (isBigger)
	{
		scores[current] = m_Score;
	}
}

void Highscore::loadFromFile()
{
	std::ifstream file;
	std::string line;
	file.open("Score.txt", std::ios::app);
	while(file.is_open())
		{
			std::getline(file, line);
			scores.push_back(std::stoi(line));
		} 
	file.close();
}

void Highscore::printHighscore() 
{
	std::cout << "Highscore: " << m_Score << std::endl;
}