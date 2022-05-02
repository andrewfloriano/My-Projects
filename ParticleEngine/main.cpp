#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include "FireEngine.h"

QdFireEngine pe(1.0f, 0.2f, 0.0f, 1.0f);

void display(void)
{
	glPushMatrix();
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	pe.draw();
	glutSwapBuffers();
    glutPostRedisplay();
    glPopMatrix();
}


void init(void) 
{
	pe.setLimit(-2, 2, -1, 3);
	pe.init(1000);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);				
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);					
	glLoadIdentity();								
	glMatrixMode(GL_MODELVIEW);	
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);					
	glEnable(GL_BLEND);									
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);	
}

//Function is called when the dimensions of the client area change
void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}


//Function that is run first
void main(void)
{
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Quagmire Particle Engine Environment");
   init();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutMainLoop();
}