#include "Map.h"
#include <random>
#include <deque>
#include <unordered_map>

Map2D::Map2D()
{
	set = nullptr;
	mapGrid = nullptr;
	height = 0;
	width = 0;
}

Map2D::~Map2D()
{
	/*Cleaning up*/
	if (set)
		delete[] set;
	if (mapGrid)
	{
		for (int i = 0; i < width; i++)
		{
			delete[] mapGrid[i];
		}
		delete[] mapGrid;
		dataPoints.clear();
	}
}

int Map2D::find(int x) const
{
	if (set[x] < 0)
	{
		return x;
	}
	return find(set[x]);
}

int Map2D::findCompress(int x) const
{
	if (set[x] < 0)
	{
		return x;
	}
	return set[x] = findCompress(set[x]);
}

int Map2D::setHeight(int x) const
{
	return set[find(x)];
}

void Map2D::unionSetsRank(int root1, int root2) const
{
	if (setHeight(root1) <= setHeight(root2))
	{
		if (setHeight(root1) == setHeight(root2))
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

std::vector<Map2D::Map2DWallData>& Map2D::GenerateMaze(int height, int width)
{
	/*Cleaning up*/
	if (set)
		delete[] set;
	if (mapGrid)
	{
		for (int i = 0; i < width; i++)
		{
			delete[] mapGrid[i];
		}
		delete[] mapGrid;
		dataPoints.clear();
	}
	this->height = height; //y-coordinates
	this->width = width; //x-coordinates
	/*Setup*/
	set = new int[height * width];
	for (int i = 0; i < height * width; i++)
		set[i] = -1;

	mapGrid = new Grid*[width];
	for (int i = 0; i < width; i++)
	{
		mapGrid[i] = new Grid[height];
		for (int j = 0; j < height; j++)
		{
			mapGrid[i][j].bottomWall = true;
			mapGrid[i][j].topWall = true;
			mapGrid[i][j].leftWall = true;
			mapGrid[i][j].rightWall = true;
			mapGrid[i][j].position = std::pair<int, int>(i, j);
		}
	}
	distribution = std::uniform_int_distribution<int>(0, height * width - 1);
	distributionHeight = std::uniform_int_distribution<int>(0, height - 1);
	distributionWidth = std::uniform_int_distribution<int>(0, width - 1);
	/*Create the maze*/

	int roomsYetToBecombined = width * height;
	int numberOfCells = width * height - 1; //(0 -> width*height - 1)

	do
	{
		bool changed = false;
		int gridCell1 = distribution(generator);
		int gridCell2 = 0;
		Direction direction = Direction(rand() % 4);
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

				int gridCell1X = gridCell1 % width;
				int gridCell1Y = gridCell1 / width;
				int gridCell2X = gridCell2 % width;
				int gridCell2Y = gridCell2 / width;
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
	for (int i = 0; i < width; i++)
	{
		float xValue = float(i);
		for (int j = 0; j < height; j++)
		{
			float yValue = float(j);
			if (mapGrid[i][j].topWall)
			{
				Map2DWallData toAdd;
				toAdd.xStart = xValue;
				toAdd.xEnd = xValue + 1.0f;
				toAdd.yStart = yValue;
				toAdd.yEnd = yValue;
				dataPoints.push_back(toAdd);
			}
			if (mapGrid[i][j].bottomWall)
			{
				Map2DWallData toAdd;
				toAdd.xStart = xValue;
				toAdd.xEnd = xValue + 1.0f;
				toAdd.yStart = yValue + 1.0f;
				toAdd.yEnd = yValue + 1.0f;
				dataPoints.push_back(toAdd);
			}
			if (mapGrid[i][j].leftWall)
			{
				Map2DWallData toAdd;
				toAdd.xStart = xValue;
				toAdd.xEnd = xValue;
				toAdd.yStart = yValue;
				toAdd.yEnd = yValue + 1.0f;
				dataPoints.push_back(toAdd);
			}
			if (mapGrid[i][j].rightWall)
			{
				Map2DWallData toAdd;
				toAdd.xStart = xValue + 1.0f;
				toAdd.xEnd = xValue + 1.0f;
				toAdd.yStart = yValue;
				toAdd.yEnd = yValue + 1.0f;
				dataPoints.push_back(toAdd);
			}
		}
	}

	return dataPoints;
}

unsigned int Map2D::AddSymbol(Map2DSymbolData::Symbol symbolType, int positionX, int positionY, float sizeX, float sizeY)
{
	Map2DSymbolData toBeAdded;
	toBeAdded.typeOfSymbol = symbolType;
	toBeAdded.positionX = positionX + 0.5f;
	toBeAdded.positionY = positionY + 0.5f;
	toBeAdded.sizeX = sizeX;
	toBeAdded.sizeY = sizeY;
	toBeAdded.used = true;

	symbols.push_back(toBeAdded);

	return unsigned int(symbols.size() - 1);
}

void Map2D::MoveSymbol(unsigned int ID, int newPositionX, int newPositionY, float newSizeX, float newSizeY)
{
	auto symbol = &symbols[ID];
	symbol->positionX = newPositionX + 0.5f;
	symbol->positionY = newPositionY + 0.5f;
	symbol->sizeX = newSizeX;
	symbol->sizeY = newSizeY;
}

void Map2D::MoveSymbol(unsigned int ID, Direction direction, bool adhereToWalls)
{
	auto symbol = &symbols[ID];
	int x = int(floor(symbol->positionX));
	int y = int(floor(symbol->positionY));
	switch (direction)
	{
	case UP:
		if (int(floor(symbol->positionY))) //Can we move up?
		{
			if (adhereToWalls)
			{
				if (!(mapGrid[x][y].topWall))
				{
					symbol->positionY -= 1.0f;
				}
			}
			else
			{
				symbol->positionY -= 1.0f;
			}
		}
		break;
	case DOWN:
		if (int(symbol->positionY) < height - 1) //Can we move down?
		{
			if (adhereToWalls)
			{
				if (!(mapGrid[x][y].bottomWall))
				{
					symbol->positionY += 1.0f;
				}
			}
			else
			{
				symbol->positionY += 1.0f;
			}
		}
		break;
	case LEFT:
		if (symbol->positionX) //Can we move to the left?
		{
			if (adhereToWalls)
			{
				if (!(mapGrid[x][y].leftWall))
				{
					symbol->positionX -= 1.0f;
				}
			}
			else
			{
				symbol->positionX -= 1.0f;
			}
		}
		break;
	case RIGHT:
		if (symbol->positionX) //Can we move to the left?
		{
			if (adhereToWalls)
			{
				if (!(mapGrid[x][y].rightWall))
				{
					symbol->positionX += 1.0f;
				}
			}
			else
			{
				symbol->positionX += 1.0f;
			}
		}
		break;
	}
}

void Map2D::MarkSymbolAsUnusedOrUsed(unsigned int ID, bool used)
{
	symbols[ID].used = used;
}

Map2D::Map2DSymbolData& Map2D::GetSymbol(unsigned int ID)
{
	return symbols[ID];
}

std::vector<Map2D::Map2DSymbolData>& Map2D::GetAllSymbols()
{
	return symbols;
}

std::vector<Map2D::Map2DWallData>& Map2D::GetMazePoints()
{
	return dataPoints;
}

std::deque<Map2D::Direction> Map2D::GetPathBetweenPoints(int startPointX, int startPointY, int goalPointX, int goalPointY) const
{
	std::vector<MapPoint*> openList; //pair(x,y) for next point
	std::vector<MapPoint*> closedList;
	std::deque<Direction> path;

	MapPoint goal;
	goal.position = std::pair<int, int>(goalPointX, goalPointY);

	MapPoint* start = new MapPoint();
	start->position = std::pair<int, int>(startPointX, startPointY);
	start->gScore = 0;
	start->hScore = abs(startPointX - goalPointX) + abs(startPointY - goalPointY);
	openList.push_back(start);

	MapPoint temp;
	while (!openList.empty())
	{
		MapPoint* evaluatedNode;
		evaluatedNode = openList.front();
		openList.erase(openList.begin());
		closedList.push_back(evaluatedNode);

		temp = *evaluatedNode;
		if (temp.position == goal.position)
		{
			while (temp.cameFrom != nullptr)
			{
				path.push_front(temp.directionForClosestPath);
				temp = *temp.cameFrom;
			}
			for (auto it : closedList)
			{
				delete it;
			}
			for (auto it : openList)
			{
				delete it;
			}
			return path;
		}

		auto tempPosition = temp.position;
		if (!mapGrid[tempPosition.first][tempPosition.second].topWall)
		{
			MapPoint* nodeToAdd;
			bool inOpenList = false;
			bool alreadyChecked = false;
			for (auto closedNodes : closedList)
			{
				if (closedNodes->position == std::pair<int, int>(tempPosition.first, tempPosition.second - 1))
				{
					alreadyChecked = true;
					break;
				}
			}
			if (!alreadyChecked)
			{
				int ID = -1;
				for (auto openNodes : openList)
				{
					ID++;
					if (openNodes->position == std::pair<int, int>(tempPosition.first, tempPosition.second - 1))
					{
						inOpenList = true;
						nodeToAdd = openNodes;

						break;
					}
				}
				if (!inOpenList)
				{
					nodeToAdd = new MapPoint();
					nodeToAdd->position = std::pair<int, int>(tempPosition.first, tempPosition.second - 1);
					nodeToAdd->gScore = temp.gScore + 1;
					nodeToAdd->hScore = temp.gScore + abs(tempPosition.first - goalPointX) + abs(tempPosition.second - 1 - goalPointY);
					nodeToAdd->directionForClosestPath = UP;
					nodeToAdd->cameFrom = evaluatedNode;
					openList.push_back(nodeToAdd); /*NOTE: Not a priority queue right now, so it will not necessarily return the "best" path!*/
				}
				else
				{
					if (nodeToAdd->gScore > temp.gScore + 1)
					{
						nodeToAdd->gScore = temp.gScore + 1;
						nodeToAdd->hScore = temp.gScore + abs(tempPosition.first - goalPointX) + abs(tempPosition.second - 1 - goalPointY);
						nodeToAdd->directionForClosestPath = UP;
						nodeToAdd->cameFrom = evaluatedNode;
						openList[ID] = nodeToAdd;
					}
				}
			}
		}
		if (!mapGrid[tempPosition.first][tempPosition.second].bottomWall)
		{
			MapPoint* nodeToAdd;
			bool inOpenList = false;
			bool alreadyChecked = false;
			for (auto closedNodes : closedList)
			{
				if (closedNodes->position == std::pair<int, int>(tempPosition.first, tempPosition.second + 1))
				{
					alreadyChecked = true;
					break;
				}
			}
			if (!alreadyChecked)
			{
				int ID = -1;
				for (auto openNodes : openList)
				{
					ID++;
					if (openNodes->position == std::pair<int, int>(tempPosition.first, tempPosition.second + 1))
					{
						inOpenList = true;
						nodeToAdd = openNodes;

						break;
					}
				}
				if (!inOpenList)
				{
					nodeToAdd = new MapPoint();
					nodeToAdd->position = std::pair<int, int>(tempPosition.first, tempPosition.second + 1);
					nodeToAdd->gScore = temp.gScore + 1;
					nodeToAdd->hScore = temp.gScore + abs(tempPosition.first - goalPointX) + abs(tempPosition.second + 1 - goalPointY);
					nodeToAdd->directionForClosestPath = DOWN;
					nodeToAdd->cameFrom = evaluatedNode;
					openList.push_back(nodeToAdd); /*NOTE: Not a priority queue right now, so it will not necessarily return the "best" path!*/
				}
				else
				{
					if (nodeToAdd->gScore > temp.gScore + 1)
					{
						nodeToAdd->gScore = temp.gScore + 1;
						nodeToAdd->hScore = temp.gScore + abs(tempPosition.first - goalPointX) + abs(tempPosition.second + 1 - goalPointY);
						nodeToAdd->directionForClosestPath = DOWN;
						nodeToAdd->cameFrom = evaluatedNode;
						openList[ID] = nodeToAdd;
					}
				}
			}
		}
		if (!mapGrid[tempPosition.first][tempPosition.second].rightWall)
		{
			MapPoint* nodeToAdd;
			bool inOpenList = false;
			bool alreadyChecked = false;
			for (auto closedNodes : closedList)
			{
				if (closedNodes->position == std::pair<int, int>(tempPosition.first + 1, tempPosition.second))
				{
					alreadyChecked = true;
					break;
				}
			}
			if (!alreadyChecked)
			{
				int ID = -1;
				for (auto openNodes : openList)
				{
					ID++;
					if (openNodes->position == std::pair<int, int>(tempPosition.first + 1, tempPosition.second))
					{
						inOpenList = true;
						nodeToAdd = openNodes;

						break;
					}
				}
				if (!inOpenList)
				{
					nodeToAdd = new MapPoint();
					nodeToAdd->position = std::pair<int, int>(tempPosition.first + 1, tempPosition.second);
					nodeToAdd->gScore = temp.gScore + 1;
					nodeToAdd->hScore = temp.gScore + abs(tempPosition.first + 1 - goalPointX) + abs(tempPosition.second - goalPointY);
					nodeToAdd->directionForClosestPath = RIGHT;
					nodeToAdd->cameFrom = evaluatedNode;
					openList.push_back(nodeToAdd); /*NOTE: Not a priority queue right now, so it will not necessarily return the "best" path!*/
				}
				else
				{
					if (nodeToAdd->gScore > temp.gScore + 1)
					{
						nodeToAdd->gScore = temp.gScore + 1;
						nodeToAdd->hScore = temp.gScore + abs(tempPosition.first + 1 - goalPointX) + abs(tempPosition.second - goalPointY);
						nodeToAdd->directionForClosestPath = RIGHT;
						nodeToAdd->cameFrom = evaluatedNode;
						openList[ID] = nodeToAdd;
					}
				}
			}
		}
		if (!mapGrid[tempPosition.first][tempPosition.second].leftWall)
		{
			MapPoint* nodeToAdd;
			bool inOpenList = false;
			bool alreadyChecked = false;
			for (auto closedNodes : closedList)
			{
				if (closedNodes->position == std::pair<int, int>(tempPosition.first - 1, tempPosition.second))
				{
					alreadyChecked = true;
					break;
				}
			}
			if (!alreadyChecked)
			{
				int ID = -1;
				for (auto openNodes : openList)
				{
					ID++;
					if (openNodes->position == std::pair<int, int>(tempPosition.first - 1, tempPosition.second))
					{
						inOpenList = true;
						nodeToAdd = openNodes;

						break;
					}
				}
				if (!inOpenList)
				{
					nodeToAdd = new MapPoint();
					nodeToAdd->position = std::pair<int, int>(tempPosition.first - 1, tempPosition.second);
					nodeToAdd->gScore = temp.gScore + 1;
					nodeToAdd->hScore = temp.gScore + abs(tempPosition.first - 1 - goalPointX) + abs(tempPosition.second - goalPointY);
					nodeToAdd->directionForClosestPath = LEFT;
					nodeToAdd->cameFrom = evaluatedNode;
					openList.push_back(nodeToAdd); /*NOTE: Not a priority queue right now, so it will not necessarily return the "best" path!*/
				}
				else
				{
					if (nodeToAdd->gScore > temp.gScore + 1)
					{
						nodeToAdd->gScore = temp.gScore + 1;
						nodeToAdd->hScore = temp.gScore + abs(tempPosition.first - 1 - goalPointX) + abs(tempPosition.second - goalPointY);
						nodeToAdd->directionForClosestPath = LEFT;
						nodeToAdd->cameFrom = evaluatedNode;
						openList[ID] = nodeToAdd;
					}
				}
			}
		}
		temp = *evaluatedNode;
	}
	if (temp.position == goal.position)
	{
		while (temp.cameFrom != nullptr)
		{
			path.push_front(temp.directionForClosestPath);
			temp = *temp.cameFrom;
		}
		for (auto it : closedList)
		{
			delete it;
		}
		for (auto it : openList)
		{
			delete it;
		}
		return path;
	}
	for (auto it : closedList)
	{
		delete it;
	}
	for (auto it : openList)
	{
		delete it;
	}
	return path;
}

std::pair<int, int> Map2D::GetRandomPointInMaze()
{
	return std::pair<int, int>(distributionWidth(generator), distributionHeight(generator));
}

bool Map2D::LineOfSight(int originX, int originY, int pointX, int pointY) const
{
	if (originX != pointX && originY != pointY)
	{
		/*There's a corner between the origin and the point we wish to check == no visibility*/
		return false;
	}
	if (originX == pointX && originY == pointY)
		return true;
	if (originX < pointX && originY == pointY)
	{
		/*We wish to look to our right*/
		for (int x = originX; x < pointX; x++)
		{
			if (mapGrid[x][originY].rightWall)
			{
				return false;
			}
		}
	}
	else if (pointX < originX && originY == pointY)
	{
		/*We wish to look to our left*/
		for (int x = pointX; x < originX; x++)
		{
			if (mapGrid[x][originY].rightWall)
			{
				return false;
			}
		}
	}
	else
	{
		if (originY < pointY && originX == pointX)
		{
			/*We wish to look up*/

			for (int y = originY; y < pointY; y++)
			{
				if (mapGrid[pointX][y].bottomWall)
				{
					return false;
				}
			}
		}
		else if (originX == pointX)
		{
			for (int y = pointY; y < originY; y++)
			{
				if (mapGrid[pointX][y].bottomWall)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool Map2D::CanMoveInDirectionFromPoint(int originX, int originY, Direction direction, bool adhereToWalls) const
{
	switch (direction)
	{
	case UP:
		if (originY) //Can we move up?
		{
			if (adhereToWalls)
			{
				if (!(mapGrid[originX][originY].topWall))
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
		break;
	case DOWN:
		if (int(originY) < height - 1) //Can we move down?
		{
			if (adhereToWalls)
			{
				if (!(mapGrid[originX][originY].bottomWall))
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
		break;
	case LEFT:
		if (originX) //Can we move to the left?
		{
			if (adhereToWalls)
			{
				if (!(mapGrid[originX][originY].leftWall))
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
		break;
	case RIGHT:
		if (originX) //Can we move to the right?
		{
			if (adhereToWalls)
			{
				if (!(mapGrid[originX][originY].rightWall))
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
		break;
	}
	return false;
}