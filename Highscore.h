#pragma once
#include <SFML/Graphics.hpp>
class Highscore
{

private:
	sf::Font m_Font;
	sf::Text m_LvlText;
	sf::Text m_ScoreText;
	sf::Text m_LinesClearedText;

	int m_Score;
	int m_TotalScore;
	int m_BonusScore;
	int m_LinesCleared;

public:

	void draw(sf::RenderWindow& window);
	void reset();
	void addScore(int m_Score);
	//void sumScore();
	//void scoreSystem(int num);
	void update(const sf::Time& dt);

	int getLvl() const;

};