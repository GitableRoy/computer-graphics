#ifdef __WIN32
  #include <windows.h>  // For MS Windows
#endif

#ifdef __APPLE__
  #include <OpenGL/gl.h>
#else
  #include <GL/gl.h>
#endif

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POINTS);
    glVertex2i(0, 0);
    glVertex2i(0, 299);
    glVertex2i(399, 0);
    glVertex2i(399, 299);
  glEnd();
  glFlush();
}

int main(int argc, char** argv) {
  /* code */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(400, 300);
  glutInitWindowPosition(200, 100);
  glutCreateWindow("sample");
  glClearColor(0.0, 0.0, 0.0);
  gluOrtho2D(0.0, 400.0, 0.0, 300.0);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
