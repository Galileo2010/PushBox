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
		SUCCESS,					// 0���ɹ�
		ERR_INVALID_NUM_FORMAT,		// 1����Ч�����֣���Invalid number format.��
		ERR_NUM_OUT_OF_RANGE,		// 2�����ֳ���Ԥ���ķ�Χ��Number out of range.��
		ERR_INCORRECT_CMD_FORMAT,	// 3����ʽ����Incorrect command format.��
		ERR_MAZE_FORMAT_ERROR		// 4����ͨ�� ���� ��Maze format error.��
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

	// ����Ƿ���ͨ�����򷵻�true
	bool MazeFormatError(const Position& begin, const Position& end);

	// ���Position�Ƿ�Խ�磬���򷵻�true
	bool OutOfRangeError(const Position& cellPos, const int& row, const int& col);

	// ���Position����
	INFO CheckPosition(const Position& cellPos, const int& row, const int& col);

	// ���Road����
	INFO CheckRoad(const Road& cellRoad, const int& row, const int& col);

	// ���и�õ��ַ�������ȡRoad
	INFO GetRoadFromString(const std::string& strRoad, Road& road, const int row, const int col);

	// ���и�õ��ַ�������ȡRowCol
	INFO GetPositionFromString(const std::string& strPos, Position& pos, const int row, const int col);

	// ����;�и��ַ���
	INFO SplitCmd(const std::string & cmd, Position& rowcol, std::vector<Road>& roadVect);
};

