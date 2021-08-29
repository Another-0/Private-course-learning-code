/*

#include<stdio.h>
#include<stdlib.h>
#include<gl/glut.h>
#include<time.h>

GLfloat a[2] = { -0.5,-0.5 }, b[2] = { 0.5,-0.5 }, c[2] = { 0,0.5 };
GLfloat n = 100;

void offset(GLfloat* a,GLfloat* b,GLfloat n) {
	if (n > 1) {
		GLfloat xl = b[0] - a[0], yl = b[1] - a[1];
		GLfloat dx = (1.0 * rand() / RAND_MAX - 0.5) / 100;
		GLfloat dy = (1.0 * rand() / RAND_MAX - 0.5) / 100;
		GLfloat tx = xl * (n - 1) / n + a[0] + dx;
		GLfloat ty = yl * (n - 1) / n + a[1] + dy;
		tx = tx < -0.5 || tx>0.5 ? a[0] : tx;
		ty = ty < a[1] ? a[1] : ty;
		glBegin(GL_LINES);
		glVertex2f(b[0], b[1]);
		glVertex2f(tx, ty);
		glEnd();
		GLfloat t[2] = { tx,ty };
		offset(a, t, n - 1);
	}
	else {
		glBegin(GL_LINES);
		glVertex2f(a[0], a[1]);
		glVertex2f(b[0], b[1]);
		glEnd();
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glVertex2f(a[0], a[1]);
	glVertex2f(b[0], b[1]);
	glEnd();
	offset(a, c, n);
	offset(b,c,n);
	glFlush();
}

int main(int argc, char** argv) {
	srand((unsigned)(time(NULL)));
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("processing_triangle");
	glutDisplayFunc(display);
	glutMainLoop();
}

*/