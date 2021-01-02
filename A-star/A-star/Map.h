#pragma once

#include <iostream>
#include <vector>
#include <thread>

using namespace std;

constexpr auto INF = 99999;;
constexpr auto SPACE = 0;;
constexpr auto OBSTICLE = 1;;
constexpr auto START = 2;;
constexpr auto FINISH = 3;;

class Node
{
public:
	int value;
	bool isObsticle;
	bool isStart;
	bool isFinish;
	bool isTested;
	bool isPathPart;
	vector<Node*> neighbours;

	Node();
};


class Map
{
public:
	vector<vector<Node*>> nodes;
	const vector<vector<int>> tiles =
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,3},
		{0,1,1,1,1,1,1,1,1,1},
		{0,1,0,0,0,1,0,0,0,0},
		{0,1,0,1,0,1,0,1,0,0},
		{0,1,0,1,0,0,0,1,1,1},
		{0,0,0,1,1,1,0,0,0,2},
	};
	vector<int> startPoint = { 0,0 };
	vector<int> finishPoint = { 0,0 };

	int size;
	Map(int size);

	void setValues();

	void show();

	~Map();

private:
};