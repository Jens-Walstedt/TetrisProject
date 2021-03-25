#include "Sound.h"

Sound::Sound()
{
	m_BackgroundMusic.openFromFile("Game Theme.flac");
}

void Sound::setBackgroundMusic()
{
	m_BackgroundMusic.play();
	m_BackgroundMusic.setVolume(10.f);
	m_BackgroundMusic.setLoop(true);
}

void Sound::speedUpMusic()
{
	m_BackgroundMusic.setPitch(1.2f);
}
