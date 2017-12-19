#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "SFML\Audio.hpp"

bool access[5] = { true, false, false, false, false };

bool Stars[5] = { true, true, true, true, true };
bool soundStars[5] = { true, true, true, true, true };

bool fromSLMtoMM = false;

bool soundBonusOff = false;

int bonuses = 0;  bool slowmo = false; int power = 0;

bool hearts[3] = { true,true,true }; int numh = 0;
bool heart1 = true, heart2 = true, heart3 = true;


int nlvl = 0; int toMainMenuisone = 0;

bool Restart = false;

int toNextLvl = 0;

bool SelectLvl = true;
bool exfromGame = true;


const float SCALE = 30.f; // для масштабирования (по умолчанию счёт в метрах => переводим в пиксели)
const float DEG = 57.29577f; // для перевода из радиант в градусы

using namespace sf;

void setWall(int x, int y, int w, int h, b2World & World)
{
	b2PolygonShape gr; // Многоугольник 
	gr.SetAsBox(w / SCALE, h / SCALE);

	b2BodyDef bdef; // Создание тела
	bdef.position.Set(x / SCALE, y / SCALE);

	b2Body *b_ground = World.CreateBody(&bdef); // Само тело, отображаемое в мире
	b_ground->CreateFixture(&gr, 1); // прикрепляем форму(shape)
}


// Установка статического обьекта
void setRTWall(int x, int y, int w, int h, b2World & World)
{
	x = x + (w / 2) + 1;
	y = y + 11 + h;
	w = w / 2;
	h = h + 10;


	b2PolygonShape gr; // Многоугольник 
	gr.SetAsBox(w / SCALE, h / SCALE);

	b2BodyDef bdef; // Создание тела
	bdef.position.Set(x / SCALE, y / SCALE);

	b2Body *b_ground = World.CreateBody(&bdef); // Само тело, отображаемое в мире
	b_ground->CreateFixture(&gr, 1); // прикрепляем форму(shape)
}