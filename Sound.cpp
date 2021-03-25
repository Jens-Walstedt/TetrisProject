#include "Sound.h"

Sound::Sound()
{
	m_BackgroundMusic.openFromFile("Game Theme.flac");
}

void Sound::setBackgroundMusic()
{
	m_BackgroundMusic.play();
	m_BackgroundMusic.setLoop(true);
}
