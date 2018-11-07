#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#pragma once

using namespace sf;

class paddle
{
public:
	float x;
	float y;
	float length;
	float width;
	float speed = 0.5;
	float move = 0;
	bool obsUp = false;

	RectangleShape SpawnPads(int, int, float, float, bool, Texture&, Texture&, int, bool);
	RectangleShape SpawnObstacle(int, Texture&);
	void MoveObstacle();
	void PlayerControl(int, bool, int);
	void AIMove(int, float, float, int);
};

