#pragma once
#include "Constants.h"
#include <iostream>

// Реализация главного меню
void setMenu(RenderWindow & window)
{
	slowmo = false;

	for (int i = 0; i < 5; i++)
	{
		Stars[i] = true;
		soundStars[i] = true;
	}

	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground, tcontrolhelp, tesc;
	menuTexture1.loadFromFile("images/Menu/StartGame.png");
	menuTexture2.loadFromFile("images/Menu/Help.png");
	menuTexture3.loadFromFile("images/Menu/Exit.png");

	aboutTexture.loadFromFile("images/Menu/helpmenu.png");
	menuBackground.loadFromFile("images/Menu/BackgrMenu.jpg");
	tcontrolhelp.loadFromFile("images/Menu/controlhelp.png");
	tesc.loadFromFile("images/Menu/esc_exit.png");

	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground), scontrolhelp(tcontrolhelp), sesc(tesc);
	bool isMenu = 1;
	int menuNum = 0;

	menuTexture1.setSmooth(true);
	menuTexture2.setSmooth(true);
	menuTexture3.setSmooth(true);

	menuBg.setPosition(0, 0);

	menuBg.setOrigin(0, 0);
	menuBg.setScale(1.1f, 1.1f); // !!!!!!!!!

	View view;
	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setPosition(Vector2f(100, 30));
		menu2.setPosition(Vector2f(100, 120));
		menu3.setPosition(Vector2f(100, 210));


		view.reset(FloatRect(0, 0, 1366, 768)); // без бага с съезжающей камерой
		window.setView(view);

		menuNum = 0;
		window.clear();//Color(129, 181, 221)

		if (IntRect(100, 30, 280, 50).contains(Mouse::getPosition(window)))
		{
			menuNum = 1;
			menu1.setPosition(100 + 8, 30 + 8);
		}

		if (IntRect(100, 120, 205, 50).contains(Mouse::getPosition(window)))
		{
			menuNum = 2;
			menu2.setPosition(100 + 8, 120 + 8);
		}

		if (IntRect(100, 210, 150, 50).contains(Mouse::getPosition(window))) // 100, 210, 150, 50
		{
			menuNum = 3;
			menu3.setPosition(100 + 8, 210 + 8);
		}


		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) { isMenu = false;    /*system("FutureSpravka.chm");*/   SelectLvl = true; }// выходим из меню 

			if (menuNum == 2) { // вызов меню ознаколения с управлением
				window.draw(menuBg);

				about.setPosition(45, 35);
				window.draw(about);
				scontrolhelp.setPosition(45, 100);
				window.draw(scontrolhelp);
				sesc.setPosition(45, 690);
				window.draw(sesc);

				window.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape));
			}

			if (menuNum == 3) { isMenu = false; exfromGame = false; window.close(); } // выход из приложения

		}



		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	////////////////////////////////////////////////////
}