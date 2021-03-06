#include "MenuWindow.h"

MenuWindow::MenuWindow(sf::Vector2f position, sf::Vector2f dimension, sf::Font font, Engine& engine) :
	m_Font(font),
	m_Engine(engine)
{
	m_Selected = 0;
	m_Rect = sf::RectangleShape(sf::Vector2f(288, 66 + 30 * 3 + 60));
	m_Rect.setPosition(position);
	m_Rect.setOutlineThickness(5.f);
	m_Rect.setFillColor(sf::Color::Blue);
	m_Rect.setOutlineColor(sf::Color::Black);

	Init();
	
}

void MenuWindow::Init()
{
	m_Volume = sf::Text(sf::String("volume"), m_Font, 30U);
	m_Volume.setFillColor(sf::Color(128, 128, 128));
	m_Volume.setPosition(m_Rect.getPosition().x + 80, m_Rect.getPosition().y + 20);

	menu.push_back(sf::Text(sf::String("-"), m_Font, 30U));
	menu.push_back(sf::Text(sf::String("+"), m_Font, 30U));
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
	//selects first menu item as default
	m_BlinkTime = sf::Time(sf::milliseconds(200));
	selected(0);
}

void MenuWindow::Events(sf::Event event, bool& showMenu)
{
	switch (event.type)
	{
	case sf::Event::Closed:
			m_Engine.m_Window.close();
		break;
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::S)
		{
			if (m_Selected == 0)
			{
				selected(2);
			}
			else
			{
				selected(1);
			}
		}
		else if (event.key.code == sf::Keyboard::W)
		{
			if (m_Selected == 1)
			{
				selected(-2);
			}
			else
			{
				selected(-1);
			}
		}
		else if (event.key.code == sf::Keyboard::A)
		{	
			if (m_Selected == 1 || m_Selected == 0)
			{
				menu[0].setFillColor(sf::Color::Red);
				m_elapseTime = true;
				m_Engine.m_Sound.setVolume(-1);
			}
		}
		else if (event.key.code == sf::Keyboard::D)
		{
			if (m_Selected == 1 || m_Selected == 0)
			{
				menu[1].setFillColor(sf::Color::Green);
				m_elapseTime = true;
				m_Engine.m_Sound.setVolume(1);
			}
		}
		else if (event.key.code == sf::Keyboard::Enter)
		{
			if (m_Selected == 2)
			{
				m_Engine.restart();
				showMenu = false;
			}
			else if (m_Selected == 3)
			{
				m_Engine.m_Window.close();
			}
		}
		else if (event.key.code == sf::Keyboard::Escape)
		{
			showMenu = false;
		}
		break;
	}
}

void MenuWindow::ChangePrevious(int change)
{
	if (m_Selected == 0)
	{
		menu[m_Selected].setFillColor(sf::Color::Black);
		menu[m_Selected + 1].setFillColor(sf::Color::Black);

	}
	else if (m_Selected == 1)
	{
		menu[m_Selected].setFillColor(sf::Color::Black);
		menu[m_Selected - 1].setFillColor(sf::Color::Black);
	}
	else
	{
		menu[m_Selected].setFillColor(sf::Color::Black);
	}
}

void MenuWindow::selected(int change)
{
	ChangePrevious(change);
	m_Selected += change;
	
	if (m_Selected >= static_cast<int>(menu.size()))
	{
		m_Selected = 0;
	}
	else if (m_Selected < 0)
	{
		m_Selected = menu.size() - 1;
	}

	if (m_Selected == 1 ||m_Selected == 0)
	{
		menu[0].setFillColor(sf::Color::White);
		menu[1].setFillColor(sf::Color::White);
	}
	else
	{
	menu[m_Selected].setFillColor(sf::Color::White);
	}
}

void MenuWindow::Update(sf::Time gameTime)
{
	if (m_elapseTime)
	{
		m_ElapsedTime += gameTime;
	}

	if (m_ElapsedTime > m_BlinkTime && (m_Selected == 1 || m_Selected == 0))
	{
		menu[0].setFillColor(sf::Color::White);
		menu[1].setFillColor(sf::Color::White);
		m_ElapsedTime = sf::Time::Zero;
		m_elapseTime = false;
	}
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
