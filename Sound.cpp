#include "Sound.h"

Sound::Sound() 
{
	m_BackgroundMusic.openFromFile("Game Theme.flac");
	m_CollisionBuffer.loadFromFile("fall.wav");
	m_ClearLineBuffer.loadFromFile("line.wav");
	m_CollisionSound.setBuffer(m_CollisionBuffer);
	m_ClearLineSound.setBuffer(m_ClearLineBuffer);
	m_CurrentVolume = 5.f;
	m_CurrentSpeed = 1.f;
}

void Sound::setBackgroundMusic()
{
	m_BackgroundMusic.play();
	m_BackgroundMusic.setVolume(m_CurrentVolume);
	//m_BackgroundMusic.setPitch(5.5f);
	m_BackgroundMusic.setLoop(true);
}

void Sound::setCollisionSound()
{
	m_CollisionSound.play();
	m_CollisionSound.setVolume(30.f);
}

void Sound::setClearLineSound()
{
	m_ClearLineSound.play();
	m_ClearLineSound.setVolume(30.f);
}

void Sound::speedUpMusic(float speed)
{
	m_BackgroundMusic.setPitch(m_CurrentSpeed += speed);
}

void Sound::setVolume(float change)
{
	m_BackgroundMusic.setVolume(m_CurrentVolume += change);
}
