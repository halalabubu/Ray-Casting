#include "ray.h"

void Ray::drawray(sf::RenderWindow& window) {
	window.draw(line, 2, sf::Lines);
}

void Ray::setOrigin(const sf::Vector2f& pos)
{
	position = pos;
}
void Ray::setDirection(sf::Vector2f direction)
{
	this->direction = direction;
}
void Ray::resetRay()
{
	sf::Vector2f p2;
	p2.x = magnitude * direction.x + position.x;
	p2.y = magnitude * direction.y + position.y;
	line[1] = p2;
	line[0] = position;

	shortestEndPoint = p2;
	currentMag = magnitude;
}
//make it use closer endpoint
void Ray::findCollision(sf::Vector2f p1, sf::Vector2f p2)
{
	sf::Vector2f p3 = line[0].position;
	sf::Vector2f p4 = line[1].position;
	//https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
	//Given two points on each line segment
	float numerator = (p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x);
	float denominator = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
	float t = numerator / denominator;

	float numeratorU = (p1.x - p3.x) * (p1.y - p2.y) - (p1.y - p3.y) * (p1.x - p2.x);
	float u = numeratorU / denominator;



	if (0 <= t && t <= 1 && 0 <= u && u <= 1)
	{

		sf::Vector2f intersection;
		intersection.x = p1.x + t * (p2.x - p1.x);
		intersection.y = p1.y + t * (p2.y - p1.y);

		float x = pow(position.x - intersection.x, 2);
		float y = pow(position.y - intersection.y, 2);
		float newMag = sqrt(x + y);

		//if magnitude is smaller use new value
		if (newMag < currentMag)
		{
			currentMag = newMag;
			shortestEndPoint = intersection;
		}
	}


}
void Ray::updateLine()
{
	line[1] = shortestEndPoint;
}
Ray::Ray()
{
}

Ray::~Ray()
{
}