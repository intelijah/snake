#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <queue>
#include <utility>
#include "Fruit.h"

class Snake
{
private:
	std::vector<sf::RectangleShape*> snake;
	float outlineThickness;
	int initialVecSize;
	bool moving;
public:
	Snake();

	void moveSnakeR();
	void moveSnakeU();
	void moveSnakeD();
	void moveSnakeL();

	void addSegment(sf::Vector2f newPlace);

	void setSnake();

	std::vector<sf::RectangleShape*> getSnake();
	bool getMoving() const;
	void setMoving(bool tOrF);

};