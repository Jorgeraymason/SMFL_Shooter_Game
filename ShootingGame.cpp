#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

int main() {
	RenderWindow window(VideoMode(640, 480), "JRGRYMSN SHOOTER");
	window.setFramerateLimit(60);

	//Initialzes points variable
	int points = 0;
	int misses;
	float hoopSpeed = 10.f;
	float ballSpeed = -5.f;

	CircleShape hoop;
	int dir = 0;
	hoop.setRadius(50.f);
	hoop.setFillColor(Color::Black);
	hoop.setOutlineThickness(2.f);
	hoop.setOutlineColor(Color::Blue);
	hoop.setPosition(Vector2f(0, 10.f));

	CircleShape ball;
	bool isShot = false;
	ball.setRadius(20.f);
	ball.setFillColor(Color::Magenta);
	ball.setPosition(Vector2f(0, window.getSize().y - ball.getRadius() * 3));

	while (window.isOpen())
	{

		Font font;
		if (!font.loadFromFile("Comic-Sans-MS.ttf"))
			return EXIT_FAILURE;

		Text text("Points: ", font, 50);
		text.setPosition(-3.f, 5.f);
		text.setFillColor(Color::Blue);

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
		}

		//Update
		if (hoop.getPosition().x <= 0)
			dir = 1;
		else if(hoop.getPosition().x + hoop.getRadius() >= window.getSize().x)
			dir = 0;

		if (dir == 0)
		{
			hoop.move(-hoopSpeed, 0);
		}
		else
		{
			hoop.move(hoopSpeed, 0);
		}

		//Update ball shot
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			isShot = true;
		}

		if(!isShot)
			ball.setPosition(Mouse::getPosition(window).x, ball.getPosition().y);
		else
			ball.move(0, ballSpeed);

		//Collision ball
		if (ball.getPosition().y <= 0 || ball.getGlobalBounds().intersects(hoop.getGlobalBounds()))
		{

			if (ball.getGlobalBounds().intersects(hoop.getGlobalBounds()))
			{
				points += 1; // Increase points by 10 when the ball collides with the hoop

				misses = 0;

				hoopSpeed += 1.f;

				ballSpeed -= 1.f;
			}
			else
			{
				misses = 1;

				if (misses <= 1)
				{
					points = 0;

					hoopSpeed = 10.f;

					ballSpeed = -5.f;
				}
			}

			//Resets ball position
			isShot = false;
			ball.setPosition(ball.getPosition().x, window.getSize().y - ball.getRadius() * 3);
		}

		window.clear(Color::White);

		// Update points text
		text.setString("Points: " + std::to_string(points));

		//Draw
		window.draw(hoop);

		window.draw(text);

		window.draw(ball);

		window.display();	
	}

	return 0;
}