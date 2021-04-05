#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window/Event.hpp"
#include "Sound.h"
#include <iostream>
#include "Engine.h"
class Engine;

class MenuWindow
{
private:
	sf::RectangleShape m_Rect;
	sf::Font m_Font;
	std::vector<sf::Text> menu;
	int m_Selected;
	sf::Text m_Volume;
	//Sound& m_Sound;
	sf::Time m_BlinkTime;
	sf::Time m_ElapsedTime;
	bool m_elapseTime;
	Engine& m_Engine;
public:
	MenuWindow(sf::Vector2f position, sf::Vector2f dimension, sf::Font font, Engine& engine);
	void Init();
	void Events(sf::Event event, bool& showMenu);
	void ChangePrevious(int change);
	//void Events(sf::Event event, bool &showMenu);
	void selected(int change);
	void Update(sf::Time gameTime);
	void Draw(sf::RenderWindow& window);

};

