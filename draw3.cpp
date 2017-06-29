/*
 * minimal.c
 *
 *  Created on: 01/05/2013
 *      Author: valle
 */

#if __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif

#include <iostream>
#include <vector>

#include "output.txt"

static int camera1 = 0, camera2 = 0, camera3 = 0;
static double xax = 0, yax = 0, zax = 0;


void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}


void display(void) {

    glLoadIdentity();
    gluLookAt (0.0f, -20.0f, 4.4f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f, 2.0f);
    
    /* Red Wire Sphere created at origin */
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glRotatef((GLfloat) camera1, 1.0, 0.0, 0.0);
    glRotatef((GLfloat) camera2, 0.0, 1.0, 0.0);
    glRotatef((GLfloat) camera3, 0.0, 0.0, 1.0);

    glTranslated(xax, yax, zax);
    glColor3f(1.0f,0.0f,0.0f);     

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

    glPopMatrix();

    glutSwapBuffers();
}


void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,(GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'c':
        camera1 = (camera1 + 10) % 360;
        break;
    case 'C':
        camera1 = (camera1 - 10) % 360;
        break;
    case 'v':
        camera2 = (camera2 + 10) % 360;
        break;
    case 'V':
        camera2 = (camera2 - 10) % 360;
        break;
    case 'b':
        camera3 = (camera3 + 10) % 360;
        break;
    case 'B':
        camera3 = (camera3 - 10) % 360;
        break;

    // Translada posição no eixo X em 0.2
    case 'w':
        xax = xax + 0.2;
        break;
    // Translada posição no eixo X em -0.2
    case 'W':
        xax = xax - 0.2;
        break;
    // Translada posição no eixo Y em 0.2
    case 'q':
        yax = yax + 0.2;
        break;
    // Translada posição no eixo Y em -0.2
    case 'Q':
        yax = yax - 0.2;
        break;
    // Translada posição no eixo Z em 0.2
    case 'e':
        zax = zax + 0.2;
        break;
    // Translada posição no eixo Z em -0.2
    case 'E':
        zax = zax - 0.2;
        break;
    case 'r':
        xax = yax = zax = 0;
        camera1 = camera2 = camera3 = 0;
        break;
    default:
        return;
    }
   glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}

