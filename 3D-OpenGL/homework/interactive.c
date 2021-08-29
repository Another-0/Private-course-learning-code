
/**
#include<stdio.h>
#include<gl/glut.h>

GLint id = 12;//������
GLint isline = 0;//�ж��Ƿ���ͼ�ε����һ�����Ƶ�
GLint winh = 400, winw = 500;//���ڴ�С
GLint f[2][2] = { {0,0},{0,0} };//�ݴ�Ķ�������
GLint mx = 0, my = 0;//��ǰ�������
GLint isselect = 0;
GLfloat r = 0, g = 0, b = 0;
GLint dn = 0, ln = 0, tn = 0, rn = 0;//ͼ����Ŀ

//������ɢ��
void paintdot(GLenum mode) {
	if (mode == GL_SELECT) {
		glPushName(0);
		glPushName(dn);
	}
	else {
		dn += 1;
	}
	glBegin(GL_POINTS);
	glVertex2i(mx, my);
	glEnd();
	if (mode == GL_SELECT) glPopName();
}
//�����߶�
void paintline(GLenum mode) { 
	if (mode == GL_SELECT) {
		glPushName(1);
	}
	if (isline == 0) {
		glBegin(GL_POINTS);
		glVertex2i(mx, my);
		glEnd();
		f[isline][0] = mx;
		f[isline][1] = my;
		isline = 1;
	}
	else {
		if (mode == GL_SELECT) {
			glPushName(ln);
		}
		else {
			ln += 1;
		}
		glBegin(GL_POINTS);
		glVertex2i(mx, my);
		glEnd();
		glBegin(GL_LINES);
		glVertex2i(f[0][0], f[0][1]);
		glVertex2i(mx, my);
		glEnd();
		isline = 0;
		if (mode == GL_SELECT)glPopName();
	}
}
//����������
void painttriangle(GLenum mode) {
	if (mode == GL_SELECT)glPushName(2);
	if (isline < 2) {
		glBegin(GL_POINTS);
		glVertex2i(mx, my);
		glEnd();
		f[isline][0] = mx;
		f[isline][1] = my;
		isline += 1;
	}
	else {
		if (mode == GL_SELECT) {
			glPushName(tn);
		}
		else {
			tn += 1;
		}
		glBegin(GL_POINTS);
		glVertex2i(mx, my);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2i(f[0][0], f[0][1]);
		glVertex2i(f[1][0], f[1][1]);
		glVertex2i(mx, my);
		glEnd();
		isline = 0;
		if (mode == GL_SELECT)glPopName();
	}
}
//���ƾ���
void paintrect(GLenum mode) {
	if (mode == GL_SELECT)glPushName(3);
	if (isline == 0) {
		glBegin(GL_POINTS);
		glVertex2i(mx, my);
		glEnd();
		f[0][0] = mx;
		f[0][1] = my;
		isline = 1;
	}
	else {
		if (mode == GL_SELECT) {
			glPushName(rn);
		}
		else {
			rn += 1;
		}
		glBegin(GL_POINTS);
		glVertex2i(mx, my);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2i(f[0][0], f[0][1]);
		glVertex2i(mx, f[0][1]);
		glVertex2i(mx, my);
		glVertex2i(f[0][0],my);
		glEnd();
		isline = 0;
		if (mode == GL_SELECT)glPopName();
	}
}

//���ƺ���
void paint(GLenum mode , GLint id) {
	switch (id)
	{
	case 11:
		paintdot(mode);
		break;
	case 12:
		paintline(mode);
		break;
	case 13:
		painttriangle(mode);
		break;
	case 14:
		paintrect(mode);
	default:
		break;
	}
}

//��ʾ�ص�����
void display(void) {
	paint(GL_RENDER, id);
	glFlush();
}

//ʰȡ������
void processhits(GLint hits, GLint namebuffer[]) {
	GLint names;
	printf("hits : %d\n", hits);
	GLint* ptr =(GLint*) namebuffer;
	for (int i = 0; i < hits; i++) {
		names = *ptr;
		ptr += 3;
		printf("names:");
		for (int j = 0; j < names; j++) {
			printf("%d", *ptr);
			ptr++;
		}
		printf("\n");
	}
}

//ʰȡ����
void select() {
	GLint picksize = 32, namebuffer[32] = { 0 };
	GLint hits, viewport[4];
	glSelectBuffer(picksize, namebuffer);
	glInitNames();
	glPushName(0);

	glRenderMode(GL_SELECT);
	glGetIntegerv(GL_VIEWPORT, viewport);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix((GLdouble)mx, (GLdouble)viewport[3]-my, 10.0, 10.0, viewport);
	gluOrtho2D(0, winw, winh, 0);
	paint(GL_SELECT, id);
	//paint(GL_SELECT, id);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	hits = glRenderMode(GL_RENDER);
	processhits(hits, namebuffer);
}

//���ص�����
void mymouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		mx = x;
		my = y;
		if (1 == isselect) {
			select();
		}
		else {
			glutPostRedisplay();
		}
	}
}

//�˵��ص�����
void mymenu(int value) {
	switch (value)
	{
	case 0:
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
		id = value;
		break;
	case 21:
		r = 1;
		g = 0;
		b = 0;
		glColor3f(r, g, b);
		break;
	case 22:
		r = 0;
		g = 1;
		b = 0;
		if (0 == isselect)glColor3f(r, g, b);
		break;
	case 23:
		r = 0;
		g = 0;
		b = 1;
		if (0 == isselect)glColor3f(r, g, b);
		break;
	case 24:
		r = 1;
		g = 1;
		b = 1;
		if (0 == isselect)glColor3f(r, g, b);
		break;
	case 3:
		isselect = (isselect + 1) % 2;
		if (isselect == 1) {
			glColor3f(0.5, 0.5, 0.5);
		}
		else {
			glColor3f(r, g, b);
		}
		isline = 0;
		break;
	default:
		isline = 0;
		id = value;
		break;
	}
}

//��ʼ������
void init() {
	glClearColor(0.0, 0.0, 0.0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0, winw, winh, 0);
	glLineWidth(3.0);
	glPointSize(5.0);
}

//������
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(winw, winh);
	glutCreateWindow("interactive");
	init();

	int menu1 = glutCreateMenu(mymenu);
	glutAddMenuEntry("��ɢ��", 11);
	glutAddMenuEntry("�߶�", 12);
	glutAddMenuEntry("������", 13);
	glutAddMenuEntry("����", 14);
	int menu2 = glutCreateMenu(mymenu);
	glutAddMenuEntry("��ɫ", 21);
	glutAddMenuEntry("��ɫ", 22);
	glutAddMenuEntry("��ɫ", 23);
	glutAddMenuEntry("��ɫ", 24);

	int menu = glutCreateMenu(mymenu);
	glutAddMenuEntry("���", 0);
	glutAddSubMenu("����ͼ��", menu1);
	glutAddSubMenu("�ı���ɫ", menu2);
	glutAddMenuEntry("�л�ʰȡģʽ", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMouseFunc(mymouse);
	glutDisplayFunc(display);
	glutMainLoop();
}

*/