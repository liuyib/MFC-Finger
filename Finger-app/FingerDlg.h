
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

// CFingerDlg �Ի���
class CFingerDlg : public CDialogEx
{

	// ����
public:
	CFingerDlg(CWnd* pParent = NULL);	// ��׼���캯��

										// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FINGER_DIALOG };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
														// ʵ��
protected:
	HICON m_hIcon;
	CStatic m_staticInfo;
	CStatic m_picCtrl1;
	CStatic m_picCtrl2;
	CString m_name;//�Ǽ�������
	CZKFPEngX m_zkfpEng;
	int m_minuCount;
	// ���ɵ���Ϣӳ�亯��
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
	char* openImagePath();//�Զ�ѡ��ͼƬ
	char* saveImagePath();//�Զ�����·������
	wchar_t *ToWideChar(char *str);//���ֽ��ַ���ת��ΪUnicode���ַ���   
								   //ʵ����ͼ��ؼ�����ʾͼ��Ĺ��ܣ�
	int ShowImageInCtrl(CStatic &picCtrl, char * filename);
	afx_msg void OnBnClickedBtnCapture();
	int ReadBMPImageFilePara(CString filename, int &width, int &height, int &depth);
	int ReadBMPImgFileData(CString fileName, unsigned char *data);//��ȡλͼ����
																  //���ı��ļ���������(�޷����ַ�����)
	int SaveDataToTextFile(char * dstFile, unsigned char*data, int width, int height);
	//����������
	int SaveDataToTextFile(char *dstFile, float *data, int width, int height);
	int Step_LoadBmpImage(char * info);

	afx_msg void OnBnClickedBtnStep1();
	afx_msg void OnBnClickedBtnDatabase();
	//���ı��ļ���ȡ�޷����ַ����͵�ͼ��λͼ����
	int ReadDataFromTextFile(char *srcFile, unsigned char*data, int iWidth, int iHeight);
	//���ı��ļ���ȡ���������͵�ͼ��λͼ����
	int readDataFromTextFile(char*srcFile, float *data, int iWidth, int iHeight);
	//ʵ��ͼ����ֵ�˲��㷨
	int MidFilter(unsigned char*ucImg, unsigned char*ucDstImg, int iWidth, int iHeigh);
	//ʹ��ð����������������������
	void Sort(unsigned char* data, int dsize);
	//�������ݵ�BMPͼ���ļ�
	int SaveDataToImageFile(char *srcFile, char *dstFile, unsigned char * data);
	//scale:ת������
	int SaveDataToImageFile(char *srcFile, char * dstFile, float*data, float scale);

	int WriteBMPImgFile(char *dstFileName, unsigned char ** pusImgData);
	//��ֵ�˲���Ԫ����
	int Step2_MidFilter(char* info);
	afx_msg void OnBnClickedBtnStep2();
	int HistoNormalize(unsigned char*ucImg, unsigned char*ucNormlImg, int iWidth, int iHeight);//ֱ��ͼ���⻯�㷨
	int Step3_Normalize(char *info);
	afx_msg void OnBnClickedBtnStep3();
	int ImgDirection(unsigned char * ucImg, float *fDirc, int iWidth, int iHeight);//ָ�Ƽ���
	int DircLowPass(float *fDirc, float *fFitDirc, int iWidth, int iHeight);//���߷����ͨ�˲��㷨
	int Step4_Direction(char *info);
	afx_msg void OnBnClickedBtnStep4();
	//ָ�Ƽ���Ƶ�ʼ����㷨
	int Frequency(unsigned char* ucImg, float *fDirection, float *fFrequency, int iWidth, int iHeight);
	int Step5_Frequency(char *info);//ʵ��ָ�Ƽ���Ƶ�ʼ��㵥������

	afx_msg void OnBnClickedBtnStep5();//������
									   //ʵ��ָ���������
	int GetMask(unsigned char* ucImg, float *fDirection, float * fFrequency, unsigned char *ucMask, int iWidth, int iHeight);
	//ʵ��ָ��������㵥�����Թ���
	int Step6_Mask(char *info);
	afx_msg void OnBnClickedBtnStep6();
	//����ʵ��Gabor�˲���ǿ�㷨
	int GaborEnhance(unsigned char*ucImg, float*fDirection, float*fFrequency, unsigned char*ucMask, unsigned char*ucImgEnhanced, int iWidth, int iHeight);
	//ͼ��Gabor�˲���ǿ��������
	int Step7_GaborEnhance(char *info);

	afx_msg void OnBnClickedBtnStep7();

	//ͼ���ֵ���㷨
	int BinaryImg(unsigned char*ucImage, unsigned char*ucBinImage, int iWidth, int iHeight, unsigned char uThreshold);

	int BinaryToGray(unsigned char*ucBinImg, unsigned char*ucGrayImg, int iWidth, int iHeight);
	int Step8_Binary(char*info);
	afx_msg void OnBnClickedBtnStep8();
	//ͼ��ϸ��
	// ucBinedImg(Դͼ����)��ucThinnedImg�����ͼ���ݣ���lWidth��ͼ���ȣ���lHeight��ͼ��߶ȣ�
	int Thinning(unsigned char * ucBinedImg, unsigned char * ucThinnedImage, int lWidth, int lHeight, int lIterativeLimit);
	int Step9_Thinning(char *info);

	afx_msg void OnBnClickedBtnStep9();

	//ָ��������ȡ
	//ucThinImg(Դͼ����)��ucMinuImg�����ͼ���ݣ���lWidth��ͼ���ȣ���lHeight��ͼ��߶ȣ�
	int Extract(unsigned char * ucThinImg, unsigned char * ucMinuImg, int lWidth, int lHeight);
	// ������ȡ��������
	//������minuCount(��������������)��info�����ز����ɹ���ʧ����ʾ��Ϣ��
	int Step10_MinuExtract(int &minuCount, char *info);
	afx_msg void OnBnClickedBtnStep10();
	//��������
	// minuData(��������)��thinData��ϸ��ͼ���ݣ���minutiaes�����������飩��minuCount����������������lWidth��ͼ���ȣ���lHeight��ͼ��߶ȣ�
	int MinuFilter(unsigned char *minuData, unsigned char *thinData, MINUTIAE * minutiaes, int &minuCount, int lWidth, int lHeight);
	//ʵ�ֱ�Ե������ȥ������
	int CutEdge(MINUTIAE *minutiaes, int count, unsigned char * ucImg, int lWidth, int lHeight);
	//�������˵�������
	//minuCount����������������info�����ز����ɹ���ʧ����ʾ��Ϣ��
	int Step11_MinuFilter(int &minuCount, char *info);
	afx_msg void OnBnClickedBtnStep11();

	//��������ģ���ļ�
	//minutiaes�����������飩��count����������������fileName��ģ���ļ�����
	int SaveMinutiae(MINUTIAE *minutiaes, int count, char *fileName);

	//���ָ�Ʊ��
	int GetNewIndexInDB();
	//������ⵥ������
	//userName���ȼ�����������info�����ز����ɹ���ʧ����Ϣ��
	int Step12_Enroll(char *userName, char *info);

	//���ַ���ת��Ϊ���ֽ��ַ���
	char *ToChar(wchar_t *str);

	//ָ������ƥ�� �������������ڹ�ϵ
	//minutiae�����������飩��minuCount��������������
	int BuildNabors(MINUTIAE *minutiae, int minuCount);
	//�����߶���б��
	//x1(�˵�1������)��y1(�˵�1������)��x2(�˵�2������)��y2(�˵�2������)
	float Angle2Points(int x1, int y1, int x2, int y2);
	//����ƥ�����ƶȼ���
	//lWidth��ͼ���ȣ���lHeight(ͼ��߶�)��minutiae1��ָ��һ�����������飩��count1��ָ��һ����������������minutiae2��ָ�ƶ������������飩��count2��ָ�ƶ���������������
	float MinuSimilarity(int lWidth, int lHeight, MINUTIAE *minutiae1, int count1, MINUTIAE *minutiae2, int count2);
	//��ȡ����ģ���ļ�
	int ReadMinutiae(char * fileName, MINUTIAE * * minutiae);
	//����ƥ�䵥������
	//������info�����ز����ɹ���ʧ����ʾ��Ϣ��
	int Step12_Match(char *info);
	//����ƥ��
	afx_msg void OnBnClickedBtnStep12b();

	//ָ��ʶ��
	//ָ�ƿ�Ԥ�죨�ж�ָ�ƿ��Ƿ�Ϊ�գ�
	bool EmptyDB();
	//ָ��ʶ�𵥲�����
	//������info�����ز����ɹ���ʧ����ʾ��Ϣ��
	int Step12_Identify(char *info);
	//ָ��ʶ�𵥲����ԣ�������ƥ�䵥������ʹ��ͬһ����ť�����Ҳ����һ��֮��

	//ָ�ƵǼǹ��̼���
	//regName���Ǽ�����������srcImgFile��Դͼ�ļ�������outImgFile��ʶ����ͼ�ļ�������info�����ز����ɹ���ʧ����ʾ��Ϣ����bSaveImg���Ƿ񱣴������м���ͼ��
	int Enroll(char *regName, char *srcImgFile, char *outImgFile, char *info, bool bSaveImg);
	//���ھ�̬ͼ���ָ�ƵǼ�
	afx_msg void OnBnClickedBtnAddImage();

	//����ָ�Ʋɼ�����ָ�ƵǼ�
	afx_msg void OnBnClickedBtnRegister();


	//ʶ����̼���
	int Identify(char *srcImgFile, char*outImgFile, char*info, bool bSaveImg);


	//�������
	afx_msg void OnBnClickedBtnStep12a();
	//���ھ�̬ͼ���ʶ��
	afx_msg void OnBnClickedBtnMatchImage();
	//���ڲɼ�����ʶ��
	afx_msg void OnBnClickedBtnIdentify();
};

