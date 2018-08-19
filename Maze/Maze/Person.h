#pragma once
#include "Maze.h"
#include "Box.h"

class Person
{
public:
	Person();
	~Person();
	Person(int i_, int j_) : i(i_), j(j_){};

	int i;
	int j;

	void MoveUp(Maze* pMaze_, Box** pBoxs_);
	void MoveDown(Maze* pMaze_, Box** pBoxs_);
	void MoveLeft(Maze* pMaze_, Box** pBoxs_);
	void MoveRight(Maze* pMaze_, Box** pBoxs_);
};

