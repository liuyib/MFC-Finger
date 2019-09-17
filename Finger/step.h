#pragma once
#include "todo.h"
#include <vector>
int minuCount = 0;

#define STEP_TXT_1 "outfile\\step1.txt"
#define STEP_IMG_2 "outfile\\step2_MidFilter.bmp"
#define STEP_TXT_2 "outfile\\step2_MidFilter.txt"

int Step1_LoadBmpImage(char *beginfilename, char* info) {
	char *filename = beginfilename;
	CopyFile(ToWideChar(filename), ToWideChar(STEP_TXT_1), false);

	int iWidth, iHeight, iDepth;
	int flag = ReadBMPImgFilePara(filename, iWidth, iHeight, iDepth);
	if (flag != 0) {
		::MessageBox(NULL, _T("图像加载失败"), _T("error"), MB_OK);
		return -1;
	}
	unsigned char *data = new unsigned char[iWidth*iHeight];
	flag = ReadBMPImgFileData(filename, data);
	if (flag != 0) {
		::MessageBox(NULL, _T("图像数据读取失败"), _T("error"), MB_OK);
		delete[] data;
		return -2;
	}
	flag = SaveDataToTextFile(STEP_TXT_1, data, iWidth, iHeight);
	if (flag != 0) {
		::MessageBox(NULL, _T("数据保存失败"), _T("error"), MB_OK);
		delete[] data;
		return -3;
	}
	//sprintf(info, "源图[%s],宽度[%d]，高度[%d]，深度[%d b]",filename,iWidth,iHeight,iDepth);
	delete[] data;
	return 0;
}

int Step2_MidFilter(char *beginfilename, char* info) {
	char srcTxtFile[] = STEP_TXT_1;
	char *srcImgFile = beginfilename;
	char dstTxtFile[] = STEP_TXT_2;
	char dstImgFile[] = STEP_IMG_2;
	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);
	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile, image1, iWidth, iHeight);
	unsigned char *image2 = new unsigned char[iWidth*iHeight];
	MidFilter(image1, image2, iWidth, iHeight);
	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);
	SaveDataToImageFile(srcImgFile, dstImgFile, image2);
	delete[] image1;
	delete[] image2;
	return 0;
}
