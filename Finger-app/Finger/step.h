#pragma once

#include "todo.h"
#include<time.h>
#include <vector>
#include <fstream> 
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <stdio.h>
#include <Ws2tcpip.h>
#include <WinSock2.h> 

using namespace std;

#pragma comment (lib,"Ws2_32.lib")



#define STEP_TXT_1 "outfile\\step1.txt"
#define STEP_IMG_2 "outfile\\step2_MidFilter.bmp"
#define STEP_TXT_2 "outfile\\step2_MidFilter.txt"
#define STEP_IMG_3 "outfile\\step3_Normalize.bmp"
#define STEP_TXT_3 "outfile\\step3_Normalize.txt"
#define STEP_IMG_4 "outfile\\step4_Direction.bmp"
#define STEP_TXT_4 "outfile\\step4_Direction.txt"
#define STEP_IMG_5 "outfile\\step5_Frequency.bmp"
#define STEP_TXT_5 "outfile\\step5_Frequency.txt"
#define STEP_IMG_6 "outfile\\step6_Mask.bmp"
#define STEP_TXT_6 "outfile\\step6_Mask.txt"
#define STEP_IMG_7 "outfile\\step7_GaborEnhance.bmp"
#define STEP_TXT_7 "outfile\\step7_GaborEnhance.txt"
#define STEP_IMG_8 "outfile\\step8_Binary.bmp"
#define STEP_TXT_8 "outfile\\step8_Binary.txt"
#define STEP_IMG_9 "outfile\\step9_Thinning.bmp"
#define STEP_TXT_9 "outfile\\step9_Thinning.txt"
#define STEP_IMG_10 "outfile\\step10_MinuExtract.bmp"
#define STEP_TXT_10 "outfile\\step10_MinuExtract.txt"
#define STEP_IMG_11 "outfile\\step11_MinuFilter.bmp"
#define STEP_TXT_11 "outfile\\step11_MinuFilter.txt"
#define STEP_IMG_11_MDL "outfile\\Step11_MinuFilter_MDL.mdl"
#define STEP_IMG_12 "outfile\\step12_Result.bmp"


int minuCount = 0;

int Step1_LoadBmpImage(char *beginfilename, char* info) {
	char *filename = beginfilename;
	CopyFile(ToWideChar(filename), ToWideChar(STEP_TXT_1), false);

	int iWidth, iHeight, iDepth;
	int flag = ReadBMPImgFilePara(filename, iWidth, iHeight, iDepth);
	if (flag != 0) {
		//sprintf(info,"ͼ�����ʧ��"); 
		::MessageBox(NULL, _T("ͼ�����ʧ��"), _T("error"), MB_OK);
		return -1;
	}
	unsigned char *data = new unsigned char[iWidth*iHeight];
	flag = ReadBMPImgFileData(filename, data);
	if (flag != 0) {
		//sprintf(info, "ͼ�����ݶ�ȡʧ��");
		::MessageBox(NULL, _T("ͼ�����ݶ�ȡʧ��"), _T("error"), MB_OK);
		delete[] data;
		return -2;
	}
	flag = SaveDataToTextFile(STEP_TXT_1, data, iWidth, iHeight);
	if (flag != 0) {
		//sprintf(info,"���ݱ���ʧ��");
		::MessageBox(NULL, _T("���ݱ���ʧ��"), _T("error"), MB_OK);
		delete[] data;
		return -3;
	}
	//sprintf(info, "Դͼ[%s],���[%d]���߶�[%d]�����[%d b]",filename,iWidth,iHeight,iDepth);
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

int Step3_HistoNormalize(char* info) {
	char srcTxtFile[] = STEP_TXT_2;
	char srcImgFile[] = STEP_IMG_2;
	char dstTxtFile[] = STEP_TXT_3;
	char dstImgFile[] = STEP_IMG_3;
	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);
	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile, image1, iWidth, iHeight);
	unsigned char *image2 = new unsigned char[iWidth*iHeight];
	HistoNormalize(image1, image2, iWidth, iHeight);
	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);
	SaveDataToImageFile(srcImgFile, dstImgFile, image2);
	delete[] image1;
	delete[] image2;

	return 0;
}

int Step4_Direction(char* info) {
	char srcTxtFile[] = STEP_TXT_3;
	char srcImgFile[] = STEP_IMG_3;
	char dstTxtFile[] = STEP_TXT_4;
	char dstImgFile[] = STEP_IMG_4;
	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);
	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile, image1, iWidth, iHeight);
	float *tmpDirections = new float[iWidth*iHeight];
	ImgDirection(image1, tmpDirections, iWidth, iHeight);
	float *directions = new float[iWidth*iHeight];
	DircLowPass(tmpDirections, directions, iWidth, iHeight);
	//SaveDataToTextFile(dstTxtFile_fx, tmpDirections, iWidth, iHeight);
	SaveDataToTextFile(dstTxtFile, directions, iWidth, iHeight);
	const int DIRECTION_SCALE = 100;
	SaveDataToImageFile(srcImgFile, dstImgFile, directions, DIRECTION_SCALE);
	delete[] image1;
	delete[] tmpDirections;
	delete[] directions;

	return 0;
}

int Step5_Frequency(char* info) {
	char srcTxtFile_Img[] = STEP_TXT_3;
	char srcTxtFile_Dir[] = STEP_TXT_4;
	char srcImgFile[] = STEP_IMG_4;
	char dstTxtFile[] = STEP_TXT_5;
	char dstImgFile[] = STEP_IMG_5;
	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);
	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile_Img, image1, iWidth, iHeight);
	float *direction = new float[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile_Dir, direction, iWidth, iHeight);

	float *frequency = new float[iWidth*iHeight];
	Frequency(image1, direction, frequency, iWidth, iHeight);

	SaveDataToTextFile(dstTxtFile, frequency, iWidth, iHeight);

	const int FREQUENCY_SCALE = 1000;
	SaveDataToImageFile(srcImgFile, dstImgFile, frequency, FREQUENCY_SCALE);
	delete[] image1;
	delete[] direction;
	delete[] frequency;
	return 0;
}

int Step6_GetMask(char *info) {
	char srcTxtFile_Img[] = STEP_TXT_3;
	char srcTxtFile_Dir[] = STEP_TXT_4;
	char srcTxtFile_Fre[] = STEP_TXT_5;
	char srcImgFile[] = STEP_IMG_5;
	char dstTxtFile[] = STEP_TXT_6;
	char dstImgFile[] = STEP_IMG_6;
	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);
	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile_Img, image1, iWidth, iHeight);
	float *direction = new float[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile_Dir, direction, iWidth, iHeight);
	float *frequency = new float[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile_Fre, frequency, iWidth, iHeight);
	unsigned char* mask = new unsigned char[iWidth*iHeight];
	GetMask(image1, direction, frequency, mask, iWidth, iHeight);

	SaveDataToTextFile(dstTxtFile, mask, iWidth, iHeight);
	SaveDataToImageFile(srcImgFile, dstImgFile, mask);
	delete[] image1;
	delete[] mask;
	delete[] direction;
	delete[] frequency;
	return 0;
}

int Step7_GaborEnhance(char *info) {
	char srcTxtFile_Img[] = STEP_TXT_3;
	char srcTxtFile_Dir[] = STEP_TXT_4;
	char srcTxtFile_Fre[] = STEP_TXT_5;
	char srcTxtFile_Msk[] = STEP_TXT_6;
	char srcImgFile[] = STEP_IMG_6;
	char dstTxtFile[] = STEP_TXT_7;
	char dstImgFile[] = STEP_IMG_7;
	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);
	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile_Img, image1, iWidth, iHeight);
	float *direction = new float[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile_Dir, direction, iWidth, iHeight);
	float *frequency = new float[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile_Fre, frequency, iWidth, iHeight);
	unsigned char* mask = new unsigned char[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile_Msk, mask, iWidth, iHeight);

	unsigned char* image2 = new unsigned char[iWidth*iHeight];
	GaborEnhance(image1, direction, frequency, mask, image2, iWidth, iHeight);

	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);
	SaveDataToImageFile(srcImgFile, dstImgFile, image2);

	delete[] image1;
	delete[] direction;
	delete[] frequency;
	delete[] mask;
	delete[] image2;
	return 0;
}

int Step8_Binary(char *info) {
	char srcTxtFile[] = STEP_TXT_7;
	char srcImgFile[] = STEP_IMG_7;
	char dstTxtFile[] = STEP_TXT_8;
	char dstImgFile[] = STEP_IMG_8;
	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);
	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile, image1, iWidth, iHeight);

	unsigned char *image2 = new unsigned char[iWidth*iHeight];
	BinaryImg(image1, image2, iWidth, iHeight, 128);

	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);

	BinaryToGray(image2, image1, iWidth, iHeight);
	SaveDataToImageFile(srcImgFile, dstImgFile, image1);

	delete[] image1;
	delete[] image2;

	return 0;
}

int Step9_Thinning(char *info) {
	char srcTxtFile[] = STEP_TXT_8;
	char srcImgFile[] = STEP_IMG_8;
	char dstTxtFile[] = STEP_TXT_9;
	char dstImgFile[] = STEP_IMG_9;

	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);

	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile, image1, iWidth, iHeight);

	unsigned char *image2 = new unsigned char[iWidth*iHeight];
	Thinning(image1, image2, iWidth, iHeight, 200);

	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);

	BinaryToGray(image2, image1, iWidth, iHeight);
	SaveDataToImageFile(srcImgFile, dstImgFile, image1);

	delete[] image1;
	delete[] image2;

	return 0;

}

int Step10_MinuExtract(char *info) {
	char srcTxtFile[] = STEP_TXT_9;
	char srcImgFile[] = STEP_IMG_9;
	char dstTxtFile[] = STEP_TXT_10;
	char dstImgFile[] = STEP_IMG_10;

	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);

	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile, image1, iWidth, iHeight);

	unsigned char *image2 = new unsigned char[iWidth*iHeight];
	minuCount = Extract(image1, image2, iWidth, iHeight);

	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);

	BinaryToGray(image2, image1, iWidth, iHeight);
	SaveDataToImageFile(srcImgFile, dstImgFile, image1);

	delete[] image1;
	delete[] image2;
	return 0;
}

int Step11_MinuFilter(char *info) {
	const int MINU_COUNT_THRED = 4;
	if (minuCount < MINU_COUNT_THRED) {
		return -1;
	}
	char srcTxtFile_Minu[] = STEP_TXT_10;
	char srcTxtFile_Thin[] = STEP_TXT_9;
	char srcImgFile[] = STEP_IMG_10;
	char dstTxtFile[] = STEP_TXT_11;
	char dstImgFile[] = STEP_IMG_11;
	char dstMdlFile[] = STEP_IMG_11_MDL;

	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);

	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile_Minu, image1, iWidth, iHeight);

	unsigned char *thin = new unsigned char[iWidth*iHeight];
	ReadDatafromTextFile(srcTxtFile_Thin, thin, iWidth, iHeight);

	MINUTIAE *minutiaes = new MINUTIAE[minuCount];
	memset(minutiaes, sizeof(MINUTIAE), minuCount);
	MinuFilter(image1, thin, minutiaes, minuCount, iWidth, iHeight);

	SaveMinutiae(minutiaes, minuCount, dstMdlFile);

	unsigned char *image2 = new unsigned char[iWidth*iHeight];
	memset(image2, 0, iWidth*iHeight);
	for (int i = 0; i < minuCount; i++) {
		image2[(minutiaes[i].y - 1)*iWidth + (minutiaes[i].x - 1)] = 0xff;
	}
	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);

	SaveDataToImageFile(srcImgFile, dstImgFile, image2);
	delete[] image1;
	delete[] image2;
	delete[] thin;
	delete[] minutiaes;

	return 0;
}

int Step12_Enroll(char *filename, char* userName, char *info) {
	char *srcImgFile = filename;
	char srcMdlFile[MAX_PATH] = { STEP_IMG_11_MDL };
	char regName[MAX_PATH] = { 0 };
	char dstImgFile[MAX_PATH] = { 0 };
	char dstMDlFile[MAX_PATH] = { 0 };
	sprintf(regName, userName);
	sprintf(dstImgFile, "%s%s.bmp", "databases//", regName);
	sprintf(dstMDlFile, "%s%s.mdl", "databases//", regName);

	CopyFile(ToWideChar(srcImgFile), ToWideChar(dstImgFile), false);
	CopyFile(ToWideChar(srcMdlFile), ToWideChar(dstMDlFile), false);
	return 0;
}

int Step12_Match(char *beginname, char *mdlfile, char *info) {
	char *srcImgFile = beginname;
	char *srcMDlFile = { STEP_IMG_11_MDL };
	char *dstMdlile = mdlfile;
	char dstImgFile[] = STEP_IMG_12;

	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);

	MINUTIAE *minu1 = NULL, *minu2 = NULL;
	int minuAccount1 = 0, minuAccount2 = 0;
	minuAccount1 = ReadMinutiae(srcMDlFile, &minu1);
	minuAccount2 = ReadMinutiae(dstMdlile, &minu2);

	float similar = MinuSimilarity(iWidth, iHeight, minu1, minuAccount1, minu2, minuAccount2);

	delete[] minu1;
	delete[] minu2;
	CopyFile(ToWideChar(srcImgFile), ToWideChar(dstImgFile), false);
	sprintf(mdlfile, "%s %lf", mdlfile, similar);
	CString name(mdlfile);
	CString ok("YES ");
	CString no("NO ");
	const float SIMILAR_THRED = 0.5;
	if (similar < SIMILAR_THRED) {
		//MessageBox(NULL, no + name, _T("No"), MB_OK);
		return 0;
	}
	MessageBox(NULL, ok + name, _T("OK"), MB_OK);
	return 1;
}

int Step12_Identify(char *beginname, char *info) {

	vector<CString> m_FileList;
	CString csDirPath = _T("databases//*.mdl");
	HANDLE file;
	WIN32_FIND_DATA fileData;
	file = FindFirstFile(csDirPath.GetBuffer(), &fileData);
	if (file != INVALID_HANDLE_VALUE)
	{
		CString ofilename = fileData.cFileName;
		CString basepa("databases//");
		CString s = basepa + ofilename;
		m_FileList.push_back(s);
		bool bState = false;
		bState = FindNextFile(file, &fileData);
		while (bState) {
			ofilename = fileData.cFileName;
			s = basepa + ofilename;
			m_FileList.push_back(s);
			bState = FindNextFile(file, &fileData);
		}
	}

	for (int len = 0; len < m_FileList.size(); len++) {
		CString fn = m_FileList[len];
		USES_CONVERSION;
		char * matchName = T2A(fn);
		Step12_Match(beginname, matchName, info);
	}
	return 0;

}
