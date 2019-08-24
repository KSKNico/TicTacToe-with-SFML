#pragma once
#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <array>


class Game {
public:
	int x;
	int y;
	int squareSize;
	int padding;
	int winCondition;
	int xResolution;
	int yResolution;
	int currentPlayer;
	int win;
	struct tile {
		std::array<int, 2> cords;
		int player;
		std::array<float, 2> middlePoint;
		std::array<int, 2> edgePoint;
	};
	std::vector<tile> tiles;

	Game(int x, int y, int squareSize, int padding, int t_winCondition);

	void update(sf::Vector2i cords);

	void checkForWinner();

};

float calculateDistance(float x1, float x2, float y1, float y2);

#endif