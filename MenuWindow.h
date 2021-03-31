#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window/Event.hpp"

class MenuWindow
{
private:
	sf::RectangleShape m_Rect;
	sf::Font m_Font;
public:
	MenuWindow(sf::Vector2f position, sf::Vector2f dimension);
	void Init();
	void Events(sf::Event event, bool &showMenu);
	void Update();
	void Draw(sf::RenderWindow& window);

};

