#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#pragma once

class ball
{
public:
	int x;
	int y;
	int speed;
	sf::Vector2f direction;
	int radius;

	sf::CircleShape SpawnBall(int, int, int);
};

