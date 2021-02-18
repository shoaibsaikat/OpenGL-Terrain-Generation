/*--------------------------------------------------------------------
Name: Mina Shoaib Rahman Saikat
Roll: 0705096
Sec : B
CSE, BUET
---------------------------------------------------------------------*/
/*--------------------------------------------------------------------
Controls:
Left, right, up, down arrow for camera movement
x, X, y, Y, z, Z for spaceobj movement
' '(space) for showing or hiding structure
---------------------------------------------------------------------*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Position.h"
#include "Graphics Engine.h"
#include "Camera.h"

using namespace std;

#define BLACK		0, 0, 0
#define DISPHEIGHT	1024
#define DISPWIDTH	768
#define OFFSET		2
#define CAMVAL		1
#define CAMROT		0.05
#define AREA 100
#define DIFF 5

bool isWire = true, showAxis = false;
float red, green, blue;
Position obj = Position();

void resetView() {
	camReset();
	obj.reset();
	red = 1, green = 1, blue = 1;
}

const int totalPoints = (AREA * 2) / DIFF;

float zValue[totalPoints + 1][totalPoints + 1];

bool isValidIndex(int index) {
	if(index < 0 || index >= totalPoints)
		return false;
	return true;
}

bool binaryRand() {
	if(rand() / 1000 > 20)
		return true;
	return false;
}

int randValue() {
	return tan(rand()) / 40;
}

void initiatePoints() {
	for(int i = 0; i <= totalPoints; i++) {
		for(int j = 0; j <= totalPoints; j++) {
			zValue[i][j] = 0;
		}
	}
	for(int a = 0; a < 100; a++) {
		for(int i = 0; i <= totalPoints; i++) {
			for(int j = 0; j <= totalPoints; j++) {
				if(binaryRand())
					if(zValue[i][j] < 10)
						zValue[i][j] += randValue();
				else
					zValue[i][j] -= randValue();
			}
		}
	}
}

int zIndex(int i) {
	return (i + 100) / 5;
}

bool isHigh(float a, float b, float c, float d) {
	if(a < 0 && b < 0 && c < 0 && d < 0)
		return false;
	return true;
}

void drawArea() {
	M3DVector3f ver1, ver2, ver3, normal;
	
	glBegin(GL_QUAD_STRIP);
	
		for(int i = -AREA; i < AREA + DIFF; i  = i + DIFF) {
			for(int j = -AREA; j < AREA + DIFF; j = j + DIFF) {
				//glBindTexture(GL_TEXTURE_2D, mountain);
				glNormal3f(0, 0, 1);

				bool maxI, maxJ, minJ;
				maxI = i >= AREA ? false : true;
				maxJ = j >= AREA ? false : true;

				glTexCoord2f(0, 0); glVertex3f(i, j, zValue[zIndex(i)][zIndex(j)]);
				ver1[0] = i, ver1[1] = j, ver1[2] = zValue[zIndex(i)][zIndex(j)];

				if(maxJ) {
					glTexCoord2f(1, 0); glVertex3f(i , j + DIFF, zValue[zIndex(i)][zIndex(j + DIFF)]);
					ver2[0] = i, ver2[1] = j + DIFF, ver2[2] = zValue[zIndex(i)][zIndex(j + DIFF)];
				}
				if(maxI && maxJ) {
					glTexCoord2f(1, 1); glVertex3f(i + DIFF, j + DIFF, zValue[zIndex(i + DIFF)][zIndex(j + DIFF)]);
					ver3[0] = i + DIFF, ver3[1] = j + DIFF, ver3[2] = zValue[zIndex(i + DIFF)][zIndex(j + DIFF)];
				}
				m3dFindNormal(normal, ver3, ver2, ver1);
				m3dNormalizeVector(normal);
				glNormal3f(normal[0], normal[1], normal[2]);


				if(maxI) {
					glTexCoord2f(0, 1); glVertex3f(i + DIFF, j, zValue[zIndex(i + DIFF)][zIndex(j)]);
					ver1[0] = i + DIFF, ver1[1] = j, ver1[2] = zValue[zIndex(i + DIFF)][zIndex(j)];
				}
				m3dFindNormal(normal, ver1, ver2, ver3);
				m3dNormalizeVector(normal);
				glNormal3f(normal[0], normal[1], normal[2]);
			}
		}

	glEnd();
}

void display() {
	glClearColor(BLACK, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(posX, posY, posZ,		tarX, tarY, tarZ,	upX, upY, upZ);

	if (!isWire) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if(!showAxis) drawAxis();

	setLight0(0, 0, 50, 0,	red, green, blue);

	obj.translateObject();
	obj.rollObject();
	obj.pitchObject();
	obj.yawObject();
	

	/*------------------------------------------------*/
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, grass);
	glNormal3f(0, 0, 1);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0, 0); glVertex3f(AREA, AREA, 0);
		glTexCoord2f(1, 0); glVertex3f(-AREA, AREA, 0);
		glTexCoord2f(0, 1); glVertex3f(AREA, -AREA, 0);
		glTexCoord2f(1, 1); glVertex3f(-AREA, -AREA, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	/*------------------------------------------------*/

	/*------------------------------------------------*/
	double equ[4];
	equ[0] = 0;
	equ[1] = 0;
	equ[2] = 1;
	equ[3] = -0.01;
	glClipPlane(GL_CLIP_PLANE0, equ);
	glEnable(GL_CLIP_PLANE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mountain);
		drawArea();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CLIP_PLANE0);
	/*------------------------------------------------*/

	glutSwapBuffers();
}

void animate() {
	glutPostRedisplay();
}

void init(float h, float w) {
	red = 1, green = 1, blue = 1;

	glMatrixMode(GL_PROJECTION);
	loadImages();

	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	gluPerspective(30,	h/w,	0.1,	10000.0);

	glClearColor(BLACK, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
	setTarget(obj.getX(), obj.getY(), obj.getZ());

	switch (key) {
		case ' ':
			isWire = !isWire;
			break;

		//axis movement
		case 'x':
			obj.xInc(OFFSET);
			break;
		case 'X':
			obj.xDec(OFFSET);
			break;
		case 'y':
			obj.yInc(OFFSET);
			break;
		case 'Y':
			obj.yDec(OFFSET);
			break;
		case 'z':
			obj.zInc(OFFSET);
			break;
		case 'Z':
			obj.zDec(OFFSET);
			break;

		//obj roll, pitch, yaw
		case 'w':
			obj.xAngleInc(OFFSET);
			break;
		case 's':
			obj.xAngleDec(OFFSET);
			break;
		case 'a':
			obj.yAngleInc(OFFSET);
			break;
		case 'd':
			obj.yAngleDec(OFFSET);
			break;
		case 'q':
			obj.zAngleInc(OFFSET);
			break;
		case 'e':
			obj.zAngleDec(OFFSET);
			break;

		//camera movement
		case '1':
			posX += CAMVAL;
			break;
		case '2':
			posX -= CAMVAL;
			break;
		case '4':
			posY += CAMVAL;
			break;
		case '5':
			posY -= CAMVAL;
			break;
		case '7':
			posZ += CAMVAL;
			break;
		case '8':
			posZ -= CAMVAL;
			break;

		//reset
		case 'o':
			resetView();
			break;
		//show or hide axis
		case 'p':
			showAxis = !showAxis;
			break;

		case '+':
			break;
		case '-':
			break;

		default:
			break;
	}
}

void specialKeyListener(int key, int x, int y) {
	setTarget(obj.getX(), obj.getY(), obj.getZ());

	switch(key) {
		case GLUT_KEY_DOWN:
			checkFlag(rotY);
			angY -= CAMROT;
			break;
		case GLUT_KEY_UP:
			checkFlag(rotY);
			angY += CAMROT;
			break;

		case GLUT_KEY_RIGHT:
			checkFlag(rotX);
			angX += CAMROT;
			break;
		case GLUT_KEY_LEFT:
			checkFlag(rotX);
			angX -= CAMROT;
			break;

		case GLUT_KEY_PAGE_UP:
			checkFlag(rotZ);
			angZ += CAMROT;
			break;
		case GLUT_KEY_PAGE_DOWN:
			checkFlag(rotZ);
			angZ -= CAMROT;
			break;

		default:
			break;
	}
}

void printInputs() {
	cout << "Object Movements:" << endl;
	cout << "x, X, y, Y, z, Z" << endl << endl;
	cout << "Object Rotations:" << endl;
	cout << "Roll: a, d; Pitch: w, s; Yaw: q, e" << endl << endl;
	cout << "Camera Movements:" << endl;
	cout << "1, 2, 4, 5, 7, 8" << endl << endl;
	cout << "Camera Rotations:" << endl;
	cout << "Roll: up, down arrow; Pitch: left, right arrow; Yaw: page up, down" << endl << endl;
	cout << "Press space to show wires" << endl;
	cout << "Press p to hide axis" << endl;
	cout << "Press o hide to reset" << endl;
}

int main(int argc, char **argv) {
	glutInit(&argc,argv);
	glutInitWindowSize(DISPHEIGHT, DISPWIDTH);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Terrain generation");
	printInputs();
	initiatePoints();

	init(DISPHEIGHT, DISPWIDTH);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutIdleFunc(animate);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyListener);
	glutMainLoop();

	return 0;
}
