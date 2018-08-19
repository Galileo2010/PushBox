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

	// ��ֻ����
	static Box* pBoxs[4];

	void init();													// ��ʼ��opengl
	static void ShowMaze(Maze* pMaze_);								// �����Թ�

	static void display();											// ��ʾ�ص�����
	static void mouse(int Button, int State, int x, int y);			// �����Ӧ�ص�����
	static void processNormalKeys(unsigned char key, int x, int y);	// ������Ӧ�ص�����
	void Run(int argc, char** argv);								// ��ѭ��

private:
	static int GridSize;				// һ�����ӵĳߴ�
	static int WindowWidth;				// ���ڿ��
	static int WindowHeight;			// ���ڸ߶�
	static int jMin;					// �ü�����߽�
	static int jMax;					// �ü����ұ߽�
	static int iMin;					// �ü����±߽�
	static int iMax;					// �ü����ϱ߽�
};

