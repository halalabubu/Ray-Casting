#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#include "ray.h"
#include "wall.h"

const int WIDTH = 1920;
const int HEIGHT = 1080;
const float CIRCLESIZE = 10.0f;
const int rayCount = 500;
const int randWalls = 8;


int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "2D Ray Casting");
	window.setFramerateLimit(144);



	//create point
	sf::CircleShape shape(CIRCLESIZE);
	shape.setOrigin(CIRCLESIZE, CIRCLESIZE);
	shape.setPosition(sf::Vector2f(WIDTH / 2, HEIGHT / 2));
	shape.setFillColor(sf::Color::Red);

	//create rays
	Ray ray[rayCount];
	for (size_t i = 0; i < rayCount; i++)
	{
		float increments = 360.0f / static_cast<float>(rayCount);
		//convert from degrees to radians
		increments = increments * 3.14159 / 180;

		sf::Vector2f temp;
		ray[i].setOrigin(shape.getPosition());

		temp.x = cos(increments * i);
		temp.y = sin(increments * i);
		ray[i].setDirection(temp);

	}



	//create object // allow creation though imgui
	Wall wall;
	std::vector<Wall> walls;

	//wall.setPoints(sf::Vector2f(400, 200), sf::Vector2f(300, 900));
	//walls.push_back(wall);
	//wall.setPoints(sf::Vector2f(1800, 50), sf::Vector2f(1600, 900));
	//walls.push_back(wall);
	//wall.setPoints(sf::Vector2f(80, 50), sf::Vector2f(1000, 200));
	//walls.push_back(wall);
	
	srand(30);
	for (size_t i = 0; i < randWalls; i++)
	{
		wall.setPoints(sf::Vector2f(rand() % WIDTH, rand() % HEIGHT), 
			sf::Vector2f(rand() % WIDTH, rand() % HEIGHT));
		walls.push_back(wall);
	}




	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//get mouse pos
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		//convert to worldspace
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

		shape.setPosition(worldPos);



		for (size_t i = 0; i < rayCount; i++)
		{
			//set ray origin to cuurent pos
			ray[i].setOrigin(shape.getPosition());
			//reset ray
			ray[i].resetRay();

			//calc ray interections
			for (size_t j = 0; j < walls.size(); j++)
				ray[i].findCollision(walls[j].getpoints()[0].position, walls[j].getpoints()[1].position);

			//use closest intersection set magnitude or pos
			ray[i].updateLine();
		}








		window.clear();
		for (size_t i = 0; i < rayCount; i++)
			ray[i].drawray(window);

		for (size_t i = 0; i < walls.size(); i++)
			walls[i].drawline(window);

		window.draw(shape);
		window.display();
	}

	return 0;
}