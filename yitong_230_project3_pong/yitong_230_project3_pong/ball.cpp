#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "ball.h"

sf::CircleShape ball::SpawnBall(int screenw, int screenh, int radius) {
	this->x = screenw / 2 - radius;
	this->y = screenh / 2 - radius;
	this->radius = radius;
	sf::CircleShape shape(this->radius);
	shape.setPosition(sf::Vector2f(this->x, this->y));
	return shape;
}
