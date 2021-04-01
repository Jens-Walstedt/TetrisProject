#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window/Event.hpp"

class MenuWindow
{
private:
	sf::RectangleShape m_Rect;
	sf::Font m_Font;
	std::vector<sf::Text> menu;

public:
	MenuWindow(sf::Vector2f position, sf::Vector2f dimension, sf::Font font);
	void Init();
	void Events(sf::Event event, bool &showMenu);
	void Update();
	void Draw(sf::RenderWindow& window);

};

