#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "paddle.h"
#include <ctime>

using namespace std;
using namespace sf;

RectangleShape paddle::SpawnPads(int screenw, int screenh, float width, float length, bool isLeft, Texture &slugleft, Texture &slugright) {
	RectangleShape shape;
	shape.setSize(Vector2f(width, length));
	shape.setPosition(Vector2f(x, y));
	if (isLeft) {
		x = 0;
		shape.setTexture(&slugleft);
	}	
	else {
		x = screenw - width;
		shape.setTexture(&slugright);
	}
	y = (screenh - length) / 2 + move;
	this->length = length;
	this->width = width;
	return shape;
}

void paddle::PlayerControl(int screenh) {
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		if (move >= ((length - screenh) / 2))
			move -= speed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S)) {
		if (move <= ((screenh - length) / 2))
			move += speed;
	}
}

void paddle::AIMove(int screenh, float bally, float radius) {
	srand(time(0));
	float miss = rand() % 40;
	if (y + length + miss < bally + radius && move <= (screenh - length) / 2)
		move += speed;
	else if (y - miss > bally + radius && move >= (length - screenh) / 2)
		move -= speed;
}
