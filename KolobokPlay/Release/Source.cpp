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

	soundBonusOff = true; // звук при активации бонуса

	b2Vec2 Gravity(0.f, 9.8f); // величина гравитации
	b2World World(Gravity); // переменная мира

fromSLMtoMM: // Из меню выбора уровня возвращаемся в главное меню

	fromSLMtoMM = false;
	if (toNextLvl == 0 && Restart == false) setMenu(window); // Если нам не нужно на следующий уровень
															 // и мы не перезапускаем его, то только тогда можем установить главное меню

	else if (toNextLvl == 1) SelectLvl = true; // иначе если мы переходим на слеюущий уровень
	if (exfromGame == false) return false; // выходим из игры
	if (SelectLvl || Restart == true || toNextLvl == 2) {

		if ((toNextLvl == 0 || toNextLvl == 2) && Restart == false) // если нам нужно на след. лвл и не перезапускаем текущий лвл
		{
			nlvl = setSLMenu(window); // номер уровня определяется возвращаемым значением из меню выбора уровня
			if (fromSLMtoMM == true) goto fromSLMtoMM;
		} // если false, переходим по метке из меню выбора уровня в главное

		else if (Restart == false) { if (nlvl < 5)nlvl++; }; // иначе если не перезапускаем уровень, тогда если лвл меньше 5
															 // инкрементируем переменную nlvl

		switch (nlvl) // в зависимости от значения переменой, устанавливаем данные определённого уровня
		{
		case 1:lvl.setLevel1(World); break;
		case 2:lvl.setLevel2(World); break;
		case 3:lvl.setLevel3(World); break;
		case 4:lvl.setLevel4(World); break;
		case 5:lvl.setLevel5(World); break;
		}
	}

	SelectLvl = false; Restart = false; // сбрасываем переменные
	toNextLvl = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	window.setFramerateLimit(70); // устанавлиаваем лимит кадров в секунду(70)

	view.reset(FloatRect(0, 0, 683 + 341.5f, 384 + 192.0f)); // устанавливаем вид камеры

	Clock clock; //привязка ко времени(а не загруженности/мощности процессора).

	Player MainPlayer("player.png", 17, 0, 160, 33, 33, 22, 12, World); // создаём главного персонажа

	float CurrentFrame = 0; // Хранит текущий кадр
	float time; // перменная времени

	while (window.isOpen())
	{
		time = (float)clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		if (slowmo == false)clock.restart(); // если бонус не активирован, перезапускаем время
											 //Чем больше делитель (сейчас это 800) тем больше действий и плавности будет в игре,
											 // но тем требовательнее она будет к ресурсам ПК.
		time = time / 1; // (800)

		Event e; // некоторое событие
		while (window.pollEvent(e))  // пока приложение открыто
		{
			if (e.type == Event::Closed) // если тип события закрытый - выходим
				window.close();
		}

		if (slowmo == true && time < 10000000.0f) // если активирован бонус, меняем значение переменной для замедления физики в игре
		{
			timeb2 = 0.5f;
		}
		if (time > 10000000.0f || slowmo == false) // если прошло 10 сек, сбрасываем данные для активации бонуса
		{
			slowmo = false;
			timeb2 = 1.0f;
			power = 0;
		}
		World.Step(timeb2 / 60.f, 8, 3); // Шаг в симуляции Box2D (действия физики за 1/60 секунды + параметры точности(по умолчанию))

										 /////////////////////////////////////////////////////////////////////////////////////////

		if (Keyboard::isKeyPressed(Keyboard::Escape) || (toMainMenuisone == 1))// если нажата клаваша Esc 
		{																	   //или переменная для перехода в главное меню равна 1

			if (toMainMenuisone == 1)// для перехода в главное меню путем установки определенных значений и выхода из внешнего тела
			{
				toMainMenu = 1; toMainMenuisone = 0;
				window.clear(); break;
			}

			sound.soundButton(); // звук нажатия кнопки

			setPauseMenu(window); // установка меню паузы
			if ((toMainMenu == 1)) // для перехода в главное меню из меню паузы
			{
				toMainMenu = 1; toMainMenuisone = 0;
				window.clear(); break;
			}
		}
		// получаем кординаты нашего персонажа для камеры
		getplayercoordinateforview(MainPlayer.sprite.getPosition().x, MainPlayer.sprite.getPosition().y);

		window.setView(view);//"оживляем" камеру в окне sfml

		window.clear(); // чистим окно

						/////////////////////////////////////////////////////////////////////////////////////////

		switch (nlvl) // отрисовываем уровень по дефолту
		{
		case 1:;
		default:lvl.Drawlvl(World);
		}

		/////////////////////////////////////////////////////////////////////////////////////////

		MainPlayer.Control(window, World); // главная функция персонажа, устанавливающая управление и взаимодействие с миром

		if (toNextLvl == 1 || toNextLvl == 2) { window.clear(); break; } // если переходим на следущий уровень, прерываем

		if (Restart == true) { window.clear(); break; } // fail menu RESTART

		window.display(); // отображение отрисованых обьектов
	}
	return true; // по умолчанию возвращаем true
}

void gameRunning() {
	if (startGame() && exfromGame) { gameRunning(); }  // пока работает игровой цикл и не выходим из игры (exfromGame == true), продолжаем игру
}

int main()
{

		HWND hWnd = GetConsoleWindow();//берем текущ консоль, (скрывает консоль (работает только под windows))
		ShowWindow(hWnd, SW_HIDE);//скрывает консоль


	// Чтение из файл номер пройденного уровня для дальнейшего доступа к предшествующим уровня до данного
	int lastComplLvl = 0;
	std::ifstream save1("savelvl.txt");
	save1 >> lastComplLvl;
	nlvl = lastComplLvl;
	save1.close();

	for (int i = 0; i < lastComplLvl; i++) access[i] = true; // Отрытие доступа пройденным ранее уровням

	gameRunning(); // функция работы игры 

				   // Запись в файл номер пройденного уровня для дальнейшего доступа к предшествующим уровня до данного
	for (int i = 4; i >= 0; i--) { if (access[i] == true) { lastComplLvl = i + 1; break; } }

	std::ofstream save("savelvl.txt");
	save << lastComplLvl;
	save.close();
}

/* Time SFML
Bремя обновляет игровую логику игры
и само оно так же постоянно обновляется (а если быть точнее перезапускается) в бесконечном цикле.
*/

/*
деструктор автоматически
вызывается компилятором в тот момент, когда объект выходит из области видимости.
*/
