#pragma once
#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>

class Grid {
	int x;
	int y;
	int padding;

	Grid(int x, int y, int padding);

	void const drawGrid(sf::RenderWindow &window);
};

#endif
