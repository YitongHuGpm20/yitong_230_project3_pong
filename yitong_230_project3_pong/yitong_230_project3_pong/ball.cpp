#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "ball.h"

sf::CircleShape ball::SpawnBall(int screenw, int screenh, float radius) {
	pos.x = screenw / 2 - radius;
	pos.y = screenh / 2 - radius;
	this->radius = radius;
	sf::CircleShape shape(this->radius);
	shape.setPosition(sf::Vector2f(pos));
	return shape;
}

sf::CircleShape ball::PrintBall() {
	sf::CircleShape shape(this->radius);
	shape.setPosition(sf::Vector2f(pos));
	return shape;
}

void ball::StartBall(sf::Vector2f& point, float angle, float dist, int screenh) {
	//sf::Vector2f dir(ax, ay);
	sf::Vector2f dir(cosf(angle),sinf(angle));
	if (pos.y >= 0 && (pos.y + (2 * radius)) <= screenh)
		point += dir * dist;
}