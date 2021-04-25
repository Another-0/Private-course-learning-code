#ifndef userSprite_H
#define userSprite_H

#include"acllib.h"
#include"blueSprite.h"
#include"greenSprite.h"
#include"redSprite.h"

class userSprite {
public:
	//玩家位置
	int x, y;
	//精灵大小
	int w, h;
	//窗口大小
	int winw, winh;
	//位移速度
	int s;
	//精灵图像
	ACL_Image* img;

	userSprite(int tx, int ty, int tw, int th, int twinw, int twinh, int ts, ACL_Image* timg);
	void move(int key);
	int collision(blueSprite *t);
	int collision(greenSprite* t);
	int collision(redSprite* t);
	void draw();
};

#endif