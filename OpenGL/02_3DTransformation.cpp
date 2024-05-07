#include <stdio.h>
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

GLfloat Vertex[50][3]; // Front plane vertices
GLfloat VertexBack[50][3]; // Back plane vertices
GLint NumVertex = 0; // Num of vertices
GLfloat WindowSizeWidth = 500.0, WindowSizeHeight = 500.0; // WindowSize
GLint AddInputMode = 1; // 1 : Input & 2 : Translation & 3, 4 : Rotation & 5 : Scale
GLfloat mx = 0.0, my = 0.0; // 마우스 클릭 위치
GLfloat mdx = 0.0, mdy = 0.0; // 마우스 놓은 위치
GLfloat tx = 0.0, ty = 0.0; // 마우스를 누른 채로 이동한 거리
GLfloat tx_old = 0.0, ty_old = 0.0; // 마우스를 누른 채로 이동한 거리 (누적)
GLfloat scale = 1.0; // Scaling rate
GLfloat centerx, centery, centerz; // Center of vercites
GLfloat zlength = 0.0;
GLfloat bx_up = -1.0, by_up = -1.0, bx_down = 1.0, by_down = 1.0; // Bbox of polygon
GLfloat fov; // Perspective fov
GLboolean isPerspective = false; // Toggle of perspective
GLfloat t[] = { 0.0, 0.0, 0.0 }; // Rotation angle of each axis

void AddInput(int button, int state, int x, int y) 
{
	mx = (x * 2.0 / WindowSizeWidth - 1.0);
	my = -((y * 2.0 / WindowSizeHeight) - 1.0);

	if (AddInputMode == 1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// 마우스를 누른 위치가 기존 bbox보다 안쪽이면 갱신
		//Bbox (y)
		if (my < by_down)
			by_down = my;
		if (my > by_up)
			by_up = my;

		//Bbox (x)
		if (mx < bx_down)
			bx_down = mx;
		if (mx > bx_up)
			bx_up = mx;

		// Front
		Vertex[NumVertex][0] = mx;
		Vertex[NumVertex][1] = my;
		Vertex[NumVertex][2] = 0.0;

		// Back
		VertexBack[NumVertex][0] = mx;
		VertexBack[NumVertex][1] = my;
		Vertex[NumVertex][2] = 0.0;

		NumVertex++;
	}
	else if (AddInputMode == 2 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		// 마우스 놓을 때 이동 거리를 누적
		tx_old += tx;
		ty_old += ty;
	}
	glutPostRedisplay();
}

void MouseDrag(int x, int y) 
{
	GLfloat centertx, centerty;
	mdx = (x * 2.0 / WindowSizeWidth - 1.0);
	mdy = -((y * 2.0 / WindowSizeHeight) - 1.0);

	// View matrix 초기화
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	if (AddInputMode == 2)
	{
		tx = mdx - mx;
		ty = mdy - my;
		glTranslatef(tx, ty, 0.0);
	}
	else if (AddInputMode == 3)
	{
		t[1] += -(mdx - mx) * 10.0 / 3.14;
		t[2] += -(mdy - my) * 10.0 / 3.14;
	}
	else if (AddInputMode == 4)
	{
		t[0] += -(mdx - mx) * 10.0 / 3.14;
	}
	else if (AddInputMode == 5)
	{
		scale *= (1.0 + (mdy - my) / 100.0);
	}
	glTranslatef(tx_old, ty_old, 0.0);
	glTranslatef(centerx, centery, centerz);
	glRotatef(t[0], 0.0, 0.0, 1.0); // 도형을 z축을 중심으로 회전 -> 도형의 xy 평면에 영향
	glRotatef(t[1], 0.0, 1.0, 0.0); // 도형을 y축을 중심으로 회전 -> 도형의 xz 평면에 영향
	glRotatef(t[2], 1.0, 0.0, 0.0); // 도형을 x축을 중심으로 회전 -> 도형의 yz 평면에 영향
	glScalef(scale, scale, scale);
	glTranslatef(-centerx, -centery, -centerz);
	glutPostRedisplay();
}

void Reshape(GLint width, GLint height)
{
	// 창 크기 업데이트
	WindowSizeWidth = width;
	WindowSizeHeight = height;

	// Viewport 설정
	glViewport(0, 0, width, height);

	// Projection matrix 설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (isPerspective)
	{
		gluPerspective(fov, 1.0, 0.0, 10.0); // fov, aspect, zNear, zFar
		isPerspective = false;
	}
	else
	{
		glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 10.0); // left, right, bottom, top, zNear, zFar
		isPerspective = true;
	}
	// Modelview matrix로 복귀
	glMatrixMode(GL_MODELVIEW);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glPointSize(5.0);

	if (AddInputMode == 1)
	{
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POINTS);
		for (int i = 0; i < NumVertex; i++) {
			glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
		}
		glEnd();
	}
	else
	{
		// Line
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		for (int i = 0; i < NumVertex; i++)
		{
			glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
			glVertex3f(VertexBack[i][0], VertexBack[i][1], VertexBack[i][2]);
		}
		glEnd();

		// Point
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
		glVertex3f(centerx, centery, centerz);
		glEnd();

		// Back
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < NumVertex; i++)
		{
			glVertex3f(VertexBack[i][0], VertexBack[i][1], VertexBack[i][2]);
		}
		glEnd();

		// Front
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < NumVertex; i++)
		{
			glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
		}
		glEnd();
	}
	glFlush();
}

void Clear()
{
	mx = 0.0, my = 0.0;
	mdx = 0.0, mdy = 0.0;
	t[0] = 0.0, t[1] = 0.0, t[2] = 0.0;
	scale = 1.0;
	tx_old = 0.0, ty_old = 0.0;
	bx_up = -1.0; by_up = -1.0; bx_down = 1.0; by_down = 1.0;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -0.1, 10.0);
	isPerspective = true;
	glMatrixMode(GL_MODELVIEW);
}

void MyMenu(int value)
{
	switch (value) {
	case 1:
		AddInputMode = 0;
		centerx = 0.0;
		centery = 0.0;
		zlength = -(abs(bx_up - bx_down) + abs(by_up - by_down)) / 2.0;
		centerz = zlength / 2.0;
		for (int i = 0; i < NumVertex; i++) {
			centerx += Vertex[i][0];
			centery += Vertex[i][1];
			VertexBack[i][2] = centerz * 2;
		}
		centerx /= NumVertex;
		centery /= NumVertex;
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
		break;
	case 6: // Clear
		NumVertex = 0;
		for (int i = 0; i < 50; i++)
		{
			Vertex[i][0] = 0.0;
			Vertex[i][1] = 0.0;
			Vertex[i][2] = 0.0;
			VertexBack[i][0] = 0.0;
			VertexBack[i][1] = 0.0;
			VertexBack[i][2] = 0.0;
		}
		Clear();
		AddInputMode = 1;
		glLoadIdentity();
		break;
	case 7: // Reset
		glTranslatef(-tx_old, -ty_old, 0.0);
		glTranslatef(centerx, centery, centerz);
		glRotatef(-t[2], 0.0, 0.0, 1.0);
		glRotatef(-t[1], 0.0, 1.0, 0.0);
		glRotatef(-t[0], 1.0, 0.0, 0.0);
		glScalef(1.0 / scale, 1.0 / scale, 1.0 / scale);
		glTranslatef(-centerx, -centery, -centerz);
		Clear();
		AddInputMode = 2;
		glLoadIdentity();
		break;
	case 8:
		AddInputMode = 8;
		fov = 90.0;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (isPerspective)
		{
			gluPerspective(fov, 1.0, 0.1, 10.0);
			isPerspective = false;
		}
		else
		{
			glOrtho(-1.0, 1.0, -1.0, 1.0, -0.1, 10.0);
			isPerspective = true;
		}
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

		// 이전에 적용된 변환들을 다시 적용
		glTranslatef(tx_old, ty_old, 0.0);
		glTranslatef(centerx, centery, centerz);
		glRotatef(t[0], 0.0, 0.0, 1.0);
		glRotatef(t[1], 0.0, 1.0, 0.0);
		glRotatef(t[2], 1.0, 0.0, 0.0);
		glScalef(scale, scale, scale);
		glTranslatef(-centerx, -centery, -centerz);
		break;
	case 9:
		exit(0);
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WindowSizeWidth, WindowSizeHeight);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("3D Transformation");
	glutCreateMenu(MyMenu);
	glutAddMenuEntry("Polygon", 1);
	glutAddMenuEntry("Translate", 2);
	glutAddMenuEntry("Rotate xy", 3);
	glutAddMenuEntry("Rotate z", 4);
	glutAddMenuEntry("Scale", 5);
	glutAddMenuEntry("Clear", 6);
	glutAddMenuEntry("Reset", 7);
	glutAddMenuEntry("Ortho/Perspective", 8);
	glutAddMenuEntry("Exit", 9);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMotionFunc(MouseDrag);
	glutDisplayFunc(Display);
	glutMouseFunc(AddInput);
	glutReshapeFunc(Reshape);

	glutMainLoop();
	return 0;
}