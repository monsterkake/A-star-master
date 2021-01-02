#include "Map.h"

Node::Node()
{
	this->value = INF;
	this->isObsticle = false;
	this->isStart = false;
	this->isFinish = false;
	this->isTested = false;
	this->isPathPart = false;
};

Map::Map(int size)
{

	this->size = size;
	nodes.clear();

	for (int i = 0; i < size; i++)
	{

		vector<Node*> tempNodeVector;
		for (int j = 0; j < size; j++)
		{
			Node* tempNode = new Node();
			if (tiles[i][j] == OBSTICLE)
				tempNode->isObsticle = true;
			else if (tiles[i][j] == START)
			{
				tempNode->isStart = true;
				tempNode->value = 0;
				this->startPoint = { i,j };
			}
			else if (tiles[i][j] == FINISH)
			{
				tempNode->isFinish = true;
				this->finishPoint = { i,j };
			}
			tempNodeVector.push_back(tempNode);
		}
		this->nodes.push_back(tempNodeVector);
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i - 1 >= 0 && !(this->nodes[i - 1][j]->isObsticle))
				this->nodes[i][j]->neighbours.push_back(this->nodes[i - 1][j]);

			if (i + 1 < size && !(this->nodes[i + 1][j]->isObsticle))
				this->nodes[i][j]->neighbours.push_back(this->nodes[i + 1][j]);

			if (j - 1 >= 0 && !(this->nodes[i][j - 1]->isObsticle))
				this->nodes[i][j]->neighbours.push_back(this->nodes[i][j - 1]);

			if (j + 1 < size && !(this->nodes[i][j + 1]->isObsticle))
				this->nodes[i][j]->neighbours.push_back(this->nodes[i][j + 1]);
		}
	}
};

void Map::show()
{
	cout << "-------------------------------------------------------------------" << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (this->nodes[i][j]->isObsticle)
				cout << "X" << "\t";
			else if (this->nodes[i][j]->isPathPart)
				cout << "+" << "\t";
			else
				//cout << " " << this->nodes[i][j]->value << " ";
				cout << this->nodes[i][j]->value << "\t";
		}
		cout << endl;
	}
	cout << "-------------------------------------------------------------------" << endl;
}

Map::~Map()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			delete this->nodes[i][j];
		}
	}
}

void Map::setValues()
{
	bool done = false;
	while (!done)
	{
		for (int i = 0; i < this->size; i++)
		{
			for (int j = 0; j < this->size; j++)
			{
				for (int k = 0; k < this->nodes[i][j]->neighbours.size(); k++)
				{
					if (this->nodes[i][j]->neighbours[k]->value > this->nodes[i][j]->value)
					{
						this->nodes[i][j]->neighbours[k]->value = this->nodes[i][j]->value + 1;
					}
				}
			}
		}
		//this_thread::sleep_for(std::chrono::seconds(1));

		if (this->nodes[this->finishPoint[0]][this->finishPoint[1]]->value < INF)
		{
			//this->show();
			done = true;
		}
	}
}