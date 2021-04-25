#ifndef greenSprite_H
#define greenSprite_H

#include"autoSprite.h"

//不同大小的绿色精灵
class greenSprite :public autoSprite {
protected:
	//体型倍率
	int size, direct;
public:
	greenSprite(int tx, int ty, int tw, int th, int tdx, int tdy, ACL_Image* timg, int tsize, int tdirect);
	void move(int winw, int winh);
	void draw();
	void changeSize();
};

#endif
