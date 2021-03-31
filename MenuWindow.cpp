#include "MenuWindow.h"

MenuWindow::MenuWindow(sf::Vector2f position, sf::Vector2f dimension)
{
	m_Rect = sf::RectangleShape(dimension);
	m_Rect.setPosition(position);
	m_Rect.setOutlineThickness(5.f);
	m_Rect.setFillColor(sf::Color::Blue);
	m_Rect.setOutlineColor(sf::Color::Black);
}

void MenuWindow::Init()
{
    
}

void MenuWindow::Events(sf::Event event, bool &showMenu)
{
    switch (event.type) {
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
}
