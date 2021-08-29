/*

#include<stdio.h>
#include<gl/glut.h>
#include<math.h>

GLdouble t = 0, a = 4, b = 6, c = 12, pi = 3.14;
GLdouble r = 3.14/3;
GLfloat size = 9;//点大小
GLfloat width = 1;//线宽

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(size);
	glLineWidth(width);
	glBegin(GL_LINES);
	GLdouble x, y, z, dx, dy, dz;
	for (int i = 0; i < 2000; i++) {
		x = (a * sin(c * t) + b) * cos(t);
		y = (a * sin(c * t) + b) * sin(t);
		z = a * cos(c * t);
		dx = y / 10;
		dy = (z * cos(r) + x * sin(r)) / 10 ;
		dz = (z * sin(r) - x * cos(r)) / 10;
		glVertex3d(dx, dy, dz);
		t += pi / 1000;
		x = (a * sin(c * t) + b) * cos(t);
		y = (a * sin(c * t) + b) * sin(t);
		z = a * cos(c * t);
		dx = y / 10;
		dy = (z * cos(r) + x * sin(r)) / 10 ;
		dz = (z * sin(r) - x * cos(r)) / 10;
		glVertex3d(dx, dy, dz);
	}
	glEnd();
	glFlush();
}

	int main(int argc, char** argv) {
		glutInit(&argc, argv);
		glutInitWindowSize(720, 720);
		glutCreateWindow("环形螺旋曲线");
		glutDisplayFunc(display);
		glutMainLoop();
	}

	*/