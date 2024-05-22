#include"functions.h"
#include<SFML/Graphics.hpp>



void drawGrid(sf::RenderWindow& l_window,int l_rows,int l_columns,int l_windowSize) {
	//std::vector<sf::VertexArray> rowLines;
	for (int i = 0; i < l_rows; i++) {
		sf::VertexArray yline(sf::Lines, 2);
		yline[0].position = sf::Vector2f(0.f, i * l_windowSize / l_rows);
		yline[1].position = sf::Vector2f(l_windowSize, i * l_windowSize / l_rows);
		//rowLines.push_back(yline);
		l_window.draw(yline);
	}

	for (int i = 0; i < l_columns; i++) {
		sf::VertexArray xline(sf::Lines, 2);
		xline[0].position = sf::Vector2f(i * l_windowSize / l_columns,0.f);
		xline[1].position = sf::Vector2f(i * l_windowSize / l_rows, l_windowSize);
		//rowLines.push_back(yline);
		l_window.draw(xline);
	}
}

void drawObstacles(sf::RenderWindow& l_window,int l_rows,int l_columns,int l_windowSize,int l_array[ROWS][COLUMNS]) {
	for (int i = 0; i <l_rows ; i++) {
		for (int j = 0; j < l_columns; j++) {
			if (l_array[i][j] == 1) {
				sf::RectangleShape square(sf::Vector2f(l_windowSize / l_rows, l_windowSize / l_columns));
				//square.setOrigin(sf::Vector2f(square.getSize().x / 2, square.getSize().y / 2));
				square.setPosition(sf::Vector2f(j * l_windowSize / l_columns, i * l_windowSize / l_rows));
				l_window.draw(square);
			}
		}
	}

}