#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <GL/freeglut.h>                  
#include <iostream>
using namespace std;

GLfloat pointArray[100];
GLfloat pointReset[100];
GLint pointCount = 0;
GLfloat WindowSizeWidth = 500.0;
GLfloat WindowSizeHeight = 500.0;
GLint AddInputMode = 1; // Transformation 종류
GLfloat centerx, centery; // 도형의 중점
GLfloat prevX, prevY; // 이전 마우스 위치

GLfloat toOrigin[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, };
GLfloat goBack[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, };
GLfloat Translation[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, };
GLfloat Rotation[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, };
GLfloat Scaling[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, };

void AddPoint(GLint button, GLint state, GLint x, GLint y)
{
	int index = pointCount * 3;
	GLfloat mx = (x * 2.0 / WindowSizeWidth - 1.0);
	GLfloat my = -((y * 2.0 / WindowSizeHeight) - 1.0);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && AddInputMode == 1)
	{
		pointArray[index + 0] = mx;
		pointArray[index + 1] = my;
		pointArray[index + 2] = 1.0;

		pointReset[index + 0] = mx;
		pointReset[index + 1] = my;
		pointReset[index + 2] = 1.0;

		pointCount++;
	}

	glutPostRedisplay();
}

void Display()
{
	int index = pointCount * 3;

	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glPointSize(5.0);

	if (AddInputMode == 1)
	{
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POINTS);
		for (int i = 0; i < index; i+=3) 
		{
			glVertex2f(pointArray[i + 0], pointArray[i + 1]);
		}
		glEnd();
	}
	else if (AddInputMode == 5)
	{
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < index; i += 3)
		{
			glVertex2f(pointReset[i + 0], pointReset[i + 1]);
			pointArray[i + 0] = pointReset[i + 0];
			pointArray[i + 1] = pointReset[i + 1];
		}
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
		glVertex2f(centerx, centery);
		glEnd();
	}
	else
	{
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < index; i+=3)
		{
			glVertex2f(pointArray[i + 0], pointArray[i + 1]);
		}
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
		glVertex2f(centerx, centery);
		glEnd();
	}
	glFlush();
}

void MyMenu(int value)
{
	int index = pointCount * 3;

	switch (value)
	{
	case 1:
		AddInputMode = 0;
		centerx = 0.;
		centery = 0.;
		for (int i = 0; i < index; i+=3) 
		{
			centerx += pointArray[i + 0];
			centery += pointArray[i + 1];
		}
		centerx /= pointCount;
		centery /= pointCount;
		break;
	case 2:
		AddInputMode = 2;
		break;
	case 3:
		AddInputMode = 3;
		break;
	case 4:
		AddInputMode = 4;
		break;
	case 5:
		AddInputMode = 5;
		centerx = 0.;
		centery = 0.;
		for (int i = 0; i < index; i += 3)
		{
			centerx += pointReset[i + 0];
			centery += pointReset[i + 1];
		}
		centerx /= pointCount;
		centery /= pointCount;
		break;
	case 6:
		AddInputMode = 1;
		pointCount = 0;
		glLoadIdentity();
		break;
	case 7:
		exit(0);
	}
	glutPostRedisplay();
}

void MatMul(GLfloat transform[], GLfloat array[])
{
	for (int i = 0; i < pointCount; i++)
	{
		GLfloat oldX = array[i * 3];
		GLfloat oldY = array[i * 3 + 1];
		GLfloat oldZ = array[i * 3 + 2];

		array[i * 3 + 0] = transform[0] * oldX + transform[1] * oldY + transform[2] * oldZ;
		array[i * 3 + 1] = transform[3] * oldX + transform[4] * oldY + transform[5] * oldZ;
		array[i * 3 + 2] = transform[6] * oldX + transform[7] * oldY + transform[8] * oldZ;
	}
}

void MouseDrag(GLint x, GLint y)
{
	int index = pointCount * 3;

	GLfloat mdx = (x * 2.0 / WindowSizeWidth - 1.0);
	GLfloat mdy = -((y * 2.0 / WindowSizeHeight) - 1.0);

	// Translation
	if (AddInputMode == 2)
	{
		GLfloat tx = mdx - centerx;
		GLfloat ty = mdy - centery;

		toOrigin[2] = -centerx;
		toOrigin[5] = -centery;

		Translation[2] = tx;
		Translation[5] = ty;

		goBack[2] = centerx;
		goBack[5] = centery;

		glClear(GL_COLOR_BUFFER_BIT);

		MatMul(toOrigin, pointArray);
		MatMul(Translation, pointArray);
		MatMul(goBack, pointArray);

		glBegin(GL_POLYGON);
		for (int i = 0; i < index; i+=3)
		{
			glVertex2f(pointArray[i + 0], pointArray[i + 1]);
		}
		glEnd();

		centerx = mdx;
		centery = mdy;
	}

	// Rotation
	if (AddInputMode == 3)
	{
		GLfloat radian = 3.0 * 3.14 / 180.0f;

		toOrigin[2] = -centerx;
		toOrigin[5] = -centery;

		if (mdx - prevX > 0.0) // x값이 양수 (오른쪽) 이면 반시계방향
		{
			Rotation[0] = cos(radian);
			Rotation[1] = -sin(radian);
			Rotation[3] = sin(radian);
			Rotation[4] = cos(radian);
		}
		else if (mdx - prevX < 0.0) // x값이 음수 (왼쪽) 이면 시계방향
		{
			Rotation[0] = cos(radian);
			Rotation[1] = sin(radian);
			Rotation[3] = -sin(radian);
			Rotation[4] = cos(radian);
		}
		goBack[2] = centerx;
		goBack[5] = centery;

		glClear(GL_COLOR_BUFFER_BIT);
		MatMul(toOrigin, pointArray);
		MatMul(Rotation, pointArray);
		MatMul(goBack, pointArray);

		glBegin(GL_POLYGON);
		for (int i = 0; i < index; i += 3)
		{
			glVertex2f(pointArray[i + 0], pointArray[i + 1]);
		}
		glEnd();
	}

	// Scaling
	if (AddInputMode == 4)
	{
		GLfloat scalingSpeed = 0.7;
		GLfloat scaleRate = 1.0 + -(scalingSpeed * ((mdx - prevX + mdy - prevY) / 2));

		toOrigin[2] = -centerx;
		toOrigin[5] = -centery;

		Scaling[8] = scaleRate;

		goBack[2] = centerx;
		goBack[5] = centery;

		glClear(GL_COLOR_BUFFER_BIT);
		MatMul(toOrigin, pointArray);
		MatMul(Scaling, pointArray);
		MatMul(goBack, pointArray);

		for (int i = 0; i < index; i+=3)
		{
			pointArray[i + 0] = pointArray[i + 0] / pointArray[i + 2];
			pointArray[i + 1] = pointArray[i + 1] / pointArray[i + 2];
			pointArray[i + 2] = pointArray[i + 2] / pointArray[i + 2];
		}

		glBegin(GL_POLYGON);
		for (int i = 0; i < index; i+=3)
		{
			glVertex2f(pointArray[i + 0], pointArray[i + 1]);
		}
		glEnd();
	}

	prevX = mdx;
	prevY = mdy;
	glutPostRedisplay();
}

void Reshape(GLint width, GLint height)
{
	WindowSizeWidth = width;
	WindowSizeHeight = height;
	glViewport(0, 0, width, height);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WindowSizeWidth, WindowSizeHeight);
	glutInitWindowPosition(100, 100);

	glutCreateWindow(argv[0]);
	glutCreateMenu(MyMenu);
	glutAddMenuEntry("Polygon", 1);
	glutAddMenuEntry("Translate", 2);
	glutAddMenuEntry("Rotate", 3);
	glutAddMenuEntry("Scale", 4);
	glutAddMenuEntry("Reset", 5);
	glutAddMenuEntry("Clear", 6);
	glutAddMenuEntry("Exit", 7);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMotionFunc(MouseDrag);
	glutMouseFunc(AddPoint);

	glutMainLoop();
	return 0;
}