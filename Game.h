#pragma once
#ifndef Game_H
#define Game_H
#include <SFML/Graphics.hpp>

class Game : public sf::Drawable, public sf::Transformable {
public:

	void printWorld(sf::Vector2f position);

	void update();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::VertexArray m_vertices;
	int windowHeight = 600;
	int windowWidth = 600;
	int pixelMap[600 * 600];

	void vertex2d();

	int numberNeighbours(int x, int y);

	int goNextGen(int x, int y);

	
};

#endif
