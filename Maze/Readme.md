## 项目介绍
### 开发环境说明
本项目使用VS2017开发，建议安装Google Test适配器插件以获得IDE原生支持的
 
可视化测试结果。

### 运行单元测试
Test为单元测试项目，基于Google Test开源框架。具体测试源代码保存在test.cpp

中，几乎对Maze项目中所有的方法进行了测试，详细内容请自行查看。


开发过程中可使用IDE在测试资源管理器中直接运行单元测试，非开发模式下cd进入

bin文件夹运行Test即可查看测试结果：

    C:\Users\Galileo\source\repos\Maze\bin>Test

输出结果：

	Microsoft Windows [版本 10.0.17134.165]
    (c) 2018 Microsoft Corporation。保留所有权利。
    
    C:\Users\Galileo\source\repos\Maze\bin>Test
    Running main() from gtest_main.cc
    [==========] Running 11 tests from 2 test cases.
    [----------] Global test environment set-up.
    [----------] 4 tests from Maze
    [ RUN  ] Maze.CreateRenderGrid
    [   OK ] Maze.CreateRenderGrid (0 ms)
    [ RUN  ] Maze.SetAndGetConnect
    [   OK ] Maze.SetAndGetConnect (0 ms)
    [ RUN  ] Maze.SetRenderStr
    [   OK ] Maze.SetRenderStr (0 ms)
    [ RUN  ] Maze.Render
    [   OK ] Maze.Render (0 ms)
    [----------] 4 tests from Maze (3 ms total)
    
    [----------] 7 tests from MazeFactory
    [ RUN  ] MazeFactory.splitCmd_Create
    [   OK ] MazeFactory.splitCmd_Create (1 ms)
    [ RUN  ] MazeFactory.GetPositionFromString
    [   OK ] MazeFactory.GetPositionFromString (0 ms)
    [ RUN  ] MazeFactory.GetRoadFromString
    [   OK ] MazeFactory.GetRoadFromString (0 ms)
    [ RUN  ] MazeFactory.CheckRoad
    [   OK ] MazeFactory.CheckRoad (0 ms)
    [ RUN  ] MazeFactory.CheckPosition
    [   OK ] MazeFactory.CheckPosition (0 ms)
    [ RUN  ] MazeFactory.OutOfRangeError
    [   OK ] MazeFactory.OutOfRangeError (0 ms)
    [ RUN  ] MazeFactory.MazeFormatError
    [   OK ] MazeFactory.MazeFormatError (0 ms)
    [----------] 7 tests from MazeFactory (9 ms total)
    
    [----------] Global test environment tear-down
    [==========] 11 tests from 2 test cases ran. (18 ms total)
    [  PASSED  ] 11 tests.
    
    C:\Users\Galileo\source\repos\Maze\bin>
    
### 运行主程序
Maze项目中，Maze和MazeFactory类实现了解析command字符串的功能，运行主程

序并输入几组数据结果如下，具体请自行测试：

    C:\Users\Galileo\source\repos\Maze\bin>Maze
    请输入测试用例或按Ctrl + C退出：
    3 3
    0 , 1  0, 2; 0, 0 1, 0; 0, 1 1, 1; 0, 2 1, 2; 1, 0 1, 1; 1, 1 1, 2; 1, 1 2, 1; 1, 2 2, 2; 2, 0 2, 1
    [W] [W] [W] [W] [W] [W] [W]
    [W] [R] [W] [R] [R] [R] [W]
    [W] [R] [W] [R] [W] [R] [W]
    [W] [R] [R] [R] [R] [R] [W]
    [W] [W] [W] [R] [W] [R] [W]
    [W] [R] [R] [R] [W] [R] [W]
    [W] [W] [W] [W] [W] [W] [W]
    请输入测试用例或按Ctrl + C退出：
    -1  4
    0 , 1  0, 2; 0, 0 1, 0; 0, 1 1, 1; 0, 2 1, 2; 1, 0 1, 1; 1, 1 1, 2; 1, 1 2, 1; 1, 2 2, 2; 2, 0 2, 1
    Number out of range.
    请输入测试用例或按Ctrl + C退出：
    3  ,3
    0 , 1  0, 2; 0, 0 1, 0; 0, 1 1, 1; 0, 2 1, 2; 1, 0 1, 1; 1, 1 1, 2; 1, 1 2, 1; 1, 2 2, 2; 2, 0 2, 1
    Incorrect command format.
    请输入测试用例或按Ctrl + C退出：
    3 3
    0,0 0,1
    [W] [W] [W] [W] [W] [W] [W]
    [W] [R] [R] [R] [W] [R] [W]
    [W] [W] [W] [W] [W] [W] [W]
    [W] [R] [W] [R] [W] [R] [W]
    [W] [W] [W] [W] [W] [W] [W]
    [W] [R] [W] [R] [W] [R] [W]
    [W] [W] [W] [W] [W] [W] [W]
    请输入测试用例或按Ctrl + C退出：
    3 3
    0 : 0 2,0
    Incorrect command format.
    请输入测试用例或按Ctrl + C退出：
    3 3
    0,02,0
    Maze format error.
    请输入测试用例或按Ctrl + C退出：
    3  3
    2.5 ,2 1,2
    Invalid number format.
    请输入测试用例或按Ctrl + C退出：
    4 5
    1   ,   12,  1;
    [W] [W] [W] [W] [W] [W] [W] [W] [W] [W] [W]
    [W] [R] [W] [R] [W] [R] [W] [R] [W] [R] [W]
    [W] [W] [W] [W] [W] [W] [W] [W] [W] [W] [W]
    [W] [R] [W] [R] [W] [R] [W] [R] [W] [R] [W]
    [W] [W] [W] [R] [W] [W] [W] [W] [W] [W] [W]
    [W] [R] [W] [R] [W] [R] [W] [R] [W] [R] [W]
    [W] [W] [W] [W] [W] [W] [W] [W] [W] [W] [W]
    [W] [R] [W] [R] [W] [R] [W] [R] [W] [R] [W]
    [W] [W] [W] [W] [W] [W] [W] [W] [W] [W] [W]
    请输入测试用例或按Ctrl + C退出：
    I^C
    C:\Users\Galileo\source\repos\Maze\bin>

### 感言
  非常感谢ThoughtWorks，让我学到了那么多的东西。作为完全没有上过计算机课的

非计算机专业的学生，这些年来全凭兴趣坚持了下来，多年前的一个夜晚独自写出有界

面的贪吃蛇的时候，那种激动人心的感觉让我永远难以忘怀，我知道我热爱什么。上一

次参加ThoughtWorks线下结对编程活动没能拿奖，回来恶补了HTML/JavaScript/CSS/

Rect.js一系列的前端知识，只为了做出比第一名更好的效果，最后我应该也做到了。这

次笔试题，前前后后用三种不同的方式实现了，也顺便开启了单元测试的新大门，收获满

满。最后，希望将来能进入ThoughtWorks学到更多的东西。   

BY：骆小俊 2018-7-29 19:30:09