#pragma once
#include <SFML/Graphics.hpp>
class Wall
{
public:
	Wall();
	~Wall();
	void setPoints(sf::Vector2f p1, sf::Vector2f p2);
	void drawline(sf::RenderWindow& window);
	sf::Vertex* getpoints();

private:
	sf::Vertex line[2];

};

