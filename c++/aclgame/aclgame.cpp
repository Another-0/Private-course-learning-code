#include"acllib.h"
#include"userSprite.h"
#include"autoSprite.h"
#include"blueSprite.h"
#include"greenSprite.h"
#include"redSprite.h"
#include<stdlib.h>
#include<math.h>
#include<time.h>
#pragma warning(disable: 4996)

const int winmaxwidth = 1000, winmaxheight = 800;//���ڴ�С
const int ux = 450, uy = 350, uw = 20, uh = 20, us = 10;//�������
int collision = 0, game = 1;//��������ײ��������Ϸ

const int bw = 20, bh = 20,bdelay = 3;//��ɫ��������
const int gw = 20, gh = 20, gsize = 5, gdirect = 1;//��ɫ��������
int maxredw = 50, maxredh = 40, rpainting = 2;//��ɫ��������

int x = 20, y = 20, dx = 0, dy = 0, rcreating = -2, rtime1 = -30, rtime2 =-70 , rmaxtime = 30;//�������
const int maxblue = 30, maxgreen = 15;//���������
int nowblue = 0, nowgreen = 0;//���о�������

double score =0, alivetime = 0;//�����ʹ��ʱ��
int rank = 50;
int finalscore = 0;//���յ÷�

userSprite* usr = NULL;//���
blueSprite* bs[maxblue] = { NULL };//��ɫ����
greenSprite* gs[maxgreen] = { NULL };//��ɫ����
redSprite* r1 = NULL, * r2 = NULL;//��ɫ����

ACL_Image img, blueimg, greenimg, redimg;//ͼƬָ��

void initData();
void paint();
void gameOver();
void keyEvent(int key, int event);
void timer(int id);

int Setup()
{	
	//��ʼ������
	initWindow("С��Ϸ", DEFAULT, DEFAULT, winmaxwidth, winmaxheight);
	//����ͼƬ
	loadImage("blueSprite.jpeg", &blueimg);
	loadImage("userSprite.jpeg", &img);
	loadImage("greenSprite.jpeg", &greenimg);
	loadImage("redSprite.jpeg", &redimg);
	//��ʼ������
	initData();
	//�¼���Ӧ	��
	registerTimerEvent(timer);
	registerKeyboardEvent(keyEvent);
	startTimer(0, 100);	
	startTimer(1, 4000);
	startTimer(2, 50);
	startTimer(3, 75);
	return 0;
}

//��ʼ����Ϸ����
void initData() {
	usr = new userSprite(ux, uy, uw, uh, winmaxwidth, winmaxheight, us, &img);
	srand((unsigned)time(NULL));
	x = rand() % (winmaxwidth * 3 / 5 - 1) + winmaxwidth / 5;
	y = rand() % (winmaxheight * 3 / 5 - 1) + winmaxheight / 5;
	dx = rand() % 10 - 5;
	dy = rand() % 10 - 5;
	r1 = new redSprite(0, y, winmaxwidth, 0, 0, dy, &redimg, rcreating, rpainting, 0);
	r2 = new redSprite(x, 0, 0, winmaxheight, dx, 0, &redimg, rcreating, rpainting, 1);
	paint();
}

//������Ϸ����
void paint() {
	if (game) {
		beginPaint();
		clearDevice();
		r1->draw();
		r2->draw();
		for (int j = 0; j < nowgreen; j++) {
			gs[j]->draw();
		}
		for (int i = 0; i < nowblue; i++) {
			bs[i]->draw();
		}
		usr->draw();
		char ps[100] = {};
		itoa(finalscore,ps,10);
		setTextSize(30);
		paintText(760, 20, "�÷֣�");
		paintText(850, 20, ps);
		endPaint();
	}
}

//������Ϸ
void gameOver() {
	cancelTimer(0);
	cancelTimer(2);
	cancelTimer(3);
	game = 0;
	beginPaint();
	clearDevice();
	setTextSize(100);
	paintText(250, 280, "��Ϸ����");
	setTextSize(50);
	char ps[100] = {};
	itoa(finalscore, ps, 10);
	paintText(300, 400, "���յ÷֣�");
	paintText(550, 400, ps);
	endPaint();
}


//���̰�������
void keyEvent(int key, int event) {
	if (event != KEY_DOWN)return;
	usr->move(key);
	for (int i = 0; i < nowblue; i++) {
		if (bs[i] != NULL) {
			collision = usr->collision(bs[i]);
			if (collision) {
				gameOver();
				return;
			}
		}
	}
	for (int j = 0; j < nowgreen; j++) {
		if (gs[j] != NULL) {
			collision = usr->collision(gs[j]);
			if (collision) {
				gameOver();
				return;
			}
		}
	}
	collision = usr->collision(r1);
	if (collision) gameOver();
	collision = usr->collision(r2);
	if (collision)gameOver();
	paint();
}


//��ʱ������
void timer(int id) {
	switch (id)
	{
	case 0://��ɫ�����ƶ�
		for (int i = 0; i < nowblue; i++) {
			bs[i]->changedirection(usr->x, usr->y);
			bs[i]->move(winmaxwidth, winmaxheight);
			collision = usr->collision(bs[i]);
			if (collision) {
				gameOver();
				break;
			}
		}

		alivetime = alivetime + 0.1;
		score = score + alivetime;
		finalscore = floor(score);
		break;
	case 1://���ɾ���
		srand((unsigned)time(NULL));

		//��ɫ��������
		x = rand() % (winmaxwidth - bw + 1);
		y = rand() % (winmaxheight - bh + 1);
		dx = rand() % 5 + 1;
		dy = rand() % 5 + 1;
		for (int k = 0; k < maxgreen; k++) {
			if (gs[k] == NULL) {
				gs[k] = new greenSprite(x, y, gh, gw, dx, dy, &greenimg, gsize, gdirect);
				nowgreen++;
				break;
			}
		}

		//��ɫ��������
		x = rand() % (winmaxwidth - bw + 1);
		y = rand() % (winmaxheight - bh + 1);
		for (int j = 0; j < maxblue; j++) {
			if (bs[j] == NULL) {
				bs[j] = new blueSprite(x, y, bw, bh, dx, dy, &blueimg, bdelay);
				nowblue++;
				break;
			}
		}
		if (nowblue == maxblue) {
			cancelTimer(1);
		}
		break;
	case 2://��ɫ�����ƶ�
		for (int a = 0; a < nowgreen; a++) {
			if (gs[a] != NULL) {
				gs[a]->changeSize();
				gs[a]->move(winmaxwidth, winmaxheight);
				collision = usr->collision(gs[a]);
				if (collision) {
					gameOver();
					break;
				}
			}
		}	
		break;
	case 3://��ɫ�����ж�
		r1->move(winmaxwidth, winmaxheight);
		r1->changeState(maxredw, maxredh, winmaxwidth, winmaxheight, rtime1, rmaxtime);
		r2->move(winmaxwidth, winmaxheight);
		r2->changeState(maxredw, maxredh, winmaxwidth, winmaxheight, rtime2, rmaxtime);
		collision = usr->collision(r1);
		if (collision) gameOver();
		collision = usr->collision(r2);
		if (collision)gameOver();
		break;
	default:
		break;
	}
	paint();
}