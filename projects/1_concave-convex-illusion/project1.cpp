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
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#define WIDTH  800
#define HEIGHT 600

#define RADIUS 200

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

    for (float angle = 90; angle <= 270; angle += 0.1) {

        std::cout << angle << std::endl;

        // color is equal to percentage of angle completion
        color = (angle - 90) / 180;
        glColor3f( color, color, color);

        std::cout << "Color is: " << color << std::endl;

        // start of line at x,y points based on angle
        x_line_start = radius * cos(angle) + x_center;
        y_line_start = radius * sin(angle) + y_center;

        // end of line at x´, y´ points based on angle
        x_line_end = radius * cos(135 - angle) + x_center;
        y_line_end = radius * sin(135 - angle) + y_center;

        // start line, end line
        glVertex2f( x_line_start, y_line_start);
        glVertex2f( x_line_end, y_line_start);  // y_line_end not neccesary because the circle is horizontal

    }

    glEnd();

    std::cout << "Circle Created" << std::endl;
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    createCircle(400, 300, RADIUS);
//    createCircle(300, 200, RADIUS);
//    createCircle(400, 300, RADIUS);
//    createCircle(600, 500, RADIUS);

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

    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
//    gluOrtho2D(-2.0, 2.0, -1.5, 1.5);
    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
