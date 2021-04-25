#include<stdio.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

BITMAPFILEHEADER fileHeader;
BITMAPINFOHEADER infoHeader;

long maxcol = 1800;//最大列数为600
typedef unsigned char(*RGB)[1800];

RGB readbmp(char* name, char* gs);
RGB zengqiang(RGB rgb, int mo[3][3], int x, int y);
int savebmp(RGB rgb, char* name);

int main() {
	int x = 0, y = 0;
	int mo1[3][3] = { {-1,-1,-1},{-1,9,-1},{-1,-1,-1} }, mo2[3][3] = { {1,2,1},{0,1,0},{-1,-2,-1} };
	RGB rgb = NULL, outrgb = NULL;
	rgb = readbmp("C:/Users/fly/Desktop/数字图像处理/shiyan4/4.bmp", "rb");
	if (rgb == NULL)return 0;
	x = (int)infoHeader.biHeight;
	y = (int)infoHeader.biWidth;
	outrgb = zengqiang(rgb, mo1, x, y);
	if (outrgb != NULL)savebmp(outrgb, "C:/Users/fly/Desktop/数字图像处理/shiyan4/41.bmp");
	//outrgb = zengqiang(rgb, mo2, x, y);
	//if (outrgb != NULL)savebmp(outrgb, "C:/Users/fly/Desktop/数字图像处理/shiyan4/42.bmp");
	free(outrgb);
	free(rgb);
	return 0;
}

//读取图片
RGB readbmp(char* name, char* gs) {
	FILE* fp = fopen(name, gs);
	if (fp == NULL) return NULL;
	fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	if (maxcol < infoHeader.biWidth * 3 || infoHeader.biHeight < 1)return NULL;
	unsigned char(*data)[1800] = (unsigned char(*)[1800])malloc(sizeof(unsigned char) * infoHeader.biHeight * 1800);
	if (data == NULL)return NULL;
	for (int i = 0; i < infoHeader.biHeight; i++) {
		fread(data[i], (sizeof(unsigned char) * infoHeader.biWidth * 3 + 3) / 4 * 4, 1, fp);
		if (ferror(fp))printf("error");
		if (feof(fp))printf("end");
	}
	fclose(fp);
	return data;
}

//储存图片
int savebmp(RGB rgb, char* name) {
	FILE* wp = fopen(name, "wb");
	if (wp == NULL)return-1;
	fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, wp);
	fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, wp);
	for (int i = 0; i < infoHeader.biHeight; i++) {
		fwrite(rgb[i], (sizeof(unsigned char) * infoHeader.biWidth * 3 + 3) / 4 * 4, 1, wp);
	}
	fclose(wp);
	return 0;
}

//图像增强
RGB zengqiang(RGB rgb, int mo[3][3], int x, int y) {
	if (maxcol < infoHeader.biWidth * 3 || infoHeader.biHeight < 2)return NULL;
	unsigned char(*data)[1800] = (unsigned char(*)[1800])malloc(sizeof(unsigned char) * infoHeader.biHeight * 1800);
	if (data == NULL)return NULL;
	int p = 0;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			for (int s = -1; s < 2; s++) {
				for (int t = -1; t < 2; t++) {
					if (i + s >= 0 && j + t >= 0 && i + s < x && j + t < y)p += mo[s + 1][t + 1] * rgb[i + s][(j + t) * 3];
				}
			}
			data[i][j * 3] = (unsigned char)p;
			data[i][j * 3 + 1] = (unsigned char)p;
			data[i][j * 3 + 2] = (unsigned char)p;
			p = 0;
		}
	}
	return data;
}