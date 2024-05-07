#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <GL/freeglut.h>                  
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

// 전역 변수
struct POINT2D // 마우스 클릭 좌표 -> 벡터에 저장
{
	float x;
	float y;
};
vector<POINT2D> pointVector; // 지금까지 좌표를 저장할 벡터
GLint pointCount = 0; // 현재 벡터 개수
GLfloat WindowSizeWidth = 1000.0;
GLfloat WindowSizeHeight = 500.0;

// 함수
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 1.0, 0.0);
	glPointSize(5.0f);

	glBegin(GL_POINTS);

	// Vector를 순회하면서 glVertex2f 실행 -> Polygon 생성
	for (const auto& point : pointVector)
	{
		glVertex2f(point.x, point.y);
	}

	glEnd();
	glFlush();
}

// 클릭한 위치에 점 찍기
void AddPoint(int button, int state, int x, int y)
{
	// 마우스 왼쪽 클릭 이벤트
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		POINT2D point;

		/***********************************************************************************/
		/***********************************************************************************/

		// -2 ~ 2 (Hard coding)
		//point.x = 2.0 * (x * 2.0 / WindowSizeWidth - 1.0);
		//point.y = -((y * 2.0 / WindowSizeHeight) - 1.0);
		
		point.x = (WindowSizeWidth / WindowSizeHeight) * (x * 2.0 / WindowSizeWidth - 1.0);
		point.y = -((y * 2.0 / WindowSizeHeight) - 1.0);

		/***********************************************************************************/
		/***********************************************************************************/

		cout << point.x << ", " << point.y << endl;
		pointVector.push_back(point);
		pointCount++;
		display();
	}
}

// 마우스 오른쪽 클릭 메뉴
void MouseEventMain(int entryID)
{
	// drawPolygon
	if (entryID == 1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glShadeModel(GL_FLAT);
		glBegin(GL_POLYGON);
		glColor3f(0.0, 1.0, 0.0);
		for (const auto& point : pointVector) // 벡터를 순회하면서 glVertex2f 실행
		{
			glVertex2f(point.x, point.y);
		}
		glEnd();
		glFlush();
	}

	// clearProgram
	if (entryID == 2)
	{
		// 화면 초기화
		glClear(GL_COLOR_BUFFER_BIT); // 화면 지우기
		glutPostRedisplay();

		// pointVector 비우기
		pointVector.clear();
	}

	// exitProgram
	if (entryID == 3)
	{
		exit(0);
	}
}

// 메뉴 등록
void EnterMenu()
{
	GLint MouseEventMainID = glutCreateMenu(MouseEventMain);
	glutAddMenuEntry("Polygon", 1);
	glutAddMenuEntry("Clear", 2);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// 프로그램 실행
int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // Single/Double buffer, Color Space, Depth/stencil/multisampling
	glutInitWindowSize(WindowSizeWidth, WindowSizeHeight);
	glutInitWindowPosition(100, 100); // Specify the screen location for the upper-left corner of the window
	// glutInitContextVersion : Specify which version of OpenGL want to use
	// glutInitContextFlags : Specify the type of OpenGL context
	// glutCreateWindow : Create a window with an OpenGL context
	glutCreateWindow(argv[0]);
	//glOrtho(-2.0, -1.0, 2.0, 1.0, -1.0, -1.0);
	gluOrtho2D(-2.0, 2.0, -1.0, 1.0);
	EnterMenu();
	glutDisplayFunc(display); // Put all the routines need to redraw the scene
	glutMouseFunc(AddPoint);
	glutMainLoop(); // Event processing begins, and the registered display callback is triggered
}