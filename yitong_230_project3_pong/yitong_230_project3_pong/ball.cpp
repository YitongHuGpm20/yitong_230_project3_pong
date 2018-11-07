#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "ball.h"
#include "paddle.h"
#include <algorithm>

using namespace sf;

float length(Vector2f v) {return sqrtf(v.x*v.x + v.y*v.y);}
float clamp(float value, float min, float max) {
	if (value < min)
		return min;
	if (value > max)
		return max;
	else
		return value;
}

CircleShape ball::SpawnBall(int screenw, int screenh, float radius, Texture &shell) {
	pos.x = screenw / 2 - radius;
	pos.y = screenh / 2 - radius;
	this->radius = radius;
	center.x = pos.x + radius;
	center.y = pos.y + radius;
	CircleShape shape(this->radius);
	shape.setPosition(Vector2f(pos));
	shape.setTexture(&shell);
	return shape;
}

CircleShape ball::PrintBall(Texture &shell, float angle) {
	center.x = pos.x + radius;
	center.y = pos.y + radius;
	CircleShape shape(radius);
	shape.setPosition(Vector2f(pos));
	shape.setTexture(&shell);
	//shape.setOrigin(pos.x + radius, pos.y + radius);
	//shape.setRotation(angle);
	return shape;
}

void ball::MoveBall(Vector2f& point, float angle, float dist, int screenh) {
	Vector2f dir(cosf(angle),sinf(angle));
	point += dir * dist;
	//pos = point;
}

bool ball::BouncePaddle(paddle pad, int screenw) {
	float closestX;
	if(pos.x < screenw / 2)
		closestX = clamp(center.x, pad.x, pad.x + pad.width - 30);
	else
		closestX = clamp(center.x, pad.x + 30, pad.x + pad.width);
	float closestY = clamp(center.y, pad.y, pad.y + pad.length);
	float distanceX = center.x - closestX;
	float distanceY = center.y - closestY;
	float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
	return distanceSquared < (radius * radius);
}

bool ball::BounceWall(int screenh) {
	if (pos.y <= 0 || pos.y + (2 * radius) >= screenh)
		return true;
	else
		return false;
}