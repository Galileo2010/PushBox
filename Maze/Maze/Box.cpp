#include "Box.h"

Box::Box()
{
}

Box::~Box()
{
}

std::vector<Box*> Box::Boxlist;

bool Box::MoveUp(Maze* pMaze_)
{
	int iNew = i - 1;
	int jNew = j;
	if (pMaze_->GetConnectState(i, j, iNew, jNew) && !HasBox(iNew, jNew))
	{
		i = iNew;
		return true;
	}
	return false;
}

bool Box::MoveDown(Maze* pMaze_)
{
	int iNew = i + 1;
	int jNew = j;
	if (pMaze_->GetConnectState(i, j, iNew, jNew) && !HasBox(iNew, jNew))
	{
		i = iNew;
		return true;
	}
	return false;
}

bool Box::MoveLeft(Maze* pMaze_)
{
	int iNew = i;
	int jNew = j - 1;
	if (pMaze_->GetConnectState(i, j, iNew, jNew) && !HasBox(iNew, jNew))
	{
		j = jNew;
		return true;
	}
	return false;
}
bool Box::MoveRight(Maze* pMaze_)
{
	int iNew = i;
	int jNew = j + 1;
	if (pMaze_->GetConnectState(i, j, iNew, jNew) && !HasBox(iNew, jNew))
	{
		j = jNew;
		return true;
	}
	return false;
}
