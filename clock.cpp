#include <GL/glut.h>
#include <ctime>
#include <cmath>
using namespace std;

class wcPt2D {
public:
    GLfloat x, y;
};

// /* Set initial display-window size. */
// GLsizei winWidth = 600, winHeight = 600;

//  Set range for world coordinates.
// GLfloat xwcMin = 0.0, xwcMax = 600.0;
// GLfloat ywcMin = 0.0, ywcMax = 600.0;

void drawClockFace();
void drawHourHand(int hour, int min);
void drawMinuteHand(int min, int sec);
void drawSecondHand(int sec);
void drawHand(int length, int width);
void circle(wcPt2D ctr, int radius, int detail);
void square(wcPt2D ctr, int size);

void drawClock() {
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    int hour = now->tm_hour;
    int min = now->tm_min;
    int sec = now->tm_sec;


    drawClockFace();
    drawHourHand(hour, min);
    drawMinuteHand(min, sec);
    drawSecondHand(sec);
}

void drawHand(int length, int width) {
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(0, 0);
    glVertex2f(width, length / 2);
    glVertex2f(0 - width, length / 2);
    glVertex2f(0, length);
    glEnd();
}

void drawClockFace() {
    wcPt2D ctr = {0, 0};
    int markSize = 7, faceRadius = 150, caseRadius = 5;



    glColor3f(0,0,0);
    circle(ctr, faceRadius * 1.1 + caseRadius, 100);
    glColor3f(1, 1, 1);
    circle(ctr, faceRadius * 1.1, 100);

    glColor3f(0, 0, 0);
    // Ticks for minutes
    glPushMatrix();
    for (int i = 0; i < 60; i++) {
        glRotatef(1 * (360 / 60), 0, 0, 1);
        glTranslatef(faceRadius, 0, 0);
        glRotatef((i + 1) * (360 / 60), 0, 0, -1);
        square(ctr, 2);
        // circle(ctr, 2, 5);
        glRotatef((i + 1) * (360 / 60), 0, 0, 1);

        glTranslatef(-faceRadius, 0, 0);
    }
    glPopMatrix();

    // Ticks for hours
    glPushMatrix();
    for (int i = 0; i < 12; i++) {
        glRotatef(1 * (360 / 12), 0, 0, 1);
        glTranslatef(faceRadius, 0, 0);
        glRotatef((i + 1) * (360 / 12), 0, 0, -1);
        // square(ctr, markSize);
        circle(ctr, markSize, 10);
        glRotatef((i + 1) * (360 / 12), 0, 0, 1);
        glTranslatef(-faceRadius, 0, 0);
    }
    glPopMatrix();

    // Stem
    circle(ctr, 5, 50);
}

void drawHourHand(int hour, int min) {
    glColor3f(0.0, 0.0, 0);
    wcPt2D ctr = {0, 0};
    double theta = (hour / 12.0) * 360;
    theta += (min / 60.0 / 12.0) * 360;
    glPushMatrix();
    int width = 10, length = 100;
    glRotatef(theta, 0, 0, -1);

    // glBegin(GL_QUADS);
    // glVertex2f(ctr.x + width, ctr.y + length);
    // glVertex2f(ctr.x + width, ctr.y);
    // glVertex2f(ctr.x - width, ctr.y);
    // glVertex2f(ctr.x - width, ctr.y + length);
    // glEnd();
    drawHand(length, width);

    glPopMatrix();
}

void drawMinuteHand(int min, int sec) {
    glColor3f(0.0, 0.0, 1);
    wcPt2D ctr = {0, 0};
    double theta = min * 6;
    theta += (sec / 60.0) * 6;
    // theta *= 6;
    glPushMatrix();
    int width = 5, length = 150;
    glRotatef(theta, 0, 0, -1);
    drawHand(length, width);
    // glBegin(GL_QUADS);
    // glVertex2f(ctr.x + width, ctr.y + length);
    // glVertex2f(ctr.x + width, ctr.y);
    // glVertex2f(ctr.x - width, ctr.y);
    // glVertex2f(ctr.x - width, ctr.y + length);
    // glEnd();

    glPopMatrix();
}

void drawSecondHand(int sec) {
    glColor3f(1, 0.0, 0);
    wcPt2D ctr = {0, 0};
    double theta = 6 * sec;
    glPushMatrix();
    int width = 5, length = 150;
    glRotatef(theta, 0, 0, -1);
    // glBegin(GL_QUADS);
    // glVertex2f(ctr.x + width, ctr.y + length);
    // glVertex2f(ctr.x + width, ctr.y);
    // glVertex2f(ctr.x - width, ctr.y);
    // glVertex2f(ctr.x - width, ctr.y + length);
    // glEnd();
    drawHand(length, width);
    glPopMatrix();
}

void square(wcPt2D ctr, int size) {
    glBegin(GL_QUADS);
    glVertex2f(ctr.x + size, ctr.y + size);
    glVertex2f(ctr.x + size, ctr.y - size);
    glVertex2f(ctr.x - size, ctr.y - size);
    glVertex2f(ctr.x - size, ctr.y + size);
    glEnd();
}

void circle(wcPt2D ctr, int radius, int detail) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(ctr.x, ctr.y);
    for(int i = 0; i < detail; i++) {
        glVertex2f(ctr.x + radius * cos(2 * i * M_PI / detail), 
                   ctr.y + radius * sin(2 * i * M_PI / detail));
    }
    glVertex2f(ctr.x + radius, ctr.y);
    glEnd();
}