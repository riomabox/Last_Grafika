#include <windows.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glut.h>
#include <iostream>
#include "imageloader.h"
using namespace std;
GLuint _wall;
GLuint _roof;
GLuint _door;
static double angle=0;

int depth;
int posisi = 0;
float langkah = 1.0;
float x = 7.5;
float y = 0.0;
float z = 0.0;

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

//cara load texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId;
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

    //dinding
    Image* image1 = loadBMP("wood_texture_2.bmp");
    _wall = loadTexture(image1);
    delete image1;

    Image* image2 = loadBMP("roof_texture_1.bmp");
    _roof = loadTexture(image2);
    delete image2;

    Image* image3 = loadBMP("door_texture_1.bmp");
    _door = loadTexture(image3);
    delete image3;
}

void myinit(void){
    glClearColor(0,0,0,0);
    glViewport(0,0,640,480);
    depth = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
   // gluPerspective(50.0,640.0/480.0,1.0,30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //atur cahaya
    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat lightPos[] = {-2 * 10, 10, 4 * 10, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void display(void){
    if (depth)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	else
		glClear(GL_COLOR_BUFFER_BIT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glPushMatrix();
    gluLookAt(7.5, 3.0, -30.0, 7.5, 0.0, 1000.0, 0.0, 1.0, 0.0);
    //if (posisi == 0)
        glTranslatef(x,y,z);
    /*if (posisi == 1)
        glTranslatef(x+langkah, y, z);
    if (posisi == 2)
        glTranslatef(x, y, z+langkah);
    if (posisi == 3)
        glTranslatef(x+(-1*langkah), y, z);
    if (posisi == 4)
        glTranslatef(x, y, z+(-1*langkah));*/
    //glRotatef(angle, 0.0f, 1.0f, 0.0f);
    //angle+=0.05;
    //set gambar
    glBindTexture(GL_TEXTURE_2D, _wall);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //depan banget
    glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex3f(2.5f, 0.0f, -5.0f);
	glTexCoord2f(0.0, 0.0); glVertex3f(7.5f, 0.0f, -5.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(7.5f, 7.0f, -5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(2.5f, 7.0f, -5.0f);
	glEnd();

    //set gambar
    glBindTexture(GL_TEXTURE_2D, _door);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//pintu
    glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.0f, 0.2f, -2.1f);
	glTexCoord2f(0.0, 0.0); glVertex3f(2.0f, 0.2f, -2.1f);
	glTexCoord2f(1.0, 0.0); glVertex3f(2.0f, 6.0f, -2.1f);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0f, 6.0f, -2.1f);
	glEnd();

	//depan menjorok
    glBindTexture(GL_TEXTURE_2D, _wall);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex3f(-7.5f, 0.0f, -2.0f);
	glTexCoord2f(0.0, 0.0); glVertex3f(2.5f, 0.0f, -2.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(2.5f, 7.0f, -2.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f( -7.5f, 7.0f, -2.0f);
	glEnd();

	//penyambung depan banget dan menjorok
    glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex3f(2.5f, 0.0f, -5.0f);
	glTexCoord2f(0.0, 0.0); glVertex3f(2.5f, 0.0f, -2.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(2.5f, 7.0f, -2.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(2.5f, 7.0f, -5.0f);
	glEnd();

	//belakang
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex3f(-7.5f, 0.0f, 5.0f);
	glTexCoord2f(0.0, 0.0); glVertex3f(7.5f, 0.0f, 5.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(7.5f, 7.0f, 5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f( -7.5f, 7.0f, 5.0f);
	glEnd();
    //kanan
    glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0); glVertex3f(7.5f, 0.0f, -5.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(7.5f, 7.0f, -5.0f);
	glTexCoord2f(0.0, 0.0); glVertex3f(7.5f, 7.0f, 5.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(7.5f, 0.0f, 5.0f);
	glEnd();
	//kiri
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-7.5f, 0.0f, -5.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(-7.5f, 7.0f, -5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(-7.5f, 7.0f, 5.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(-7.5f, 0.0f, 5.0f);
	glEnd();
	//bawah
    glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-7.5f, 0.0f, -5.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(7.5f, 0.0f, -5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(7.5f, 0.0f, 5.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(-7.5f, 0.0f, 5.0f);
	glEnd();

    glBindTexture(GL_TEXTURE_2D, _roof);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//atas depan
    glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0); glVertex3f(-7.5f, 7.0f, -5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0f, 10.0f, 0.0f);
	glTexCoord2f(2.0, 0.0); glVertex3f(7.5f, 7.0f, -5.0f);
	glEnd();
	//atas belakang
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0); glVertex3f(-7.5f, 7.0f, 5.0f);
	glTexCoord2f(2.0, 0.0); glVertex3f(7.5f, 7.0f, 5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();
	//atas kiri
    glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0); glVertex3f(-7.5f, 7.0f, -5.0f);
	glTexCoord2f(2.0, 0.0); glVertex3f(-7.5f, 7.0f, 5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();
	//atas kanan
    glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0); glVertex3f(7.5f, 7.0f, -5.0f);
	glTexCoord2f(2.0, 0.0); glVertex3f(7.5f, 7.0f, 5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();
	glFlush();
	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	/* Petunjuk navigasi cursor:

	  "a": Bergerak ke kiri
	  "d": Bergerak ke kanan
	  "w": Bergerak maju
	  "s": Bergerak mundur
	  "t": Mengatur keberadaan kedalaman

	*/
	switch (key)
	{
	case 'a':
	case 'A':
		glTranslatef(langkah, 0.0, 0.0);
		posisi = 1;
		break;
	case 'd':
	case 'D':
		glTranslatef((-1*langkah), 0.0, 0.0);
		posisi = 3;
		break;
	case 'w':
	case 'W':
		glTranslatef(0.0, 0.0, langkah);
		posisi = 2;
		break;
	case 's':
	case 'S':
		glTranslatef(0.0, 0.0, (-1*langkah));
		posisi = 4;
		break;
	case 'j':
	case 'J':
        glRotatef(-1.0, 0.0f, 1.0f, 0.0f);
		break;
	case 'l':
	case 'L':
        glRotatef(1.0, 0.0f, 1.0f, 0.0f);
		break;
	case 't':
	case 'T':
		if (depth)
		{
			depth = 0;
			glDisable(GL_DEPTH_TEST);
		}
		else
		{
			depth = 1;
			glEnable(GL_DEPTH_TEST);
		}
	}
	display();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("FP_Grafkom");
	initRendering();
	myinit();
	glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
	glutReshapeFunc(handleResize);
	glutMainLoop();

	return 0;
 }
