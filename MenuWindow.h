#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window/Event.hpp"
#include "Sound.h"

class MenuWindow
{
private:
	sf::RectangleShape m_Rect;
	sf::Font m_Font;
	std::vector<sf::Text> menu;
	int m_Selected;
	sf::Text m_Volume;
	Sound& m_Sound;

public:
	MenuWindow(sf::Vector2f position, sf::Vector2f dimension, sf::Font font, Sound& sound);
	void Init();
	void Events(sf::Event event, bool& showMenu, sf::RenderWindow& window);
	//void Events(sf::Event event, bool &showMenu);
	void selected(int change);
	void Update(sf::Time gameTime);
	void Draw(sf::RenderWindow& window);

};

