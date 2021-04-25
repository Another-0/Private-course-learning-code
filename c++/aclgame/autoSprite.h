#ifndef autoSprite_H
#define autoSprite_H

#include"acllib.h"

//���� -- ����
class autoSprite {
public:
	//�����λ��
	int x, y;
	//����Ĵ�С
	int width, height;
	//������ƶ�����
	int dx, dy;
	//�����ͼ��
	ACL_Image *img;

	//���캯�� -- ������
	autoSprite(int tx, int ty, int twidth, int theight, int tdx, int tdy, ACL_Image* timg);

	//��������
	virtual ~autoSprite();

	//�ƶ�
	virtual void move(int winwidth,int winheight) = 0;

	//����
	virtual void draw() = 0;
};

#endif