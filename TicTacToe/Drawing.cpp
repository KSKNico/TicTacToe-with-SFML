#include "Drawing.h"
#include "Game.h"

Drawing::Drawing(sf::RenderWindow &window, Game &game): window { window }, game{ game } {
	circle.loadFromFile("assets/textures/circle.png");
	cross.loadFromFile("assets/textures/cross.png");
	cross.setSmooth(true);
	circle.setSmooth(true);

	font.loadFromFile("assets/fonts/arial.ttf");
	winText.setFont(font);
	winText.setStyle(sf::Text::Bold);
	winText.setCharacterSize(50);

	rectangleButton.setSize(sf::Vector2f(100, 30));
	rectangleButton.setPosition(sf::Vector2f(5, game.yResolution - 30 - 5));
	rectangleButton.setFillColor(sf::Color::Black);

	resetText.setPosition(sf::Vector2f(5, game.yResolution - 30 - 5));
	resetText.setFont(font);
	resetText.setString("RESET");
	resetText.setFillColor(sf::Color::Yellow);
}

void const Drawing::drawGrid() {
	sf::VertexArray line(sf::Lines, 2);
	// define colors
	line[0].color = sf::Color::White;
	line[1].color = sf::Color::White;

	// draw all verticle lines
	for (int i = 1; i < game.x; i++) {
		line[0].position = sf::Vector2f(game.padding + i * game.squareSize, game.padding);
		line[1].position = sf::Vector2f(game.padding + i * game.squareSize, game.yResolution - game.padding);
		window.draw(line);
	}

	// draw all horizontal lines
	for (int i = 1; i < game.y; i++) {
		line[0].position = sf::Vector2f(game.padding, game.padding + i * game.squareSize);
		line[1].position = sf::Vector2f(game.xResolution - game.padding, game.padding + i * game.squareSize);
		window.draw(line);
	}
	

	for (Game::tile &tile : game.tiles) {
		sf::Sprite sprite;
		if (tile.player == 1) {
			sprite.setTexture(cross);
		}
		else if (tile.player == 2) {
			sprite.setTexture(circle);
		}
		sprite.setScale((game.squareSize-2) / 300.0f, (game.squareSize-2) / 300.0f);
		sprite.setPosition(sf::Vector2f(tile.edgePoint[0], tile.edgePoint[1]));
		window.draw(sprite);
	}
}

void Drawing::printWinnerText() {
	if (game.win == 1) {
		winText.setFillColor(sf::Color::Red);
		winText.setString("Cross wins!");
	}
	else if (game.win == 2) {
		winText.setFillColor(sf::Color::Blue);
		winText.setString("Circle wins!");
	}
	else if (game.win == 3) {
		winText.setFillColor(sf::Color::Yellow);
		winText.setString("Draw!");
	}
	// winText.setPosition(sf::Vector2f(10.0f, 10.0f));
	window.draw(winText);
}

void Drawing::drawButton() const {
	window.draw(rectangleButton);
	window.draw(resetText);
}

bool Drawing::checkForClick(sf::Vector2f mousePosition) {
	sf::Vector2f topLeft = rectangleButton.getPosition();
	sf::Vector2f bottomRight = rectangleButton.getSize() + topLeft;

	return (mousePosition.x > topLeft.x && mousePosition.y > topLeft.y && mousePosition.x < bottomRight.x && mousePosition.y < bottomRight.y);
}

