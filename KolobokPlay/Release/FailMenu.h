#include "Constants.h"

// Реализация меню поражения
void setFailMenu(RenderWindow & window) {

	slowmo = false;

	for (int i = 0; i < 5; i++) Stars[i] = true; // сбрасывание звёзд (теперь их снова можно собрать)

	numh = 0;

	// загразука текстур и установка спрайтов, масштаба, сглаживания
	Texture menuTexture1, menuTexture2, menuBackground, menuBg2;
	menuTexture1.loadFromFile("images/Menu/Exit2.png");
	menuTexture2.loadFromFile("images/Menu/Restart.png");

	menuBackground.loadFromFile("images/Menu/BackgrSelection.png");

	Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;

	menuTexture1.setSmooth(true);
	menuTexture2.setSmooth(true);
	menuBackground.setSmooth(true);
	menuBg2.setSmooth(true);

	menu1.setScale(1.3f, 1.3f);

	menuBg.setPosition(0, 0);


	View view;

	while (isMenu) // цикл отображения меню
	{
		menu2.setPosition(Vector2f(100, 60)); // устанавливаем позицию спрайтов на экране
		menu1.setPosition(Vector2f(100, 160));



		view.reset(FloatRect(0, 0, 1366, 768)); // камера для меню
		window.setView(view); // установка вида для текущего меню

		menuNum = 0;
		window.clear();

		// реализация анимации 
		if (IntRect(100, 60, 379, 55).contains(Mouse::getPosition(window)))
		{
			menuNum = 1;
			menu2.setPosition(100 + 8, 60 + 8);
		}

		if (IntRect(100, 160, 165, 55).contains(Mouse::getPosition(window)))
		{
			menuNum = 2;
			menu1.setPosition(100 + 8, 160 + 8);
		}


		if (Mouse::isButtonPressed(Mouse::Left)) // при нажатии на определенную иконку
		{
			if (menuNum == 1) {
				isMenu = false; Restart = true; break; // выход и перезапуск

				for (int i = 0; i < 5; i++) { // сбрасываем звук для сбора звезд
					soundStars[i] = true;
				}

			}
			if (menuNum == 2) { isMenu = false; toMainMenuisone = 1; break; } // выход в главное меню

		}


		// отрисовка и отображение
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);

		window.display();
	}
	////////////////////////////////////////////////////
}
