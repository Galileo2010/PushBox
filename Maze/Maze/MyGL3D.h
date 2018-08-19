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
	void init(int width, int height);													// ��ʼ��opengl
	static void ShowMaze(Maze* pMaze_);								// �����Թ�

	static void ShowWall(int i, int j);

	static void display();											// ��ʾ�ص�����


	static void reshape(int w, int h)
	{
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-2, 10, -2, 10, -10, 10);
	}

	static void mouse(int Button, int State, int x, int y);			// �����Ӧ�ص�����
	static void processNormalKeys(unsigned char key, int x, int y);	// ������Ӧ�ص�����
	void Run(int argc, char** argv);								// ��ѭ��
private:
	static int WindowWidth;				// ���ڿ��
	static int WindowHeight;			// ���ڸ߶�
	static double gluOrtho2DLeft;		// �ü�����߽�
	static double gluOrtho2DRight;		// �ü����ұ߽�
	static double gluOrtho2DBottom;		// �ü����±߽�
	static double gluOrtho2DTop;		// �ü����ϱ߽�
};

