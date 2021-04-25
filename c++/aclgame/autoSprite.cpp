#include"acllib.h"
#include"autoSprite.h"

//基类函数实现
autoSprite::autoSprite(int tx, int ty, int twidth, int theight, int tdx, int tdy, ACL_Image* timg) {
	x = tx;
	y = ty;
	width = twidth;
	height = theight;
	dx = tdx;
	dy = tdy;
	img = timg;
};

autoSprite::~autoSprite() {

};