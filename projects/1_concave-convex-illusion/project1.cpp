//
//  Project1.cpp
//
//
//  Created by Leroy Leslie on 7/18/16.
//
//

#include <stdio.h>

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

GLfloat r(double angle) {
    return sin(angle);
}

void createOval(void) {
    glBegin(GL_LINES);

    double t, p = 3.141593 / 180;
    for(int i = 0; i < 360; i = i + 1) {
        t = i * p;
        glVertex2f(r(t) * cos(t), r(t) * sin(t));
    }

    glEnd();
}

void drawCircle (void) {
    /**
        Does stuff
     */

    GLfloat x_center = 0;
    GLfloat y_center = 0;
    GLfloat y_position;
    GLfloat x_position;

    float gradient_color = 0;


    std::cout << "Drawing Circle" << std::endl;

    glBegin(GL_LINES);

    for ( y_position = RADIUS; y_position >= (-1 * RADIUS); y_position -= 0.05 ) {

        // Find X
        if (( (RADIUS * RADIUS) - ( y_position * y_position ) ) < 0) continue;
        else x_position = sqrt( (RADIUS * RADIUS) - (( y_position * y_position ) + (y_center * y_center)) );

//        if (( ((y_position - y_center) * (y_position - y_center)) - (RADIUS * RADIUS)) < 0) continue;
//        else x_position = sqrt( pow((y_position - y_center), 2) - pow(RADIUS, 2) ) + x_center;

        // Change Color
        gradient_color = fabs((y_position + RADIUS )/ (2 * RADIUS));
        glColor3f( gradient_color, gradient_color, gradient_color);
        std::cout << "Gradient Color is: " << gradient_color << std::endl;

        // Draw Line
        glVertex2f( (-1 * x_position), y_position );
        glVertex2f(x_position, y_position);
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

        std::cout << "Color is: " << color << std::endl;

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

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
//    createCircle(400, 300, RADIUS);
//    createCircle(300, 200, RADIUS);
//    createCircle(400, 300, RADIUS);
//    createCircle(600, 500, RADIUS);
//    createOval();

    drawCircle();

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
    gluOrtho2D(-200.0, 200.0, -150.0, 150.0);
    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
