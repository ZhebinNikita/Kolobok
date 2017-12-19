#pragma once
#include "Constants.h"
#include "RWindow.h"

// реализация интерфейса с функциями для установки уровня (изображения, спрайты, расположения статических тел Box2D) 
// и отрисовка с отображением
class Levels
{
public:


	Texture tlevel, bglvl, tStar;
	Sprite slevel, sbglvl, sStar[5];
	int numlvl = 0;

	// 
	void setLevel1(b2World & World)
	{
		bglvl.loadFromFile("images/Levels/BGoflvl/sky1.jpg");
		sbglvl.setTexture(bglvl, false); sbglvl.setPosition(0, -300); sbglvl.setScale(2.5f, 4.5f);

		tlevel.loadFromFile("images/Levels/LEVEL1.png");

		slevel.setTexture(tlevel, false);

		// сглаживание
		tlevel.setSmooth(true);

		////////////   Stars   ///////////////
		tStar.loadFromFile("images/TileSet/hearts.png");
		tStar.setSmooth(true);

		numlvl = 1;


		sStar[0].setTexture(tStar);
		sStar[0].setScale(0.7f, 0.7f);
		sStar[0].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[0].setPosition(450, 500);

		sStar[1].setTexture(tStar);
		sStar[1].setScale(0.7f, 0.7f);
		sStar[1].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[1].setPosition(1025, 410);

		sStar[2].setTexture(tStar);
		sStar[2].setScale(0.7f, 0.7f);
		sStar[2].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[2].setPosition(1030, 260);

		sStar[3].setTexture(tStar);
		sStar[3].setScale(0.7f, 0.7f);
		sStar[3].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[3].setPosition(1750, 475);

		sStar[4].setTexture(tStar);
		sStar[4].setScale(0.7f, 0.7f);
		sStar[4].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[4].setPosition(2700, 545);

		/////////box2d///////////
		setWall(3839 / 2, 800 + 11, 3839 / 2, 10, World);  //

		setWall(385, 0, 10, 2000, World); // left wall
		setWall(3845, 0, 10, 2000, World); // right wall


										   //setWall(512 + (287 / 2)+1, 576 + 11 + (100), 287/2, 10 + (100), World); // red wall
		setRTWall(512, 576, 287, 100, World); // !!!!!!!!!!!!!!!!!!!!!!


		setWall(768 + (32 / 2) + 1, 544 + 11 + (100), 32 / 2, 10 + (100), World); // red box

		setWall(864 + (128 / 2) + 1, 481 + 11 + (100 * 2), 128 / 2, 10 + (100 * 2), World); // first ground

		setWall(1058 + (120 / 2) + 1, 384 + 11 + (100 * 2), 120 / 2, 10 + (100 * 2), World); // second ground

		setWall(1281 + (31 / 2) + 1, 289 + 11 + (100 * 3), 31 / 2, 10 + (100 * 3), World); // 3 ground
		setWall(1310 + ((62 / 2) + 1), 448 + (11 + (100 * 3)), 62 / 2, 10 + (100 * 3), World); // 3 ground hole
		setWall(1346 + ((60 / 2) + 1), 289 + (11 + (100 * 3)), 60 / 2, 10 + (100 * 3), World); // 3 ground

		setWall(1538 + ((92 / 2) + 1), 481 + (11 + (10)), 92 / 2, 10 + (10), World); // 4 platform
		setWall(1553 + ((62 / 2) + 1), 495 + (11 + (100 * 3)), 62 / 2, 10 + (100 * 3), World); // 4 platform


		setWall(1697 + ((68 / 2) + 1), 404 + (11 + (1)), 68 / 2, 10 + (1), World); // 5 platform
		setWall(1760 + ((68 / 2) + 1), 384 - 32 + (11 + (1)), 68 / 2, 10 + (1), World); // 5 platform


		setWall(1794 + ((124 / 2) + 1), 257 + (11 + (100 * 3)), 124 / 2, 10 + (100 * 3), World); // 6 platform


		setWall(1920 + ((62 / 2) + 1), 416 + (11 + (100 * 3)), 62 / 2, 10 + (100 * 3), World); // mini-platform 1
		setWall(1920 + ((62 / 2 * 2) + 1), 416 + (33) + (11 + (100 * 3)), 62 / 2 * 2, 10 + (100 * 3), World); // mini-platform 2
		setWall(1920 + ((62 / 2 * 2 * 2) + 1), 416 + (33 * 2) + (11 + (100 * 3)), 62 / 2 * 2, 10 + (100 * 3), World); // mini-platform 3
		setWall(1920 + ((62 / 2) - 23), 416 + (33 * 2 * 1.5) + (11 + (100 * 3)), 62 / 2 * 2 * 2 * 2, 10 + (100 * 3), World); // mini-platform 4

		setWall(2176 + ((63 / 2) + 1), 545 + (11 + (100 * 3)), 63 / 2, 10 + (100 * 3), World); // mini-platform 5
		setWall(2240 + ((63 / 2) + 1), 576 + (11 + (100 * 3)), 63 / 2, 10 + (100 * 3), World); // mini-platform 6
		setWall(2304 + ((63 / 2) + 1), 608 + (11 + (100 * 3)), 63 / 2, 10 + (100 * 3), World); // mini-platform 7
		setWall(2368 + ((63 / 2) + 1), 641 + (11 + (100 * 3)), 63 / 2, 10 + (100 * 3), World); // mini-platform 8
		setWall(2432 + ((63 / 2) + 1), 673 + (11 + (100 * 3)), 63 / 2, 10 + (100 * 3), World); // mini-platform 9
		setWall(2496 + ((63 / 2) + 1), 705 + (11 + (100 * 3)), 63 / 2, 10 + (100 * 3), World); // mini-platform 10
		setWall(2560 + ((63 / 2) + 1), 736 + (11 + (100 * 3)), 63 / 2, 10 + (100 * 3), World); // mini-platform 11


		setWall(2688 + ((1000 / 2) + 1), 641 + (11 + (100 * 3)), 1000 / 2, 10 + (100 * 3), World); // platform 7


	}


	////////////////////////////////////////////////////////////////////////////////


	void setLevel2(b2World & World)
	{
		bglvl.loadFromFile("images/Levels/BGoflvl/sky.jpg");
		sbglvl.setTexture(bglvl, false); sbglvl.setPosition(0, -300); sbglvl.setScale(2.5f, 2.5f);

		tlevel.loadFromFile("images/Levels/REALLEVEL1.png");

		slevel.setTexture(tlevel, false);


		// сглаживание
		tlevel.setSmooth(true);

		////////////   Stars   ///////////////
		tStar.loadFromFile("images/TileSet/hearts.png");
		tStar.setSmooth(true);

		numlvl = 2;

		sStar[0].setTexture(tStar);
		sStar[0].setScale(0.7f, 0.7f);
		sStar[0].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[0].setPosition(450, 500);

		sStar[1].setTexture(tStar);
		sStar[1].setScale(0.7f, 0.7f);
		sStar[1].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[1].setPosition(945, 725);

		sStar[2].setTexture(tStar);
		sStar[2].setScale(0.7f, 0.7f);
		sStar[2].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[2].setPosition(1655, 610);

		sStar[3].setTexture(tStar);
		sStar[3].setScale(0.7f, 0.7f);
		sStar[3].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[3].setPosition(2575, 585);

		sStar[4].setTexture(tStar);
		sStar[4].setScale(0.7f, 0.7f);
		sStar[4].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[4].setPosition(3085, 675);

		/////////box2d///////////
		setRTWall(0, 801, 4640, 1000, World); // ground

		setRTWall(0, 0, 364, 1000, World); // leftwall
		setRTWall(3840, 0, 364, 1000, World); // rightwall

		setRTWall(512, 576, (800 - 512), 1000, World); // platform 1
		setRTWall(864, 480, (896 - 864 - 3), 1000, World); // platform 2
		setRTWall(928, 768, (950 - 928 + 10), 1000, World); // platform 3
		setRTWall(1056, 672, (1184 - 1056), 1000, World); // platform 4
		setRTWall(1280, 640, (1408 - 1280 - 1), 1000, World); // platform 5
		setRTWall(1408, 640, (1408 - 1408 - 1), 1000, World); // platform 6
		setRTWall(1280, 673, (1568 - 1280), 1000, World); // platform 7
		setRTWall(1664, 640, (1856 - 1664 - 1), 30, World); // platform 8
		setRTWall(1920, 576, (2240 - 1920 - 3), 30, World); // platform 9

		setRTWall(2272, 609, 32, 1000, World); // platform 10
		setRTWall(2272 + 64 + 32, 609, 32, 1000, World); // platform 11
		setRTWall(2272 + 64 * 3, 609, 32, 1000, World); // platform 12
		setRTWall(2272 + 64 * 4 + 32, 609, 32, 1000, World); // platform 13
		setRTWall(2272 + 64 * 7 - 64, 609, 32, 1000, World); // platform 14

		setRTWall(2689, 577, 32 * 3, 32, World); // platform 15
		setRTWall(2816, 705, 32, 32, World); // platform 16
		setRTWall(2816 + 32 * 4, 705, 32, 32, World); // platform 17
		setRTWall(2816 + 32 * 8, 705, 32, 32, World); // platform 18
		setRTWall(2816 + 32 * 12, 705, 32, 32, World); // platform 19
		setRTWall(2816 + 32 * 16, 705, 32, 32, World); // platform 20

		setRTWall(3425, 705, 320, 932, World); // platform 19

	}


	////////////////////////////////////////////////////////////////////////////////


	void setLevel3(b2World & World)
	{
		bglvl.loadFromFile("images/Levels/BGoflvl/sky1.jpg");
		sbglvl.setTexture(bglvl, false); sbglvl.setPosition(0, -300); sbglvl.setScale(2.5f, 2.5f);

		tlevel.loadFromFile("images/Levels/LEVEL3.png");

		slevel.setTexture(tlevel, false);


		// сглаживание
		tlevel.setSmooth(true);

		////////////   Stars   ///////////////
		tStar.loadFromFile("images/TileSet/hearts.png");
		tStar.setSmooth(true);

		numlvl = 3;

		sStar[0].setTexture(tStar);
		sStar[0].setScale(0.7f, 0.7f);
		sStar[0].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[0].setPosition(615, 640);

		sStar[1].setTexture(tStar);
		sStar[1].setScale(0.7f, 0.7f);
		sStar[1].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[1].setPosition(525, 540);

		sStar[2].setTexture(tStar);
		sStar[2].setScale(0.7f, 0.7f);
		sStar[2].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[2].setPosition(1200, 480);

		sStar[3].setTexture(tStar);
		sStar[3].setScale(0.7f, 0.7f);
		sStar[3].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[3].setPosition(1750, 475);

		sStar[4].setTexture(tStar);
		sStar[4].setScale(0.7f, 0.7f);
		sStar[4].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[4].setPosition(1716, 485);

		/////////box2d///////////
		setRTWall(0, 801, 4640, 1000, World); // ground

		setRTWall(0, 0, 383, 1000, World); // leftwall
		setRTWall(3840, 0, 364, 1000, World); // rightwall

		setRTWall(513, 578, 31, 1000, World); // platform 1
		setRTWall(608, 673, 31, 7, World); // platform 2
		setRTWall(640, 578, 31, 1000, World); // platform 3
		setRTWall(640 + 32 * 2 + 2, 578, 29, 1000, World);
		setRTWall(640 + 32 * 4 + 2, 578, 29, 1000, World);


		setRTWall(640 + 32 * (4 + 7) + 2, 578, 32 * 12 - 5, 1000, World);


		setRTWall(1600, 578, 31 * 2, 1000, World);
		setRTWall(1728, 578, 31 * 2, 1000, World);
		setRTWall(1857, 578, 31 * 2, 1000, World);


		setRTWall(1985, 689 + 16, 31 * 3, 5, World);

		setRTWall(1985 + 32 * 5 - 1, 689 + 16, 31 * 4, 5, World);

		setRTWall(1985 + 32 * 18 - 1, 689 + 16, 31 * 4, 5, World);

		setRTWall(2048, 518, 31, 5, World);

		setRTWall(2240, 577, 31, 5 * 5 * 2, World);
		setRTWall(2369, 577, 31, 5 * 5 * 2, World);

		setRTWall(2369, 706, 31 * 4, 7, World);

		setRTWall(2753, 385, 31, 5 * 9 * 2, World);
		setRTWall(2720, 449, 33, 6, World);
		setRTWall(2689, 577, 31 * 4, 6, World);

		setRTWall(3040, 705, 31 * 44, 6, World);
	}


	////////////////////////////////////////////////////////////////////////////////

	void setLevel4(b2World & World)
	{
		bglvl.loadFromFile("images/Levels/BGoflvl/sky1.jpg");
		sbglvl.setTexture(bglvl, false); sbglvl.setPosition(0, -300); sbglvl.setScale(2.5f, 2.5f);

		tlevel.loadFromFile("images/Levels/LEVEL4.png");

		slevel.setTexture(tlevel, false);


		// сглаживание
		tlevel.setSmooth(true);

		////////////   Stars   ///////////////
		tStar.loadFromFile("images/TileSet/hearts.png");
		tStar.setSmooth(true);

		numlvl = 4;

		sStar[0].setTexture(tStar);
		sStar[0].setScale(0.7f, 0.7f);
		sStar[0].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[0].setPosition(1160, 700);

		sStar[1].setTexture(tStar);
		sStar[1].setScale(0.7f, 0.7f);
		sStar[1].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[1].setPosition(1425, 660);

		sStar[2].setTexture(tStar);
		sStar[2].setScale(0.7f, 0.7f);
		sStar[2].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[2].setPosition(1880, 310);

		sStar[3].setTexture(tStar);
		sStar[3].setScale(0.7f, 0.7f);
		sStar[3].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[3].setPosition(2315, 680);

		sStar[4].setTexture(tStar);
		sStar[4].setScale(0.7f, 0.7f);
		sStar[4].setTextureRect(IntRect(490, 10, 60, 80));
		sStar[4].setPosition(3243, 670);

		/////////box2d///////////
		setRTWall(0, 801, 4640, 1000, World); // ground

		setRTWall(0, 0, 383, 1000, World); // leftwall
		setRTWall(3840, 0, 364, 1000, World); // rightwall

		setRTWall(512, 577, (800 - 512), 2, World); // platform 1
		setRTWall(992, 641, (1184 - 992), 2, World); // platform 2
		setRTWall(1152, 737, (1216 - 1152), 2, World); // platform 3
		setRTWall(1344, 737, (1504 - 1344), 2, World); // platform 4

		setRTWall(1568, 641, (1600 - 1568), 2, World); // platform 5
		setRTWall(1728, 545, 32, 2, World); // platform 6
		setRTWall(1600, 417, 32, 2, World); // platform 7
		setRTWall(1728, 353, 32, 2, World); // platform 8

		setRTWall(1856, 353, 32 * 3, 2, World); // platform 9
		setRTWall(2048, 577, 32 * 2, 2, World); // platform 10
		setRTWall(2208, 737, 32 * 5, 2, World); // platform 11
		setRTWall(2528, 705, 32 * 3, 2, World); // platform 12
		setRTWall(2816, 705, 32 * 30, 2, World); // platform 13
	}

	////////////////////////////////////////////////////////////////////////////////

	void setLevel5(b2World & World)
	{
		bglvl.loadFromFile("images/Levels/BGoflvl/sky1.jpg");
		sbglvl.setTexture(bglvl, false); sbglvl.setPosition(0, -300); sbglvl.setScale(2.5f, 2.5f);

		numlvl = 0;

		tlevel.loadFromFile("images/Levels/LEVEL5.png");

		slevel.setTexture(tlevel, false);


		// сглаживание
		tlevel.setSmooth(true);

		////////////   Stars   ///////////////
		// ЧЕМ БОЛЬШЕ СОБРАНО ЗВЁЗД НА ПРЕДЫДУЩИХ УРОВНЯХ, ТЕМ БОЛЬШЕ БОНУСОВ НА ПОСЛЕДНЕМ
		// В УРОВНЯХ ТАК ЖЕ ИМЕЮТСЯ БОНУСЫ

		/////////box2d///////////
		setRTWall(0, 801, 4640, 1000, World); // ground

		setRTWall(0, 0, 383, 1000, World); // leftwall
		setRTWall(3840, 0, 364, 1000, World); // rightwall



	}

	void Drawlvl(b2World & World)
	{
		//////////Draw/////////////// 
		window.draw(sbglvl);
		window.draw(slevel);
		switch (numlvl)
		{
		case 1: for (int i = 0; i < 5; i++) { if (Stars[i] == true)	window.draw(sStar[i]); }break;
		case 2: for (int i = 0; i < 5; i++) { if (Stars[i] == true)	window.draw(sStar[i]); } break;
		case 3: for (int i = 0; i < 5; i++) { if (Stars[i] == true)	window.draw(sStar[i]); } break;
		case 4: for (int i = 0; i < 5; i++) { if (Stars[i] == true)	window.draw(sStar[i]); } break;
		case 5: for (int i = 0; i < 5; i++) { if (Stars[i] == true)	window.draw(sStar[i]); } break;
		}

	}
};








// exemple of dymamiclevel
/*
void setLevel1(b2World & World)
{
t.loadFromFile("images/ground.png");
t2.loadFromFile("images/objects1.png");
t3.loadFromFile("images/objects2.png");
t4.loadFromFile("images/platform.png");
t5.loadFromFile("images/flag.png");
t6.loadFromFile("images/stars2wlp.jpg");

sGround.setTexture(t, false);
sBox.setTexture(t2, false);
sStone.setTexture(t2, false);
sSwing.setTexture(t3, false);
sPlatform.setTexture(t4, false);
sFlag.setTexture(t5, false);
sBackground.setTexture(t6, false);

// сглаживание
t2.setSmooth(true);


sBox.setTextureRect(IntRect(81, 0, 61, 61)); // позиция (left, top, ширина, высота)
sBox.setOrigin(30, 30);				// переносим точку отсчёта в центр картинки, т.к. по умолчанию в левом верхнем углу


sSwing.setTextureRect(IntRect(378, 0, 28, 242));
sSwing.setOrigin(20, 121);

sStone.setTextureRect(IntRect(0, 0, 80, 80));
sStone.setOrigin(40, 40);

sGround.setPosition(0, 320);
sFlag.setPosition(587, 19);

/////////box2d///////////
setWall(400, 490, 2000, 10, World);
setWall(400, 0, 2000, 1, World);
setWall(55, 438, 64, 60, World);
setWall(710, 435, 100, 60, World); // right ground
setWall(158, 224, 33, 10, World);
setWall(608, 114, 33, 10, World);
setWall(0, 0, 10, 2000, World); // left wall
setWall(795, 0, 10, 2000, World); // right wall

b2PolygonShape shape; // (Polygon - многоугольник)
shape.SetAsBox(30 / SCALE, 30 / SCALE); // => Размер ящика 60 на 60 пикселей!


b2BodyDef bdef; // Определение тела блока в world
bdef.type = b2_dynamicBody;

for (int i = 0; i<2; i++) {
bdef.position.Set(18, 10);
b2Body *body = World.CreateBody(&bdef); // Само тело
body->CreateFixture(&shape, 2);		// 2 параметр - ПЛОТНОСТЬ		// СОЗДАТЬ ПРИВЯЗКУ !!!
body->SetUserData("box");			// идентифицировать объект
}

bdef.position.Set(5, 14);
b2Body *body = World.CreateBody(&bdef);
body->CreateFixture(&shape, 2);
body->SetUserData("box");

///////////////////////
b2CircleShape circle;

/////////////////////////
bdef.position.Set(5, 2);
circle.m_radius = 40 / SCALE;
b2Body *b = World.CreateBody(&bdef);
b->CreateFixture(&circle, 8);
b->SetUserData("stone");

/////////////////////////
bdef.position.Set(11, 15);
bdef.angle = 90 * DEG;
b = World.CreateBody(&bdef);
shape.SetAsBox(5 / SCALE, 120 / SCALE);
b->CreateFixture(&shape, 1);
circle.m_radius = 2 / SCALE;
circle.m_p.Set(-20 / SCALE, 0);
b->CreateFixture(&circle, 1);
b->SetUserData("swing");




}
void Drawlvl1(b2World & World)
{
//////////Draw///////////////
window.draw(sBackground);
window.draw(sGround);
window.draw(sFlag);

sPlatform.setPosition(100, 200); window.draw(sPlatform);
sPlatform.setPosition(550, 90);	window.draw(sPlatform);

for (itlvl = World.GetBodyList(); itlvl != 0; itlvl = itlvl->GetNext()) // пробегаем по всем телам (GetBodyList())
{
poslvl = itlvl->GetPosition(); // Считываем позицию
anglelvl = itlvl->GetAngle();	// Считываем угол

if (itlvl->GetUserData() == "box") // Если тело - box
{
sBox.setPosition(poslvl.x*SCALE, poslvl.y*SCALE); // установка спрайту полученных параметров (позиция и угол)
sBox.setRotation(anglelvl*DEG);				// Умножаем на DEG для перевода в градусы
window.draw(sBox);							// отрисовка
}

if (itlvl->GetUserData() == "swing") // качели
{
sSwing.setPosition(poslvl.x*SCALE, poslvl.y*SCALE);
sSwing.setRotation(anglelvl*DEG);
window.draw(sSwing);
}

if (itlvl->GetUserData() == "stone")
{
sStone.setPosition(poslvl.x*SCALE, poslvl.y*SCALE);
sStone.setRotation(anglelvl*DEG);
window.draw(sStone);
}
}

}

*/
