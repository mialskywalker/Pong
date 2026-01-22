#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <vector>

int main()
{


	VideoMode vm(1920, 1080);

	RenderWindow window(vm, "Pong", Style::Fullscreen);
	int scorePlayer1 = 0;
	int scorePlayer2 = 0;

	Bat player1(1920 - 50, 1080 / 2);
	Bat player2(50, 1080 / 2);
	Ball ball(1920 / 2, 1080 / 2);

	Text hud;

	Font font;
	font.loadFromFile("fonts/DS-DIGIT.ttf");

	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(Color::White);
	hud.setPosition(20, 20);

	Clock clock;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();

		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();

		if (Keyboard::isKeyPressed(Keyboard::Up) && player1.getPosition().top > 0)
			player1.moveUp();
		else
			player1.stopUp();

		if (Keyboard::isKeyPressed(Keyboard::Down) && player1.getPosition().top < 1080 - 150)
			player1.moveDown();
		else
			player1.stopDown();

		if (Keyboard::isKeyPressed(Keyboard::W) && player2.getPosition().top > 0)
			player2.moveUp();
		else
			player2.stopUp();

		if (Keyboard::isKeyPressed(Keyboard::S) && player2.getPosition().top < 1080 - 150)
			player2.moveDown();
		else
			player2.stopDown();

		Time dt = clock.restart();
		player1.update(dt);
		player2.update(dt);
		ball.update(dt);

		std::stringstream ss;
		ss << "                       Score: " << scorePlayer1 << "                                Score:" << scorePlayer2;
		hud.setString(ss.str());


		if (ball.getPosition().left > window.getSize().x)
		{
			ball.reboundSide();
			scorePlayer1++;
		}

		if (ball.getPosition().left < 0)
		{
			ball.reboundSide();
			scorePlayer2++;
		}

		if (ball.getPosition().intersects(player1.getPosition()) || ball.getPosition().intersects(player2.getPosition()))
		{
			ball.reboundBat();
		}

		if (ball.getPosition().top < 0 || ball.getPosition().top + ball.getPosition().height > window.getSize().y)
		{
			ball.reboundTopOrBottom();
		}

		window.clear();
		window.draw(hud);
		window.draw(player1.getShape());
		window.draw(player2.getShape());
		window.draw(ball.getShape());
		window.display();
	}

	return 0;
}