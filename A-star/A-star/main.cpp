#include "Map.h"
#include "SFML\Graphics.hpp"
#include "SFML\OpenGL.hpp"

void algorithm(Map& map)
{
	bool done = false;
	vector<Node*> path;
	path.push_back(map.nodes[map.startPoint[0]][map.startPoint[1]]);

	while (!done)
	{

		int bestNeighbour = -1;
		for (int i = 0; i < (path[path.size() - 1]->neighbours.size()); i++)
		{
			if (path[path.size() - 1]->neighbours[i]->value > path[path.size() - 1]->value && !path[path.size() - 1]->neighbours[i]->isTested)
			{
				bestNeighbour = i;
			}
		}
		if (bestNeighbour >= 0)
			path.push_back(path[path.size() - 1]->neighbours[bestNeighbour]);
		else
		{
			path[path.size() - 1]->isTested = true;
			path.pop_back();
		}

		if (path.size() == 0)
			path.push_back(map.nodes[map.startPoint[0]][map.startPoint[1]]);
		else
		{
			if (path[path.size() - 1]->isFinish)
			{
				done = true;
			}
			else if (path[path.size() - 1]->value > map.nodes[map.finishPoint[0]][map.finishPoint[1]]->value)
			{
				path[path.size() - 1]->isTested = true;
				path.pop_back();
			}
		}
		/*
		cout << "-------------------------------------------------------------------" << endl;
		for (int i = 0; i < path.size(); i++)
		{
			cout << path[i]->value << "  ";
		}
		cout << "-------------------------------------------------------------------" << endl;
		*/
	}
	for (int i = 0; i < path.size(); i++)
	{
		path[i]->isPathPart = true;
	}
}

class Program 
{
	sf::RenderWindow window;
	sf::Event event;
	Map *map;
public:
	Program() 
	{
		this->map = new Map(10);
		//this->map->setValues();
		//algorithm(*map);
	}
	void updateMap() 
	{
		for (int i = 0; i < map->size; i++)
		{
			for (int j = 0; j < map->size; j++)
			{
				map->nodes[i][j]->isPathPart = false;
				map->nodes[i][j]->isTested = false;
				map->nodes[i][j]->value = INF;
				map->nodes[map->startPoint[0]][map->startPoint[1]]->value = 0;
			}
		}
		this->map->setValues();
		algorithm(*map);
	}

	void render()
	{
		drawMap();
	}

	void drawMap()
	{
		sf::RectangleShape tile;
		tile.setSize(sf::Vector2f(window.getSize().x / map->size, window.getSize().x / map->size));
		window.clear();
		for (int i = 0; i < map->size; i++)
		{
			for (int j = 0; j < map->size; j++)
			{
				tile.setPosition(window.getSize().x / map->size * j, window.getSize().x / map->size * i);
				if (map->nodes[i][j]->isObsticle)
				{
					tile.setFillColor(sf::Color::Red);
					window.draw(tile);
				}
				else if (map->nodes[i][j]->isPathPart)
				{
					tile.setFillColor(sf::Color::Blue);
					window.draw(tile);
				}
				else
				{
					tile.setFillColor(sf::Color::Black);
					window.draw(tile);
				}
			}
		}
		tile.setPosition(window.getSize().x / map->size * map->finishPoint[1], window.getSize().x / map->size * map->finishPoint[0]);
		tile.setFillColor(sf::Color::Green);
		window.draw(tile);
		tile.setPosition(window.getSize().x / map->size * map->startPoint[1], window.getSize().x / map->size * map->startPoint[0]);
		tile.setFillColor(sf::Color::Yellow);
		window.draw(tile);

		window.display();
	}

	void handleEvents()
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2i mPos = sf::Mouse::getPosition(window);
					int mPosx = sf::Mouse::getPosition(window).x / map->size;
					int mPosy = sf::Mouse::getPosition(window).y / map->size;
					if ((mPos.x / (window.getSize().x / map->size) < map->size) &&
						(mPos.y / (window.getSize().x / map->size) < map->size) &&
						(mPos.x / (window.getSize().x / map->size) >= 0) &&
						(mPos.y / (window.getSize().x / map->size) >= 0)) 
					{
						if(!map->nodes[mPos.y / (window.getSize().x / map->size)][mPos.x / (window.getSize().x / map->size)]->isStart &&
							!map->nodes[mPos.y / (window.getSize().x / map->size)][mPos.x / (window.getSize().x / map->size)]->isFinish
							)
						map->nodes[mPos.y / (window.getSize().x / map->size)][mPos.x / (window.getSize().x / map->size)]->isObsticle =
						!map->nodes[mPos.y / (window.getSize().x / map->size)][mPos.x / (window.getSize().x / map->size)]->isObsticle;
					}
				}
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Q)
					window.close();
				break;

			default: break;
			}
		}
	}

	void loop()
	{
		while (window.isOpen()) 
		{
			render();
			handleEvents();
			updateMap();
		}
	}

	void init()
	{
		window.create(sf::VideoMode(500, 600), "main");
		window.setFramerateLimit(60);
	}
};

int main()
{
	Program prog;
	prog.init();
	
	//Map map(10);
	//map.setValues();
	//algorithm(map);
	//prog.createMap();
	prog.loop();
	//system("pause");
}

