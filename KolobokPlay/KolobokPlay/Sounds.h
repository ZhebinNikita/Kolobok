#pragma once
#include "SFML\Audio.hpp"	// for MUSIC
#include "Constants.h"


//////////////////////////////////////////////////// реализаци€ »Ќ“≈–‘≈…—ј «¬” ќ¬
class SoundGame {
private:
	Sound sound;
	SoundBuffer buffer;

public:

	void soundJump()
	{
		buffer.loadFromFile("music/jump.wav");	// загружаем в буфер sound
		sound.setBuffer(buffer); //создаем звук и загружаем в него звук из буфера 
		sound.setVolume(50);
		sound.play();
	}

	void soundWin()
	{
		buffer.loadFromFile("music/win.wav");	// загружаем в буфер sound
		sound.setBuffer(buffer); //создаем звук и загружаем в него звук из буфера 
		sound.setVolume(50);
		sound.play();
	}

	void soundDeath()
	{
		buffer.loadFromFile("music/death.wav");	// загружаем в буфер sound
		sound.setBuffer(buffer); //создаем звук и загружаем в него звук из буфера 
		sound.setVolume(50);
		sound.play();
	}

	void soundStar()
	{
		buffer.loadFromFile("music/star.wav");	// загружаем в буфер sound
		sound.setBuffer(buffer); //создаем звук и загружаем в него звук из буфера 
		sound.setVolume(50);
		sound.play();
	}

	void soundBonusOn()
	{
		buffer.loadFromFile("music/slowmo_on.wav");	// загружаем в буфер sound
		sound.setBuffer(buffer); //создаем звук и загружаем в него звук из буфера 
		sound.setVolume(50);
		sound.play();
	}

	void soundButton()
	{
		buffer.loadFromFile("music/button.wav");	// загружаем в буфер sound
		sound.setBuffer(buffer); //создаем звук и загружаем в него звук из буфера 
		sound.setVolume(60);
		sound.play();
	}
};