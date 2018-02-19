#include <GL/glut.h>
#include <ctime>
using namespace std;


// /* Set initial display-window size. */
// GLsizei winWidth = 600, winHeight = 600;

//  Set range for world coordinates.
// GLfloat xwcMin = 0.0, xwcMax = 600.0;
// GLfloat ywcMin = 0.0, ywcMax = 600.0;

void drawClockFace();
void drawHourHand(int, int);
void drawMinuteHand(int, int);
void drawSecondHand(int);

void drawClock() {
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    int hour = now->tm_hour;
    int min = now->tm_min;
    int sec = now->tm_sec;


    drawHourHand(hour, min);
    drawMinuteHand(min, sec);
    drawSecondHand(sec);
    drawClockFace();
}

class wcPt2D {
public:
    GLfloat x, y;
};

void square(wcPt2D ctr, int size) {
    GLint k;
    glBegin(GL_QUADS);
    glVertex2f(ctr.x + size, ctr.y + size);
    glVertex2f(ctr.x + size, ctr.y - size);
    glVertex2f(ctr.x - size, ctr.y - size);
    glVertex2f(ctr.x - size, ctr.y + size);
    glEnd();
}


void drawClockFace() {
    glColor3f(0, 0, 0);
    wcPt2D ctr = {0, 0};
    glPushMatrix();


    int markSize = 7, markDistance = 150;
    for (int i = 0; i < 60; i++) {
        glRotatef(1 * (360 / 60), 0, 0, 1);
        glTranslatef(markDistance, 0, 0);
        glRotatef((i + 1) * (360 / 60), 0, 0, -1);
        square(ctr, 2);
        glRotatef((i + 1) * (360 / 60), 0, 0, 1);

        glTranslatef(-markDistance, 0, 0);
    }
    for (int i = 0; i < 12; i++) {
        glRotatef(1 * (360 / 12), 0, 0, 1);
        glTranslatef(markDistance, 0, 0);
        glRotatef((i + 1) * (360 / 12), 0, 0, -1);
        square(ctr, markSize);
        glRotatef((i + 1) * (360 / 12), 0, 0, 1);
        glTranslatef(-markDistance, 0, 0);
    }
    glPopMatrix();
}

void drawHourHand(int hour, int min) {
    glColor3f(0.0, 0.0, 0);
    wcPt2D ctr = {0, 0};
    double theta = (hour / 12.0) * 360;
    theta += (min / 60.0 / 12.0) * 360;
    glPushMatrix();
    int width = 3, length = 150;
    glRotatef(theta, 0, 0, -1);

    glBegin(GL_QUADS);
    glVertex2f(ctr.x + width, ctr.y + length);
    glVertex2f(ctr.x + width, ctr.y);
    glVertex2f(ctr.x - width, ctr.y);
    glVertex2f(ctr.x - width, ctr.y + length);
    glEnd();

    glPopMatrix();
}

void drawMinuteHand(int min, int sec) {
    glColor3f(0.0, 0.0, 1);
    wcPt2D ctr = {0, 0};
    double theta = min * 6;
    theta += (sec / 60.0) * 6;
    // theta *= 6;
    glPushMatrix();
    int width = 1, length = 150;
    glRotatef(theta, 0, 0, -1);
    glBegin(GL_QUADS);
    glVertex2f(ctr.x + width, ctr.y + length);
    glVertex2f(ctr.x + width, ctr.y);
    glVertex2f(ctr.x - width, ctr.y);
    glVertex2f(ctr.x - width, ctr.y + length);
    glEnd();

    glPopMatrix();
}

void drawSecondHand(int sec) {
    glColor3f(1, 0.0, 0);
    wcPt2D ctr = {0, 0};
    double theta = 6 * sec;
    glPushMatrix();
    int width = 1, length = 150;
    glRotatef(theta, 0, 0, -1);
    glBegin(GL_QUADS);
    glVertex2f(ctr.x + width, ctr.y + length);
    glVertex2f(ctr.x + width, ctr.y);
    glVertex2f(ctr.x - width, ctr.y);
    glVertex2f(ctr.x - width, ctr.y + length);
    glEnd();

    glPopMatrix();
}

