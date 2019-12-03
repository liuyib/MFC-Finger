
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

// CFingerDlg 对话框
class CFingerDlg : public CDialogEx
{

	// 构造
public:
	CFingerDlg(CWnd* pParent = NULL);	// 标准构造函数

										// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FINGER_DIALOG };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
														// 实现
protected:
	HICON m_hIcon;
	CStatic m_staticInfo;
	CStatic m_picCtrl1;
	CStatic m_picCtrl2;
	CString m_name;//登记人姓名
	CZKFPEngX m_zkfpEng;
	int m_minuCount;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP();
	afx_msg void OnImageReceivedZkfpengx(BOOL FAR*AImageValid);

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedBtnDisconnect();
	char* openImagePath();//自动选择图片
	char* saveImagePath();//自动保存路径命名
	wchar_t *ToWideChar(char *str);//多字节字符串转换为Unicode宽字符串   
								   //实现在图像控件中显示图像的功能，
	int ShowImageInCtrl(CStatic &picCtrl, char * filename);
	afx_msg void OnBnClickedBtnCapture();
	int ReadBMPImageFilePara(CString filename, int &width, int &height, int &depth);
	int ReadBMPImgFileData(CString fileName, unsigned char *data);//获取位图数据
																  //用文本文件保存数据(无符号字符类型)
	int SaveDataToTextFile(char * dstFile, unsigned char*data, int width, int height);
	//浮点数类型
	int SaveDataToTextFile(char *dstFile, float *data, int width, int height);
	int Step_LoadBmpImage(char * info);

	afx_msg void OnBnClickedBtnStep1();
	afx_msg void OnBnClickedBtnDatabase();
	//从文本文件读取无符号字符类型的图像位图数据
	int ReadDataFromTextFile(char *srcFile, unsigned char*data, int iWidth, int iHeight);
	//从文本文件读取浮点数类型的图像位图数据
	int readDataFromTextFile(char*srcFile, float *data, int iWidth, int iHeight);
	//实现图像中值滤波算法
	int MidFilter(unsigned char*ucImg, unsigned char*ucDstImg, int iWidth, int iHeigh);
	//使用冒泡排序对数组进行升序排序
	void Sort(unsigned char* data, int dsize);
	//保存数据到BMP图像文件
	int SaveDataToImageFile(char *srcFile, char *dstFile, unsigned char * data);
	//scale:转换比例
	int SaveDataToImageFile(char *srcFile, char * dstFile, float*data, float scale);

	int WriteBMPImgFile(char *dstFileName, unsigned char ** pusImgData);
	//中值滤波单元测试
	int Step2_MidFilter(char* info);
	afx_msg void OnBnClickedBtnStep2();
	int HistoNormalize(unsigned char*ucImg, unsigned char*ucNormlImg, int iWidth, int iHeight);//直方图均衡化算法
	int Step3_Normalize(char *info);
	afx_msg void OnBnClickedBtnStep3();
	int ImgDirection(unsigned char * ucImg, float *fDirc, int iWidth, int iHeight);//指纹脊线
	int DircLowPass(float *fDirc, float *fFitDirc, int iWidth, int iHeight);//脊线方向低通滤波算法
	int Step4_Direction(char *info);
	afx_msg void OnBnClickedBtnStep4();
	//指纹脊线频率计算算法
	int Frequency(unsigned char* ucImg, float *fDirection, float *fFrequency, int iWidth, int iHeight);
	int Step5_Frequency(char *info);//实现指纹脊线频率计算单步测试

	afx_msg void OnBnClickedBtnStep5();//测试五
									   //实现指纹掩码计算
	int GetMask(unsigned char* ucImg, float *fDirection, float * fFrequency, unsigned char *ucMask, int iWidth, int iHeight);
	//实现指纹掩码计算单步测试功能
	int Step6_Mask(char *info);
	afx_msg void OnBnClickedBtnStep6();
	//用于实现Gabor滤波增强算法
	int GaborEnhance(unsigned char*ucImg, float*fDirection, float*fFrequency, unsigned char*ucMask, unsigned char*ucImgEnhanced, int iWidth, int iHeight);
	//图像Gabor滤波增强单步测试
	int Step7_GaborEnhance(char *info);

	afx_msg void OnBnClickedBtnStep7();

	//图像二值化算法
	int BinaryImg(unsigned char*ucImage, unsigned char*ucBinImage, int iWidth, int iHeight, unsigned char uThreshold);

	int BinaryToGray(unsigned char*ucBinImg, unsigned char*ucGrayImg, int iWidth, int iHeight);
	int Step8_Binary(char*info);
	afx_msg void OnBnClickedBtnStep8();
	//图像细化
	// ucBinedImg(源图数据)，ucThinnedImg（结果图数据），lWidth（图像宽度），lHeight（图像高度）
	int Thinning(unsigned char * ucBinedImg, unsigned char * ucThinnedImage, int lWidth, int lHeight, int lIterativeLimit);
	int Step9_Thinning(char *info);

	afx_msg void OnBnClickedBtnStep9();

	//指纹特征提取
	//ucThinImg(源图数据)，ucMinuImg（结果图数据），lWidth（图像宽度），lHeight（图像高度）
	int Extract(unsigned char * ucThinImg, unsigned char * ucMinuImg, int lWidth, int lHeight);
	// 特征提取单步测试
	//参数：minuCount(返回特征点数量)，info（返回操作成功或失败提示信息）
	int Step10_MinuExtract(int &minuCount, char *info);
	afx_msg void OnBnClickedBtnStep10();
	//特征过滤
	// minuData(特征过滤)，thinData（细化图数据），minutiaes（特征点数组），minuCount（特征点数量），lWidth（图像宽度），lHeight（图像高度）
	int MinuFilter(unsigned char *minuData, unsigned char *thinData, MINUTIAE * minutiaes, int &minuCount, int lWidth, int lHeight);
	//实现边缘特征点去除功能
	int CutEdge(MINUTIAE *minutiaes, int count, unsigned char * ucImg, int lWidth, int lHeight);
	//特征过滤单步测试
	//minuCount（特征点数量），info（返回操作成功或失败提示信息）
	int Step11_MinuFilter(int &minuCount, char *info);
	afx_msg void OnBnClickedBtnStep11();

	//保存特征模板文件
	//minutiaes（特征点数组），count（特征点数量），fileName（模板文件名）
	int SaveMinutiae(MINUTIAE *minutiaes, int count, char *fileName);

	//获得指纹编号
	int GetNewIndexInDB();
	//特征入库单步测试
	//userName（等级人姓名），info（返回操作成功或失败信息）
	int Step12_Enroll(char *userName, char *info);

	//宽字符串转换为多字节字符串
	char *ToChar(wchar_t *str);

	//指纹特征匹配 构建特征点相邻关系
	//minutiae（特征点数组），minuCount（特征点数量）
	int BuildNabors(MINUTIAE *minutiae, int minuCount);
	//计算线段倾斜度
	//x1(端点1横坐标)，y1(端点1纵坐标)，x2(端点2横坐标)，y2(端点2纵坐标)
	float Angle2Points(int x1, int y1, int x2, int y2);
	//特征匹配相似度计算
	//lWidth（图像宽度），lHeight(图像高度)，minutiae1（指纹一的特征点数组），count1（指纹一的特征点数量），minutiae2（指纹二的特征点数组），count2（指纹二的特征点数量）
	float MinuSimilarity(int lWidth, int lHeight, MINUTIAE *minutiae1, int count1, MINUTIAE *minutiae2, int count2);
	//读取特征模板文件
	int ReadMinutiae(char * fileName, MINUTIAE * * minutiae);
	//特征匹配单步测试
	//参数：info（返回操作成功或失败提示信息）
	int Step12_Match(char *info);
	//单步匹配
	afx_msg void OnBnClickedBtnStep12b();

	//指纹识别
	//指纹库预检（判断指纹库是否为空）
	bool EmptyDB();
	//指纹识别单步测试
	//参数：info（返回操作成功或失败提示信息）
	int Step12_Identify(char *info);
	//指纹识别单步测试，与特征匹配单步测试使用同一个按钮，语句也仅有一字之差

	//指纹登记过程集成
	//regName（登记人姓名），srcImgFile（源图文件名），outImgFile（识别结果图文件名），info（返回操作成功或失败提示信息），bSaveImg（是否保存所有中间结果图像）
	int Enroll(char *regName, char *srcImgFile, char *outImgFile, char *info, bool bSaveImg);
	//基于静态图像的指纹登记
	afx_msg void OnBnClickedBtnAddImage();

	//基于指纹采集器的指纹登记
	afx_msg void OnBnClickedBtnRegister();


	//识别过程集成
	int Identify(char *srcImgFile, char*outImgFile, char*info, bool bSaveImg);


	//特征入库
	afx_msg void OnBnClickedBtnStep12a();
	//基于静态图像的识别
	afx_msg void OnBnClickedBtnMatchImage();
	//基于采集器的识别
	afx_msg void OnBnClickedBtnIdentify();
};

