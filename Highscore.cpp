#include <iostream>
#include <stdio.h>
#include <string>
#include "Highscore.h"
#include <fstream>
#include <utility>

#include <fstream>
#include <utility>
#include <string>


Highscore::Highscore(int fieldsize, Sound& sound, sf::Font &font, sf::Sprite& sprite) : m_ScoreText(), m_LvlText(), m_LinesClearedText(), m_Font(font), m_Sound(sound), m_BackgroundSprite(sprite)
{
	m_Score = 0;
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

	m_HighScoreText.setFont(m_Font);
	m_HighScoreText.setFillColor(sf::Color::White);
	m_HighScoreText.setCharacterSize(15);
	m_HighScoreText.setPosition(sf::Vector2f{ 18 * (float)m_FieldSize + 3, 220.f });

	loadFromFile();
}

void Highscore::reset() 
{
	writeToVector();
	printHighscore();
	m_LinesCleared = 0;
	m_Score = 0;
	m_Sound.resetSpeed();
	m_BackgroundSprite.setColor(sf::Color::White);
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
	window.draw(m_HighScoreText);
}

void Highscore::sumScore() 
{
	m_Score += m_BonusScore;
	m_BonusScore = 0;
}
void Highscore::scoreSystem(int num, sf::Sprite& sprite) 
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
		switch (lvl)
		{
		case 0:
			sprite.setColor(sf::Color::White);
			break;
		case 1:
			sprite.setColor(sf::Color::Green);
			break;
		case 2:
			sprite.setColor(sf::Color::Yellow);
			break;
		case 3:
			sprite.setColor(sf::Color::Blue);
			break;
		case 4:
			sprite.setColor(sf::Color::Red);
			break;
		default:
			break;
		}
		m_Sound.speedUpMusic(0.05);
		m_currentLevel = lvl;
	}
}

void Highscore::update(const sf::Time& dt)
{
	m_ScoreText.setString(std::string{ "Score:\n" + std::to_string(m_Score) });
	m_LvlText.setString(std::string{ "Level:\n" + std::to_string(m_LinesCleared / 10) });
	m_LinesClearedText.setString(std::string{ "Lines:\n" + std::to_string(m_LinesCleared) });
	m_HighScoreText.setString(std::string{"Highscore:\n" + std::to_string(gethighscore())});
}

int Highscore::gethighscore(){

	if (scores.size() == 0) {
		return 0;
	}
	else
	{
		return scores[scores.size()-1];
	}
	
}

int Highscore::getLvl() const 
{
	return m_LinesCleared / 10;
}

void Highscore::writeToVector()
{
	//sort vector
	std::sort(scores.begin(), scores.end());

	//check if score is under 3
	if (scores.size() <= 3)
	{
		
		scores.push_back(m_Score);
	}

	//check if 3

	else if (scores.size() >= 3)
	{
		ReplaceHigherScore();
	}


}

void Highscore::writeToFile()
{

	std::ofstream file;

	file.open("Score.txt");

	for (int m_Score : scores)
	{
		file << m_Score << std::endl;
	}
	file.close();
}

void Highscore::ReplaceHigherScore()
{

	
	//get lowest value and replace it 
	int current = -1;
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

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			scores.push_back(std::stoi(line));
		}
	}
	file.close();

}

void Highscore::printHighscore() 
{
	std::cout << "Highscore: " << m_Score << std::endl;
}