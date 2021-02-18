/*--------------------------------------------------------------------
Name: Mina Shoaib Rahman Saikat
Roll: 0705096
Sec : B
CSE, BUET
Position calculation is copyright protected by Mina Shoaib Rahman Saikat
---------------------------------------------------------------------*/
#include <cmath>
#include <GL\glut.h>

class Position {
	float objectX, objectY, objectZ;
	float angleX, angleY, angleZ;

public:
	Position() { objectX = objectY = objectZ = angleX = angleY = angleZ = 0; }

	Position(float x, float y, float z, float xAng, float yAng, float zAng) {
		objectX = x;
		objectY = y;
		objectZ = z;
		angleX = xAng;
		angleY = yAng;
		angleZ = zAng;
	}

	/*----------------------------------------------------------------*/
	void reset() { objectX = objectY = objectZ = angleX = angleY = angleZ = 0; }

	/*----------------------------------------------------------------*/
	void xInc(float val) { objectX += val; }
	void xDec(float val) { objectX -= val; }

	void yInc(float val) { objectY += val; }
	void yDec(float val) { objectY -= val; }

	void zInc(float val) { objectZ += val; }
	void zDec(float val) { objectZ -= val; }

	/*----------------------------------------------------------------*/
	void translateObject() { glTranslatef(objectX, objectY, objectZ); }

	/*----------------------------------------------------------------*/
	void xAngleInc(float val) { angleX += val; }
	void xAngleDec(float val) { angleX -= val; }

	void yAngleInc(float val) { angleY += val; }
	void yAngleDec(float val) { angleY -= val; }

	void zAngleInc(float val) { angleZ += val; }
	void zAngleDec(float val) { angleZ -= val; }

	/*----------------------------------------------------------------*/
	void rollObject()	{ glRotatef(angleX, 1, 0, 0); }
	void pitchObject()	{ glRotatef(angleY, 0, 1, 0); }
	void yawObject()	{ glRotatef(angleZ, 0, 0, 1); }

	/*----------------------------------------------------------------*/
	float getX() { return objectX; }
	float getY() { return objectY; }
	float getZ() { return objectZ; }

	float getAngleX() { return angleX; }
	float getAngleY() { return angleY; }
	float getAngleZ() { return angleZ; }
};
