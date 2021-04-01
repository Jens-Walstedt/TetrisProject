#include "MenuWindow.h"

MenuWindow::MenuWindow(sf::Vector2f position, sf::Vector2f dimension, sf::Font font):
m_Font(font)
{
	m_Selected = 0;
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
		menu[i].setPosition(m_Rect.getPosition().x + 80, m_Rect.getPosition().y + 64 * i);
	}
}

void MenuWindow::Events(sf::Event event, bool& showMenu)
{
	switch (event.type) 
	{
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::S)
		{
			selected(1);
		}
		else if (event.key.code == sf::Keyboard::W)
		{
			selected(-1);
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

void MenuWindow::selected(int change)
{
	menu[m_Selected].setFillColor(sf::Color::Black);
	m_Selected += change;
	if (m_Selected >= static_cast<int>(menu.size()))
	{
		m_Selected = 0;
	}
	else if (m_Selected < 0)
	{
		m_Selected = menu.size() - 1;
	}
	
	menu[m_Selected].setFillColor(sf::Color::White);
	
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
