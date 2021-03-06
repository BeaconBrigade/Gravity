//
// Created May 11, 2022 by Ryan Cullen
//
//
// Definition of Planet class
//
//
//

#include "planet.hpp"

// First number is mass of moon (div 10^8) in kg and second is 
// radius of moon in m. Multiply radius to get mass
// of moon-like object. aka, this is kg/m
const double MOON_MASS_TO_RADIUS = 7.34767309e14 / 1737400.0;

Planet::Planet(float radius, bool iscentre)
{
	sf::Color colour;
	sf::Texture moon;
	Planet::m_Shape = sf::CircleShape(radius);

	// Planet velocity, colour and position
	if (iscentre)
	{
		Planet::m_Shape.setPosition(WINDOWWIDTH / 2 - radius, WINDOWWIDTH / 2 - radius);
		Planet::m_Velocity = sf::Vector2f(-0.7f, 0.f);
		Planet::m_Shape.setFillColor(sf::Color::Yellow);
	}
	else
	{
		Planet::m_Shape.setPosition(WINDOWWIDTH / 2 - radius, WINDOWWIDTH / 2 - 50);
		Planet::m_Velocity = sf::Vector2f(1.4f, 0.f);
		Planet::m_Shape.setFillColor(sf::Color::White);
	}

	// Planet texture
	if (!moon.loadFromFile("resource/moon_texture.jpg"))
		exit(1);
	Planet::m_Shape.setOutlineColor(sf::Color(0, 0, 0));
	Planet::m_Shape.setOutlineThickness(2.f);
	Planet::m_Shape.setTexture(&moon);
	
	// Planet mass in kg -> m * (kg/m) = kg
	Planet::m_Mass = (double)(radius * 5) * MOON_MASS_TO_RADIUS;
}

// Add gravity to current velocity
void Planet::updatePosition(sf::Vector2f gravity)
{
	Planet::m_Velocity += gravity;
	Planet::m_Shape.move(Planet::m_Velocity);
}

