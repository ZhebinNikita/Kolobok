#include "Constants.h"
#include "MainMenu.h"

int toMainMenu = 0;

// Реализация меню паузы
void setPauseMenu(RenderWindow & window) {

	toMainMenu = 0;
	Texture menuTexture1, menuTexture2, menuBackground;
	menuTexture1.loadFromFile("images/Menu/Continue.png");
	menuTexture2.loadFromFile("images/Menu/ExitPM.png");
	menuBackground.loadFromFile("images/Menu/BackgrSelection.png");

	Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;

	menuTexture1.setSmooth(true);
	menuTexture2.setSmooth(true);
	menuBackground.setSmooth(true);

	menuBg.setPosition(0, 0);


	View view;
	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setPosition(Vector2f(100, 60));
		menu2.setPosition(Vector2f(100, 140));



		view.reset(FloatRect(0, 0, 1366, 768)); // без бага с съезжающей камерой
		window.setView(view);

		menuNum = 0;
		window.clear();//Color(129, 181, 221)

		if (IntRect(100, 60, 270, 50).contains(Mouse::getPosition(window)))
		{
			menuNum = 1;
			for (float i = 0; i < 8; i++) menu1.setPosition(100 + i, 60 + i);
		}

		if (IntRect(100, 140, 160, 50).contains(Mouse::getPosition(window)))
		{
			menuNum = 2;
			for (float i = 0; i < 8; i++) menu2.setPosition(100 + i, 140 + i);
		}


		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) { isMenu = false; }// выходим из меню 
			if (menuNum == 2) {
				isMenu = false; toMainMenu = 1; numh = 0;

				for (int i = 0; i < 5; i++) { // сброс параметров
					Stars[i] = true;
					soundStars[i] = true;
				}

				heart1 = true; heart2 = true; heart3 = true; // сброс сердец

			}

		}



		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);

		window.display();
	}
	////////////////////////////////////////////////////
}
