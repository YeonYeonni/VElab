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
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "quaternion_utils.hpp"
GLFWwindow* window;

GLfloat Vertex[20][3], VertexB[20][3]; //Vertex array for front & back faces
GLint normalIndex = 0;
GLfloat resultVector[20][3];
GLint NumVertex = 0;                   //Number of vertices
GLint AddInputMode = 1;                //1:Input, 2:Translation, 3:Orthographic/Perspective View
GLboolean ProjectionMode = GL_TRUE;    //TRUE:Orthographic, FALSE:Perspective
GLboolean SurfaceNormalMode = GL_TRUE;
GLfloat mx, my;                        //Mouse picking position 
GLfloat mdx = 0.0, mdy = 0.0;          //Mouse dragging position
GLfloat tx, ty;                        //Amount of translation
GLfloat tx_old = 0.0, ty_old = 0.0;    //Accumulated translation
GLfloat centerx, centery, centerz;     //Center of the polygon
GLfloat bx_up = -1.0, by_up = -1.0, bx_lo = 1.0, by_lo = 1.0; //Bounding box of vertices
GLfloat fov, slope, dx, dy; // 시야각, 경사, 이동량

GLfloat scale = 1.0;
GLfloat theta = 0.0, angle = 0.0;
GLfloat M[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }; // 4 x 4 modelview matrix
GLfloat axisRotateX = 0.0, axisRotateY = 0.0, axisRotateZ = 0.0; // 회전축

// Lighting
// Back
GLfloat ambientLight0[] = { 0.3, 0.3, 0.3, 1.0 }; // RGBA (-1.0 ~ 1.0)
GLfloat diffuseLight0[] = { 1.0, 1.0, 0.0, 1.0 }; // RGBA (-1.0 ~ 1.0) -> Red (오른쪽에서 왼쪽)
GLfloat specularLight0[] = { 1.0, 1.0, 1.0, 1.0 }; // RGBA (-1.0 ~ 1.0)
GLfloat shininess0[] = { 25.0 }; // 0 ~ 128

// Front
GLfloat ambientLight1[] = { 0.3, 0.3, 0.3, 1.0 }; // RGBA (-1.0 ~ 1.0)
GLfloat diffuseLight1[] = { 1.0, 0.0, 1.0, 1.0 }; // RGBA (-1.0 ~ 1.0) -> Blue (왼쪽에서 오른쪽)
GLfloat specularLight1[] = { 1.0, 1.0, 1.0, 1.0 }; // RGBA (-1.0 ~ 1.0)
GLfloat shininess1[] = { 50.0 }; // 0 ~ 128

// Side
GLfloat ambientLight2[] = { 0.3, 0.3, 0.3, 1.0 }; // RGBA (-1.0 ~ 1.0)
GLfloat diffuseLight2[] = { 1.0, 1.0, 1.0, 1.0 }; // RGBA (-1.0 ~ 1.0) -> Blue (왼쪽에서 오른쪽)
GLfloat specularLight2[] = { 1.0, 1.0, 1.0, 1.0 }; // RGBA (-1.0 ~ 1.0)
GLfloat shininess2[] = { 75.0 }; // 0 ~ 128

// Light
GLfloat posLight0[] = { 0.5, 0.5, 2.5, 1.0 };
GLfloat posLight1[] = { -0.5, -0.5, -2.5, 1.0 };

// Material
GLfloat ambientMaterial1[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat diffuseMaterial1[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat specularMaterial1[] = { 1.0, 1.0, 1.0, 1.0 };

// Quaternion
float h_Angle = 0.0f;
float v_Angle = 0.0f;
float a_Angle = 0.0f;
float h_Angle_old = 0.0f;
float v_Angle_old = 0.0f;
float a_Angle_old = 0.0f;
glm::vec3 gPosition1(-1.5f, 0.0f, 0.0f);
glm::vec3 gPosition2(1.5f, 0.0f, 0.0f);
glm::quat gOrientation1;
glm::quat gOrientation2;

// For speed computation
double lastTime = glfwGetTime();
double lastFrameTime = lastTime;
int nbFrames = 0;

//-------------------------------------------------/----------------------------
// mouse click callback function
//-----------------------------------------------------------------------------
void AddInput(int button, int state, int x, int y) {
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
		glGetFloatv(GL_MODELVIEW_MATRIX, M); // 현재 모델뷰 행렬을 M에 저장
		M[12] = 0.0; // Translate 인자를 제거. 추후 multmatrix에 translate를 적용시키지 않기 위함
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
void MouseDrag(int x, int y) {

	mdx = (x - 250.) / 250.;  // Mouse dragging position
	mdy = (250. - y) / 250.;

	tx = mdx - mx;  // Mouse dragging diatance
	ty = mdy - my;

	// 마우스 드래그 방향에 수직한 직선의 기울기
	slope = (mdx - mx) / (mdy - my); //Slope of the normal line of mouse drag direction

	// Unit normal vector
	if (mdy < my) dx = sqrt(1.0 / (1. + slope * slope));  // Unit normal vector(x)
	else dx = -sqrt(1.0 / (1. + slope * slope));

	dy = -slope * dx;  // Unit normal vector(y)

	theta = atan(dy / dx) * 180. / 3.14; // x축과 빨간 선과의 각도

	if (my == mdy) theta = 90.;
	if (mdy > my) theta += 180.;


	glMatrixMode(GL_MODELVIEW); //Set-up for the modeling & viewing matrix
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0, 1, 0);

	// Measure speed
	double currentTime = glfwGetTime();
	float deltaTime = (float)(currentTime - lastFrameTime);
	lastFrameTime = currentTime;
	nbFrames++;
	if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1sec ago
		// printf and reset
		// printf("%f  %d  %f ms/frame\n",currentTime, nbFrames,  1000.0/double(nbFrames));
		nbFrames = 0;
		lastTime += 1.0;
	}

	// Compute Angle
	angle = sqrt((mdy - my) * (mdy - my) + (mdx - mx) * (mdx - mx)) * 180. / 3.14 * 4.; // 회전 각도

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

		// 1. Angle
		h_Angle += -0.005 * float(250 / 2 - x);
		v_Angle += -0.005 * float(250 / 2 - y);
		//glm::vec3 desiredDir = glm::vec3(sin(h_Angle) * glm::cos(-v_Angle) + 1.5f, glm::sin(-v_Angle), glm::cos(h_Angle) * glm::cos(-v_Angle));
		//glm::vec3 desiredUp = glm::vec3(0.0f, 1.f, 0.0f);

		// 2. Compute the desired orientation
		//glm::quat targetOrientation = normalize(LookAt(desiredDir, desiredUp));

		// 3. Create Quaternion and Interpolate
		gOrientation1 = glm::quat(glm::vec3(v_Angle, h_Angle, a_Angle));
		//gOrientation1 = RotateTowards(gOrientation1, targetOrientation, 5.0f * deltaTime); // 현재 쿼터니언을 목표 쿼터니언으로 보간
		//gOrientation2 = glm::quat(cos(h_Angle), desiredDir[0] * sin(h_Angle), desiredDir[1] * sin(h_Angle), desiredDir[2] * sin(h_Angle));

		// 4. Model Matrix
		glm::mat4 RotationMatrix = glm::mat4_cast(gOrientation1);
		//glm::mat4 RotationMatrix = glm::mat4_cast(gOrientation2 * gOrientation1);

		// 5. Transformation
		glTranslatef(centerx, centery, centerz); // 모델의 중심으로 이동
		glMultMatrixf(glm::value_ptr(RotationMatrix)); // 회전 적용
		glTranslatef(-centerx, -centery, -centerz); // 모델을 원래 위치로 이동
	}
	else if (AddInputMode == 4) // Rotation about Z
	{
		theta = 0.0;
		scale = 1.0;
	}
	else if (AddInputMode == 5) // Rotate Axis
	{
		axisRotateX = angle;
		axisRotateY = theta;
	}
	else if (AddInputMode == 6) // Scaling
	{
		theta = 0.0;
		angle = 0.0;
		scale = abs(1.0 + ty / 2.0);
	}

	glTranslatef(tx_old, ty_old, 0.0);
	glTranslatef(centerx, centery, centerz);
	glRotatef(theta, 0., 0., 1.);
	//if (AddInputMode == 3) glMultMatrixf(glm::value_ptr(RotationMatrix)); // 회전 적용
	if (AddInputMode == 4) glRotatef(-tx * 180. / 3.14, 0., 0., 1.); // Rotate Z
	glRotatef(-theta, 0., 0., 1.);
	glMultMatrixf(M);
	glScalef(scale, scale, scale);
	glTranslatef(-centerx, -centery, -centerz);

	// Redraw the scene in the display callback function
	glutPostRedisplay();
}

void drawAxis() {
	glPushMatrix();
	glLoadIdentity();
	glRotatef(axisRotateY, 0., 0., 1.);
	glRotatef(axisRotateX, 1.0, 0.0, 0.0);
	glRotatef(-axisRotateY, 0., 0., 1.);
	glLineWidth(2.0);

	// X-axis (Red)
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glEnd();

	// Y-axis (Green)
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glEnd();

	// Z-axis (Blue)
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 1.0);
	glEnd();

	glLineWidth(1.0);

	// Light position을 실시간으로 변환
	GLfloat matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	posLight0[0] = matrix[0] * 1.0 + matrix[12];
	posLight0[1] = matrix[4] * 0.0 + matrix[13];
	posLight0[2] = matrix[8] * -1.0 + matrix[14];

	posLight1[0] = matrix[0] * -1.0 + matrix[12];
	posLight1[1] = matrix[4] * 1.0 + matrix[13];
	posLight1[2] = matrix[8] * -1.0 + matrix[14];

	glPopMatrix();
}

// Point - Point = Vector
void PointToVector(GLfloat vertex1[3], GLfloat vertex2[3], GLfloat result[3])
{
	result[0] = vertex2[0] - vertex1[0];
	result[1] = vertex2[1] - vertex1[1];
	result[2] = vertex2[2] - vertex1[2];
}

void CrossProduct(GLfloat vector1[3], GLfloat vector2[3], GLfloat normal[3])
{
	normal[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
	normal[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
	normal[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];
}

void NormalizeVector(GLfloat vector[3])
{
	GLfloat len = 2.0 * sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
	if (len != 0)
	{
		vector[0] /= len;
		vector[1] /= len;
		vector[2] /= len;
	}
}

//-----------------------------------------------------------------------------
// display callback function
//-----------------------------------------------------------------------------
void Display()
{
	int i;

	//Clear the color & depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (AddInputMode == 1) { // Vertices only
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POINTS);
		for (i = 0; i < NumVertex; i++) {
			glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
		}
		glEnd();
	}
	else {
		// Point to Vector
		GLfloat v1[3], v2[3], v3[3], v4[3], v5[3], v6[3], v7[3], v8[3], v9[3];
		GLfloat SurfaceNormal[3] = { 0, 0, 0 };
		GLfloat VertexNormal[3] = { 0, 0, 0 };

		// SurfaceNormal
		if (SurfaceNormalMode)
		{
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINES);

			// Side Surface Normal
			for (int i = 0; i < NumVertex; i++) {

				int prev = (i - 1 + NumVertex) % NumVertex;
				int next = (i + 1) % NumVertex;

				PointToVector(Vertex[i], VertexB[i], v1);
				PointToVector(Vertex[i], Vertex[next], v2);
				CrossProduct(v1, v2, SurfaceNormal);
				NormalizeVector(SurfaceNormal);

				// Draw
				glVertex3f(Vertex[i][0] + v2[0] / 2, Vertex[i][1] + v2[1] / 2, centerz);
				glVertex3f(Vertex[i][0] + v2[0] / 2 + SurfaceNormal[0], Vertex[i][1] + v2[1] / 2 + SurfaceNormal[1], centerz + SurfaceNormal[2]);
			}

			// Front Surface Normal
			glVertex3f(centerx, centery, 0.0);
			glVertex3f(centerx, centery, 0.5);

			// Back Surface Normal
			glVertex3f(centerx, centery, centerz * 2);
			glVertex3f(centerx, centery, centerz * 2 - 0.5);

			glEnd();
		}

		// VertexNormal
		if (!SurfaceNormalMode)
		{
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINES);

			// Front Plane Vertex
			for (int i = 0; i < NumVertex; i++) {
				GLfloat VertexNormal[3] = { 0, 0, 0 };

				int prev = (i - 1 + NumVertex) % NumVertex;
				int next = (i + 1) % NumVertex;

				PointToVector(Vertex[i], VertexB[i], v1);
				PointToVector(Vertex[i], Vertex[next], v2);

				PointToVector(Vertex[prev], VertexB[prev], v3);
				PointToVector(Vertex[prev], Vertex[i], v4);

				PointToVector(Vertex[i], Vertex[next], v5);
				PointToVector(Vertex[i], Vertex[prev], v6);

				CrossProduct(v1, v2, SurfaceNormal);
				NormalizeVector(SurfaceNormal);

				VertexNormal[0] += SurfaceNormal[0];
				VertexNormal[1] += SurfaceNormal[1];
				VertexNormal[2] += SurfaceNormal[2];

				CrossProduct(v3, v4, SurfaceNormal);
				NormalizeVector(SurfaceNormal);
				VertexNormal[0] += SurfaceNormal[0];
				VertexNormal[1] += SurfaceNormal[1];
				VertexNormal[2] += SurfaceNormal[2];

				CrossProduct(v5, v6, SurfaceNormal);
				NormalizeVector(SurfaceNormal);
				VertexNormal[0] += SurfaceNormal[0];
				VertexNormal[1] += SurfaceNormal[1];
				VertexNormal[2] += SurfaceNormal[2];

				NormalizeVector(VertexNormal);

				glVertex3fv(Vertex[i]);
				glVertex3f(Vertex[i][0] + VertexNormal[0] * 0.5, Vertex[i][1] + VertexNormal[1] * 0.5, Vertex[i][2] + VertexNormal[2] * 0.5);
			}

			// Back Plane Vertex
			for (int i = 0; i < NumVertex; i++) {
				GLfloat VertexNormal[3] = { 0, 0, 0 };

				int prev = (i - 1 + NumVertex) % NumVertex;
				int next = (i + 1) % NumVertex;

				PointToVector(VertexB[i], Vertex[i], v1);
				PointToVector(VertexB[i], VertexB[next], v2);

				PointToVector(VertexB[prev], Vertex[prev], v3);
				PointToVector(VertexB[prev], VertexB[i], v4);

				PointToVector(VertexB[i], VertexB[next], v5);
				PointToVector(VertexB[i], VertexB[prev], v6);

				CrossProduct(v2, v1, SurfaceNormal);
				NormalizeVector(SurfaceNormal);
				VertexNormal[0] += SurfaceNormal[0];
				VertexNormal[1] += SurfaceNormal[1];
				VertexNormal[2] += SurfaceNormal[2];

				CrossProduct(v4, v3, SurfaceNormal);
				NormalizeVector(SurfaceNormal);
				VertexNormal[0] += SurfaceNormal[0];
				VertexNormal[1] += SurfaceNormal[1];
				VertexNormal[2] += SurfaceNormal[2];

				CrossProduct(v6, v5, SurfaceNormal);
				NormalizeVector(SurfaceNormal);
				VertexNormal[0] += SurfaceNormal[0];
				VertexNormal[1] += SurfaceNormal[1];
				VertexNormal[2] += SurfaceNormal[2];

				NormalizeVector(VertexNormal);

				glVertex3fv(VertexB[i]);
				glVertex3f(VertexB[i][0] + VertexNormal[0] * 0.5, VertexB[i][1] + VertexNormal[1] * 0.5, VertexB[i][2] + VertexNormal[2] * 0.5);
			}
			glEnd();
		}
		// Light position
		glLightfv(GL_LIGHT0, GL_POSITION, posLight0);
		glLightfv(GL_LIGHT1, GL_POSITION, posLight1);

		// Surfacenormal을 실시간으로 변환
		GLfloat matrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix); // 현재 모델뷰 매트릭스를 matrix에 가져옴
		SurfaceNormal[0] = matrix[0] * 1.0 + matrix[12];
		SurfaceNormal[1] = matrix[4] * 0.0 + matrix[13];
		SurfaceNormal[2] = matrix[8] * -1.0 + matrix[14];

		// Back face
		glBegin(GL_POLYGON);
		//glMaterialfv(GL_FRONT, GL_AMBIENT, ambientLight0);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseLight0);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight0);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess0);
		//glNormal3f(0.0, 0.0, 1.0); // Normal (x, y, z)
		glNormal3f(SurfaceNormal[0], SurfaceNormal[1], SurfaceNormal[2]);
		for (i = 0; i < NumVertex; i++) {
			glVertex3f(VertexB[i][0], VertexB[i][1], VertexB[i][2]);
		}
		glEnd();

		// Side faces
		glBegin(GL_QUAD_STRIP); //Side faces
		//glMaterialfv(GL_FRONT, GL_AMBIENT, ambientLight2);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseLight2);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight2);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess2);
		//glNormal3f(0.0, 0.0, 1.0); // Normal (x, y, z)
		glNormal3f(SurfaceNormal[0], SurfaceNormal[1], SurfaceNormal[2]);
		for (i = 0; i < NumVertex; i++) {
			glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
			glVertex3f(VertexB[i][0], VertexB[i][1], VertexB[i][2]);
		}
		glVertex3f(Vertex[0][0], Vertex[0][1], Vertex[0][2]);
		glVertex3f(VertexB[0][0], VertexB[0][1], VertexB[0][2]);
		glEnd();

		// Front face
		glBegin(GL_POLYGON);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambientLight1);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseMaterial1);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial1);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess1);
		//glNormal3f(0.0, 0.0, 1.0); // Normal (x, y, z)
		glNormal3f(SurfaceNormal[0], SurfaceNormal[1], SurfaceNormal[2]);
		for (i = 0; i < NumVertex; i++) {
			glVertex3f(Vertex[i][0], Vertex[i][1], Vertex[i][2]);
		}
		glEnd();

		//Center of the front face
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
		glVertex3f(centerx, centery, centerz);
		glEnd();

		// Light Sphere
		glPushMatrix();
		glLoadIdentity();
		glColor3f(0.0, 1.0, 0.0);
		glTranslatef(posLight0[0], posLight0[1], posLight0[2]);
		glutSolidSphere(0.1, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glLoadIdentity();
		glColor3f(0.0, 0.0, 1.0);
		glTranslatef(posLight1[0], posLight1[1], posLight1[2]);
		glutSolidSphere(0.1, 20, 20);
		glPopMatrix();
	}
	// Draw Axis
	drawAxis();

	//Force execution of GL commands in finite time
	glFlush();
}

//-----------------------------------------------------------------------------
// initiate graphics for the application
//-----------------------------------------------------------------------------
void InitGraphics(void)
{
	// Lighting 0
	glLightfv(GL_LIGHT0, GL_POSITION, posLight0);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Lighting 1
	glLightfv(GL_LIGHT1, GL_POSITION, posLight1);
	//glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);

	// 감쇠
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	//glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	//glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	// Set-up view volume for the application
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ProjectionMode) {
		glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 10.0);
	}
	else {
		fov = atan(0.5) * 180. / 3.14 * 2.0;
		gluPerspective(fov, 1.0, 0.1, 10.0);
	}

	// Set-up the original view vector
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, M); // 현재 모델뷰 행렬을 M에 저장
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0, 1, 0);

	// Initialize graphics primitives
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glShadeModel(GL_SMOOTH);
	glPointSize(5.0);
}

//-----------------------------------------------------------------------------
// menu function of a windows application
//-----------------------------------------------------------------------------
void MyMenu(int value)
{
	int i;

	switch (value) {
	case 1: // Calculate center of vertices
		AddInputMode = 0;
		centerx = 0.;
		centery = 0.;
		centerz = -(abs(bx_up - bx_lo) + abs(by_up - by_lo)) / 4.0;  // Half of the BB
		for (i = 0; i < NumVertex; i++) {
			centerx += Vertex[i][0];
			centery += Vertex[i][1];
			VertexB[i][2] = centerz * 2.;
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
		if (ProjectionMode) {
			glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 10.0);
		}
		else {
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
		axisRotateX = 0.0, axisRotateY = 0.0, axisRotateZ = 0.0;
		drawAxis();
		InitGraphics();
		break;
	case 9: // Clear the vertices & reset the view
		AddInputMode = 1;
		NumVertex = 0;
		ProjectionMode = GL_TRUE;
		tx_old = 0.0;
		ty_old = 0.0;
		bx_up = -1.0; by_up = -1.0; bx_lo = 1.0; by_lo = 1.0;
		axisRotateX = 0.0, axisRotateY = 0.0, axisRotateZ = 0.0;
		drawAxis();
		InitGraphics();
		break;
	case 10:
		exit(0);
	case 11: // Surface normal
		AddInputMode = 11;
		SurfaceNormalMode = !SurfaceNormalMode;
		break;
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
	glutAddMenuEntry("Surface/Vertex", 11);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Start GLUT main loop
	glutMainLoop();

	return 0;
}