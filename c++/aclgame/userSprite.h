#ifndef userSprite_H
#define userSprite_H

#include"acllib.h"
#include"blueSprite.h"
#include"greenSprite.h"
#include"redSprite.h"

class userSprite {
public:
	//���λ��
	int x, y;
	//�����С
	int w, h;
	//���ڴ�С
	int winw, winh;
	//λ���ٶ�
	int s;
	//����ͼ��
	ACL_Image* img;

	userSprite(int tx, int ty, int tw, int th, int twinw, int twinh, int ts, ACL_Image* timg);
	void move(int key);
	int collision(blueSprite *t);
	int collision(greenSprite* t);
	int collision(redSprite* t);
	void draw();
};

#endif