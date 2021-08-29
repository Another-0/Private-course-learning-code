/*

#include<stdio.h>
#include<gl/glut.h>
#include<time.h>
#define _USE_MATH_DEFINES
#include<math.h>
#pragma warning(disable : 4996)


GLint Width = 500, Height = 500;
GLfloat h = 0, m = 0, s = 0;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    //绘制底盘
    GLfloat R = 160, r = 150, rt = 100;
    GLfloat n = 0;
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 200; i++) {
        glVertex3f(R * cos(n + i * M_PI / 100), R * sin(n + i * M_PI / 100), -2);
    }
    glEnd();
    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 200; i++) {
        glVertex3f(r * cos(n + i * M_PI / 100), r * sin(n + i * M_PI / 100), -1);
    }
    glEnd();
    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 0, 0);
    glVertex3f(0, 0, -1);
    glColor3f(1, 1, 1);
    for (int i = 0; i <= 20; i++) {
        glVertex3f(rt * cos(n + i * M_PI / 10), rt * sin(n + i * M_PI / 10), -1);
    }
    glEnd();
    glShadeModel(GL_FLAT);

    //绘制数标
    glColor3f(0, 0, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    for (int i = 0; i < 12; i++) {
        glPushMatrix();
        glRotatef(i * 30, 0, 0, 3);
        glTranslatef(r, 0, 0);
        if (i % 3 == 0) {
            glRectf(-12, 10, 0, -10);
        }
        else {
            glRectf(-35, 4, 0, -4);
        }
        glPopMatrix();
    }

//指针
    GLfloat r1 = 70, r2 = 90, r3 = 110;
    GLdouble theta1, theta2, theta3;
    theta1 = h * M_PI / 6 + m / 60 * M_PI / 6;
    theta2 = m * M_PI / 30 + s / 60 * M_PI / 30;
    theta3 = (double)s * 6;
    glLineWidth(2);
    //时针
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_POLYGON);
    glVertex3f(r1 * sin(theta1), r1 * cos(theta1),0);
    glVertex3f(12 * sin(theta1 + M_PI / 2), 12 * cos(theta1 + M_PI / 2),0);
    glVertex3f(18 * sin(theta1 + M_PI), 18 * cos(theta1 + M_PI),0);
    glVertex3f(12 * sin(theta1 - M_PI / 2), 12 * cos(theta1 - M_PI / 2),0);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(r1 * sin(theta1), r1 * cos(theta1), 0);
    glVertex3f(12 * sin(theta1 + M_PI / 2), 12 * cos(theta1 + M_PI / 2), 0);
    glVertex3f(18 * sin(theta1 + M_PI), 18 * cos(theta1 + M_PI), 0);
    glVertex3f(12* sin(theta1 - M_PI / 2), 12 * cos(theta1 - M_PI / 2), 0);
    glEnd();
    //分针
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_POLYGON);
    glVertex3f(r2 * sin(theta2), r2 * cos(theta2), 0);
    glVertex3f(8 * sin(theta2 + M_PI / 2), 8 * cos(theta2 + M_PI / 2), 0);
    glVertex3f(18 * sin(theta2 + M_PI), 18 * cos(theta2 + M_PI), 0);
    glVertex3f(8 * sin(theta2 - M_PI / 2), 8 * cos(theta2 - M_PI / 2), 0);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(r2 * sin(theta2), r2 * cos(theta2), 0);
    glVertex3f(8 * sin(theta2 + M_PI / 2), 8 * cos(theta2 + M_PI / 2), 0);
    glVertex3f(18 * sin(theta2 + M_PI), 18 * cos(theta2 + M_PI), 0);
    glVertex3f(8 * sin(theta2 - M_PI / 2), 8 * cos(theta2 - M_PI / 2), 0);
    glEnd();
    //秒针
    glPushMatrix();
    glRotatef(theta3, 0, 0, -1);
    glColor3f(0.9, 0.9, 0.9);
    glRectf(-2, r3, 2, -15);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-2, r3, 0);
    glVertex3f(2, r3, 0);
    glVertex3f(2, -15, 0);
    glVertex3f(-2, -15, 0);
    glEnd();
    glPopMatrix();

    //指针中心
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 200; i++) {
        glVertex3f(5* cos(n + i * M_PI / 100), 5 * sin(n + i * M_PI / 100), 1);
    }
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 200; i++) {
        glVertex3f(5 * cos(n + i * M_PI / 100), 5 * sin(n + i * M_PI / 100), 1);
    }
    glEnd();
    glFlush();
}

void timerFunc(int value)
{
    s += 1;
    int carry1 = 0;
    if (s >= 60)
    {
        s = 0;
        carry1 = 1;
    }
    m += carry1;
    int carry2 = 0;
    if (m >= 60)
    {
        m = 0;
        carry2 = 1;
    }
    h += carry2;
    if (h >= 24)
        h = 0;
    glutPostRedisplay(); 
    glutTimerFunc(1000, timerFunc, 1); 
}

void SetupRC(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Width / 2, Width / 2, -Height / 2, Height / 2, -5, 5);
    struct tm* localTime;
    time_t curTime;
    time(&curTime);
    localTime = localtime(&curTime);
    h = localTime->tm_hour;
    m = localTime->tm_min;
    s = localTime->tm_sec;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("时钟程序");
    SetupRC();
    glutDisplayFunc(display);
    glutTimerFunc(1000, timerFunc, 1);
    glutMainLoop(); 
    return 0;
}


*/