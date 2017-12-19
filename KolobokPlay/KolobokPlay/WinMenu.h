#include "Constants.h"



// Реализация меню победы
void setWinMenu(RenderWindow & window) {

	//// bonuses ////
	if (nlvl<5)
		access[nlvl] = true;

	slowmo = false;
	if (Stars[0] == false && Stars[1] == false && Stars[2] == false && Stars[3] == false && Stars[4] == false)
		if (bonuses < 4) bonuses++;

	for (int i = 0; i < 5; i++) {
		Stars[i] = true;
		soundStars[i] = true;
	}
	heart1 = true; heart2 = true; heart3 = true;
	hearts[0] = true; hearts[1] = true; hearts[2] = true; numh = 0;

	Texture menuTexture1, menuTexture2, menuBackground, menulvlcom, texit;
	texit.loadFromFile("images/Menu/Exit2.png");
	menuTexture1.loadFromFile("images/Menu/nextlevel.png");
	menuTexture2.loadFromFile("images/Menu/SelectLvl.png");
	menulvlcom.loadFromFile("images/Menu/lvlcomplete.png");

	menuBackground.loadFromFile("images/Menu/BackgrSelection.png");

	Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground), lvlcom(menulvlcom);
	bool isMenu = 1;
	int menuNum = 0;

	menuTexture1.setSmooth(true);
	menuTexture2.setSmooth(true);
	menuBackground.setSmooth(true);
	menulvlcom.setSmooth(true);

	menuBg.setPosition(0, 0);


	View view;

	while (isMenu)
	{
		menu1.setScale(0.9f, 0.9f); menu1.setPosition(100, 60);
		menu2.setScale(0.9f, 0.9f); menu2.setPosition(100, 170);

		lvlcom.setPosition(500, 580);


		view.reset(FloatRect(0, 0, 1366, 768));
		window.setView(view);

		menuNum = 0;
		window.clear();

		if (IntRect(100, 60, 340, 54).contains(Mouse::getPosition(window)))
		{
			menuNum = 1;
			menu1.setPosition(100 + 8, 60 + 8);
		}

		if (IntRect(100, 170, 386, 64).contains(Mouse::getPosition(window)))
		{
			menuNum = 2;
			menu2.setPosition(100 + 8, 170 + 8);
		}


		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) { isMenu = false; toNextLvl = 1; }// переход на следующий лвл
			if (menuNum == 2) { isMenu = false; toNextLvl = 2; break; } // выход в главное меню

		}



		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(lvlcom);

		window.display();
	}
	////////////////////////////////////////////////////
}
