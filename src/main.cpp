//
// Created by Ryan Cullen May 11, 2022
//
// 
// Gravity simulation between two moon-like objects
//
//
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "planet.hpp"

const float GRAVCONST = 6.67430e-11;

sf::Vector2f accGrav(Planet &first, Planet &second);
float distanceApart(sf::Vector2f, sf::Vector2f, int, int, float *);

// Main game loop and initialization
int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWWIDTH), "Gravity Simulation!", sf::Style::Default, settings);
	window.setFramerateLimit(10);
	sf::Event event;
	sf::Sprite background;
	sf::Texture backTexture;
	sf::Vector2f gravity;
	int radiusSum, dist;
	bool isCollided = false;

	Planet planet1(100, true), planet2(30, false);

	// Load background image
	if (!backTexture.loadFromFile("resource/starry_sky.png"))
		return 1;
	background.setTexture(backTexture);
	background.setColor(sf::Color(150, 150, 150)); // darken background image
	
	// Game loop
	while (window.isOpen())
	{
		// Event handling
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed :
					window.close();
					break;
				default :
					break;
			}

		}
		// Update sprite postions
		if (!isCollided)
		{
			gravity = accGrav(planet1, planet2);
			planet2.updatePosition(-1.f * gravity);
		}

		// Check for planet collisions
		float unimportant = 0.f;
		float *skip = &unimportant;
		radiusSum = abs(planet1.m_Shape.getRadius()) + abs(planet2.m_Shape.getRadius());
		dist = distanceApart(planet1.m_Shape.getPosition(), planet2.m_Shape.getPosition(), planet1.m_Shape.getRadius(), planet2.m_Shape.getRadius(), skip);
		if (radiusSum > dist)
		{
			// BOOM!!
			isCollided = true;
		}

		// Draw window and sprites
		window.clear();

		window.draw(background);
		window.draw(planet1.m_Shape);
		window.draw(planet2.m_Shape);

		window.display();
	}
	
	return 0;
}

// Calculate acceleration due to gravity using a = G(m1*m2)/r^2
sf::Vector2f accGrav(Planet &first, Planet &second)
{
	sf::Vector2f acceleration;
	float magnitude, direction, accX, accY;
	
	// calculate distance between two points (components)
	float radius1 = first.m_Shape.getRadius(), radius2 = second.m_Shape.getRadius();
	float r = distanceApart(first.m_Shape.getPosition(), second.m_Shape.getPosition(), radius1, radius2, &direction) * 10000.f;
	
	// calculate acceleration due to gravity using Newton's law of universal gravitation
	magnitude = GRAVCONST * ((first.m_Mass * second.m_Mass) / (r * r));

	// convert magnitude back to components
	accX = cos(direction) * magnitude;
	accY = sin(direction) * magnitude;

	acceleration = sf::Vector2f(accX, accY);
	std::cout << "Gravity: x = " << accX << ", y = " << accY << '\n';
	return acceleration;
}

// Calculate distance between two points
float distanceApart(sf::Vector2f first, sf::Vector2f second, int radius1, int radius2, float *direction)
{
	float x1 = first.x - radius1, x2 = second.x - radius2;
	float deltaX = (x2 - x1);
	float y1 = first.y - radius1, y2 = second.y - radius2;
	float deltaY = (y2 - y1);

	// calculate direction
	*direction = atan(deltaY / deltaX);

	return sqrt((deltaY * deltaY) + (deltaX * deltaX));
}





