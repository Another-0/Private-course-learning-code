/*

#include<stdio.h>
#include<gl/glut.h>
#include<math.h>

GLint light0 = 1, light1 = 1;
GLint shininess = 20;

//设置光源
void CreateLight(void) {
	glEnable(GL_LIGHTING);
	if (light0==1) {
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
	}
	if (light1==1) {
		glEnable(GL_LIGHT1);
	}
	else {
		glDisable(GL_LIGHT1);
	}
	GLfloat pointlight_position[] = { 5, 5, 5,1 };
	GLfloat pointlight_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat pointlight_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat pointlight_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pointlight_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, pointlight_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, pointlight_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, pointlight_ambient);

	GLfloat spotlight_position[] = { 0, 0, 5,1 };
	GLfloat spotlight_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat spotlight_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat spotlight_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat spotlight_direction[] = { 0.0, 0.0, -1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, spotlight_position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, spotlight_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spotlight_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, spotlight_ambient);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlight_direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);
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
			glVertex3f(-10, dx + 20/n, dy);
			glVertex3f(-10, dx + 20/n, dy -20/n);
			glVertex3f(-10, dx, dy - 20/n);
			dx += 20/n;
		}
		dx = -10;
		dy -= 20/n;
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
	GLfloat floor_ambient[4] = { 0.6, 0.2, 0.5, 0.5 };
	GLfloat floor_diffuse[4] = { 0.8, 0.2, 0.5, 0.5 };
	GLfloat floor_specular[4] = { 0.5, 0.5, 0.5,1.0 };
	GLfloat floor_shininess = 100;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, floor_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, floor_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, floor_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, floor_shininess);


	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	GLfloat dx = 10, dy = 10, n = 10;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			glTexCoord2f(1.0, 1.0);
			glVertex3f(dx, dy, -10);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(dx - 20 / n, dy, -10);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(dx - 20 / n, dy - 20 / n, -10);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(dx, dy - 20 / n, -10);
			dx -= 20 / n;
		}
		dx = 10;
		dy -= 20 / n;
	}
	glEnd();
}

//绘制物体
void DrawFurnishings() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glColor3f(0, 0, 0.8);
	glTranslatef(2, -3, -5);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glutSolidCone(1.2, 4.0, 80, 50);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.8, 0.5, 0);
	glTranslatef(-2, 0, -2);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glutSolidSphere(2, 50, 50);
	glPopMatrix();
}

//绘制房间
void DrawWorld() {
	CreateLight();
	DrawWall();
	DrawCeiling();
	DrawGround();
	DrawFurnishings();
}

//绘制窗口
void display(void) {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, 1, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(11, 0, 0, 0, 0, 0, 0, 0, 1);

	DrawWorld();
	glFlush();
}

//键盘回调
void mykey(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		shininess += 2;
	}
	if (key == GLUT_KEY_DOWN) {
		shininess -= 2;
	}
	printf("shininess : %d\n",shininess);
	glutPostRedisplay();
}

//菜单回调
void LightMenu(int value) {
	switch (value)
	{
	case 0:
		light0 = 1;
		break;
	case 1:
		light0 = 0;
		break;
	case 2:
		light1 = 1;
		break;
	case 3:
		light1 = 0;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

//初始化
void init() {
	glEnable(GL_COLOR_MATERIAL);
	glLightModeli(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_TEXTURE_2D);

	GLubyte image[8][8][3];
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int t = (i < 4 && j < 4) || (i >= 4 && j >= 4) ? 255 : 0;
			image[i][j][0] = image[i][j][1] = image[i][j][2] = (GLubyte)t;
		}
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 8, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("光照房间");
	glutDisplayFunc(display);
	glutSpecialFunc(mykey);
	init();
	glutCreateMenu(LightMenu);
	glutAddMenuEntry("开启环境光", 0);
	glutAddMenuEntry("关闭环境光", 1);
	glutAddMenuEntry("开启聚光灯", 2);
	glutAddMenuEntry("关闭聚光灯", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}

*/