#include "Map.h"
#include <random>
Map2D::Map2D()
{
}

Map2D::~Map2D()
{
}

int Map2D::find(int x) const
{
	if (set[x] < 0)
	{
		return x;
	}
	else
	{
		return find(set[x]);
	}
}

int Map2D::findCompress(int x)
{
	if (set[x] < 0)
	{
		return x;
	}
	else
	{
		return set[x] = findCompress(set[x]);
	}
}

int Map2D::height(int x) const
{
	return set[find(x)];
}

void Map2D::unionSetsRank(int root1, int root2)
{
	if (height(root1) <= height(root2))
	{
		if (height(root1) == height(root2))
		{
			set[root1]--;
		}
		set[root2] = root1;
	}
	else
	{
		set[root1] = root2;
	}
}
std::vector<Map2D::Map2DPointData> Map2D::GenerateMaze(int height, int width)
{
	/*Setup*/
	std::vector<Map2DPointData> dataPoints;
	set = new int[height*width];
	for (int i = 0; i < height*width; i++)
		set[i] = -1;

	Grid** mapGrid = new Grid*[height];
	for (int i = 0; i < height; i++)
	{
		mapGrid[i] = new Grid[width];
		for (int j = 0; j < width; j++)
		{
			mapGrid[i][j].bottomWall = true;
			mapGrid[i][j].topWall = true;
			mapGrid[i][j].leftWall = true;
			mapGrid[i][j].rightWall = true;
		}
	}
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, height*width - 1);
	/*Create the maze*/
	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	int roomsYetToBecombined = width*height;
	int gridCell1;
	int gridCell2;
	int numberOfCells = width*height - 1; //(0 -> width*height - 1)
	Direction direction;
	do
	{
		bool changed = false;
		gridCell1 = distribution(generator);
		direction = Direction(rand() % 4);
		switch (direction)
		{
		case UP:
			if (gridCell1 - width > 0)
			{
				gridCell2 = gridCell1 - width;
				changed = true;
			}
			break;
		case DOWN:
			if (gridCell1 + width < numberOfCells)
			{
				gridCell2 = gridCell1 + width;
				changed = true;
			}
			break;
		case LEFT:
			if (gridCell1 != 0 && (gridCell1 % width != 0))
			{
				gridCell2 = gridCell1 - 1;
				changed = true;
			}
			break;
		case RIGHT:

			if (gridCell1 != numberOfCells && ((gridCell1 + 1) % width != 0))
			{
				gridCell2 = gridCell1 + 1;
				changed = true;
			}
			break;
		}
		if (changed)
		{
			int root1 = findCompress(gridCell1);
			int root2 = findCompress(gridCell2);
			if (root1 != root2)
			{
				unionSetsRank(root1, root2);

				int gridCell1X = gridCell1 / width;
				int gridCell1Y = gridCell1 % width;
				int gridCell2X = gridCell2 / width;
				int gridCell2Y = gridCell2 % width;
				switch (direction)
				{
				case UP:
					mapGrid[gridCell1X][gridCell1Y].topWall = false;
					mapGrid[gridCell2X][gridCell2Y].bottomWall = false;
					break;
				case DOWN:
					mapGrid[gridCell1X][gridCell1Y].bottomWall = false;
					mapGrid[gridCell2X][gridCell2Y].topWall = false;

					break;
				case LEFT:
					mapGrid[gridCell1X][gridCell1Y].leftWall = false;
					mapGrid[gridCell2X][gridCell2Y].rightWall = false;

					break;
				case RIGHT:
					mapGrid[gridCell1X][gridCell1Y].rightWall = false;
					mapGrid[gridCell2X][gridCell2Y].leftWall = false;

					break;
				}

				roomsYetToBecombined--;
			}
		}
	} while (roomsYetToBecombined != 1);

	/*Create the datapoints for the map*/
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (mapGrid[i][j].topWall)
			{
				Map2DPointData toAdd;
				toAdd.xStart = j;
				toAdd.xEnd = j + 1;
				toAdd.yStart = i;
				toAdd.yEnd = i;
				dataPoints.push_back(toAdd);
			}
			if (mapGrid[i][j].bottomWall)
			{
				Map2DPointData toAdd;
				toAdd.xStart = j;
				toAdd.xEnd = j + 1;
				toAdd.yStart = i + 1;
				toAdd.yEnd = i + 1;
				dataPoints.push_back(toAdd);
			}
			if (mapGrid[i][j].leftWall)
			{
				Map2DPointData toAdd;
				toAdd.xStart = j;
				toAdd.xEnd = j;
				toAdd.yStart = i;
				toAdd.yEnd = i + 1;
				dataPoints.push_back(toAdd);
			}
			if (mapGrid[i][j].rightWall)
			{
				Map2DPointData toAdd;
				toAdd.xStart = j + 1;
				toAdd.xEnd = j + 1;
				toAdd.yStart = i;
				toAdd.yEnd = i + 1;
				dataPoints.push_back(toAdd);
			}
		}
	}

	/*Cleaning up*/
	delete[] set;

	for (int i = 0; i < height; i++)
	{
		delete[] mapGrid[i];
	}
	delete[] mapGrid;

	return dataPoints;
}