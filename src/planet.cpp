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
// mass of the sun * 10^-10 divided by radius of the sun
const double SUN_MASS_TO_RADIUS = 1.989e20 / 6.9634e8;

Planet::Planet(float radius, bool iscentre)
{
	sf::Color colour;
	sf::Texture moon;
	Planet::m_Shape = sf::CircleShape(radius);

	// Planet velocity, colour and position
	if (iscentre)
	{
		Planet::m_Shape.setPosition(WINDOWWIDTH / 2 - radius, WINDOWWIDTH / 2 - radius);
		Planet::m_Velocity = sf::Vector2f(0.f, 0.f);
		Planet::m_Shape.setFillColor(sf::Color::Yellow);

		// Planet mass in kg -> m * (kg/m) = kg
		Planet::m_Mass = (double)(radius * 5) * SUN_MASS_TO_RADIUS;
	}
	else
	{
		Planet::m_Shape.setPosition(WINDOWWIDTH / 2 - radius, WINDOWWIDTH / 2 - 200);
		Planet::m_Velocity = sf::Vector2f(3.f, 0.f);
		Planet::m_Shape.setFillColor(sf::Color::White);

		// Planet mass in kg -> m * (kg/m) = kg
		Planet::m_Mass = (double)(radius * 5) * MOON_MASS_TO_RADIUS;
	}

	// Planet texture
	if (!moon.loadFromFile("resource/moon_texture.jpg"))
		exit(1);
	Planet::m_Shape.setOutlineColor(sf::Color(0, 0, 0));
	Planet::m_Shape.setOutlineThickness(2.f);
	Planet::m_Shape.setTexture(&moon);
}

// Add gravity to current velocity
void Planet::updatePosition(sf::Vector2f forceOfGravity)
{
	// create acceleration by dividing by mass F=ma => a = F/m
	Planet::m_Velocity += forceOfGravity / m_Mass;
	Planet::m_Shape.move(Planet::m_Velocity);
}
