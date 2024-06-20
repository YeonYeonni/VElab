//-----------------------------------------------------------------------------
//           Name: 3D_viewing_manipulation.cpp
//         Author: Young Ho Chai
//  Last Modified: 05/16/16
//    Description: This sample demonstrates how adjustments to OpenGL's 
//                 viewing position effect the view.
//
//   Control: Left Mouse Click & Drag Up     - Viewer moves upward
//            Left Mouse Click & Drag Down   - Viewer moves downward
//            Left Mouse Click & Drag Left   - Viewer moves leftward
//            Left Mouse Click & Drag Right  - Viewer moves rightward
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
#include <gl/freeglut.h>

GLfloat Vertex[20][3], VertexB[20][3]; //Vertex array for front & back faces
GLint NumVertex = 0;                   //Number of vertices
GLint AddInputMode = 1;                //1:Input, 2:Translation, 3:Orthographic/Perspective View
GLboolean ProjectionMode = GL_TRUE;    //TRUE:Orthographic, FALSE:Perspective
GLfloat mx, my;                        //Mouse picking position 
GLfloat mdx = 0.0, mdy = 0.0;          //Mouse dragging position
GLfloat tx, ty;                        //Amount of translation
GLfloat tx_old = 0.0, ty_old = 0.0;    //Accumulated translation
GLfloat centerx, centery, centerz;     //Center of the polygon
GLfloat bx_up = -1.0, by_up = -1.0, bx_lo = 1.0, by_lo = 1.0; //Bounding box of vertices
GLfloat fov, slope, dx, dy; // �þ߰�, ���, �̵���

GLfloat scale = 1.0;
GLfloat theta = 0.0, angle = 0.0;
GLfloat M[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }; // 4 x 4 modelview matrix
GLfloat axisRotateX = 0.0, axisRotateY = 0.0, axisRotateZ = 0.0; // ȸ����

//-----------------------------------------------------------------------------
// mouse click callback function
//-----------------------------------------------------------------------------
void AddInput(int button, int state, int x, int y){
	
	mx = (x - 250.) / 250.; //Mouse click position
	my = (250. - y) / 250.;

	if (AddInputMode == 1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (my < by_lo) by_lo = my;  //Bounding box calculation(y)
		if (my > by_up) by_up = my;

		if (mx < bx_lo) bx_lo = mx;  //Bounding box calculation(x)
		if (mx > bx_up) bx_up = mx;

		Vertex[NumVertex][0] = mx;   //Vertices for frontal face
		Vertex[NumVertex][1] = my;
		Vertex[NumVertex][2] = 0.0;
		VertexB[NumVertex][0] = mx;  //Vertices for back face
		VertexB[NumVertex][1] = my;

		NumVertex++;
	} 
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		glGetFloatv(GL_MODELVIEW_MATRIX, M); // ���� �𵨺� ����� M�� ����
		M[12] = 0.0; // Translate ���ڸ� ����. ���� multmatrix�� translate�� �����Ű�� �ʱ� ����
		M[13] = 0.0;
		M[14] = 0.0;

		if (AddInputMode == 2)  //Accumulated translation with mouse relese in translation mode  
		{
			tx_old += tx;
			ty_old += ty;
		}
	}

	//Redraw the scene in the display callback function
	glutPostRedisplay();
}

//-----------------------------------------------------------------------------
// mouse drag callback function
//-----------------------------------------------------------------------------
void MouseDrag(int x, int y){

	mdx = (x - 250.) / 250.;  // Mouse dragging position
	mdy = (250. - y) / 250.;

	tx = mdx - mx;  // Mouse dragging diatance
	ty = mdy - my;
	
	// ���콺 �巡�� ���⿡ ������ ������ ����
	slope = (mdx - mx) / (mdy - my); //Slope of the normal line of mouse drag direction

	// Unit normal vector
	if (mdy < my) dx = sqrt(1.0 / (1. + slope*slope));  // Unit normal vector(x)
	else dx = -sqrt(1.0 / (1. + slope*slope));

	dy = -slope*dx;  // Unit normal vector(y)

	theta = atan(dy / dx)*180. / 3.14; // x��� ���� ������ ����

	if (my == mdy) theta = 90.;
	if (mdy > my) theta += 180.;


	angle = sqrt((mdy - my)*(mdy - my) + (mdx - mx)*(mdx - mx))*180. / 3.14*4.; // ȸ�� ����

    glMatrixMode(GL_MODELVIEW); //Set-up for the modeling & viewing matrix
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0, 1, 0);

	if (AddInputMode == 2) // Translation
	{
		theta = 0.0;
		angle = 0.0;
		scale = 1.0;
		glTranslatef(tx, ty, 0.0);
	}
	else if (AddInputMode == 3) // Rotation
	{
		scale = 1.0;
	}
	else if (AddInputMode == 4) // Rotation about Z
	{
		theta = 0.0;
		scale = 1.0;
	}
	else if (AddInputMode == 5) // Rotate Axis
	{
		axisRotateX += (mdy - my) * 180. / 3.14;
		axisRotateY += (mdx - mx) * 180. / 3.14;
	}
	else if (AddInputMode == 6) // Scaling
	{
		theta = 0.0;
		angle = 0.0;
		scale = abs(1.0 + ty/2.0);
	}

	glTranslatef(tx_old, ty_old, 0.0);
	glTranslatef(centerx, centery, centerz);
	glRotatef(theta, 0., 0., 1.);

	if (AddInputMode == 3) glRotatef(angle, 1., 0., 0.); // Rotate XY
	if (AddInputMode == 4) glRotatef(-tx * 180./3.14, 0., 0., 1.); // Rotate Z
	if (AddInputMode == 5) // Rotate axis
	{
		glRotatef(axisRotateX, 1.0, 0.0, 0.0);
		glRotatef(axisRotateY, 0.0, 1.0, 0.0);
	}
	glRotatef(-theta, 0., 0., 1.);
	glMultMatrixf(M); // �𵨺� ��ȯ ����
	glScalef(scale, scale, scale);
	glTranslatef(-centerx, -centery, -centerz);

	// Redraw the scene in the display callback function
	glutPostRedisplay();
}

//-----------------------------------------------------------------------------
// display callback function
//-----------------------------------------------------------------------------
void Display()
{
	int i;

	//Clear the color & depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (AddInputMode == 1){ // Vertices only
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POINTS);
		for (i = 0; i < NumVertex; i++){
			glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
		}
		glEnd();
    }
	else{
		// Back face
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POLYGON);
		for (i = 0; i < NumVertex; i++){
			glVertex3f(VertexB[i][0], VertexB[i][1], VertexB[i][2]);
		}
		glEnd();

		// Lines between faces
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		for (i = 0; i < NumVertex; i++){
			glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
			glVertex3f(VertexB[i][0], VertexB[i][1], VertexB[i][2]);
		}
		glEnd();

		// Front face
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POLYGON);
		for (i = 0; i < NumVertex; i++){
			glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
		}
		glEnd();

		//Center of the front face
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
			glVertex3f(centerx, centery, centerz);
		glEnd();

		// Polygon
		glPushMatrix(); // ���� ��� ���¸� ��� ���ÿ� ����
			glLoadIdentity(); // ���� �𵨺� ��� �ʱ�ȭ
			glLineWidth(5.0);

			// ���콺 �巡�� ���� (���)
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_LINES);
			glVertex3f(mx, my, 0.0); // ���콺 Ŭ�� ��ġ (mx, my)
			glVertex3f(mdx, mdy, 0.0); // ���콺 �巡�� ��ġ (mdx, mdy)
			glEnd();

			glTranslatef(mx, my, 0.0);

			// ���콺 �巡�� ����� ������ �� (����) (dx, dy)
			glColor3f(0.0, 1.0, 0.0); 
			glBegin(GL_LINES);
			glVertex3f(dx, dy, 0.0); // Unit Vector (dx, dy)
			glVertex3f(-dx, -dy, 0.0);
			glEnd();

			glLineWidth(1.0);
		glPopMatrix(); // ��� ���ÿ��� �ֻ��� ����� �����ϰ� ����

		// Draw the coordinate axis
		glPushMatrix(); // ���� ��� ���¸� ��� ���ÿ� ����
			glLoadIdentity();
			glRotatef(axisRotateX, 1.0, 0.0, 0.0);
			glRotatef(axisRotateY, 0.0, 1.0, 0.0);
			glLineWidth(2.0);

			glBegin(GL_LINES);
			// X-axis (Red) 
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(1.0, 0.0, 0.0);
			// Y-axis (Green)
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 1.0, 0.0);
			// Z-axis (Blue)
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, 1.0);
			glEnd();
		glPopMatrix(); // ��� ���ÿ��� �ֻ��� ����� �����ϰ� ����
	}
	
	//Force execution of GL commands in finite time
	glFlush();
}

//-----------------------------------------------------------------------------
// initiate graphics for the application
//-----------------------------------------------------------------------------
void InitGraphics(void)
{
	// Initialize graphics primitives
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glShadeModel(GL_SMOOTH);
	glPointSize(5.0);

	// Set-up view volume for the application
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ProjectionMode){
		glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 10.0);
	}
	else{
		//viewer(0, 0, 5) -> (1, 1, 0) : (-1, -1, 0)
		/*
			atan : ź��Ʈ���� ���� ������ ���� ������ ��ȯ
			0.5 : ���� �ݳ��̸� ī�޶�κ����� �Ÿ��� ���� ����. (���� �ݳ��� : ���� �������� ī�޶� ������ �Ÿ��������� ���÷����� �ٶ󺸴� ������ ����)
			* 180. / 3.14 : ���� ���� ������ ��ȯ. 3.14 (phi) �� ���� 180�� ����
			* 2.0 : ���ݱ����� ����� ���� �ݳ��̿� ���� ����. ��ü �þ߰��� ��� ���� 2�� ���� => ī�޶󿡼� ���� ��� ~ ���� �ϴ� ���� �ϼ�
		*/
		fov = atan(0.5) * 180. / 3.14 * 2.0;
		gluPerspective(fov, 1.0, 0.1, 10.0);
	}

	// Set-up the original view vector
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, M); // ���� �𵨺� ����� M�� ����
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0, 1, 0);
}

//-----------------------------------------------------------------------------
// menu function of a windows application
//-----------------------------------------------------------------------------
void MyMenu(int value)
{
	int i;

	switch (value){
	    case 1: // Calculate center of vertices
			AddInputMode = 0;
			centerx = 0.;
			centery = 0.;
			centerz = -(abs(bx_up - bx_lo) + abs(by_up - by_lo)) / 4.0;  // Half of the BB
			for (i = 0; i < NumVertex; i++){
				centerx += Vertex[i][0];
				centery += Vertex[i][1];
				VertexB[i][2] = centerz*2.;
			}
			centerx /= NumVertex;
			centery /= NumVertex;
			break;
		case 2: // Translation of the polygon
			AddInputMode = 2;
			break;
		case 3: // Rotation of the polygon
			AddInputMode = 3;
			break;
		case 4: // Rotation about the Z axis
			AddInputMode = 4;
			break;
		case 5: // Rotation of the axis
			AddInputMode = 5;
			break;
		case 6: // Scaling of the polygon
			AddInputMode = 6;
			break;
		case 7: // Toggle the projection mode
			AddInputMode = 7;
			ProjectionMode = !ProjectionMode;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			if (ProjectionMode){
				glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 10.0);
			}
			else{
				fov = atan(0.5) * 180. / 3.14 * 2.0;   // viewer(0, 0, 5) -> (1, 1, 0):(-1, -1, 0)
				gluPerspective(fov, 1.0, 0.1, 10.0);
			}
			break;
		case 8: // Reset the view
			AddInputMode = 0;
			angle = 0;
			theta = 0;
			tx_old = 0.0;
			ty_old = 0.0;
			InitGraphics();
			break;
		case 9: // Clear the vertices & reset the view
			AddInputMode = 1;
			NumVertex = 0;
			ProjectionMode = GL_TRUE;
			tx_old = 0.0;
			ty_old = 0.0;
			bx_up = -1.0; by_up = -1.0; bx_lo = 1.0; by_lo = 1.0;
			InitGraphics();
			break;
		case 10:
			exit(0);
	}
	
	//Redraw the scene in the display callback function
	glutPostRedisplay();
}

//-----------------------------------------------------------------------------
// main function of a windows application
//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
	// Initialize FreeGLUT
	glutInit(&argc, argv);

	// Create Single Buffered Window
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
    glutCreateWindow("Assignment3");

	// Initialize OpenGL graphics state
	InitGraphics();

	// Register Callbacks:
	glutDisplayFunc(Display);
	glutMouseFunc(AddInput);
	glutMotionFunc(MouseDrag);
	
	// Create Pull-down Menu:
	glutCreateMenu(MyMenu);
	glutAddMenuEntry("Polygon", 1);
	glutAddMenuEntry("Translation", 2);
	glutAddMenuEntry("Rotate", 3);
	glutAddMenuEntry("Rotate about Z", 4);
	glutAddMenuEntry("Rotate axis", 5);
	glutAddMenuEntry("Scale", 6);
	glutAddMenuEntry("Orthographic/Perspective", 7);
	glutAddMenuEntry("Reset", 8);
	glutAddMenuEntry("Clear", 9);
	glutAddMenuEntry("Exit", 10);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Start GLUT main loop
	glutMainLoop();

	return 0;
}