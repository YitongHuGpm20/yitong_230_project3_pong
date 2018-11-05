#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "paddle.h"
#pragma once

using namespace sf;

class ball
{
public:
	Vector2f pos;
	Vector2f dir;
	Vector2f center;
	float radius;

	CircleShape SpawnBall(int, int, float);
	CircleShape PrintBall();
	void MoveBall(Vector2f &, float, float, int);
	bool BouncePaddle(paddle);
	bool BounceWall(int);
};

