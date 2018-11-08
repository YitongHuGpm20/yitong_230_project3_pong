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
	paddle pad1, pad2, pad3, obstacle;
	float ax, ay;
	do {
		ax = rand() % screenw - (screenw / 2);
		ay = rand() % screenh - (screenh / 2);
	} while (ax * ax <= ay * ay && (ay * ay <= 202500 || ay * ay >= 22500));
	float angle = atan2f(ay, ax);
	float speed = 0.3;
	float radius = 30;
	int countwin = 0;
	int count = 0;
	float rotateAngle = 0;
	Clock clock;
	
	Texture slugleft;
	slugleft.loadFromFile("slugleft.png");
	Texture slugleftmove;
	slugleftmove.loadFromFile("slugleftmove.png");
	Texture slugright;
	slugright.loadFromFile("slugright.png");
	Texture slugrightmove;
	slugrightmove.loadFromFile("slugrightmove.png");
	Texture shell;
	shell.loadFromFile("shell.png");
	Texture background;
	background.loadFromFile("forest.jpg");
	Texture wood;
	wood.loadFromFile("wood.jpg");
	
	RenderWindow window(VideoMode(screenw, screenh), "Slugs and Shell");
	window.draw(ball.SpawnBall(screenw, screenh, radius, shell));
	RectangleShape forest;
	forest.setTexture(&background);
	forest.setSize(Vector2f(screenw, screenh));
	forest.setPosition(Vector2f(0, 0));
	//CircleShape powerup(20);
	//powerup.setFillColor(Color::Green);
	
	Font font;
	font.loadFromFile("arial.ttf");
	Text score;
	score.setFont(font);
	score.setCharacterSize(48);
	score.setString("0  0");
	score.setPosition(screenw / 2 - 40, 0);
	score.setFillColor(Color::Cyan);
	Text timer;
	timer.setFont(font);
	timer.setCharacterSize(72);
	timer.setPosition(screenw / 2, 30);
	timer.setOutlineColor(Color::Magenta);
	timer.setFillColor(Color::Red);
	
	SoundBuffer bounce;
	bounce.loadFromFile("bounce.wav");
	Sound bouncese;
	bouncese.setBuffer(bounce);
	SoundBuffer bouncewall;
	bouncewall.loadFromFile("bouncewall.wav");
	Sound wall;
	wall.setBuffer(bouncewall);
	Music bgm;
	bgm.openFromFile("bgm.ogg");
	bgm.setLoop(true);
	bgm.play();
	SoundBuffer glass;
	glass.loadFromFile("score.wav");
	Sound getscore;
	getscore.setBuffer(glass);
	SoundBuffer clap;
	clap.loadFromFile("win.wav");
	Sound winsound;
	winsound.setBuffer(clap);
	
	Text select;
	select.setFont(font);
	select.setCharacterSize(24);
	select.setPosition(10, 10);
	select.setFillColor(Color::Yellow);
	select.setString("Input Numbers to Select:");
	Text pve;
	pve.setFont(font);
	pve.setCharacterSize(24);
	pve.setPosition(10, 60);
	pve.setFillColor(Color::Yellow);
	pve.setString("1. PVE");
	Text pvp;
	pvp.setFont(font);
	pvp.setCharacterSize(24);
	pvp.setPosition(10, 110);
	pvp.setFillColor(Color::Yellow);
	pvp.setString("2. PVP");
	Text ppve;
	ppve.setFont(font);
	ppve.setCharacterSize(24);
	ppve.setPosition(10, 160);
	ppve.setFillColor(Color::Yellow);
	ppve.setString("3. 2PVE");
	int gameMode = 0;
	RenderWindow menu(VideoMode(400, 300), "Main Menu");
	while (menu.isOpen()) {
		Event eventc;
		while (menu.pollEvent(eventc)) {
			if (Keyboard::isKeyPressed(Keyboard::Num1)) {
				gameMode = 1;
				menu.close();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num2)) {
				gameMode = 2;
				menu.close();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num3)) {
				gameMode = 3;
				menu.close();
			}
		}
		menu.clear();
		menu.draw(select);
		menu.draw(pve);
		menu.draw(pvp);
		menu.draw(ppve);
		menu.display();
	}
	
	if (gameMode == 1 || gameMode == 2)
		window.draw(pad1.SpawnPads(screenw, screenh, 45, 128, true, slugleft, slugright, gameMode, false));
	else if (gameMode == 3) {
		window.draw(pad1.SpawnPads(screenw, screenh, 45, 128, true, slugleft, slugright, gameMode, false));
		window.draw(pad3.SpawnPads(screenw, screenh, 45, 128, true, slugleft, slugright, gameMode, true));
	}
	window.draw(pad2.SpawnPads(screenw, screenh, 45, 128, false, slugleft, slugright, gameMode, false));
	float dt = clock.restart().asSeconds();
	
	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();
		}
		isWon = false;
		//float dt = clock.restart().asSeconds();
		/*if (rotateAngle != 360)
			rotateAngle += 1;
		else
			rotateAngle = 0;*/
		window.clear();
		window.draw(forest);
		window.draw(score);
		window.draw(ball.PrintBall(shell, rotateAngle));
		window.draw(obstacle.SpawnObstacle(screenw, wood));
		if(gameMode == 1 || gameMode == 2)
			window.draw(pad1.PrintPads(screenw, screenh, true, slugleft, slugright, gameMode, false));
		else if (gameMode == 3) {
			window.draw(pad1.PrintPads(screenw, screenh, true, slugleft, slugright, gameMode, false));
			window.draw(pad3.PrintPads(screenw, screenh, true, slugleft, slugright, gameMode, true));
		}
		window.draw(pad2.PrintPads(screenw, screenh, false, slugleft, slugright, gameMode, false));
		window.display();
		pad1.PlayerControl(screenh, true, gameMode, dt);
		if (gameMode == 1)
			pad2.AIMove(screenh, ball.pos.y, ball.radius, gameMode, dt);
		else if (gameMode == 2)
			pad2.PlayerControl(screenh, false, gameMode, dt);
		else if (gameMode == 3) {
			pad2.AIMove(screenh, ball.pos.y, ball.radius, gameMode, dt);
			pad3.PlayerControl(screenh, false, gameMode, dt);
		}
		if (ball.BouncePaddle(obstacle, screenw)) {
			if ((ball.center.x <= screenw / 2 && ax >= 0) || (ball.center.x > screenw / 2 && ax < 0)) {
				ax = -ax;
				bouncese.play();
			}
		}
		else if (ball.BouncePaddle(pad1, screenw) && ax < 0) {
			ax = -ax;
			speed += 0.02;
			bouncese.play();
		}
		else if (ball.BouncePaddle(pad2, screenw) && ax >= 0) {
			ax = -ax;
			speed += 0.02;
			bouncese.play();
		}
		if (gameMode == 3) {
			if (ball.BouncePaddle(pad3, screenw) && ax < 0) {
				ax = -ax;
				speed += 0.02;
				bouncese.play();
			}
		}
		if (ball.BounceWall(screenh)) {
			ay = -ay;
			wall.play();
		}
		angle = atan2f(ay, ax);
		count++;
		if(count >= 1000)
			ball.MoveBall(ball.pos, angle, speed, screenh, dt);
		if (ball.pos.x <= ball.radius * (-2)) {
			scoreRight++;
			getscore.play();
			ball.pos.x = screenw / 2 - radius;
			ball.pos.y = screenh / 2 - radius;
			do {
				ax = rand() % screenw - (screenw / 2);
				ay = rand() % screenh - (screenh / 2);
			} while (ax * ax < ay * ay);
			angle = atan2f(ay, ax);
			speed = 0.3;
			count = 0;
			obstacle.x = (screenw - obstacle.width) / 2;
			obstacle.move = 0;
		}
		if (ball.pos.x >= screenw) {
			scoreLeft++;
			getscore.play();
			ball.pos.x = screenw / 2 - radius;
			ball.pos.y = screenh / 2 - radius;
			do {
				ax = rand() % screenw - (screenw / 2);
				ay = rand() % screenh - (screenh / 2);
			} while (ax * ax < ay * ay);
			angle = atan2f(ay, ax);
			speed = 0.3;
			count = 0;
			obstacle.x = (screenw - obstacle.width) / 2;
			obstacle.move = 0;
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
			winsound.play();
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
					if (Keyboard::isKeyPressed(Keyboard::Space))
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
		if (count >= 1000) {
			if (obstacle.y >= screenh - 120) {
				obstacle.obsUp = true;
			}
			else if (obstacle.y <= 0) {
				obstacle.obsUp = false;
			}
			obstacle.MoveObstacle(dt);
		}
	}
	return 0;
}