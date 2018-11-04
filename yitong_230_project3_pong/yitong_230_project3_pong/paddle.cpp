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

sf::RectangleShape paddle::SpawnPads(int screenw, int screenh, float width, float length, bool isLeft) {
	if (isLeft)
		x = 0;
	else 
		x = screenw - width;
	y = (screenh - length) / 2 + move;
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(width, length));
	shape.setPosition(sf::Vector2f(x, y));
	this->length = length;
	return shape;
}

void paddle::PlayerControl(int screenh) {
	//if (y >= 0 && (y + length) <= screenh) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (move >= ((length - screenh) / 2))
				move -= speed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (move <= ((screenh - length) / 2))
				move += speed;
		}
	//}
}

void paddle::AIMove(int screenh, float bally, float radius) {
	//if (y >= 0 && (y + length) <= screenh) {
		if ((y + length) < (bally + radius))
			move += speed;
		else if (y > (bally + radius))
			move -= speed;
	//}
}
