#pragma once
#include <GL/glut.h>
#include "Maze.h"

class MyGL3D
{
public:
	MyGL3D();
	~MyGL3D();

	MyGL3D(int argc, char** argv, Maze* pMaze_);

	static Maze* pMaze;
	void init(int width, int height);													// 初始化opengl
	static void ShowMaze(Maze* pMaze_);								// 绘制迷宫

	static void ShowWall(int i, int j);

	static void display();											// 显示回调函数


	static void reshape(int w, int h)
	{
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-2, 10, -2, 10, -10, 10);
	}

	static void mouse(int Button, int State, int x, int y);			// 鼠标响应回调函数
	static void processNormalKeys(unsigned char key, int x, int y);	// 键盘响应回调函数
	void Run(int argc, char** argv);								// 主循环
private:
	static int WindowWidth;				// 窗口宽度
	static int WindowHeight;			// 窗口高度
	static double gluOrtho2DLeft;		// 裁剪区左边界
	static double gluOrtho2DRight;		// 裁剪区右边界
	static double gluOrtho2DBottom;		// 裁剪区下边界
	static double gluOrtho2DTop;		// 裁剪区上边界
};

