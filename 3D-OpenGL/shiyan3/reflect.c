

#include<stdio.h>
#include<gl/glut.h>


//创建光源
void CreateLight(void) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat pointlight_position[] = { 5, 5, 5,1 };
	GLfloat pointlight_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat pointlight_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat pointlight_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pointlight_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, pointlight_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, pointlight_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, pointlight_ambient);
}

//绘制墙壁
void DrawWall() {
	GLfloat wall_ambient[4] = { 0.6, 0.2, 0.5, 0.5 };
	GLfloat wall_diffuse[4] = { 0.8, 0.2, 0.5, 0.5 };
	GLfloat wall_specular[4] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat wall_shininess = 50;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wall_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wall_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wall_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, wall_shininess);

	glColor3f(0.4, 0.4, 0.7);
	glNormal3f(1, 0, 0);
	glBegin(GL_QUADS);
	GLfloat dx = -10, dy = 10, n = 2;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			glVertex3f(-10, dx, dy);
			glVertex3f(-10, dx + 20 / n, dy);
			glVertex3f(-10, dx + 20 / n, dy - 20 / n);
			glVertex3f(-10, dx, dy - 20 / n);
			dx += 20 / n;
		}
		dx = -10;
		dy -= 20 / n;
	}
	glEnd();

	glNormal3f(0, 1, 0);
	glBegin(GL_QUADS);
	dx = 10;
	dy = 10;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			glVertex3f(dx, -10, dy);
			glVertex3f(dx - 20 / n, -10, dy);
			glVertex3f(dx - 20 / n, -10, dy - 20 / n);
			glVertex3f(dx, -10, dy - 20 / n);
			dx -= 20 / n;
		}
		dx = 10;
		dy -= 20 / n;
	}
	glEnd();

	glNormal3f(0, -1, 0);
	glBegin(GL_QUADS);
	dx = 10;
	dy = 10;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			glVertex3f(dx, 10, dy);
			glVertex3f(dx - 20 / n, 10, dy);
			glVertex3f(dx - 20 / n, 10, dy - 20 / n);
			glVertex3f(dx, 10, dy - 20 / n);
			dx -= 20 / n;
		}
		dx = 10;
		dy -= 20 / n;
	}
	glEnd();
}

//绘制屋顶
void DrawCeiling() {
	GLfloat wall_ambient[4] = { 0.6, 0.2, 0.5, 0.5 };
	GLfloat wall_diffuse[4] = { 0.8, 0.2, 0.5, 0.5 };
	GLfloat wall_specular[4] = { 0.5, 0.5, 0.5,1.0 };
	GLfloat wall_shininess = 100;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wall_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wall_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wall_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, wall_shininess);

	glColor3f(0, 0.4, 0);
	glNormal3f(0, 0, -1);
	glBegin(GL_QUADS);
	GLfloat dx = 10, dy = 10, n = 2;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			glVertex3f(dx, dy, 10);
			glVertex3f(dx - 20 / n, dy, 10);
			glVertex3f(dx - 20 / n, dy - 20 / n, 10);
			glVertex3f(dx, dy - 20 / n, 10);
			dx -= 20 / n;
		}
		dx = 10;
		dy -= 20 / n;
	}
	glEnd();
}

//绘制地板
void DrawGround() {
	GLfloat ground_ambient[4] = { 1, 1, 1, 0.5 };
	GLfloat ground_diffuse[4] = { 1, 1, 1, 0.5 };
	GLfloat ground_specular[4] = { 1, 1, 1, 0.5 };
	GLfloat ground_shininess = 50;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ground_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ground_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ground_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ground_shininess);

	glColor4f(1, 1, 1, 0.3);
	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-10, 10, -10);
	glVertex3f(10, 10, -10);
	glVertex3f(10, -10, -10);
	glVertex3f(-10, -10, -10);
	glEnd();
}

//绘制物体
void DrawFurnishings() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glColor3f(0, 0, 0.8);
	glTranslatef(-7, -5, -8);
	glutSolidCone(1.2, 4.0, 80, 50);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.8, 0.5, 0);
	glTranslatef(-7, 5, -8);
	glutSolidSphere(2, 50, 50);
	glPopMatrix();
}

//绘制房间
void DrawWorld() {
	CreateLight();
	DrawWall();
	DrawCeiling();
	DrawFurnishings();
}

//绘制反光
void reflectWorld() {
	glPushMatrix();
	GLfloat fLightPosMirror[4] = { 5,5,-25,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, fLightPosMirror);
	glPushMatrix();

	glFrontFace(GL_CW);
	glTranslatef(0, 0, -20);
	glScalef(1.0f, 1.0f, -1.0f);
	DrawWorld();
	glFrontFace(GL_CCW);
	glPopMatrix();

	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	DrawGround();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);

	GLfloat fLightPos[] = { 5, 5, 5,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, fLightPos);
	DrawWorld();
	glPopMatrix();
}

void display(void) {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, 1, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(11, 0, 0, 0, 0, 0, 0, 0, 1);

	reflectWorld();
	glFlush();
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glLightModeli(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("反光房间");
	glutDisplayFunc(display);
	init();

	glutMainLoop();
	return 0;
}

