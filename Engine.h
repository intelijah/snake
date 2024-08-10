#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "SnakeClass.h"
#include "Fruit.h"

class Engine
{
private:
	sf::VideoMode vm;
	sf::RenderWindow window;
	bool running = true;

	Snake snake;
	Fruit fruit;

	sf::Clock clock;
	sf::Time dt;
	
	sf::Font font;

	sf::String playString;
	sf::Text playText;
	sf::String gameOverString;
	sf::Text gameOverText;
	std::stringstream scoreString;
	sf::Text scoreText;
	sf::String winString;
	sf::Text winText;

	int score; 
	std::string scoreNumAsString;
	float timeBeforeNextFrame;
	float timeCounter;

	enum class Direction { LEFT, RIGHT, UP, DOWN };
	Direction dir;

	enum class GameState { PLAYING, GAMEOVER, WIN, START, PAUSED };
	GameState gameState;
public:
	Engine();

	bool const getRunning() const;
	bool const getMoving() const;
	void setMoving(bool tOrF);

	void run();

	void input();
	void update();
	void draw();
};