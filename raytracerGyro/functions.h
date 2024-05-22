#pragma once
#include"variables.h"
#include<SFML/Graphics.hpp>
 
 
void drawGrid(sf::RenderWindow& l_window, int l_rows, int l_columns, int l_windowSize);

 
void drawObstacles(sf::RenderWindow& l_window, int l_rows, int l_columns, int l_windowSize, int l_array[ROWS][COLUMNS]);