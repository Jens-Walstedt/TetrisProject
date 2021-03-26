#pragma once
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>

class Sound
{
private:
	sf::Music m_BackgroundMusic;
	sf::SoundBuffer m_CollisionBuffer;
	sf::SoundBuffer m_ClearLineBuffer;
	sf::Sound m_CollisionSound;
	sf::Sound m_ClearLineSound;

public:
	Sound();
	void setBackgroundMusic();
	void setCollisionSound();
	void setClearLineSound();
	void speedUpMusic();
};

