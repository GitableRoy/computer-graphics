/**
 *
 * @author Leroy Leslie
 * created: 8/7/16
 *
 **/

#include <stdio.h>
#include <stdlib.h>
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
#include <glut.h>
#endif

GLfloat pos[] = {-2, 4, 5, 1},                          // Light position
amb[] = {0.3, 0.3, 0.3, 1.0};                   // Ambient intensity

GLfloat front_amb_diff[] = {0.7, 0.5, 0.1, 1.0};        // Front side property
GLfloat back_amb_diff[] = {0.4, 0.7, 0.1, 1.0};         // Back side property

GLfloat spe[] = {0.25, 0.25, 0.25, 1.0};                // Property for front & back_amb_diff
GLfloat theta = 0,
dt = 0.5,
axes[3][3] = {{1, 0, 0},
              {0, 1, 0},
              {0, 0, 1}},
diag[3][3] = {{1, 0, 0},
              {0, 1, 1},
              {0, 0, 1}};

int axis = 4;                                           // 0:x, 1:y, 2:z: light around z
bool idleOn = true;

GLfloat xTranslate, yTranslate, slope;


GLfloat ring(double angle) {
    return cos(angle);
}


void createWatchFace() {
    glPushMatrix();
        GLUquadricObj* quadObj = gluNewQuadric();
        gluQuadricDrawStyle(quadObj, GLU_OUTLINE_POLYGON);
        gluCylinder(quadObj, 1.5, 1.5, 0.5, 50, 4);
        glRotated(180,0,0,0);
        gluDisk(quadObj, 0, 1.5, 50, 1);
        glRotated(180,0,0,0);
        glTranslated(0, 0, 0.5);
        gluDisk(quadObj, 0, 1.5, 50, 1);
    glPopMatrix();
}

void createWristband() {
    glPushMatrix();
        glScalef(10, 4, 1);
        glRotatef(90, 0, 1, 0);

        double t, p = 3.141593 / 180;
        for(int i = 0; i < 360; i = i + 20) {
            t = i * p;
            xTranslate = ring(t) * cos(t);
            yTranslate = ring(t) * sin(t);
            slope = xTranslate/yTranslate;
//            std::cout << slope << std::endl;

            glPushMatrix();
                glTranslatef(xTranslate, yTranslate, 0);
//                glRotatef(-1/slope, 1, 0, 0);
                glutSolidCube(0.2);
            glPopMatrix();
        }
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);

        if(axis < 3) {
            glRotated(theta, axes[axis][0], axes[axis][1], axes[axis][2]);
        }
        else if (axis > 3) {
            glRotated(theta, diag[axis%3][0], diag[axis%3][1], diag[axis%3][2]);
        }
        else{
            glPushMatrix();                                     // Preserve CTM for object
            glRotated(theta, 0, 0, 1);                        // Rotate light around z
            glLightfv(GL_LIGHT0, GL_POSITION, pos);
            glPopMatrix();                                      // Restore CTM for object
        }
        // glutSolidTorus(0.4, 1.0, 48, 96);                     // Draw object
        //glutSolidOctahedron();

    createWatchFace();
    createWristband();


    glPopMatrix();
    glutSwapBuffers();
};

void idle(void) {
//    if(theta >= 360) axis = (axis + 1)%4;                // Cycle through the 4 stages
    if(idleOn) theta = (theta < 360)? theta + dt:dt;                // Increment rotation angle
    glutPostRedisplay();
};

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case '0':
            std::cout << "0 pressed" << std::endl;
            if(idleOn) idleOn = false;
            else idleOn = true;
            break;

        case '1':
            std::cout << "1 pressed" << std::endl;
            idleOn = true;
            axis = 0;
            break;

        case '2':
            std::cout << "2 pressed" << std::endl;
            idleOn = true;
            axis = 1;
            break;

        case '3':
            std::cout << "3 pressed" << std::endl;
            idleOn = true;
            axis = 2;
            break;

        case '4':
            std::cout << "6 pressed" << std::endl;
            axis = 4;
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("GLUT Objects");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.0, 2, 8);                        // Or use glOrtho(-2, 2 ,-2, 2, 2, 8);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_amb_diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);      // For solid once

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0, 0, -5);                               // Translate object and light to put object in view volume
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    std::cout << "Started" << std::endl;

    glutMainLoop();
};
