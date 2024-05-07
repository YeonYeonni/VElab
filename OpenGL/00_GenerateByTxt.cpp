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
struct POINT2D  // 마우스 클릭 좌표 -> 벡터에 저장
{
	float x;
	float y;
};
vector<POINT2D> pointVector; // 지금까지 좌표를 저장할 벡터

// 함수
void txtLoad() // txt 파일을 불러오는 함수
{
	string line;
	ifstream file("Polygon.txt");
	if (file.is_open())
	{
		// 파일을 한줄한줄 읽기
		while (getline(file, line))
		{
			POINT2D point; // Struct instance
			int num = sscanf(line.c_str(), "%f,%f", &point.x, &point.y); // Str->float

			// line의 수가 2일 경우에만 vector에 넣기
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

	// Vector를 순회하면서 glVertex2f 실행 -> Polygon 생성
	for (const auto& point : pointVector)
	{
		glVertex2f(point.x, point.y);
	}
	glEnd();
	glFlush();
}

// 프로그램 실행
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