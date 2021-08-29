#include<stdio.h>
#include<gl/glut.h>
#define _USE_MATH_DEFINES
#include<math.h>

GLdouble tr = 0.3, dr = 0.5, h = 0.5;
GLdouble n = 20, y = 3.14 / 10;
GLint kaiguan = 1;

void paint(GLdouble dp[3], GLdouble tp[3], GLdouble i) {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3d(dp[0], dp[2] * sin(y) + dp[1] * cos(y), dp[2] * cos(y) - dp[1] * sin(y));
	glVertex3d(tp[0], tp[2] * sin(y) + tp[1] * cos(y), tp[2] * cos(y) - tp[1] * sin(y));
	dp[0] = dr * cos((i + 1) * 2 * M_PI / n);
	dp[2] = dr * sin((i + 1) * 2 * M_PI / n);
	glVertex3d(dp[0], dp[2] * sin(y) + dp[1] * cos(y), dp[2] * cos(y) - dp[1] * sin(y));
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLES);
	glVertex3d(tp[0], tp[2] * sin(y) + tp[1] * cos(y), tp[2] * cos(y) - tp[1] * sin(y));
	glVertex3d(dp[0], dp[2] * sin(y) + dp[1] * cos(y), dp[2] * cos(y) - dp[1] * sin(y));
	tp[0] = tr * cos((2 * i + 3) * M_PI / n);
	tp[2] = tr * sin((2 * i + 3) * M_PI / n);
	glVertex3d(tp[0], tp[2] * sin(y) + tp[1] * cos(y), tp[2] * cos(y) - tp[1] * sin(y));
	glEnd();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	GLdouble dp[3] = { 0 }, tp[3] = { 0 };
	dp[0] = dr;
	dp[1] = -h / 2;
	dp[2] = 0;
	tp[0] = tr * cos(M_PI / n);
	tp[1] = h / 2;
	tp[2] = tr * sin(M_PI / n);
	for (GLdouble i = 0; i < n; i++) {
		paint(dp, tp, i);
		dp[0] = dr * cos((i + 1) * 2 * M_PI / n);
		dp[2] = dr * sin((i + 1) * 2 * M_PI / n);
		tp[0] = tr * cos((2 * i + 3) * M_PI / n);
		tp[2] = tr * sin((2 * i + 3) * M_PI / n);
	}
	glBegin(GL_LINE_STRIP);
	for (GLdouble j = 0; j <= n; j++) {
		glVertex3d(dp[0], dp[2] * sin(y) + dp[1] * cos(y), dp[2] * cos(y) - dp[1] * sin(y));
		dp[0] = dr * cos((j + 1) * 2 * M_PI / n);
		dp[2] = dr * sin((j + 1) * 2 * M_PI / n);
	}
	glEnd();
	glFlush();
}

void changer(int key, int x, int y) {
	if (kaiguan == 1) {
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT && key == GLUT_KEY_DOWN) {
			dr -= 0.05;
			dr = dr <= 0 ? 0.05 : dr;
		}
		else if (glutGetModifiers() == GLUT_ACTIVE_SHIFT && key == GLUT_KEY_UP) {
			dr += 0.05;
			dr = dr >= 1 ? 0.95 : dr;
		}
		else if (key == GLUT_KEY_DOWN) {
			tr -= 0.05;
			tr = tr <= 0 ? 0.05 : tr;
		}
		else if (key == GLUT_KEY_UP) {
			tr += 0.05;
			tr = tr >= 1 ? 0.95 : tr;
		}
		display();
	}
}

void lock(int button, int state, int x, int y) {
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		kaiguan = (kaiguan + 1) % 2;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(720, 720);
	glutCreateWindow("change circle");
	glutDisplayFunc(display);
	glutSpecialFunc(changer);
	glutMouseFunc(lock);
	glutMainLoop();
}

