//
//  Project_2.cpp
//
//
//  Created by Leroy Leslie on 7/13/16.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifdef __WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif

#define WIDTH  1000
#define HEIGHT 600

GLfloat blue[4][3] =   {{ 6,  0, 0},
                        { 6, 25, 0},
                        {-6, 25, 0},
                        {-6,  0, 0}};

GLfloat black[4][3] =  {{10, -5, 0},
                        {10, 30, 0},
                        { 0, 30, 0},
                        { 0, -5, 0}};

GLfloat white[4][3] =  {{-10, -5, 0},
                        {-10, 30, 0},
                        { 0,  30, 0},
                        { 0,  -5, 0}};

GLfloat colors[3][3] = {{ 0, 0, 0},
                        { 1, 1, 1},
                        { 0, 0, 1},};

void draw_blue(void) {
    glBegin(GL_POLYGON);
    for(int i = 0; i < 4; i++) glVertex3fv(blue[i]);
    glEnd();
}

void draw_bw(int color, int control) {
    glBegin(GL_POLYGON);
    if((color + control)%2 == 0) {
        for(int i = 0; i < 4; i++) glVertex3fv(black[i]);
    }
    else {
        for(int i = 0; i < 4; i++) glVertex3fv(white[i]);
    }
    glEnd();
}

void draw_rect(int color, int control) {
    for(int rot = 0; rot < 360; rot += 45) {
        glPushMatrix ();
        glRotated (rot, 0, 0, 1);
        glTranslated (0, 50, 0);
        if (color == 2) draw_blue();
        else draw_bw(color, control);
        glPopMatrix();
    }
}

void draw_ring(int control) {
    for (int i = 0; i < 3; i++) {
        glColor3fv(colors[i]);
        glPushMatrix();
        glTranslated( i, i, -i);
        glScaled(1, 1, 1);
        draw_rect(i, control);
        glPopMatrix();
    }
}



void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTranslated(-375, 150, 0);
    for(int i = 0; i < 4; i++) {
        draw_ring(i%2);
        glTranslated(0, -300, 0);
        draw_ring((i+1)%2);    // (i+1)%2
        glTranslated(250, 300, 0);
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
