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

// ���� ����
struct POINT2D // ���콺 Ŭ�� ��ǥ -> ���Ϳ� ����
{
	float x;
	float y;
};
vector<POINT2D> pointVector; // ���ݱ��� ��ǥ�� ������ ����
GLint pointCount = 0; // ���� ���� ����
GLfloat WindowSizeWidth = 1000.0;
GLfloat WindowSizeHeight = 500.0;

// �Լ�
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 1.0, 0.0);
	glPointSize(5.0f);

	glBegin(GL_POINTS);

	// Vector�� ��ȸ�ϸ鼭 glVertex2f ���� -> Polygon ����
	for (const auto& point : pointVector)
	{
		glVertex2f(point.x, point.y);
	}

	glEnd();
	glFlush();
}

// Ŭ���� ��ġ�� �� ���
void AddPoint(int button, int state, int x, int y)
{
	// ���콺 ���� Ŭ�� �̺�Ʈ
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

// ���콺 ������ Ŭ�� �޴�
void MouseEventMain(int entryID)
{
	// drawPolygon
	if (entryID == 1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glShadeModel(GL_FLAT);
		glBegin(GL_POLYGON);
		glColor3f(0.0, 1.0, 0.0);
		for (const auto& point : pointVector) // ���͸� ��ȸ�ϸ鼭 glVertex2f ����
		{
			glVertex2f(point.x, point.y);
		}
		glEnd();
		glFlush();
	}

	// clearProgram
	if (entryID == 2)
	{
		// ȭ�� �ʱ�ȭ
		glClear(GL_COLOR_BUFFER_BIT); // ȭ�� �����
		glutPostRedisplay();

		// pointVector ����
		pointVector.clear();
	}

	// exitProgram
	if (entryID == 3)
	{
		exit(0);
	}
}

// �޴� ���
void EnterMenu()
{
	GLint MouseEventMainID = glutCreateMenu(MouseEventMain);
	glutAddMenuEntry("Polygon", 1);
	glutAddMenuEntry("Clear", 2);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// ���α׷� ����
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