#ifndef redSprite_H
#define redSprite_H

#include"autoSprite.h"

class redSprite :public autoSprite {
public:
	//×´Ì¬
	int creating;
	int painting;
	//ÖáÏò
	int xy;

	redSprite(int tx, int ty, int tw, int th, int tdx, int tdy, ACL_Image* timg, int tcreating, int tpainting, int txy);
	void draw();
	void move(int winw, int winh);
	void changeState(int &maxredw, int &maxredh, int maxwinw, int maxwinh,int &rtime,int maxrtime);
};
#endif