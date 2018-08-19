#include "gtest/gtest.h"
#include "../Maze/MazeFactory.h"

// 创建RenderGrid
TEST(Maze, CreateRenderGrid)
{
	Maze maze;
	maze.CreateRenderGrid(4, 5);
	EXPECT_EQ(maze.mRenderGrid.size(), 4 * 2 + 1);
	for (auto it : maze.mRenderGrid)
		EXPECT_EQ(it.size(), 5 * 2 + 1);
}

// 设置道路连通
TEST(Maze, SetAndGetConnect)
{
	Maze maze;
	maze.CreateRenderGrid(4, 5);
	EXPECT_FALSE(maze.GetConnectState(0, 0, 0, 1));
	maze.SetConnect(0, 0, 0, 1);
	EXPECT_TRUE(maze.GetConnectState(0, 0, 0, 1));

	EXPECT_FALSE(maze.GetConnectState(1, 1, 0, 1));
	maze.SetConnect(1, 1, 0, 1);
	EXPECT_TRUE(maze.GetConnectState(1, 1, 0, 1));
}

TEST(Maze, SetRenderStr)
{
	Maze maze;
	std::string str1 = "this is renderStr 01";
	std::string str2 = "this is renderStr 02";

	maze.SetRenderStr(str1);
	EXPECT_EQ(maze.mRenderStr, str1);

	maze.SetRenderStr(str2);
	EXPECT_EQ(maze.mRenderStr, str2);
}

TEST(Maze, Render)
{
	Maze maze;
	maze.CreateRenderGrid(3, 3);
	maze.SetConnect(0, 0, 0, 1);
	maze.SetConnect(1, 1, 0, 1);
	EXPECT_EQ(maze.Render(),
"[W] [W] [W] [W] [W] [W] [W]\n\
[W] [R] [R] [R] [W] [R] [W]\n\
[W] [W] [W] [R] [W] [W] [W]\n\
[W] [R] [W] [R] [W] [R] [W]\n\
[W] [W] [W] [W] [W] [W] [W]\n\
[W] [R] [W] [R] [W] [R] [W]\n\
[W] [W] [W] [W] [W] [W] [W]");
}

// INFO splitCmd和Create函数主要在main中测试
TEST(MazeFactory, splitCmd_Create)
{
	MazeFactory factory;
	std::string cmd = "  3 3\n 0, 1 0, 2; 0, 0 1, 0; 0, 1 1, 1; 0, 2 1, 2; 1, 0 1, 1; 1, 1 1, 2; 1, 1 2, 1; 1, 2 2, 2; 2, 0 2, 1";
	Maze* pmaze = factory.Create(cmd);
	std::string render = pmaze->Render();
	EXPECT_EQ(render,
"[W] [W] [W] [W] [W] [W] [W]\n\
[W] [R] [W] [R] [R] [R] [W]\n\
[W] [R] [W] [R] [W] [R] [W]\n\
[W] [R] [R] [R] [R] [R] [W]\n\
[W] [W] [W] [R] [W] [R] [W]\n\
[W] [R] [R] [R] [W] [R] [W]\n\
[W] [W] [W] [W] [W] [W] [W]");
	delete pmaze;
}

// INFO GetPositionFromString(const std::string& strPos, Position& pos, const int row, const int col)
TEST(MazeFactory, GetPositionFromString)
{
	MazeFactory factory;
	MazeFactory::Position p;
	std::string cmd = "   3    5   ";
	int M = 10, N = 10;
	EXPECT_EQ(factory.GetPositionFromString(cmd, p, M, N), MazeFactory::SUCCESS);
	EXPECT_EQ(p.i, 3);
	EXPECT_EQ(p.j, 5);

	cmd = "   3  ,  5   ";
	EXPECT_EQ(factory.GetPositionFromString(cmd, p, M, N), MazeFactory::ERR_INCORRECT_CMD_FORMAT);

	cmd = "   3.0  5   ";
	EXPECT_EQ(factory.GetPositionFromString(cmd, p, M, N), MazeFactory::ERR_INVALID_NUM_FORMAT);

	cmd = "   -1  5   ";
	EXPECT_EQ(factory.GetPositionFromString(cmd, p, M, N), MazeFactory::ERR_NUM_OUT_OF_RANGE);
}

// INFO GetRoadFromString(const std::string& strRoad, Road& road, const int row, const int col)
TEST(MazeFactory, GetRoadFromString)
{
	MazeFactory factory;
	MazeFactory::Road road;
	int M = 10, N = 10;

	std::string cmd = "  0  ,  1  0  , 0  ";
	EXPECT_EQ(factory.GetRoadFromString(cmd, road, M, N), MazeFactory::SUCCESS);
	EXPECT_EQ(road.begin.i, 0);
	EXPECT_EQ(road.begin.j, 1);
	EXPECT_EQ(road.end.i, 0);
	EXPECT_EQ(road.end.j, 0);

	cmd = "  0  :  1  0  , 0  ";
	EXPECT_EQ(factory.GetRoadFromString(cmd, road, M, N), MazeFactory::ERR_INCORRECT_CMD_FORMAT);

	cmd = "  0.5  ,  1  0  , 0  ";
	EXPECT_EQ(factory.GetRoadFromString(cmd, road, M, N), MazeFactory::ERR_INVALID_NUM_FORMAT);

	cmd = "  0  ,  -1  0  , 0  ";
	EXPECT_EQ(factory.GetRoadFromString(cmd, road, M, N), MazeFactory::ERR_NUM_OUT_OF_RANGE);
}

// INFO CheckRoad(const Road& cellRoad, const int row, const int col)
TEST(MazeFactory, CheckRoad)
{
	MazeFactory factory;
	MazeFactory::Road road;
	int M = 10, N = 10;

	road.begin.i = 0, road.begin.j = 0, road.end.i = 0, road.end.j = 1;
	EXPECT_EQ(factory.CheckRoad(road, M, N), MazeFactory::SUCCESS);
	road.begin.i = 1, road.begin.j = 3, road.end.i = 2, road.end.j = 3;
	EXPECT_EQ(factory.CheckRoad(road, M, N), MazeFactory::SUCCESS);

	road.begin.i = -1, road.begin.j = 0, road.end.i = 0, road.end.j = 1;
	EXPECT_EQ(factory.CheckRoad(road, M, N), MazeFactory::ERR_NUM_OUT_OF_RANGE);
	road.begin.i = 0, road.begin.j = 10, road.end.i = 0, road.end.j = 1;
	EXPECT_EQ(factory.CheckRoad(road, M, N), MazeFactory::ERR_NUM_OUT_OF_RANGE);


	road.begin.i = 0, road.begin.j = 0, road.end.i = 1, road.end.j = 1;
	EXPECT_EQ(factory.CheckRoad(road, M, N), MazeFactory::ERR_MAZE_FORMAT_ERROR);
	road.begin.i = 0, road.begin.j = 0, road.end.i = 0, road.end.j = 2;
	EXPECT_EQ(factory.CheckRoad(road, M, N), MazeFactory::ERR_MAZE_FORMAT_ERROR);
}

// INFO CheckPosition(const Position& cellPos, const int& row, const int& col)
TEST(MazeFactory, CheckPosition)
{
	MazeFactory factory;
	MazeFactory::Position p;
	int M = 4, N = 5;  

	p.i = 4, p.j = 2;
	EXPECT_EQ(factory.CheckPosition(p, M, N), MazeFactory::ERR_NUM_OUT_OF_RANGE);
	p.i = -1, p.j = 2;
	EXPECT_EQ(factory.CheckPosition(p, M, N), MazeFactory::ERR_NUM_OUT_OF_RANGE);
	p.i = 1, p.j = 6;
	EXPECT_EQ(factory.CheckPosition(p, M, N), MazeFactory::ERR_NUM_OUT_OF_RANGE);

	p.i = 3, p.j = 3;
	EXPECT_EQ(factory.CheckPosition(p, M, N), MazeFactory::SUCCESS);
	p.i = 2, p.j = 0;
	EXPECT_EQ(factory.CheckPosition(p, M, N), MazeFactory::SUCCESS);
	p.i = 1, p.j = 4;
	EXPECT_EQ(factory.CheckPosition(p, M, N), MazeFactory::SUCCESS);
}

// inline bool OutOfRangeError(const Position& cellPos, const int& row, const int& col)
TEST(MazeFactory, OutOfRangeError)
{
	MazeFactory factory;
	MazeFactory::Position p;
	int M = 4, N = 5;  
	// 不越界数据
	p.i = 1, p.j = 2;
	EXPECT_FALSE(factory.OutOfRangeError(p, M, N));
	p.i = 3, p.j = 3;
	EXPECT_FALSE(factory.OutOfRangeError(p, M, N));
	p.i = 1, p.j = 2;
	EXPECT_FALSE(factory.OutOfRangeError(p, M, N));
	p.i = 2, p.j = 3;
	EXPECT_FALSE(factory.OutOfRangeError(p, M, N));
	// 越界数据
	p.i = 4, p.j = 0;
	EXPECT_TRUE(factory.OutOfRangeError(p, M, N));
	p.i = -1, p.j = 2;
	EXPECT_TRUE(factory.OutOfRangeError(p, M, N));
	p.i = 1, p.j = 5;
	EXPECT_TRUE(factory.OutOfRangeError(p, M, N));
}

//  bool MazeFormatError(const Position& begin, const Position& end)
TEST(MazeFactory, MazeFormatError)
{
	MazeFactory factory;
	MazeFactory::Position p1, p2;
	// 连通数据
	p1.i = 1, p1.j = 2, p2.i = 1, p2.j = 1;
	EXPECT_FALSE(factory.MazeFormatError(p1, p2));
	p1.i = 1, p1.j = 1, p2.i = 2, p2.j = 1;
	EXPECT_FALSE(factory.MazeFormatError(p1, p2));
	p1.i = 1, p1.j = 1, p2.i = 1, p2.j = 2;
	EXPECT_FALSE(factory.MazeFormatError(p1, p2));
	p1.i = 2, p1.j = 1, p2.i = 1, p2.j = 1;
	EXPECT_FALSE(factory.MazeFormatError(p1, p2));
	// 不连通数据
	p1.i = 0, p1.j = 0, p2.i = 1, p2.j = 1;
	EXPECT_TRUE(factory.MazeFormatError(p1, p2));
	p1.i = 1, p1.j = 1, p2.i = 0, p2.j = 0;
	EXPECT_TRUE(factory.MazeFormatError(p1, p2));
	p1.i = 2, p1.j = 0, p2.i = 0, p2.j = 0;
	EXPECT_TRUE(factory.MazeFormatError(p1, p2));
}