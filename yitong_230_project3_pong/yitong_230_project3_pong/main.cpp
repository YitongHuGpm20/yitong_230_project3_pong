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

using namespace std;

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
	
	sf::RenderWindow window(sf::VideoMode(screenw, screenh), "Yitong's Pong");
	sf::RectangleShape middle;
	middle.setSize(sf::Vector2f(3.f, screenh));
	middle.setPosition(sf::Vector2f(((screenw - 3) / 2), 0));
	window.draw(ball.SpawnBall(screenw, screenh, 20));
	
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
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
		ball.StartBall(ball.pos, angle, 0.3, screenh);
	}

	return 0;
}