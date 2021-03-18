#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Engine
{
private:
	sf::RenderWindow m_Window;
	void update();
	void events();
	void render();

public:
	Engine();
	void start();
};

