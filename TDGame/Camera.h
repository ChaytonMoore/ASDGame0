#pragma once
#include <SFML/Graphics.hpp>

struct Camera
{
	static sf::Vector2f Delta;
	static sf::Vector2f Location;
	static float Zoom;

	static void CameraMovement(double DeltaTime);

	static float GetDistance(sf::Vector2f a, sf::Vector2f b);
};

