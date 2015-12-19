#include <windows.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glut.h>
#include <iostream>

using namespace std;

static double angle=0;

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void myinit(void){
    glClearColor(0,0,0,0);
    glViewport(0,0,640,480);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glPushMatrix();
    gluLookAt(7.5, 10.0, -30.0, 7.5, 0.0, 10.0, 0.0, 1.0, 0.0);
    glTranslatef(7.5,0.0,0.0);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    angle+=0.05;

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
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("FP_Grafkom");
	myinit();
	glutDisplayFunc(display);
	glutReshapeFunc(handleResize);
	glutMainLoop();

	return 0;
 }