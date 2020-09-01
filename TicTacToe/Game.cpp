#include "Game.h"
#include "Drawing.h"
#include <assert.h>
#include <array>
#include <vector>
#include <cmath>


Game::Game(int x, int y, int squareSize, int padding, int t_winCondition) : x{ x }, y{ y }, padding{ padding }, squareSize{ squareSize } {
	assert(t_winCondition <= x && t_winCondition <= y);
	winCondition = t_winCondition;

	// player1 -> 1
	// player2 -> 2
	currentPlayer = 1;
	win = 0;

	// Calculate resolution based on the dimensions of the grid
	xResolution = padding * 2 + x * squareSize;
	yResolution = padding * 2 + y * squareSize;

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			tiles.push_back(
				Game::tile{
					std::array<int, 2> {i, j},
					0,
					std::array<float,2> {padding + squareSize * i + (float)squareSize / 2, padding + squareSize * j + (float)squareSize / 2},
					std::array<int,2> {padding + squareSize * i, padding + squareSize * j}
				}
			);
		}
	}
}

void Game::update(sf::Vector2i cords) {
	float max_distance = INFINITY;
	Game::tile *selected = nullptr;
	for (auto &tile : tiles) {
		float distance = calculateDistance((float)cords.x, tile.middlePoint[0], (float)cords.y, tile.middlePoint[1]);
		if (calculateDistance((float)cords.x, tile.middlePoint[0], (float)cords.y, tile.middlePoint[1]) < max_distance) {
			selected = &tile;
			max_distance = distance;
		}
	}


	if (selected->player == 0) {
		// claim tile for the currentPlayer
		selected->player = currentPlayer;
	}

	// switch current player around
	if (currentPlayer == 1) {
		currentPlayer = 2;
	}
	else {
		currentPlayer = 1;
	}

	// check for a winner
	checkForWinner();
}

void Game::checkForWinner() {
	int player1;
	int player2;

	// check for draw
	win = 3;
	for (auto tile : tiles) {
		if (tile.player == 0)
			win = 0;
	}

	//horizontal wins
	for (int i = 0; i < x; i++) {
		player1 = 0;
		player2 = 0;
		for (int j = 0; j < y; j++) {
			if (tiles[i+j*y].player == 1) {
				player2 = 0;
				player1++;
			}
			else if (tiles[i+j*y].player == 2) {
				player1 = 0;
				player2++;
			}
			else {
				player1 = 0;
				player2 = 0;
			}

			if (player1 >= winCondition || player2 >= winCondition) {
				win = player1 > player2 ? 1 : 2;
			}
		}
	}

	//verticle wins
	for (int i = 0; i < x; i++) {
		player1 = 0;
		player2 = 0;
		for (int j = 0; j < y; j++) {
			if (tiles[j+i*y].player == 1) {
				player2 = 0;
				player1++;
			}
			else if (tiles[j+i*y].player == 2) {
				player1 = 0;
				player2++;
			}
			else {
				player1 = 0;
				player2 = 0;
			}

			if (player1 >= winCondition || player2 >= winCondition) {
				win = player1 > player2 ? 1 : 2;
			}
		}
	}

	int a = 0;
	int b = 0;
	//diagonal from top left to bottom right for y = 0
	for (int i = 0; i < x; i++) {
		player1 = 0;
		player2 = 0;
		a = i;
		b = 0;
		while (a < x && b < y) {
			if (tiles[a*y + b].player == 1) {
				player2 = 0;
				player1++;
			}
			else if (tiles[a*y + b].player == 2) {
				player1 = 0;
				player2++;
			}
			else {
				player1 = 0;
				player2 = 0;
			}
			if (player1 >= winCondition || player2 >= winCondition) {
				win = player1 > player2 ? 1 : 2;
			}
			a++;
			b++;
		}
	}

	//diagonal from top left to bottom right for x = 0
	for (int i = 0; i < y; i++) {
		player1 = 0;
		player2 = 0;
		a = 0;
		b = i;
		while (a < x && b < y) {
			if (tiles[a*y + b].player == 1) {
				player2 = 0;
				player1++;
			}
			else if (tiles[a*y + b].player == 2) {
				player1 = 0;
				player2++;
			}
			else {
				player1 = 0;
				player2 = 0;
			}
			if (player1 >= winCondition || player2 >= winCondition) {
				win = player1 > player2 ? 1 : 2;
			}
			a++;
			b++;
		}
	}

	//diagonal from top right to bottom left for y = 0
	for (int i = 0; i < x; i++) {
		player1 = 0;
		player2 = 0;
		a = i;
		b = 0;
		while (a < x && b < y && a >= 0 && b >= 0) {
			if (tiles[a*y + b].player == 1) {
				player2 = 0;
				player1++;
			}
			else if (tiles[a*y + b].player == 2) {
				player1 = 0;
				player2++;
			}
			else {
				player1 = 0;
				player2 = 0;
			}
			if (player1 >= winCondition || player2 >= winCondition) {
				win = player1 > player2 ? 1 : 2;
			}
			a--;
			b++;
		}
	}

	//diagonal from top right to bottom left for x = x
	for (int i = 0; i < y; i++) {
		player1 = 0;
		player2 = 0;
		a = x;
		b = i;
		while (a < x && b < y && a >= 0 && b >= 0) {
			if (tiles[a*y + b].player == 1) {
				player2 = 0;
				player1++;
			}
			else if (tiles[a*y + b].player == 2) {
				player1 = 0;
				player2++;
			}
			else {
				player1 = 0;
				player2 = 0;
			}
			if (player1 >= winCondition || player2 >= winCondition) {
				win = player1 > player2 ? 1 : 2;
			}
			a--;
			b++;
		}
	}
}

float calculateDistance(float x1, float x2, float y1, float y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void Game::reset() {
	tiles.clear();
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			tiles.push_back(
				Game::tile{
					std::array<int, 2> {i, j},
					0,
					std::array<float,2> {padding + squareSize * i + (float)squareSize / 2, padding + squareSize * j + (float)squareSize / 2},
					std::array<int,2> {padding + squareSize * i, padding + squareSize * j}
				}
			);
		}
	}
	if (win == 1) {
		currentPlayer = 2;
	}
	else {
		currentPlayer = 1;
	}
	win = 0;

}
