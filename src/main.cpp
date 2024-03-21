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

sf::Vector2f forceOfGravity(Planet &first, Planet &second);
float distanceApart(sf::Vector2f, sf::Vector2f, int, int, float *);

// Main game loop and initialization
int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWWIDTH), "Gravity Simulation!", sf::Style::Default, settings);
	window.setFramerateLimit(60);
	sf::Event event;
	sf::Sprite background;
	sf::Texture backTexture;
	sf::Vector2f gravity;
	int dist;
	bool isCollided = false;
	Planet planet1(20.0, true), planet2(3.5f, false);

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
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		// Update sprite postions
		if (!isCollided)
		{
			gravity = forceOfGravity(planet1, planet2);
			planet1.updatePosition(gravity);
			planet2.updatePosition(-gravity);
		}

		// Check for planet collisions
		float unimportant = 0.f; // store values nowhere
		float *skip = &unimportant;

		dist = distanceApart(planet1.m_Shape.getPosition(), planet2.m_Shape.getPosition(), planet1.m_Shape.getRadius(), planet2.m_Shape.getRadius(), skip);

		if (dist < (planet1.m_Shape.getRadius() + planet2.m_Shape.getRadius()))
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

// Calculate force of gravity with Fg = G(m1*m2)/r^2
sf::Vector2f forceOfGravity(Planet &first, Planet &second)
{
	sf::Vector2f force;
	float magnitude, direction, fx, fy;

	// calculate distance between two points (components)
	float radius1 = first.m_Shape.getRadius(), radius2 = second.m_Shape.getRadius();
	float r = distanceApart(first.m_Shape.getPosition(), second.m_Shape.getPosition(), radius1, radius2, &direction);

	// calculate force using Newton's law of universal gravitation
	magnitude = GRAVCONST * ((first.m_Mass * second.m_Mass) / (r * r));

	// convert magnitude back to components
	fx = cos(direction) * magnitude;
	fy = sin(direction) * magnitude;

	force = sf::Vector2f(fx, fy);
	return force;
}

// Calculate distance between two points
float distanceApart(sf::Vector2f first, sf::Vector2f second, int radius1, int radius2, float *direction)
{
	float deltaX = second.x - first.x;
	float deltaY = second.y - first.y;

	// calculate direction
	*direction = atan2(deltaY, deltaX);

	return sqrt((deltaY * deltaY) + (deltaX * deltaX));
}
