#pragma once
#include "SFML\Audio.hpp"	// for MUSIC
#include "Constants.h"


//////////////////////////////////////////////////// ���������� ���������� ������
class SoundGame {
private:
	Sound sound;
	SoundBuffer buffer;

public:

	void soundJump()
	{
		buffer.loadFromFile("music/jump.wav");	// ��������� � ����� sound
		sound.setBuffer(buffer); //������� ���� � ��������� � ���� ���� �� ������ 
		sound.setVolume(50);
		sound.play();
	}

	void soundWin()
	{
		buffer.loadFromFile("music/win.wav");	// ��������� � ����� sound
		sound.setBuffer(buffer); //������� ���� � ��������� � ���� ���� �� ������ 
		sound.setVolume(50);
		sound.play();
	}

	void soundDeath()
	{
		buffer.loadFromFile("music/death.wav");	// ��������� � ����� sound
		sound.setBuffer(buffer); //������� ���� � ��������� � ���� ���� �� ������ 
		sound.setVolume(50);
		sound.play();
	}

	void soundStar()
	{
		buffer.loadFromFile("music/star.wav");	// ��������� � ����� sound
		sound.setBuffer(buffer); //������� ���� � ��������� � ���� ���� �� ������ 
		sound.setVolume(50);
		sound.play();
	}

	void soundBonusOn()
	{
		buffer.loadFromFile("music/slowmo_on.wav");	// ��������� � ����� sound
		sound.setBuffer(buffer); //������� ���� � ��������� � ���� ���� �� ������ 
		sound.setVolume(50);
		sound.play();
	}

	void soundButton()
	{
		buffer.loadFromFile("music/button.wav");	// ��������� � ����� sound
		sound.setBuffer(buffer); //������� ���� � ��������� � ���� ���� �� ������ 
		sound.setVolume(60);
		sound.play();
	}
};