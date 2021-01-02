#include "Map.h"

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

int main()
{
	Map map(10);
	map.setValues();
	map.show();
	algorithm(map);
	map.show();
}

