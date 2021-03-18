#pragma once
#include <SFML/Graphics.hpp>
#include "Movement.h"
#include "Grid.h"

class Engine
{
private:
	sf::Time m_ElapsedTime;
	std::unique_ptr<Grid> m_Grid;
	sf::Texture m_Texture;
	sf::Sprite m_BackgroundSprite;

	sf::RenderWindow m_Window;
	void update(const sf::Time& gameTime);
	void events();
	void render();

public:
	Engine();
	void start();
};

