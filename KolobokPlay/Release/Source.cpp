#include "Constants.h"
#include "Player.h"
#include "view.h"
#include "RWindow.h"

#include "MainMenu.h"
#include "PauseMenu.h"
#include "SelectLevel.h"

#include "Sounds.h"

#include "Levels.h"

#include <iostream>
#include <fstream> 
#include <cstring> 


#include <Windows.h>
#define _WIN32_WINNT 0x0500

Levels lvl; float timeb2 = 1.0f; SoundGame sound;


bool startGame()
{

	soundBonusOff = true; // ���� ��� ��������� ������

	b2Vec2 Gravity(0.f, 9.8f); // �������� ����������
	b2World World(Gravity); // ���������� ����

fromSLMtoMM: // �� ���� ������ ������ ������������ � ������� ����

	fromSLMtoMM = false;
	if (toNextLvl == 0 && Restart == false) setMenu(window); // ���� ��� �� ����� �� ��������� �������
															 // � �� �� ������������� ���, �� ������ ����� ����� ���������� ������� ����

	else if (toNextLvl == 1) SelectLvl = true; // ����� ���� �� ��������� �� �������� �������
	if (exfromGame == false) return false; // ������� �� ����
	if (SelectLvl || Restart == true || toNextLvl == 2) {

		if ((toNextLvl == 0 || toNextLvl == 2) && Restart == false) // ���� ��� ����� �� ����. ��� � �� ������������� ������� ���
		{
			nlvl = setSLMenu(window); // ����� ������ ������������ ������������ ��������� �� ���� ������ ������
			if (fromSLMtoMM == true) goto fromSLMtoMM;
		} // ���� false, ��������� �� ����� �� ���� ������ ������ � �������

		else if (Restart == false) { if (nlvl < 5)nlvl++; }; // ����� ���� �� ������������� �������, ����� ���� ��� ������ 5
															 // �������������� ���������� nlvl

		switch (nlvl) // � ����������� �� �������� ���������, ������������� ������ ������������ ������
		{
		case 1:lvl.setLevel1(World); break;
		case 2:lvl.setLevel2(World); break;
		case 3:lvl.setLevel3(World); break;
		case 4:lvl.setLevel4(World); break;
		case 5:lvl.setLevel5(World); break;
		}
	}

	SelectLvl = false; Restart = false; // ���������� ����������
	toNextLvl = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	window.setFramerateLimit(70); // �������������� ����� ������ � �������(70)

	view.reset(FloatRect(0, 0, 683 + 341.5f, 384 + 192.0f)); // ������������� ��� ������

	Clock clock; //�������� �� �������(� �� �������������/�������� ����������).

	Player MainPlayer("player.png", 17, 0, 160, 33, 33, 22, 12, World); // ������ �������� ���������

	float CurrentFrame = 0; // ������ ������� ����
	float time; // ��������� �������

	while (window.isOpen())
	{
		time = (float)clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
		if (slowmo == false)clock.restart(); // ���� ����� �� �����������, ������������� �����
											 //��� ������ �������� (������ ��� 800) ��� ������ �������� � ��������� ����� � ����,
											 // �� ��� �������������� ��� ����� � �������� ��.
		time = time / 1; // (800)

		Event e; // ��������� �������
		while (window.pollEvent(e))  // ���� ���������� �������
		{
			if (e.type == Event::Closed) // ���� ��� ������� �������� - �������
				window.close();
		}

		if (slowmo == true && time < 10000000.0f) // ���� ����������� �����, ������ �������� ���������� ��� ���������� ������ � ����
		{
			timeb2 = 0.5f;
		}
		if (time > 10000000.0f || slowmo == false) // ���� ������ 10 ���, ���������� ������ ��� ��������� ������
		{
			slowmo = false;
			timeb2 = 1.0f;
			power = 0;
		}
		World.Step(timeb2 / 60.f, 8, 3); // ��� � ��������� Box2D (�������� ������ �� 1/60 ������� + ��������� ��������(�� ���������))

										 /////////////////////////////////////////////////////////////////////////////////////////

		if (Keyboard::isKeyPressed(Keyboard::Escape) || (toMainMenuisone == 1))// ���� ������ ������� Esc 
		{																	   //��� ���������� ��� �������� � ������� ���� ����� 1

			if (toMainMenuisone == 1)// ��� �������� � ������� ���� ����� ��������� ������������ �������� � ������ �� �������� ����
			{
				toMainMenu = 1; toMainMenuisone = 0;
				window.clear(); break;
			}

			sound.soundButton(); // ���� ������� ������

			setPauseMenu(window); // ��������� ���� �����
			if ((toMainMenu == 1)) // ��� �������� � ������� ���� �� ���� �����
			{
				toMainMenu = 1; toMainMenuisone = 0;
				window.clear(); break;
			}
		}
		// �������� ��������� ������ ��������� ��� ������
		getplayercoordinateforview(MainPlayer.sprite.getPosition().x, MainPlayer.sprite.getPosition().y);

		window.setView(view);//"��������" ������ � ���� sfml

		window.clear(); // ������ ����

						/////////////////////////////////////////////////////////////////////////////////////////

		switch (nlvl) // ������������ ������� �� �������
		{
		case 1:;
		default:lvl.Drawlvl(World);
		}

		/////////////////////////////////////////////////////////////////////////////////////////

		MainPlayer.Control(window, World); // ������� ������� ���������, ��������������� ���������� � �������������� � �����

		if (toNextLvl == 1 || toNextLvl == 2) { window.clear(); break; } // ���� ��������� �� �������� �������, ���������

		if (Restart == true) { window.clear(); break; } // fail menu RESTART

		window.display(); // ����������� ����������� ��������
	}
	return true; // �� ��������� ���������� true
}

void gameRunning() {
	if (startGame() && exfromGame) { gameRunning(); }  // ���� �������� ������� ���� � �� ������� �� ���� (exfromGame == true), ���������� ����
}

int main()
{

		HWND hWnd = GetConsoleWindow();//����� ����� �������, (�������� ������� (�������� ������ ��� windows))
		ShowWindow(hWnd, SW_HIDE);//�������� �������


	// ������ �� ���� ����� ����������� ������ ��� ����������� ������� � �������������� ������ �� �������
	int lastComplLvl = 0;
	std::ifstream save1("savelvl.txt");
	save1 >> lastComplLvl;
	nlvl = lastComplLvl;
	save1.close();

	for (int i = 0; i < lastComplLvl; i++) access[i] = true; // ������� ������� ���������� ����� �������

	gameRunning(); // ������� ������ ���� 

				   // ������ � ���� ����� ����������� ������ ��� ����������� ������� � �������������� ������ �� �������
	for (int i = 4; i >= 0; i--) { if (access[i] == true) { lastComplLvl = i + 1; break; } }

	std::ofstream save("savelvl.txt");
	save << lastComplLvl;
	save.close();
}

/* Time SFML
B���� ��������� ������� ������ ����
� ���� ��� ��� �� ��������� ����������� (� ���� ���� ������ ���������������) � ����������� �����.
*/

/*
���������� �������������
���������� ������������ � ��� ������, ����� ������ ������� �� ������� ���������.
*/
