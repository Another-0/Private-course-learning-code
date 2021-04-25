#include"redSprite.h"
#include<stdlib.h>
#include<time.h>

redSprite::redSprite(int tx, int ty, int tw, int th, int tdx, int tdy, ACL_Image* timg, int tcreating, int tpainting, int txy) :autoSprite(tx, ty, tw, th, tdx, tdy, timg) {
	creating = tcreating;
	painting = tpainting;
	xy = txy;
}

void redSprite::draw() {
	if(creating!=-2)putImageScale(img, x, y, width, height);
}

void redSprite::changeState(int &maxredw, int &maxredh,int maxwinw,int maxwinh,int &rtime,int maxrtime) {
	if (creating == 0) {
		if (xy == 0 && (y <= maxwinh / 10 || y + height >= maxwinh * 9 / 10))creating = -1;
		if (xy == 1 && (x <= maxwinw / 10 || x + width >= maxwinw * 9 / 10))creating = -1;
	}
	if (creating==1) {
		if (xy == 0 && height >= maxredh)creating = 0;
		if (xy == 1 && width >= maxredw)creating = 0;
	}
	if (creating == -1) {
		if (xy == 0 && height <= 0)creating = -2;
		if (xy == 1 && width <= 0)creating = -2;
	}
	if (creating == -2) {
		srand((unsigned)time(NULL));
		if (rtime >= maxrtime) {
			rtime = 0;
			creating = 1;
			if (xy == 1) {
				maxredw = rand() % 61 + 10;
				x = rand() % (maxwinw * 3 / 5 - 1) + maxwinw / 5;
				dx = rand() % 10 - 5;
				dx = dx == 0 ? 1 : dx;
			}
			if (xy == 0) {
				maxredh = rand() % 61 + 10;
				y = rand() % (maxwinh * 3 / 5 - 1) + maxwinh / 5;
				dy = rand() % 10 - 5;
				dy = dy == 0 ? 1 : dy;
			}
		}
		else {
			rtime = rtime + rand() % 3;
		}
	}
}

void redSprite::move(int winw, int winh) {
	if (creating == 0) {
		if (xy == 0) {
			y += dy;
		}
		if (xy == 1) {
			x += dx;
		}
	}
	if (creating == 1) {
		if (xy == 0) {
			height += painting;
			y -= painting / 2;
		}
		if (xy == 1) {
			width += painting;
			x -= painting / 2;
		}
	}
	if (creating == -1) {
		if (xy == 0 ) {
			height -= painting;
			y +=  painting / 2;
		}
		if (xy == 1 ) {
			width -= painting;
			x += painting / 2;
		}
	}
}