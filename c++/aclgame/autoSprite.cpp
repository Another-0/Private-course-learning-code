#include"acllib.h"
#include"autoSprite.h"

//���ຯ��ʵ��
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