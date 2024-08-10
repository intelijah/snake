#include "Fruit.h"

Fruit::Fruit()
{
	srand((int)time(0));

	outlineThickness = 2.5f;

	fruitPos.x = ((rand() % 20) * 25) + outlineThickness, fruitPos.y = ((rand() % 20) * 25) + outlineThickness;
	fruitSize.x = 20.f, fruitSize.y = 20.f;
	fruitRect.setFillColor(sf::Color::Red);
	fruitRect.setOutlineColor(sf::Color::Black);
	fruitRect.setSize(fruitSize);
	fruitRect.setPosition(fruitPos);
}

sf::RectangleShape Fruit::getRect()
{
	return fruitRect;
}

void Fruit::randomizePos()
{
	sf::Vector2f newPos;
	newPos.x = ((rand() % 20) * 25) + outlineThickness;
	newPos.y = ((rand() % 20) * 25) + outlineThickness;
	fruitRect.setPosition(newPos);
}

