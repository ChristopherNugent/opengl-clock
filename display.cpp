#include <GL/glut.h>
#include <unistd.h>
#include "clock.cpp"

/* Set initial display-window size. */
GLsizei winWidth = 600, winHeight = 600;

/* Set range for world coordinates. */
GLfloat xwcMin = 0.0, xwcMax = 600.0;
GLfloat ywcMin = 0.0, ywcMax = 600.0;


void displayFcn(void) {
    // updates per second
    const int FPS = 3;
    // Center clock
    glTranslatef(xwcMax / 2, ywcMax / 2, 0);
    while (true) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawClock();
        usleep(1000000 / FPS);       // 60 fps
        glFlush();
    }
}

void init(void) {
    /* Set color of display window to white. */
    glClearColor(1.0, 1.0, 0.7, 0.0);
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Clock");

    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
}
