#pragma once
#include "Constants.h"

View view;


void getplayercoordinateforview(float x, float y) { // для считывания координат игрока

	view.setCenter(x + 100, y); // передавая его координаты камере. 
}