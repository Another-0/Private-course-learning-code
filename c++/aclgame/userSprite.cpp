#include"userSprite.h"

userSprite::userSprite(int tx, int ty,int tw,int th,int twinw,int twinh,int ts,ACL_Image *timg) {
	x = tx;
	y = ty;
	w = tw;
	h = th;
	winw = twinw;
	winh = twinh;
	s = ts;
	img = timg;
}

void userSprite::move(int key) {
	switch (key)
	{
	case VK_UP:
		y -= s;
		if (y < 0)y = 0;
		break;
	case VK_DOWN:
		y += s;
		if (y + h > winh)y = winh - h;
		break;
	case VK_LEFT:
		x -= s;
		if (x < 0)x = 0;
		break;
	case VK_RIGHT:
		x += s;
		if (x + w > winw)x = winw - w;
		break;
	default:
		break;
	}
}

void userSprite::draw() {
	putImageScale(img, x, y, w, h);
}

int userSprite::collision(blueSprite *t) {
	if (x + w <= t->x || t->x + t->width <= x || y + h <= t->y || t->y + t->height <= y) {
		return 0;
	}
	return 1;
}

int userSprite::collision(greenSprite* t) {
	if (x + w <= t->x || t->x + t->width <= x || y + h <= t->y || t->y + t->height <= y) {
		return 0;
	}
	return 1;
}

int userSprite::collision(redSprite* t) {
	if (t-> xy==1&&t->creating==0) {
		if (x + w <= t->x || t->x + t->width <= x)return 0;
		return 1;
	}
	if (t->xy == 0&&t->creating==0) {
		if (y + h <= t->y || t->y + t->height <= y)return 0;
		return 1;
	}
	return 0;
}