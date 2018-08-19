#include <iostream>
#include <windows.h>
#include "MazeFactory.h"
#include "MyGL2D.h"

int main(int argc, char **argv)
{
	/*
	// 控制台显示
	while (true)
	{
		// 官方测试用例"  3 3\n   0 , 1  0, 2; 0, 0 1, 0; 0, 1 1, 1; 0, 2 1, 2; 1, 0 1, 1; 1, 1 1, 2; 1, 1 2, 1; 1, 2 2, 2; 2, 0 2, 1;";
		std::cout << "请输入测试用例或按Ctrl + C退出：" << std::endl;
		std::string str, str1, str2;
		std::getline(std::cin, str1);
		std::getline(std::cin, str2);
		str = str1 + '\n' + str2;
		MazeFactory factory;
		Maze* pmaze = factory.Create(str);

		std::string render = pmaze->Render();
		for (size_t i = 0; i < render.length(); i++)
		{
			auto color = (render[i] == 'R') ? FOREGROUND_GREEN : FOREGROUND_RED;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
			std::cout << render[i];
		}
		std::cout << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		MyGLEngine(argc, argv, pmaze);

		delete pmaze;
	}
	*/

	// opengl窗口显示
	{
		//std::cout << "请输入测试用例：" << std::endl;
		//std::string str, str1, str2;
		//std::getline(std::cin, str1);
		//std::getline(std::cin, str2);
		//str = str1 + '\n' + str2;
		std::string str = " 8 8\n1, 2 1, 3; 1, 3 1, 4; 1, 2 2, 2; 2, 2 3, 2; 3, 2 3, 3; 3, 3 3, 4; 3, 4 2, 4; 2, 4 1, 4; 2, 4 2, 5; 2, 5 2, 6; 2, 6 3, 6; 3, 6 4, 6; 4, 6 4, 5; 4, 5 4, 4; 4, 4 3, 4; 3, 2 3, 1; 3, 1 4, 1; 3, 2 4, 2; 4, 1 4, 2; 4, 2 4, 3; 4, 3 4, 4; 4, 3 3, 3; 4, 2 5, 2; 5, 2 5, 3; 5, 3 4, 3; 5, 3 6, 3; 6, 3 6, 4; 6, 4 5, 4; 5, 4 5, 3; 5, 4 4, 4; 1, 0 0, 0; 0, 0 0, 1; 0, 1 0, 2; 0, 2 0, 3; 0, 3 0, 4; 0, 4 0, 5; 0, 5 1, 5; 0, 5 0, 6; 0, 6 1, 6; 1, 5 1, 6; 0, 6 0, 7; 0, 7 1, 7; 1, 6 1, 7; 1, 7 2, 7; 2, 7 3, 7; 3, 7 4, 7; 4, 7 5, 7; 5, 7 6, 7; 6, 7 7, 7; 7, 7 7, 6; 7, 6 6, 6; 6, 6 5, 6; 5, 6 5, 7; 6, 7 6, 6; 5, 6 5, 5; 5, 5 6, 5; 6, 5 6, 6; 7, 6 7, 5; 7, 5 6, 5; 7, 5 7, 4; 7, 4 7, 3; 7, 3 7, 2; 7, 2 7, 1; 7, 1 7, 0; 7, 0 6, 0; 6, 0 6, 1; 6, 1 7, 1; 6, 1 6, 2; 6, 2 7, 2; 6, 1 5, 1; 5, 1 5, 0; 5, 0 6, 0; 5, 0 4, 0; 4, 0 3, 0; 3, 0 2, 0; 2, 0 2, 1; 2, 1 1, 1; 1, 1 0, 1; 1, 1 1, 0; 1, 0 2, 0;";
		MazeFactory factory;
		Maze* pmaze = factory.Create(str);
		//std::cout << pmaze->Render();
		if(!pmaze->mRenderGrid.empty())
			MyGL2D(argc, argv, pmaze);
		delete pmaze;
	}
	return 0;
}