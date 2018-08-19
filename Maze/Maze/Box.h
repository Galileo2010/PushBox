#pragma once
#include "Maze.h"

class Box
{
public:
	Box();
	~Box();

	static std::vector<Box*> Boxlist;//


	Box(int i_, int j_) : i(i_), j(j_){
		Boxlist.push_back(this);
	};

	int i;
	int j;
	bool MoveUp(Maze* pMaze_);
	bool MoveDown(Maze* pMaze_);
	bool MoveLeft(Maze* pMaze_);
	bool MoveRight(Maze* pMaze_);

	bool HasBox(int i_, int j_)
	{
		for (const auto iter : Boxlist)
			if (iter->i == i_ && iter->j == j_)
				return true;
		return false;
	}
};

