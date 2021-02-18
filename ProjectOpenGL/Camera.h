/*--------------------------------------------------------------------
Name: Mina Shoaib Rahman Saikat
Roll: 0705096
Sec : B
CSE, BUET
Camera calculation is copyright protected by Mina Shoaib Rahman Saikat
---------------------------------------------------------------------*/
#include <cmath>
#include <GL\glut.h>

enum modes { rotX, rotY, rotZ };

int camFlag = -1;
//just for safety, so that garbage value at camFlag doesn't match with modes at the first place
float upX = 0, upY = 0, upZ = 1;
float tarX = 0, tarY = 0, tarZ = 0;
float posX = 200, posY = 200, posZ = 100;
float angX = 0, angY = 0, angZ = 0;
float radX, radY, radZ;

void setTarget(float x, float y, float z) {
	tarX = x;
	tarY = y;
	tarZ = z;
}

void checkFlag(int flag) {
	if(flag != camFlag) {
		camFlag = flag;
		angX = 0, angY = 0, angZ = 0;
		radX = posX;
		radY = posY;
		radZ = posZ;
	} else {
		switch(flag) {
			case rotX:
				posX = radX * cos(angX);
				posY = radY * sin(angX);
				break;
			case rotY:
				posY = radY * cos(angY);
				posZ = radZ * sin(angY);
				break;
			case rotZ:
				posZ = radZ * cos(angZ);
				posX = radX * sin(angZ);
				break;

			default:
				break;
		}
	}
}

void camReset() {
	upX = upY = 0;
	upZ = 1;
	tarX = tarY = tarZ = 0;
	posX = posY = 200, posZ = 100;
}