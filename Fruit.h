#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <cstdlib>

class Fruit
{
private:
	sf::RectangleShape fruitRect;
	sf::Vector2f fruitPos;
	sf::Vector2f fruitSize;
	float outlineThickness;
public:
	Fruit();

	sf::RectangleShape getRect();

	void randomizePos();
};