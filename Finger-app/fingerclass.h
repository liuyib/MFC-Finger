#include "stdafx.h"
// FingerDlg.h : 头文件
//
#pragma once
#include "CZKFPEngX.h"//引入指纹采集器SDK
#include<fstream>
#include<iomanip>
#include<algorithm>
#include<io.h>//for filelength()
#define STEP_IMG_1 "temp\\Step1_Source.bmp"
#define STEP_TXT_1 "temp\\Step1_Source.txt"
#include<direct.h>//for _mkdir()
//语音
#include <sapi.h>
#include <sphelper.h>
#pragma comment(lib,sapi.lib) 

#include<string>
#define TEMP_DIR "temp\\" //临时文件夹，用于存放指纹入库前的所有中间处理结果
#define DB_DIR "Database\\"//指纹库文件夹
#define DB_INDEX_TXT "Database\\index.txt" //指纹库索引文件
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
//空白图
#define WIDTHBYTES(bits) ((DWORD)(((bits)+31) & (~31)) / 8)
struct NEIGHBOR {
	int x;//横坐标（列）
	int y;//纵坐标（行）
	int type;//特征点类型（1-端点，3-分叉点）
	float Theta;//两点连线角度（弧度）
	float Theta2Ridge;//两点脊线方向夹角（弧度）
	float ThetaThisNibor;//相邻特征点的脊线方向（弧度）
	int distance;//两点距离（像素数量）
};
struct MINUTIAE {
	int x;//横坐标（列）
	int y;//纵坐标（行）
	int type;//特征点类型（1-端点，3-分叉点）
	float theta;//该点处的脊线方向（弧度）
	NEIGHBOR *neibors;//相邻特征点序列
};
using namespace std;
//全局函数
void InitDatabase();//创建并初始化指纹库
void InitFile(char *filename);//创建并初始化文件
void GetDatabaseInfo(char *info); //获取指纹库统计信息
bool getVoiceTips(CString s);
void makebmp();
int Enroll(char * regName, char * srcImgFile, char * outImgFile, char * info, bool bSaveImg);