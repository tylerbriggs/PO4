#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include "Game.h"


/**
* Function check
*   prints grid
* @param sf vector 2f
* @return void
*/
void Game::printWorld(sf::Vector2f pix_location) {
	int x = pix_location.x;
	int y = pix_location.y;
	// When a vertex is added to the vertexArray it checks if it has been added before
	if (pixelMap[goNextGen(x, y)] != 1) {
		m_vertices.append(sf::Vertex(pix_location, sf::Color::Magenta));
		pixelMap[goNextGen(x, y)] = 1;
	}
}
/**
* Function check
*  runs through rules and acts accordingly
* @param none
* @return none
*/
void Game::update() {
	m_vertices.clear();
	for (int i = 0; i < windowHeight; i++) {
		for (int j = 0; j < windowWidth; j++) {
			int numOfNeighbours = numberNeighbours(j, i);
			// If the cell is alive check these:
			if (pixelMap[goNextGen(j, i)] == 1) {
				if (numOfNeighbours < 2 || numOfNeighbours > 3) {
					// Cell dead don't create vertex
				}
				else if (numOfNeighbours == 2 || numOfNeighbours == 3) {
					// Cell is alive birth
					m_vertices.append(sf::Vertex(sf::Vector2f(j, i), sf::Color::Magenta));
				}
			}
			// If the cell is dead:
			else {
				if (numOfNeighbours == 3) {
					// Make the cell alive
					m_vertices.append(sf::Vertex(sf::Vector2f(j, i), sf::Color::Magenta));
				}
			}
		}
	}
	vertex2d();
}
/**
* Function check
*   clears grid. adds each value to grid
* @param {int} size : initial size of vector
* @return void
*/
void Game::vertex2d() {
	// clears pixelMap
	std::memset(pixelMap, 0, sizeof(pixelMap));
	// Add each value from vertexArray back into grid
	for (int i = 0; i < m_vertices.getVertexCount(); i++) {
		int x = m_vertices[i].position.x;
		int y = m_vertices[i].position.y;
		pixelMap[goNextGen(x, y)] = 1;
	}
}
/**
* Function check
*   change the x, y coordinates to a single index
* @param {int} size : initial size of vector
* @return void
*/

int Game::goNextGen(int x, int y) {
	int index = ((y * windowHeight) - 1) + (x + 1);
	return index;
}

/**
* Function check
*   checks neighbors
* @param {int} x,y from 2d
* @return int number of neighbors
*/
int Game::numberNeighbours(int x, int y) {
	int numberOfNeighbours = 0;
	
	bool yUp = false;
	bool yDown = false;
	bool xUp = false;
	bool xDown = false;

	// check if the values are in the array range
	if (x + 1 > windowWidth) {
		xUp = true;
	}

    if (y + 1 > windowHeight) {
	    yUp = true;
    }

	if (x - 1 < 0) {
		xDown = true;
	}

	if (y - 1 < 0) {
		yDown = true;
	}

	// check and count neighbors
	
	if (pixelMap[goNextGen(x - 1, y - 1)] == 1 && xDown == false && yDown == false) {
		numberOfNeighbours ++;
	}
	if (pixelMap[goNextGen(x, y - 1)] == 1 && yDown == false) {
		numberOfNeighbours ++;
	}
	if (pixelMap[goNextGen(x + 1, y - 1)] == 1 && xUp == false && yDown == false) {
		numberOfNeighbours ++;
	}

	if (pixelMap[goNextGen(x - 1, y + 1)] == 1 && xDown == false && yUp == false) {
		numberOfNeighbours ++;
	}
	if (pixelMap[goNextGen(x - 1, y)] == 1 && xDown == false) {
		numberOfNeighbours ++;
	}
	if (pixelMap[goNextGen(x + 1, y)] == 1 && xUp == false) {
		numberOfNeighbours ++;
	}
	if (pixelMap[goNextGen(x + 1, y + 1)] == 1 && yUp == false && xUp == false) {
		numberOfNeighbours ++;
	}
	if (pixelMap[goNextGen(x, y + 1)] == 1 && yUp == false) {
		numberOfNeighbours ++;
	}
	return numberOfNeighbours;
}

/**
* Function draw 
* refrence from sfml 
* lets user play god in the game of life
* @param sf target,and states
* @return none
*/
void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// our particles don't use a texture
	states.texture = NULL;
	// draw the vertex array
	target.draw(m_vertices, states);
	// apply the transform
	states.transform *= getTransform();
}
