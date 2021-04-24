#include<stdio.h>
#include <windows.h>
#include<math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int main() {
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	int gray = 255;
	long sumdot = 0;
	double grayarray[257] = { 0 };
	unsigned char newhist[256] = { "0" };

	FILE* fp = fopen("C:/Users/fly/Desktop/数字图像处理/shiyan2/hist1.bmp", "r");
	if (fp == NULL) {
		printf("Not Find！");
	}
	else {
		fread(&fileHeader, sizeof(BITMAPFILEHEADER),1, fp);
		fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
		sumdot = infoHeader.biWidth * infoHeader.biHeight;
		unsigned char s[1500] = { "0" };
		for (int i = 0; i < infoHeader.biHeight; i++) {
			fread(s, 3 * infoHeader.biWidth, 1, fp);
			int t = 0;
			for (int j = 0; j < 3 * infoHeader.biWidth; j += 3) {
				t = (int)s[j+1];
				grayarray[t] += 1;
			}
		}

		for (int k = 1; k < 257; k++) {
			grayarray[k] = grayarray[k] / sumdot;
			grayarray[k] += grayarray[k - 1];
			newhist[k - 1] =(unsigned int) floor(grayarray[k] * 255);
			printf("%d  ", newhist[k-1]);
		}
		FILE* wp = fopen("C:/Users/fly/Desktop/数字图像处理/shiyan2/hist2.bmp", "w");
		fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, wp);
		fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, wp);
		fseek(fp, 54L, SEEK_SET);
		for (int i = 0; i < infoHeader.biHeight; i++) {
			fread(s, 3 * infoHeader.biWidth, 1, fp);
			for (int j = 0; j < infoHeader.biWidth; j++) {
				if (s[3 * j] != newhist[s[3*j]]) {
					s[3 * j] = newhist[s[3 * j]];
					s[3 * j + 1] = s[3 * j];
					s[3 * j + 2] = s[3 * j];
				}
			}
			fwrite(s, 3 * infoHeader.biWidth, 1, wp);;
		}
		fclose(wp);
		fclose(fp);
	}
	return 0;
}