#pragma once
#include <SFML/Graphics.hpp>
class Ray
{
public:
	Ray();
	~Ray();


	void drawray(sf::RenderWindow& window);
	void setOrigin(const sf::Vector2f& pos);
	void setDirection(sf::Vector2f direction);
	void resetRay();
	//sets the endpoint if closer than prev
	void findCollision(sf::Vector2f p3, sf::Vector2f p4);
	void updateLine();
private:
	sf::Vector2f position;
	sf::Vector2f direction;
	sf::Vector2f endPoint;
	sf::Vector2f shortestEndPoint;

	sf::Vertex line[2];

	//TODO make based on chosen resolution
	float magnitude = 1200.0f;
	float currentMag;
};

