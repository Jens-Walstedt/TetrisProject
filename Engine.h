#pragma once
#include <SFML/Graphics.hpp>
#include "Movement.h"
#include "Grid.h"
#include "Tetromino.h"
#include "Highscore.h"
#include "Utility.h"

#include <iostream>

class Engine
{
private:
	sf::Sprite m_BackgroundSprite; //TEST

	int m_TetroId;
	int m_BlockSize;
	sf::Time m_ElapsedTime;
	std::unique_ptr<Grid> m_Grid;
	sf::Texture m_Texture;
	sf::Texture m_Background;
	std::unique_ptr<Tetromino> m_Tetromino;
	

	sf::RenderWindow m_Window;
	sf::RectangleShape m_SeparationLine;
	void update(const sf::Time& gameTime);
	void events();
	void render();
	void createTetromino();
	void rotate();		// TODO: call rotation logic
	void proceed(Movement move);		// TODO: call proceed logic
	void Direction();	// TODO: call Direction logic

	bool CollisionDetection(std::array<sf::Vector2i, 4> block);		// Create grid

	bool isOccupied(int x, int y);

	Highscore m_HighScore;
	


public:
	Engine();
	void start();
};

