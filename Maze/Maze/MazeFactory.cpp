#include "MazeFactory.h"

MazeFactory::MazeFactory() {};
MazeFactory::~MazeFactory() {};

Maze* MazeFactory::Create(std::string& command)
{
	Maze* pmaze = new Maze();
	std::vector<Road >vec;
	Position rowcol;
	INFO info = SplitCmd(command, rowcol, vec);
	switch (info)
	{
		case ERR_INVALID_NUM_FORMAT:
			pmaze->SetRenderStr("Invalid number format.");
			break;
		case ERR_NUM_OUT_OF_RANGE:
			pmaze->SetRenderStr("Number out of range.");
			break;
		case ERR_INCORRECT_CMD_FORMAT:
			pmaze->SetRenderStr("Incorrect command format.");
			break;
		case ERR_MAZE_FORMAT_ERROR:
			pmaze->SetRenderStr("Maze format error.");
			break;
		case SUCCESS:
		{
			pmaze->CreateRenderGrid(rowcol.i, rowcol.j);
			for (const auto& item : vec)
				pmaze->SetConnect(item.begin.i, item.begin.j, item.end.i, item.end.j);
		}
		default:
			break;
		}
		return pmaze;
};

// ����Ƿ���ͨ�����򷵻�true
bool MazeFactory::MazeFormatError(const Position& begin, const Position& end)
{
	return fabs(begin.i - end.i) + fabs(begin.j - end.j) != 1;
};

// ���Position�Ƿ�Խ�磬���򷵻�true
bool MazeFactory::OutOfRangeError(const Position& cellPos, const int& row, const int& col)
{
	return (cellPos.i < 0 || cellPos.i >= row || cellPos.j < 0 || cellPos.j >= col);
};

// ���Position����
MazeFactory::INFO MazeFactory::CheckPosition(const Position& cellPos, const int& row, const int& col)
{
	if (OutOfRangeError(cellPos, row, col))
		return ERR_NUM_OUT_OF_RANGE;
	else
		return SUCCESS;
};

// ���Road����
MazeFactory::INFO MazeFactory::CheckRoad(const Road& cellRoad, const int& row, const int& col)
{
	if (OutOfRangeError(cellRoad.begin, row, col) || OutOfRangeError(cellRoad.end, row, col))
		return ERR_NUM_OUT_OF_RANGE;
	else if (MazeFormatError(cellRoad.begin, cellRoad.end))
		return ERR_MAZE_FORMAT_ERROR;
	else return SUCCESS;
}

// ���и�õ��ַ�������ȡRoad
MazeFactory::INFO MazeFactory::GetRoadFromString(const std::string& strRoad, Road& road, const int row, const int col)
{
	// ���ж��Ƿ�����Ч����:���֡������š��ո񡢷ָ�����֮��ģ�0:0 1_0֮���Ӧ�����ڸ�ʽ����
	static std::regex regInvid("[^0-9\\s,:_+-]");
	std::smatch invid;
	if (std::regex_search(strRoad, invid, regInvid))
		return ERR_INVALID_NUM_FORMAT;
	//static regex regRoad("[\\s]*[-|+]?\\d{1,}[\\s]*[,][\\s]*[-|+]?\\d{1,}[\\s]+[\\s]*[-|+]?\\d{1,}[\\s]*[,][\\s]*[-|+]?\\d{1,}[\\s]*");
	// ��ȷ����Զ��ȷ
	if (sscanf_s(strRoad.c_str(), "%d , %d %d , %d", &road.begin.i, &road.begin.j, &road.end.i, &road.end.j) == 4)
		return CheckRoad(road, row, col);
	else
		return ERR_INCORRECT_CMD_FORMAT;
}

// ���и�õ��ַ�������ȡRowCol
MazeFactory::INFO MazeFactory::GetPositionFromString(const std::string& strPos, Position& pos, const int row, const int col)
{
	// ���ж��Ƿ�����Ч����:���֡������š��ո񡢷ָ�����֮��ģ�0:0 1_0֮���Ӧ�����ڸ�ʽ����
	static std::regex regInvid("[^0-9\\s,:_+-]");
	std::smatch invid;
	if (std::regex_search(strPos, invid, regInvid))
		return ERR_INVALID_NUM_FORMAT;
	// ��ȷ����Զ��ȷ
	if (sscanf_s(strPos.c_str(), "%d%d", &pos.i, &pos.j) == 2)
		return CheckPosition(pos, row, col);
	else
		return ERR_INCORRECT_CMD_FORMAT;
}

	// ����;�и��ַ���
MazeFactory::INFO MazeFactory::SplitCmd(const std::string & cmd, Position& rowcol, std::vector<Road>& roadVect)
{
	INFO info;
	std::string strTemp;
	int nowPos = 0, lastPos = 0;

	// ��ȡ����������
	nowPos = cmd.find('\n', lastPos);
	if (std::string::npos == nowPos)	return ERR_INCORRECT_CMD_FORMAT;
	else
	{
		strTemp = cmd.substr(lastPos, nowPos - lastPos);
		int MAX_ROW = 100;
		info = GetPositionFromString(strTemp, rowcol, MAX_ROW, MAX_ROW);
		if (SUCCESS != info)	return info;
		lastPos = nowPos + 1;
	}
	// ��ȡÿ��ָ���е�����
	Road tempRoad;
	do {
		nowPos = cmd.find(';', lastPos);
		if (std::string::npos == nowPos)	break;
		strTemp = cmd.substr(lastPos, nowPos - lastPos);

		info = GetRoadFromString(strTemp, tempRoad, rowcol.i, rowcol.j);
		if (SUCCESS != info)
			return info;
		else
			roadVect.push_back(tempRoad);

		lastPos = nowPos + 1;
	} while (1);

	if (lastPos < cmd.size())
	{
		strTemp = cmd.substr(lastPos, cmd.size() - lastPos);
		info = GetRoadFromString(strTemp, tempRoad, rowcol.i, rowcol.j);
		if (SUCCESS != info)
			return info;
		else
			roadVect.push_back(tempRoad);
	}
		return SUCCESS;
}


