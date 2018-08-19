#include "MyGL2D.h"

// static参数
Maze* MyGL2D::pMaze = nullptr;
Person* MyGL2D::pPerson = nullptr;
Box* MyGL2D::pBox = nullptr;

Box* MyGL2D::pBoxs[4] = { nullptr,nullptr,nullptr,nullptr };

static Gold golds[4] = { Gold(4,2),Gold(4,3),Gold(4,6),Gold(5,3) };

int MyGL2D::GridSize = 0;
int MyGL2D::WindowWidth = 0;
int MyGL2D::WindowHeight = 0;
int MyGL2D::jMin = 0;
int MyGL2D::jMax = 0;
int MyGL2D::iMin = 0;
int MyGL2D::iMax = 0;

MyGL2D::MyGL2D(){}

MyGL2D::MyGL2D(int argc, char** argv, Maze* pMaze_) {
	
	pMaze = pMaze_;
	pPerson = new Person(1, 3);
	pBox = new Box(1, 1);

	//static Box boxs[4] = { Box(2,2),Box(2,4),Box(4,4),Box(4,5) };
	//static Box golds[4] = { Box(4,2),Box(4,3),Box(4,6),Box(5,3) };

	pBoxs[0] = new Box(2, 2);
	pBoxs[1] = new Box(2, 4);
	pBoxs[2] = new Box(4, 4);
	pBoxs[3] = new Box(4, 5);


	// 窗口与裁剪区参数计算
	MyGL2D::GridSize = 50;
	iMax = pMaze->mRenderGrid.size() / 2;
	jMax = pMaze->mRenderGrid[0].size() / 2;
	WindowWidth = jMax * GridSize;
	WindowHeight = iMax * GridSize;
	jMin = 0;
	iMin = 0;

	Run(argc, argv);
};

MyGL2D::~MyGL2D()
{
	pMaze = NULL;
	WindowWidth = 0;
	WindowHeight = 0;
	jMin = 0;
	jMax = 0;
	iMin = 0;
	iMax = 0;
}

//初始化函数 
void MyGL2D::init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(jMin, jMax, iMin, iMax);
}

// 显示Maze
void MyGL2D::ShowMaze(Maze* pMaze_)
{
	// (i,j)对应的屏幕坐标左上角（j, M - i）,右下角(j + 1, M - i - 1)
	//glRectf(j, gluOrtho2DTop - i, j + 1, gluOrtho2DTop - i - 1);// i行j列对应的矩形坐标
	//static Box boxs[4] = { Box(2,2),Box(2,4),Box(4,4),Box(4,5) };
	

	// 显示person
	glColor3f(1.0, 0.0, 0.0);
	glRectf(pPerson->j, iMax - pPerson->i, pPerson->j + 1, iMax - pPerson->i - 1);
	// 显示Boxs
	for (auto k = 0; k < 4; k++)
	{
		glColor3f(0.0, 0.0, 1.0);
		glRectf(pBoxs[k]->j, iMax - pBoxs[k]->i, pBoxs[k]->j + 1, iMax - pBoxs[k]->i - 1);
		/*glLineWidth(1);
		glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(pBoxs[k]->j, iMax - pBoxs[k]->i);
		glVertex2i(pBoxs[k]->j + 1, iMax - pBoxs[k]->i - 1);
		glVertex2i(pBoxs[k]->j, iMax - pBoxs[k]->i - 1);
		glVertex2i(pBoxs[k]->j + 1, iMax - pBoxs[k]->i);
		glEnd();*/
	}
	// 显示golds
	for (auto k = 0; k < 4; k++)
	{
		glColor3f(0.0, 0.0, 1.0);
		glLineWidth(1);
		glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(golds[k].j, iMax - golds[k].i);
		glVertex2i(golds[k].j + 1, iMax - golds[k].i - 1);
		glVertex2i(golds[k].j, iMax - golds[k].i - 1);
		glVertex2i(golds[k].j + 1, iMax - golds[k].i);
		glEnd();
	}

	/*glColor3f(0.0, 0.0, 1.0);
	glRectf(pBox->j, iMax - pBox->i, pBox->j + 1, iMax - pBox->i - 1);
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(pBox->j, iMax - pBox->i);
	glVertex2i(pBox->j + 1, iMax - pBox->i - 1);
	glVertex2i(pBox->j, iMax - pBox->i - 1);
	glVertex2i(pBox->j + 1, iMax - pBox->i);
	glEnd();*/
	// 绘制内墙
	for (int i = 0; i < iMax; i++)
		for (int j = 0; j < jMax; j++)
		{
			// 与右边不连通，竖直线
			if (j + 1 < jMax && !pMaze_->GetConnectState(i, j, i, j + 1))
			{
				glLineWidth(4);
				glBegin(GL_LINES);
				glColor3f(0.0, 0.0, 0.0);
				glVertex2i(j + 1,iMax -  i);
				glVertex2i(j + 1, iMax - i - 1);
				glEnd();
			}
			// 与下边不连通，水平线
			if (i + 1 < iMax && !pMaze_->GetConnectState(i, j, i + 1, j))
			{
				glLineWidth(4);
				glBegin(GL_LINES);
				glColor3f(0.0, 0.0, 0.0);
				glVertex2i(j , iMax - i - 1);
				glVertex2i(j + 1, iMax - i - 1);
				glEnd();
			}
		}
	//绘制外墙
	glLineWidth(8);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	static GLfloat delta = 0.001;
	glVertex2f(delta, delta);
	glVertex2f(delta, iMax - delta);
	glVertex2f(jMax - delta, iMax - delta);
	glVertex2f(jMax - delta, delta);
	glEnd();

}

// 显示回调函数
void MyGL2D::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(211.0/255, 198.0 / 255, 198.0 / 255, 0);// 设置背景色
	ShowMaze(pMaze);
	glutSwapBuffers();



	if (golds[0].CheckGameOver(pBoxs[0]->Boxlist))
	{
		std::cout << "game over" << std::endl;
		return;
	}

	static int index = 0;
	std::string cmdlist = "lDDrrDldlUluRuurrDrrddLLLdlUUdrrrruullDLdlluRdrRuuullDDldRdrdrUUULDlluRuurrDrrddLLLrddlUlUUddrrurruullDLDRRlllluRdrruuullDDldRuuurrddLruulldD";
	char key = cmdlist[index];
	if (key == 'u' || key == 'U')
	{
		pPerson->MoveUp(pMaze, pBoxs);
	}
	else if (key == 'd' || key == 'D')
	{
		pPerson->MoveDown(pMaze, pBoxs);
	}
	else if (key == 'l' || key == 'L')
	{
		pPerson->MoveLeft(pMaze, pBoxs);
	}
	else if (key == 'r' || key == 'R')
	{
		pPerson->MoveRight(pMaze, pBoxs);
	}
	index++;
	Sleep(500);
}

// 鼠标响应回调函数
void MyGL2D::mouse(int Button, int State, int x, int y)
{
	// 鼠标左键：控制cell之间连通
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
	{
		//static std::string cmd = "8 8 \n";
		static int iOld = 0;
		static int jOld = 0;
		static int counter = 0;
		// 由屏幕坐标（x,y） => 数组序号(i,j) 转换：i = y / GridSize, j = x /GridSize;
		int i = y / GridSize, j = x / GridSize;
		if (counter % 2 == 0)
		{
			iOld = i;
			jOld = j;
			std::cout << "Cell1:" << i << "," << j << std::endl;
		}
		else
		{
			pMaze->SetConnect(iOld, jOld, i, j);
			//cmd += std::to_string(iOld) + "," + std::to_string(jOld) + " " + std::to_string(i) + "," + std::to_string(j) + ";";
			//std::cout << cmd;
			//bool b = pMaze->GetConnectState(iOld, jOld, i, j);
			iOld = i;
			jOld = j;
			std::cout << "Cell2:" << i << "," << j << std::endl;
		}
		counter++;
		glutPostRedisplay();
	}
	else if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN)
	{
		//鼠标右键，暂未定义
	}
	else if (Button == GLUT_MIDDLE_BUTTON && State == GLUT_DOWN)
	{
		//鼠标中键，暂未定义
	}
}


// 键盘响应回调函数
void MyGL2D::processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'W')
	{
		// 键盘A/a
		pPerson->MoveUp(pMaze, pBoxs);
	}
	else if (key == 's' || key == 'S')
	{
		// 键盘Z/z
		pPerson->MoveDown(pMaze, pBoxs);
	}
	else if (key == 'a' || key == 'A')
	{
		// 键盘Z/z
		pPerson->MoveLeft(pMaze, pBoxs);
	}
	else if (key == 'd' || key == 'D')
	{
		// 键盘Z/z
		pPerson->MoveRight(pMaze, pBoxs);
	}
	glutPostRedisplay();
}

// OPenGL入口模块
void MyGL2D::Run(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow("Maze");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(processNormalKeys);
	glutIdleFunc(display);
	glutMainLoop();
}