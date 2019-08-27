#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Drawing.h"
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

std::map<std::string, int> readConfig(std::string pathToConfig) {
	std::map<std::string, int> configs;
	std::fstream fileStream;
	fileStream.open(pathToConfig, std::ios::in);

	std::string line;
	while (std::getline(fileStream, line))
	{
		std::istringstream is_line(line);
		std::string key;
		if (std::getline(is_line, key, '='))
		{
			std::string value;
			if (std::getline(is_line, value))
				configs.insert(std::pair <std::string,int> (key, std::stoi(value)));
		}
	}
	return configs;
}

int main() {
	std::map<std::string, int> config = readConfig("./config.cfg");
	Game game { config["x"], config["y"], config["tileSize"], config["padding"], config["winningNumber"] };
	sf::RenderWindow window(sf::VideoMode(game.xResolution, game.yResolution), "Tic Tac Toe");
	Drawing drawing{ window, game };
	int win = 0;
	bool updated = true;
	bool endDrawn = false;
	while (window.isOpen())
	{
		// Event processing
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Request for closing the window
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				endDrawn = false;
				if (game.win == 0) {
					game.update(sf::Mouse::getPosition(window));
					updated = true;
				}
				else {
					if(drawing.checkForClick((sf::Vector2f)sf::Mouse::getPosition(window))) {
						game.reset();
						updated = true;
					}
				}
			}
		}

		// Clear the whole window before rendering a new frame
		
		if (updated) {
			window.clear();
			drawing.drawGrid();
			updated = false;
			window.display();
		}
		if (game.win != 0 && !endDrawn) {
			window.clear();
			drawing.drawGrid();
			drawing.printWinnerText();
			drawing.drawButton();
			endDrawn = true;
			window.display();
		}
		
		// End the current frame and display its contents on screen
	}
}