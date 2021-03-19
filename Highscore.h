#pragma once
#include <SFML/Graphics.hpp>
class Highscore
{
private:
	sf::Font m_Font;
	sf::Text m_LvlText;
	sf::Text m_ScoreText;

	int m_Score;

public:
	Highscore();

	void draw(sf::RenderWindow& window);
	void reset();
	void update(const sf::Time& dt);
	int getLvl();
};

