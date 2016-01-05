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
GLuint _small_gate;
GLuint _picture1;
GLuint _window1;
GLuint _floor1;
static double angle=0;

static int begin;
static int spin = 90;

#define langkah 1.0
#define navigasi 10.0
#define spot 5.0

int depth;
int posisi = 0;
float camera_x = 7.5;
float camera_y = 3.7;
float camera_z = -30.0;
float camera_angle = 0.0;
float camera_rotate = 7.5;
float flashlight = 7.5;

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
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
	//glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

    //dinding
    Image* image1 = loadBMP("wood_texture_2.bmp");
    _wall = loadTexture(image1);
    delete image1;
    //roof
    Image* image2 = loadBMP("roof_texture_1.bmp");
    _roof = loadTexture(image2);
    delete image2;
    //pintu
    Image* image3 = loadBMP("door_texture_1.bmp");
    _door = loadTexture(image3);
    delete image3;
    //pagar kecil
    Image* image4 = loadBMP("wood_texture_3.bmp");
    _small_gate = loadTexture(image4);
    delete image4;
    //lukisan
    Image* image5 = loadBMP("picture_texture_1.bmp");
    _picture1 = loadTexture(image5);
    delete image5;
    //cendela
    Image* image6 = loadBMP("window_texture_1.bmp");
    _window1 = loadTexture(image6);
    delete image6;
    //lantai
    Image* image7 = loadBMP("wood_texture_1.bmp");
    _floor1 = loadTexture(image7);
    delete image7;
}

void
movelight(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    begin = x;
  }
}

void
motion(int x, int y)
{
  spin = (spin - (x - begin)) % 360;
  begin = x;
  glutPostRedisplay();
}

void myinit(void){

    glViewport(0,0,640,480);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
    depth = 1;
    //atur cahaya
    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat lightPos[] = {-2 * 10, 10, 4 * 10, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void display(void){
      GLfloat position[] =
      //{7.5, 0.0, -50.5, 1.0};
      //{flashlight, 0.0, -100.5, 0.0};
      {flashlight, 0.0, -100.5, 0.0};
    if (depth)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	else
		glClear(GL_COLOR_BUFFER_BIT);

      glPushMatrix();
      glRotated((GLdouble) spin, 0.0, 1.0, 0.0);
      glRotated(0.0, 1.0, 0.0, 0.0);
      glLightfv(GL_LIGHT0, GL_POSITION, position);

      glTranslated(0.0, -0.25, 1.5);
      glDisable(GL_LIGHTING);
      glDisable(GL_TEXTURE_2D);
      glColor3f(0.0, 1.0, 1.0);
      glutWireCube(0.07);
      glEnable(GL_LIGHTING);
      glEnable(GL_TEXTURE_2D);
      glColor3f(1.0, 1.0, 1.0);
      glPopMatrix();

    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glPushMatrix();
    //if (posisi == 0)
        gluLookAt(camera_x, camera_y, camera_z, camera_rotate, camera_angle, 100.0, 0.0, 1.0, 0.0);
        glTranslatef(7.5,0.0,0.0);
    //if (posisi == 1)
    //    gluLookAt(camera_x+(-1*langkah), camera_y, camera_z, 7.5, 0.0, 1000.0, 0.0, 1.0, 0.0);
        //glTranslatef(x+(-1*langkah), y, z);
    //if (posisi == 2)
        //camera_z = camera_z + langkah;
    //    gluLookAt(camera_x, camera_y, camera_z+langkah, 7.5, 0.0, 1000.0, 0.0, 1.0, 0.0);
        //glTranslatef(x, y, z+(-1*langkah));
    //if (posisi == 3)
    //    gluLookAt(camera_x+langkah, camera_y, camera_z, 7.5, 0.0, 1000.0, 0.0, 1.0, 0.0);
        //glTranslatef(x+langkah, y, z);
    //if (posisi == 4)
    //    gluLookAt(camera_x, camera_y, camera_z+(-1*langkah), 7.5, 0.0, 1000.0, 0.0, 1.0, 0.0);
        //glTranslatef(x, y, z+langkah);
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

	//pagar kecil bagian batangan
    glBindTexture(GL_TEXTURE_2D, _small_gate);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    double simpan = -7.0;
    for(int a=0;a<15;a++)
    {
        if(a%2==0)
        {
        glTexCoord2f(0.0, 1.0); glVertex3f(simpan-0.2, 0.0f, -5.0f);
        glTexCoord2f(0.0, 0.0); glVertex3f(simpan, 0.0f, -5.0f);
        glTexCoord2f(1.0, 0.0); glVertex3f(simpan, 2.0f, -5.0f);
        glTexCoord2f(1.0, 1.0); glVertex3f(simpan-0.2, 2.0f, -5.0f);
        }
        simpan += 0.5;
    }
    simpan = -7.0;
    for(int a=0;a<15;a++)
    {
        if(a%2==0)
        {
        glTexCoord2f(0.0, 1.0); glVertex3f(simpan-0.2, 0.0f, -4.7f);
        glTexCoord2f(0.0, 0.0); glVertex3f(simpan, 0.0f, -4.7f);
        glTexCoord2f(1.0, 0.0); glVertex3f(simpan, 2.0f, -4.7f);
        glTexCoord2f(1.0, 1.0); glVertex3f(simpan-0.2, 2.0f, -4.7f);
        }
        simpan += 0.5;
    }
    simpan = -7.0;
    for(int a=0;a<15;a++)
    {
        if(a%2==0)
        {
        glTexCoord2f(0.0, 1.0); glVertex3f(simpan, 0.0f, -5.0f);
        glTexCoord2f(0.0, 0.0); glVertex3f(simpan, 0.0f, -4.7f);
        glTexCoord2f(1.0, 0.0); glVertex3f(simpan, 2.0f, -4.7f);
        glTexCoord2f(1.0, 1.0); glVertex3f(simpan, 2.0f, -5.0f);
        }
        simpan += 0.5;
    }
    simpan = -7.0;
    for(int a=0;a<15;a++)
    {
        if(a%2==0)
        {
        glTexCoord2f(0.0, 1.0); glVertex3f(simpan-0.2, 0.0f, -5.0f);
        glTexCoord2f(0.0, 0.0); glVertex3f(simpan-0.2, 0.0f, -4.7f);
        glTexCoord2f(1.0, 0.0); glVertex3f(simpan-0.2, 2.0f, -4.7f);
        glTexCoord2f(1.0, 1.0); glVertex3f(simpan-0.2, 2.0f, -5.0f);
        }
        simpan += 0.5;
    }
	glEnd();
	//pagar kecil bagian batangan
    glBegin(GL_QUADS);
    //atas
    glTexCoord2f(0.0, 1.0); glVertex3f(-7.3, 2.2f, -5.0f);
    glTexCoord2f(0.0, 0.0); glVertex3f(simpan-0.5, 2.2f, -5.0f);
    glTexCoord2f(1.0, 0.0); glVertex3f(simpan-0.5, 2.2f, -4.7f);
    glTexCoord2f(1.0, 1.0); glVertex3f(-7.3, 2.2f, -4.7f);
    //bawah
    glTexCoord2f(0.0, 1.0); glVertex3f(-7.3, 2.0f, -5.0f);
    glTexCoord2f(0.0, 0.0); glVertex3f(simpan-0.5, 2.0f, -5.0f);
    glTexCoord2f(1.0, 0.0); glVertex3f(simpan-0.5, 2.0f, -4.7f);
    glTexCoord2f(1.0, 1.0); glVertex3f(-7.3, 2.0f, -4.7f);
    //depan
    glTexCoord2f(0.0, 1.0); glVertex3f(-7.3, 2.0f, -5.0f);
    glTexCoord2f(0.0, 0.0); glVertex3f(simpan-0.5, 2.0f, -5.0f);
    glTexCoord2f(1.0, 0.0); glVertex3f(simpan-0.5, 2.2f, -5.0f);
    glTexCoord2f(1.0, 1.0); glVertex3f(-7.3, 2.2f, -5.0f);
	//belakang
    glTexCoord2f(0.0, 1.0); glVertex3f(-7.3, 2.0f, -4.7f);
    glTexCoord2f(0.0, 0.0); glVertex3f(simpan-0.5, 2.0f, -4.7f);
    glTexCoord2f(1.0, 0.0); glVertex3f(simpan-0.5, 2.2f, -4.7f);
    glTexCoord2f(1.0, 1.0); glVertex3f(-7.3, 2.2f, -4.7f);
	glEnd();

    //lukisan
    glBindTexture(GL_TEXTURE_2D, _picture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex3f(-7.2f, 3.0f, -4.5f);
	glTexCoord2f(1.0, 0.0); glVertex3f(-7.2f, 5.0f, -4.5f);
	glTexCoord2f(1.0, 1.0); glVertex3f(-7.2f, 5.0f, -3.0f);
	glTexCoord2f(0.0, 0.0); glVertex3f(-7.2f, 3.0f, -3.0f);
	glEnd();
	//cendela menjorok
    glBindTexture(GL_TEXTURE_2D, _window1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0); glVertex3f(-6.5f, 2.0f, -2.1f);
	glTexCoord2f(0.0, 1.0); glVertex3f(-2.5f, 2.0f, -2.1f);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2.5f, 5.0f, -2.1f);
	glTexCoord2f(1.0, 0.0); glVertex3f( -6.5f, 5.0f, -2.1f);
	glEnd();

    glBindTexture(GL_TEXTURE_2D, _wall);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //kanan
    glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0); glVertex3f(7.5f, 0.0f, -5.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(7.5f, 7.0f, -5.0f);
	glTexCoord2f(0.0, 0.0); glVertex3f(7.5f, 7.0f, 5.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(7.5f, 0.0f, 5.0f);
	glEnd();
	//kiri
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-7.3f, 0.0f, -5.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(-7.3f, 7.0f, -5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(-7.3f, 7.0f, 5.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(-7.3f, 0.0f, 5.0f);
	glEnd();

    glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-7.5f, 0.0f, -5.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(-7.5f, 7.0f, -5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(-7.5f, 7.0f, 5.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(-7.5f, 0.0f, 5.0f);
	glEnd();

    glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex3f(-7.5f, 0.0f, -5.0f);
	glTexCoord2f(0.0, 0.0); glVertex3f(-7.3f, 0.0f, -5.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(-7.3f, 7.0f, -5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f( -7.5f, 7.0f, -5.0f);
	glEnd();

	//belakang
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex3f(-7.5f, 0.0f, 5.0f);
	glTexCoord2f(0.0, 0.0); glVertex3f(7.5f, 0.0f, 5.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(7.5f, 7.0f, 5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f( -7.5f, 7.0f, 5.0f);
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
    glBindTexture(GL_TEXTURE_2D, _floor1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //bawah
    glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-7.5f, 0.0f, -5.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(7.5f, 0.0f, -5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(7.5f, 0.0f, 5.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(-7.5f, 0.0f, 5.0f);
	glEnd();
    //sebagai pondasi
    glBindTexture(GL_TEXTURE_2D, _wall);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//kiri pondasi
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-7.5f, -0.5f, -5.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(-7.5f, 0.0f, -5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(-7.5f, 0.0f, 5.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(-7.5f, -0.5f, 5.0f);
	glEnd();
    //kanan pondasi
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(7.5f, 0.0f, 5.0f);
    glTexCoord2f(1.0, 0.0); glVertex3f(7.5f, -0.5f, 5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(7.5f, -0.5f, -5.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(7.5f, 0.0f, -5.0f);
	glEnd();
	//depan pondasi
    //glColor3d(1,0,0);
    glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex3f(-7.5f, 0.0f, -5.0f);
	glTexCoord2f(0.0, 0.0); glVertex3f(7.5f, 0.0f, -5.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(7.5f, -0.5f, -5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(-7.5f, -0.5f, -5.0f);
	glEnd();
	//belakang pondasi
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex3f(-7.5f, -0.5f, 5.0f);
	glTexCoord2f(0.0, 0.0); glVertex3f(7.5f, -0.5f, 5.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(7.5f, 0.0f, 5.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(-7.5f, 0.0f, 5.0f);
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
		//glTranslatef(langkah, 0.0, 0.0);
		camera_x = camera_x + langkah;
		//posisi = 1;
		break;
	case 'd':
	case 'D':
		//glTranslatef((-1*langkah), 0.0, 0.0);
		camera_x =  camera_x - langkah;
		//posisi = 3;
		break;
	case 'w':
	case 'W':
		//glTranslatef(0.0, 0.0, langkah);
		camera_z = camera_z + langkah;
		//posisi = 2;
		break;
	case 's':
	case 'S':
		//glTranslatef(0.0, 0.0, (-1*langkah));
		camera_z =  camera_z - langkah;
		//posisi = 4;
		break;
	case 'i':
	case 'I':
		//glTranslatef(0.0, 0.0, (-1*langkah));
		camera_angle =  camera_angle + navigasi;
		//posisi = 4;
		break;
	case 'k':
	case 'K':
		//glTranslatef(0.0, 0.0, (-1*langkah));
		camera_angle =  camera_angle - navigasi;
		//posisi = 4;
		break;
	case 'j':
	case 'J':
        //glRotatef(-1.0, 0.0f, 1.0f, 0.0f);
        camera_rotate = camera_rotate + navigasi;
        flashlight = flashlight + spot;
		break;
	case 'l':
	case 'L':
        //glRotatef(1.0, 0.0f, 1.0f, 0.0f);
        camera_rotate = camera_rotate - navigasi;
        flashlight = flashlight - spot;
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
	myinit();
    glutMouseFunc(movelight);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    initRendering();
    glutReshapeFunc(handleResize);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
 }
