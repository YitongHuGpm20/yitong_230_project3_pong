#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "ball.h"
#include "paddle.h"
#include <ctime>
#include <chrono>
#include <thread>
#include <string>
#include <sstream>

using namespace std;
using namespace sf;

template <typename T>
string toString(T arg){
	stringstream ss;
	ss << arg;
	return ss.str();
}

int main()
{
	srand(time(0));
	int screenw = 800;
	int screenh = 600;
	ball ball;
	paddle pad1, pad2;
	float ax = rand() % screenw - (screenw / 2);
	float ay = rand() % screenh - (screenh / 2);
	float angle = atan2f(ay, ax);
	float speed = 0.3;
	float radius = 20;
	int scoreLeft = 0, scoreRight = 0;
	string scoreLefttext, scoreRighttext, printscore;

	RenderWindow window(VideoMode(screenw, screenh), "Yitong's Pong");
	RectangleShape middle;
	middle.setSize(Vector2f(3.f, screenh));
	middle.setPosition(Vector2f(((screenw - 3) / 2), 0));
	window.draw(ball.SpawnBall(screenw, screenh, radius));
	Font font;
	font.loadFromFile("arial.ttf");
	Text score;
	score.setFont(font);
	score.setCharacterSize(48);
	score.setString("0  0");
	score.setPosition(screenw / 2 - 40, 0);
	score.setFillColor(Color::Cyan);
	//chrono::seconds dura(5);
	//this_thread::sleep_for(dura);
	
	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(middle);
		window.draw(score);
		window.draw(ball.PrintBall());
		window.draw(pad1.SpawnPads(screenw, screenh, 20, 120, true));
		window.draw(pad2.SpawnPads(screenw, screenh, 20, 120, false));
		window.display();
		pad1.PlayerControl(screenh);
		pad2.AIMove(screenh, ball.pos.y, ball.radius);
		if (ball.BouncePaddle(pad1) || ball.BouncePaddle(pad2)) {
			ax = -ax;
			speed += 0.02;
		}
		if (ball.BounceWall(screenh))
			ay = -ay;
		angle = atan2f(ay, ax);
		ball.MoveBall(ball.pos, angle, speed, screenh);
		if (ball.pos.x <= ball.radius * (-2)) {
			scoreRight++;
			ball.pos.x = screenw / 2 - radius;
			ball.pos.y = screenh / 2 - radius;
			ax = rand() % screenw - (screenw / 2);
			ay = rand() % screenh - (screenh / 2);
			angle = atan2f(ay, ax);
			speed = 0.3;
		}
		if (ball.pos.x >= screenw) {
			scoreLeft++;
			ball.pos.x = screenw / 2 - radius;
			ball.pos.y = screenh / 2 - radius;
			ax = rand() % screenw - (screenw / 2);
			ay = rand() % screenh - (screenh / 2);
			angle = atan2f(ay, ax);
			speed = 0.3;
		}
		scoreLefttext = toString<int>(scoreLeft);
		scoreRighttext = toString<int>(scoreRight);
		printscore = scoreLefttext + "  " + scoreRighttext;
		score.setString(printscore);
	}
	return 0;
}