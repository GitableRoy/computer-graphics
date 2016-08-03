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

int width = 400,
height = 600,
vert[100][2],
n = 0,
type = GL_LINE_STRIP,
v;

bool rubberbanding=false,
antialiasing=false;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    if (n==1 && (type==GL_LINE_STRIP || type == GL_LINE_LOOP)) {
        glBegin(GL_POINTS);
        glVertex2iv(vert[0]);
        glEnd();
    }
    glBegin(type);
    for (int i = 0; i < n; i++) glVertex2iv(vert[i]);
    glEnd();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key){
        case 'a':antialiasing =! antialiasing;
            if(antialiasing) {
                glEnable(GL_BLEND);
                glEnable(GL_LINE_SMOOTH);
            }else{
                glDisable(GL_BLEND);
                glDisable(GL_LINE_SMOOTH);
            }
            break;
        case 'r': n = 0; break;
//        case 'l': type = GL_LINE_STRIP; break;
        case 'c': type = GL_LINE_LOOP; break;
        case 'v': type = GL_POINTS; break;
//        case 'e': std::cout<< "Enter button working" << std::endl;
    }
    glutPostRedisplay();
}

int findVertex(int x, int y) {
    int dx, dy;
    for(int i = 0; i < n; i++) {
        dx = vert[i][0] - x;
        dy = vert[i][1] - y;
        if(dx*dx + dy*dy < 16) return i;
    }
    return -1;
}

void mouse (int button, int state, int x, int y) {
    switch(button) {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN) {
                v = n++;
                vert[v][0] = x;
                vert[v][1] = height - 1 - y;
                rubberbanding = true;
                glutPostRedisplay();
            }
            else rubberbanding = false;
            break;
        case GLUT_RIGHT_BUTTON:
            if((state==GLUT_DOWN) && (v = findVertex(x, height-1-y)) != -1){
                if(glutGetModifiers () == GLUT_ACTIVE_CTRL) {
                    for (int i=v; i<n-1; i++) {
                        vert[i][0]= vert[i+1][0];
                        vert[i][1]= vert[i+1][1];
                    }
                    n--;
                } else {
                    vert[v][0]=x;
                    vert[v][1]=height-1-y;
                    rubberbanding = true;
                }
                glutPostRedisplay();
            }
            else rubberbanding = false;
            break;
    }
}

void motion(int x, int y) {
    if(rubberbanding) {
        vert[v][0] = x;
        vert[v][1] = height -1 -y;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    /* Initialize GLUT */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(50, 100);
    glutCreateWindow("Project 3");
    
    
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0,0,0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    glutMainLoop();
    return 0;
}
