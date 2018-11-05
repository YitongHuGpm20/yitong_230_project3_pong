#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#pragma once

class paddle
{
public:
	float x;
	float y;
	float length;
	float width;
	float speed = 0.5;
	float move = 0;

	sf::RectangleShape SpawnPads(int, int, float, float, bool);
	void PlayerControl(int);
	void AIMove(int, float, float);
};

