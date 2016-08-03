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
height = 600;

class Polygon {
public:
    int vert[100][2],
    numberOfVertices = 0,
    type = GL_LINE_STRIP,
    vertexIndex;

    // public:
    bool intersect(void) {
        return false;
    }

};

class Vertex {
private:
    int color[1][3],
    xyLocation[1][2];

public:
    Vertex(int x, int y){
        xyLocation[0][0] = x;
        xyLocation[0][1] = y;
    }

    int getXYLocation() {
        return 0;
    }

    void setColor() {}
};


bool rubberbanding=false,
antialiasing=false;

Polygon polly;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    if (polly.numberOfVertices==1 && (polly.type==GL_LINE_STRIP || polly.type == GL_LINE_LOOP)) {
        glBegin(GL_POINTS);
        glVertex2iv(polly.vert[0]);
        glEnd();
    }
    glBegin(polly.type);
    for (int i = 0; i < polly.numberOfVertices; i++) glVertex2iv(polly.vert[i]);
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
        case 'r': polly.numberOfVertices = 0; break;
            //        case 'l': polly.type = GL_LINE_STRIP; break;
        case 'c': polly.type = GL_LINE_LOOP;
            if (polly.vertexIndex < 5) std::cout<< "4 vetices button working" << std::endl;
            break;
        case 'v': polly.type = GL_POINTS; break;
            //        case 'e': std::cout<< "Enter button working" << std::endl;
    }
    glutPostRedisplay();
}

int findVertex(int x, int y) {
    int dx, dy;
    for(int i = 0; i < polly.numberOfVertices; i++) {
        dx = polly.vert[i][0] - x;
        dy = polly.vert[i][1] - y;
        if(dx*dx + dy*dy < 16) return i;
    }
    return -1;
}

void mouse (int button, int state, int x, int y) {
    switch(button) {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN) {
                polly.vertexIndex = polly.numberOfVertices++;
                polly.vert[polly.vertexIndex][0] = x;
                polly.vert[polly.vertexIndex][1] = height - 1 - y;
                rubberbanding = true;
                glutPostRedisplay();
            }
            else rubberbanding = false;
            break;
        case GLUT_RIGHT_BUTTON:
            if((state==GLUT_DOWN) && (polly.vertexIndex = findVertex(x, height-1-y)) != -1){
                if(glutGetModifiers () == GLUT_ACTIVE_CTRL) {
                    for (int i=polly.vertexIndex; i<polly.numberOfVertices-1; i++) {
                        polly.vert[i][0]= polly.vert[i+1][0];
                        polly.vert[i][1]= polly.vert[i+1][1];
                    }
                    polly.numberOfVertices--;
                } else {
                    polly.vert[polly.vertexIndex][0]=x;
                    polly.vert[polly.vertexIndex][1]=height-1-y;
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
        polly.vert[polly.vertexIndex][0] = x;
        polly.vert[polly.vertexIndex][1] = height -1 -y;
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
