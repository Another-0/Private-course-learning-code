#ifndef autoSprite_H
#define autoSprite_H

#include"acllib.h"

//精灵 -- 基类
class autoSprite {
public:
	//精灵的位置
	int x, y;
	//精灵的大小
	int width, height;
	//精灵的移动方向
	int dx, dy;
	//精灵的图像
	ACL_Image *img;

	//构造函数 -- 创建类
	autoSprite(int tx, int ty, int twidth, int theight, int tdx, int tdy, ACL_Image* timg);

	//析构函数
	virtual ~autoSprite();

	//移动
	virtual void move(int winwidth,int winheight) = 0;

	//绘制
	virtual void draw() = 0;
};

#endif