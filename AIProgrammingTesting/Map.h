#pragma once
#include <vector>
#include <random>
#include <deque>

class Map2D
{
public:
	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	struct Map2DWallData
	{
		float xStart, yStart;
		float xEnd, yEnd;
	};

	struct Map2DSymbolData
	{
		enum Symbol
		{
			CIRCLE,
			LINE,
			DASHED_LINE
		} typeOfSymbol;

		float positionX, positionY;
		float sizeX, sizeY; //Works as "length" for the line. The "unused" size is set to 0.
		bool used = true;
	};

private:
	struct Grid
	{
		bool topWall;
		bool bottomWall;
		bool leftWall;
		bool rightWall;
		std::pair<int, int> position;
	};

	struct MapPoint
	{
		MapPoint* cameFrom = nullptr;
		Direction directionForClosestPath;
		std::pair<int, int> position;
		int gScore;
		int hScore;
	};

	int* set;
	Grid** mapGrid;
	int height; //x-coordinates
	int width; //y-coordinates
	std::vector<Map2DWallData> dataPoints;
	std::vector<Map2DSymbolData> symbols;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;
	std::uniform_int_distribution<int> distributionWidth;
	std::uniform_int_distribution<int> distributionHeight;

	/*Map Generation --- HelpFunctions*/
	int find(int x) const;
	int findCompress(int x) const;
	int setHeight(int x) const;
	void unionSetsRank(int root1, int root2) const;

public:
	Map2D();
	~Map2D();
	std::vector<Map2DWallData>& GenerateMaze(int height, int width);
	unsigned int AddSymbol(Map2DSymbolData::Symbol symbolType, int positionX, int positionY, float sizeX, float sizeY);
	void MoveSymbol(unsigned int ID, int newPositionX, int newPositionY, float newSizeX, float newSizeY);
	void MoveSymbol(unsigned int ID, Direction direction, bool adhereToWalls = true);
	void MarkSymbolAsUnusedOrUsed(unsigned int ID, bool used = false);
	Map2DSymbolData& GetSymbol(unsigned int ID);
	std::vector<Map2DSymbolData>& GetAllSymbols();
	std::vector<Map2DWallData>& GetMazePoints();
	std::deque<Direction> GetPathBetweenPoints(int startPointX, int startPointY, int goalPointX, int goalPointY) const;
	std::pair<int, int> GetRandomPointInMaze();
	bool LineOfSight(int originX, int originY, int pointX, int pointY) const;
	bool CanMoveInDirectionFromPoint(int originX, int originY, Direction direction, bool adhereToWalls = true) const;
};
