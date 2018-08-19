#include "Person.h"



Person::Person()
{
}


Person::~Person()
{
}

void Person::MoveUp(Maze* pMaze_, Box** pBoxs_)
{
	int iNew = i - 1;
	int jNew = j;
	if (pMaze_->GetConnectState(i,j, iNew, jNew))
	{
		// 若连通，则看是否被箱子占用
		for (auto k = 0; k < 4; k++)
		{
			if ((pBoxs_[k])->i == iNew && (pBoxs_[k])->j == jNew)
			{
				// 占用则看箱子能不能移动
				if ((pBoxs_[k])->MoveUp(pMaze_))
				{
					i = iNew;
				}
				return;
			}
		}
		i = iNew;
	}
}

void Person::MoveDown(Maze* pMaze_, Box** pBoxs_)
{
	int iNew = i + 1;
	int jNew = j;
	// 先看是否连通
	if (pMaze_->GetConnectState(i, j, iNew, jNew))
	{
		// 若连通，则看是否被箱子占用
		for (auto k = 0; k < 4; k++)
		{
			if ((pBoxs_[k])->i == iNew && (pBoxs_[k])->j == jNew)
			{
				// 占用则看箱子能不能移动
				if ((pBoxs_[k])->MoveDown(pMaze_))
				{
					i = iNew;
				}
				return;
			}
		}
		i = iNew;
	}
}

void Person::MoveLeft(Maze* pMaze_, Box** pBoxs_)
{
	int iNew = i;
	int jNew = j - 1;
	if (pMaze_->GetConnectState(i, j, iNew, jNew))
	{
		// 若连通，则看是否被箱子占用
		for (auto k = 0; k < 4; k++)
		{
			if ((pBoxs_[k])->i == iNew && (pBoxs_[k])->j == jNew)
			{
				// 占用则看箱子能不能移动
				if ((pBoxs_[k])->MoveLeft(pMaze_))
				{
					j = jNew;
				}
				return;
			}
		}
		j = jNew;
	}
}
void Person::MoveRight(Maze* pMaze_, Box** pBoxs_)
{
	int iNew = i;
	int jNew = j + 1;
	if (pMaze_->GetConnectState(i, j, iNew, jNew))
	{
		// 若连通，则看是否被箱子占用
		for (auto k = 0; k < 4; k++)
		{
			if ((pBoxs_[k])->i == iNew && (pBoxs_[k])->j == jNew)
			{
				// 占用则看箱子能不能移动
				if ((pBoxs_[k])->MoveRight(pMaze_))
				{
					j = jNew;
				}
				return;
			}
		}
		j = jNew;
	}
}
