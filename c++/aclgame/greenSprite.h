#ifndef greenSprite_H
#define greenSprite_H

#include"autoSprite.h"

//��ͬ��С����ɫ����
class greenSprite :public autoSprite {
protected:
	//���ͱ���
	int size, direct;
public:
	greenSprite(int tx, int ty, int tw, int th, int tdx, int tdy, ACL_Image* timg, int tsize, int tdirect);
	void move(int winw, int winh);
	void draw();
	void changeSize();
};

#endif
