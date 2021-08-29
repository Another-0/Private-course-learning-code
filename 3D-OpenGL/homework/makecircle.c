/*

#include<stdio.h>
#include<gl/glut.h>
#include<math.h>


double r = 0;
double pi = 3.14;
double n = 100;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(50, 50, 400, 400);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++) {
		glVertex2f(cos(r), sin(r));
		r += 2*pi / n;
		}
	glEnd();

	glFlush();
}

int main(int argc,char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("make-circle");
	glutDisplayFunc(display);
	glutMainLoop();
}

*/