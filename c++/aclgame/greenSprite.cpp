#include"greenSprite.h"

greenSprite::greenSprite(int tx, int ty, int tw, int th, int tdx, int tdy, ACL_Image* timg, int tsize, int tdirect) :autoSprite(tx, ty, tw, th, tdx, tdy, timg) {
	size = tsize;
	direct = tdirect;
}

void greenSprite::changeSize() {
	size += direct;
	if (size == 5 || size == 30)direct *= -1;
}

void greenSprite::move(int winw, int winh) {
	if (x < 0 || winw < x + width) dx *= -1;
	if (y < 0 || winh < y + height)dy *= -1;
	x += dx;
	y += dy;
}

void greenSprite::draw() {
	width = 10 + size * 3;
	height = 10 + size * 3;
	putImageScale(img, x, y, width, height);
}