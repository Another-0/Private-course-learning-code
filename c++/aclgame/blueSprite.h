#ifndef blueSprite_H
#define blueSprite_H

#include"autoSprite.h"

//׷����ҵ���ɫ����
class blueSprite :public autoSprite {
protected:
	//׷���ӳ�
	int delay;

public:
	blueSprite(int tx, int ty, int twidth, int theight, int tdx, int tdy, ACL_Image* timg, int tdelay);
	blueSprite(blueSprite& t);

	void move(int winwidth,int winheight);

	//�������λ�øı��ƶ�����
	void changedirection(int ux,int uy);

	void draw();
};

#endif