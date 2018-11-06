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

int screenw = 800;
int screenh = 600;
int scoreLeft = 0, scoreRight = 0;
string scoreLefttext, scoreRighttext, printscore;
bool isWon = false;

int main()
{
	srand(time(0));
	ball ball;
	paddle pad1, pad2;
	float ax, ay;
	do {
		ax = rand() % screenw - (screenw / 2);
		ay = rand() % screenh - (screenh / 2);
	} while (ax * ax < ay * ay);
	float angle = atan2f(ay, ax);
	float speed = 0.3;
	float radius = 30;
	int countwin = 0;
	int count = 0;
	Texture slugleft;
	slugleft.loadFromFile("slugleft.png");
	Texture slugright;
	slugright.loadFromFile("slugright.png");
	Texture shell;
	shell.loadFromFile("shell.png");
	RenderWindow window(VideoMode(screenw, screenh), "Slugs and Shell");
	RectangleShape middle;
	middle.setSize(Vector2f(3.f, screenh));
	middle.setPosition(Vector2f(((screenw - 3) / 2), 0));
	window.draw(ball.SpawnBall(screenw, screenh, radius, shell));
	Font font;
	font.loadFromFile("arial.ttf");
	Text score;
	score.setFont(font);
	score.setCharacterSize(48);
	score.setString("0  0");
	score.setPosition(screenw / 2 - 40, 0);
	score.setFillColor(Color::Cyan);
	float rotateAngle = 0;
	
	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();
		}
		isWon = false;
		if (rotateAngle != 360)
			rotateAngle += 5;
		else
			rotateAngle = 0;
		window.clear();
		window.draw(middle);
		window.draw(score);
		window.draw(ball.PrintBall(shell, rotateAngle));
		window.draw(pad1.SpawnPads(screenw, screenh, 45, 128, true, slugleft, slugright));
		window.draw(pad2.SpawnPads(screenw, screenh, 45, 128, false, slugleft, slugright));
		window.display();
		pad1.PlayerControl(screenh);
		pad2.AIMove(screenh, ball.pos.y, ball.radius);
		if (ball.BouncePaddle(pad1, screenw) || ball.BouncePaddle(pad2, screenw)) {
			ax = -ax;
			speed += 0.02;
		}
		if (ball.BounceWall(screenh))
			ay = -ay;
		angle = atan2f(ay, ax);
		count++;
		if(count >= 1000)
			ball.MoveBall(ball.pos, angle, speed, screenh);
		if (ball.pos.x <= ball.radius * (-2)) {
			scoreRight++;
			ball.pos.x = screenw / 2 - radius;
			ball.pos.y = screenh / 2 - radius;
			do {
				ax = rand() % screenw - (screenw / 2);
				ay = rand() % screenh - (screenh / 2);
			} while (ax * ax < ay * ay);
			angle = atan2f(ay, ax);
			speed = 0.3;
			count = 0;
		}
		if (ball.pos.x >= screenw) {
			scoreLeft++;
			ball.pos.x = screenw / 2 - radius;
			ball.pos.y = screenh / 2 - radius;
			do {
				ax = rand() % screenw - (screenw / 2);
				ay = rand() % screenh - (screenh / 2);
			} while (ax * ax < ay * ay);
			angle = atan2f(ay, ax);
			speed = 0.3;
			count = 0;
		}
		Text win;
		win.setFont(font);
		win.setCharacterSize(24);
		win.setPosition(60, 10);
		win.setFillColor(Color::Yellow);
		Text restart;
		restart.setFont(font);
		restart.setCharacterSize(24);
		restart.setPosition(10, 60);
		restart.setFillColor(Color::Yellow);
		restart.setString("Press Space to Restart...");
		if (scoreLeft == 5) {
			win.setString("Player One won!");
			isWon = true;
		}
		else if (scoreRight == 5) {
			win.setString("Player Two won!");
			isWon = true;
		}
		if (isWon) {
			scoreLeft = 0;
			scoreRight = 0;
			ball.pos.x = screenw / 2 - radius;
			ball.pos.y = screenh / 2 - radius;
			do {
				ax = rand() % screenw - (screenw / 2);
				ay = rand() % screenh - (screenh / 2);
			} while (ax * ax < ay * ay);
			angle = atan2f(ay, ax);
			speed = 0.3;
			count = 0;
			RenderWindow message(VideoMode(300, 100), "Winner");

			while (message.isOpen()) {
				Event eventm;
				while (message.pollEvent(eventm)) {
					if (Keyboard::isKeyPressed(Keyboard::Space) || eventm.type == Event::Closed)
						message.close();
				}
				message.clear();
				message.draw(win);
				message.draw(restart);
				message.display();
			}
			
		}
		scoreLefttext = toString<int>(scoreLeft);
		scoreRighttext = toString<int>(scoreRight);
		printscore = scoreLefttext + "  " + scoreRighttext;
		score.setString(printscore);
	}
	return 0;
}