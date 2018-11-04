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
	//float x, y;
	float speed;
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Vector2f dir;
	float radius;

	sf::CircleShape SpawnBall(int, int, float);
	sf::CircleShape PrintBall();
	void StartBall(sf::Vector2f &, float, float, int);
};

