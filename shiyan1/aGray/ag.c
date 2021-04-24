#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int main() {
	unsigned char rgb[720] = { "0" };
	unsigned char a = '0';
	long l = 54;
	FILE* fp = fopen("C:/Users/fly/Desktop/数字图像处理/shiyan1/1.bmp", "rb+");
	if (fp == NULL) {
		printf("not find!");
		return 0;
	}
	else {
		fseek(fp, 54L, SEEK_SET);
		for (int i = 0; i < 320; i++) {
			fread(rgb, 1, 720, fp);
			for (int j = 0; j < 240; j++) {
				a = (rgb[3 * j] + rgb[3 * j + 1] + rgb[3 * j + 2]) / 3;
				rgb[3 * j] = a;
				rgb[3 * j + 1] = a;
				rgb[3 * j + 2] = a;
			}
			fseek(fp, l, SEEK_SET);
			l += 720;
			fwrite(rgb, 1, 720, fp);
			fseek(fp, l, SEEK_SET);
		}
		fclose(fp);
		return 0;
	}
}