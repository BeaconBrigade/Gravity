//
// Created May 11, 2022 by Ryan Cullen
//
// Definition of Planet class
//
//

#include "planet.hpp"
#include <ctime>

// First number is mass of moon in kg and second is 
// radius of moon in m. Multiply radius to get mass
// of moon like object. aka, this is kg/m
const double MOON_MASS_TO_RADIUS = 7.34767309e22 / 1737400.0;

Planet::Planet(int radius, bool islead)
{
	sf::Color colour;

	if (islead)
		srand(time(NULL));

	// Planet shape and colour
	Planet::m_Shape = sf::CircleShape(radius / 5);
	colour = sf::Color((rand() * 1000) % 255, (rand() * 1000) % 255, (rand() * 1000) % 255);
	Planet::m_Shape.setFillColor(colour);
	
	// Planet mass in kg -> m * (kg/m) = kg
	Planet::m_Mass = (double)radius * MOON_MASS_TO_RADIUS;
}


