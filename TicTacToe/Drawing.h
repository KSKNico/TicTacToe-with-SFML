#pragma once
#ifndef DRAWING_H
#define DRAWING_H

#include <SFML/Graphics.hpp>
class Game;

class Drawing {
public:
	sf::RenderWindow &window;
	Game &game;
	sf::Texture circle;
	sf::Texture cross;
	sf::Text winText;
	sf::Font font;
	sf::RectangleShape rectangleButton;
	sf::Text resetText;

	Drawing(sf::RenderWindow &window, Game &game);

	void const drawGrid();

	void printWinnerText();

	void drawButton() const;

	bool checkForClick(sf::Vector2f mousePosition);
};
#endif
