
#include<stdio.h>
#include<gl/glut.h>
#define _USE_MATH_DEFINES
#include<math.h>

GLfloat Width = 500, Height = 500;
GLfloat r = 50, theta = M_PI / 2, fai;
GLfloat upx = 0, upy = 1, upz = 0;
GLfloat cx, cy, cz;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    cx = r * sin(theta) * sin(fai);
    cy = r * cos(theta);
    cz = r * sin(theta) * cos(fai);
    gluLookAt(cx, cy ,cz, 0, 0, 0, upx, upy, upz);
    glColor3f(1, 0, 0);
    glutWireCube(10);
    glPushMatrix();
    glTranslatef(12, 12, 12);
    glColor3f(0, 1, 0);
    glutSolidCube(8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-12, -12, -12);
    glColor3f(0, 0, 1);
    glutSolidCube(5);
    glPopMatrix();
	glFlush();
}

void mykey(int key, int x, int y) {
    GLfloat delta = M_PI / 12;
    GLint t = 0;
    switch (key)
    {
    case GLUT_KEY_UP:
        if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
            r += 3;
        }
        else {
            theta -= delta;
            t--;
            if(t<-12){
                t = 0;
                upy = -upy;
            }
        }
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
            r -= 3;
        }
        else {
            theta += delta;
            t++;
            if (t > 12) {
                t = 0;
                upy = -upy;
            }
        }
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        fai -= delta;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        fai += delta;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();   
    gluPerspective(90, 1, 10, 100);
    //glOrtho(-40, 40, -40, 40, 10, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(Width, Height);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("ÉãÏñ»úÒÆ¶¯");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(mykey);
    glutMainLoop();
    return 0;
}
