#include "Constants.h"

// ���������� ���� ���������
void setFailMenu(RenderWindow & window) {

	slowmo = false;

	for (int i = 0; i < 5; i++) Stars[i] = true; // ����������� ���� (������ �� ����� ����� �������)

	numh = 0;

	// ��������� ������� � ��������� ��������, ��������, �����������
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

	while (isMenu) // ���� ����������� ����
	{
		menu2.setPosition(Vector2f(100, 60)); // ������������� ������� �������� �� ������
		menu1.setPosition(Vector2f(100, 160));



		view.reset(FloatRect(0, 0, 1366, 768)); // ������ ��� ����
		window.setView(view); // ��������� ���� ��� �������� ����

		menuNum = 0;
		window.clear();

		// ���������� �������� 
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


		if (Mouse::isButtonPressed(Mouse::Left)) // ��� ������� �� ������������ ������
		{
			if (menuNum == 1) {
				isMenu = false; Restart = true; break; // ����� � ����������

				for (int i = 0; i < 5; i++) { // ���������� ���� ��� ����� �����
					soundStars[i] = true;
				}

			}
			if (menuNum == 2) { isMenu = false; toMainMenuisone = 1; break; } // ����� � ������� ����

		}


		// ��������� � �����������
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);

		window.display();
	}
	////////////////////////////////////////////////////
}
