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

using namespace std;

int main()
{
	int screenw = 800;
	int screenh = 600;
	sf::RenderWindow window(sf::VideoMode(screenw, screenh), "Yitong's Pong");
	sf::RectangleShape middle;
	middle.setSize(sf::Vector2f(3.f, screenh));
	middle.setPosition(sf::Vector2f(((screenw - 3) / 2), 0));
	ball ball;
	paddle pad1, pad2;
	

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		pad1.PlayerControl(screenh);
		window.clear();
		window.draw(middle);
		window.draw(ball.SpawnBall(screenw, screenh, 20));
		window.draw(pad1.SpawnPads(screenw, screenh, 20, 120, true));
		window.draw(pad2.SpawnPads(screenw, screenh, 20, 120, false));
		window.display();
	}

	return 0;
}
/*
void PlayerControl() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		move -=
	}
}*/