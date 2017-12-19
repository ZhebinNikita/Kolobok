#pragma once
#include "SFML\Audio.hpp"	// for MUSIC

#include "Constants.h"
#include "view.h"
#include "WinMenu.h"
#include "FailMenu.h"

#include "Sounds.h"

////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player {
public:
	Color color;

	Texture texture, tHeart, tBonus;
	Sprite sprite, sHeart, sBonus;

	b2BodyDef bdef; // Определение тела блока в world	
	b2CircleShape circle; // ФОРМА ТЕЛА, тк перс - шар 
	b2Body *pBody; // для создания тела в игровом мире

	bool onGround; // для проверки находится ли персонаж на земле
	b2Vec2 pos;		// для получения кординат
	b2Body* it;		// указатель не тело Box2D
	b2Fixture *f;
	bool awake;   // для корректной работы функций управления
	b2Vec2 vel;  // для считывания угла
	float  angVel;

	b2Vec2 posP; // Считываем позицию
	float angleP;	// Считываем угол
	b2Body* itp; // для пробежки по телам

	SoundGame soundg; // for sounds

	Player(String F, int r, int rectLeft, int rectTop, int rectWidth, int rectHeight, float posX, float posY, b2World & World) {
		texture.loadFromFile("images/" + F); // загружаем изображение
		texture.setSmooth(true); // сглаживание

		sprite.setTexture(texture); // установливаем спрайту изображение

		sprite.setTextureRect(IntRect(rectLeft, rectTop, rectWidth, rectHeight));
		sprite.setOrigin((float)rectWidth / 2, (float)rectHeight / 2); // переносим точку отсчёта в центр картинки

		bdef.type = b2_dynamicBody; // тип тела - динамическое
		bdef.position.Set(posX, posY); // позиция персонажа в мире

		circle.m_radius = r / 30.f; // для масштабирования, ибо по умолчанию счёт в метрах, переводим в пиксели 

		pBody = World.CreateBody(&bdef); // Тело в мир
		pBody->CreateFixture(&circle, 2);		// СОЗДАТЬ ПРИВЯЗКУ !!! (2 параметр - плотность)
		pBody->SetUserData("player"); // идентифицировать объект	

									  ///////////////////////////////////////////////////////////////////////////////////////////////////// Hearts

		tHeart.loadFromFile("images/TileSet/hearts.png");
		tHeart.setSmooth(true);
		sHeart.setTexture(tHeart);
		sHeart.setScale(0.7f, 0.7f); // устанавливаем масштаб спрайта


		tBonus.loadFromFile("images/TileSet/hearts.png");
		tBonus.setSmooth(true);
		sBonus.setTexture(tBonus);
		sBonus.setScale(0.7f, 0.7f);

	}


	void Control(RenderWindow & window, b2World & World) // for Draw
	{
		/////check if onGround//////
		onGround = 0;
		pos = pBody->GetPosition(); // Считываем позицию персонажа
		pos.y += 18.5f / SCALE; // ТОЧКА прям под персонажем 
		for (it = World.GetBodyList(); it != 0; it = it->GetNext()) // Проходим в цикле по всем телам
			for (f = it->GetFixtureList(); f != 0; f = f->GetNext()) // Для каждого тела проходим по всем прикреплённым к нему фигурам
				if (f->TestPoint(pos))  onGround = true; // Если эта ТОЧКА попала внутрь

														 ///////////////////////////// CONTROL ///////////////////////////////////////////////////////////////////////////////

		awake = true;

		vel = pBody->GetLinearVelocity();	 // СЧИТЫВАНИЕ СКОРОСТИ 
		angVel = pBody->GetAngularVelocity(); // СЧИТЫВАНИЕ УГЛОВОЙ СКОРОСТИ

											  // ОГРАНИЧЕНИЕ СКОРОСТИ(+-20)				// ПРИДАЁМ УСКОРЕНИЕ ПО X и Y (Torque)																				// Вращение персонажа с ограничением угловой скорости (Torque - вращать)
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
			if (vel.x < 5) {
				pBody->ApplyForceToCenter(b2Vec2(80 + (power / 8), 0), awake);
				if (angVel < 10 / 2) pBody->ApplyTorque(10, NULL);
			}


		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
			if (vel.x > -5) {
				pBody->ApplyForceToCenter(b2Vec2(-80 - (power / 8), 0), awake);
				if (angVel > -10 / 2)  pBody->ApplyTorque(-10, NULL);
			}


		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Space))// JUMP
		{
			if (onGround) {
				soundg.soundJump();
				pBody->ApplyForceToCenter(b2Vec2(0, -1000 - (power / 2 + (power / 4))), awake);
				onGround = false;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		{
			pBody->SetAwake(true);
			pBody->ApplyForceToCenter(b2Vec2(0, 20 + (power / 9)), awake);

		}

		//////////////////////////////////////// DRAW ///////////////////////////////////////////////////////////////////////////////////
		for (this->itp = World.GetBodyList(); this->itp != 0; this->itp = this->itp->GetNext()) // пробегаем по всем телам (GetBodyList())
		{
			this->posP = this->itp->GetPosition(); // Считываем позицию
			this->angleP = this->itp->GetAngle();	// Считываем угол
			if (this->itp->GetUserData() == "player")
			{

				this->sprite.setPosition(this->posP.x*SCALE, this->posP.y*SCALE);
				this->sprite.setRotation(this->angleP*DEG);
				window.draw(this->sprite);
			}
		}

		//////////////////////////////////////////////////// WIN //////////////////////////////////////////////////////////////////////////// 

		switch (nlvl) // проверка в зависимости от номера уровня. Если спрайт персонажа расположжен дальше определенной позиции,
		{ // устанавливаем меню пройденного уровня и проигрываем звук
		case 2:
			if (this->sprite.getPosition().x > 3564)
			{
				soundg.soundWin();

				setWinMenu(window);
			}
			; break;

		case 1:
			if (this->sprite.getPosition().x > 3375)
			{
				soundg.soundWin();

				setWinMenu(window);
			}
			; break;

		case 3:
			if (this->sprite.getPosition().x > 3354)
			{
				soundg.soundWin();

				setWinMenu(window);
			}
			; break;

		case 4:

			if (this->sprite.getPosition().x > 3356)
			{
				soundg.soundWin();

				setWinMenu(window);
			}

			; break;
		case 5:

			if (this->sprite.getPosition().x > 3545)
			{
				soundg.soundWin();

				setWinMenu(window);
			}

			; break;
		}


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// DEATH

		switch (nlvl) // реализация гибели персонажа, жизней, активации бонуса.
		{
		case 2:

			if ((this->sprite.getPosition().y > 777) || (this->sprite.getPosition().x > 1412 && this->sprite.getPosition().x < 1435 && this->sprite.getPosition().y>649) || (this->sprite.getPosition().x > 1540 && this->sprite.getPosition().x < 1562 && this->sprite.getPosition().y>649) || (this->sprite.getPosition().x > 2820 && this->sprite.getPosition().x < 2843 && this->sprite.getPosition().y>678) || (this->sprite.getPosition().x > 3428 && this->sprite.getPosition().x < 3451 && this->sprite.getPosition().y>681))
			{
				soundg.soundDeath();

				for (int i = 0; i < 10; i++) {
					this->sprite.setTextureRect(IntRect(32, 63, 33, 33));	this->sprite.setColor(Color::Red); window.draw(this->sprite); window.display();
					this->sprite.setTextureRect(IntRect(198, 64, 33, 33));	this->sprite.setColor(Color::Blue); window.draw(this->sprite); window.display();
					this->sprite.setTextureRect(IntRect(32, 63, 33, 33));	this->sprite.setColor(Color::Cyan); window.draw(this->sprite); window.display();
					this->sprite.setTextureRect(IntRect(198, 64, 33, 33));	this->sprite.setColor(Color::Yellow); window.draw(this->sprite); window.display();
				}



				switch (numh)
				{
				case 0:heart3 = false; Restart = true;	break;
				case 1:heart2 = false; Restart = true;	break;
				case 2:heart1 = false; break;
				}
				numh++;
				slowmo = false;
			}

			; break;

		case 1:

			if ((this->sprite.getPosition().x > 1310 && this->sprite.getPosition().x < 1344 && this->sprite.getPosition().y>426) || (this->sprite.getPosition().x > 3200 && this->sprite.getPosition().x < 3260 && this->sprite.getPosition().y>615) || (this->sprite.getPosition().x > 3011 && this->sprite.getPosition().x < 3068 && this->sprite.getPosition().y>615) || (this->sprite.getPosition().x > 2852 && this->sprite.getPosition().x < 2908 && this->sprite.getPosition().y>615) || (this->sprite.getPosition().x > 2756 && this->sprite.getPosition().x < 2780 && this->sprite.getPosition().y>615) || (this->sprite.getPosition().y > 776))
			{
				soundg.soundDeath();


				for (int i = 0; i < 10; i++) {
					this->sprite.setTextureRect(IntRect(32, 63, 33, 33));	this->sprite.setColor(Color::Red); window.draw(this->sprite); window.display();
					this->sprite.setTextureRect(IntRect(198, 64, 33, 33));	this->sprite.setColor(Color::Blue); window.draw(this->sprite); window.display();
					this->sprite.setTextureRect(IntRect(32, 63, 33, 33));	this->sprite.setColor(Color::Cyan); window.draw(this->sprite); window.display();
					this->sprite.setTextureRect(IntRect(198, 64, 33, 33));	this->sprite.setColor(Color::Yellow); window.draw(this->sprite); window.display();


				}



				switch (numh)
				{
				case 0:heart3 = false; Restart = true;	break;
				case 1:heart2 = false; Restart = true;	break;
				case 2:heart1 = false; break;
				}
				numh++;
				slowmo = false;
			}

			; break;

		case 3:

			if ((this->sprite.getPosition().x > 705 && this->sprite.getPosition().x < 732 && this->sprite.getPosition().y>550) || (this->sprite.getPosition().x > 993 && this->sprite.getPosition().x < (993 + 32) && this->sprite.getPosition().y < 441) || (this->sprite.getPosition().x > 1154 && this->sprite.getPosition().x < (1154 + 32) && this->sprite.getPosition().y < 441) || (this->sprite.getPosition().x > 1313 && this->sprite.getPosition().x < (1313 + 32) && this->sprite.getPosition().y < 441) || (this->sprite.getPosition().x > 1058 && this->sprite.getPosition().x < (1058 + 30) && this->sprite.getPosition().y>550) || (this->sprite.getPosition().y > 776) || (this->sprite.getPosition().x > 1155 && this->sprite.getPosition().x < (1155 + (31 * 3)) && this->sprite.getPosition().y>550) || (this->sprite.getPosition().x > 1346 && this->sprite.getPosition().x < (1346 + 30) && this->sprite.getPosition().y>550) || (this->sprite.getPosition().x > 1858 && this->sprite.getPosition().x < (1858 + 30) && this->sprite.getPosition().y>550) || (this->sprite.getPosition().x > 2020 && this->sprite.getPosition().x < (2020 + (31 * 3)) && this->sprite.getPosition().y < (513 + 31)) || (this->sprite.getPosition().x > 2049 && this->sprite.getPosition().x < (2049 + 30) && this->sprite.getPosition().y < 572) || (this->sprite.getPosition().x > 3013 && this->sprite.getPosition().x < (3013 + 30) && this->sprite.getPosition().y < 510))
			{
				soundg.soundDeath();


				for (int i = 0; i < 10; i++) {
					this->sprite.setTextureRect(IntRect(32, 63, 33, 33));	this->sprite.setColor(Color::Red); window.draw(this->sprite); window.display();
					this->sprite.setTextureRect(IntRect(198, 64, 33, 33));	this->sprite.setColor(Color::Blue); window.draw(this->sprite); window.display();
					this->sprite.setTextureRect(IntRect(32, 63, 33, 33));	this->sprite.setColor(Color::Cyan); window.draw(this->sprite); window.display();
					this->sprite.setTextureRect(IntRect(198, 64, 33, 33));	this->sprite.setColor(Color::Yellow); window.draw(this->sprite); window.display();


				}



				switch (numh)
				{
				case 0:heart3 = false; Restart = true;	break;
				case 1:heart2 = false; Restart = true;	break;
				case 2:heart1 = false; break;
				}
				numh++;
				slowmo = false;
			}

			; break;

		case 4:

			if ((this->sprite.getPosition().x > 2338 && this->sprite.getPosition().x < (2338 + 31) && this->sprite.getPosition().y>710) || (this->sprite.getPosition().x > 2209 && this->sprite.getPosition().x < (2209 + 31) && this->sprite.getPosition().y>710) || (this->sprite.getPosition().x > 2595 && this->sprite.getPosition().x < (2595 + 31) && this->sprite.getPosition().y>704 - 31) || (this->sprite.getPosition().x > 2529 && this->sprite.getPosition().x < (2529 + 31) && this->sprite.getPosition().y>704 - 31) || (this->sprite.getPosition().x > 994 && this->sprite.getPosition().x < (994 + 31) && this->sprite.getPosition().y>615) || (this->sprite.getPosition().x > 1090 && this->sprite.getPosition().x < (1090 + 32 * 3) && this->sprite.getPosition().y>615 && this->sprite.getPosition().y < 640) || (this->sprite.getPosition().x > 1347 && this->sprite.getPosition().x < (1347 + 31 * 2) && this->sprite.getPosition().y>710) || (this->sprite.getPosition().x > 1475 - 31 && this->sprite.getPosition().x < (1475 + 31) && this->sprite.getPosition().y>710) || (this->sprite.getPosition().x > 1522 && this->sprite.getPosition().x < (1522 + 31) && this->sprite.getPosition().y>326 && this->sprite.getPosition().y < 366) || (this->sprite.getPosition().y > 776) || (this->sprite.getPosition().x > 1954 && this->sprite.getPosition().x < (1954 + 31 * 2) && this->sprite.getPosition().y>358) || (this->sprite.getPosition().x > 2015 && this->sprite.getPosition().x < (2015 + 31) && this->sprite.getPosition().y>386) || (this->sprite.getPosition().x > 2117 && this->sprite.getPosition().x < (2117 + 30) && this->sprite.getPosition().y>450 && this->sprite.getPosition().y < 511) || (this->sprite.getPosition().x > 2146 && this->sprite.getPosition().x < (2146 + (31 * 3)) && this->sprite.getPosition().y>420 && this->sprite.getPosition().y < 450) || (this->sprite.getPosition().x > 2210 && this->sprite.getPosition().x < (2210 + 30) && this->sprite.getPosition().y < 440) || (this->sprite.getPosition().x > 2274 && this->sprite.getPosition().x < (2274 + 31) && this->sprite.getPosition().y>710) || (this->sprite.getPosition().x > 2914 && this->sprite.getPosition().x < (2914 + 31 * 2) && this->sprite.getPosition().y>675) || (this->sprite.getPosition().x > 3040 && this->sprite.getPosition().x < (3040 + 31 * 2) && this->sprite.getPosition().y>675) || (this->sprite.getPosition().x > 3170 && this->sprite.getPosition().x < (3170 + 31 * 2) && this->sprite.getPosition().y>675) || (this->sprite.getPosition().x > 3266 && this->sprite.getPosition().x < (3266 + 31) && this->sprite.getPosition().y>675))
			{
				soundg.soundDeath();


				for (int i = 0; i < 10; i++) {
					this->sprite.setTextureRect(IntRect(32, 63, 33, 33));	this->sprite.setColor(Color::Red); window.draw(this->sprite); window.display();
					this->sprite.setTextureRect(IntRect(198, 64, 33, 33));	this->sprite.setColor(Color::Blue); window.draw(this->sprite); window.display();
					this->sprite.setTextureRect(IntRect(32, 63, 33, 33));	this->sprite.setColor(Color::Cyan); window.draw(this->sprite); window.display();
					this->sprite.setTextureRect(IntRect(198, 64, 33, 33));	this->sprite.setColor(Color::Yellow); window.draw(this->sprite); window.display();


				}


				switch (numh)
				{
				case 0:heart3 = false; Restart = true;	break;
				case 1:heart2 = false; Restart = true;	break;
				case 2:heart1 = false; break;
				}
				numh++; slowmo = false;
			}

			; break;
		case 5:

			if ((this->sprite.getPosition().x < 541 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 898 && this->sprite.getPosition().x < 957 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 994 && this->sprite.getPosition().x < 1117 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 1218 && this->sprite.getPosition().x < 1341 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 1410 && this->sprite.getPosition().x < 1502 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 1538 && this->sprite.getPosition().x < 1597 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 1666 && this->sprite.getPosition().x < 1694 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 1730 && this->sprite.getPosition().x < 1821 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 1858 && this->sprite.getPosition().x < 1886 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 1922 && this->sprite.getPosition().x < 2014 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 2082 && this->sprite.getPosition().x < 2238 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 2306 && this->sprite.getPosition().x < 2430 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 2467 && this->sprite.getPosition().x < 2589 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 2627 && this->sprite.getPosition().x < 2686 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 2723 && this->sprite.getPosition().x < 2844 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 2883 && this->sprite.getPosition().x < 3005 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 3075 && this->sprite.getPosition().x < 3197 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x > 3266 && this->sprite.getPosition().x < 3357 && this->sprite.getPosition().y>772) || (this->sprite.getPosition().x < 3545 && this->sprite.getPosition().y>997))
			{
				soundg.soundDeath();


				for (int i = 0; i < 10; i++) {
					this->sprite.setTextureRect(IntRect(32, 63, 33, 33));	this->sprite.setColor(Color::Red); window.draw(this->sprite); window.display();
					this->sprite.setTextureRect(IntRect(198, 64, 33, 33));	this->sprite.setColor(Color::Blue); window.draw(this->sprite); window.display();
					this->sprite.setTextureRect(IntRect(32, 63, 33, 33));	this->sprite.setColor(Color::Cyan); window.draw(this->sprite); window.display();
					this->sprite.setTextureRect(IntRect(198, 64, 33, 33));	this->sprite.setColor(Color::Yellow); window.draw(this->sprite); window.display();


				}


				switch (numh)
				{
				case 0:heart3 = false; Restart = true;	break;
				case 1:heart2 = false; Restart = true;	break;
				case 2:heart1 = false; break;
				}
				numh++; slowmo = false;
			}

			; break;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////// DRAW HEARTS ///////////////////////////////////////////////////////////////////////////////////
		// отрисовка сердце относительно камеры при условии утрачено оно или нет
		if (heart1 == true) {
			sHeart.setTextureRect(IntRect(320, 70, 60, 70));
			this->sHeart.setPosition(view.getCenter().x - 460, view.getCenter().y - 270);
			window.draw(this->sHeart);
		}
		else
		{
			sHeart.setTextureRect(IntRect(240, 67, 80, 125 - 68));
			this->sHeart.setPosition(view.getCenter().x - 460, view.getCenter().y - 275);
			window.draw(this->sHeart);
		}
		if (heart2 == true) {
			sHeart.setTextureRect(IntRect(320, 70, 60, 70));
			this->sHeart.setPosition(view.getCenter().x - 460 + 35, view.getCenter().y - 270);
			window.draw(this->sHeart);
		}
		else
		{
			sHeart.setTextureRect(IntRect(240, 67, 80, 125 - 68));
			this->sHeart.setPosition(view.getCenter().x - 460 + 35, view.getCenter().y - 275);
			window.draw(this->sHeart);
		}
		if (heart3 == true) {
			sHeart.setTextureRect(IntRect(320, 70, 60, 70));
			this->sHeart.setPosition(view.getCenter().x - 460 + 70, view.getCenter().y - 270);
			window.draw(this->sHeart);
		}
		else
		{
			sHeart.setTextureRect(IntRect(240, 67, 80, 125 - 68));
			this->sHeart.setPosition(view.getCenter().x - 460 + 70, view.getCenter().y - 275);
			window.draw(this->sHeart);
		}



		if (heart1 == false && heart2 == false && heart3 == false) {
			setFailMenu(window);
			heart1 = true; heart2 = true; heart3 = true; numh = 0;
		}


		//////////////////////////////////////// STARS ///////////////////////////////////////////////////////////////////////////////////
		// Установка звезд в зависимости от уровня
		switch (nlvl)
		{
		case 1:

			if (this->sprite.getPosition().x > 440 && this->sprite.getPosition().x < 450 + 60 && this->sprite.getPosition().y > 490 && this->sprite.getPosition().y < 490 + 40) Stars[0] = false;
			if (this->sprite.getPosition().x > 1015 && this->sprite.getPosition().x < 1025 + 60 && this->sprite.getPosition().y > 400 && this->sprite.getPosition().y < 400 + 40) Stars[1] = false;
			if (this->sprite.getPosition().x > 1020 && this->sprite.getPosition().x < 1030 + 60 && this->sprite.getPosition().y > 250 && this->sprite.getPosition().y < 250 + 40) Stars[2] = false;
			if (this->sprite.getPosition().x > 1740 && this->sprite.getPosition().x < 1740 + 60 && this->sprite.getPosition().y > 465 && this->sprite.getPosition().y < 465 + 40) Stars[3] = false;
			if (this->sprite.getPosition().x > 2690 && this->sprite.getPosition().x < 2690 + 60 && this->sprite.getPosition().y > 535 && this->sprite.getPosition().y < 535 + 40) Stars[4] = false;

			break;
		case 2:

			if (this->sprite.getPosition().x > 440 && this->sprite.getPosition().x < 450 + 60 && this->sprite.getPosition().y > 490 && this->sprite.getPosition().y < 490 + 40) Stars[0] = false;
			if (this->sprite.getPosition().x > 935 && this->sprite.getPosition().x < 945 + 60 && this->sprite.getPosition().y > 715 && this->sprite.getPosition().y < 715 + 40) Stars[1] = false;
			if (this->sprite.getPosition().x > 1645 && this->sprite.getPosition().x < 1655 + 60 && this->sprite.getPosition().y > 600 && this->sprite.getPosition().y < 600 + 40) Stars[2] = false;
			if (this->sprite.getPosition().x > 2565 && this->sprite.getPosition().x < 2575 + 60 && this->sprite.getPosition().y > 575 && this->sprite.getPosition().y < 575 + 40) Stars[3] = false;
			if (this->sprite.getPosition().x > 3075 && this->sprite.getPosition().x < 3085 + 60 && this->sprite.getPosition().y > 665 && this->sprite.getPosition().y < 665 + 40) Stars[4] = false;

			break;
		case 3:

			if (this->sprite.getPosition().x > 605 && this->sprite.getPosition().x < 615 + 60 && this->sprite.getPosition().y > 630 && this->sprite.getPosition().y < 630 + 40) Stars[0] = false;
			if (this->sprite.getPosition().x > 515 && this->sprite.getPosition().x < 525 + 60 && this->sprite.getPosition().y > 530 && this->sprite.getPosition().y < 530 + 40) Stars[1] = false;
			if (this->sprite.getPosition().x > 1190 && this->sprite.getPosition().x < 1200 + 60 && this->sprite.getPosition().y > 470 && this->sprite.getPosition().y < 470 + 40) Stars[2] = false;
			if (this->sprite.getPosition().x > 1740 && this->sprite.getPosition().x < 1750 + 60 && this->sprite.getPosition().y > 465 && this->sprite.getPosition().y < 465 + 40) Stars[3] = false;
			if (this->sprite.getPosition().x > 1706 && this->sprite.getPosition().x < 1716 + 60 && this->sprite.getPosition().y > 475 && this->sprite.getPosition().y < 475 + 40) Stars[4] = false;

			break;
		case 4:

			if (this->sprite.getPosition().x > 1150 && this->sprite.getPosition().x < 1160 + 60 && this->sprite.getPosition().y > 690 && this->sprite.getPosition().y < 690 + 40) Stars[0] = false;
			if (this->sprite.getPosition().x > 1415 && this->sprite.getPosition().x < 1425 + 60 && this->sprite.getPosition().y > 650 && this->sprite.getPosition().y < 650 + 40) Stars[1] = false;
			if (this->sprite.getPosition().x > 1870 && this->sprite.getPosition().x < 1880 + 60 && this->sprite.getPosition().y > 300 && this->sprite.getPosition().y < 300 + 40) Stars[2] = false;
			if (this->sprite.getPosition().x > 2305 && this->sprite.getPosition().x < 2315 + 60 && this->sprite.getPosition().y > 670 && this->sprite.getPosition().y < 670 + 40) Stars[3] = false;
			if (this->sprite.getPosition().x > 3233 && this->sprite.getPosition().x < 3243 + 60 && this->sprite.getPosition().y > 660 && this->sprite.getPosition().y < 660 + 40) Stars[4] = false;

			break;
		}

		for (int i = 0; i < 5; i++) // берём звезду - проигрывается звук
		{
			if (Stars[i] == false && soundStars[i] == true)
			{
				soundg.soundStar(); soundStars[i] = false;
			}
		}

		//////////////////////////////////////// BONUSES ///////////////////////////////////////////////////////////////////////////////////

		// Установка, отрисовка бонусов в зависимости от их количества
		if (bonuses == 1 || bonuses == 2 || bonuses == 3 || bonuses == 4) {
			sBonus.setTextureRect(IntRect(320, 388, 60, 70));
			this->sBonus.setPosition(view.getCenter().x - 460, view.getCenter().y - 220);
			window.draw(this->sBonus);
		}
		if (bonuses == 2 || bonuses == 3 || bonuses == 4) {
			sBonus.setTextureRect(IntRect(320, 388, 60, 70));
			this->sBonus.setPosition(view.getCenter().x - 430, view.getCenter().y - 220);
			window.draw(this->sBonus);
		}
		if (bonuses == 3 || bonuses == 4) {
			sBonus.setTextureRect(IntRect(320, 388, 60, 70));
			this->sBonus.setPosition(view.getCenter().x - 400, view.getCenter().y - 220);
			window.draw(this->sBonus);
		}
		if (bonuses == 4) {
			sBonus.setTextureRect(IntRect(320, 388, 60, 70));
			this->sBonus.setPosition(view.getCenter().x - 370, view.getCenter().y - 220);
			window.draw(this->sBonus);
		}

		if (bonuses > 0) { // активация бонуса
			if (Keyboard::isKeyPressed(Keyboard::F))
			{
				bonuses--; slowmo = true; power = 2000;
				soundg.soundBonusOn();
			}
		}



	}
};

