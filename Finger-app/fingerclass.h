#include "stdafx.h"
// FingerDlg.h : ͷ�ļ�
//
#pragma once
#include "CZKFPEngX.h"//����ָ�Ʋɼ���SDK
#include<fstream>
#include<iomanip>
#include<algorithm>
#include<io.h>//for filelength()
#define STEP_IMG_1 "temp\\Step1_Source.bmp"
#define STEP_TXT_1 "temp\\Step1_Source.txt"
#include<direct.h>//for _mkdir()
//����
#include <sapi.h>
#include <sphelper.h>
#pragma comment(lib,sapi.lib) 

#include<string>
#define TEMP_DIR "temp\\" //��ʱ�ļ��У����ڴ��ָ�����ǰ�������м䴦����
#define DB_DIR "Database\\"//ָ�ƿ��ļ���
#define DB_INDEX_TXT "Database\\index.txt" //ָ�ƿ������ļ�
#define STEP_TXT_2 "temp\\Step2_MidFilter.txt"
#define STEP_IMG_2 "temp\\Step2_MidFilter.bmp"
#define STEP_TXT_3 "temp\\Step3_Normalize.txt"
#define STEP_IMG_3 "temp\\Step3_Normalize.bmp"
#define STEP_TXT_4 "temp\\Step4_Direction.txt"
#define STEP_IMG_4 "temp\\Step4_Direction.bmp"
#define STEP_TXT_5 "temp\\Step5_Frequency.txt"
#define STEP_IMG_5 "temp\\Step5_Frequency.bmp"
#define STEP_TXT_6 "temp\\Step6_Mask.txt"
#define STEP_IMG_6 "temp\\Step6_Mask.bmp"
#define STEP_TXT_7 "temp\\Step7_GaborEnhance.txt"
#define STEP_IMG_7 "temp\\Step7_GaborEnhance.bmp"
#define STEP_TXT_8 "temp\\Step8_Binary.txt"
#define STEP_IMG_8 "temp\\Step8_Binary.bmp"
#define STEP_TXT_9 "temp\\Step9_Thinning.txt"
#define STEP_IMG_9 "temp\\Step8_Thinning.bmp"
#define STEP_TXT_10 "temp\\Step10_MinuExtract.txt"
#define STEP_IMG_10 "temp\\Step10_MinuExtract.bmp"
#define STEP_TXT_11 "temp\\Step11_MinuFilter.txt"
#define STEP_IMG_11 "temp\\Step11_MinuFilter.bmp"
#define STEP_IMG_11_MDL "temp\\Step11_MinuFilter_MDL.mdl"
#define STEP_IMG_12 "temp\\Step12_Result.bmp"
#define EMPTY "temp\\empty.bmp" 
//�հ�ͼ
#define WIDTHBYTES(bits) ((DWORD)(((bits)+31) & (~31)) / 8)
struct NEIGHBOR {
	int x;//�����꣨�У�
	int y;//�����꣨�У�
	int type;//���������ͣ�1-�˵㣬3-�ֲ�㣩
	float Theta;//�������߽Ƕȣ����ȣ�
	float Theta2Ridge;//���㼹�߷���нǣ����ȣ�
	float ThetaThisNibor;//����������ļ��߷��򣨻��ȣ�
	int distance;//������루����������
};
struct MINUTIAE {
	int x;//�����꣨�У�
	int y;//�����꣨�У�
	int type;//���������ͣ�1-�˵㣬3-�ֲ�㣩
	float theta;//�õ㴦�ļ��߷��򣨻��ȣ�
	NEIGHBOR *neibors;//��������������
};
using namespace std;
//ȫ�ֺ���
void InitDatabase();//��������ʼ��ָ�ƿ�
void InitFile(char *filename);//��������ʼ���ļ�
void GetDatabaseInfo(char *info); //��ȡָ�ƿ�ͳ����Ϣ
bool getVoiceTips(CString s);
void makebmp();
int Enroll(char * regName, char * srcImgFile, char * outImgFile, char * info, bool bSaveImg);