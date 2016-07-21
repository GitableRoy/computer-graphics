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


    std::cout << "Drawing Circle" << std::endl;

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

    std::cout << "Circle Drawn" << std::endl;
}

void createCircle(int x_center, int y_center, int radius) {
    /**
     Starts at top of circle
        Finds the x, y   location of the circle's circumference
        Finds the x´, y´ location of the circle's circumference (horizonatally opposite of it)
     Draws horizontal line from x,y to x´,y´ 
     Repeats this by moving counterclockwise from 90˚ to 270˚

     */

    GLfloat x_line_start;
    GLfloat y_line_start;
    GLfloat x_line_end;
    GLfloat y_line_end;
    float color = 0;

    std::cout << "Creating Circle" << std::endl;

    glBegin(GL_LINES);

    for (float angle = 90; angle <= 270; angle += 0.05	) {

        std::cout << angle << std::endl;

        /* color is equal to percentage of angle completion */
        color = (angle - 90) / 180;
        glColor3f( color, color, color);

//        std::cout << "Color is: " << color << std::endl;

        /* start of line at x,y points based on angle */
        x_line_start = radius * cos(angle) + x_center;
        y_line_start = radius * sin(angle) + y_center;

        /* end of line at x´, y´ points based on angle  */
        x_line_end = radius * cos(180 - angle) + x_center;
        y_line_end = radius * sin(180 - angle) + y_center;  // unneccesary, the line is horizonal

        /* start line, end line */
        glVertex2f( x_line_start, y_line_start);
        glVertex2f( x_line_end, y_line_start);              // using line

    }

    glEnd();

    std::cout << "Circle Created" << std::endl;
}

//bool isOverlapping (Circle) {
//
//}

void callCircle(int amount) {
    GLfloat prev_x_center[amount];// = {};
    GLfloat prev_y_center[amount];// = {};
    GLfloat curr_x_center;
    GLfloat curr_y_center;


    while (amount > 0) {
        // Select random place on map for center
        curr_x_center = rand() % (WIDTH - RADIUS - PADDING) + (-(WIDTH - RADIUS));
        curr_y_center = rand() % (HEIGHT - RADIUS - PADDING) + (-(HEIGHT - RADIUS));
        bool concave = rand() % 2;
        int successful_draws = 0;

        for( int i = 0; i < amount; i++) {

            if (( fabs(curr_x_center - prev_x_center[i]) <= (RADIUS/2) )  ||
                ( fabs(prev_y_center[i] + curr_y_center) <= (RADIUS/2) )) {
                std::cout << "unsuccessful" << std::endl;
                break;
            }
            if ((( fabs(curr_x_center - prev_x_center[i]) <= (RADIUS/2) )  ||
                 ( fabs(prev_y_center[i] + curr_y_center) <= (RADIUS/2) )) &&
                 (i == successful_draws) ) {
                std::cout << "unsuccessful" << std::endl;
                continue;
            }
            else {
                std::cout << "successful! distance between center x and last center x is: " << fabs(prev_x_center[i] + curr_x_center) << std::endl;

                std::cout << "successful! distance between center y and last center y is: " << fabs(prev_y_center[i] + curr_y_center) << std::endl;

                drawCircle(curr_x_center, curr_y_center, concave);
                prev_x_center[i+1] = curr_x_center;
                prev_y_center[i+1] = curr_y_center;
                amount--;
            }
        }
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    drawCircle(600, 90, true);
    drawCircle(200, 127, false);
    drawCircle(-100, 210, true);
    drawCircle(-500, -70, false);
    drawCircle(-150, -100, true);
    drawCircle(70, -50, false);

//    callCircle(8);

    glFlush();
}

void reshape (GLsizei width, GLsizei height) {
    float w_aspect = WIDTH / HEIGHT, aspect=((float)width) / height;
    if (aspect <= w_aspect) {
        glViewport( 0, (height - width / w_aspect)/2, width, width/w_aspect);
    }
    else {
        glViewport(( width - height * w_aspect ) / 2, 0, height * w_aspect, height );
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
}

int main(int argc, char** argv) {
    /* Initialize GLUT */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Project 1");


    glClearColor(0.5, 0.5, 0.5, 0.0);

//    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
    gluOrtho2D(-WIDTH, WIDTH, -HEIGHT, HEIGHT);
    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
