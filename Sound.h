#pragma once
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>

class Sound
{
private:
	sf::Music m_BackgroundMusic;
	sf::SoundBuffer m_CollisionBuffer;
	sf::SoundBuffer m_ClearLineBuffer;

public:
	Sound();
	void setBackgroundMusic();
	void setCollisionSound(sf::Sound m_CollisionSound);
	void setClearLineSound(sf::Sound m_ClearLineSound);
	void speedUpMusic();
};

