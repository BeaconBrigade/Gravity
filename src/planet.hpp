//
// Created May 11, 2022 by Ryan Cullen
//
// Header for Planet class
//
//

#include <SFML/Graphics.hpp>
const int WINDOWWIDTH = 800;

class Planet
{
public:
	sf::CircleShape m_Shape;
	sf::Vector2f m_Velocity;
	float m_Mass;

public:
	Planet(float radius, bool iscentre);
	void updatePosition(sf::Vector2f forceOfGravity);
};
