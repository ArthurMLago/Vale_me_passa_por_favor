/*
 * solarsystem.c
 *
 *  Created on: 16/05/2013
 *      Author: valle
 */

#if __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <iostream>
#include <vector>

#include "output.txt"

static int year = 0, day = 0, moon1 = 0, moon2 = 0, camera = 0;


void init(void)
{
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth (30.0f);

	// glShadeModel ( GL_SMOOTH);

// 	glEnable (GL_LIGHTING);
// 	glEnable (GL_LIGHT0);
// 	glEnable (GL_DEPTH_TEST);
} 

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Sets up the camera
	glLoadIdentity();
	gluLookAt (0.0f, -20.0f, 4.4f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f);
	glRotatef ((GLfloat) camera, moon1, moon2, 0.0f);

	// Positions the lighting (fixed i.r.t. the world)
	// glLightfv(GL_LIGHT0, GL_POSITION, (GLfloat[4]){5.0f, 10.0f, 5.0f, 1.0f});
	// glLightfv(GL_LIGHT0, GL_DIFFUSE,  (GLfloat[4]){1.0f, 1.0f, 1.0f, 1.0f});
	// glLightfv(GL_LIGHT0, GL_SPECULAR, (GLfloat[4]){1.0f, 1.0f, 1.0f, 1.0f});

	// glLightModelfv(GL_LIGHT_MODEL_AMBIENT, (GLfloat[4]){0.1f, 0.1f, 0.1f, 1.0f});



	// draws planet
	glTranslatef(0,0,-4.0);
	glRotatef ((GLfloat) day, 0.0f, 1.0f, 0.0f);
	// glColor3f (0.0f, 1.0f, 1.0f);


		for (int i = 0; i < 38; i++){
			glBegin(GL_LINES);

			for (int j = 0; j < sizes[i + 2] - 1; j++){

				glVertex3fv(vec[i][j]);    // v0-v1-v2
				glVertex3fv(vec[i][j + 1]);

			}
			glVertex3fv(vec[i][ sizes[i+2] - 1 ]);    // v0-v1-v2
			glVertex3fv(vec[i][0]);

		    glEnd();


		}



	// glFlush();
	glutSwapBuffers();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	gluPerspective(60.0f, (GLfloat) w/(GLfloat) h, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);

}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 'c':
			camera = (camera + 10) % 360;
			glutPostRedisplay();
			break;
		case 'C':
			camera = (camera - 10) % 360;
			glutPostRedisplay();
			break;
		case 'd':
			day = (day + 10) % 360;
			glutPostRedisplay();
			break;
		case 'D':
			day = (day - 10) % 360;
			glutPostRedisplay();
			break;
		case 'm':
			moon1 = (moon1 + 10) % 360;
			glutPostRedisplay();
			break;
		case 'M':
			moon1 = (moon1 - 10) % 360;
			glutPostRedisplay();
			break;
		case 'n':
			moon2 = (moon2 + 10) % 360;
			glutPostRedisplay();
			break;
		case 'N':
			moon2 = (moon2 - 10) % 360;
			glutPostRedisplay();
			break;
		case 'y':
			year = (year + 5) % 360;
			glutPostRedisplay();
			break;
		case 'Y':
			year = (year - 5) % 360;
			glutPostRedisplay();
			break;
		default:
			break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
