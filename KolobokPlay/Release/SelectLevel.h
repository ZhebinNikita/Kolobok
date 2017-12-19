#pragma once
#include "Constants.h"

// Реализация меню выбора уровня
int setSLMenu(RenderWindow & window) {

	Texture one, two, three, four, five, menuBackground, tesc;
	one.loadFromFile("images/Menu/one.png");
	two.loadFromFile("images/Menu/two.png");
	three.loadFromFile("images/Menu/three.png");
	four.loadFromFile("images/Menu/four.png");
	five.loadFromFile("images/Menu/five.png");

	tesc.loadFromFile("images/Menu/esc_exit.png");

	menuBackground.loadFromFile("images/Menu/BackgrSelection.png");

	Sprite menu1(one), menu2(two), menu3(three), menu4(four), menu5(five), menuBg(menuBackground), sesc(tesc);

	bool isMenu = 1;
	int menuNum = 0;

	one.setSmooth(true);
	two.setSmooth(true);
	three.setSmooth(true);
	four.setSmooth(true);
	five.setSmooth(true);

	menuBg.setPosition(0, 0);

	menuBg.setOrigin(0, 0);
	menuBg.setScale(1.0f, 1.0f); // !!!!!!!!!

	View view;
	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setPosition(100, 40);
		menu2.setPosition(200, 40);
		menu3.setPosition(300, 40);
		menu4.setPosition(400, 40);
		menu5.setPosition(500, 40);
		sesc.setPosition(45, 690);

		view.reset(FloatRect(0, 0, 1366, 768));
		window.setView(view);

		menuNum = 0;
		window.clear();


		if (IntRect(100, 40, 40, 60).contains(Mouse::getPosition(window)))
		{
			menuNum = 1;
			menu1.setPosition(100 + 8, 40 + 8);
		}

		if (IntRect(200, 40, 40, 60).contains(Mouse::getPosition(window)))
		{
			menuNum = 2;
			menu2.setPosition(200 + 8, 40 + 8);
		}

		if (IntRect(300, 40, 40, 60).contains(Mouse::getPosition(window)))
		{
			menuNum = 3;
			menu3.setPosition(300 + 8, 40 + 8);
		}

		if (IntRect(400, 40, 40, 60).contains(Mouse::getPosition(window)))
		{
			menuNum = 4;
			menu4.setPosition(400 + 8, 40 + 8);
		}

		if (IntRect(500, 40, 40, 60).contains(Mouse::getPosition(window)))
		{
			menuNum = 5;
			menu5.setPosition(500 + 8, 40 + 8);
		}





		if (Mouse::isButtonPressed(Mouse::Left)) // выбор уровня
		{
			switch (menuNum)
			{
			case 1:  if (access[0] == true) return 1; break;
			case 2:  if (access[1] == true)return 2; break;
			case 3:  if (access[2] == true)return 3; break;
			case 4:  if (access[3] == true)return 4; break;
			case 5:  if (access[4] == true)return 5; break;
			}

		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) { isMenu = false; fromSLMtoMM = true; break; } // выход в главное меню




		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu4);
		window.draw(menu5);
		window.draw(sesc);

		window.display();
	}

	return 1;
}