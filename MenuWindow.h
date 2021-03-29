#pragma once
#include "SFML/Graphics.hpp";

class MenuWindow
{
private:
	sf::Vector2f m_Position;
	sf::Vector2f m_Dimension;
	sf::RectangleShape m_rect;
public:
	MenuWindow(sf::Vector2f position, sf::Vector2f dimension);
	void Init();
	void Update();
	void Draw();

};

