#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Sound.h"

class Sound;
class Highscore
{

private:
	sf::Font m_Font;
	sf::Text m_LvlText;
	sf::Text m_ScoreText;
	sf::Text m_LinesClearedText;



	int m_FieldSize;

	int m_Score;
	int m_BonusScore;
	int m_LinesCleared;

	Sound& m_Sound;

	sf::Text textbox;

public:

	Highscore(int fieldsize, Sound& sound);

	void draw(sf::RenderWindow& window);
	void reset();
	void addScore(int m_Score);
	void sumScore();
	void scoreSystem(int num);
	void update(const sf::Time& dt);

	int getLvl() const;

};