#include "Sound.h"

Sound::Sound()
{
	m_BackgroundMusic.openFromFile("Game Theme.flac");
	m_CollisionBuffer.loadFromFile("fall.wav");
	m_ClearLineBuffer.loadFromFile("line.wav");
}

void Sound::setBackgroundMusic()
{
	m_BackgroundMusic.play();
	m_BackgroundMusic.setVolume(10.f);
	m_BackgroundMusic.setLoop(true);
}

void Sound::setCollisionSound(sf::Sound m_CollisionSound)
{
	m_CollisionSound.setBuffer(m_CollisionBuffer);
	m_CollisionSound.play();
	m_CollisionSound.setVolume(25.f);
}

void Sound::setClearLineSound(sf::Sound m_ClearLineSound)
{
	m_ClearLineSound.setBuffer(m_ClearLineBuffer);
	m_ClearLineSound.play();
	m_ClearLineSound.setVolume(25.f);
}



void Sound::speedUpMusic()
{
	m_BackgroundMusic.setPitch(1.2f);
}
