#pragma once
#include <string>
#include <regex>
#include "Maze.h"
class MazeFactory
{
public:
	MazeFactory();
	~MazeFactory();

	enum INFO
	{
		SUCCESS,					// 0、成功
		ERR_INVALID_NUM_FORMAT,		// 1、无效的数字：”Invalid number format.”
		ERR_NUM_OUT_OF_RANGE,		// 2、数字超出预定的范围”Number out of range.”
		ERR_INCORRECT_CMD_FORMAT,	// 3、格式错误”Incorrect command format.”
		ERR_MAZE_FORMAT_ERROR		// 4、连通性 错误 ”Maze format error.”
	};

	typedef struct tagPosition
	{
		int i;
		int j;
	}Position, *PPosition;

	typedef struct tagRoad
	{
		Position begin;
		Position end;
	}Road, *PRoad;

	Maze* Create(std::string& command);

	// 检查是否不连通，是则返回true
	bool MazeFormatError(const Position& begin, const Position& end);

	// 检查Position是否越界，是则返回true
	bool OutOfRangeError(const Position& cellPos, const int& row, const int& col);

	// 检查Position数据
	INFO CheckPosition(const Position& cellPos, const int& row, const int& col);

	// 检查Road数据
	INFO CheckRoad(const Road& cellRoad, const int& row, const int& col);

	// 从切割好的字符串中提取Road
	INFO GetRoadFromString(const std::string& strRoad, Road& road, const int row, const int col);

	// 从切割好的字符串中提取RowCol
	INFO GetPositionFromString(const std::string& strPos, Position& pos, const int row, const int col);

	// 按照;切割字符串
	INFO SplitCmd(const std::string & cmd, Position& rowcol, std::vector<Road>& roadVect);
};

