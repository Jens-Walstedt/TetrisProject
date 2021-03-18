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

public:
	Engine();
	void start();
};

