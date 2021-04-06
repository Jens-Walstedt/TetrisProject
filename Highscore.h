#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <vector>

#include "Sound.h"

class Sound;
class Highscore
{

private:

	int gethighscore();

	sf::Font &m_Font;
	sf::Text m_LvlText;
	sf::Text m_ScoreText;
	sf::Text m_LinesClearedText;
	sf::Text m_HighScoreText;


	int score;

	int m_FieldSize;
	int m_Score;
	int m_BonusScore;
	int m_LinesCleared;
	int m_currentLevel;
	sf::Sprite& m_BackgroundSprite;

	Sound& m_Sound;

	sf::Text textbox;

	std::vector<int> scores;

public:

	Highscore(int fieldsize, Sound& sound, sf::Font &font, sf::Sprite& sprite);

	void draw(sf::RenderWindow& window);
	void reset();
	void addScore(int m_Score);
	void sumScore();
	void scoreSystem(int num, sf::Sprite& sprite);
	void update(const sf::Time& dt);
	void printHighscore();
	void loadFromFile();
	void writeToFile();
	void writeToVector();
	

	void ReplaceHigherScore();


	int getLvl() const;

};