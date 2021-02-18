/*--------------------------------------------------------------------
Name: Mina Shoaib Rahman Saikat
Roll: 0705096
Sec : B
CSE, BUET
Graphics Engine is copyright protected by Mina Shoaib Rahman Saikat
---------------------------------------------------------------------*/
#include <cmath>
#include "Vector.h"
#include <GL\glut.h>
#include<windows.h>

#define PI	3.14159265

/*--------------------------------------------------------------------
Sets eight cameras with white color
--------------------------------------------------------------------*/
void setLight0(float x, float y, float z, float d, float r, float g, float b) {
	GLfloat light_position[] = { x, y, z, d };
	GLfloat light_color[] = { r, g, b, 1 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
}

void setLight1(float x, float y, float z, float d, float r, float g, float b) {
	GLfloat light_position[] = { x, y, z, d };
	GLfloat light_color[] = { r, g, b, 1 };

	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_color);
}

void setLight2(float x, float y, float z, float d, float r, float g, float b) {
	GLfloat light_position[] = { x, y, z, d };
	GLfloat light_color[] = { r, g, b, 1 };

	glLightfv(GL_LIGHT2, GL_POSITION, light_position);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_color);
}

void setLight3(float x, float y, float z, float d, float r, float g, float b) {
	GLfloat light_position[] = { x, y, z, d };
	GLfloat light_color[] = { r, g, b, 1 };

	glLightfv(GL_LIGHT3, GL_POSITION, light_position);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_color);
}

void setLight4(float x, float y, float z, float d, float r, float g, float b) {
	GLfloat light_position[] = { x, y, z, d };
	GLfloat light_color[] = { r, g, b, 1 };

	glLightfv(GL_LIGHT4, GL_POSITION, light_position);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT4, GL_SPECULAR, light_color);
}

void setLight5(float x, float y, float z, float d, float r, float g, float b) {
	GLfloat light_position[] = { x, y, z, d };
	GLfloat light_color[] = { r, g, b, 1 };

	glLightfv(GL_LIGHT5, GL_POSITION, light_position);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT5, GL_SPECULAR, light_color);
}

void setLight6(float x, float y, float z, float d, float r, float g, float b) {
	GLfloat light_position[] = { x, y, z, d };
	GLfloat light_color[] = { r, g, b, 1 };

	glLightfv(GL_LIGHT6, GL_POSITION, light_position);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT6, GL_SPECULAR, light_color);
}

void setLight7(float x, float y, float z, float d, float r, float g, float b) {
	GLfloat light_position[] = { x, y, z, d };
	GLfloat light_color[] = { r, g, b, 1 };

	glLightfv(GL_LIGHT7, GL_POSITION, light_position);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT7, GL_SPECULAR, light_color);
}

/*--------------------------------------------------------------------
Draws the x, y and z axis
--------------------------------------------------------------------*/
void drawAxis() {
	glBegin(GL_LINES);
			glColor3f(0, 1, 0);
		//Y axis
		glVertex3f(0, -1000, 0);
		glVertex3f(0,  1000, 0);

		//X axis
			glColor3f(0, 0, 1);
		glVertex3f(-1000, 0, 0);
		glVertex3f( 1000, 0, 0);
		
		//Z axis
			glColor3f(1, 0, 0);
		glVertex3f( 0, 0, -1000);
		glVertex3f( 0, 0, 1000);
	glEnd();
}


int num_texture = 0;
GLuint grass, mountain;

int myLoadBitmap(char *filename)
{
    int i, j=0;
	FILE *l_file;
	unsigned char *l_texture;
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;
	num_texture++;
	if( (l_file = fopen(filename, "rb"))==NULL) return (-1);
	fread(&fileheader, sizeof(fileheader), 1, l_file);
	fseek(l_file, sizeof(fileheader), SEEK_SET);
	fread(&infoheader, sizeof(infoheader), 1, l_file);
	l_texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
	for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
	{
		fread(&rgb, sizeof(rgb), 1, l_file);
		l_texture[j+0] = rgb.rgbtRed;
		l_texture[j+1] = rgb.rgbtGreen;
		l_texture[j+2] = rgb.rgbtBlue;
		l_texture[j+3] = 255;
		j += 4;
	}
	fclose(l_file);
	glBindTexture(GL_TEXTURE_2D, num_texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
	l_texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA,
	GL_UNSIGNED_BYTE, l_texture);
	free(l_texture);
	return (num_texture);
}

void loadImages()
{
	grass = myLoadBitmap("grass.bmp");
	mountain = myLoadBitmap("mountain.bmp");
}