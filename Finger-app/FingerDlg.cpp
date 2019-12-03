
// FingerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Finger.h"
#include "FingerDlg.h"
#include "afxdialogex.h"
#include "Login.h"
//语音
#include <sapi.h>
#include <sphelper.h>
#pragma comment(lib,sapi.lib) 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CFingerDlg 对话框
int liu = 0;
CFingerDlg::CFingerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FINGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	makebmp();
}

void CFingerDlg::DoDataExchange(CDataExchange* pDX)
{//主要用于确定系统界面中各控件ID和相应的控件变量的绑定对应关系。
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_INFO, m_staticInfo);
	DDX_Control(pDX, IDC_STATIC_IMG_1, m_picCtrl1);
	DDX_Control(pDX, IDC_STATIC_IMG_2, m_picCtrl2);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Control(pDX, IDC_ZKFPENGX, m_zkfpEng);
}

BEGIN_MESSAGE_MAP(CFingerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CFingerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CFingerDlg::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CFingerDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_DISCONNECT, &CFingerDlg::OnBnClickedBtnDisconnect)
	ON_BN_CLICKED(IDC_BTN_CAPTURE, &CFingerDlg::OnBnClickedBtnCapture)
	ON_BN_CLICKED(IDC_BTN_STEP_1, &CFingerDlg::OnBnClickedBtnStep1)
	ON_BN_CLICKED(IDC_BTN_DATABASE, &CFingerDlg::OnBnClickedBtnDatabase)
	ON_BN_CLICKED(IDC_BTN_STEP_2, &CFingerDlg::OnBnClickedBtnStep2)
	ON_BN_CLICKED(IDC_BTN_STEP_3, &CFingerDlg::OnBnClickedBtnStep3)
	ON_BN_CLICKED(IDC_BTN_STEP_4, &CFingerDlg::OnBnClickedBtnStep4)
	ON_BN_CLICKED(IDC_BTN_STEP_5, &CFingerDlg::OnBnClickedBtnStep5)
	ON_BN_CLICKED(IDC_BTN_STEP_6, &CFingerDlg::OnBnClickedBtnStep6)
	ON_BN_CLICKED(IDC_BTN_STEP_7, &CFingerDlg::OnBnClickedBtnStep7)
	ON_BN_CLICKED(IDC_BTN_STEP_8, &CFingerDlg::OnBnClickedBtnStep8)
	ON_BN_CLICKED(IDC_BTN_STEP_9, &CFingerDlg::OnBnClickedBtnStep9)
	ON_BN_CLICKED(IDC_BTN_STEP_10, &CFingerDlg::OnBnClickedBtnStep10)
	ON_BN_CLICKED(IDC_BTN_STEP_10, &CFingerDlg::OnBnClickedBtnStep10)
	ON_BN_CLICKED(IDC_BTN_STEP_11, &CFingerDlg::OnBnClickedBtnStep11)
	ON_BN_CLICKED(IDC_BTN_STEP_12B, &CFingerDlg::OnBnClickedBtnStep12b)
	ON_BN_CLICKED(IDC_BTN_ADD_IMAGE, &CFingerDlg::OnBnClickedBtnAddImage)
	ON_BN_CLICKED(IDC_BTN_IDENTIFY, &CFingerDlg::OnBnClickedBtnIdentify)
	ON_BN_CLICKED(IDC_BTN_REGISTER, &CFingerDlg::OnBnClickedBtnRegister)
	ON_BN_CLICKED(IDC_BTN_STEP_12A, &CFingerDlg::OnBnClickedBtnStep12a)
	ON_BN_CLICKED(IDC_BTN_MATCH_IMAGE, &CFingerDlg::OnBnClickedBtnMatchImage)
	ON_BN_CLICKED(IDC_BTN_IDENTIFY, &CFingerDlg::OnBnClickedBtnIdentify)
END_MESSAGE_MAP()
BEGIN_EVENTSINK_MAP(CFingerDlg, CDialog)
	ON_EVENT(CFingerDlg, IDC_ZKFPENGX, 8, OnImageReceivedZkfpengx, VTS_PBOOL)
END_EVENTSINK_MAP()

// CFingerDlg 消息处理程序

BOOL CFingerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

									// TODO: 在此添加额外的初始化代码

	CLogin m_login;//使登录窗口在主窗口之前运行	
	m_login.DoModal();

	CRgn rgnTmp;
	RECT rc;
	GetClientRect(&rc);
	rgnTmp.CreateRoundRectRgn(rc.left + 3, rc.top + 3, rc.right - rc.left - 3, rc.bottom - rc.top - 3, 6, 6);
	SetWindowRgn(rgnTmp, TRUE);
	InitDatabase();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFingerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFingerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CFingerDlg::OnImageReceivedZkfpengx(BOOL * AImageValid)
{//将指纹图像自适应显示在某一图像控件上
 //设置显示区域
 //CRect rect;//定义矩形对象
 //m_picCtrl1.GetClientRect(&rect);//获得pictrue控件所在的矩形区域
 //CDC *pDc = m_picCtrl1.GetWindowDC();//获得picture控件的设置环境句柄
 //SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);//设置位图拉伸模式
 //显示图像
 //image.StretchBlt(pDc->m_hDC, rect, SRCCOPY);//将图像画到picture控件表示的矩形区域
 //更新控件显示
 //m_picCtrl1.Invalidate(false);//更新控件显
 //释放变量空间
 //image.Destroy();
 //m_picCtrl1.ReleaseDC(pDc);//释放picture控件的设置环境句柄
	HDC hdc = this->GetDC()->m_hDC;//获得显示设备上下文环境的句柄
	int x = 170;//图像绘制区左上角横坐标
	int y = 80;//图像绘制区左上角纵坐标
	int width = m_zkfpEng.get_ImageWidth();//图像绘制区的宽度
	int height = m_zkfpEng.get_ImageHeight();//图像绘制区的高度
											 //makebmp();
	ShowImageInCtrl(m_picCtrl1, "empty.bmp");
	ShowImageInCtrl(m_picCtrl2, "empty.bmp");//清空图片
	m_zkfpEng.PrintImageAt(int(hdc), x, y, width - 10, height);//绘制图像。
															   //m_staticInfo.SetWindowText(ToWideChar(""));//清空字；



}

void CFingerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

void CFingerDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CFingerDlg::OnBnClickedBtnExit()
{
	// TODO: Add your control notification handler code here
	OnOK();//关闭当前对话框（系统界面）
}

void CFingerDlg::OnBnClickedBtnConnect()
{
	// TODO: Add your control notification handler code here
	int z = 2;
	z = m_zkfpEng.InitEngine();//启动指纹采集器；
	if (z == 0) {

		//MessageBox(_T("采集器连接成功."), _T("提示"));//显示信息
		MessageBox(L"采集器连接成功");
		GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(FALSE);//点击启动后，启动按钮变灰；
		GetDlgItem(IDC_BTN_DISCONNECT)->EnableWindow(FALSE);//关闭按钮变亮
		liu = 1;
		//GetDlgItem(IDD_FINGER_DIALOG)->EnableWindow(TRUE);
	}
	else if (z == 1) {
		//MessageBox(_T("指纹识别驱动程序加载失败."), _T("提示"));//显示信息 
		MessageBox(L"指纹识别驱动程序加载失败");
	}
	else if (z == 2) {
		//MessageBox(_T("没有连接指纹识别器."), _T("提示"));//显示信息 
		MessageBox(L"没有连接指纹识别器");
	}

}

void CFingerDlg::OnBnClickedBtnDisconnect()
{
	liu = 0;
	m_zkfpEng.EndEngine();//停止指纹采集器；
	GetDlgItem(IDC_BTN_DISCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(true);//启动变亮
}

char* CFingerDlg::openImagePath()
{
	//char *srcImgFile = NULL;
	BOOL isOpen = TRUE;//为TRUE则显示打开文件对话框，为FALSE则显示保存文件对话框
	CString defaulDir = L"D:\\fingerimages";//默认打开的文件路径
	CString fileName = L"L01_01.bmp";//默认打开的文件名
	CString filter = L"文件（*.bmp;*.png;*.jpeg）|*.bmp;*.png;*.jpeg||";//文件过滤的类型；
	CFileDialog openFileDlg(isOpen, defaulDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"D:\\fingerimages\\L01_01.bmp";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaulDir + "\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}
	//复制图像
	char *srcImgFile = new char[filePath.GetLength() + 1];
	LPCTSTR p = filePath.GetBuffer(0);
	filePath.ReleaseBuffer();
	strcpy_s(srcImgFile, filePath.GetLength() + 1, CT2CA(p));
	return srcImgFile;
}

char* CFingerDlg::saveImagePath()
{
	//char * srcImgFile = NULL;
	BOOL isOpen = FALSE;//为TRUE则显示打开文件对话框，为FALSE则显示保存文件对话框
	CString defaulDir = L"D:\\fingerimages";//默认打开的文件路径
	CString fileName = L"L01_01.bmp";//默认打开的文件名
	CString filter = L"文件（*.bmp;*.png;*.jpeg）|*.bmp;*.png;*.jpeg||";//文件过滤的类型；
	CFileDialog openFileDlg(isOpen, defaulDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"D:\\fingerimages\\L01_01.bmp";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaulDir + "\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}
	//复制图像
	char *srcImgFile = new char[filePath.GetLength() + 1];
	LPCTSTR p = filePath.GetBuffer(0);
	filePath.ReleaseBuffer();
	strcpy_s(srcImgFile, filePath.GetLength() + 1, CT2CA(p));
	return srcImgFile;

}

wchar_t * CFingerDlg::ToWideChar(char * str)
{
	int num = MultiByteToWideChar(0, 0, str, -1, NULL, 0);
	wchar_t *wideStr = new wchar_t[num];
	MultiByteToWideChar(0, 0, str, -1, wideStr, num);
	return wideStr;
}

int CFingerDlg::ShowImageInCtrl(CStatic & picCtrl, char * filename)
{
	//清空系统界面上原先显示的图像文字
	//HDC hdc = this->GetDC()->m_hDC;//获得显示设备上下文环境的句柄
	//int x = 160;//图像绘制区左上角横坐标
	//int y = 80;//图像绘制区左上角纵坐标
	//m_zkfpEng.PrintImageAt(int(hdc), x, y, 0, 0);//绘制图像。//没实现
	//载入图像
	CImage image;
	HRESULT hResult = image.Load(ToWideChar(filename));
	int width = image.GetWidth();//图像宽度
	int height = image.GetHeight();//图像高度
								   //设置显示区域
	CRect rect;//定义矩形对象
	picCtrl.GetClientRect(&rect);//获得pictrue控件所在的矩形区域
	CDC *pDc = picCtrl.GetWindowDC();//获得picture控件的设置环境句柄
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);//设置位图拉伸模式
													//显示图像
	image.StretchBlt(pDc->m_hDC, rect, SRCCOPY);//将图像画到picture控件表示的矩形区域
												//更新控件显示
	picCtrl.Invalidate(false);//更新控件显示
							  //释放变量空间
	image.Destroy();
	picCtrl.ReleaseDC(pDc);//释放picture控件的设置环境句柄


	return 0;
}


void CFingerDlg::OnBnClickedBtnCapture()
{
	// TODO: Add your control notification handler code here
	//采集图像（保存指纹图像）
	BOOL isOpen = FALSE;
	CString defaulDir = L"D:\\fingerimages";//默认打开的文件路径
	CString fileName = L"L01_01.bmp";//默认打开的文件名
	CString filter = L"文件（*.bmp;*.png;*.jpeg）|*.bmp;*.png;*.jpeg||";//文件过滤的类型；
	CFileDialog openFileDlg(isOpen, defaulDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"D:\\fingerimages\\L01_01.bmp";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaulDir + "\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}
	//指定名称，指定路径
	m_zkfpEng.SaveBitmap(filePath);
}

int CFingerDlg::ReadBMPImageFilePara(CString fileName, int & width, int & height, int & depth)
{//获取图像参数信息
	CImage image;
	HRESULT hResult = image.Load(fileName);
	if (FAILED(hResult) || image.IsNull()) {
		//MessageBox(_T("该文件为空"), _T("提示"));//显示信息
		MessageBox(L"该文件为空");
		return -1;
	}
	//获得图像参数
	width = image.GetWidth();
	height = image.GetHeight();
	depth = image.GetBPP();
	if (depth != 8) {
		return -2;
	}
	image.Destroy();

	return 0;
}

int CFingerDlg::ReadBMPImgFileData(CString filename, unsigned char * data)
{//获取图像位图数据
 //载入图像
	CImage image;
	HRESULT hResult = image.Load(filename);
	if (FAILED(hResult) || image.IsNull()) {
		return -1;
	}

	//获得图像参数
	int width = image.GetWidth();
	int height = image.GetHeight();
	int depth = image.GetBPP();//获得以bit为单位的图像深度（每个像素的位数）
	if (depth != 8) {//目前系统仅支持8位？？？
		return -2;
	}
	//初始化结果数组
	memset(data, 0, width*height);
	//读取图像数据

	int pitch = image.GetPitch();
	unsigned char * pDatal = (unsigned char *)image.GetBits();
	unsigned char * pData2 = data;
	unsigned gray = 0;
	unsigned char * pRow1, *pRow2, *pPix1, *pPix2;
	//逐行逐列扫描(按像素来)
	for (int y = 0; y < height; y++) {
		pRow1 = pDatal + pitch*y;
		pRow2 = pData2 + width * y;
		for (int x = 0; x < width; x++) {
			pPix1 = pRow1 + x;
			gray = *pPix1;
			pPix2 = pRow2 + x;
			*pPix2 = gray;
		}
	}
	image.Destroy();


	return 0;
}

int CFingerDlg::SaveDataToTextFile(char * dstFile, unsigned char * data, int width, int height)
{//保存数据
	ofstream fout(dstFile, ios::out);//使用覆盖写入方法
	if (!fout) {
		return -1;
	}
	//按指定格式向文件写入数据
	int space = 5;
	for (int i = 0; i < height * width; i++) {
		fout << setw(space) << int(data[i]);//等宽写入数据
		if (i%width == (width - 1)) {
			fout << endl;
		}
	}
	fout.close();

	return 0;
}

int CFingerDlg::SaveDataToTextFile(char * dstFile, float * data, int width, int height)
{
	ofstream fout(dstFile, ios::out);//
	if (!fout) {
		return -1;
	}
	int preci = 6;
	int space = 16;
	fout.precision(preci);
	for (int i = 0; i < height*width; i++) {
		fout << " " << setw(space) << data[i];//等宽写入数据
		if (i % width == (width - 1)) {
			fout << endl;
		}
	}

	fout.close();

	return 0;
}

int CFingerDlg::Step_LoadBmpImage(char * info)
{//载入指纹图像
 //选择图像***********************修改代码（由用户动态选择和指定指纹图像）

	BOOL isOpen = TRUE;//为TRUE则显示打开文件对话框，为FALSE则显示保存文件对话框
	CString defaulDir = L"D:\\fingerimages";//默认打开的文件路径
	CString fileName = L"L01_01.bmp";//默认打开的文件名
	CString filter = L"文件（*.bmp;*.png;*.jpeg）|*.bmp;*.png;*.jpeg||";//文件过滤的类型；
	CFileDialog openFileDlg(isOpen, defaulDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"D:\\fingerimages\\L01_01.bmp";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaulDir + "\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}
	//char filename[MAX_PATH] = filePath;
	//复制图像
	CopyFile(filePath, ToWideChar(STEP_IMG_1), false);
	//读取图像参数并检测有效性
	int iWidth, iHeight, iDepth;
	int flag = ReadBMPImageFilePara(filePath, iWidth, iHeight, iDepth);
	if (flag != 0) {
		sprintf(info, "图像失败.");
		MessageBox(L"图像失败");
		return -1;
	}
	//读取图像数据
	unsigned char *data = new unsigned char[iWidth*iHeight];
	flag = ReadBMPImgFileData(filePath, data);
	if (flag != 0) {
		sprintf(info, "图像数据读取失败");
		MessageBox(L"图像数据读取失败");
		delete[] data;//释放内存
		return -2;
	}

	//保存数据
	flag = SaveDataToTextFile(STEP_TXT_1, data, iWidth, iHeight);
	if (flag != 0) {
		sprintf(info, "数据保存失败");
		MessageBox(L"数据保存失败");
		delete[] data;
		return -3;
	}
	//返回图像参数信息

	sprintf(info, "宽度[%d],高度[%d],深度[%d]", iWidth, iHeight, iDepth);
	delete[] data;

	return 0;
}


void CFingerDlg::OnBnClickedBtnStep1()
{//载入图像
 // TODO: Add your control notification handler code here
 //初始化操作结果信息
	char info[MAX_PATH] = { 0 };
	//载入图像
	Step_LoadBmpImage(info);
	//显示操作结果信息
	m_staticInfo.SetWindowText(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_1);
}

//创建空白图片
void makebmp()
{
	int nSize = abs(long(240 * WIDTHBYTES(24 * 320)));
	char*  buff = new char[nSize];
	memset(buff, 255, nSize);

	BITMAPINFOHEADER header;
	header.biSize = sizeof(BITMAPINFOHEADER);

	header.biWidth = 32;
	header.biHeight = 32 * (-1);
	header.biBitCount = 24;
	header.biCompression = 0;
	header.biSizeImage = 0;
	header.biClrImportant = 0;
	header.biClrUsed = 0;
	header.biXPelsPerMeter = 0;
	header.biYPelsPerMeter = 0;
	header.biPlanes = 1;


	//3 构造文件
	BITMAPFILEHEADER bmpFileHeader;
	HANDLE hFile = NULL;
	DWORD dwTotalWriten = 0;
	DWORD dwWriten;


	bmpFileHeader.bfType = 0x4d42; //'BM';
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + nSize;


	FILE* pf = fopen("empty.bmp", "wb");
	fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, pf);
	fwrite(&header, sizeof(BITMAPINFOHEADER), 1, pf);
	fwrite(buff, 1, nSize, pf);
	fclose(pf);
	delete buff;
}
void InitDatabase()
{
	_mkdir(TEMP_DIR);//创建临时文件夹
	_mkdir(DB_DIR);//创建指纹库文件夹
	InitFile(DB_INDEX_TXT);//创建索引文件
}

void InitFile(char * filename)
{
	FILE *index = fopen(filename, "w");//若文件不存在则创建，若已存在则清空其内容
	fclose(index);//关闭文件
}


void GetDatabaseInfo(char * info)
{
	//遍历指纹库
	int pNo = 0;//指纹序号
	char name[MAX_PATH] = { 0 };//登记人姓名
	char srcFile[MAX_PATH] = { 0 };//指纹图像文件
	char mdlFile[MAX_PATH] = { 0 };//指纹特征文件
	FILE *index = fopen(DB_INDEX_TXT, "r");//打开索引文件
	while (!feof(index))
	{
		fscanf(index, "%d %s %s %s\n", &pNo, srcFile, mdlFile, name);
	}
	fclose(index);//关闭文件

				  //统计指纹库信息
	string s = "当前指纹库中共有" + to_string(pNo) + "条记录";
	CString cs(s.c_str());
	//MessageBox(cs);
	sprintf(info, "当前指纹库中共有%d条记录", pNo);

}

void CFingerDlg::OnBnClickedBtnDatabase()
{//指纹库信息按钮
 // TODO: Add your control notification handler code here
	char info[MAX_PATH] = { 0 };//初始化显示信息
								//获取指纹库信息
	GetDatabaseInfo(info);//获取指纹库信息
	m_staticInfo.SetWindowText(ToWideChar(info));//显示指纹库信息；
}

int CFingerDlg::ReadDataFromTextFile(char * srcFile, unsigned char * data, int iWidth, int iHeight)
{
	//打开原文件
	ifstream fin(srcFile, ios::in);
	if (!fin) {
		return -1;
	}
	//读取数据
	int d = 0;
	for (int i = 0; i < iHeight*iWidth; i++) {
		fin >> d;
		data[i] = (unsigned char)d;
	}
	//关闭文件
	fin.close();
	return 0;
}

int CFingerDlg::readDataFromTextFile(char * srcFile, float * data, int iWidth, int iHeight)
{
	//打开源文件
	ifstream fin(srcFile, ios::in);
	if (!fin) {
		return -1;
	}
	//读取数据

	for (int i = 0; i < iHeight*iWidth; i++) {
		fin >> data[i];
	}
	//关闭文件
	fin.close();


	return 0;
}

int CFingerDlg::MidFilter(unsigned char * ucImg, unsigned char * ucDstImg, int iWidth, int iHeight)
{
	//结果图像数据初始化
	memset(ucDstImg, 0, iWidth*iHeight);
	//中心区域滤波（使用3*3邻域）
	unsigned char*pUp, *pDown, *pImg;//用来确定3*3邻域的3个图像数据指针（下文简称“邻域指针”）
	unsigned char x[9];//3*3邻域图像数据数组
	for (int i = 1; i < iHeight - 1; i++) {//遍历第二行到倒数第二行
										   //初始化邻域指针
		pUp = ucImg + (i - 1)*iWidth;
		pImg = ucImg + i*iWidth;
		pDown = ucImg + (i + 1)*iWidth;
		for (int j = 1; j < iWidth - 1; j++) {//遍历第二列到倒数第二列
											  //移动邻域指针
			pUp++;
			pImg++;
			pDown++;
			//获取3*3邻域指针
			x[0] = *(pUp - 1);
			x[1] = *(pImg - 1);
			x[2] = *(pDown - 1);

			x[3] = *pUp;
			x[4] = *pImg;
			x[5] = *pDown;

			x[6] = *(pUp + 1);
			x[7] = *(pImg + 1);
			x[8] = *(pDown + 1);

			//数组排序
			Sort(x, 9);

			//结果图像数据取邻域中值
			*(ucDstImg + i*iWidth + j) = x[4];
		}
	}
	//第一行和最后一行滤波（使用2*3邻域）
	pDown = ucImg + iWidth;
	for (int j = 1; j < iWidth - 1; j++) {
		//获取2*3邻域数据
		x[0] = *(ucImg + j - 1);
		x[1] = *(ucImg + j);
		x[2] = *(ucImg + j + 1);

		x[3] = *(pDown + j - 1);
		x[4] = *(pDown + j);
		x[5] = *(pDown + j + 1);

		//数组排序
		Sort(x, 6);
		//结果取中值
		*(ucDstImg + j) = x[3];
	}
	//最后一行
	pUp = ucImg + iWidth*(iHeight - 2);
	pDown = ucImg + iWidth *(iHeight - 1);
	for (int j = 1; j < iWidth - 1; j++) {
		//获取2*3邻域数据
		x[0] = *(pDown + j - 1);
		x[1] = *(pDown + j);
		x[2] = *(pDown + j + 1);
		x[3] = *(pUp + j - 1);
		x[4] = *(pUp + j);
		x[5] = *(pUp + j + 1);

		//数组排序
		Sort(x, 6);
		*(ucDstImg + iWidth*(iHeight - 1) + j) = x[3];
	}

	//step4:4个角点滤波（使用2*2邻域）
	//左上角点
	x[0] = *(ucImg);//获取2*2邻域
	x[1] = *(ucImg + 1);
	x[2] = *(ucImg + iWidth);
	x[3] = *(ucImg + iWidth + 1);
	Sort(x, 4);
	*(ucDstImg) = x[2];//结果取中值

					   //右上角点
	x[0] = *(ucImg + iWidth - 1);
	x[1] = *(ucImg + iWidth - 2);
	x[2] = *(ucImg + 2 * iWidth - 1);
	x[3] = *(ucImg + 2 * iWidth - 2);
	Sort(x, 4);
	*(ucDstImg + iWidth - 1) = x[2];


	//左下角点
	x[0] = *(ucImg + (iHeight - 1)*iWidth);//获取2*2邻域数据
	x[1] = *(ucImg + (iHeight - 2)*iWidth);
	x[2] = *(ucImg + (iHeight - 1)*iWidth + 1);
	x[3] = *(ucImg + (iHeight - 2)*iWidth + 1);
	*(ucDstImg + (iHeight - 1)*iWidth) = x[2];

	//右下角点
	x[0] = *(ucImg + (iHeight - 0)*iWidth - 1);
	x[1] = *(ucImg + (iHeight - 1)*iWidth - 1);
	x[2] = *(ucImg + (iHeight - 0)*iWidth - 2);
	x[3] = *(ucImg + (iHeight - 1)*iWidth - 2);
	Sort(x, 4);
	*(ucDstImg + (iHeight - 0)*iWidth - 1) = x[2];

	return 0;
}

void CFingerDlg::Sort(unsigned char * data, int dsize)
{
	unsigned char temp = 0;
	for (int i = 0; i < dsize; i++) {
		for (int j = dsize - 1; j > i; j--) {
			if (data[j] < data[j - 1]) {
				temp = data[i];
				data[i] = data[j - 1];
				data[j - 1] = temp;
			}
		}
	}
}

int CFingerDlg::SaveDataToImageFile(char * srcFile, char * dstFile, unsigned char * data)
{
	CopyFile(ToWideChar(srcFile), ToWideChar(dstFile), false);
	//写入数据
	WriteBMPImgFile(dstFile, &data);

	return 0;
}

int CFingerDlg::SaveDataToImageFile(char * srcFile, char * dstFile, float * data, float scale)
{
	//读取图像参数
	int iWidth, iHeight, iDepth;
	ReadBMPImageFilePara((CString)srcFile, iWidth, iHeight, iDepth);
	//文件复制
	CopyFile(ToWideChar(srcFile), ToWideChar(dstFile), false);
	//数据转换
	unsigned char *tmpData = new unsigned char[iWidth*iHeight];
	for (int i = 0; i < int(iWidth*iHeight); i++) {
		tmpData[i] = unsigned char((scale * data[i]));
	}

	//写入数据
	WriteBMPImgFile(dstFile, &tmpData);
	//释放内存空间
	delete[] tmpData;

	return 0;
}

int CFingerDlg::WriteBMPImgFile(char * dstFileName, unsigned char ** pusImgData)
{
	FILE *fp = fopen(dstFileName, "r+b");
	if (!fp) {
		return -1;
	}
	//读取图像参数信息
	int imgType, iWidth, iHeight;
	int iStartPos = 0;//位图数据区起始地址
	fseek(fp, 10L, SEEK_SET);
	fread((char*)(&iStartPos), 4, 1, fp);
	fseek(fp, 18L, SEEK_SET);
	fread((char*)(&iWidth), 4, 1, fp);
	fread((char*)(&iHeight), 4, 1, fp);
	unsigned short temp;
	fseek(fp, 28L, SEEK_SET);
	fread((char *)(&temp), 2, 1, fp);
	imgType = temp;
	if (imgType != 8) {
		return -2;
	}

	//向数据区写入数据
	unsigned char * usImgData = *pusImgData;//待保存数据数组地址
	int iWidthInFile = 0;
	if (iWidth % 4 > 0) {
		iWidthInFile = iWidth - iWidth % 4 + 4;
	}
	else
	{
		iWidthInFile = iWidth;
	}

	for (int i = iHeight - 1; i >= 0; i--) {//倒序存储
		fseek(fp, iStartPos, SEEK_SET);//定位行首地址
		fwrite((usImgData + i*iWidth), 1, iWidth, fp);//写入一行数据
		iStartPos += iWidthInFile;//调整行首地址
	}

	//关闭文件
	fclose(fp);

	return 0;
}

int CFingerDlg::Step2_MidFilter(char * info)
{
	//设置输入输出文件名
	char srcTxtFile[MAX_PATH] = { STEP_TXT_1 };//原数据文件名
	char srcImgFile[MAX_PATH] = { STEP_IMG_1 };//源图文件名
	char dstTxtFile[MAX_PATH] = { STEP_TXT_2 };//结果
	char dstImgFile[MAX_PATH] = { STEP_IMG_2 };
	//读取图像参数
	int iWidth, iHeight, iDepth;
	ReadBMPImageFilePara((CString)srcImgFile, iWidth, iHeight, iDepth);//??????????不知道可不可以
																	   //读取源数据
	unsigned char*image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile, image1, iWidth, iHeight);

	//中值滤波

	unsigned char*image2 = new unsigned char[iWidth*iHeight];
	MidFilter(image1, image2, iWidth, iHeight);

	//保存结果数据(TXT文件)
	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);
	//保存结果图像（BMP文件，仅用于显示）
	SaveDataToImageFile(srcImgFile, dstImgFile, image2);

	//释放内存空间

	delete[] image1;
	delete[] image2;

	sprintf(info, "完成中值滤波");
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep2()//中值滤波单击响应事件
{
	//初始化操作结果信息
	char info[MAX_PATH] = { 0 };

	//中值滤波
	Step2_MidFilter(info);
	//显示操作结果信息
	m_staticInfo.SetWindowTextW(ToWideChar(info));//??????????
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_1);//显示输入图像
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_2);//显示输出图像。
}

int CFingerDlg::HistoNormalize(unsigned char * ucImg, unsigned char * ucNormlImg, int iWidth, int iHeight)
{
	//构建源图灰度直方图
	unsigned int Histogram[256];
	memset(Histogram, 0, 256 * sizeof(int));
	for (int i = 0; i < iHeight; i++) {
		for (int j = 0; j < iWidth; j++) {
			Histogram[ucImg[i*iWidth + j]]++;
		}
	}

	//计算源图的灰度均值和方差
	double dMean = 0;
	for (int i = 1; i < 255; i++) {
		dMean += i * Histogram[i];
	}

	dMean = int(dMean / (iWidth*iHeight));
	double dSigma = 0;
	for (int i = 0; i < 255; i++) {
		dSigma += Histogram[i] * (i - dMean)*(i - dMean);
	}
	dSigma /= (iWidth * iHeight);
	dSigma = sqrt(dSigma);
	//对各像素进行均衡化操作
	double dMean0 = 128, dSigma0 = 128;//预设灰度均值和方差（此处均设128）
	double dCoeff = dSigma0 / dSigma;//转换系数
	for (int i = 0; i < iHeight; i++) {
		for (int j = 0; j < iWidth; j++) {
			double dVal = ucImg[i*iWidth + j];
			dVal = dMean0 + dCoeff*(dVal - dMean0);
			if (dVal < 0) {
				dVal = 0;
			}
			else if (dVal > 255)
			{
				dVal = 255;
			}
			ucNormlImg[i*iWidth + j] = (unsigned char)dVal;
		}
	}
	return 0;
}

int CFingerDlg::Step3_Normalize(char * info)
{
	//设置输入输出文件名
	char srcTxtFile[MAX_PATH] = { STEP_TXT_2 };//源
	char srcImgFile[MAX_PATH] = { STEP_IMG_2 };
	char dstTxtFile[MAX_PATH] = { STEP_TXT_3 };//结果
	char dstImgFile[MAX_PATH] = { STEP_IMG_3 };

	//读取图像参数
	int iWidth, iHeight, iDepth;//图像宽度高度深度
	ReadBMPImageFilePara((CString)srcImgFile, iWidth, iHeight, iDepth);
	//读取源数据
	unsigned char*image1 = new unsigned char[iWidth * iHeight];
	ReadDataFromTextFile(srcTxtFile, image1, iWidth, iHeight);
	//直方图均衡化
	unsigned char * image2 = new unsigned char[iWidth*iHeight];
	HistoNormalize(image1, image2, iWidth, iHeight);
	//保存结果数据（TXT文件）
	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);
	//保存结果图像（BMP文件，仅用于显示）
	SaveDataToImageFile(srcImgFile, dstImgFile, image2);

	//释放空间
	delete[] image1;
	delete[] image2;

	//MessageBox(L"完成直方图均衡化");
	sprintf(info, "完成直方图均衡化");

	return 0;
}
//直方图均衡化
void CFingerDlg::OnBnClickedBtnStep3()
{
	//初始化操作结果信息
	char info[MAX_PATH] = { 0 };
	Step3_Normalize(info);
	m_staticInfo.SetWindowTextW(ToWideChar(info));

	ShowImageInCtrl(m_picCtrl1, STEP_IMG_2);//显示输入图像
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_3);
}

int CFingerDlg::ImgDirection(unsigned char * ucImg, float * fDirc, int iWidth, int iHeight)
{
	const int SEMISIZ = 7;//领域窗口区域半径
	int dx[SEMISIZ * 2 + 1][SEMISIZ * 2 + 1];
	int dy[SEMISIZ * 2 + 1][SEMISIZ * 2 + 1];
	float fx, fy;
	//结果初始化
	memset(fDirc, 0, iWidth*iHeight * sizeof(float));
	for (int y = SEMISIZ + 1; y < iHeight - SEMISIZ - 1; y++) {//逐行遍历（除去边缘）
		for (int x = SEMISIZ + 1; x < iWidth - SEMISIZ - 1; x++) {
			//逐列遍历（除去边缘）
			for (int j = 0; j < SEMISIZ * 2 + 1; j++) {
				for (int i = 0; i < SEMISIZ * 2 + 1; i++) {
					int index1 = (y + j - SEMISIZ)*iWidth + x + i - SEMISIZ;
					int index2 = (y + j - SEMISIZ)*iWidth + x + i - SEMISIZ - 1;
					int index3 = (y + j - SEMISIZ - 1)*iWidth + x + i - SEMISIZ;
					dx[i][j] = int(ucImg[index1] - ucImg[index2]);
					dx[i][j] = int(ucImg[index1] - ucImg[index3]);
				}
			}

			//计算当前像素的脊线方向值
			fx = 0.0;
			fy = 0.0;
			for (int j = 0; j < SEMISIZ * 2 + 1; j++) {
				for (int i = 0; i < SEMISIZ * 2 + 1; i++) {
					fx += 2 * dx[i][j] * dy[i][j];
					fy += (dx[i][j] * dx[i][j] - dy[i][j] * dy[i][j]);
				}
			}

			fDirc[y*iWidth + x] = atan2(fx, fy);
		}
	}
	return 0;
}

int CFingerDlg::DircLowPass(float * fDirc, float * fFitDirc, int iWidth, int iHeight)
{//定义变量
	const int DIR_FILTER_SIZE = 2;
	int blocksize = 2 * DIR_FILTER_SIZE + 1;
	int imgsize = iWidth * iHeight;
	float *filter = new float[blocksize*blocksize];//使用5*5滤波器
	float *phix = new float[imgsize];
	float *phiy = new float[imgsize];
	float *phi2x = new float[imgsize];
	float *phi2y = new float[imgsize];
	memset(fFitDirc, 0, sizeof(float)*iWidth*iHeight);
	//设置5*5高斯低通滤波器模板

	float tempSum = 0.0;
	for (int y = 0; y < blocksize; y++) {
		for (int x = 0; x < blocksize; x++) {
			filter[y*blocksize + x] = (float)(blocksize - (abs(DIR_FILTER_SIZE - x) + abs(DIR_FILTER_SIZE - y)));
			tempSum += filter[y*blocksize + x];
		}
	}
	for (int y = 0; y < blocksize; y++) {
		for (int x = 0; x < blocksize; x++) {
			filter[y*blocksize + x] /= tempSum;
		}
	}

	//计算各像素点的方向正弦值和余弦值
	for (int y = 0; y < iHeight; y++)
	{
		for (int x = 0; x < iWidth; x++) {
			phix[y*iWidth + x] = cos(fDirc[y*iWidth + x]);
			phiy[y*iWidth + x] = sin(fDirc[y*iWidth + x]);
		}

	}

	//对所有像素进行方向低通滤波
	memset(phi2x, 0, sizeof(float)*imgsize);
	memset(phi2y, 0, sizeof(float)*imgsize);
	float nx, ny;
	int val;
	for (int y = 0; y < iHeight - blocksize; y++) {
		for (int x = 0; x < iWidth - blocksize; x++) {
			nx = 0.0;
			ny = 0.0;
			for (int j = 0; j < blocksize; j++) {
				for (int i = 0; i < blocksize; i++) {
					val = (x + i) + (j + y)*iWidth;
					nx += filter[j*blocksize + i] * phix[val];
					ny += filter[j*blocksize + i] * phiy[val];
				}
			}

			//将累加结果作为当前像素的新的方向正弦值和余弦值
			val = x + y*iWidth;
			phi2x[val] = nx;
			phi2y[val] = ny;
		}
	}

	for (int y = 0; y < iHeight - blocksize; y++) {
		for (int x = 0; x < iWidth - blocksize; x++) {
			val = x + y*iWidth;
			fFitDirc[val] = atan2(phi2y[val], phi2x[val])*0.5;
		}
	}

	delete[] phi2x;
	delete[] phi2y;
	delete[] phiy;
	delete[] phix;
	return 0;
}

int CFingerDlg::Step4_Direction(char * info)
{
	char srcTxtFile[MAX_PATH] = { STEP_TXT_3 };
	char srcImgFile[MAX_PATH] = { STEP_IMG_3 };
	char dstTxtFile[MAX_PATH] = { STEP_TXT_4 };
	char dstImgFile[MAX_PATH] = { STEP_IMG_4 };

	//读取图像参数
	int iWidth, iHeight, iDepth;
	ReadBMPImageFilePara((CString)srcImgFile, iWidth, iHeight, iDepth);
	//读取源数据
	unsigned char*image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile, image1, iWidth, iHeight);
	//方向计算
	float *tmpDirections = new float[iWidth*iHeight];
	ImgDirection(image1, tmpDirections, iWidth, iHeight);
	//方向低通滤波
	float *directions = new float[iWidth*iHeight];
	DircLowPass(tmpDirections, directions, iWidth, iHeight);
	//保存结果数据
	SaveDataToTextFile(dstTxtFile, directions, iWidth, iHeight);
	//保存结果图像（BMP文件，仅用于显示）
	const int DIRECTION_SCALE = 100;
	SaveDataToImageFile(srcImgFile, dstImgFile, directions, DIRECTION_SCALE);

	delete[] image1;
	delete[] tmpDirections;
	delete[] directions;

	sprintf(info, "完成方向计算");
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep4()
{//方向计算

	char info[MAX_PATH] = { 0 };
	//指纹脊线方向计算；
	Step4_Direction(info);
	m_staticInfo.SetWindowTextW(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_3);
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_4);
}

int CFingerDlg::Frequency(unsigned char * ucImg, float * fDirection, float * fFrequency, int iWidth, int iHeight)
{
	//窗口大小
	const int SIZE_L = 32;
	const int SIZE_W = 16;
	const int SIZE_L2 = 16;
	const int SIZE_W2 = 8;
	//正弦波峰值点
	int peak_pos[SIZE_L];
	int peak_cnt;
	float peak_freq;
	float Xsig[SIZE_L];
	//方向
	float dir = 0.0;
	float cosdir = 0.0;
	float sindir = 0.0;
	float maxPeak, minPeak;
	//结果初始化
	float *frequency1 = new float[iWidth * iHeight];
	memset(fFrequency, 0, sizeof(float)*iWidth*iHeight);
	memset(frequency1, 0, sizeof(float)*iWidth*iHeight);
	int x, y;
	int d, k;
	int u, v;
	for (y = SIZE_L2; y < iHeight - SIZE_L2; y++) {
		for (x = SIZE_L2; x < iWidth - SIZE_L2; x++) {
			//当前像素的脊线方向
			dir = fDirection[(y + SIZE_W2)*iWidth + (x + SIZE_W2)];
			cosdir = -sin(dir);
			sindir = cos(dir);
			//计算以当前像素为中心的L*W邻域窗口的幅值序列
			for (k = 0; k < SIZE_L; k++) {
				Xsig[k] = 0.0;
				for (d = 0; d < SIZE_W; d++) {
					u = (int)(x + (d - SIZE_W2)*cosdir + (k - SIZE_L2)*sindir);
					v = (int)(y + (d - SIZE_W2)*sindir + (k - SIZE_L2)*cosdir);
					//边界点处理
					if (u < 0) {
						u = 0;
					}
					else if (u > iWidth - 1) {
						u = iWidth - 1;
					}
					if (v < 0) {
						v = 0;
					}
					else if (v > iHeight - 1)
					{
						v = iHeight - 1;
					}
					Xsig[k] += ucImg[u + v*iWidth];
				}
				Xsig[k] /= SIZE_W;
			}

			//确定幅值序列变化范围
			maxPeak = minPeak = Xsig[0];
			for (k = 0; k < SIZE_L; k++) {
				if (minPeak > Xsig[k]) {
					minPeak = Xsig[k];
				}
				if (maxPeak < Xsig[k]) {
					maxPeak = Xsig[k];
				}
			}

			//确定峰值点位置
			peak_cnt = 0;
			if ((maxPeak - minPeak) > 64)
			{
				for (k = 0; k < SIZE_L; k++) {
					if ((Xsig[k - 1] < Xsig[k]) && (Xsig[k] >= Xsig[k + 1])) {
						peak_pos[peak_cnt++] = k;
					}
				}
			}

			//计算峰值点平均间距
			peak_freq = 0.0;
			if (peak_cnt >= 2) {
				for (k = 0; k < peak_cnt - 1; k++) {
					peak_freq += (peak_pos[k + 1] - peak_pos[k]);
				}
				peak_freq /= peak_cnt - 1;
			}
			//计算当前像素的频率
			if (peak_freq < 3.0 || peak_freq > 25.0) {
				frequency1[x + y*iWidth] = 0.0;
			}
			else
			{
				frequency1[x + y*iWidth] = 1.0 / peak_freq;
			}
		}
	}

	//对频率进行均值滤波
	for (y = SIZE_L2; y < iHeight - SIZE_L2; y++) {
		for (x = SIZE_L2; x < iWidth - SIZE_L2; x++) {
			k = x + y*iWidth;
			peak_freq = 0.0;
			//使用以当前像素为中心的5*5邻域窗口进行均值滤波
			for (v = -2; v <= 2; v++) {
				for (u = -2; u <= 2; u++) {
					peak_freq += frequency1[(x + u) + (y + v)*iWidth];
				}
			}
			fFrequency[k] = peak_freq / 25;
		}
	}
	delete[] frequency1;

	return 0;
}

int CFingerDlg::Step5_Frequency(char * info)
{
	//设置输入输出文件名
	char srcTxtFile_Img[MAX_PATH] = { STEP_TXT_3 };
	char srcTxtFile_Dir[MAX_PATH] = { STEP_TXT_4 };
	char srcImgFile[MAX_PATH] = { STEP_IMG_4 };
	char dstTxtFile[MAX_PATH] = { STEP_TXT_5 };
	char dstImgFile[MAX_PATH] = { STEP_IMG_5 };

	//读取图像参数
	int iWidth, iHeight, iDepth;
	int flag = ReadBMPImageFilePara((CString)srcImgFile, iWidth, iHeight, iDepth);
	//读取图像源数据
	unsigned char*image1 = new unsigned char[iWidth * iHeight];
	ReadDataFromTextFile(srcTxtFile_Img, image1, iWidth, iHeight);
	//读取方向源数据
	float *dirction = new float[iWidth*iHeight];
	readDataFromTextFile(srcTxtFile_Dir, dirction, iWidth, iHeight);
	//频率计算
	float *frequency = new float[iWidth*iHeight];
	Frequency(image1, dirction, frequency, iWidth, iHeight);

	//保存结果数据（TXT 文件）
	SaveDataToTextFile(dstTxtFile, frequency, iWidth, iHeight);

	//保存结果图像
	const int FREQUENCY_SCALE = 1000;
	SaveDataToImageFile(srcImgFile, dstImgFile, frequency, FREQUENCY_SCALE);
	//释放内存空间
	delete[] image1;
	delete[] dirction;
	delete[] frequency;
	//返回操作成败状态
	sprintf(info, "完成频率计算");

	return 0;
}
//频率计算
void CFingerDlg::OnBnClickedBtnStep5()
{
	//初始化操作结果信息
	char info[MAX_PATH] = { 0 };

	//指纹频率计算
	Step5_Frequency(info);
	//显示操作结果信息
	m_staticInfo.SetWindowTextW(ToWideChar(info));
	//显示图像
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_4);//显示输入图像
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_5);//显示输出图像
}

int CFingerDlg::GetMask(unsigned char * ucImg, float * fDirection, float * fFrequency, unsigned char * ucMask, int iWidth, int iHeight)
{
	//阈值分割
	float freqMin = 1.0 / 25.0;
	float freqMax = 1.0 / 3.0;
	int x, y, k;
	int pos, posout;
	memset(ucMask, 0, iWidth*iHeight);
	for (y = 0; y < iHeight; y++) {
		for (x = 0; x < iWidth; x++) {
			pos = x + y*iWidth;
			posout = x + y*iWidth;
			ucMask[posout] = 0;
			if (fFrequency[pos] >= freqMin && fFrequency[pos] <= freqMax) {
				ucMask[posout] = 255;
			}
		}
	}
	//第二步：填充孔洞（利用形态学的膨胀原理）
	for (k = 0; k < 4; k++) {
		//标记前景点
		for (y = 1; y < iHeight - 1; y++) {
			for (x = 1; x < iWidth - 1; x++) {
				if (ucMask[x + y*iWidth] == 0xFF) {//前景点

					ucMask[x - 1 + y*iWidth] |= 0x80;
					ucMask[x + 1 + y*iWidth] |= 0x80;
					ucMask[x + (y - 1)*iWidth] |= 0x80;
					ucMask[x + (y + 1)*iWidth] |= 0x80;
				}
			}
		}
		//判断和设置前景点
		for (y = 1; y < iHeight - 1; y++) {//逐行遍历
			for (x = 1; x < iWidth - 1; x++) {//逐列遍历
											  //将标记为前景点的像素都设为前景点
				if (ucMask[x + y*iWidth]) {
					ucMask[x + y*iWidth] = 0xFF;//设为前景点
				}
			}
		}
	}

	//第三步：去除边缘和孤立点（利用形态学的腐蚀原理）
	for (k = 0; k < 12; k++) {//重复腐蚀多次（次数自定）
							  //标记背景点
		for (y = 1; y < iHeight - 1; y++) {//逐行遍历
			for (x = 1; x < iWidth - 1; x++) {//逐列遍历
											  //背景点的上下左右四个相邻点都标记为潜在背景点（将8位像素值的后7位都设为0予以标记）
				if (ucMask[x + y*iWidth] == 0x0)//背景点
				{
					ucMask[x - 1 + y*iWidth] &= 0x80;
					ucMask[x + 1 + y*iWidth] &= 0x80;
					ucMask[x + (y - 1)*iWidth] &= 0x80;
					ucMask[x + (y + 1)*iWidth] &= 0x80;
				}
			}
		}
		//判断和设置背景点
		for (y = 1; y < iHeight - 1; y++) {
			for (x = 1; x < iWidth - 1; x++) {
				//只要不是前景点的所有像素都设为背景点
				if (ucMask[x + y*iWidth] != 0xFF) {//非前景点
					ucMask[x + y*iWidth] = 0x0;//设为背景点（像素值为0）
				}
			}
		}
	}

	return 0;
}

int CFingerDlg::Step6_Mask(char * info)
{
	char srcTxtFile_Img[MAX_PATH] = { STEP_TXT_3 };//图像源
	char srcTxtFile_Dir[MAX_PATH] = { STEP_TXT_4 };//方向源
	char srcTxtFile_Fre[MAX_PATH] = { STEP_TXT_5 };//频率源
	char srcImgFile[MAX_PATH] = { STEP_IMG_5 };//源图
	char dstTxtFile[MAX_PATH] = { STEP_TXT_6 };//结果数据文件名
	char dstImgFile[MAX_PATH] = { STEP_IMG_6 };//结果图文件名

											   //读取图像参数
	int iWidth, iHeight, iDepth;
	ReadBMPImageFilePara((CString)srcImgFile, iWidth, iHeight, iDepth);
	//读取图像源数据
	unsigned char*image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Img, image1, iWidth, iHeight);
	//读取方向源数据
	float *direction = new float[iWidth*iHeight];
	readDataFromTextFile(srcTxtFile_Dir, direction, iWidth, iHeight);
	//读取频率源数据
	float *frequency = new float[iWidth*iHeight];
	readDataFromTextFile(srcTxtFile_Fre, frequency, iWidth, iHeight);
	//掩码计算
	unsigned char*mask = new unsigned char[iWidth*iHeight];
	GetMask(image1, direction, frequency, mask, iWidth, iHeight);

	//保存结果数据（TXT文件）
	SaveDataToTextFile(dstTxtFile, mask, iWidth, iHeight);
	//保存结果图像（BMP文件，仅用于显示）
	SaveDataToImageFile(srcImgFile, dstImgFile, mask);

	//释放空间
	delete[] image1;
	delete[] mask;
	delete[] direction;
	delete[] frequency;
	//返回操作成败状态

	sprintf(info, "完成掩码计算");

	return 0;
}

void CFingerDlg::OnBnClickedBtnStep6()
{
	//初始化操作结果信息
	char info[MAX_PATH] = { 0 };
	//指纹掩码计算
	Step6_Mask(info);
	//显示操作结果信息
	m_staticInfo.SetWindowTextW(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_5);
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_6);

}

int CFingerDlg::GaborEnhance(unsigned char* ucImg, float * fDirection, float * fFrequency, unsigned char * ucMask, unsigned char * ucImgEnhanced, int iWidth, int iHeight)
{
	const float PI = 3.141592654;
	int i, j, u, v;
	int wg2 = 5;
	float sum, f, g;
	float x2, y2;
	float dx2 = 1.0 / (4.0*4.0);//沿x轴方向的高斯包络常量
	float dy2 = 1.0 / (4.0*4.0);
	//结果初始化
	memset(ucImgEnhanced, 0, iWidth*iHeight);
	//Gabor滤波
	for (j = wg2; j < iHeight - wg2; j++) {
		for (i = wg2; i < iWidth - wg2; i++) {
			//跳过背景点
			if (ucMask[i + j*iWidth] == 0) {//掩码为0表示背景点
				continue;
			}
			//获取当前像素的方向和频率
			g = fDirection[i + j*iWidth];
			f = fFrequency[i + j*iWidth];
			g += PI / 2;//垂直方向
						//对当前像素进行Gabor滤波
			sum = 0.0;
			for (v = -wg2; v <= wg2; v++) {
				for (u = -wg2; u <= wg2; u++) {
					x2 = -u*sin(g) + v*cos(g);//x坐标旋转
					y2 = u*cos(g) + v*sin(g);
					sum += exp(-0.5*(x2*x2*dx2 + y2*y2*dy2)) * cos(2 * PI*x2*f)*ucImg[(i - u) + (j - v)*iWidth];
				}
			}
			//边界值处理
			if (sum > 255.0) {
				sum = 255.0;
			}if (sum < 0.0) {
				sum = 0.0;
			}
			//得到当前像素的滤波结果
			ucImgEnhanced[i + j*iWidth] = (unsigned char)sum;

		}
	}
	return 0;
}

int CFingerDlg::Step7_GaborEnhance(char * info)
{
	char srcTxtFile_Img[MAX_PATH] = { STEP_TXT_3 };//图像源
	char srcTxtFile_Dir[MAX_PATH] = { STEP_TXT_4 };//方向源
	char srcTxtFile_Fre[MAX_PATH] = { STEP_TXT_5 };//频率源
	char srcTxtFile_Msk[MAX_PATH] = { STEP_TXT_6 };//源图
	char srcImgFile[MAX_PATH] = { STEP_IMG_6 };//源图
	char dstTxtFile[MAX_PATH] = { STEP_TXT_7 };//结果数据文件名
	char dstImgFile[MAX_PATH] = { STEP_IMG_7 };//结果图文件名

	int iWidth, iHeight, iDepth;
	ReadBMPImageFilePara((CString)srcImgFile, iWidth, iHeight, iDepth);
	//读取图像源数据
	unsigned char*image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Img, image1, iWidth, iHeight);
	//方向源数据
	float *direction = new float[iWidth*iHeight];
	readDataFromTextFile(srcTxtFile_Dir, direction, iWidth, iHeight);
	//频率源
	float *frequency = new float[iWidth*iHeight];
	readDataFromTextFile(srcTxtFile_Fre, frequency, iWidth, iHeight);
	//掩码
	unsigned char*mask = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Msk, mask, iWidth, iHeight);
	//Gabor滤波增强
	unsigned char*image2 = new unsigned char[iWidth*iHeight];
	GaborEnhance(image1, direction, frequency, mask, image2, iWidth, iHeight);
	//保存结果数据（TXT文件）
	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);
	SaveDataToImageFile(srcImgFile, dstImgFile, image2);//仅用于显示
														//释放内存空间
	delete[] image1;
	delete[] direction;
	delete[] frequency;
	delete[] mask;
	delete[] image2;
	//返回操作成败状态
	sprintf(info, "完成Gabor滤波增强");

	return 0;
}

void CFingerDlg::OnBnClickedBtnStep7()
{
	//初始化操作结果信息
	char info[MAX_PATH] = { 0 };
	//Gabor滤波增强
	Step7_GaborEnhance(info);
	m_staticInfo.SetWindowTextW(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_6);
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_7);
}

int CFingerDlg::BinaryImg(unsigned char * ucImage, unsigned char * ucBinImage, int iWidth, int iHeight, unsigned char uThreshold)
{
	unsigned char*pStart = ucImage, *pEnd = ucImage + iWidth*iHeight;
	unsigned char*pDest = ucBinImage;
	while (pStart < pEnd)
	{
		*pDest = *pStart>uThreshold ? 1 : 0;//二值化
		pStart++;
		pDest++;
	}

	return 0;
}

int CFingerDlg::BinaryToGray(unsigned char * ucBinImg, unsigned char * ucGrayImg, int iWidth, int iHeight)
{
	unsigned char*pStart = ucBinImg, *pEnd = ucBinImg + iWidth*iHeight;
	unsigned char*pDest = ucGrayImg;
	while (pStart < pEnd)
	{
		*pDest = (*pStart) > 0 ? 255 : 0;
		pStart++;
		pDest++;
	}

	return 0;
}

int CFingerDlg::Step8_Binary(char * info)
{
	char srcTxtFile[MAX_PATH] = { STEP_TXT_7 };//图像源
	char srcImgFile[MAX_PATH] = { STEP_IMG_7 };//源图
	char dstTxtFile[MAX_PATH] = { STEP_TXT_8 };//结果数据文件名
	char dstImgFile[MAX_PATH] = { STEP_IMG_8 };//结果图文件名

	int iWidth, iHeight, iDepth;
	ReadBMPImageFilePara((CString)srcImgFile, iWidth, iHeight, iDepth);

	unsigned char*image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile, image1, iWidth, iHeight);

	unsigned char*image2 = new unsigned char[iWidth*iHeight];
	BinaryImg(image1, image2, iWidth, iHeight, 128);
	//保存结果数据
	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);
	BinaryToGray(image2, image1, iWidth, iHeight);
	SaveDataToImageFile(srcImgFile, dstImgFile, image1);
	delete[] image1;
	delete[] image2;
	sprintf(info, "完成二值化");
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep8()
{
	char info[MAX_PATH] = { 0 };
	//图像二值化
	Step8_Binary(info);
	m_staticInfo.SetWindowTextW(ToWideChar(info));
	//显示图像
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_7);
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_8);

}

int CFingerDlg::Thinning(unsigned char * ucBinedImg, unsigned char * ucThinnedImage, int lWidth, int lHeight, int lIterativeLimit)
{

	unsigned char x1, x2, x3, x4, x5, x6, x7, x8, xp;
	unsigned char g1, g2, g3, g4;
	unsigned char b1, b2, b3, b4;
	unsigned char np1, np2, npm;
	unsigned char *pUp, *pDown, *pImg;
	int lDeletedPoints = 0;

	memcpy(ucThinnedImage, ucBinedImg, lWidth*lHeight);

	for (int it = 0; it < lIterativeLimit; it++)
	{
		lDeletedPoints = 0;

		for (int i = 1; i < lHeight - 1; i++)
		{
			pUp = ucBinedImg + (i - 1)*lWidth;
			pImg = ucBinedImg + i*lWidth;
			pDown = ucBinedImg + (i + 1)*lWidth;

			for (int j = 1; j < lWidth - 1; j++)
			{
				pUp++;
				pImg++;
				pDown++;

				if (!*pImg)
				{
					continue;
				}

				x6 = *(pUp - 1);
				x5 = *(pImg - 1);
				x4 = *(pDown - 1);

				x7 = *pUp;
				xp = *pImg;
				x3 = *pDown;

				x8 = *(pUp + 1);
				x1 = *(pImg + 1);
				x2 = *(pDown + 1);

				b1 = !x1 && (x2 == 1 || x3 == 1);
				b2 = !x3 && (x4 == 1 || x5 == 1);
				b3 = !x5 && (x6 == 1 || x7 == 1);
				b4 = !x7 && (x8 == 1 || x1 == 1);

				g1 = (b1 + b2 + b3 + b4) == 1;

				np1 = x1 || x2;
				np1 += x3 || x4;
				np1 += x5 || x6;
				np1 += x7 || x8;
				np2 = x2 || x3;
				np2 += x4 || x5;
				np2 += x6 || x7;
				np2 += x8 || x1;

				npm = np1 > np2 ? np2 : np1;
				g2 = npm >= 2 && npm <= 3;

				g3 = (x1 && (x2 || x3 || !x8)) == 0;
				g4 = (x5 && (x6 || x7 || !x4)) == 0;

				if (g1 && g2 && g3)
				{
					ucThinnedImage[lWidth*i + j] = 0;
					++lDeletedPoints;
				}
			}
		}

		memcpy(ucBinedImg, ucThinnedImage, lWidth*lHeight);

		for (int i = 1; i < lHeight - 1; i++)
		{
			pUp = ucBinedImg + (i - 1)*lWidth;
			pImg = ucBinedImg + i*lWidth;
			pDown = ucBinedImg + (i + 1)*lWidth;

			for (int j = 1; j < lWidth - 1; j++)
			{
				pUp++;
				pImg++;
				pDown++;

				if (!*pImg)
				{
					continue;
				}

				x6 = *(pUp - 1);
				x5 = *(pImg - 1);
				x4 = *(pDown - 1);

				x7 = *pUp;
				xp = *pImg;
				x3 = *pDown;

				x8 = *(pUp + 1);
				x1 = *(pImg + 1);
				x2 = *(pDown + 1);

				b1 = !x1 && (x2 == 1 || x3 == 1);
				b2 = !x3 && (x4 == 1 || x5 == 1);
				b3 = !x5 && (x6 == 1 || x7 == 1);
				b4 = !x7 && (x8 == 1 || x1 == 1);

				g1 = (b1 + b2 + b3 + b4) == 1;

				np1 = x1 || x2;
				np1 += x3 || x4;
				np1 += x5 || x6;
				np1 += x7 || x8;
				np2 = x2 || x3;
				np2 += x4 || x5;
				np2 += x6 || x7;
				np2 += x8 || x1;

				npm = np1 > np2 ? np2 : np1;
				g2 = npm >= 2 && npm <= 3;

				g3 = (x1 && (x2 || x3 || !x8)) == 0;
				g4 = (x5 && (x6 || x7 || !x4)) == 0;

				if (g1 && g2 && g4)
				{
					ucThinnedImage[lWidth*i + j] = 0;
					++lDeletedPoints;
				}
			}
		}

		memcpy(ucBinedImg, ucThinnedImage, lWidth*lHeight);

		if (lDeletedPoints == 0)
		{
			break;
		}
	}

	for (int i = 0; i < lHeight; i++)
	{
		for (int j = 0; j < lWidth; j++)
		{
			if (i<16)
			{
				ucThinnedImage[i*lWidth + j] = 0;
			}
			else if (i >= lHeight - 16)
			{
				ucThinnedImage[i*lWidth + j] = 0;
			}
			if (j<16)
			{
				ucThinnedImage[i*lWidth + j] = 0;
			}
			else if (j >= lWidth - 16)
			{
				ucThinnedImage[i*lWidth + j] = 0;
			}
		}
	}

	return 0;
}

int CFingerDlg::Step9_Thinning(char * info)
{
	//设置输入输出文件名
	char srcTxtFile[MAX_PATH] = { STEP_TXT_8 };		//源数据文件名
	char srcImgFile[MAX_PATH] = { STEP_IMG_8 };		//源图文件名
	char dstTxtFile[MAX_PATH] = { STEP_TXT_9 };	//结果数据文件名
	char dstImgFile[MAX_PATH] = { STEP_IMG_9 };	//结果图文件名

												//读取图像参数
	int lWidth, lHeight, lDepth;
	ReadBMPImageFilePara((CString)srcImgFile, lWidth, lHeight, lDepth);
	//读取源数据
	unsigned char *image1 = new unsigned char[lWidth*lHeight];
	ReadDataFromTextFile(srcTxtFile, image1, lWidth, lHeight);

	//细化
	unsigned char *image2 = new unsigned char[lWidth*lHeight];
	Thinning(image1, image2, lWidth, lHeight, 200);

	//保存结果数据（TXT文件）
	SaveDataToTextFile(dstTxtFile, image2, lWidth, lHeight);

	//保存结果图像（BMP文件，仅用于显示）
	BinaryToGray(image2, image1, lWidth, lHeight);	//二值图显示转换
	SaveDataToImageFile(srcImgFile, dstImgFile, image1);

	//释放内存空间
	delete[] image1;
	delete[] image2;

	//返回操作成败状态
	sprintf(info, "完成细化");
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep9()
{
	// TODO: 在此添加控件通知处理程序代码
	//初始化操作结果信息
	char info[MAX_PATH] = { 0 };

	//图像细化
	Step9_Thinning(info);

	//显示操作结果信息
	m_staticInfo.SetWindowText(ToWideChar(info));

	//显示图像
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_8);
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_9);
}

int CFingerDlg::Extract(unsigned char * ucThinImg, unsigned char * ucMinuImg, int lWidth, int lHeight)
{
	//定义变量
	unsigned char * pDest = ucMinuImg;	//结果图数据指针
	unsigned char * pUp, *pDown, *pImg;	//源图邻域指针
	unsigned char x1, x2, x3, x4, x5, x6, x7, x8;	//八邻点
	unsigned char nc;	//八邻点中黑点数量
	int lMinuCount = 0;	//特征点数量

						//结果初始化（全设为0，表示都是非特征点）
	memset(pDest, 0, lWidth*lHeight);

	//遍历源图以提取特征指纹
	for (int i = 1; i < lHeight - 1; i++)	//逐行遍历
	{
		//初始化邻域指针
		pUp = ucThinImg + (i - 1)*lWidth;
		pImg = ucThinImg + i*lWidth;
		pDown = ucThinImg + (i + 1)*lWidth;

		for (int j = 1; j < lWidth - 1; j++) //逐列遍历
		{
			//调整邻域指针
			pUp++;
			pImg++;
			pDown++;

			//跳过背景点（背景点像素值为0）
			if (!*pImg)
			{
				continue;
			}

			//获取3*3邻域窗口内所有8个邻点像素的灰度值
			x6 = *(pUp - 1);
			x5 = *(pImg - 1);
			x4 = *(pDown - 1);

			x7 = *pUp;
			x3 = *pDown;

			x8 = *(pUp + 1);
			x1 = *(pImg + 1);
			x2 = *(pDown + 1);

			//统计八邻点中黑点数量
			nc = x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8;

			//特征点判断
			if (nc == 1)	//端点
			{
				pDest[i*lWidth + j] = 1;	//结果图中对应像素点设为1（表示端点）
				++lMinuCount;	//特征点数量加1
			}
			else if (nc == 3)	//分叉点
			{
				pDest[i*lWidth + j] = 3;	//结果图中对应像素点设为3（表示分叉点）
				++lMinuCount;	//特征点数量加1
			}
		}
	}

	return lMinuCount;
}

int CFingerDlg::Step10_MinuExtract(int & minuCount, char * info)
{
	//结果初始化
	minuCount = 0;//特征点数量

				  //设置输入输出文件名
	char srcTxtFile[MAX_PATH] = { STEP_TXT_9 };		//源数据文件名
	char srcImgFile[MAX_PATH] = { STEP_IMG_9 };		//源图文件名
	char dstTxtFile[MAX_PATH] = { STEP_TXT_10 };	//结果数据文件名
	char dstImgFile[MAX_PATH] = { STEP_IMG_10 };	//结果图文件名

													//读取图像参数
	int lWidth, lHeight, lDepth;
	ReadBMPImageFilePara((CString)srcImgFile, lWidth, lHeight, lDepth);


	//读取源数据
	unsigned char *image1 = new unsigned char[lWidth*lHeight];
	ReadDataFromTextFile(srcTxtFile, image1, lWidth, lHeight);

	//特征提取
	unsigned char *image2 = new unsigned char[lWidth*lHeight];
	minuCount = Extract(image1, image2, lWidth, lHeight);

	//保存结果数据（TXT文件）
	SaveDataToTextFile(dstTxtFile, image2, lWidth, lHeight);

	//保存结果图像（BMP文件，仅用于显示）
	BinaryToGray(image2, image1, lWidth, lHeight);	//二值图显示转换
	SaveDataToImageFile(srcImgFile, dstImgFile, image1);

	//释放内存空间
	delete[] image1;
	delete[] image2;

	//返回操作成败状态
	sprintf(info, "完成特征提取");
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep10()
{
	// TODO: 在此添加控件通知处理程序代码
	//初始化操作结果信息
	char info[MAX_PATH] = { 0 };
	//特征提取
	Step10_MinuExtract(m_minuCount, info);
	//显示操作结果信息
	m_staticInfo.SetWindowText(ToWideChar(info));

	//显示图像
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_9);
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_10);
}

int CFingerDlg::MinuFilter(unsigned char * minuData, unsigned char * thinData, MINUTIAE * minutiaes, int & minuCount, int lWidth, int lHeight)
{
	//第1步：计算细化图中各点方向
	float * dir = new float[lWidth*lHeight];
	memset(dir, 0, lWidth*lHeight * sizeof(float));

	//计算脊线方向
	ImgDirection(thinData, dir, lWidth, lHeight);

	//第2步：从特征图中提取特征点数据
	unsigned char * pImg;
	unsigned char val;
	int temp = 0;
	for (int i = 1; i < lHeight - 1; i++)	//逐行遍历
	{
		pImg = minuData + i*lWidth;
		for (int j = 1; j < lWidth - 1; j++)	//逐列遍历
		{		//获取特征图数据
			++pImg;		//特征图指针后移
			val = *pImg;  //特征图像数值（0 -- 非特征点， 1 -- 端点， 3 -- 分叉点 ）

						  //提取特征点数据
			if (val>0)
			{
				minutiaes[temp].x = j + 1;	//横坐标（从1开始）
				minutiaes[temp].y = i + 1;	//纵坐标（从1开始）
				minutiaes[temp].theta = dir[i*lWidth + j];	//脊线方向
				minutiaes[temp].type = int(val);	//特征点类型（1--端点，3--分叉点）
				++temp;	//特征点数组指针后移
			}
		}
	}

	delete[] dir;

	//第3步：去除边缘特征点
	minuCount = CutEdge(minutiaes, minuCount, thinData, lWidth, lHeight);

	//第4步：去除毛刺/小孔/间断等伪特征点
	//初始化标记数组
	int *pFlag = new int[minuCount];	//标记数组（标记值：0-保留，1-删除）
	memset(pFlag, 0, sizeof(int) * minuCount);

	//遍历所有特征点
	int x1, x2, y1, y2, type1, type2;
	//特征点1遍历
	for (int i = 0; i < minuCount; i++)	//特征点1遍历
	{	//获取特征点1信息
		x1 = minutiaes[i].x;
		y1 = minutiaes[i].y;
		type1 = minutiaes[i].type;	//特征点类型（1--端点，3--分叉点）

									//特征点2遍历
		for (int j = i + 1; j < minuCount; j++)	//特征点2遍历
		{	//跳过已删特征点
			if (pFlag[j] == 1)
			{
				continue;
			}

			//获取特征点2信息
			x2 = minutiaes[j].x;
			y2 = minutiaes[j].y;
			type2 = minutiaes[j].type;	//特征点类型（1--端点，3--分叉点）

										//计算两点距离
			int r = (int)sqrt(float((y1 - y2)*(y1 - y2) + (x1 - x2)*(x1 - x2)));

			//删除间距过小的特征点
			if (r <= 4)		//如果间距不大于4则认为间距过小（间距阈值可自定）
			{
				if (type1 == type2)		//如果两点类型相同
				{
					if (type1 == 1)		//如果两点都是端点，则认定为“短线或纹线间断”
					{
						pFlag[i] = pFlag[j] = 1;	//同时删掉两点
					}
					else   //如果两点都是分叉点，则认定为“小孔”
					{
						pFlag[j] = 1;	//只删除点2
					}
				}
				else if (type1 == 1)	 //如果点1是端点而点2是分叉点，则点1为“毛刺”
				{
					pFlag[i] = 1;	//只删除掉点1
				}
				else   //如果点1是分叉点而点2是端点，则点2为“毛刺”
				{
					pFlag[j] = 1;	//只删除掉点2
				}
			}
		}
	}

	//
	int newCount = 0;
	for (int i = 0; i < minuCount; i++)
	{
		if (pFlag[i] == 0)
		{
			memcpy(&minutiaes[newCount], &minutiaes[i], sizeof(MINUTIAE));
			newCount++;
		}
	}

	delete[] pFlag;
	minuCount = newCount;

	return 0;
}

int CFingerDlg::CutEdge(MINUTIAE * minutiaes, int count, unsigned char * ucImg, int lWidth, int lHeight)
{
	int minuCount = count;
	int x, y, type;
	bool del;

	int *pFlag = new int[minuCount];
	memset(pFlag, 0, sizeof(int)*minuCount);

	for (int i = 0; i < minuCount; i++)
	{
		y = minutiaes[i].y - 1;
		x = minutiaes[i].x - 1;
		type = minutiaes[i].type;

		del = true;

		//根据当前
		if (x < lWidth / 2)	//如果位于图像左半图
		{
			if (abs(lWidth / 2 - x) > abs(lHeight / 2 - y))   //如果位于图像左半图的左侧
			{
				//在特征图中查找当前特征点同一列左侧是否还有其他特征点
				while (--x >= 0)	//逐一左移查找
				{
					//如果在左侧存在其他特征点，则说明当前特征点不是边缘特征点，就无须删除
					if (ucImg[x + y*lWidth]>0)	//特征图像素值（0-非特征点，1-端点，3-分叉点）
					{
						del = false;	//删除标记设置为false
						break;	//停止当前特征点的左移查找过程
					}
				}
			}
			else  //如果位于图像左半图的右侧
			{
				if (y>lHeight / 2)	//如果位于图像左半图的右下侧
				{
					//在特征图中查找当前特征点同一列下侧是否还有其他特征点
					while (++y<lHeight)	//逐一下移查找
					{
						//如果在下侧存在其他特征点，则说明当前特征点不是边缘特征点，就无须删除
						if (ucImg[x + y*lWidth]>0)	//特征图像素值（0-非特征点，1-端点，3-分叉点）
						{
							del = false;	//删除标记设置为false
							break;	//停止当前特征点的下移查找过程
						}
					}
				}
				else // 如果位于图像左半图的右上侧
				{
					//在特征图中查找当前特征点同一列上侧是否还有其他特征点
					while (--y >= 0)	//逐一上移查找
					{
						//如果在上侧存在其他特征点，则说明当前特征点不是边缘特征点，就无须删除
						if (ucImg[x + y*lWidth]>0)	//特征图像素值（0-非特征点，1-端点，3-分叉点）
						{
							del = false;	//删除标记设置为false
							break;	//停止当前特征点的上移查找过程
						}
					}
				}
			}
		}
		else   //如果位于图像右半图
		{
			if (abs(lWidth / 2 - x) > abs(lHeight / 2 - y))	//如果位于图像右半图的右侧
			{
				//在特征图中查找当前特征点同一行右侧是否还有其他特征点
				while (++x < lWidth)	//逐一右侧查找
				{
					//如果在右侧存在其他特征点，则说明当前特征点不是边缘特征点，就无须删除
					if (ucImg[x + y*lWidth]>0)	//特征图像素值（0-非特征点，1-端点，3-分叉点）
					{
						del = false;	//删除标记设置为false
						break;	//停止当前特征点的上移查找过程
					}
				}
			}
			else    //如果位于图像右半图的左侧
			{
				if (y > lHeight / 2)	//如果位于图像右半图的左下侧
				{
					//在特征图中查找当前特征点同一列下侧是否还有其他特征点
					while (++y<lHeight)	//逐一下移查找
					{
						//如果在下侧存在其他特征点，则说明当前特征点不是边缘特征点，就无须删除
						if (ucImg[x + y*lWidth]>0)	//特征图像素值（0-非特征点，1-端点，3-分叉点）
						{
							del = false;	//删除标记设置为false
							break;	//停止当前特征点的下移查找过程
						}
					}
				}
				else   //如果位于图像右半图的左上侧
				{
					//在特征图中查找当前特征点同一列上侧是否还有其他特征点
					while (--y >= 0)	//逐一上移查找
					{
						//如果在上侧存在其他特征点，则说明当前特征点不是边缘特征点，就无须删除
						if (ucImg[x + y*lWidth]>0)	//特征图像素值（0-非特征点，1-端点，3-分叉点）
						{
							del = false;	//删除标记设置为false
							break;	//停止当前特征点的上移查找过程
						}
					}
				}
			}
		}

		//如果当前特征点是边缘特征点，则予以删除（在标记数组中将其标记设置为1）
		if (del)	//如果当前特征点的删除标记为true，则表明其为边缘特征点
		{
			pFlag[i] = 1;	//在标记数组中将其标记设置为1（表示删除）
			continue;	//继续判断数组结构中的下一个特征点
		}
	}

	//重组特征点结构数组（在当前结构数组中将所有有效特征点前移）
	int newCount = 0;	//有效特征点数量（同时也是重组后的有效特征点数组下标）
	for (int i = 0; i < minuCount; i++)
	{
		if (pFlag[i] == 0)	//如果当前特征点需要保留（标记值：0-保留，1-删除）
		{
			memcpy(&minutiaes[newCount], &minutiaes[i], sizeof(MINUTIAE));	//特征点结构整体复制
			newCount++;	//有效特征点下标后移（有效特征点数量加1）
		}
	}

	delete pFlag;
	pFlag = NULL;

	//返回有效特征点数量
	return newCount;
}

int CFingerDlg::Step11_MinuFilter(int & minuCount, char * info)
{

	//设置输入输出文件名
	char srcTxtFile_Minu[MAX_PATH] = { STEP_TXT_10 };//特征图源数据文件名
	char srcTxtFile_Thin[MAX_PATH] = { STEP_TXT_9 }; //细化图源数据文件名

	char srcImgFile[MAX_PATH] = { STEP_IMG_10 };	//源数据文件名
	char dstTxtFile[MAX_PATH] = { STEP_TXT_11 };	//结果数据文件名
	char dstImgFile[MAX_PATH] = { STEP_IMG_11 };	//结果图文件名
	char dstMdlFile[MAX_PATH] = { STEP_IMG_11_MDL };//结果模板文件名


													//读取图像参数
	int lWidth, lHeight, lDepth;
	ReadBMPImageFilePara((CString)srcImgFile, lWidth, lHeight, lDepth);

	//读取特征图源数据
	unsigned char *image1 = new unsigned char[lWidth*lHeight];
	ReadDataFromTextFile(srcTxtFile_Minu, image1, lWidth, lHeight);

	//读取细化图源数据
	unsigned char * thin = new unsigned char[lWidth*lHeight];
	ReadDataFromTextFile(srcTxtFile_Thin, thin, lWidth, lHeight);


	//特征过滤
	MINUTIAE * minutiaes = new MINUTIAE[minuCount];
	memset(minutiaes, sizeof(MINUTIAE), minuCount);
	MinuFilter(image1, thin, minutiaes, minuCount, lWidth, lHeight);

	//保存模板文件
	SaveMinutiae(minutiaes, minuCount, dstMdlFile);

	//生成结果图像
	unsigned char *image2 = new unsigned char[lWidth*lHeight];
	memset(image2, 0, lWidth*lHeight);
	for (int i = 0; i < minuCount; i++)
	{
		image2[(minutiaes[i].y - 1)*lWidth + (minutiaes[i].x - 1)] = 0xff;
	}

	//保存结果数据（TXT文件）
	SaveDataToTextFile(dstTxtFile, image2, lWidth, lHeight);

	//保存结果图像（BMP文件，仅用于显示）
	SaveDataToImageFile(srcImgFile, dstImgFile, image2);

	//释放内存空间
	delete[] image1;
	delete[] thin;
	delete[] minutiaes;
	delete[] image2;

	//返回操作成败状态
	sprintf(info, "完成特征过滤");
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep11()
{
	// TODO: 在此添加控件通知处理程序代码
	//初始化操作结果信息
	char info[MAX_PATH] = { 0 };
	//特征提取
	Step11_MinuFilter(m_minuCount, info);

	//显示操作结果信息
	m_staticInfo.SetWindowText(ToWideChar(info));

	//显示图像
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_10);
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_11);
}

int CFingerDlg::SaveMinutiae(MINUTIAE * minutiaes, int count, char * fileName)
{
	//打开文件（二进制写入方式）
	FILE *fp = fopen(fileName, "wb");
	if (!fp)
	{
		return -1;
	}

	//将所有特征点的结构体数据整体写入文件
	const static int TemplateFileFlag = 0x3571027f;
	fwrite(&TemplateFileFlag, sizeof(int), 1, fp);	//写入特征模板文件标记
	fwrite(&count, sizeof(int), 1, fp);	//写入特征点数量
	for (int i = 0; i < count; i++)	//逐一写入所有特征点
	{
		fwrite(&minutiaes[i], sizeof(MINUTIAE), 1, fp);	//将特征点结构整体写入
	}

	//关闭文件
	fclose(fp);
	return 0;
}

int CFingerDlg::GetNewIndexInDB()
{
	//从index文件中读取最后一条记录编号
	int sNo = 0;
	char name[MAX_PATH] = { 0 }, srcFile[MAX_PATH] = { 0 }, mdlFile[MAX_PATH] = { 0 };
	FILE *index = fopen(DB_INDEX_TXT, "r");
	while (!feof(index))
	{
		fscanf(index, "%d %s %s %s\n", &sNo, srcFile, mdlFile, name);
	}
	fclose(index);

	//生成新编号
	sNo = sNo + 1;

	//返回新编号
	return sNo;
}

int CFingerDlg::Step12_Enroll(char * userName, char * info)
{

	//设置输入文件名
	char srcImgFile[MAX_PATH] = { STEP_IMG_1 };	//源图文件名
	char srcMdlFile[MAX_PATH] = { STEP_IMG_11_MDL };	//模板文件名

														//获得数据库内新指纹记录编号
	int sNo = GetNewIndexInDB();

	//设置用户名/源图文件名/源模板文件名等需要存入数据库的指纹登记信息
	char regName[MAX_PATH] = { 0 };	//登记人姓名
	char dstImgFile[MAX_PATH] = { 0 };	//源图文件
	char dstMdlFile[MAX_PATH] = { 0 };	//源模板文件
	sprintf(regName, userName);		//直接复制界面输入内容
	sprintf(dstImgFile, "%s%d.bmp", DB_DIR, sNo);	//存入数据库文件夹内，以编号命名
	sprintf(dstMdlFile, "%s%d.mdl", DB_DIR, sNo);	//存入数据库文件夹内，以编号命名

													//保存原始图像
	CopyFile(ToWideChar(srcImgFile), ToWideChar(dstImgFile), false);

	//保存模板文件
	CopyFile(ToWideChar(srcMdlFile), ToWideChar(dstMdlFile), false);

	//指纹登记信息写入数据库索引文件
	FILE *index = fopen(DB_INDEX_TXT, "a");	//追加模式写入
	fprintf(index, "%d %s %s %s\n", sNo, dstImgFile, dstMdlFile, regName);
	fclose(index);

	sprintf(info, "完成特征入库.");
	return 0;
}

char * CFingerDlg::ToChar(wchar_t * str)
{
	int num = WideCharToMultiByte(0, 0, str, -1, NULL, 0, NULL, false);
	char *chStr = new char[num];
	WideCharToMultiByte(0, 0, str, -1, chStr, num, NULL, false);
	return chStr;
}

int CFingerDlg::BuildNabors(MINUTIAE * minutiae, int minuCount)
{


	//定义变量
	const int MAX_NEIGHBOR_EACH = 10;	//每个特征点最多保存10个相邻特征点
	int x1, x2, y1, y2;
	int *pFlag = new int[minuCount];	//相邻标记数组（标记值：0-不相邻，1-相邻）

										//遍历特征点数组
	for (int i = 0; i < minuCount; i++)
	{
		//获取当前特征点信息
		x1 = minutiae[i].x;
		y1 = minutiae[i].y;

		//初始化当前特征点的相邻标记数组
		memset(pFlag, 0, sizeof(int)*minuCount);	//初始化为全0（不相邻）
		pFlag[i] = 1;	//将自身标记为“相邻”

						//为当前特征点创建并初始化相邻特征点结构数组
		minutiae[i].neibors = new NEIGHBOR[MAX_NEIGHBOR_EACH];	//创建相邻特征点结构数组

		if (minutiae[i].neibors == NULL)
		{
			return -1;
		}
		memset(minutiae[i].neibors, 0, sizeof(NEIGHBOR)*MAX_NEIGHBOR_EACH);	//初始化数组

																			//查找和保存10个相邻特征点
		for (int neighborNo = 0; neighborNo < MAX_NEIGHBOR_EACH; neighborNo++)	//重复10次
		{
			//初始化最小间距和对应的特征点下标
			int minDistance = 1000;	//最小间距
			int minNo = 0;	//最小间距对应特征点下标

							//查找相邻特征点之外的最近的不相邻特征点
			for (int j = 0; j < minuCount; j++)	//每次都遍历所有特征点
			{
				//跳过已找到的相邻特征点
				if (pFlag[j] == 1)	//（标记值：0-不相邻，1-相邻）
				{
					continue;
				}

				//获取特征点2的信息
				x2 = minutiae[j].x;
				y2 = minutiae[j].y;

				//计算两点间距
				int r = (int)sqrt(float((y1 - y2)*(y1 - y2) + (x1 - x2)*(x1 - x2)));

				//查找最小间距
				if (r < minDistance)
				{
					minNo = j;
					minDistance = r;
				}
			}

			//保存查找结果
			pFlag[minNo] = 1;	//将找到的最近的不相邻特征点的标记设置为“相邻”
			minutiae[i].neibors[neighborNo].x = minutiae[minNo].x;	//横坐标（列坐标）
			minutiae[i].neibors[neighborNo].y = minutiae[minNo].y;	//纵坐标（行坐标）
			minutiae[i].neibors[neighborNo].type = minutiae[minNo].type;	//特征点类型（1-端点，3-分叉点）
			minutiae[i].neibors[neighborNo].Theta = Angle2Points(minutiae[minNo].x, minutiae[minNo].y, x1, y1); //两点连线角度（弧度）
			minutiae[i].neibors[neighborNo].Theta2Ridge = minutiae[minNo].theta - minutiae[i].theta;	//两点极限方向夹角（弧度）
			minutiae[i].neibors[neighborNo].ThetaThisNibor = minutiae[minNo].theta;	//相邻点的脊线方向（弧度）
			minutiae[i].neibors[neighborNo].distance = minDistance;	//两点距离
		}
	}

	delete[] pFlag;

	return 0;
}

float CFingerDlg::Angle2Points(int x1, int y1, int x2, int y2)
{


	const float PI = 3.141592654;
	float diffY, diffX;
	float theta = 0.0;

	diffY = y2 - y1;
	diffX = x2 - x1;

	if (diffY<0 && diffX>0)
	{
		theta = atan2(-1 * diffY, diffX);
	}
	else if (diffY<0 && diffX<0)
	{
		theta = PI - atan2(-1 * diffY, -1 * diffX);
	}
	else if (diffY>0 && diffX<0)
	{
		theta = atan2(diffY, -1 * diffX);
	}
	else if (diffY>0 && diffX>0)
	{
		theta = PI - atan2(diffY, diffX);
	}
	else if (diffX == 0)
	{
		theta = PI / 2;
	}
	else
	{
		theta = 0.0;
	}

	return theta;
}

float CFingerDlg::MinuSimilarity(int lWidth, int lHeight, MINUTIAE * minutiae1, int count1, MINUTIAE * minutiae2, int count2)
{

	const int MAX_SIMILAR_PAIR = 100;	//最多保存100对配对相似特征点
	const int MAX_NEIGHBOR_EACH = 10;	//每个特征点最多保存10个相邻特征点

										//构建特征点相邻关系
	BuildNabors(minutiae1, count1);
	BuildNabors(minutiae2, count2);

	//初始化特征点匹配结果（相似特征点点对）
	int similarPair[MAX_SIMILAR_PAIR][2];
	memset(similarPair, 0, 100 * 2 * sizeof(int));

	//选择基准特征和参考特征
	MINUTIAE *baseMinutiae;	//基准特征点数组（含特征点较少）
	MINUTIAE *refMinutiae;	//参考特征点数组（含特征点较多）
	int baseAccount, refAccount;
	if (count1<count2)
	{
		baseMinutiae = minutiae1;
		baseAccount = count1;
		refMinutiae = minutiae2;
		refAccount = count2;
	}
	else
	{
		baseMinutiae = minutiae2;
		baseAccount = count2;
		refMinutiae = minutiae1;
		refAccount = count1;
	}

	//方便起见，下文中“特征点”均简称为的“点”，例如“基准点/参考点/相邻点/相似点”等
	NEIGHBOR *baseNeighbors = NULL;	//基准点的相邻点指针
	NEIGHBOR *refNeighbors = NULL;	//参考点的相邻点指针
	int similarMinutiae = 0;	//相似点对数量（数组下标）
	float baseTheta, refTheta;	//基准方向和参考方向

								//特征点匹配（在参考点数组中寻找与每一个基准点对应的最相似的参考点）
	for (int i = 0; i < baseAccount; i++)	//逐一遍历参考点数组
	{
		//获取当前基准点信息
		baseNeighbors = baseMinutiae[i].neibors;	//基准点的相邻点数组
		baseTheta = baseMinutiae[i].theta;	//基准点的脊线方向

											//在参考点数组中寻找雨当前基准点最相似的参考点
		int refSimilarNo = 0;
		int maxSimilarNeibors = 0;
		for (int j = 0; j < refAccount; j++)	//逐一遍历参考点数组
		{
			//跳过与当前基准点类型不同的参考点
			if (refMinutiae[j].type != baseMinutiae[i].type)
			{
				continue;
			}

			//获取当前参考点信息
			refNeighbors = refMinutiae[j].neibors;	//参考点的相邻点数组
			refTheta = refMinutiae[j].theta;	//参考点的脊线方向

												//通话机相似相邻点数量
			int thisSimilarNeigbors = 0;	//相似相邻点数量初始化为0
											//逐一遍历当前基准点的相邻点数组
			for (int m = 0; m < MAX_NEIGHBOR_EACH; m++)
			{
				//在当前参考点的相邻点数组中查找与当前基准点的当前相邻点相似的相邻点
				for (int n = 0; n < MAX_NEIGHBOR_EACH; n++)	//逐一遍历当前参考点的相邻点数组
				{
					//跳过类型不同的相邻点
					if (baseNeighbors[m].type != refNeighbors[n].type)
					{
						continue;
					}

					//计算两个相邻点之间的距离差和不同角度差（弧度）
					int dist = abs(int(baseNeighbors[m].distance - refNeighbors[n].distance));
					float theta1 = abs(float((baseNeighbors[m].Theta - baseTheta) - (refNeighbors[n].Theta - refTheta)));
					float theta2 = abs(float(baseNeighbors[m].Theta2Ridge - refNeighbors[n].Theta2Ridge));
					float theta3 = abs(float((baseNeighbors[m].Theta - baseNeighbors[m].ThetaThisNibor) - (refNeighbors[n].Theta - refNeighbors[n].ThetaThisNibor)));

					//如果距离差小于指定阈值（此处取4）并且角度差均小于指定阈值（此处取0.15）,则认为这两个相邻点相似
					if (dist<4 && theta1<0.15f && theta2<0.15f && theta3<0.15f)
					{
						++thisSimilarNeigbors;	//相似相邻点数加1
						break;	//转向当前基准点的下一个相邻点继续查找
					}
				}
			}

			//如果3对以上相邻点相似，则认为当前基准点与当前当前参考点相似，保存匹配结果
			if ((thisSimilarNeigbors >= MAX_NEIGHBOR_EACH * 3 / 10) && (similarMinutiae<MAX_SIMILAR_PAIR))
			{
				similarPair[similarMinutiae][0] = i;	//保存当前基准点下标
				similarPair[similarMinutiae][1] = refSimilarNo;	//保存当前参考点下标
				++similarMinutiae;	//相似点对数量加一（数组下标后移）
			}
		}
	}

	//计算特征匹配相似度
	float similarity = similarMinutiae / 8.0f;
	//如果相似特征点数量小于指定下限阈值（此处取2），则认为两个指纹完全不匹配
	similarity = similarity < 2 ? 0.0f : similarity;	//边界值处理
															//如果相似特征点数量大于指定上限阈值（此处取8），则认为两个指纹完全匹配
	similarity = similarity > 10 ? 1.0f : similarity;	//边界值处理

															//返回特征匹配相似度
	return similarity;
}

int CFingerDlg::ReadMinutiae(char * fileName, MINUTIAE ** minutiae)
{


	//打开文件（二进制读取方式）
	FILE *fp = fopen(fileName, "rb");
	if (!fp)
	{
		return -1;
	}

	//逐一真题读取所有特征点的结构体数据
	const static int TemplateFileFlag = 0x3571027f;
	int flag;
	fread(&flag, sizeof(int), 1, fp);	//读取特征模板文件标记
	if (flag != TemplateFileFlag)
	{
		return -2;
	}

	int account;
	fread(&account, sizeof(int), 1, fp);	//读取特征点数量

	*minutiae = new MINUTIAE[account];	//创建特征点结构数组
	if (minutiae == NULL)
	{
		return -3;
	}

	for (int i = 0; i < account; i++)	//逐一读取所有特征点
	{
		fread(&((*minutiae)[i]), sizeof(MINUTIAE), 1, fp);	//整体读取特征点结构
	}

	//关闭文件
	fclose(fp);
	return account;
}

int CFingerDlg::Step12_Match(char * info)
{
	//设置输入输出文件名
	char srcImgFile[MAX_PATH] = { STEP_IMG_1 };	//源图文件名
	char srcMdlFile[MAX_PATH] = { STEP_IMG_11_MDL };	//模板文件名
	char dstImgFile[MAX_PATH] = { STEP_IMG_12 };	//结果图文件名

													//读取图像参数
	int lWidth, lHeight, lDepth;
	ReadBMPImageFilePara((CString)srcImgFile, lWidth, lHeight, lDepth);

	//读取指纹特征数据
	MINUTIAE *minu = NULL;
	int minuAccount = ReadMinutiae(srcMdlFile, &minu);

	//特征匹配（此处仅测试自身与自身匹配）
	float similar = MinuSimilarity(lWidth, lHeight, minu, minuAccount, minu, minuAccount);

	//释放内存空间
	delete[] minu;

	//保存匹配结果图像
	CopyFile(ToWideChar(srcImgFile), ToWideChar(dstImgFile), false);

	//返回操作成败状态
	const float SIMILAR_THRED = 0.1;	//匹配相似度阈值（小于阈值则认为不匹配）
	if (similar < SIMILAR_THRED)
	{
		sprintf(info, "匹配失败");
		return -3;
	}

	sprintf(info, "匹配成功：相似度[%.2f].", similar);
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep12b()
{
	// TODO: 在此添加控件通知处理程序代码

	//初始化操作结果信息
	char info[MAX_PATH] = { 0 };

	Step12_Match(info);	//特征匹配
						//Step12_Identify(info);	//指纹识别

						//显示操作结果信息
	m_staticInfo.SetWindowText(ToWideChar(info));

	//显示图像
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_1);	//显示原始图像
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_12);	//显示指纹图像特征
}

bool CFingerDlg::EmptyDB()
{
	//打开文件
	char indexFile[MAX_PATH] = { DB_INDEX_TXT };	//指纹库索引文件
	FILE *pFile = fopen(indexFile, "r");
	if (!pFile)	//若索引文件不存在或异常，则指纹库为空
	{
		return true;
	}

	//判断指纹库是否为空（索引文件内容是否为空）
	int size = filelength(fileno(pFile));	//文件长度（以字节为单位）
	bool bEmpty = (size < 1) ? true : false;	//若索引文件内容为空，则指纹库为空

												//关闭文件
	fclose(pFile);

	//返回判断结果
	return bEmpty;
}

int CFingerDlg::Step12_Identify(char * info)
{
	//设置输入输出文件名
	char srcImgFile[MAX_PATH] = { STEP_IMG_1 };	//源图文件名
	char srcMdlFile[MAX_PATH] = { STEP_IMG_11_MDL };	//源图指纹特征文件名
	char dstImgFile[MAX_PATH] = { STEP_IMG_12 };	//结果图文件名
	char dstMdlFile[MAX_PATH] = { 0 };	//结果图指纹特征文件名

										//指纹库预检（判断指纹库是否为空）
	EmptyDB();

	//读取图像参数
	int lWidth, lHeight, lDepth;
	ReadBMPImageFilePara((CString)srcImgFile, lWidth, lHeight, lDepth);
	//读取指纹特征数据
	MINUTIAE *minu1 = NULL, *minu2 = NULL;
	int minuAccount1 = 0, minuAccount2 = 0;
	minuAccount1 = ReadMinutiae(srcMdlFile, &minu1);

	//特征识别
	int id = 0;
	char name[MAX_PATH] = { 0 }, src[MAX_PATH] = { 0 }, mdl[MAX_PATH] = { 0 };
	float maxSimilar = -1;
	int maxID = -1;
	char maxName[MAX_PATH] = { 0 }, maxSrc[MAX_PATH] = { 0 };

	FILE *index = fopen(DB_INDEX_TXT, "r");	//打开指纹库索引文件

	while (!feof(index))
	{
		//读取指纹记录信息（指纹编号/指纹图像文件名/特征模板文件名/登记人姓名）
		fscanf(index, "%d %s %s %s\n", &id, src, mdl, name);
		sprintf(dstMdlFile, mdl);

		//从特征模板文件中读取指纹特征
		minuAccount2 = ReadMinutiae(dstMdlFile, &minu2);

		//特征匹配
		float similar = MinuSimilarity(lWidth, lHeight, minu1, minuAccount1, minu2, minuAccount2);

		//保存相似度最高的指纹记录信息
		if (similar>maxSimilar)
		{
			maxSimilar = similar;
			maxID = id;
			sprintf(maxName, name);
			sprintf(maxSrc, src);
		}
	}

	fclose(index);	//关闭文件

					//释放内存空间
	delete minu1;
	delete minu2;

	//返回识别结果
	const float SIMILAR_THRED = 0.1;	//匹配相似度阈值（小于阈值则认为不匹配）
	if (maxID<0 || maxSimilar<SIMILAR_THRED)
	{
		sprintf(info, "识别失败.");
		MessageBox(L"识别失败");
		return -2;
	}
	CopyFile(ToWideChar(maxSrc), ToWideChar(dstImgFile), false);	//复制识别结果图像
	sprintf(info, "识别成功. 识别结果：姓名[%s],目标指纹[%s]，相似度：[%.2f].", maxName, maxSrc, maxSimilar);

	return 0;
}

int CFingerDlg::Enroll(char * regName, char * srcImgFile, char * outImgFile, char * info, bool bSaveImg)
{
	//第0步：设置中间结果文件名
	//中间结果数据文件名
	char stepTxtFile1[MAX_PATH] = { STEP_TXT_1 };
	char stepTxtFile2[MAX_PATH] = { STEP_TXT_2 };
	char stepTxtFile3[MAX_PATH] = { STEP_TXT_3 };
	char stepTxtFile4[MAX_PATH] = { STEP_TXT_4 };
	char stepTxtFile5[MAX_PATH] = { STEP_TXT_5 };
	char stepTxtFile6[MAX_PATH] = { STEP_TXT_6 };
	char stepTxtFile7[MAX_PATH] = { STEP_TXT_7 };
	char stepTxtFile8[MAX_PATH] = { STEP_TXT_8 };
	char stepTxtFile9[MAX_PATH] = { STEP_TXT_9 };
	char stepTxtFile10[MAX_PATH] = { STEP_TXT_10 };
	char stepTxtFile11[MAX_PATH] = { STEP_TXT_11 };

	//中间结果图像文件名
	char stepImgFile1[MAX_PATH] = { STEP_IMG_1 };
	char stepImgFile2[MAX_PATH] = { STEP_IMG_2 };
	char stepImgFile3[MAX_PATH] = { STEP_IMG_3 };
	char stepImgFile4[MAX_PATH] = { STEP_IMG_4 };
	char stepImgFile5[MAX_PATH] = { STEP_IMG_5 };
	char stepImgFile6[MAX_PATH] = { STEP_IMG_6 };
	char stepImgFile7[MAX_PATH] = { STEP_IMG_7 };
	char stepImgFile8[MAX_PATH] = { STEP_IMG_8 };
	char stepImgFile9[MAX_PATH] = { STEP_IMG_9 };
	char stepImgFile10[MAX_PATH] = { STEP_IMG_10 };
	char stepImgFile11[MAX_PATH] = { STEP_IMG_11 };
	char stepImgFile12[MAX_PATH] = { STEP_IMG_12 };

	//指纹特征模板文件名
	char stepMdlFile11[MAX_PATH] = { STEP_IMG_11_MDL };

	//第1步：图像载入，读取源图数据和参数信息
	int lWidth, lHeight, lDepth;
	ReadBMPImageFilePara((CString)srcImgFile, lWidth, lHeight, lDepth);
	unsigned char *image1 = new unsigned char[lWidth*lHeight];
	unsigned char *image2 = new unsigned char[lWidth*lHeight];
	ReadBMPImgFileData((CString)srcImgFile, image1);	//读取源图数据
	memset(image2, 0, lWidth*lHeight);	//结果图像初始化
	if (bSaveImg)
	{
		CopyFile(ToWideChar(srcImgFile), ToWideChar(stepImgFile1), false);
		SaveDataToTextFile(stepTxtFile1, image1, lWidth, lHeight);
	}

	//第2步：中值滤波
	MidFilter(image1, image2, lWidth, lHeight);	//中值滤波
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile2, image2);
		SaveDataToTextFile(stepTxtFile2, image2, lWidth, lHeight);
	}

	//第3步：直方图均衡化
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//以第2步滤波结果为源图数据
	HistoNormalize(image1, image2, lWidth, lHeight);	//直方图均衡化
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile3, image2);
		SaveDataToTextFile(stepTxtFile3, image2, lWidth, lHeight);
	}

	//第4步：方向计算
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//以第3步均衡化结果为源图数据
	float *tmpDirection = new float[lWidth*lHeight];
	float *direction = new float[lWidth*lHeight];
	ImgDirection(image1, tmpDirection, lWidth, lHeight);	//方向计算
	DircLowPass(tmpDirection, direction, lWidth, lHeight);	//方向低通滤波
	if (bSaveImg)
	{
		const int DIRECTION_SCALE = 100;	// 方向结果转换比例（仅用于结果显示）
		SaveDataToImageFile(srcImgFile, stepImgFile4, direction, DIRECTION_SCALE);
		SaveDataToTextFile(stepTxtFile4, direction, lWidth, lHeight);
	}
	delete[] tmpDirection;

	//第5步：频率计算
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//以第3步均衡化结果为源图数据
	float *frequency = new float[lWidth*lHeight];
	Frequency(image1, direction, frequency, lWidth, lHeight);	//频率计算
	if (bSaveImg)
	{
		const int FREQUENCY_SCALE = 1000;	// 频率结果转换比例（仅用于结果显示）
		SaveDataToImageFile(srcImgFile, stepImgFile5, frequency, FREQUENCY_SCALE);
		SaveDataToTextFile(stepTxtFile5, frequency, lWidth, lHeight);
	}

	//第6步：掩码计算
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//以第3步均衡化结果为源图数据
	unsigned char * mask = new unsigned char[lWidth*lHeight];
	GetMask(image1, direction, frequency, mask, lWidth, lHeight);	//掩码计算
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile6, mask);
		SaveDataToTextFile(stepTxtFile6, mask, lWidth, lHeight);
	}

	//第7步：Gabor滤波增强
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//以第3步均衡化结果为源图数据
	GaborEnhance(image1, direction, frequency, mask, image2, lWidth, lHeight);	//增强
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile7, image2);
		SaveDataToTextFile(stepTxtFile7, image2, lWidth, lHeight);
	}
	delete[] direction;
	delete[] frequency;
	delete[] mask;

	//第8步：二值化
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//以第7步Gabor滤波结果为源图数据
	BinaryImg(image1, image2, lWidth, lHeight, 128);	//二值化
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile8, image2);
		SaveDataToTextFile(stepTxtFile8, image2, lWidth, lHeight);
	}

	//第9步：细化
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//以第8步二值化结果为源图数据
	Thinning(image1, image2, lWidth, lHeight, 128);	//细化
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile9, image2);
		SaveDataToTextFile(stepTxtFile9, image2, lWidth, lHeight);
	}
	unsigned char *thin = new unsigned char[lWidth*lHeight];
	memcpy(thin, image2, sizeof(unsigned char)*lWidth*lHeight);		//保存细化结果

																	//第10步：特征提取
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//以第9步细化结果为源图数据
	int minuCount = Extract(image1, image2, lWidth, lHeight);	//特征提取
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile10, image2);
		SaveDataToTextFile(stepTxtFile10, image2, lWidth, lHeight);
	}

	//第11步：特征过滤
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//以第10步特征提取结果为源图数据
	MINUTIAE *minutiaes = new MINUTIAE[minuCount];
	memset(minutiaes, sizeof(MINUTIAE), minuCount);
	MinuFilter(image1, thin, minutiaes, minuCount, lWidth, lHeight);	//特征过滤
	delete[] thin;
	SaveMinutiae(minutiaes, minuCount, stepMdlFile11);	//保存特征数据文件
	if (true) // bSaveImg
	{
		memset(image2, 0, lWidth*lHeight);
		for (int i = 0; i < minuCount; i++)
		{
			image2[(minutiaes[i].y - 1)*lWidth + (minutiaes[i].x - 1)] = 0xff;
		}
		SaveDataToImageFile(srcImgFile, stepImgFile11, image2);
		SaveDataToTextFile(stepTxtFile11, image2, lWidth, lHeight);
	}

	//第12步：特征入库
	int sNo = GetNewIndexInDB();	//获取数据库新指纹记录编号
	char dbImgFile[MAX_PATH] = { 0 };	//数据库中源图文件名
	char dbMdlFile[MAX_PATH] = { 0 };	//数据库中模板文件名
	sprintf(dbImgFile, "%s%d.bmp", DB_DIR, sNo);	//设置源图文件名（存入数据库文件夹内，以编号命名）
	sprintf(dbMdlFile, "%s%d.mdl", DB_DIR, sNo);	//设置模板文件名（存入数据库文件夹内，以编号命名）

	if (minuCount>0)
	{
		//保存原始指纹图像
		CopyFile(ToWideChar(srcImgFile), ToWideChar(dbImgFile), false);

		//保存指纹特征模板文件
		CopyFile(ToWideChar(stepMdlFile11), ToWideChar(dbMdlFile), false);

		//指纹登记信息写入数据库索引文件
		FILE *index = fopen(DB_INDEX_TXT, "a");	//追加模式写入
		fprintf(index, "%d %s %s %s\n", sNo, dbImgFile, dbMdlFile, regName);
		fclose(index);
	}

	//释放空间
	delete[] image1;
	delete[] image2;
	delete[] minutiaes;
	MessageBox(L"指纹登记成功");
	sprintf(info, "指纹登记成功");
	return 0;
}

void CFingerDlg::OnBnClickedBtnAddImage()
{
	// TODO: 在此添加控件通知处理程序代码

	//初始化操作结果信息
	char info[MAX_PATH] = { 0 };

	//获取界面输入内容（登记人姓名）
	UpdateData(true);
	if (m_name.GetLength() == 0) {
		//MessageBox(_T("请输入姓名"), _T("提示"));//显示信息
		MessageBox(L"请输入姓名");
		return;
	}
	//改进点：可以自由选择要打开的文件
	//选择图像
	//char *srcImgFile= "D:\\fingerimages\\L01_01.bmp";	

	//复制图像
	char*srcImgFile = openImagePath();

	//指纹登记
	bool bSaveImg = false;	//是否保存中间结果
	char *outImgFile = new char[MAX_PATH];
	//指纹特征结果图像文件名
	Enroll(ToChar(m_name.GetBuffer()), srcImgFile, outImgFile, info, bSaveImg);	//指纹登记			
																				//MessageBox(_T("登记成功"), _T("提示"));//显示信息 
																				//MessageBox(L"登记成功");
	m_staticInfo.SetWindowText(ToWideChar(info));
	//显示图像
	ShowImageInCtrl(m_picCtrl1, srcImgFile);	//显示原始指纹图像
												//ShowImageInCtrl(m_picCtrl2, outImgFile);	//显示识别结果图像

}

void CFingerDlg::OnBnClickedBtnRegister()
{
	// TODO: 在此添加控件通知处理程序代码

	//初始化操作结果信息
	if (liu == 0) {
		MessageBox(_T("未启动采集器"), _T("提示"));
		return;
	}
	char info[MAX_PATH] = { 0 };

	//获取界面输入内容（登记人姓名）
	UpdateData(true);

	//实时采集图像,由用户指定名称

	//char*srcImgFile = NULL;
	char *srcImgFile = new char[MAX_PATH];
	srcImgFile = saveImagePath();
	m_zkfpEng.SaveBitmap(ToWideChar(srcImgFile));

	//指纹登记
	bool bSaveImg = false;	//是否保存中间结果
	char *outImgFile = new char[MAX_PATH];	//指纹特征结果图像文件名
	Enroll(ToChar(m_name.GetBuffer()), srcImgFile, outImgFile, info, bSaveImg);	//指纹登记

																				//显示操作结果信息
	m_staticInfo.SetWindowText(ToWideChar(info));

	//显示图像
	ShowImageInCtrl(m_picCtrl1, srcImgFile);	//显示原始指纹图像
	ShowImageInCtrl(m_picCtrl2, "empty.bmp");	//显示识别结果图像
}

int CFingerDlg::Identify(char * srcImgFile, char * outImgFile, char * info, bool bSaveImg)
{//第0步：设置中间结果文件名
 //中间结果数据文件名
	char stepTxtFile1[MAX_PATH] = { STEP_TXT_1 };
	char stepTxtFile2[MAX_PATH] = { STEP_TXT_2 };
	char stepTxtFile3[MAX_PATH] = { STEP_TXT_3 };
	char stepTxtFile4[MAX_PATH] = { STEP_TXT_4 };
	char stepTxtFile5[MAX_PATH] = { STEP_TXT_5 };
	char stepTxtFile6[MAX_PATH] = { STEP_TXT_6 };
	char stepTxtFile7[MAX_PATH] = { STEP_TXT_7 };
	char stepTxtFile8[MAX_PATH] = { STEP_TXT_8 };
	char stepTxtFile9[MAX_PATH] = { STEP_TXT_9 };
	char stepTxtFile10[MAX_PATH] = { STEP_TXT_10 };
	char stepTxtFile11[MAX_PATH] = { STEP_TXT_11 };
	//中间结果图像文件名
	char stepImgFile1[MAX_PATH] = { STEP_IMG_1 };
	char stepImgFile2[MAX_PATH] = { STEP_IMG_2 };
	char stepImgFile3[MAX_PATH] = { STEP_IMG_3 };
	char stepImgFile4[MAX_PATH] = { STEP_IMG_4 };
	char stepImgFile5[MAX_PATH] = { STEP_IMG_5 };
	char stepImgFile6[MAX_PATH] = { STEP_IMG_6 };
	char stepImgFile7[MAX_PATH] = { STEP_IMG_7 };
	char stepImgFile8[MAX_PATH] = { STEP_IMG_8 };
	char stepImgFile9[MAX_PATH] = { STEP_IMG_9 };
	char stepImgFile10[MAX_PATH] = { STEP_IMG_10 };
	char stepImgFile11[MAX_PATH] = { STEP_IMG_11 };
	char stepImgFile12[MAX_PATH] = { STEP_IMG_12 };

	//指纹特征模板文件名
	char stepMdlFile11[MAX_PATH] = { STEP_IMG_11_MDL };
	//指纹库预检（判断指纹库是否为空）
	EmptyDB();
	//第1步：图像载入，读取源图数据和参数信息
	int iWidth, iHeight, iDepth;
	ReadBMPImageFilePara((CString)srcImgFile, iWidth, iHeight, iDepth);//读取源图参数信息
	unsigned char*image1 = new unsigned char[iWidth*iHeight];
	unsigned char*image2 = new unsigned char[iWidth*iHeight];
	ReadBMPImgFileData((CString)srcImgFile, image1);//读取源图数据
	memset(image2, 0, iWidth*iHeight);//结果图初始化
	if (bSaveImg) {
		CopyFile(ToWideChar(srcImgFile), ToWideChar(stepImgFile1), false);
		SaveDataToTextFile(stepTxtFile1, image1, iWidth, iHeight);
	}

	//第2步：中值滤波
	MidFilter(image1, image2, iWidth, iHeight);//中值滤波
	if (bSaveImg) {
		SaveDataToImageFile(srcImgFile, stepImgFile2, image2);
		SaveDataToTextFile(stepTxtFile2, image2, iWidth, iHeight);
	}

	//第3步：直方图均衡化
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以第2步滤波结果为源图数据
	HistoNormalize(image1, image2, iWidth, iHeight);//直方图均衡化
	if (bSaveImg) {
		SaveDataToImageFile(srcImgFile, stepImgFile3, image2);
		SaveDataToTextFile(stepImgFile3, image2, iWidth, iHeight);
	}

	//第4步：方向计算
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以第3步均衡化结果为源图数据
	float*tmpDirection = new float[iWidth*iHeight];
	float*direction = new float[iWidth*iHeight];
	ImgDirection(image1, tmpDirection, iWidth, iHeight);//方向计算
	DircLowPass(tmpDirection, direction, iWidth, iHeight);//方向低通滤波
	if (bSaveImg) {
		const int DIRECTION_SCALE = 100;//方向结果转换比例（仅用于结果显示）
		SaveDataToImageFile(srcImgFile, stepImgFile4, direction, DIRECTION_SCALE);
		SaveDataToTextFile(stepTxtFile4, direction, iWidth, iHeight);
	}
	delete[] tmpDirection;

	//第5步：频率计算
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);// 以第3步均衡化结果为源图数据
	float*frequency = new float[iWidth*iHeight];
	Frequency(image1, direction, frequency, iWidth, iHeight);//频率计算
	if (bSaveImg) {
		const int FREQUENCY_SCALE = 1000;//频率结果转换比例（仅用于结果显示）
		SaveDataToImageFile(srcImgFile, stepImgFile5, frequency, FREQUENCY_SCALE);
		SaveDataToTextFile(stepImgFile5, frequency, iWidth, iHeight);
	}


	//第6步:掩码计算
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);
	unsigned char*mask = new unsigned char[iWidth*iHeight];
	GetMask(image1, direction, frequency, mask, iWidth, iHeight);//掩码计算
	if (bSaveImg) {
		SaveDataToImageFile(srcImgFile, stepImgFile6, mask);
		SaveDataToTextFile(stepImgFile6, mask, iWidth, iHeight);
	}

	//第7步：Gabor滤波增强
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);
	GaborEnhance(image1, direction, frequency, mask, image2, iWidth, iHeight);//增强
	if (bSaveImg) {
		SaveDataToImageFile(srcImgFile, stepImgFile7, image2);
		SaveDataToTextFile(stepImgFile7, image2, iWidth, iHeight);
	}
	delete[] direction;
	delete[] frequency;
	delete[] mask;
	//第8步：二值化
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);
	BinaryImg(image1, image2, iWidth, iHeight, 128);//二值化
	if (bSaveImg) {
		SaveDataToImageFile(srcImgFile, stepImgFile8, image2);
		SaveDataToTextFile(stepTxtFile8, image2, iWidth, iHeight);
	}

	//第九步：细化
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);
	Thinning(image1, image2, iWidth, iHeight, 128);//细化
	if (bSaveImg) {
		SaveDataToImageFile(srcImgFile, stepImgFile9, image2);
		SaveDataToTextFile(stepTxtFile9, image2, iWidth, iHeight);
	}

	unsigned char *thin = new unsigned char[iWidth*iHeight];
	memcpy(thin, image2, sizeof(unsigned char)*iWidth*iHeight);

	//第10步：特征提取
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);
	int minuCount = Extract(image1, image2, iWidth, iHeight);//特征提取
	if (bSaveImg) {
		SaveDataToImageFile(srcImgFile, stepImgFile10, image2);
		SaveDataToTextFile(stepTxtFile10, image2, iWidth, iHeight);
	}

	//第11步：
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);
	MINUTIAE *minutiaes = new MINUTIAE[minuCount];
	memset(minutiaes, sizeof(MINUTIAE), minuCount);
	MinuFilter(image1, thin, minutiaes, minuCount, iWidth, iHeight);//特征过滤
	delete[] thin;
	SaveMinutiae(minutiaes, minuCount, stepImgFile11);//保存特征数据文件
	if (bSaveImg) {
		memset(image2, 0, iWidth*iHeight);
		for (int i = 0; i < minuCount; i++) {
			image2[(minutiaes[i].y - 1)*iWidth + (minutiaes[i].x - 1)] = 0xff;
		}
		SaveDataToImageFile(srcImgFile, stepImgFile11, image2);
		SaveDataToTextFile(stepTxtFile11, image2, iWidth, iHeight);
	}
	delete[] image1;
	delete[] image2;

	//第12步：特征识别
	int id = 0;
	char name[MAX_PATH] = { 0 }, src[MAX_PATH] = { 0 }, mdl[MAX_PATH] = { 0 };
	float maxSimilar = -1;
	int maxID = -1;
	char maxName[MAX_PATH] = { 0 }, maxSrc[MAX_PATH] = { 0 };
	MINUTIAE *minutiaes2 = NULL;
	int minuCount2 = 0;
	FILE *index = fopen(DB_INDEX_TXT, "r");//打开指纹库索引文件
	while (!feof(index))
	{
		//读取指纹记录信息（指纹编号/指纹图像文件名/特征模板文件名/登记人姓名）
		fscanf(index, "%d %s %s %s\n", &id, src, mdl, name);
		//从特征模板文件中读取指纹特征
		minuCount2 = ReadMinutiae(mdl, &minutiaes2);
		//特征匹配
		float similar = MinuSimilarity(iWidth, iHeight, minutiaes, minuCount, minutiaes2, minuCount2);

		//保存相似度最高的指纹记录信息
		if (similar > maxSimilar) {
			maxSimilar = similar;
			maxID = id;
			sprintf(maxName, name);
			sprintf(maxSrc, src);
		}
	}

	fclose(index);//关闭文件
	delete[] minutiaes;
	delete[] minutiaes2;

	//返回识别结果

	const float SIMILAR_THRED = 0.1;//匹配相似度阈值（小于阈值则认为不匹配）
	if (maxID < 0 || maxSimilar < SIMILAR_THRED) {
		sprintf(info, "识别失败.");
		MessageBox(L"识别失败");
		return -12;
	}

	strcpy(outImgFile, maxSrc);//保存识别结果图像文件名
	if (bSaveImg) {
		CopyFile(ToWideChar(maxSrc), ToWideChar(stepImgFile12), false);//复制识别结果图像
	}
	string s2(maxName);
	string s = "识别成功。 识别结果：姓名" + s2 + "相似度为:" + to_string(maxSimilar);
	CString cs(s.c_str());
	MessageBox(cs);
	sprintf(info, "识别成功。 识别结果：姓名[%s],目标指纹[%s],相似度[%.2f].", maxName, maxSrc, maxSimilar);
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep12a()
{

	//初始化操作结果信息
	char info[MAX_PATH] = { 0 };

	//获得界面输入内容
	UpdateData(true);

	//特征入库
	Step12_Enroll(ToChar(m_name.GetBuffer()), info);

	//显示操作结果信息s
	m_staticInfo.SetWindowText(ToWideChar(info));

	//显示图像
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_1);	//显示原始指纹图像
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_11);	//显示指纹特征图像

}

//静态指纹图像识别操作
void CFingerDlg::OnBnClickedBtnMatchImage()
{
	//初始化操作结果信息
	char info[MAX_PATH] = { 0 };
	//自动选择选择图像

	//char*srcImgFile = NULL;
	//复制图像
	char *srcImgFile = openImagePath();

	//指纹识别
	bool bSaveImg = false;//是否保存中间结果图像
	char outImgFile[MAX_PATH] = { 0 };//识别结果图像文件名
	Identify(srcImgFile, outImgFile, info, bSaveImg);//指纹识别

													 //显示操作结果信息
	m_staticInfo.SetWindowTextW(ToWideChar(info));
	//显示图像
	ShowImageInCtrl(m_picCtrl1, srcImgFile);//显示原始指纹图像
	ShowImageInCtrl(m_picCtrl2, outImgFile);//显示识别结果图像

}

//基于指纹采集器的指纹识别
void CFingerDlg::OnBnClickedBtnIdentify()
{
	//初始化操作结果信息
	if (liu== 0) {
		MessageBox(_T("未启动采集器"), _T("提示"));
		return;
	}
	char info[MAX_PATH] = { 0 };
	//实时采集图像

	//char*srcImgFile = NULL;
	char *srcImgFile = "capt.bmp";
	m_zkfpEng.SaveBitmap(ToWideChar(srcImgFile));

	//指纹识别
	bool bSaveImg = false;//是否保存中间结果图像
	char *outImgFile = new char[MAX_PATH];//识别结果图像文件名
	Identify(srcImgFile, outImgFile, info, bSaveImg);//指纹识别
													 //显示操作结果图像
	m_staticInfo.SetWindowText(ToWideChar(info));
	//显示图像
	ShowImageInCtrl(m_picCtrl1, srcImgFile);//显示原始指纹图像
	ShowImageInCtrl(m_picCtrl2, outImgFile);//显示识别结果图像
}

