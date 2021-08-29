/*

#include<stdio.h>
#include<gl/glut.h>
#include<math.h>

GLdouble t = 0, a = 3, b = 8, c = 8, pi = 3.14;
GLdouble r = -3.14 / 10;
GLfloat size = 1;//点大小
GLfloat width = 5;//线宽

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(size);
	glLineWidth(width);
	glBegin(GL_LINES);
	GLdouble x, y, z, dx, dy, dz;
	for (int i = 0; i < 1000; i++) {
		x = a * t * cos(c * t) + b;
		y = a * t * sin(c * t) + b;
		z = c * t;
		dx = y / 100;
		dy = (z * cos(r) + x * sin(r)) / 100-0.4;
		dz = (z * sin(r) - x * cos(r)) / 100;
		glVertex3d(dx, dy, dz);
		t += pi / 100;
		x = a * t * cos(c * t) + b;
		y = a * t * sin(c * t) + b;
		z = c * t;
		dx = y / 100;
		dy = (z * cos(r) + x * sin(r)) / 100-0.4;
		dz = (z * sin(r) - x * cos(r)) / 100;
		glVertex3d(dx, dy, dz);
	}
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(720, 720);
	glutCreateWindow("锥形螺旋曲线");
	glutDisplayFunc(display);
	glutMainLoop();
}


*/