#pragma once
#include <GL/glut.h>
#include <iostream>
#include <string>

#include "Maze.h"
#include "Person.h"
#include "Box.h"
#include "Gold.h"

class MyGL2D
{
public:
	MyGL2D();
	~MyGL2D();

	MyGL2D(int argc, char** argv, Maze* pMaze_);

	static Maze* pMaze;
	static Person * pPerson;
	static Box* pBox;

	// 多只箱子
	static Box* pBoxs[4];

	void init();													// 初始化opengl
	static void ShowMaze(Maze* pMaze_);								// 绘制迷宫

	static void display();											// 显示回调函数
	static void mouse(int Button, int State, int x, int y);			// 鼠标响应回调函数
	static void processNormalKeys(unsigned char key, int x, int y);	// 键盘响应回调函数
	void Run(int argc, char** argv);								// 主循环

private:
	static int GridSize;				// 一个格子的尺寸
	static int WindowWidth;				// 窗口宽度
	static int WindowHeight;			// 窗口高度
	static int jMin;					// 裁剪区左边界
	static int jMax;					// 裁剪区右边界
	static int iMin;					// 裁剪区下边界
	static int iMax;					// 裁剪区上边界
};

