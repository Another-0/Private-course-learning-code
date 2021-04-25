#include"blueSprite.h"
#include<stdlib.h>
#include<time.h>
#include<math.h>

blueSprite::blueSprite(int tx, int ty, int twidth, int theight, int tdx, int tdy, ACL_Image* timg, int tdelay) :autoSprite(tx, ty, twidth, theight, tdx, tdy, timg) {
	delay = tdelay;
}

blueSprite::blueSprite(blueSprite& t) : autoSprite(t) {
	delay = t.delay;
}

void blueSprite::changedirection(int ux, int uy) {
	if (delay == 0) {
		srand((unsigned)time(NULL));
		double Dx = double(ux) - double(x);
		double Dy = double(uy) - double(y);
		double l = sqrt(Dx * Dx + Dy * Dy);
		dx = floor(3 * Dx / l )+ rand() % 7 - 3;
		dy = floor(3 * Dy / l )+ rand() % 7 - 3;
		delay = 10;
	}
	else
	{
		delay--;
	}
}

void blueSprite::move(int winwidth,int winheight) {
	if (x < 0 || winwidth < x + width ) dx *= -1;
	if (y < 0 || winheight < y + height )dy *= -1;
	x += dx;
	y += dy;
}

void blueSprite::draw() {
	putImageScale(img, x, y,width,height);
}