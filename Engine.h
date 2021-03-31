#pragma once
#include <SFML/Graphics.hpp>
#include "Movement.h"
#include "Grid.h"
#include "Tetromino.h"
#include "Highscore.h"
#include "Utility.h"
#include "Sound.h"
#include "MenuWindow.h"
#include <iostream>

class Engine
{
	friend class Grid;
private:
	sf::Sprite m_BackgroundSprite; //TEST

	int m_TetroId;
	int m_FieldSize;
	sf::Time m_ElapsedTime;

	std::unique_ptr<Grid> m_Grid;
	std::unique_ptr<Tetromino> m_Preview;
	std::unique_ptr<Tetromino> m_Tetromino;

	sf::Texture m_Texture;
	sf::Texture m_Background;

	sf::RenderWindow m_Window;
	sf::RectangleShape m_GridBorder;
	std::unique_ptr<MenuWindow> m_MenuWindow;
	bool m_ShowMenu;
	sf::View view;
	
	void update(const sf::Time& gameTime);
	void events();
	void DisplayMenu();
	void render();
	void createTetromino();
	void rotate();		// TODO: call rotation logic
	void proceed(Movement move);		// TODO: call proceed logic
	void Direction();	// TODO: call Direction logic

	bool CollisionDetection(std::array<sf::Vector2i, 4> block);		// Create grid
	sf::Vector2f m_GridPosition;

	bool isOccupied(int x, int y);

	Highscore m_HighScore;
	Sound m_Sound;


public:
	Engine();
	void start();
};

