#include"main.h"
#include"functions.h"
#include<iostream>
//constexpr auto deltaTime = 1.f/60.f;

void Game::run() {
	clock;
	while (mWindow.isOpen()) {
		
		processEvents();
		update();
		display();
	}
}

void Game::processEvents() {
	while(mWindow.pollEvent(windowCloseEvent)){
		if(windowCloseEvent.type == sf::Event::Closed) 
		mWindow.close();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			mWindow.close();
		}
	}
}

void Game::update() {
	deltaTime = clock.restart();
	player.playerMovement(deltaTime);
	player.rayEmitter(mWindow,obstacleMap);
}

void Game::display() {
	mWindow.clear(sf::Color::Black);
	player.drawPlayer(mWindow);
	drawGrid(mWindow,ROWS,COLUMNS, WINDOWSIZE);
    drawObstacles(mWindow, ROWS, COLUMNS, WINDOWSIZE, obstacleMap);
	mWindow.display();

}

int main() {
	Game game;
	game.run();
	return 0;
}
