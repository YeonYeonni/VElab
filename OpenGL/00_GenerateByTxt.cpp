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
struct POINT2D  // ���콺 Ŭ�� ��ǥ -> ���Ϳ� ����
{
	float x;
	float y;
};
vector<POINT2D> pointVector; // ���ݱ��� ��ǥ�� ������ ����

// �Լ�
void txtLoad() // txt ������ �ҷ����� �Լ�
{
	string line;
	ifstream file("Polygon.txt");
	if (file.is_open())
	{
		// ������ �������� �б�
		while (getline(file, line))
		{
			POINT2D point; // Struct instance
			int num = sscanf(line.c_str(), "%f,%f", &point.x, &point.y); // Str->float

			// line�� ���� 2�� ��쿡�� vector�� �ֱ�
			if (num == 2)
			{
				pointVector.push_back(point);
			}
		}
		file.close();
	}
	else
	{
		cout << "Read Failed!";
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glBegin(GL_TRIANGLE_FAN);

	// Triangle
	// Color
	glColor3f(0.0, 1.0, 0.0);

	// Vector�� ��ȸ�ϸ鼭 glVertex2f ���� -> Polygon ����
	for (const auto& point : pointVector)
	{
		glVertex2f(point.x, point.y);
	}
	glEnd();
	glFlush();
}

// ���α׷� ����
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	txtLoad();
	glutDisplayFunc(display);
	glutMainLoop();
}