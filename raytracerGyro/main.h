#pragma once
#include"variables.h"
#include"player.h"
#include<SFML/Graphics.hpp>
#include<vector>


class Game :Player{
public:
	void run();
	Game();

private:
	void processEvents();
	void display();
	void update();
	Player player;
	sf::Time deltaTime;
	sf::Clock clock;
private:
	sf::RenderWindow mWindow;
	sf::Event windowCloseEvent;
	int obstacleMap[ROWS][COLUMNS];
	//std::vector< std::vector<int>> obstacle( ROWS, std::vector<int>(COLUMNS));
};
Game::Game() :mWindow{ sf::VideoMode(WINDOWSIZE,WINDOWSIZE),"rayCaster" },
obstacleMap{ {0, 0, 1, 0, 0, 0, 0, 1, 1, 0},
			 {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			 {0, 0, 1, 0, 1, 0, 1, 0, 0, 0},
			 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			 {0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
			 {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
			 {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
			 {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			 {0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
			 {1, 0, 0, 1, 0, 0, 0, 0, 0, 1}
}

{
	mWindow.setMouseCursorVisible(false);
}

