#include "MenuWindow.h"

MenuWindow::MenuWindow(sf::Vector2f position, sf::Vector2f dimension, sf::Font font):
m_Font(font)
{
	m_Rect = sf::RectangleShape(dimension);
	m_Rect.setPosition(position);
	m_Rect.setOutlineThickness(5.f);
	m_Rect.setFillColor(sf::Color::Blue);
	m_Rect.setOutlineColor(sf::Color::Black);

	Init();
}

void MenuWindow::Init()
{
	menu.push_back(sf::Text(sf::String("button1"), m_Font, 30U));
	menu.push_back(sf::Text(sf::String("button2"), m_Font, 30U));
	menu.push_back(sf::Text(sf::String("button3"), m_Font, 30U));

	for (size_t i = 0; i < menu.size(); i++)
	{
		menu[i].setFillColor(sf::Color::Black);
		menu[i].setPosition(m_Rect.getPosition().x + 20, m_Rect.getPosition().y + 20 * i);
	}

}

void MenuWindow::Events(sf::Event event, bool& showMenu)
{
	switch (event.type) 
	{
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::S)
		{

		}
		else if (event.key.code == sf::Keyboard::W)
		{

		}
		else if (event.key.code == sf::Keyboard::A)
		{

		}
		else if (event.key.code == sf::Keyboard::D)
		{

		}
		else if (event.key.code == sf::Keyboard::Escape)
		{
			showMenu = false;
		}
		break;
	}
}

void MenuWindow::Update()
{

}

void MenuWindow::Draw(sf::RenderWindow& window)
{
	window.draw(m_Rect);
	for (size_t i = 0; i < menu.size(); i++)
	{
		window.draw(menu[i]);
	}
}
