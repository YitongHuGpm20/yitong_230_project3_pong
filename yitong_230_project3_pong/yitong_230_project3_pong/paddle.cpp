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

RectangleShape paddle::SpawnPads(int screenw, int screenh, float width, float length, bool isLeft, Texture &slugleft, Texture &slugright, int gameMode, bool isSecondLeft) {
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
	if(gameMode == 3 && !isSecondLeft)
		y = (screenh - length) / 4 + move;
	else if(gameMode == 3 && isSecondLeft)
		y = (screenh - length) / 4 * 3 + move;
	else if(gameMode == 1 || gameMode == 2)
		y = (screenh - length) / 2 + move;
	this->length = length;
	this->width = width;
	return shape;
}

RectangleShape paddle::SpawnObstacle(int screenw) {
	RectangleShape shape;
	width = 20;
	length = 120;
	shape.setSize(Vector2f(width, length));
	x = (screenw - width) / 2;
	y = move;
	shape.setPosition(Vector2f(x, y));
	shape.setFillColor(Color::Magenta);
	return shape;
}

void paddle::MoveObstacle() {
	if (!obsUp)
		move += 0.1;
	else
		move -= 0.1;
}

void paddle::PlayerControl(int screenh, bool isLeft, int gameMode) {
	if (gameMode == 1 || gameMode == 2) {
		if (isLeft) {
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				if (y >= 0)
					move -= speed;
			}
			else if (Keyboard::isKeyPressed(Keyboard::S)) {
				if (y + length <= screenh)
					move += speed;
			}
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				if (y >= 0)
					move -= speed;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down)) {
				if (y + length <= screenh)
					move += speed;
			}
		}
	}
	else if (gameMode == 3) {
		if (isLeft) {
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				if (y >= 0)
					move -= speed;
			}
			else if (Keyboard::isKeyPressed(Keyboard::S)) {
				if (y + length <= screenh / 2)
					move += speed;
			}
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				if (y >= screenh / 2)
					move -= speed;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down)) {
				if (y + length <= screenh)
					move += speed;
			}
		}
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
