//
//  Project1.cpp
//
//
//  Created by Leroy Leslie on 7/18/16.
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

#define WIDTH  800
#define HEIGHT 600

#define RADIUS 100
#define PADDING 10


void drawCircle (GLfloat x_center, GLfloat y_center, bool concave) {
    /**
        Does stuff
     */

    GLfloat y_position;
    GLfloat x_position;

    float gradient_color = 0;


//    std::cout << "Drawing Circle" << std::endl;

    glBegin(GL_LINES);

    for ( y_position = RADIUS; y_position >= (-1 * RADIUS); y_position-- ) {

        // Find X
        if (( (RADIUS * RADIUS) - ( y_position * y_position ) ) < 0) continue;
        else x_position = sqrt( (RADIUS * RADIUS) - (( y_position * y_position )) );

        // Change Color
        if (concave) gradient_color = fabs((y_position + RADIUS )/ (2 * RADIUS));
        else gradient_color = fabs((y_position - RADIUS )/ (2 * RADIUS)); //else convex

        glColor3f( gradient_color, gradient_color, gradient_color);
//        std::cout << "Gradient Color is: " << gradient_color << std::endl;

        // Draw Line
        glVertex2f( (-1 * x_position) + x_center, y_position +y_center );
        glVertex2f(x_position + x_center, y_position + y_center);
//        std::cout << "X: "<< x_position << ", Y: " << y_position << std::endl;
    }

    glEnd();

//    std::cout << "Circle Drawn" << std::endl;
}

bool concave (int draws) {
    return draws % 2 == 0;
}

void generateCircles(int amount) {
    GLfloat prev_x_center[amount];// = {};
    GLfloat prev_y_center[amount];// = {};
    GLfloat curr_x_center;
    GLfloat curr_y_center;
    int successful_draws = 0;


    // set first circle
    curr_x_center = rand() % ((WIDTH * 3/2) - (RADIUS *2));
    curr_y_center = rand() % ((HEIGHT * 3/2) - (RADIUS *2));
    curr_x_center -= WIDTH;
    curr_y_center -= HEIGHT;
    drawCircle(curr_x_center, curr_y_center, true);
    prev_x_center[0] = curr_x_center;
    prev_y_center[0] = curr_y_center;
    successful_draws++;
    amount--;


    // draw the rest of circles
    while (amount > 0) {

        // Select random place on map for center
        curr_x_center = rand() % (WIDTH * 3/2);
        curr_y_center = rand() % (HEIGHT * 3/2);
        curr_x_center -= WIDTH;
        curr_y_center -= HEIGHT;

//        std::cout <<"("<<curr_x_center<<", "<<curr_y_center<<")"<<std::endl;

        int i = 0;
        bool placeable = true;
        while( prev_x_center[i] != 0) {
            if (( fabs(curr_x_center - prev_x_center[i]) <= (RADIUS * 2) )  ||
                ( fabs(prev_y_center[i] + curr_y_center) <= (RADIUS * 2) )) {
                placeable = false;
            }
            i++;
        }

        if (placeable) {
            drawCircle(curr_x_center, curr_y_center, concave(successful_draws));
            std::cout <<"("<<curr_x_center<<", "<<curr_y_center<<")"<<std::endl;
            prev_x_center[i+1] = curr_x_center;
            prev_y_center[i+1] = curr_y_center;
            successful_draws++;
            amount--;
        }
    }


}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

//    drawCircle(600, 90, true);
//    drawCircle(200, 127, false);
//    drawCircle(-160, 210, true);
//    drawCircle(-500, -70, false);
//    drawCircle(-150, -100, true);
//    drawCircle(70, -400, false);

    generateCircles(6);

    glFlush();
}

int main(int argc, char** argv) {
    /* Initialize GLUT */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Project 1");


    glClearColor(0.5, 0.5, 0.5, 0.0);

    gluOrtho2D(-WIDTH, WIDTH, -HEIGHT, HEIGHT);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
