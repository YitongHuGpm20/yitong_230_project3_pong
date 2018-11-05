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

using namespace std;
using namespace sf;

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
	
	RenderWindow window(VideoMode(screenw, screenh), "Yitong's Pong");
	RectangleShape middle;
	middle.setSize(Vector2f(3.f, screenh));
	middle.setPosition(Vector2f(((screenw - 3) / 2), 0));
	window.draw(ball.SpawnBall(screenw, screenh, radius));
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
		window.draw(ball.PrintBall());
		window.draw(pad1.SpawnPads(screenw, screenh, 20, 120, true));
		window.draw(pad2.SpawnPads(screenw, screenh, 20, 120, false));
		window.display();
		pad1.PlayerControl(screenh);
		pad2.AIMove(screenh, ball.pos.y, ball.radius);
		if (ball.BouncePaddle(pad1) || ball.BouncePaddle(pad2)) {
			ax = -ax;
			speed += 0.01;
		}
		angle = atan2f(ay, ax);
		ball.MoveBall(ball.pos, angle, speed, screenh);
	}

	return 0;
}