//
//  Project_2.cpp
//
//
//  Created by Leroy Leslie on 7/13/16.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>

#ifdef __WIN32
#include <windows.h>  // For MS Windows
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#endif

#define WIDTH  1000
#define HEIGHT 600

GLfloat shield[4][3] = {{ 5,  0, 0},
                        { 8, 20, 0},
                        {-8, 20, 0},
                        {-5,  0, 0}};

GLfloat colors[3][3] = {{ 0, 0, 0},
                        { 1, 1, 1},
                        { 0, 0, 1},};

void draw_shield(void) {
    glBegin(GL_POLYGON);
    for(int i = 0; i < 5; i++) glVertex3fv(shield[i] + HEIGHT/2);
    glEnd();
}

void draw_rect(void) {
    for(int rot = 0; rot < 360; rot += 30) {
        glPushMatrix ();
        glRotated (rot, 0, 0, 1);
        glTranslated (10, 50, 0);
        draw_shield();
        glPopMatrix();
    }
}

void draw_ring(int width_div, int height_div) {
    for (int i = 0; i < 3; i++) {
        glColor3fv(colors[i]);
        glPushMatrix();
        glTranslated( i, i, -i*5);
        //glTranslated( (i-3)*50 , (i-3)*50, -i*5 );
        glScaled(i+1, i+1, i+1);
        draw_rect();
        glPopMatrix();
    }
}



void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(int x_position = 2; x_position <= 4; x_position += 2){
        for(int y_position = 2; y_position <= 4; y_position += 2){
            draw_ring(x_position, y_position);
        }
    }
    glFlush();
}

int main(int argc, char** argv) {
    /* Initialize GLUT */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Project 2");


    glClearColor(1.0, 1.0, 0.0, 0.0);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, 0, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
