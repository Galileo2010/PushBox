#pragma once
#include <vector>
class Maze
{
public:
	Maze();
	~Maze();

	using Line = std::vector<int>;
	using Grid = std::vector<Line>;

	std::string Render();
	void SetRenderStr(std::string str);
	
	void CreateRenderGrid(int M, int N);
	void SetConnect(int i1, int j1, int i2, int j2);
	bool GetConnectState(int i1, int j1, int i2, int j2);
public:// ���㵥Ԫ���ԣ���Ϊpublic
	std::string ConvertGridtoString(const Grid& Grid_);

	Grid mRenderGrid;
	std::string mRenderStr;
};

