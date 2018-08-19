#include "MyGL3D.h"

MyGL3D::MyGL3D() {}


static float xrot = 0.0;
static float yrot = 0.0;
static float zrot = 0.0;


MyGL3D::~MyGL3D()
{
	pMaze = NULL;
	WindowWidth = 0;
	WindowHeight = 0;
	gluOrtho2DLeft = 0;
	gluOrtho2DRight = 0;
	gluOrtho2DBottom = 0;
	gluOrtho2DTop = 0;
}

Maze* MyGL3D::pMaze = NULL;
int MyGL3D::WindowWidth = 0;
int MyGL3D::WindowHeight = 0;
double MyGL3D::gluOrtho2DLeft = 0;
double MyGL3D::gluOrtho2DRight = 0;
double MyGL3D::gluOrtho2DBottom = 0;
double MyGL3D::gluOrtho2DTop = 0;

MyGL3D::MyGL3D(int argc, char** argv, Maze* pMaze_) {

	pMaze = pMaze_;
	// 窗口参数计算
	int row = pMaze->mRenderGrid.size();		// 行对应高度
	int col = pMaze->mRenderGrid[0].size();		// 列对应宽度
	WindowWidth = col * 50;
	WindowHeight = row * 50;
	gluOrtho2DLeft = 0;
	gluOrtho2DBottom = 0;
	gluOrtho2DRight = col;
	gluOrtho2DTop = row;

	Run(argc, argv);
};

//初始化函数 
void MyGL3D::init(int width, int height)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 0);
	//材质反光性设置
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //镜面反射参数
	GLfloat mat_shininess[] = { 50.0 };               //高光指数
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };   //灯位置(1,1,1), 最后1-开关
	GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 }; //环境光参数

	glClearColor(0.0, 0.0, 0.0, 0.0);  //背景色
	glShadeModel(GL_SMOOTH);           //多变性填充模式

									   //材质属性
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	//灯光设置
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //散射光属性
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //镜面反射光
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //环境光参数

	glEnable(GL_LIGHTING);   //开关:使用光
	glEnable(GL_LIGHT0);     //打开0#灯
	glEnable(GL_DEPTH_TEST); //打开深度测试
}

// 显示Maze
void MyGL3D::ShowMaze(Maze* pMaze_)
{
	for (int i = 0; i < pMaze_->mRenderGrid.size(); i++)
		for (int j = 0; j < pMaze_->mRenderGrid[i].size(); j++)
		{
			if (pMaze_->mRenderGrid[i][j] == 0)
				ShowWall(i, j);
		}
}



void MyGL3D::ShowWall( int i, int j)
{
	// (i,j)对应的屏幕坐标左上角（j, M - i）,右下角(j + 1, M - i - 1)
		glBegin(GL_QUADS);
		glVertex3f(j, gluOrtho2DTop - i, 1);
		glVertex3f(j + 1, gluOrtho2DTop - i, 1);
		glVertex3f(j + 1, gluOrtho2DTop - i - 1, 1);
		glVertex3f(j , gluOrtho2DTop - i - 1, 1);

		glVertex3f(j, gluOrtho2DTop - i, 1);
		glVertex3f(j, gluOrtho2DTop - i - 1, 1);
		glVertex3f(j, gluOrtho2DTop - i - 1, 0);
		glVertex3f(j, gluOrtho2DTop - i, 0);

		glVertex3f(j + 1, gluOrtho2DTop - i, 1);
		glVertex3f(j + 1, gluOrtho2DTop - i - 1, 1);
		glVertex3f(j + 1, gluOrtho2DTop - i - 1, 0);
		glVertex3f(j + 1, gluOrtho2DTop - i, 0);

		glVertex3f(j, gluOrtho2DTop - i, 1);
		glVertex3f(j + 1, gluOrtho2DTop - i, 1);
		glVertex3f(j + 1, gluOrtho2DTop - i, 0);
		glVertex3f(j, gluOrtho2DTop - i, 0);

		glVertex3f(j + 1, gluOrtho2DTop - i - 1, 1);
		glVertex3f(j, gluOrtho2DTop - i - 1, 1); 
		glVertex3f(j, gluOrtho2DTop - i - 1, 0);
		glVertex3f(j + 1, gluOrtho2DTop - i - 1, 0);

		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(j, gluOrtho2DTop - i, 0);
		glVertex3f(j + 1, gluOrtho2DTop - i, 0);
		glVertex3f(j + 1, gluOrtho2DTop - i - 1, 0);
		glVertex3f(j, gluOrtho2DTop - i - 1, 0);
		glEnd();
}

// 显示回调函数
void MyGL3D::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 10, -2, 10, -10, 10);
	glRotatef(xrot, 1, 0, 0);
	glRotatef(yrot, 0, 1, 0);
	ShowMaze(pMaze);

	glutSwapBuffers();
}

// 鼠标响应模块
void MyGL3D::mouse(int Button, int State, int x, int y)
{
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
	{
		xrot += 0.5;

	}
	else if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN)
	{
		//鼠标右键
		yrot += 0.5;
	}
	//else if (Button == GLUT_MIDDLE_BUTTON && State == GLUT_DOWN)
	{
		//鼠标中键
		xrot += 10;
	}
	glutPostRedisplay();
}


// 键盘响应模块
void MyGL3D::processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 'a' || key == 'A')
	{
		// 键盘A/a
	}
	else if (key == 'z' || key == 'Z')
	{
		// 键盘Z/z
	}
	glutPostRedisplay();
}

// 入口模块，从此处进入绘图循环，size为窗口尺寸
void MyGL3D::Run(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Maze");
	init(640, 480);
	glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(processNormalKeys);
	glutIdleFunc(display);
	glutMainLoop();
}