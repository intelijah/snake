#include "SnakeClass.h"

Snake::Snake()
{
	outlineThickness = 2.5f;
	initialVecSize = 3;

	for (int i = 0; i < initialVecSize; i++)
	{
		sf::RectangleShape* newSegment = new sf::RectangleShape;

		newSegment->setSize(sf::Vector2f(20, 20));
		newSegment->setFillColor(sf::Color::Green);
		newSegment->setOutlineColor(sf::Color::Black);
		newSegment->setOutlineThickness(2.5f);
		newSegment->setPosition(sf::Vector2f(100 + outlineThickness, 100 + outlineThickness));
		snake.push_back(newSegment);
		newSegment->setPosition(newSegment->getPosition().x, newSegment->getPosition().y + (20 + (outlineThickness * 2)));

		moving = false;
	}
}

void Snake::moveSnakeR()
{
	for (int i = 0; i < snake.size() - 1; i++)
	{
		snake[i]->setPosition(snake[i + 1]->getPosition());
	}
	snake.back()->setPosition(snake.back()->getPosition().x + (20 + (outlineThickness * 2)), snake.back()->getPosition().y);
}

void Snake::moveSnakeU()
{
	for (int i = 0; i < snake.size() - 1; i++)
	{
		snake[i]->setPosition(snake[i + 1]->getPosition());
	}
	snake.back()->setPosition(snake.back()->getPosition().x, snake.back()->getPosition().y - (20 + (outlineThickness * 2)));
}

void Snake::moveSnakeD()
{
	for (int i = 0; i < snake.size() - 1; i++)
	{
		snake[i]->setPosition(snake[i + 1]->getPosition());
	}
	snake.back()->setPosition(snake.back()->getPosition().x, snake.back()->getPosition().y + (20 + (outlineThickness * 2)));
}

void Snake::moveSnakeL()
{
	for (int i = 0; i < snake.size() - 1; i++)
	{
		snake[i]->setPosition(snake[i + 1]->getPosition());
	}
	snake.back()->setPosition(snake.back()->getPosition().x - (20 + (outlineThickness * 2)), snake.back()->getPosition().y);
}

void Snake::addSegment(sf::Vector2f newPlace)
{
	sf::RectangleShape* newSegment = new sf::RectangleShape;
	newSegment->setSize(sf::Vector2f(20, 20));
	newSegment->setFillColor(sf::Color::Green);
	newSegment->setOutlineColor(sf::Color::Black);
	newSegment->setOutlineThickness(2.5f);
	newSegment->setPosition(newPlace);

	snake.emplace(snake.begin(), newSegment);
}

void Snake::setSnake()
{
	sf::Vector2f initialPos(100, 100);
	for (int i = 0; i < snake.size() - 3; i++)
	{
		snake.pop_back();
	}
	for (int i = 0; i < snake.size(); i++)
	{
		snake[i]->setPosition(initialPos);
		initialPos.y += 20 + ((outlineThickness * 2) + 2.5f);
	}
	setMoving(false);
}

std::vector<sf::RectangleShape*> Snake::getSnake()
{
	return snake;
}

bool Snake::getMoving() const
{
	return moving;
}

void Snake::setMoving(bool tOrF)
{
	moving = tOrF;
}
