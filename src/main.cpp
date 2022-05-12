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
const int WINDOWWIDTH = 800;

sf::Vector2f accGrav(Planet &first, Planet &second);

// Main game loop and initialization
int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWWIDTH), "Gravity Simulation!");
	sf::Event event;
	sf::Sprite background;
	sf::Texture backTexture;

	Planet planet1(100, true), planet2(300, false);
	planet1.m_Shape.setPosition(0.f, 0.f);
	planet2.m_Shape.setPosition(WINDOWWIDTH / 2 - 75, WINDOWWIDTH / 2 - 75);

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
	float x1 = first.m_Shape.getPosition().x - radius1, x2 = second.m_Shape.getPosition().x - radius2;
	float deltaX = x2 - x1;
	float y1 = first.m_Shape.getPosition().y - radius1, y2 = second.m_Shape.getPosition().y - radius2;
	float deltaY = y2 - y1;
	float r = sqrt((deltaY * deltaY) + (deltaX * deltaX));

	// calculate direction from origin using components
	direction = atan(deltaY / deltaX);

	// calculate acceleration due to gravity using Newton's law of universal gravitation
	magnitude = GRAVCONST * ((first.m_Mass * second.m_Mass) / (r * r));

	// convert magnitude back to components
	accX = cos(direction) * magnitude;
	accY = sin(direction) * magnitude;

	acceleration = sf::Vector2f(accX, accY);
	return acceleration;
}




