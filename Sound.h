#pragma once
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>

class Sound
{
private:
	sf::Music m_BackgroundMusic;

public:
	Sound();
	void setBackgroundMusic();
	void speedUpMusic();
};

