#pragma once
#include <SFML/Graphics.hpp>

#include "Grid.h"

class Engine
{
private:
	std::unique_ptr<Grid> m_Grid;

	sf::RenderWindow m_Window;
	void update(const sf::Time& gameTime);
	void events();
	void render();
	void rotate();		// TODO: call rotation logic
	void proceed();		// TODO: call proceed logic
	void Direction();	// TODO: call Direction logic

	std::unique_ptr<Grid> m_Grid;
	Highscore m_HighScore;	// TODO: call Highscore object


public:
	Engine();
	void start();
};

