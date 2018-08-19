#include "Maze.h"

Maze::Maze() {};
Maze::~Maze() 
{
	for (auto it : mRenderGrid)
		it.clear();
	mRenderGrid.clear();
	mRenderStr.clear();
};

void Maze::CreateRenderGrid(int M, int N)
{
	mRenderGrid.resize(M * 2 + 1);
	for (int i = 0; i < M * 2 + 1; ++i)
			mRenderGrid[i].resize(N * 2 + 1, 0);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			mRenderGrid[i * 2 + 1][j * 2 + 1] = 1;
}

void Maze::SetRenderStr(std::string str) { mRenderStr = str; }

// 调用者保证输入为相邻点
void Maze::SetConnect(int i1, int j1, int i2, int j2)
{
	int i = i1 + i2 + 1, j = j1 + j2 + 1;
	mRenderGrid[i][j] = 1;
}

bool Maze::GetConnectState(int i1, int j1, int i2, int j2)
{
	int iMax = mRenderGrid.size()/2, jMax = mRenderGrid[0].size()/2;
	if (i1 < 0 || i1 >= iMax || j1 < 0 || j1 >= jMax ||
		i2 < 0 || i2 >= iMax || j2 < 0 || j2 >= jMax)
		return false;
	int i = i1 + i2 + 1, j = j1 + j2 + 1;
	return (mRenderGrid[i][j] == 1);
}

std::string Maze::ConvertGridtoString(const Grid& Grid_)
{
	std::string result;
	for (const auto line : Grid_)
	{
		for (const auto element : line)
			result += (element == 1) ? "[R] " : "[W] ";
		result.pop_back();
		result += '\n';
	}
	result.pop_back();
	return result;
}

std::string Maze::Render()
{
	if (mRenderStr.length() == 0) mRenderStr = ConvertGridtoString(mRenderGrid);
	return mRenderStr;
}