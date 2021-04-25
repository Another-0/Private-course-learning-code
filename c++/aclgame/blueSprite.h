#ifndef blueSprite_H
#define blueSprite_H

#include"autoSprite.h"

//追踪玩家的蓝色精灵
class blueSprite :public autoSprite {
protected:
	//追踪延迟
	int delay;

public:
	blueSprite(int tx, int ty, int twidth, int theight, int tdx, int tdy, ACL_Image* timg, int tdelay);
	blueSprite(blueSprite& t);

	void move(int winwidth,int winheight);

	//根据玩家位置改变移动方向
	void changedirection(int ux,int uy);

	void draw();
};

#endif