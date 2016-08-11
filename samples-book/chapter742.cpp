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
                      {0, 0, 1}};

int axis = 0;                                           // 0:x, 1:y, 2:z: light around z

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT |
          GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  if(axis < 3) {
  glRotated(theta, axes[axis][0], axes[axis][1], axes[axis][2]);
  }
  else {
    glPushMatrix();                                     // Preserve CTM for object
      glRotated(theta, 0, 0, 1);                        // Rotate light around z
      glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glPopMatrix();                                      // Restore CTM for object
  }
  glutSolidTorus(0.4, 1.0, 48, 96);                     // Draw object
  glPopMatrix();
  glutSwapBuffers();
};

void idle(void) {
  if(theta >= 360) axis = (axis + 1)%4;                // Cycle through the 4 stages
  theta = (theta < 360)? theta + dt:dt;                // Increment rotation angle
  glutPostRedisplay();
};

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
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 75);

  glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);      // For solid once

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslated(0, 0, -5);                               // Translate object and light to put object in view volume
  glLightfv(GL_LIGHT0, GL_POSITION, pos);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutMainLoop();
};
