#pragma once
#include <vector>

class Map2D
{
private:

	struct Map2DPointData
	{
		float xStart, yStart;
		float xEnd, yEnd;
	};

private:
	struct Grid
	{
		bool topWall;
		bool bottomWall;
		bool leftWall;
		bool rightWall;
	};
	int* set;
	int find(int x) const;
	int findCompress(int x);
	int height(int x) const;
	void unionSetsRank(int root1, int root2);

public:
	Map2D();
	~Map2D();
	std::vector<Map2DPointData> GenerateMaze(int height, int width);
};