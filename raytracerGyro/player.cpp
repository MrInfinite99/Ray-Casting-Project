#include"player.h"

Player::Player() :ray{sf::Lines,2} {
	playerCircle.setRadius(10.0f);
	playerCircle.setOrigin(playerCircle.getRadius() / 2, playerCircle.getRadius() / 2);
	playerCircle.setFillColor(sf::Color::Red);
	playerCircle.setPosition(sf::Vector2f(300.0f, 30.0f));
	playerSpeed = 300.0f;
}


void Player::playerMovement(sf::Time l_deltaTime ) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		playerCircle.move(sf::Vector2f(0.0f,playerSpeed*l_deltaTime.asSeconds()));
		 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		playerCircle.move(sf::Vector2f(0.0f, -playerSpeed * l_deltaTime.asSeconds()));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		playerCircle.move(sf::Vector2f(-playerSpeed * l_deltaTime.asSeconds(), 0.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerCircle.move(sf::Vector2f(playerSpeed * l_deltaTime.asSeconds(), 0.0f));
		 
	}

	 
}

void Player::drawPlayer(sf::RenderWindow& l_window) {
	l_window.draw(playerCircle);
	 
	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		l_window.draw(rays[i]);
	}
	 
}

void Player::rayEmitter(sf::RenderWindow& l_window, int array[ROWS][COLUMNS]) {

	sf::Vector2i mousePosition = sf::Mouse::getPosition(l_window);

	rayArray(l_window);
	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		float y_pos = rays[i][1].position.y - playerCircle.getPosition().y;
		float x_pos = rays[i][1].position.x - playerCircle.getPosition().x;
		float angle = (180 / PI) * atan2(y_pos, x_pos); // the 1st quad is the 4th,and it follows clockwise from there
		sf::Vector2i rayPath = sf::Vector2i(floor(playerCircle.getPosition().x / CELL_SIZE), floor(playerCircle.getPosition().y / CELL_SIZE));

		angle *= (PI / 180);//back to radians
		float scalingFactorX = sqrt(1 + (tan(angle) * tan(angle)));
		float scalingFactorY = sqrt(1 + (cot(angle)) * (cot(angle)));
		angle *= (180 / PI);//back to degrees

		if (angle > 0 && angle < 90) {
			rayHorzLength = (floor(playerCircle.getPosition().x / CELL_SIZE) + 1) * (CELL_SIZE)-playerCircle.getPosition().x;
			rayVertLength = (floor(playerCircle.getPosition().y / CELL_SIZE) + 1) * (CELL_SIZE)-playerCircle.getPosition().y;

			while (array[rayPath.y][rayPath.x] != 1) {
				sf::Vector2i rayStartPos = sf::Vector2i(floor(playerCircle.getPosition().x / CELL_SIZE), floor(playerCircle.getPosition().y / CELL_SIZE));
				sf::Vector2i rayFinalPos = sf::Vector2i(floor(rays[i][1].position.x / CELL_SIZE), (floor(rays[i][1].position.y / CELL_SIZE)));

				if (rayStartPos != rayFinalPos) {

					if (rayPath.x < 0 || rayPath.x > COLUMNS - 1 || rayPath.y < 0 || rayPath.y > ROWS - 1) {
						break; // Exit loop if rayPath is out of bounds
					}

					if ((rayFinalPos.x == rayPath.x) && (rayFinalPos.y == rayPath.y) && (array[rayPath.y][rayPath.x] != 1)) {

						break;
					}

					if (rayHorzLength * scalingFactorX > rayVertLength * scalingFactorY) {
						rayVertLength += CELL_SIZE;
						rayPath.y++;

					}
					else if (rayHorzLength * scalingFactorX < rayVertLength * scalingFactorY) {
						rayHorzLength += CELL_SIZE;
						rayPath.x++;

					}
					else {
						rayVertLength += CELL_SIZE;
						rayPath.y++;
						rayHorzLength += CELL_SIZE;
						rayPath.x++;
					}

				}
				else
					break;

			}
			//check collision and intersection
			if (array[rayPath.y][rayPath.x] == 1) {
				float intersectX = 0.0f, intersectY = 0.0f;

				if ((rayPath.x * CELL_SIZE - rays[i][0].position.x) / cos(angle * (PI / 180)) > (rayPath.y * CELL_SIZE - rays[i][0].position.y) / sin(angle * (PI / 180))) {

					intersectX = rayPath.x * CELL_SIZE;
					intersectY = playerCircle.getPosition().y + (intersectX - playerCircle.getPosition().x) * tan(angle * (PI / 180));
					rays[i][1].position.x = intersectX;
					rays[i][1].position.y = intersectY;
				}
				else if ((rayPath.x * CELL_SIZE - rays[i][0].position.x) / cos(angle * (PI / 180)) < (rayPath.y * CELL_SIZE - rays[i][0].position.y) / sin(angle * (PI / 180))) {

					intersectY = rayPath.y * CELL_SIZE;
					intersectX = playerCircle.getPosition().x + (intersectY - playerCircle.getPosition().y) * cot(angle * (PI / 180));
					rays[i][1].position.x = intersectX;
					rays[i][1].position.y = intersectY;
				}
			}
			else {

			}
		}
		else if (angle > 90 && angle < 180) {

			rayHorzLength = playerCircle.getPosition().x - (floor(playerCircle.getPosition().x / CELL_SIZE) + 0) * (CELL_SIZE);
			rayVertLength = (floor(playerCircle.getPosition().y / CELL_SIZE) + 1) * (CELL_SIZE)-playerCircle.getPosition().y;
			while (array[rayPath.y][rayPath.x] != 1) {
				sf::Vector2i rayStartPos = sf::Vector2i(floor(playerCircle.getPosition().x / CELL_SIZE), floor(playerCircle.getPosition().y / CELL_SIZE));
				sf::Vector2i rayFinalPos = sf::Vector2i(floor(rays[i][1].position.x / CELL_SIZE), (floor(rays[i][1].position.y / CELL_SIZE)));

				if (rayStartPos != rayFinalPos) {

					if (rayPath.x < 0 || rayPath.x > COLUMNS - 1 || rayPath.y < 0 || rayPath.y > ROWS - 1) {
						break; // Exit loop if rayPath is out of bounds
					}

					if ((rayFinalPos.x == rayPath.x) && (rayFinalPos.y == rayPath.y) && (array[rayPath.y][rayPath.x] != 1)) {

						break;
					}


					if (rayHorzLength * scalingFactorX > rayVertLength * scalingFactorY) {
						rayVertLength += CELL_SIZE;
						rayPath.y++;

					}
					else if (rayHorzLength * scalingFactorX < rayVertLength * scalingFactorY) {
						rayHorzLength += CELL_SIZE;
						rayPath.x--;

					}
					else {
						rayVertLength += CELL_SIZE;
						rayPath.y++;
						rayHorzLength += CELL_SIZE;
						rayPath.x--;
					}


				}
				else
					break;

			}
			//check collision and intersection
			if (array[rayPath.y][rayPath.x] == 1) {
				float intersectX = 0.0f, intersectY = 0.0f;
				float t1 = ((rayPath.x + 1) * -CELL_SIZE + rays[i][0].position.x) / ((-1) * cos(angle * (PI / 180)));
				float t2 = (rayPath.y * CELL_SIZE - rays[i][0].position.y) / sin(angle * (PI / 180));


				if (t1 > t2) {

					intersectX = (rayPath.x + 1) * CELL_SIZE;
					intersectY = playerCircle.getPosition().y + (intersectX - playerCircle.getPosition().x) * tan(angle * (PI / 180));
					rays[i][1].position.x = intersectX;
					rays[i][1].position.y = intersectY;
				}
				else if (t1 < t2) {

					intersectY = rayPath.y * CELL_SIZE;
					intersectX = playerCircle.getPosition().x + (intersectY - playerCircle.getPosition().y) * cot(angle * (PI / 180));
					rays[i][1].position.x = intersectX;
					rays[i][1].position.y = intersectY;
				}
			}
		}
		else if (angle < 0 && angle > -90) {
			rayHorzLength = (floor(playerCircle.getPosition().x / CELL_SIZE) + 1) * (CELL_SIZE)-playerCircle.getPosition().x;
			rayVertLength = playerCircle.getPosition().y - (floor(playerCircle.getPosition().y / CELL_SIZE) + 0) * (CELL_SIZE);
			while (array[rayPath.y][rayPath.x] != 1) {
				sf::Vector2i rayStartPos = sf::Vector2i(floor(playerCircle.getPosition().x / CELL_SIZE), floor(playerCircle.getPosition().y / CELL_SIZE));
				sf::Vector2i rayFinalPos = sf::Vector2i(floor(rays[i][1].position.x / CELL_SIZE), (floor(rays[i][1].position.y / CELL_SIZE)));

				if (rayStartPos != rayFinalPos) {

					if (rayPath.x < 0 || rayPath.x > COLUMNS - 1 || rayPath.y < 0 || rayPath.y > ROWS - 1) {
						break; // Exit loop if rayPath is out of bounds
					}

					if ((rayFinalPos.x == rayPath.x) && (rayFinalPos.y == rayPath.y) && (array[rayPath.y][rayPath.x] != 1)) {

						break;
					}


					if (rayHorzLength * scalingFactorX > rayVertLength * scalingFactorY) {
						rayVertLength += CELL_SIZE;
						rayPath.y--;

					}
					else if (rayHorzLength * scalingFactorX < rayVertLength * scalingFactorY) {
						rayHorzLength += CELL_SIZE;
						rayPath.x++;

					}
					else {
						rayVertLength += CELL_SIZE;
						rayPath.y--;
						rayHorzLength += CELL_SIZE;
						rayPath.x++;
					}


				}
				else
					break;

			}
			//check collision and intersection
			if (array[rayPath.y][rayPath.x] == 1) {
				float intersectX = 0.0f, intersectY = 0.0f;
				float t1 = (rayPath.x * CELL_SIZE - rays[i][0].position.x) / cos(angle * (PI / 180));
				float t2 = ((rayPath.y + 1) * CELL_SIZE - rays[i][0].position.y) / sin(angle * (PI / 180));


				if (t1 > t2) {

					intersectX = rayPath.x * CELL_SIZE;
					intersectY = playerCircle.getPosition().y + (intersectX - playerCircle.getPosition().x) * tan(angle * (PI / 180));
					rays[i][1].position.x = intersectX;
					rays[i][1].position.y = intersectY;
				}
				else if (t1 < t2) {

					intersectY = (rayPath.y + 1) * CELL_SIZE;
					intersectX = playerCircle.getPosition().x + (intersectY - playerCircle.getPosition().y) * cot(angle * (PI / 180));
					rays[i][1].position.x = intersectX;
					rays[i][1].position.y = intersectY;
				}
			}
		}
		else if (angle <-90 && angle > -180) {
			rayHorzLength = -(floor(playerCircle.getPosition().x / CELL_SIZE) + 0) * (CELL_SIZE)+playerCircle.getPosition().x;
			rayVertLength = -(floor(playerCircle.getPosition().y / CELL_SIZE) + 0) * (CELL_SIZE)+playerCircle.getPosition().y;
			while (array[rayPath.y][rayPath.x] != 1) {
				sf::Vector2i rayStartPos = sf::Vector2i(floor(playerCircle.getPosition().x / CELL_SIZE), floor(playerCircle.getPosition().y / CELL_SIZE));
				sf::Vector2i rayFinalPos = sf::Vector2i(floor(rays[i][1].position.x / CELL_SIZE), (floor(rays[i][1].position.y / CELL_SIZE)));

				if (rayStartPos != rayFinalPos) {

					if (rayPath.x < 0 || rayPath.x > COLUMNS - 1 || rayPath.y < 0 || rayPath.y > ROWS - 1) {
						break; // Exit loop if rayPath is out of bounds
					}

					if ((rayFinalPos.x == rayPath.x) && (rayFinalPos.y == rayPath.y) && (array[rayPath.y][rayPath.x] != 1)) {

						break;
					}


					if (rayHorzLength * scalingFactorX > rayVertLength * scalingFactorY) {
						rayVertLength += CELL_SIZE;
						rayPath.y--;

					}
					else if (rayHorzLength * scalingFactorX < rayVertLength * scalingFactorY) {
						rayHorzLength += CELL_SIZE;
						rayPath.x--;

					}
					else {
						rayVertLength += CELL_SIZE;
						rayPath.y--;
						rayHorzLength += CELL_SIZE;
						rayPath.x--;
					}


				}
				else
					break;

			}

			if (array[rayPath.y][rayPath.x] == 1) {
				float intersectX = 0.0f, intersectY = 0.0f;

				if (((rayPath.x + 1) * CELL_SIZE - rays[i][0].position.x) / cos(angle * (PI / 180)) > ((rayPath.y + 1) * CELL_SIZE - rays[i][0].position.y) / sin(angle * (PI / 180))) {

					intersectX = (rayPath.x + 1) * CELL_SIZE;
					intersectY = playerCircle.getPosition().y + (intersectX - playerCircle.getPosition().x) * tan(angle * (PI / 180));
					rays[i][1].position.x = intersectX;
					rays[i][1].position.y = intersectY;
				}
				else if (((rayPath.x + 1) * CELL_SIZE - rays[i][0].position.x) / cos(angle * (PI / 180)) < ((rayPath.y + 1) * CELL_SIZE - rays[i][0].position.y) / sin(angle * (PI / 180))) {

					intersectY = (rayPath.y + 1) * CELL_SIZE;
					intersectX = playerCircle.getPosition().x + (intersectY - playerCircle.getPosition().y) * cot(angle * (PI / 180));
					rays[i][1].position.x = intersectX;
					rays[i][1].position.y = intersectY;
				}
			}
		}

	}

	//the algorithm





}
 
 
float cot(float angle) {
	 
	float degrees = angle * 180.0f / PI;

	if (std::fmod(degrees, 180.0f) == 90.0f) {
		return std::numeric_limits<float>::infinity(); 
	}
	return 1 / tan(angle);
}

void Player::rayArray(sf::RenderWindow& l_window) {


	rays.clear();

	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		sf::VertexArray singleRay(sf::Lines, 2);
		rays.push_back(singleRay);
	}

	sf::Vector2f playerPosition = playerCircle.getPosition();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(l_window);
	sf::Vector2f mouseWorldPosition = l_window.mapPixelToCoords(mousePosition);

	// Calculate the direction vector from player to mouse position
	sf::Vector2f direction = mouseWorldPosition - playerPosition;
	float directionLength = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	sf::Vector2f unitDirection = direction / directionLength;

	// Set the initial ray based on mouse position
	rays[0][0].position = playerPosition;
	rays[0][1].position = mouseWorldPosition;

	for (int i = 1; i < NUMBER_OF_LINES; i++) {
		float angle = ROTATION_ANGLE * i;
		float cosAngle = std::cos(angle);
		float sinAngle = std::sin(angle);

		// Rotate the unit direction vector around the player's position
		sf::Vector2f rotatedDirection;
		rotatedDirection.x = cosAngle * unitDirection.x - sinAngle * unitDirection.y;
		rotatedDirection.y = sinAngle * unitDirection.x + cosAngle * unitDirection.y;
		sf::Vector2f rayEndPosition = playerPosition + rotatedDirection * directionLength;

		rays[i][0].position = playerPosition;
		rays[i][1].position = rayEndPosition;
		rays[i][0].color = sf::Color::Green;
		rays[i][1].color = sf::Color::Green;
	}


}