#include<stdio.h>
#include<gl/glut.h>

GLint light0 = 1;
GLint textmode = 1;
GLint texton = 1;
GLuint wall_texture, floor_texture, ceiling_texture;
GLubyte wall[8][8][3], floor[8][8][3], ceiling[8][8][3];

//载入纹理对象
GLuint createTexture(GLubyte texels[8][8][3]) {
	GLuint last_texture_ID, texture_ID;
	glGenTextures(1, &texture_ID);
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 8, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, texels);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, last_texture_ID);
	return texture_ID;
}

//创建环境光
void CreateLight(void) {
	glEnable(GL_LIGHTING);
	if (light0 == 1) {
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
	}
	GLfloat pointlight_position[] = { 5, 5, 5,1 };
	GLfloat pointlight_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat pointlight_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat pointlight_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pointlight_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, pointlight_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, pointlight_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, pointlight_ambient);
}

//绘制墙壁
void DrawWall()  {
	GLfloat wall_ambient[4] = { 0.6, 0.2, 0.5, 0.5 };
	GLfloat wall_diffuse[4] = { 0.8, 0.2, 0.5, 0.5 };
	GLfloat wall_specular[4] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat wall_shininess = 50;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wall_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wall_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wall_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, wall_shininess);

	glBindTexture(GL_TEXTURE_2D, wall_texture);
	glColor3f(0.4, 0.4, 0.7);
	glNormal3f(1, 0, 0);
	glBegin(GL_QUADS);
	GLfloat dx = -10, dy = 10, n = 10;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			glTexCoord2f(0.0, 1.0);
			glVertex3f(-10, dx, dy);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(-10, dx + 20 / n, dy);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(-10, dx + 20 / n, dy - 20 / n);
			glTexCoord2f(0.0, 0.0);
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
			glTexCoord2f(1.0, 1.0);
			glVertex3f(dx, -10, dy);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(dx - 20 / n, -10, dy);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(dx - 20 / n, -10, dy - 20 / n);
			glTexCoord2f(1.0, 0.0);
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
			glTexCoord2f(1.0, 1.0);
			glVertex3f(dx, 10, dy);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(dx - 20 / n, 10, dy);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(dx - 20 / n, 10, dy - 20 / n);
			glTexCoord2f(1.0, 0.0);
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
	glBindTexture(GL_TEXTURE_2D, ceiling_texture);

	GLfloat wall_ambient[4] = { 0.6, 0.2, 0.5, 0.5 };
	GLfloat wall_diffuse[4] = { 0.8, 0.2, 0.5, 0.5 };
	GLfloat wall_specular[4] = { 0.5, 0.5, 0.5,1.0 };
	GLfloat wall_shininess = 100;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wall_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wall_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wall_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, wall_shininess);


	glColor3f(0.1, 0.4, 0.1);
	glNormal3f(0, 0, -1);
	glBegin(GL_QUADS);
	GLfloat dx = 10, dy = 10, n = 10;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			glTexCoord2f(1.0, 1.0);
			glVertex3f(dx, dy, 10);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(dx - 20 / n, dy, 10);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(dx - 20 / n, dy - 20 / n, 10);
			glTexCoord2f(1.0, 0.0);
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
	glBindTexture(GL_TEXTURE_2D, floor_texture);

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
	glBindTexture(GL_TEXTURE_2D, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glColor3f(0, 0, 0.8);
	glTranslatef(2, -3, -5);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);
	glutSolidCone(1.2, 4.0, 80, 50);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.8, 0.5, 0);
	glTranslatef(-2, 0, -2);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);
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
	gluLookAt(12, 0, 0, 0, 0, 0, 0, 0, 1);


	if (texton) {
		glEnable(GL_TEXTURE_2D);
		if (textmode) {
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		}
		else {
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}
	}
	else {
		glDisable(GL_TEXTURE_2D);
	}

	DrawWorld();
	glFlush();
}

//菜单回调
void LightMenu(int value) {
	switch (value)
	{
	case 0:
		light0 = (light0 + 1) % 2;
		break;
	case 1:
		texton = (texton + 1) % 2;
		break;
	case 2:
		textmode = (textmode + 1) % 2;
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

	//地板纹理
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			GLubyte t = (i < 4 && j < 4) || (i >= 4 && j >= 4) ? 255 : 0;
			floor[i][j][0] = floor[i][j][1] = floor[i][j][2] = t;
		}
	}
	floor_texture = createTexture(floor);

	//墙壁纹理
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			GLubyte r = (5 * i * j) % 255;
			GLubyte g = (5 * i * j) % 255;
			GLubyte b = (5 * i * j) % 255;
			wall[i][j][0] = (GLubyte)r;
			wall[i][j][1] = (GLubyte)g;
			wall[i][j][2] = (GLubyte)b;
		}
	}
	wall_texture = createTexture(wall);

	//天花板纹理
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i + j >= 6 && i + j <= 8 || i + 1 >= j && i <= j + 1) {
				ceiling[i][j][0] = ceiling[i][j][1] = ceiling[i][j][2] = 0;
			}
			else {
				ceiling[i][j][0] = ceiling[i][j][1] = ceiling[i][j][2] = 255;
			}
		}
	}
	ceiling_texture = createTexture(ceiling);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("纹理房间");
	glutDisplayFunc(display);
	init();
	glutCreateMenu(LightMenu);
	glutAddMenuEntry("开启/关闭环境光", 0);
	glutAddMenuEntry("开启/关闭纹理", 1);
	glutAddMenuEntry("切换纹理模式", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}