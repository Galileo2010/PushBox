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
	// ���ڲ�������
	int row = pMaze->mRenderGrid.size();		// �ж�Ӧ�߶�
	int col = pMaze->mRenderGrid[0].size();		// �ж�Ӧ���
	WindowWidth = col * 50;
	WindowHeight = row * 50;
	gluOrtho2DLeft = 0;
	gluOrtho2DBottom = 0;
	gluOrtho2DRight = col;
	gluOrtho2DTop = row;

	Run(argc, argv);
};

//��ʼ������ 
void MyGL3D::init(int width, int height)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 0);
	//���ʷ���������
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //���淴�����
	GLfloat mat_shininess[] = { 50.0 };               //�߹�ָ��
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };   //��λ��(1,1,1), ���1-����
	GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 }; //���������

	glClearColor(0.0, 0.0, 0.0, 0.0);  //����ɫ
	glShadeModel(GL_SMOOTH);           //��������ģʽ

									   //��������
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	//�ƹ�����
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //ɢ�������
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //���淴���
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //���������

	glEnable(GL_LIGHTING);   //����:ʹ�ù�
	glEnable(GL_LIGHT0);     //��0#��
	glEnable(GL_DEPTH_TEST); //����Ȳ���
}

// ��ʾMaze
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
	// (i,j)��Ӧ����Ļ�������Ͻǣ�j, M - i��,���½�(j + 1, M - i - 1)
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

// ��ʾ�ص�����
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

// �����Ӧģ��
void MyGL3D::mouse(int Button, int State, int x, int y)
{
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
	{
		xrot += 0.5;

	}
	else if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN)
	{
		//����Ҽ�
		yrot += 0.5;
	}
	//else if (Button == GLUT_MIDDLE_BUTTON && State == GLUT_DOWN)
	{
		//����м�
		xrot += 10;
	}
	glutPostRedisplay();
}


// ������Ӧģ��
void MyGL3D::processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 'a' || key == 'A')
	{
		// ����A/a
	}
	else if (key == 'z' || key == 'Z')
	{
		// ����Z/z
	}
	glutPostRedisplay();
}

// ���ģ�飬�Ӵ˴������ͼѭ����sizeΪ���ڳߴ�
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