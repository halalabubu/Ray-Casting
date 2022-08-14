#include "wall.h"

void Wall::drawline(sf::RenderWindow& window) {
	window.draw(line, 2, sf::Lines);
}
sf::Vertex* Wall::getpoints()
{
	return line;
}
Wall::Wall()
{
}

Wall::~Wall()
{
}

void Wall::setPoints(sf::Vector2f p1, sf::Vector2f p2)
{
	line[0] = p1;
	line[1] = p2;
}
