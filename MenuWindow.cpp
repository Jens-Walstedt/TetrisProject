#include "MenuWindow.h"

MenuWindow::MenuWindow(sf::Vector2f position, sf::Vector2f dimension, sf::Font font, Sound& sound) :
	m_Font(font),
	m_Sound(sound)
{
	m_Selected = 0;
	m_Rect = sf::RectangleShape(sf::Vector2f(288, 66 + 30 * 3 + 60));
	m_Rect.setPosition(position);
	m_Rect.setOutlineThickness(5.f);
	m_Rect.setFillColor(sf::Color::Blue);
	m_Rect.setOutlineColor(sf::Color::Black);

	Init();
	selected(0);
}

void MenuWindow::Init()
{
	m_Volume = sf::Text(sf::String("volume"), m_Font, 30U);
	m_Volume.setFillColor(sf::Color(128, 128, 128));
	m_Volume.setPosition(m_Rect.getPosition().x + 80, m_Rect.getPosition().y + 20);

	menu.push_back(sf::Text(sf::String("+"), m_Font, 30U));
	menu.push_back(sf::Text(sf::String("-"), m_Font, 30U));
	menu.push_back(sf::Text(sf::String("restart"), m_Font, 30U));
	menu.push_back(sf::Text(sf::String("exit"), m_Font, 30U));

	int gap = 1;
	for (size_t i = 0; i < menu.size(); i++)
	{
		menu[i].setFillColor(sf::Color::Black);
		if (i == 1)
		{
			menu[i].setPosition(m_Rect.getPosition().x + 80 + 80, m_Rect.getPosition().y + 50 * (i));
			gap = 0;
		}
		else
		{
			menu[i].setPosition(m_Rect.getPosition().x + 80, m_Rect.getPosition().y + 50 * (i + gap));
		}
	}
}

void MenuWindow::Events(sf::Event event, bool& showMenu, sf::RenderWindow &window)
{
	switch (event.type)
	{
	case sf::Event::Closed:
			window.close();
		break;
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
			if (m_Selected == 1)
			{
				m_Sound.setVolume(-1);
			}
		}
		else if (event.key.code == sf::Keyboard::D)
		{
			if (m_Selected == 1)
			{
				m_Sound.setVolume(1);
			}
		}
		else if (event.key.code == sf::Keyboard::Enter)
		{
			if (m_Selected == 2)
			{
				//TODO: Restart Game
			}
			else if (m_Selected == 3)
			{
				window.close();
			}
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

void MenuWindow::Update(sf::Time gameTime)
{

}

void MenuWindow::Draw(sf::RenderWindow& window)
{

	window.draw(m_Rect);
	window.draw(m_Volume);
	for (size_t i = 0; i < menu.size(); i++)
	{
		window.draw(menu[i]);
	}
}
