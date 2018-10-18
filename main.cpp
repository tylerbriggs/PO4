/*
Tyler Briggs
Program 3
2143 OOP

purpose of this program is to creat John Conways game of life
right clich to give life to new cell. Left click to play
refrences:
replit.com/TerryGriffin
https://gamedevelopment.tutsplus.com/tutorials/creating-life-conways-game-of-life--gamedev-558
sfml.com
^^sorry can give derict url. spent a lot of time on turtorial.
https://www.youtube.com/watch?v=WVCM3Rv4VV8

GitHub:TylerBriggs
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

int main() {
	//Game g(600, 600); // create with some window size

	//g.draw();
	//g.run(388); // run for 1000 generations.
	//g.printWorld("outfilename.txt");
	//I thouht i could make a draw function to subsitute for the input file
	//I was in over my head. this creats window then runs till end using sfml classes.

		// create the window
		sf::RenderWindow window(sf::VideoMode(600, 600), "Particles");
		Game g;

		// time between updates and set clock
		sf::Clock clock;
		sf::Time updateSpace = sf::seconds(.75);
		bool startTimer = false;
		// Start main game loop
		while (window.isOpen()) {

			// handle events
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}

			// If left mouse is pressed add live cells to the vertexArray
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i mouse = sf::Mouse::getPosition(window);
				g.printWorld(window.mapPixelToCoords(mouse));
			}

			// If the right mouse is pressed start updating
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				// make the clock to start the game
				startTimer = true;
			}

			// If the right mouse has been pressed and the time period is reached then update
			if (clock.getElapsedTime().asSeconds() >= updateSpace.asSeconds() && startTimer == true) {
				g.update();
				clock.restart();
			}

			// display grid
			window.clear();
			window.draw(g);
			window.display(); 
		}
	return 0;
}
