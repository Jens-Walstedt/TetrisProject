#pragma once
#include <SFML/Graphics.hpp>
#include "Movement.h"
#include "Grid.h"
#include "Tetromino.h"

class Engine
{
private:
	sf::Sprite m_BackgroundSprite; //TEST

	sf::Time m_ElapsedTime;
	std::unique_ptr<Grid> m_Grid;
	sf::Texture m_Texture;
	std::unique_ptr<Tetromino> m_Tetromino;
	

	sf::RenderWindow m_Window;
	void update(const sf::Time& gameTime);
	void events();
	void render();
	void rotate();		// TODO: call rotation logic
	void proceed();		// TODO: call proceed logic
	void Direction();	// TODO: call Direction logic

	//Highscore m_HighScore;	// TODO: call Highscore object

	


public:
	//Engine();
	void start();
};

