#pragma once
#include"variables.h"
#include<SFML/Graphics.hpp>
#include<iostream>
#include<cmath>
#include <limits>
#include<vector>

 class Player {
public:
	Player();
	friend class Game;
private:
	float playerSpeed;
	sf::CircleShape playerCircle;
	sf::Vector2f mousePosition; 
	void rayEmitter(sf::RenderWindow& l_window,int array[ROWS][COLUMNS]);
	void playerMovement(sf::Time l_deltaTime );
	void drawPlayer(sf::RenderWindow& l_window);
	void rayArray(sf::RenderWindow& l_window);
	sf::VertexArray ray;
	float rayHorzLength;
	float rayVertLength;
	
	std::vector<sf::VertexArray> rays;
};