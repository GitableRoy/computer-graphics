/**
*
* Leroy Leslie
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <valarray>

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

float pi = 3.141592;

GLfloat colors[3][3] = {{ 0, 0, 0},
                        { 1, 0, 0},
                        { 0, 1, 0},};

class Polygon {
public:
    int vert[100][2],
    numberOfVertices,
    type,
    vertexIndex;
    bool complete;

	Polygon(){
		numberOfVertices = 0;
		type = GL_LINE_STRIP;
		complete = false;
	}

    // public:
    bool intersect(void) {
        return false;
    }

};

bool rubberbanding=false,
antialiasing=false;

Polygon polly;
Polygon anna;

bool inside(int* vertex, Polygon shape) {
    float angle[100], a, b, c, adj_i, hyp_i, adj_j, hyp_j, rot, angleSum = 0;

	/*
    std::cout << "Vertex("<< vertex[0] << "," << vertex[1] << ")"<< std::endl;
    for (int i = 0; i < shape.numberOfVertices - 1; i++){
        std::cout << "Shape("<< shape.vert[i][0] << "," << shape.vert[i][1] << ")"<< std::endl;
    }
	*/

     for (int i = 0; i < shape.numberOfVertices - 1; i++){

         // calculate length of triangle's sides
         a = sqrtf((pow((shape.vert[i][0] - vertex[0]), 2)
                     + pow((shape.vert[i][1] - vertex[1]), 2)));
         // std::cout << "Distance of A: "<< a <<std::endl;


         b = sqrtf((pow((shape.vert[i+1][0] - vertex[0]), 2)
                  +   pow((shape.vert[i+1][1] - vertex[1]), 2)));
         // std::cout << "Distance of B: "<< b <<std::endl;


         c = sqrtf((pow((shape.vert[i][0] - shape.vert[i+1][0]), 2)
                     + pow((shape.vert[i][1] - shape.vert[i+1][1]), 2)));
         // std::cout << "Distance of C: "<< c <<std::endl;


		 // use reference angles to find out whether rotating clockwise or counter
		 adj_i = sqrt(pow(vertex[0], 2) + pow((shape.vert[i][1] - vertex[1]), 2));
		 hyp_i = sqrt(pow(vertex[0], 2) + pow((shape.vert[i][1] - vertex[1]), 2));

		 adj_i = sqrt(pow(vertex[0], 2) + pow((shape.vert[i+1][1] - vertex[1]), 2));
		 hyp_i = sqrt(pow(vertex[0], 2) + pow((shape.vert[i+1][1] - vertex[1]), 2));

		 rot = acos(adj_i/hyp_i) - acos(adj_j/hyp_j);
		 std::cout << ": "<< adj_i<<", "<< hyp_i<<", " <<adj_j<< ", " << hyp_j << "r: " << rot <<std::endl;


		 // use law of cosine to calculate angle
		 if(rot<0)
			angle[i] = -1*(acos((a*a + b*b - c*c)
                        /(2 * a * b))) * 180/pi;

		 else
         angle[i] = (acos((a*a + b*b - c*c)
                        /(2 * a * b))) * 180/pi;
         // std::cout << "Angle of V: " << angle[i] << std::endl;
     }

    std::valarray<float> angles (angle, shape.numberOfVertices);
//    std::cout << angles.sum() << std::endl;

    for (int i = 0; i < 100; i++) angleSum+=angle[i];

    std::cout << "Sum of Angles: " <<angleSum << std::endl;


    return true;
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    if (polly.numberOfVertices==1 && (polly.type==GL_LINE_STRIP || polly.type == GL_LINE_LOOP)) {
        glBegin(GL_POINTS);
        glVertex2iv(polly.vert[0]);
        glEnd();
    }
    glBegin(polly.type);
        glColor3fv(colors[0]);
        for (int i = 0; i < polly.numberOfVertices; i++) glVertex2iv(polly.vert[i]);
    glEnd();

    glBegin(anna.type);
        glColor3fv(colors[1]);
    for (int i = 0; i < anna.numberOfVertices; i++){

        if(inside(anna.vert[i], polly)) glColor3fv(colors[2]);
        else glColor3fv(colors[1]);

        glVertex2iv(anna.vert[i]);
    }
    glEnd();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    if (polly.complete) {
        switch(key) {
            case 'a':antialiasing =! antialiasing;
                if(antialiasing) {
                    glEnable(GL_BLEND);
                    glEnable(GL_LINE_SMOOTH);
                }else{
                    glDisable(GL_BLEND);
                    glDisable(GL_LINE_SMOOTH);
                }
                break;
            case 'r': polly.numberOfVertices = 0;
                polly.type = GL_LINE_STRIP;
                polly.complete = false;
                break;
        }
    }
    else {
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
            case 'r': polly.numberOfVertices = 0;
                polly.type = GL_LINE_STRIP;
                polly.complete = false;
                break;
            case 'c': polly.type = GL_LINE_LOOP;
                polly.complete = true;
                glColor3fv(colors[1]);
                anna.type = GL_POINTS;
                break;
        }
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
    if (polly.complete){
        switch(button) {
            case GLUT_LEFT_BUTTON:
                if(state == GLUT_DOWN) {
                    anna.vertexIndex = anna.numberOfVertices++;
                    anna.vert[anna.vertexIndex][0] = x;
                    anna.vert[anna.vertexIndex][1] = height - 1 - y;
//                    rubberbanding = true;
                    glutPostRedisplay();
                }
                else rubberbanding = false;
                break;
            case GLUT_RIGHT_BUTTON:
                if((state==GLUT_DOWN) && (anna.vertexIndex = findVertex(x, height-1-y)) != -1){
                    if(glutGetModifiers () == GLUT_ACTIVE_CTRL) {
                        for (int i=anna.vertexIndex; i<anna.numberOfVertices-1; i++) {
                            anna.vert[i][0]= anna.vert[i+1][0];
                            anna.vert[i][1]= anna.vert[i+1][1];
                        }
                        anna.numberOfVertices--;
                    } else {
                        anna.vert[anna.vertexIndex][0]=x;
                        anna.vert[anna.vertexIndex][1]=height-1-y;
                        rubberbanding = true;
                    }
                    glutPostRedisplay();
                }
                else rubberbanding = false;
                break;
        }
    }
    else {
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
//            case GLUT_RIGHT_BUTTON:
//                if((state==GLUT_DOWN) && (polly.vertexIndex = findVertex(x, height-1-y)) != -1){
//                    if(glutGetModifiers () == GLUT_ACTIVE_CTRL) {
//                        for (int i=polly.vertexIndex; i<polly.numberOfVertices-1; i++) {
//                            polly.vert[i][0]= polly.vert[i+1][0];
//                            polly.vert[i][1]= polly.vert[i+1][1];
//                        }
//                        polly.numberOfVertices--;
//                    } else {
//                        polly.vert[polly.vertexIndex][0]=x;
//                        polly.vert[polly.vertexIndex][1]=height-1-y;
//                        rubberbanding = true;
//                    }
//                    glutPostRedisplay();
//                }
//                else rubberbanding = false;
//                break;
        }
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
