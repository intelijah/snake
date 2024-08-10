#include "Engine.h"
#include <iostream>

Engine::Engine()
{
	vm.height = 505; 
	vm.width = 505;
	std::cout << "creating window!";
	window.create(vm, "Snake!", sf::Style::Default);
	if (window.isOpen())
	{
		std::cout << "did it.";
	}
	else
	{
		std::cout << "fail.";
	}

	dir = Direction::DOWN;
	gameState = GameState::START;

	score = 0;
	scoreNumAsString = std::to_string(score);

	playString = "Welcome to Snake!\nPress enter to play";
	gameOverString = "Game Over!\nYour score was " + scoreNumAsString + "\nPress enter to play again";
	winString = "You Win! Yay!";
	scoreString << "Score  " << score;

	font.loadFromFile("fonts/S.A.O 16.ttf");

	playText.setFont(font);
	playText.setCharacterSize(25);
	playText.setOrigin(playText.getGlobalBounds().left + (playText.getGlobalBounds().width / 2), playText.getGlobalBounds().top + (playText.getGlobalBounds().height / 2));
	playText.setPosition(window.getSize().x / 3.6f, window.getSize().y / 3.1f);
	playText.setFillColor(sf::Color::White);
	playText.setString(playString);

	gameOverText.setFont(font);
	gameOverText.setCharacterSize(22);
	gameOverText.setOrigin(gameOverText.getGlobalBounds().left + (gameOverText.getGlobalBounds().width / 2), gameOverText.getGlobalBounds().top + (gameOverText.getGlobalBounds().height / 2));
	gameOverText.setPosition(window.getSize().x / 3.6f, window.getSize().y / 3.1f);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setString(gameOverString);

	winText.setFont(font);
	winText.setCharacterSize(40);
	winText.setOrigin(winText.getGlobalBounds().left + (winText.getGlobalBounds().width / 2), winText.getGlobalBounds().top + (winText.getGlobalBounds().height / 2));
	winText.setPosition(window.getSize().x / 3.6f, window.getSize().y / 3.1f);
	winText.setFillColor(sf::Color::White);
	winText.setString(winString);

	scoreText.setFont(font);
	scoreText.setCharacterSize(15);
	scoreText.setStyle(sf::Text::Bold);
	scoreText.setPosition(sf::Vector2f(5.f, 5.f));
	scoreText.setFillColor(sf::Color::White);
	scoreText.setString(scoreString.str());

	snake.setMoving(false);

	timeBeforeNextFrame = 150.f;
	timeCounter = 0.f;

	dt = clock.restart();
}

bool const Engine::getRunning() const
{
	return running;
}

void Engine::input()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			{
				window.close();
				break;
			}

		case sf::Event::KeyPressed:
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				if (gameState == GameState::GAMEOVER || gameState == GameState::WIN || gameState == GameState::START || gameState == GameState::PAUSED)
				{
					if (gameState == GameState::GAMEOVER)
					{
						fruit.randomizePos();
						gameState = GameState::PLAYING;
					}
					else if (gameState == GameState::WIN)
					{
						gameState == GameState::PLAYING;
						snake.setSnake();
						dir = Direction::DOWN;
					}
					else
					{
						gameState = GameState::PLAYING;
					}
				}
				
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
				break;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (dir == Direction::RIGHT || 
					snake.getSnake().back()->getPosition().x - 
					(20 + (snake.getSnake().back()->getOutlineThickness() * 2)) == 
					snake.getSnake()[snake.getSnake().size() - 1]->getPosition().x)
				{
					continue;
				}
				else
				{
					dir = Direction::LEFT;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (dir == Direction::LEFT ||
					snake.getSnake().back()->getPosition().x +
					(20 + (snake.getSnake().back()->getOutlineThickness() * 2)) ==
					snake.getSnake()[snake.getSnake().size() - 1]->getPosition().x)
				{
					continue;
				}
				else
				{
					dir = Direction::RIGHT;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (dir == Direction::DOWN ||
					snake.getSnake().back()->getPosition().y +
					(20 + (snake.getSnake().back()->getOutlineThickness() * 2)) ==
					snake.getSnake()[snake.getSnake().size() - 1]->getPosition().y)
				{
					continue;
				}
				else
				{
					dir = Direction::UP;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (dir == Direction::UP ||
					snake.getSnake().back()->getPosition().y -
					(20 + (snake.getSnake().back()->getOutlineThickness() * 2)) ==
					snake.getSnake()[snake.getSnake().size() - 1]->getPosition().y)
				{
					continue;
				}
				else
				{
					dir = Direction::DOWN;
				}
			}
			break;
		}
		default:
			{
				break;
			}
		}
	}
}

void Engine::run()
{
	while (window.isOpen())
	{
		input();
		update();
		draw();
	}
}

void Engine::update()
{
	// time counter adds to itself the delta time as seconds (0.whatevernumber) 
	// every time the update function is ran
	timeCounter += dt.asSeconds() * 1.4f;
	
	// if the game is in playing game, the snake moves and the game is played
	if (gameState == GameState::PLAYING)
	{
		snake.setMoving(true);

		// move snake 1 block in the respective direction if the time counter 
		// hasn't reached the time needed to be gotten before the next frame, 
		// which is 100.
		if (timeCounter >= timeBeforeNextFrame)
		{
			if (dir == Direction::RIGHT)
			{
				snake.moveSnakeR();
			}
			else if (dir == Direction::LEFT)
			{
				snake.moveSnakeL();
			}
			else if (dir == Direction::UP)
			{
				snake.moveSnakeU();
			}
			else if (dir == Direction::DOWN)
			{
				snake.moveSnakeD();
			}

			// iterates through the snake and checks if the snake has gotten a 
			// fruit, and then adds three segments if it has
			for (int i = 0; i < snake.getSnake().size(); i++)
			{
				if (snake.getSnake()[i]->getGlobalBounds().intersects(fruit.getRect().getGlobalBounds()))
				{
					int segsToAdd = 3;
					int counter = 0;

					// adds 3 segments
					for (int i = 0; i < segsToAdd; i++)
					{
						snake.addSegment(sf::Vector2f(snake.getSnake().front()->getPosition()));
					}

					// changes fruit position
					fruit.randomizePos();

					// adds ten to score
					score += 10;

					// clears scoreString ss to Score  (score) and sets scoreText to that string
					scoreString.str("");
					scoreString << "Score  " << score;
					scoreText.setString(scoreString.str());

					// makes snake faster every fruit
					timeBeforeNextFrame -= 3.f;
				}

				// check collision with walls or the snake's self and put game over if they do collide
				for (int i = 0; i < snake.getSnake().size() - 1; i++)
				{
					if (snake.getSnake().back()->getPosition() == snake.getSnake()[i]->getPosition() ||
						snake.getSnake().back()->getPosition().x < 0 || 
						snake.getSnake().back()->getPosition().y < 0 || 
						snake.getSnake().back()->getPosition().x > 480 || // 480 is just a random number below 505, 
						snake.getSnake().back()->getPosition().y > 480)   // the height and width of the screen
					{
						gameState = GameState::GAMEOVER;
					}
				}
				
			}
			timeCounter = 0;
		}

		// if the snake reaches above the 400 (fills the whole screen), you win
		if (snake.getSnake().size() >= 400)
		{
			gameState = GameState::WIN;
		}
		
	}

	// if game is paused, snake doesn't move
	if (gameState == GameState::PAUSED)
	{
		snake.setMoving(false);
	}

	// if game over, reset everything and change game over string to game 
	// over blah blah blah plus the score you got
	if (gameState == GameState::GAMEOVER)
	{
		snake.setMoving(false);
		snake.setSnake();
		timeBeforeNextFrame = 100.f;
		timeCounter = 0;
		scoreNumAsString = std::to_string(score);
		gameOverString = "Game Over!\nYour score was " + scoreNumAsString + "\nPress enter to play again";
		gameOverText.setString(gameOverString);
	}

	// if you win, reset everything
	if (gameState == GameState::WIN)
	{
		snake.setMoving(false);
		timeBeforeNextFrame = 100.f;
		timeCounter = 0;
	}
}


void Engine::draw()
{
	window.clear();

	// start gamestate stuff drawn
	if (gameState == GameState::START)
	{
		window.draw(playText);
	}

	// playing gamestate stuff drawn
	if (gameState == GameState::PLAYING)
	{
		//draws snake
		for (sf::RectangleShape* segment : snake.getSnake())
		{
			window.draw(*segment);
		}
		//draws fruit
		window.draw(fruit.getRect());
	}

	// game over gamestate stuff drawn
	if (gameState == GameState::GAMEOVER)
	{
		//draws game over text
		window.draw(gameOverText);
	}

	// win gamestate stuff drawn
	if (gameState == GameState::WIN)
	{
		window.draw(winText);
		// i wanted to show the snake so you see the achievement you've made :)
		for (sf::RectangleShape* segment : snake.getSnake())
		{
			window.draw(*segment);
		}
	}

	// pause gamestate stuff drawn (same stuff is drawn for playing, but here
	// snake is not moving
	if (gameState == GameState::PAUSED)
	{
		for (sf::RectangleShape* segment : snake.getSnake())
		{
			window.draw(*segment);
		}
		window.draw(fruit.getRect());
	}
	window.draw(scoreText);
	window.display();
}