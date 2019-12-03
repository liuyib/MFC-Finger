
// FingerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Finger.h"
#include "FingerDlg.h"
#include "afxdialogex.h"
#include "Login.h"
//����
#include <sapi.h>
#include <sphelper.h>
#pragma comment(lib,sapi.lib) 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CFingerDlg �Ի���
int liu = 0;
CFingerDlg::CFingerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FINGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	makebmp();
}

void CFingerDlg::DoDataExchange(CDataExchange* pDX)
{//��Ҫ����ȷ��ϵͳ�����и��ؼ�ID����Ӧ�Ŀؼ������İ󶨶�Ӧ��ϵ��
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

// CFingerDlg ��Ϣ�������

BOOL CFingerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

									// TODO: �ڴ���Ӷ���ĳ�ʼ������

	CLogin m_login;//ʹ��¼������������֮ǰ����	
	m_login.DoModal();

	CRgn rgnTmp;
	RECT rc;
	GetClientRect(&rc);
	rgnTmp.CreateRoundRectRgn(rc.left + 3, rc.top + 3, rc.right - rc.left - 3, rc.bottom - rc.top - 3, 6, 6);
	SetWindowRgn(rgnTmp, TRUE);
	InitDatabase();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFingerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFingerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CFingerDlg::OnImageReceivedZkfpengx(BOOL * AImageValid)
{//��ָ��ͼ������Ӧ��ʾ��ĳһͼ��ؼ���
 //������ʾ����
 //CRect rect;//������ζ���
 //m_picCtrl1.GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������
 //CDC *pDc = m_picCtrl1.GetWindowDC();//���picture�ؼ������û������
 //SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);//����λͼ����ģʽ
 //��ʾͼ��
 //image.StretchBlt(pDc->m_hDC, rect, SRCCOPY);//��ͼ�񻭵�picture�ؼ���ʾ�ľ�������
 //���¿ؼ���ʾ
 //m_picCtrl1.Invalidate(false);//���¿ؼ���
 //�ͷű����ռ�
 //image.Destroy();
 //m_picCtrl1.ReleaseDC(pDc);//�ͷ�picture�ؼ������û������
	HDC hdc = this->GetDC()->m_hDC;//�����ʾ�豸�����Ļ����ľ��
	int x = 170;//ͼ����������ϽǺ�����
	int y = 80;//ͼ����������Ͻ�������
	int width = m_zkfpEng.get_ImageWidth();//ͼ��������Ŀ��
	int height = m_zkfpEng.get_ImageHeight();//ͼ��������ĸ߶�
											 //makebmp();
	ShowImageInCtrl(m_picCtrl1, "empty.bmp");
	ShowImageInCtrl(m_picCtrl2, "empty.bmp");//���ͼƬ
	m_zkfpEng.PrintImageAt(int(hdc), x, y, width - 10, height);//����ͼ��
															   //m_staticInfo.SetWindowText(ToWideChar(""));//����֣�



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
	OnOK();//�رյ�ǰ�Ի���ϵͳ���棩
}

void CFingerDlg::OnBnClickedBtnConnect()
{
	// TODO: Add your control notification handler code here
	int z = 2;
	z = m_zkfpEng.InitEngine();//����ָ�Ʋɼ�����
	if (z == 0) {

		//MessageBox(_T("�ɼ������ӳɹ�."), _T("��ʾ"));//��ʾ��Ϣ
		MessageBox(L"�ɼ������ӳɹ�");
		GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(FALSE);//���������������ť��ң�
		GetDlgItem(IDC_BTN_DISCONNECT)->EnableWindow(FALSE);//�رհ�ť����
		liu = 1;
		//GetDlgItem(IDD_FINGER_DIALOG)->EnableWindow(TRUE);
	}
	else if (z == 1) {
		//MessageBox(_T("ָ��ʶ�������������ʧ��."), _T("��ʾ"));//��ʾ��Ϣ 
		MessageBox(L"ָ��ʶ�������������ʧ��");
	}
	else if (z == 2) {
		//MessageBox(_T("û������ָ��ʶ����."), _T("��ʾ"));//��ʾ��Ϣ 
		MessageBox(L"û������ָ��ʶ����");
	}

}

void CFingerDlg::OnBnClickedBtnDisconnect()
{
	liu = 0;
	m_zkfpEng.EndEngine();//ָֹͣ�Ʋɼ�����
	GetDlgItem(IDC_BTN_DISCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(true);//��������
}

char* CFingerDlg::openImagePath()
{
	//char *srcImgFile = NULL;
	BOOL isOpen = TRUE;//ΪTRUE����ʾ���ļ��Ի���ΪFALSE����ʾ�����ļ��Ի���
	CString defaulDir = L"D:\\fingerimages";//Ĭ�ϴ򿪵��ļ�·��
	CString fileName = L"L01_01.bmp";//Ĭ�ϴ򿪵��ļ���
	CString filter = L"�ļ���*.bmp;*.png;*.jpeg��|*.bmp;*.png;*.jpeg||";//�ļ����˵����ͣ�
	CFileDialog openFileDlg(isOpen, defaulDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"D:\\fingerimages\\L01_01.bmp";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaulDir + "\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}
	//����ͼ��
	char *srcImgFile = new char[filePath.GetLength() + 1];
	LPCTSTR p = filePath.GetBuffer(0);
	filePath.ReleaseBuffer();
	strcpy_s(srcImgFile, filePath.GetLength() + 1, CT2CA(p));
	return srcImgFile;
}

char* CFingerDlg::saveImagePath()
{
	//char * srcImgFile = NULL;
	BOOL isOpen = FALSE;//ΪTRUE����ʾ���ļ��Ի���ΪFALSE����ʾ�����ļ��Ի���
	CString defaulDir = L"D:\\fingerimages";//Ĭ�ϴ򿪵��ļ�·��
	CString fileName = L"L01_01.bmp";//Ĭ�ϴ򿪵��ļ���
	CString filter = L"�ļ���*.bmp;*.png;*.jpeg��|*.bmp;*.png;*.jpeg||";//�ļ����˵����ͣ�
	CFileDialog openFileDlg(isOpen, defaulDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"D:\\fingerimages\\L01_01.bmp";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaulDir + "\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}
	//����ͼ��
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
	//���ϵͳ������ԭ����ʾ��ͼ������
	//HDC hdc = this->GetDC()->m_hDC;//�����ʾ�豸�����Ļ����ľ��
	//int x = 160;//ͼ����������ϽǺ�����
	//int y = 80;//ͼ����������Ͻ�������
	//m_zkfpEng.PrintImageAt(int(hdc), x, y, 0, 0);//����ͼ��//ûʵ��
	//����ͼ��
	CImage image;
	HRESULT hResult = image.Load(ToWideChar(filename));
	int width = image.GetWidth();//ͼ����
	int height = image.GetHeight();//ͼ��߶�
								   //������ʾ����
	CRect rect;//������ζ���
	picCtrl.GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������
	CDC *pDc = picCtrl.GetWindowDC();//���picture�ؼ������û������
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);//����λͼ����ģʽ
													//��ʾͼ��
	image.StretchBlt(pDc->m_hDC, rect, SRCCOPY);//��ͼ�񻭵�picture�ؼ���ʾ�ľ�������
												//���¿ؼ���ʾ
	picCtrl.Invalidate(false);//���¿ؼ���ʾ
							  //�ͷű����ռ�
	image.Destroy();
	picCtrl.ReleaseDC(pDc);//�ͷ�picture�ؼ������û������


	return 0;
}


void CFingerDlg::OnBnClickedBtnCapture()
{
	// TODO: Add your control notification handler code here
	//�ɼ�ͼ�񣨱���ָ��ͼ��
	BOOL isOpen = FALSE;
	CString defaulDir = L"D:\\fingerimages";//Ĭ�ϴ򿪵��ļ�·��
	CString fileName = L"L01_01.bmp";//Ĭ�ϴ򿪵��ļ���
	CString filter = L"�ļ���*.bmp;*.png;*.jpeg��|*.bmp;*.png;*.jpeg||";//�ļ����˵����ͣ�
	CFileDialog openFileDlg(isOpen, defaulDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"D:\\fingerimages\\L01_01.bmp";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaulDir + "\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}
	//ָ�����ƣ�ָ��·��
	m_zkfpEng.SaveBitmap(filePath);
}

int CFingerDlg::ReadBMPImageFilePara(CString fileName, int & width, int & height, int & depth)
{//��ȡͼ�������Ϣ
	CImage image;
	HRESULT hResult = image.Load(fileName);
	if (FAILED(hResult) || image.IsNull()) {
		//MessageBox(_T("���ļ�Ϊ��"), _T("��ʾ"));//��ʾ��Ϣ
		MessageBox(L"���ļ�Ϊ��");
		return -1;
	}
	//���ͼ�����
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
{//��ȡͼ��λͼ����
 //����ͼ��
	CImage image;
	HRESULT hResult = image.Load(filename);
	if (FAILED(hResult) || image.IsNull()) {
		return -1;
	}

	//���ͼ�����
	int width = image.GetWidth();
	int height = image.GetHeight();
	int depth = image.GetBPP();//�����bitΪ��λ��ͼ����ȣ�ÿ�����ص�λ����
	if (depth != 8) {//Ŀǰϵͳ��֧��8λ������
		return -2;
	}
	//��ʼ���������
	memset(data, 0, width*height);
	//��ȡͼ������

	int pitch = image.GetPitch();
	unsigned char * pDatal = (unsigned char *)image.GetBits();
	unsigned char * pData2 = data;
	unsigned gray = 0;
	unsigned char * pRow1, *pRow2, *pPix1, *pPix2;
	//��������ɨ��(��������)
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
{//��������
	ofstream fout(dstFile, ios::out);//ʹ�ø���д�뷽��
	if (!fout) {
		return -1;
	}
	//��ָ����ʽ���ļ�д������
	int space = 5;
	for (int i = 0; i < height * width; i++) {
		fout << setw(space) << int(data[i]);//�ȿ�д������
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
		fout << " " << setw(space) << data[i];//�ȿ�д������
		if (i % width == (width - 1)) {
			fout << endl;
		}
	}

	fout.close();

	return 0;
}

int CFingerDlg::Step_LoadBmpImage(char * info)
{//����ָ��ͼ��
 //ѡ��ͼ��***********************�޸Ĵ��루���û���̬ѡ���ָ��ָ��ͼ��

	BOOL isOpen = TRUE;//ΪTRUE����ʾ���ļ��Ի���ΪFALSE����ʾ�����ļ��Ի���
	CString defaulDir = L"D:\\fingerimages";//Ĭ�ϴ򿪵��ļ�·��
	CString fileName = L"L01_01.bmp";//Ĭ�ϴ򿪵��ļ���
	CString filter = L"�ļ���*.bmp;*.png;*.jpeg��|*.bmp;*.png;*.jpeg||";//�ļ����˵����ͣ�
	CFileDialog openFileDlg(isOpen, defaulDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"D:\\fingerimages\\L01_01.bmp";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaulDir + "\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}
	//char filename[MAX_PATH] = filePath;
	//����ͼ��
	CopyFile(filePath, ToWideChar(STEP_IMG_1), false);
	//��ȡͼ������������Ч��
	int iWidth, iHeight, iDepth;
	int flag = ReadBMPImageFilePara(filePath, iWidth, iHeight, iDepth);
	if (flag != 0) {
		sprintf(info, "ͼ��ʧ��.");
		MessageBox(L"ͼ��ʧ��");
		return -1;
	}
	//��ȡͼ������
	unsigned char *data = new unsigned char[iWidth*iHeight];
	flag = ReadBMPImgFileData(filePath, data);
	if (flag != 0) {
		sprintf(info, "ͼ�����ݶ�ȡʧ��");
		MessageBox(L"ͼ�����ݶ�ȡʧ��");
		delete[] data;//�ͷ��ڴ�
		return -2;
	}

	//��������
	flag = SaveDataToTextFile(STEP_TXT_1, data, iWidth, iHeight);
	if (flag != 0) {
		sprintf(info, "���ݱ���ʧ��");
		MessageBox(L"���ݱ���ʧ��");
		delete[] data;
		return -3;
	}
	//����ͼ�������Ϣ

	sprintf(info, "���[%d],�߶�[%d],���[%d]", iWidth, iHeight, iDepth);
	delete[] data;

	return 0;
}


void CFingerDlg::OnBnClickedBtnStep1()
{//����ͼ��
 // TODO: Add your control notification handler code here
 //��ʼ�����������Ϣ
	char info[MAX_PATH] = { 0 };
	//����ͼ��
	Step_LoadBmpImage(info);
	//��ʾ���������Ϣ
	m_staticInfo.SetWindowText(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_1);
}

//�����հ�ͼƬ
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


	//3 �����ļ�
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
	_mkdir(TEMP_DIR);//������ʱ�ļ���
	_mkdir(DB_DIR);//����ָ�ƿ��ļ���
	InitFile(DB_INDEX_TXT);//���������ļ�
}

void InitFile(char * filename)
{
	FILE *index = fopen(filename, "w");//���ļ��������򴴽������Ѵ��������������
	fclose(index);//�ر��ļ�
}


void GetDatabaseInfo(char * info)
{
	//����ָ�ƿ�
	int pNo = 0;//ָ�����
	char name[MAX_PATH] = { 0 };//�Ǽ�������
	char srcFile[MAX_PATH] = { 0 };//ָ��ͼ���ļ�
	char mdlFile[MAX_PATH] = { 0 };//ָ�������ļ�
	FILE *index = fopen(DB_INDEX_TXT, "r");//�������ļ�
	while (!feof(index))
	{
		fscanf(index, "%d %s %s %s\n", &pNo, srcFile, mdlFile, name);
	}
	fclose(index);//�ر��ļ�

				  //ͳ��ָ�ƿ���Ϣ
	string s = "��ǰָ�ƿ��й���" + to_string(pNo) + "����¼";
	CString cs(s.c_str());
	//MessageBox(cs);
	sprintf(info, "��ǰָ�ƿ��й���%d����¼", pNo);

}

void CFingerDlg::OnBnClickedBtnDatabase()
{//ָ�ƿ���Ϣ��ť
 // TODO: Add your control notification handler code here
	char info[MAX_PATH] = { 0 };//��ʼ����ʾ��Ϣ
								//��ȡָ�ƿ���Ϣ
	GetDatabaseInfo(info);//��ȡָ�ƿ���Ϣ
	m_staticInfo.SetWindowText(ToWideChar(info));//��ʾָ�ƿ���Ϣ��
}

int CFingerDlg::ReadDataFromTextFile(char * srcFile, unsigned char * data, int iWidth, int iHeight)
{
	//��ԭ�ļ�
	ifstream fin(srcFile, ios::in);
	if (!fin) {
		return -1;
	}
	//��ȡ����
	int d = 0;
	for (int i = 0; i < iHeight*iWidth; i++) {
		fin >> d;
		data[i] = (unsigned char)d;
	}
	//�ر��ļ�
	fin.close();
	return 0;
}

int CFingerDlg::readDataFromTextFile(char * srcFile, float * data, int iWidth, int iHeight)
{
	//��Դ�ļ�
	ifstream fin(srcFile, ios::in);
	if (!fin) {
		return -1;
	}
	//��ȡ����

	for (int i = 0; i < iHeight*iWidth; i++) {
		fin >> data[i];
	}
	//�ر��ļ�
	fin.close();


	return 0;
}

int CFingerDlg::MidFilter(unsigned char * ucImg, unsigned char * ucDstImg, int iWidth, int iHeight)
{
	//���ͼ�����ݳ�ʼ��
	memset(ucDstImg, 0, iWidth*iHeight);
	//���������˲���ʹ��3*3����
	unsigned char*pUp, *pDown, *pImg;//����ȷ��3*3�����3��ͼ������ָ�루���ļ�ơ�����ָ�롱��
	unsigned char x[9];//3*3����ͼ����������
	for (int i = 1; i < iHeight - 1; i++) {//�����ڶ��е������ڶ���
										   //��ʼ������ָ��
		pUp = ucImg + (i - 1)*iWidth;
		pImg = ucImg + i*iWidth;
		pDown = ucImg + (i + 1)*iWidth;
		for (int j = 1; j < iWidth - 1; j++) {//�����ڶ��е������ڶ���
											  //�ƶ�����ָ��
			pUp++;
			pImg++;
			pDown++;
			//��ȡ3*3����ָ��
			x[0] = *(pUp - 1);
			x[1] = *(pImg - 1);
			x[2] = *(pDown - 1);

			x[3] = *pUp;
			x[4] = *pImg;
			x[5] = *pDown;

			x[6] = *(pUp + 1);
			x[7] = *(pImg + 1);
			x[8] = *(pDown + 1);

			//��������
			Sort(x, 9);

			//���ͼ������ȡ������ֵ
			*(ucDstImg + i*iWidth + j) = x[4];
		}
	}
	//��һ�к����һ���˲���ʹ��2*3����
	pDown = ucImg + iWidth;
	for (int j = 1; j < iWidth - 1; j++) {
		//��ȡ2*3��������
		x[0] = *(ucImg + j - 1);
		x[1] = *(ucImg + j);
		x[2] = *(ucImg + j + 1);

		x[3] = *(pDown + j - 1);
		x[4] = *(pDown + j);
		x[5] = *(pDown + j + 1);

		//��������
		Sort(x, 6);
		//���ȡ��ֵ
		*(ucDstImg + j) = x[3];
	}
	//���һ��
	pUp = ucImg + iWidth*(iHeight - 2);
	pDown = ucImg + iWidth *(iHeight - 1);
	for (int j = 1; j < iWidth - 1; j++) {
		//��ȡ2*3��������
		x[0] = *(pDown + j - 1);
		x[1] = *(pDown + j);
		x[2] = *(pDown + j + 1);
		x[3] = *(pUp + j - 1);
		x[4] = *(pUp + j);
		x[5] = *(pUp + j + 1);

		//��������
		Sort(x, 6);
		*(ucDstImg + iWidth*(iHeight - 1) + j) = x[3];
	}

	//step4:4���ǵ��˲���ʹ��2*2����
	//���Ͻǵ�
	x[0] = *(ucImg);//��ȡ2*2����
	x[1] = *(ucImg + 1);
	x[2] = *(ucImg + iWidth);
	x[3] = *(ucImg + iWidth + 1);
	Sort(x, 4);
	*(ucDstImg) = x[2];//���ȡ��ֵ

					   //���Ͻǵ�
	x[0] = *(ucImg + iWidth - 1);
	x[1] = *(ucImg + iWidth - 2);
	x[2] = *(ucImg + 2 * iWidth - 1);
	x[3] = *(ucImg + 2 * iWidth - 2);
	Sort(x, 4);
	*(ucDstImg + iWidth - 1) = x[2];


	//���½ǵ�
	x[0] = *(ucImg + (iHeight - 1)*iWidth);//��ȡ2*2��������
	x[1] = *(ucImg + (iHeight - 2)*iWidth);
	x[2] = *(ucImg + (iHeight - 1)*iWidth + 1);
	x[3] = *(ucImg + (iHeight - 2)*iWidth + 1);
	*(ucDstImg + (iHeight - 1)*iWidth) = x[2];

	//���½ǵ�
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
	//д������
	WriteBMPImgFile(dstFile, &data);

	return 0;
}

int CFingerDlg::SaveDataToImageFile(char * srcFile, char * dstFile, float * data, float scale)
{
	//��ȡͼ�����
	int iWidth, iHeight, iDepth;
	ReadBMPImageFilePara((CString)srcFile, iWidth, iHeight, iDepth);
	//�ļ�����
	CopyFile(ToWideChar(srcFile), ToWideChar(dstFile), false);
	//����ת��
	unsigned char *tmpData = new unsigned char[iWidth*iHeight];
	for (int i = 0; i < int(iWidth*iHeight); i++) {
		tmpData[i] = unsigned char((scale * data[i]));
	}

	//д������
	WriteBMPImgFile(dstFile, &tmpData);
	//�ͷ��ڴ�ռ�
	delete[] tmpData;

	return 0;
}

int CFingerDlg::WriteBMPImgFile(char * dstFileName, unsigned char ** pusImgData)
{
	FILE *fp = fopen(dstFileName, "r+b");
	if (!fp) {
		return -1;
	}
	//��ȡͼ�������Ϣ
	int imgType, iWidth, iHeight;
	int iStartPos = 0;//λͼ��������ʼ��ַ
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

	//��������д������
	unsigned char * usImgData = *pusImgData;//���������������ַ
	int iWidthInFile = 0;
	if (iWidth % 4 > 0) {
		iWidthInFile = iWidth - iWidth % 4 + 4;
	}
	else
	{
		iWidthInFile = iWidth;
	}

	for (int i = iHeight - 1; i >= 0; i--) {//����洢
		fseek(fp, iStartPos, SEEK_SET);//��λ���׵�ַ
		fwrite((usImgData + i*iWidth), 1, iWidth, fp);//д��һ������
		iStartPos += iWidthInFile;//�������׵�ַ
	}

	//�ر��ļ�
	fclose(fp);

	return 0;
}

int CFingerDlg::Step2_MidFilter(char * info)
{
	//������������ļ���
	char srcTxtFile[MAX_PATH] = { STEP_TXT_1 };//ԭ�����ļ���
	char srcImgFile[MAX_PATH] = { STEP_IMG_1 };//Դͼ�ļ���
	char dstTxtFile[MAX_PATH] = { STEP_TXT_2 };//���
	char dstImgFile[MAX_PATH] = { STEP_IMG_2 };
	//��ȡͼ�����
	int iWidth, iHeight, iDepth;
	ReadBMPImageFilePara((CString)srcImgFile, iWidth, iHeight, iDepth);//??????????��֪���ɲ�����
																	   //��ȡԴ����
	unsigned char*image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile, image1, iWidth, iHeight);

	//��ֵ�˲�

	unsigned char*image2 = new unsigned char[iWidth*iHeight];
	MidFilter(image1, image2, iWidth, iHeight);

	//����������(TXT�ļ�)
	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);
	//������ͼ��BMP�ļ�����������ʾ��
	SaveDataToImageFile(srcImgFile, dstImgFile, image2);

	//�ͷ��ڴ�ռ�

	delete[] image1;
	delete[] image2;

	sprintf(info, "�����ֵ�˲�");
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep2()//��ֵ�˲�������Ӧ�¼�
{
	//��ʼ�����������Ϣ
	char info[MAX_PATH] = { 0 };

	//��ֵ�˲�
	Step2_MidFilter(info);
	//��ʾ���������Ϣ
	m_staticInfo.SetWindowTextW(ToWideChar(info));//??????????
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_1);//��ʾ����ͼ��
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_2);//��ʾ���ͼ��
}

int CFingerDlg::HistoNormalize(unsigned char * ucImg, unsigned char * ucNormlImg, int iWidth, int iHeight)
{
	//����Դͼ�Ҷ�ֱ��ͼ
	unsigned int Histogram[256];
	memset(Histogram, 0, 256 * sizeof(int));
	for (int i = 0; i < iHeight; i++) {
		for (int j = 0; j < iWidth; j++) {
			Histogram[ucImg[i*iWidth + j]]++;
		}
	}

	//����Դͼ�ĻҶȾ�ֵ�ͷ���
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
	//�Ը����ؽ��о��⻯����
	double dMean0 = 128, dSigma0 = 128;//Ԥ��ҶȾ�ֵ�ͷ���˴�����128��
	double dCoeff = dSigma0 / dSigma;//ת��ϵ��
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
	//������������ļ���
	char srcTxtFile[MAX_PATH] = { STEP_TXT_2 };//Դ
	char srcImgFile[MAX_PATH] = { STEP_IMG_2 };
	char dstTxtFile[MAX_PATH] = { STEP_TXT_3 };//���
	char dstImgFile[MAX_PATH] = { STEP_IMG_3 };

	//��ȡͼ�����
	int iWidth, iHeight, iDepth;//ͼ���ȸ߶����
	ReadBMPImageFilePara((CString)srcImgFile, iWidth, iHeight, iDepth);
	//��ȡԴ����
	unsigned char*image1 = new unsigned char[iWidth * iHeight];
	ReadDataFromTextFile(srcTxtFile, image1, iWidth, iHeight);
	//ֱ��ͼ���⻯
	unsigned char * image2 = new unsigned char[iWidth*iHeight];
	HistoNormalize(image1, image2, iWidth, iHeight);
	//���������ݣ�TXT�ļ���
	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);
	//������ͼ��BMP�ļ�����������ʾ��
	SaveDataToImageFile(srcImgFile, dstImgFile, image2);

	//�ͷſռ�
	delete[] image1;
	delete[] image2;

	//MessageBox(L"���ֱ��ͼ���⻯");
	sprintf(info, "���ֱ��ͼ���⻯");

	return 0;
}
//ֱ��ͼ���⻯
void CFingerDlg::OnBnClickedBtnStep3()
{
	//��ʼ�����������Ϣ
	char info[MAX_PATH] = { 0 };
	Step3_Normalize(info);
	m_staticInfo.SetWindowTextW(ToWideChar(info));

	ShowImageInCtrl(m_picCtrl1, STEP_IMG_2);//��ʾ����ͼ��
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_3);
}

int CFingerDlg::ImgDirection(unsigned char * ucImg, float * fDirc, int iWidth, int iHeight)
{
	const int SEMISIZ = 7;//���򴰿�����뾶
	int dx[SEMISIZ * 2 + 1][SEMISIZ * 2 + 1];
	int dy[SEMISIZ * 2 + 1][SEMISIZ * 2 + 1];
	float fx, fy;
	//�����ʼ��
	memset(fDirc, 0, iWidth*iHeight * sizeof(float));
	for (int y = SEMISIZ + 1; y < iHeight - SEMISIZ - 1; y++) {//���б�������ȥ��Ե��
		for (int x = SEMISIZ + 1; x < iWidth - SEMISIZ - 1; x++) {
			//���б�������ȥ��Ե��
			for (int j = 0; j < SEMISIZ * 2 + 1; j++) {
				for (int i = 0; i < SEMISIZ * 2 + 1; i++) {
					int index1 = (y + j - SEMISIZ)*iWidth + x + i - SEMISIZ;
					int index2 = (y + j - SEMISIZ)*iWidth + x + i - SEMISIZ - 1;
					int index3 = (y + j - SEMISIZ - 1)*iWidth + x + i - SEMISIZ;
					dx[i][j] = int(ucImg[index1] - ucImg[index2]);
					dx[i][j] = int(ucImg[index1] - ucImg[index3]);
				}
			}

			//���㵱ǰ���صļ��߷���ֵ
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
{//�������
	const int DIR_FILTER_SIZE = 2;
	int blocksize = 2 * DIR_FILTER_SIZE + 1;
	int imgsize = iWidth * iHeight;
	float *filter = new float[blocksize*blocksize];//ʹ��5*5�˲���
	float *phix = new float[imgsize];
	float *phiy = new float[imgsize];
	float *phi2x = new float[imgsize];
	float *phi2y = new float[imgsize];
	memset(fFitDirc, 0, sizeof(float)*iWidth*iHeight);
	//����5*5��˹��ͨ�˲���ģ��

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

	//��������ص�ķ�������ֵ������ֵ
	for (int y = 0; y < iHeight; y++)
	{
		for (int x = 0; x < iWidth; x++) {
			phix[y*iWidth + x] = cos(fDirc[y*iWidth + x]);
			phiy[y*iWidth + x] = sin(fDirc[y*iWidth + x]);
		}

	}

	//���������ؽ��з����ͨ�˲�
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

			//���ۼӽ����Ϊ��ǰ���ص��µķ�������ֵ������ֵ
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

	//��ȡͼ�����
	int iWidth, iHeight, iDepth;
	ReadBMPImageFilePara((CString)srcImgFile, iWidth, iHeight, iDepth);
	//��ȡԴ����
	unsigned char*image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile, image1, iWidth, iHeight);
	//�������
	float *tmpDirections = new float[iWidth*iHeight];
	ImgDirection(image1, tmpDirections, iWidth, iHeight);
	//�����ͨ�˲�
	float *directions = new float[iWidth*iHeight];
	DircLowPass(tmpDirections, directions, iWidth, iHeight);
	//����������
	SaveDataToTextFile(dstTxtFile, directions, iWidth, iHeight);
	//������ͼ��BMP�ļ�����������ʾ��
	const int DIRECTION_SCALE = 100;
	SaveDataToImageFile(srcImgFile, dstImgFile, directions, DIRECTION_SCALE);

	delete[] image1;
	delete[] tmpDirections;
	delete[] directions;

	sprintf(info, "��ɷ������");
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep4()
{//�������

	char info[MAX_PATH] = { 0 };
	//ָ�Ƽ��߷�����㣻
	Step4_Direction(info);
	m_staticInfo.SetWindowTextW(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_3);
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_4);
}

int CFingerDlg::Frequency(unsigned char * ucImg, float * fDirection, float * fFrequency, int iWidth, int iHeight)
{
	//���ڴ�С
	const int SIZE_L = 32;
	const int SIZE_W = 16;
	const int SIZE_L2 = 16;
	const int SIZE_W2 = 8;
	//���Ҳ���ֵ��
	int peak_pos[SIZE_L];
	int peak_cnt;
	float peak_freq;
	float Xsig[SIZE_L];
	//����
	float dir = 0.0;
	float cosdir = 0.0;
	float sindir = 0.0;
	float maxPeak, minPeak;
	//�����ʼ��
	float *frequency1 = new float[iWidth * iHeight];
	memset(fFrequency, 0, sizeof(float)*iWidth*iHeight);
	memset(frequency1, 0, sizeof(float)*iWidth*iHeight);
	int x, y;
	int d, k;
	int u, v;
	for (y = SIZE_L2; y < iHeight - SIZE_L2; y++) {
		for (x = SIZE_L2; x < iWidth - SIZE_L2; x++) {
			//��ǰ���صļ��߷���
			dir = fDirection[(y + SIZE_W2)*iWidth + (x + SIZE_W2)];
			cosdir = -sin(dir);
			sindir = cos(dir);
			//�����Ե�ǰ����Ϊ���ĵ�L*W���򴰿ڵķ�ֵ����
			for (k = 0; k < SIZE_L; k++) {
				Xsig[k] = 0.0;
				for (d = 0; d < SIZE_W; d++) {
					u = (int)(x + (d - SIZE_W2)*cosdir + (k - SIZE_L2)*sindir);
					v = (int)(y + (d - SIZE_W2)*sindir + (k - SIZE_L2)*cosdir);
					//�߽�㴦��
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

			//ȷ����ֵ���б仯��Χ
			maxPeak = minPeak = Xsig[0];
			for (k = 0; k < SIZE_L; k++) {
				if (minPeak > Xsig[k]) {
					minPeak = Xsig[k];
				}
				if (maxPeak < Xsig[k]) {
					maxPeak = Xsig[k];
				}
			}

			//ȷ����ֵ��λ��
			peak_cnt = 0;
			if ((maxPeak - minPeak) > 64)
			{
				for (k = 0; k < SIZE_L; k++) {
					if ((Xsig[k - 1] < Xsig[k]) && (Xsig[k] >= Xsig[k + 1])) {
						peak_pos[peak_cnt++] = k;
					}
				}
			}

			//�����ֵ��ƽ�����
			peak_freq = 0.0;
			if (peak_cnt >= 2) {
				for (k = 0; k < peak_cnt - 1; k++) {
					peak_freq += (peak_pos[k + 1] - peak_pos[k]);
				}
				peak_freq /= peak_cnt - 1;
			}
			//���㵱ǰ���ص�Ƶ��
			if (peak_freq < 3.0 || peak_freq > 25.0) {
				frequency1[x + y*iWidth] = 0.0;
			}
			else
			{
				frequency1[x + y*iWidth] = 1.0 / peak_freq;
			}
		}
	}

	//��Ƶ�ʽ��о�ֵ�˲�
	for (y = SIZE_L2; y < iHeight - SIZE_L2; y++) {
		for (x = SIZE_L2; x < iWidth - SIZE_L2; x++) {
			k = x + y*iWidth;
			peak_freq = 0.0;
			//ʹ���Ե�ǰ����Ϊ���ĵ�5*5���򴰿ڽ��о�ֵ�˲�
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
	//������������ļ���
	char srcTxtFile_Img[MAX_PATH] = { STEP_TXT_3 };
	char srcTxtFile_Dir[MAX_PATH] = { STEP_TXT_4 };
	char srcImgFile[MAX_PATH] = { STEP_IMG_4 };
	char dstTxtFile[MAX_PATH] = { STEP_TXT_5 };
	char dstImgFile[MAX_PATH] = { STEP_IMG_5 };

	//��ȡͼ�����
	int iWidth, iHeight, iDepth;
	int flag = ReadBMPImageFilePara((CString)srcImgFile, iWidth, iHeight, iDepth);
	//��ȡͼ��Դ����
	unsigned char*image1 = new unsigned char[iWidth * iHeight];
	ReadDataFromTextFile(srcTxtFile_Img, image1, iWidth, iHeight);
	//��ȡ����Դ����
	float *dirction = new float[iWidth*iHeight];
	readDataFromTextFile(srcTxtFile_Dir, dirction, iWidth, iHeight);
	//Ƶ�ʼ���
	float *frequency = new float[iWidth*iHeight];
	Frequency(image1, dirction, frequency, iWidth, iHeight);

	//���������ݣ�TXT �ļ���
	SaveDataToTextFile(dstTxtFile, frequency, iWidth, iHeight);

	//������ͼ��
	const int FREQUENCY_SCALE = 1000;
	SaveDataToImageFile(srcImgFile, dstImgFile, frequency, FREQUENCY_SCALE);
	//�ͷ��ڴ�ռ�
	delete[] image1;
	delete[] dirction;
	delete[] frequency;
	//���ز����ɰ�״̬
	sprintf(info, "���Ƶ�ʼ���");

	return 0;
}
//Ƶ�ʼ���
void CFingerDlg::OnBnClickedBtnStep5()
{
	//��ʼ�����������Ϣ
	char info[MAX_PATH] = { 0 };

	//ָ��Ƶ�ʼ���
	Step5_Frequency(info);
	//��ʾ���������Ϣ
	m_staticInfo.SetWindowTextW(ToWideChar(info));
	//��ʾͼ��
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_4);//��ʾ����ͼ��
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_5);//��ʾ���ͼ��
}

int CFingerDlg::GetMask(unsigned char * ucImg, float * fDirection, float * fFrequency, unsigned char * ucMask, int iWidth, int iHeight)
{
	//��ֵ�ָ�
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
	//�ڶ��������׶���������̬ѧ������ԭ��
	for (k = 0; k < 4; k++) {
		//���ǰ����
		for (y = 1; y < iHeight - 1; y++) {
			for (x = 1; x < iWidth - 1; x++) {
				if (ucMask[x + y*iWidth] == 0xFF) {//ǰ����

					ucMask[x - 1 + y*iWidth] |= 0x80;
					ucMask[x + 1 + y*iWidth] |= 0x80;
					ucMask[x + (y - 1)*iWidth] |= 0x80;
					ucMask[x + (y + 1)*iWidth] |= 0x80;
				}
			}
		}
		//�жϺ�����ǰ����
		for (y = 1; y < iHeight - 1; y++) {//���б���
			for (x = 1; x < iWidth - 1; x++) {//���б���
											  //�����Ϊǰ��������ض���Ϊǰ����
				if (ucMask[x + y*iWidth]) {
					ucMask[x + y*iWidth] = 0xFF;//��Ϊǰ����
				}
			}
		}
	}

	//��������ȥ����Ե�͹����㣨������̬ѧ�ĸ�ʴԭ��
	for (k = 0; k < 12; k++) {//�ظ���ʴ��Σ������Զ���
							  //��Ǳ�����
		for (y = 1; y < iHeight - 1; y++) {//���б���
			for (x = 1; x < iWidth - 1; x++) {//���б���
											  //����������������ĸ����ڵ㶼���ΪǱ�ڱ����㣨��8λ����ֵ�ĺ�7λ����Ϊ0���Ա�ǣ�
				if (ucMask[x + y*iWidth] == 0x0)//������
				{
					ucMask[x - 1 + y*iWidth] &= 0x80;
					ucMask[x + 1 + y*iWidth] &= 0x80;
					ucMask[x + (y - 1)*iWidth] &= 0x80;
					ucMask[x + (y + 1)*iWidth] &= 0x80;
				}
			}
		}
		//�жϺ����ñ�����
		for (y = 1; y < iHeight - 1; y++) {
			for (x = 1; x < iWidth - 1; x++) {
				//ֻҪ����ǰ������������ض���Ϊ������
				if (ucMask[x + y*iWidth] != 0xFF) {//��ǰ����
					ucMask[x + y*iWidth] = 0x0;//��Ϊ�����㣨����ֵΪ0��
				}
			}
		}
	}

	return 0;
}

int CFingerDlg::Step6_Mask(char * info)
{
	char srcTxtFile_Img[MAX_PATH] = { STEP_TXT_3 };//ͼ��Դ
	char srcTxtFile_Dir[MAX_PATH] = { STEP_TXT_4 };//����Դ
	char srcTxtFile_Fre[MAX_PATH] = { STEP_TXT_5 };//Ƶ��Դ
	char srcImgFile[MAX_PATH] = { STEP_IMG_5 };//Դͼ
	char dstTxtFile[MAX_PATH] = { STEP_TXT_6 };//��������ļ���
	char dstImgFile[MAX_PATH] = { STEP_IMG_6 };//���ͼ�ļ���

											   //��ȡͼ�����
	int iWidth, iHeight, iDepth;
	ReadBMPImageFilePara((CString)srcImgFile, iWidth, iHeight, iDepth);
	//��ȡͼ��Դ����
	unsigned char*image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Img, image1, iWidth, iHeight);
	//��ȡ����Դ����
	float *direction = new float[iWidth*iHeight];
	readDataFromTextFile(srcTxtFile_Dir, direction, iWidth, iHeight);
	//��ȡƵ��Դ����
	float *frequency = new float[iWidth*iHeight];
	readDataFromTextFile(srcTxtFile_Fre, frequency, iWidth, iHeight);
	//�������
	unsigned char*mask = new unsigned char[iWidth*iHeight];
	GetMask(image1, direction, frequency, mask, iWidth, iHeight);

	//���������ݣ�TXT�ļ���
	SaveDataToTextFile(dstTxtFile, mask, iWidth, iHeight);
	//������ͼ��BMP�ļ�����������ʾ��
	SaveDataToImageFile(srcImgFile, dstImgFile, mask);

	//�ͷſռ�
	delete[] image1;
	delete[] mask;
	delete[] direction;
	delete[] frequency;
	//���ز����ɰ�״̬

	sprintf(info, "����������");

	return 0;
}

void CFingerDlg::OnBnClickedBtnStep6()
{
	//��ʼ�����������Ϣ
	char info[MAX_PATH] = { 0 };
	//ָ���������
	Step6_Mask(info);
	//��ʾ���������Ϣ
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
	float dx2 = 1.0 / (4.0*4.0);//��x�᷽��ĸ�˹���糣��
	float dy2 = 1.0 / (4.0*4.0);
	//�����ʼ��
	memset(ucImgEnhanced, 0, iWidth*iHeight);
	//Gabor�˲�
	for (j = wg2; j < iHeight - wg2; j++) {
		for (i = wg2; i < iWidth - wg2; i++) {
			//����������
			if (ucMask[i + j*iWidth] == 0) {//����Ϊ0��ʾ������
				continue;
			}
			//��ȡ��ǰ���صķ����Ƶ��
			g = fDirection[i + j*iWidth];
			f = fFrequency[i + j*iWidth];
			g += PI / 2;//��ֱ����
						//�Ե�ǰ���ؽ���Gabor�˲�
			sum = 0.0;
			for (v = -wg2; v <= wg2; v++) {
				for (u = -wg2; u <= wg2; u++) {
					x2 = -u*sin(g) + v*cos(g);//x������ת
					y2 = u*cos(g) + v*sin(g);
					sum += exp(-0.5*(x2*x2*dx2 + y2*y2*dy2)) * cos(2 * PI*x2*f)*ucImg[(i - u) + (j - v)*iWidth];
				}
			}
			//�߽�ֵ����
			if (sum > 255.0) {
				sum = 255.0;
			}if (sum < 0.0) {
				sum = 0.0;
			}
			//�õ���ǰ���ص��˲����
			ucImgEnhanced[i + j*iWidth] = (unsigned char)sum;

		}
	}
	return 0;
}

int CFingerDlg::Step7_GaborEnhance(char * info)
{
	char srcTxtFile_Img[MAX_PATH] = { STEP_TXT_3 };//ͼ��Դ
	char srcTxtFile_Dir[MAX_PATH] = { STEP_TXT_4 };//����Դ
	char srcTxtFile_Fre[MAX_PATH] = { STEP_TXT_5 };//Ƶ��Դ
	char srcTxtFile_Msk[MAX_PATH] = { STEP_TXT_6 };//Դͼ
	char srcImgFile[MAX_PATH] = { STEP_IMG_6 };//Դͼ
	char dstTxtFile[MAX_PATH] = { STEP_TXT_7 };//��������ļ���
	char dstImgFile[MAX_PATH] = { STEP_IMG_7 };//���ͼ�ļ���

	int iWidth, iHeight, iDepth;
	ReadBMPImageFilePara((CString)srcImgFile, iWidth, iHeight, iDepth);
	//��ȡͼ��Դ����
	unsigned char*image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Img, image1, iWidth, iHeight);
	//����Դ����
	float *direction = new float[iWidth*iHeight];
	readDataFromTextFile(srcTxtFile_Dir, direction, iWidth, iHeight);
	//Ƶ��Դ
	float *frequency = new float[iWidth*iHeight];
	readDataFromTextFile(srcTxtFile_Fre, frequency, iWidth, iHeight);
	//����
	unsigned char*mask = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Msk, mask, iWidth, iHeight);
	//Gabor�˲���ǿ
	unsigned char*image2 = new unsigned char[iWidth*iHeight];
	GaborEnhance(image1, direction, frequency, mask, image2, iWidth, iHeight);
	//���������ݣ�TXT�ļ���
	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);
	SaveDataToImageFile(srcImgFile, dstImgFile, image2);//��������ʾ
														//�ͷ��ڴ�ռ�
	delete[] image1;
	delete[] direction;
	delete[] frequency;
	delete[] mask;
	delete[] image2;
	//���ز����ɰ�״̬
	sprintf(info, "���Gabor�˲���ǿ");

	return 0;
}

void CFingerDlg::OnBnClickedBtnStep7()
{
	//��ʼ�����������Ϣ
	char info[MAX_PATH] = { 0 };
	//Gabor�˲���ǿ
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
		*pDest = *pStart>uThreshold ? 1 : 0;//��ֵ��
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
	char srcTxtFile[MAX_PATH] = { STEP_TXT_7 };//ͼ��Դ
	char srcImgFile[MAX_PATH] = { STEP_IMG_7 };//Դͼ
	char dstTxtFile[MAX_PATH] = { STEP_TXT_8 };//��������ļ���
	char dstImgFile[MAX_PATH] = { STEP_IMG_8 };//���ͼ�ļ���

	int iWidth, iHeight, iDepth;
	ReadBMPImageFilePara((CString)srcImgFile, iWidth, iHeight, iDepth);

	unsigned char*image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile, image1, iWidth, iHeight);

	unsigned char*image2 = new unsigned char[iWidth*iHeight];
	BinaryImg(image1, image2, iWidth, iHeight, 128);
	//����������
	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);
	BinaryToGray(image2, image1, iWidth, iHeight);
	SaveDataToImageFile(srcImgFile, dstImgFile, image1);
	delete[] image1;
	delete[] image2;
	sprintf(info, "��ɶ�ֵ��");
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep8()
{
	char info[MAX_PATH] = { 0 };
	//ͼ���ֵ��
	Step8_Binary(info);
	m_staticInfo.SetWindowTextW(ToWideChar(info));
	//��ʾͼ��
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
	//������������ļ���
	char srcTxtFile[MAX_PATH] = { STEP_TXT_8 };		//Դ�����ļ���
	char srcImgFile[MAX_PATH] = { STEP_IMG_8 };		//Դͼ�ļ���
	char dstTxtFile[MAX_PATH] = { STEP_TXT_9 };	//��������ļ���
	char dstImgFile[MAX_PATH] = { STEP_IMG_9 };	//���ͼ�ļ���

												//��ȡͼ�����
	int lWidth, lHeight, lDepth;
	ReadBMPImageFilePara((CString)srcImgFile, lWidth, lHeight, lDepth);
	//��ȡԴ����
	unsigned char *image1 = new unsigned char[lWidth*lHeight];
	ReadDataFromTextFile(srcTxtFile, image1, lWidth, lHeight);

	//ϸ��
	unsigned char *image2 = new unsigned char[lWidth*lHeight];
	Thinning(image1, image2, lWidth, lHeight, 200);

	//���������ݣ�TXT�ļ���
	SaveDataToTextFile(dstTxtFile, image2, lWidth, lHeight);

	//������ͼ��BMP�ļ�����������ʾ��
	BinaryToGray(image2, image1, lWidth, lHeight);	//��ֵͼ��ʾת��
	SaveDataToImageFile(srcImgFile, dstImgFile, image1);

	//�ͷ��ڴ�ռ�
	delete[] image1;
	delete[] image2;

	//���ز����ɰ�״̬
	sprintf(info, "���ϸ��");
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʼ�����������Ϣ
	char info[MAX_PATH] = { 0 };

	//ͼ��ϸ��
	Step9_Thinning(info);

	//��ʾ���������Ϣ
	m_staticInfo.SetWindowText(ToWideChar(info));

	//��ʾͼ��
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_8);
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_9);
}

int CFingerDlg::Extract(unsigned char * ucThinImg, unsigned char * ucMinuImg, int lWidth, int lHeight)
{
	//�������
	unsigned char * pDest = ucMinuImg;	//���ͼ����ָ��
	unsigned char * pUp, *pDown, *pImg;	//Դͼ����ָ��
	unsigned char x1, x2, x3, x4, x5, x6, x7, x8;	//���ڵ�
	unsigned char nc;	//���ڵ��кڵ�����
	int lMinuCount = 0;	//����������

						//�����ʼ����ȫ��Ϊ0����ʾ���Ƿ������㣩
	memset(pDest, 0, lWidth*lHeight);

	//����Դͼ����ȡ����ָ��
	for (int i = 1; i < lHeight - 1; i++)	//���б���
	{
		//��ʼ������ָ��
		pUp = ucThinImg + (i - 1)*lWidth;
		pImg = ucThinImg + i*lWidth;
		pDown = ucThinImg + (i + 1)*lWidth;

		for (int j = 1; j < lWidth - 1; j++) //���б���
		{
			//��������ָ��
			pUp++;
			pImg++;
			pDown++;

			//���������㣨����������ֵΪ0��
			if (!*pImg)
			{
				continue;
			}

			//��ȡ3*3���򴰿�������8���ڵ����صĻҶ�ֵ
			x6 = *(pUp - 1);
			x5 = *(pImg - 1);
			x4 = *(pDown - 1);

			x7 = *pUp;
			x3 = *pDown;

			x8 = *(pUp + 1);
			x1 = *(pImg + 1);
			x2 = *(pDown + 1);

			//ͳ�ư��ڵ��кڵ�����
			nc = x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8;

			//�������ж�
			if (nc == 1)	//�˵�
			{
				pDest[i*lWidth + j] = 1;	//���ͼ�ж�Ӧ���ص���Ϊ1����ʾ�˵㣩
				++lMinuCount;	//������������1
			}
			else if (nc == 3)	//�ֲ��
			{
				pDest[i*lWidth + j] = 3;	//���ͼ�ж�Ӧ���ص���Ϊ3����ʾ�ֲ�㣩
				++lMinuCount;	//������������1
			}
		}
	}

	return lMinuCount;
}

int CFingerDlg::Step10_MinuExtract(int & minuCount, char * info)
{
	//�����ʼ��
	minuCount = 0;//����������

				  //������������ļ���
	char srcTxtFile[MAX_PATH] = { STEP_TXT_9 };		//Դ�����ļ���
	char srcImgFile[MAX_PATH] = { STEP_IMG_9 };		//Դͼ�ļ���
	char dstTxtFile[MAX_PATH] = { STEP_TXT_10 };	//��������ļ���
	char dstImgFile[MAX_PATH] = { STEP_IMG_10 };	//���ͼ�ļ���

													//��ȡͼ�����
	int lWidth, lHeight, lDepth;
	ReadBMPImageFilePara((CString)srcImgFile, lWidth, lHeight, lDepth);


	//��ȡԴ����
	unsigned char *image1 = new unsigned char[lWidth*lHeight];
	ReadDataFromTextFile(srcTxtFile, image1, lWidth, lHeight);

	//������ȡ
	unsigned char *image2 = new unsigned char[lWidth*lHeight];
	minuCount = Extract(image1, image2, lWidth, lHeight);

	//���������ݣ�TXT�ļ���
	SaveDataToTextFile(dstTxtFile, image2, lWidth, lHeight);

	//������ͼ��BMP�ļ�����������ʾ��
	BinaryToGray(image2, image1, lWidth, lHeight);	//��ֵͼ��ʾת��
	SaveDataToImageFile(srcImgFile, dstImgFile, image1);

	//�ͷ��ڴ�ռ�
	delete[] image1;
	delete[] image2;

	//���ز����ɰ�״̬
	sprintf(info, "���������ȡ");
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʼ�����������Ϣ
	char info[MAX_PATH] = { 0 };
	//������ȡ
	Step10_MinuExtract(m_minuCount, info);
	//��ʾ���������Ϣ
	m_staticInfo.SetWindowText(ToWideChar(info));

	//��ʾͼ��
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_9);
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_10);
}

int CFingerDlg::MinuFilter(unsigned char * minuData, unsigned char * thinData, MINUTIAE * minutiaes, int & minuCount, int lWidth, int lHeight)
{
	//��1��������ϸ��ͼ�и��㷽��
	float * dir = new float[lWidth*lHeight];
	memset(dir, 0, lWidth*lHeight * sizeof(float));

	//���㼹�߷���
	ImgDirection(thinData, dir, lWidth, lHeight);

	//��2����������ͼ����ȡ����������
	unsigned char * pImg;
	unsigned char val;
	int temp = 0;
	for (int i = 1; i < lHeight - 1; i++)	//���б���
	{
		pImg = minuData + i*lWidth;
		for (int j = 1; j < lWidth - 1; j++)	//���б���
		{		//��ȡ����ͼ����
			++pImg;		//����ͼָ�����
			val = *pImg;  //����ͼ����ֵ��0 -- �������㣬 1 -- �˵㣬 3 -- �ֲ�� ��

						  //��ȡ����������
			if (val>0)
			{
				minutiaes[temp].x = j + 1;	//�����꣨��1��ʼ��
				minutiaes[temp].y = i + 1;	//�����꣨��1��ʼ��
				minutiaes[temp].theta = dir[i*lWidth + j];	//���߷���
				minutiaes[temp].type = int(val);	//���������ͣ�1--�˵㣬3--�ֲ�㣩
				++temp;	//����������ָ�����
			}
		}
	}

	delete[] dir;

	//��3����ȥ����Ե������
	minuCount = CutEdge(minutiaes, minuCount, thinData, lWidth, lHeight);

	//��4����ȥ��ë��/С��/��ϵ�α������
	//��ʼ���������
	int *pFlag = new int[minuCount];	//������飨���ֵ��0-������1-ɾ����
	memset(pFlag, 0, sizeof(int) * minuCount);

	//��������������
	int x1, x2, y1, y2, type1, type2;
	//������1����
	for (int i = 0; i < minuCount; i++)	//������1����
	{	//��ȡ������1��Ϣ
		x1 = minutiaes[i].x;
		y1 = minutiaes[i].y;
		type1 = minutiaes[i].type;	//���������ͣ�1--�˵㣬3--�ֲ�㣩

									//������2����
		for (int j = i + 1; j < minuCount; j++)	//������2����
		{	//������ɾ������
			if (pFlag[j] == 1)
			{
				continue;
			}

			//��ȡ������2��Ϣ
			x2 = minutiaes[j].x;
			y2 = minutiaes[j].y;
			type2 = minutiaes[j].type;	//���������ͣ�1--�˵㣬3--�ֲ�㣩

										//�����������
			int r = (int)sqrt(float((y1 - y2)*(y1 - y2) + (x1 - x2)*(x1 - x2)));

			//ɾ������С��������
			if (r <= 4)		//�����಻����4����Ϊ����С�������ֵ���Զ���
			{
				if (type1 == type2)		//�������������ͬ
				{
					if (type1 == 1)		//������㶼�Ƕ˵㣬���϶�Ϊ�����߻����߼�ϡ�
					{
						pFlag[i] = pFlag[j] = 1;	//ͬʱɾ������
					}
					else   //������㶼�Ƿֲ�㣬���϶�Ϊ��С�ס�
					{
						pFlag[j] = 1;	//ֻɾ����2
					}
				}
				else if (type1 == 1)	 //�����1�Ƕ˵����2�Ƿֲ�㣬���1Ϊ��ë�̡�
				{
					pFlag[i] = 1;	//ֻɾ������1
				}
				else   //�����1�Ƿֲ�����2�Ƕ˵㣬���2Ϊ��ë�̡�
				{
					pFlag[j] = 1;	//ֻɾ������2
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

		//���ݵ�ǰ
		if (x < lWidth / 2)	//���λ��ͼ�����ͼ
		{
			if (abs(lWidth / 2 - x) > abs(lHeight / 2 - y))   //���λ��ͼ�����ͼ�����
			{
				//������ͼ�в��ҵ�ǰ������ͬһ������Ƿ�������������
				while (--x >= 0)	//��һ���Ʋ���
				{
					//��������������������㣬��˵����ǰ�����㲻�Ǳ�Ե�����㣬������ɾ��
					if (ucImg[x + y*lWidth]>0)	//����ͼ����ֵ��0-�������㣬1-�˵㣬3-�ֲ�㣩
					{
						del = false;	//ɾ���������Ϊfalse
						break;	//ֹͣ��ǰ����������Ʋ��ҹ���
					}
				}
			}
			else  //���λ��ͼ�����ͼ���Ҳ�
			{
				if (y>lHeight / 2)	//���λ��ͼ�����ͼ�����²�
				{
					//������ͼ�в��ҵ�ǰ������ͬһ���²��Ƿ�������������
					while (++y<lHeight)	//��һ���Ʋ���
					{
						//������²�������������㣬��˵����ǰ�����㲻�Ǳ�Ե�����㣬������ɾ��
						if (ucImg[x + y*lWidth]>0)	//����ͼ����ֵ��0-�������㣬1-�˵㣬3-�ֲ�㣩
						{
							del = false;	//ɾ���������Ϊfalse
							break;	//ֹͣ��ǰ����������Ʋ��ҹ���
						}
					}
				}
				else // ���λ��ͼ�����ͼ�����ϲ�
				{
					//������ͼ�в��ҵ�ǰ������ͬһ���ϲ��Ƿ�������������
					while (--y >= 0)	//��һ���Ʋ���
					{
						//������ϲ�������������㣬��˵����ǰ�����㲻�Ǳ�Ե�����㣬������ɾ��
						if (ucImg[x + y*lWidth]>0)	//����ͼ����ֵ��0-�������㣬1-�˵㣬3-�ֲ�㣩
						{
							del = false;	//ɾ���������Ϊfalse
							break;	//ֹͣ��ǰ����������Ʋ��ҹ���
						}
					}
				}
			}
		}
		else   //���λ��ͼ���Ұ�ͼ
		{
			if (abs(lWidth / 2 - x) > abs(lHeight / 2 - y))	//���λ��ͼ���Ұ�ͼ���Ҳ�
			{
				//������ͼ�в��ҵ�ǰ������ͬһ���Ҳ��Ƿ�������������
				while (++x < lWidth)	//��һ�Ҳ����
				{
					//������Ҳ�������������㣬��˵����ǰ�����㲻�Ǳ�Ե�����㣬������ɾ��
					if (ucImg[x + y*lWidth]>0)	//����ͼ����ֵ��0-�������㣬1-�˵㣬3-�ֲ�㣩
					{
						del = false;	//ɾ���������Ϊfalse
						break;	//ֹͣ��ǰ����������Ʋ��ҹ���
					}
				}
			}
			else    //���λ��ͼ���Ұ�ͼ�����
			{
				if (y > lHeight / 2)	//���λ��ͼ���Ұ�ͼ�����²�
				{
					//������ͼ�в��ҵ�ǰ������ͬһ���²��Ƿ�������������
					while (++y<lHeight)	//��һ���Ʋ���
					{
						//������²�������������㣬��˵����ǰ�����㲻�Ǳ�Ե�����㣬������ɾ��
						if (ucImg[x + y*lWidth]>0)	//����ͼ����ֵ��0-�������㣬1-�˵㣬3-�ֲ�㣩
						{
							del = false;	//ɾ���������Ϊfalse
							break;	//ֹͣ��ǰ����������Ʋ��ҹ���
						}
					}
				}
				else   //���λ��ͼ���Ұ�ͼ�����ϲ�
				{
					//������ͼ�в��ҵ�ǰ������ͬһ���ϲ��Ƿ�������������
					while (--y >= 0)	//��һ���Ʋ���
					{
						//������ϲ�������������㣬��˵����ǰ�����㲻�Ǳ�Ե�����㣬������ɾ��
						if (ucImg[x + y*lWidth]>0)	//����ͼ����ֵ��0-�������㣬1-�˵㣬3-�ֲ�㣩
						{
							del = false;	//ɾ���������Ϊfalse
							break;	//ֹͣ��ǰ����������Ʋ��ҹ���
						}
					}
				}
			}
		}

		//�����ǰ�������Ǳ�Ե�����㣬������ɾ�����ڱ�������н���������Ϊ1��
		if (del)	//�����ǰ�������ɾ�����Ϊtrue���������Ϊ��Ե������
		{
			pFlag[i] = 1;	//�ڱ�������н���������Ϊ1����ʾɾ����
			continue;	//�����ж�����ṹ�е���һ��������
		}
	}

	//����������ṹ���飨�ڵ�ǰ�ṹ�����н�������Ч������ǰ�ƣ�
	int newCount = 0;	//��Ч������������ͬʱҲ����������Ч�����������±꣩
	for (int i = 0; i < minuCount; i++)
	{
		if (pFlag[i] == 0)	//�����ǰ��������Ҫ���������ֵ��0-������1-ɾ����
		{
			memcpy(&minutiaes[newCount], &minutiaes[i], sizeof(MINUTIAE));	//������ṹ���帴��
			newCount++;	//��Ч�������±���ƣ���Ч������������1��
		}
	}

	delete pFlag;
	pFlag = NULL;

	//������Ч����������
	return newCount;
}

int CFingerDlg::Step11_MinuFilter(int & minuCount, char * info)
{

	//������������ļ���
	char srcTxtFile_Minu[MAX_PATH] = { STEP_TXT_10 };//����ͼԴ�����ļ���
	char srcTxtFile_Thin[MAX_PATH] = { STEP_TXT_9 }; //ϸ��ͼԴ�����ļ���

	char srcImgFile[MAX_PATH] = { STEP_IMG_10 };	//Դ�����ļ���
	char dstTxtFile[MAX_PATH] = { STEP_TXT_11 };	//��������ļ���
	char dstImgFile[MAX_PATH] = { STEP_IMG_11 };	//���ͼ�ļ���
	char dstMdlFile[MAX_PATH] = { STEP_IMG_11_MDL };//���ģ���ļ���


													//��ȡͼ�����
	int lWidth, lHeight, lDepth;
	ReadBMPImageFilePara((CString)srcImgFile, lWidth, lHeight, lDepth);

	//��ȡ����ͼԴ����
	unsigned char *image1 = new unsigned char[lWidth*lHeight];
	ReadDataFromTextFile(srcTxtFile_Minu, image1, lWidth, lHeight);

	//��ȡϸ��ͼԴ����
	unsigned char * thin = new unsigned char[lWidth*lHeight];
	ReadDataFromTextFile(srcTxtFile_Thin, thin, lWidth, lHeight);


	//��������
	MINUTIAE * minutiaes = new MINUTIAE[minuCount];
	memset(minutiaes, sizeof(MINUTIAE), minuCount);
	MinuFilter(image1, thin, minutiaes, minuCount, lWidth, lHeight);

	//����ģ���ļ�
	SaveMinutiae(minutiaes, minuCount, dstMdlFile);

	//���ɽ��ͼ��
	unsigned char *image2 = new unsigned char[lWidth*lHeight];
	memset(image2, 0, lWidth*lHeight);
	for (int i = 0; i < minuCount; i++)
	{
		image2[(minutiaes[i].y - 1)*lWidth + (minutiaes[i].x - 1)] = 0xff;
	}

	//���������ݣ�TXT�ļ���
	SaveDataToTextFile(dstTxtFile, image2, lWidth, lHeight);

	//������ͼ��BMP�ļ�����������ʾ��
	SaveDataToImageFile(srcImgFile, dstImgFile, image2);

	//�ͷ��ڴ�ռ�
	delete[] image1;
	delete[] thin;
	delete[] minutiaes;
	delete[] image2;

	//���ز����ɰ�״̬
	sprintf(info, "�����������");
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʼ�����������Ϣ
	char info[MAX_PATH] = { 0 };
	//������ȡ
	Step11_MinuFilter(m_minuCount, info);

	//��ʾ���������Ϣ
	m_staticInfo.SetWindowText(ToWideChar(info));

	//��ʾͼ��
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_10);
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_11);
}

int CFingerDlg::SaveMinutiae(MINUTIAE * minutiaes, int count, char * fileName)
{
	//���ļ���������д�뷽ʽ��
	FILE *fp = fopen(fileName, "wb");
	if (!fp)
	{
		return -1;
	}

	//������������Ľṹ����������д���ļ�
	const static int TemplateFileFlag = 0x3571027f;
	fwrite(&TemplateFileFlag, sizeof(int), 1, fp);	//д������ģ���ļ����
	fwrite(&count, sizeof(int), 1, fp);	//д������������
	for (int i = 0; i < count; i++)	//��һд������������
	{
		fwrite(&minutiaes[i], sizeof(MINUTIAE), 1, fp);	//��������ṹ����д��
	}

	//�ر��ļ�
	fclose(fp);
	return 0;
}

int CFingerDlg::GetNewIndexInDB()
{
	//��index�ļ��ж�ȡ���һ����¼���
	int sNo = 0;
	char name[MAX_PATH] = { 0 }, srcFile[MAX_PATH] = { 0 }, mdlFile[MAX_PATH] = { 0 };
	FILE *index = fopen(DB_INDEX_TXT, "r");
	while (!feof(index))
	{
		fscanf(index, "%d %s %s %s\n", &sNo, srcFile, mdlFile, name);
	}
	fclose(index);

	//�����±��
	sNo = sNo + 1;

	//�����±��
	return sNo;
}

int CFingerDlg::Step12_Enroll(char * userName, char * info)
{

	//���������ļ���
	char srcImgFile[MAX_PATH] = { STEP_IMG_1 };	//Դͼ�ļ���
	char srcMdlFile[MAX_PATH] = { STEP_IMG_11_MDL };	//ģ���ļ���

														//������ݿ�����ָ�Ƽ�¼���
	int sNo = GetNewIndexInDB();

	//�����û���/Դͼ�ļ���/Դģ���ļ�������Ҫ�������ݿ��ָ�ƵǼ���Ϣ
	char regName[MAX_PATH] = { 0 };	//�Ǽ�������
	char dstImgFile[MAX_PATH] = { 0 };	//Դͼ�ļ�
	char dstMdlFile[MAX_PATH] = { 0 };	//Դģ���ļ�
	sprintf(regName, userName);		//ֱ�Ӹ��ƽ�����������
	sprintf(dstImgFile, "%s%d.bmp", DB_DIR, sNo);	//�������ݿ��ļ����ڣ��Ա������
	sprintf(dstMdlFile, "%s%d.mdl", DB_DIR, sNo);	//�������ݿ��ļ����ڣ��Ա������

													//����ԭʼͼ��
	CopyFile(ToWideChar(srcImgFile), ToWideChar(dstImgFile), false);

	//����ģ���ļ�
	CopyFile(ToWideChar(srcMdlFile), ToWideChar(dstMdlFile), false);

	//ָ�ƵǼ���Ϣд�����ݿ������ļ�
	FILE *index = fopen(DB_INDEX_TXT, "a");	//׷��ģʽд��
	fprintf(index, "%d %s %s %s\n", sNo, dstImgFile, dstMdlFile, regName);
	fclose(index);

	sprintf(info, "����������.");
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


	//�������
	const int MAX_NEIGHBOR_EACH = 10;	//ÿ����������ౣ��10������������
	int x1, x2, y1, y2;
	int *pFlag = new int[minuCount];	//���ڱ�����飨���ֵ��0-�����ڣ�1-���ڣ�

										//��������������
	for (int i = 0; i < minuCount; i++)
	{
		//��ȡ��ǰ��������Ϣ
		x1 = minutiae[i].x;
		y1 = minutiae[i].y;

		//��ʼ����ǰ����������ڱ������
		memset(pFlag, 0, sizeof(int)*minuCount);	//��ʼ��Ϊȫ0�������ڣ�
		pFlag[i] = 1;	//��������Ϊ�����ڡ�

						//Ϊ��ǰ�����㴴������ʼ������������ṹ����
		minutiae[i].neibors = new NEIGHBOR[MAX_NEIGHBOR_EACH];	//��������������ṹ����

		if (minutiae[i].neibors == NULL)
		{
			return -1;
		}
		memset(minutiae[i].neibors, 0, sizeof(NEIGHBOR)*MAX_NEIGHBOR_EACH);	//��ʼ������

																			//���Һͱ���10������������
		for (int neighborNo = 0; neighborNo < MAX_NEIGHBOR_EACH; neighborNo++)	//�ظ�10��
		{
			//��ʼ����С���Ͷ�Ӧ���������±�
			int minDistance = 1000;	//��С���
			int minNo = 0;	//��С����Ӧ�������±�

							//��������������֮�������Ĳ�����������
			for (int j = 0; j < minuCount; j++)	//ÿ�ζ���������������
			{
				//�������ҵ�������������
				if (pFlag[j] == 1)	//�����ֵ��0-�����ڣ�1-���ڣ�
				{
					continue;
				}

				//��ȡ������2����Ϣ
				x2 = minutiae[j].x;
				y2 = minutiae[j].y;

				//����������
				int r = (int)sqrt(float((y1 - y2)*(y1 - y2) + (x1 - x2)*(x1 - x2)));

				//������С���
				if (r < minDistance)
				{
					minNo = j;
					minDistance = r;
				}
			}

			//������ҽ��
			pFlag[minNo] = 1;	//���ҵ�������Ĳ�����������ı������Ϊ�����ڡ�
			minutiae[i].neibors[neighborNo].x = minutiae[minNo].x;	//�����꣨�����꣩
			minutiae[i].neibors[neighborNo].y = minutiae[minNo].y;	//�����꣨�����꣩
			minutiae[i].neibors[neighborNo].type = minutiae[minNo].type;	//���������ͣ�1-�˵㣬3-�ֲ�㣩
			minutiae[i].neibors[neighborNo].Theta = Angle2Points(minutiae[minNo].x, minutiae[minNo].y, x1, y1); //�������߽Ƕȣ����ȣ�
			minutiae[i].neibors[neighborNo].Theta2Ridge = minutiae[minNo].theta - minutiae[i].theta;	//���㼫�޷���нǣ����ȣ�
			minutiae[i].neibors[neighborNo].ThetaThisNibor = minutiae[minNo].theta;	//���ڵ�ļ��߷��򣨻��ȣ�
			minutiae[i].neibors[neighborNo].distance = minDistance;	//�������
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

	const int MAX_SIMILAR_PAIR = 100;	//��ౣ��100���������������
	const int MAX_NEIGHBOR_EACH = 10;	//ÿ����������ౣ��10������������

										//�������������ڹ�ϵ
	BuildNabors(minutiae1, count1);
	BuildNabors(minutiae2, count2);

	//��ʼ��������ƥ�����������������ԣ�
	int similarPair[MAX_SIMILAR_PAIR][2];
	memset(similarPair, 0, 100 * 2 * sizeof(int));

	//ѡ���׼�����Ͳο�����
	MINUTIAE *baseMinutiae;	//��׼���������飨����������٣�
	MINUTIAE *refMinutiae;	//�ο����������飨��������϶ࣩ
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

	//��������������С������㡱�����Ϊ�ġ��㡱�����硰��׼��/�ο���/���ڵ�/���Ƶ㡱��
	NEIGHBOR *baseNeighbors = NULL;	//��׼������ڵ�ָ��
	NEIGHBOR *refNeighbors = NULL;	//�ο�������ڵ�ָ��
	int similarMinutiae = 0;	//���Ƶ�������������±꣩
	float baseTheta, refTheta;	//��׼����Ͳο�����

								//������ƥ�䣨�ڲο���������Ѱ����ÿһ����׼���Ӧ�������ƵĲο��㣩
	for (int i = 0; i < baseAccount; i++)	//��һ�����ο�������
	{
		//��ȡ��ǰ��׼����Ϣ
		baseNeighbors = baseMinutiae[i].neibors;	//��׼������ڵ�����
		baseTheta = baseMinutiae[i].theta;	//��׼��ļ��߷���

											//�ڲο���������Ѱ���굱ǰ��׼�������ƵĲο���
		int refSimilarNo = 0;
		int maxSimilarNeibors = 0;
		for (int j = 0; j < refAccount; j++)	//��һ�����ο�������
		{
			//�����뵱ǰ��׼�����Ͳ�ͬ�Ĳο���
			if (refMinutiae[j].type != baseMinutiae[i].type)
			{
				continue;
			}

			//��ȡ��ǰ�ο�����Ϣ
			refNeighbors = refMinutiae[j].neibors;	//�ο�������ڵ�����
			refTheta = refMinutiae[j].theta;	//�ο���ļ��߷���

												//ͨ�����������ڵ�����
			int thisSimilarNeigbors = 0;	//�������ڵ�������ʼ��Ϊ0
											//��һ������ǰ��׼������ڵ�����
			for (int m = 0; m < MAX_NEIGHBOR_EACH; m++)
			{
				//�ڵ�ǰ�ο�������ڵ������в����뵱ǰ��׼��ĵ�ǰ���ڵ����Ƶ����ڵ�
				for (int n = 0; n < MAX_NEIGHBOR_EACH; n++)	//��һ������ǰ�ο�������ڵ�����
				{
					//�������Ͳ�ͬ�����ڵ�
					if (baseNeighbors[m].type != refNeighbors[n].type)
					{
						continue;
					}

					//�����������ڵ�֮��ľ����Ͳ�ͬ�ǶȲ���ȣ�
					int dist = abs(int(baseNeighbors[m].distance - refNeighbors[n].distance));
					float theta1 = abs(float((baseNeighbors[m].Theta - baseTheta) - (refNeighbors[n].Theta - refTheta)));
					float theta2 = abs(float(baseNeighbors[m].Theta2Ridge - refNeighbors[n].Theta2Ridge));
					float theta3 = abs(float((baseNeighbors[m].Theta - baseNeighbors[m].ThetaThisNibor) - (refNeighbors[n].Theta - refNeighbors[n].ThetaThisNibor)));

					//��������С��ָ����ֵ���˴�ȡ4�����ҽǶȲ��С��ָ����ֵ���˴�ȡ0.15��,����Ϊ���������ڵ�����
					if (dist<4 && theta1<0.15f && theta2<0.15f && theta3<0.15f)
					{
						++thisSimilarNeigbors;	//�������ڵ�����1
						break;	//ת��ǰ��׼�����һ�����ڵ��������
					}
				}
			}

			//���3���������ڵ����ƣ�����Ϊ��ǰ��׼���뵱ǰ��ǰ�ο������ƣ�����ƥ����
			if ((thisSimilarNeigbors >= MAX_NEIGHBOR_EACH * 3 / 10) && (similarMinutiae<MAX_SIMILAR_PAIR))
			{
				similarPair[similarMinutiae][0] = i;	//���浱ǰ��׼���±�
				similarPair[similarMinutiae][1] = refSimilarNo;	//���浱ǰ�ο����±�
				++similarMinutiae;	//���Ƶ��������һ�������±���ƣ�
			}
		}
	}

	//��������ƥ�����ƶ�
	float similarity = similarMinutiae / 8.0f;
	//�����������������С��ָ��������ֵ���˴�ȡ2��������Ϊ����ָ����ȫ��ƥ��
	similarity = similarity < 2 ? 0.0f : similarity;	//�߽�ֵ����
															//���������������������ָ��������ֵ���˴�ȡ8��������Ϊ����ָ����ȫƥ��
	similarity = similarity > 10 ? 1.0f : similarity;	//�߽�ֵ����

															//��������ƥ�����ƶ�
	return similarity;
}

int CFingerDlg::ReadMinutiae(char * fileName, MINUTIAE ** minutiae)
{


	//���ļ��������ƶ�ȡ��ʽ��
	FILE *fp = fopen(fileName, "rb");
	if (!fp)
	{
		return -1;
	}

	//��һ�����ȡ����������Ľṹ������
	const static int TemplateFileFlag = 0x3571027f;
	int flag;
	fread(&flag, sizeof(int), 1, fp);	//��ȡ����ģ���ļ����
	if (flag != TemplateFileFlag)
	{
		return -2;
	}

	int account;
	fread(&account, sizeof(int), 1, fp);	//��ȡ����������

	*minutiae = new MINUTIAE[account];	//����������ṹ����
	if (minutiae == NULL)
	{
		return -3;
	}

	for (int i = 0; i < account; i++)	//��һ��ȡ����������
	{
		fread(&((*minutiae)[i]), sizeof(MINUTIAE), 1, fp);	//�����ȡ������ṹ
	}

	//�ر��ļ�
	fclose(fp);
	return account;
}

int CFingerDlg::Step12_Match(char * info)
{
	//������������ļ���
	char srcImgFile[MAX_PATH] = { STEP_IMG_1 };	//Դͼ�ļ���
	char srcMdlFile[MAX_PATH] = { STEP_IMG_11_MDL };	//ģ���ļ���
	char dstImgFile[MAX_PATH] = { STEP_IMG_12 };	//���ͼ�ļ���

													//��ȡͼ�����
	int lWidth, lHeight, lDepth;
	ReadBMPImageFilePara((CString)srcImgFile, lWidth, lHeight, lDepth);

	//��ȡָ����������
	MINUTIAE *minu = NULL;
	int minuAccount = ReadMinutiae(srcMdlFile, &minu);

	//����ƥ�䣨�˴�����������������ƥ�䣩
	float similar = MinuSimilarity(lWidth, lHeight, minu, minuAccount, minu, minuAccount);

	//�ͷ��ڴ�ռ�
	delete[] minu;

	//����ƥ����ͼ��
	CopyFile(ToWideChar(srcImgFile), ToWideChar(dstImgFile), false);

	//���ز����ɰ�״̬
	const float SIMILAR_THRED = 0.1;	//ƥ�����ƶ���ֵ��С����ֵ����Ϊ��ƥ�䣩
	if (similar < SIMILAR_THRED)
	{
		sprintf(info, "ƥ��ʧ��");
		return -3;
	}

	sprintf(info, "ƥ��ɹ������ƶ�[%.2f].", similar);
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep12b()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ʼ�����������Ϣ
	char info[MAX_PATH] = { 0 };

	Step12_Match(info);	//����ƥ��
						//Step12_Identify(info);	//ָ��ʶ��

						//��ʾ���������Ϣ
	m_staticInfo.SetWindowText(ToWideChar(info));

	//��ʾͼ��
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_1);	//��ʾԭʼͼ��
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_12);	//��ʾָ��ͼ������
}

bool CFingerDlg::EmptyDB()
{
	//���ļ�
	char indexFile[MAX_PATH] = { DB_INDEX_TXT };	//ָ�ƿ������ļ�
	FILE *pFile = fopen(indexFile, "r");
	if (!pFile)	//�������ļ������ڻ��쳣����ָ�ƿ�Ϊ��
	{
		return true;
	}

	//�ж�ָ�ƿ��Ƿ�Ϊ�գ������ļ������Ƿ�Ϊ�գ�
	int size = filelength(fileno(pFile));	//�ļ����ȣ����ֽ�Ϊ��λ��
	bool bEmpty = (size < 1) ? true : false;	//�������ļ�����Ϊ�գ���ָ�ƿ�Ϊ��

												//�ر��ļ�
	fclose(pFile);

	//�����жϽ��
	return bEmpty;
}

int CFingerDlg::Step12_Identify(char * info)
{
	//������������ļ���
	char srcImgFile[MAX_PATH] = { STEP_IMG_1 };	//Դͼ�ļ���
	char srcMdlFile[MAX_PATH] = { STEP_IMG_11_MDL };	//Դͼָ�������ļ���
	char dstImgFile[MAX_PATH] = { STEP_IMG_12 };	//���ͼ�ļ���
	char dstMdlFile[MAX_PATH] = { 0 };	//���ͼָ�������ļ���

										//ָ�ƿ�Ԥ�죨�ж�ָ�ƿ��Ƿ�Ϊ�գ�
	EmptyDB();

	//��ȡͼ�����
	int lWidth, lHeight, lDepth;
	ReadBMPImageFilePara((CString)srcImgFile, lWidth, lHeight, lDepth);
	//��ȡָ����������
	MINUTIAE *minu1 = NULL, *minu2 = NULL;
	int minuAccount1 = 0, minuAccount2 = 0;
	minuAccount1 = ReadMinutiae(srcMdlFile, &minu1);

	//����ʶ��
	int id = 0;
	char name[MAX_PATH] = { 0 }, src[MAX_PATH] = { 0 }, mdl[MAX_PATH] = { 0 };
	float maxSimilar = -1;
	int maxID = -1;
	char maxName[MAX_PATH] = { 0 }, maxSrc[MAX_PATH] = { 0 };

	FILE *index = fopen(DB_INDEX_TXT, "r");	//��ָ�ƿ������ļ�

	while (!feof(index))
	{
		//��ȡָ�Ƽ�¼��Ϣ��ָ�Ʊ��/ָ��ͼ���ļ���/����ģ���ļ���/�Ǽ���������
		fscanf(index, "%d %s %s %s\n", &id, src, mdl, name);
		sprintf(dstMdlFile, mdl);

		//������ģ���ļ��ж�ȡָ������
		minuAccount2 = ReadMinutiae(dstMdlFile, &minu2);

		//����ƥ��
		float similar = MinuSimilarity(lWidth, lHeight, minu1, minuAccount1, minu2, minuAccount2);

		//�������ƶ���ߵ�ָ�Ƽ�¼��Ϣ
		if (similar>maxSimilar)
		{
			maxSimilar = similar;
			maxID = id;
			sprintf(maxName, name);
			sprintf(maxSrc, src);
		}
	}

	fclose(index);	//�ر��ļ�

					//�ͷ��ڴ�ռ�
	delete minu1;
	delete minu2;

	//����ʶ����
	const float SIMILAR_THRED = 0.1;	//ƥ�����ƶ���ֵ��С����ֵ����Ϊ��ƥ�䣩
	if (maxID<0 || maxSimilar<SIMILAR_THRED)
	{
		sprintf(info, "ʶ��ʧ��.");
		MessageBox(L"ʶ��ʧ��");
		return -2;
	}
	CopyFile(ToWideChar(maxSrc), ToWideChar(dstImgFile), false);	//����ʶ����ͼ��
	sprintf(info, "ʶ��ɹ�. ʶ����������[%s],Ŀ��ָ��[%s]�����ƶȣ�[%.2f].", maxName, maxSrc, maxSimilar);

	return 0;
}

int CFingerDlg::Enroll(char * regName, char * srcImgFile, char * outImgFile, char * info, bool bSaveImg)
{
	//��0���������м����ļ���
	//�м��������ļ���
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

	//�м���ͼ���ļ���
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

	//ָ������ģ���ļ���
	char stepMdlFile11[MAX_PATH] = { STEP_IMG_11_MDL };

	//��1����ͼ�����룬��ȡԴͼ���ݺͲ�����Ϣ
	int lWidth, lHeight, lDepth;
	ReadBMPImageFilePara((CString)srcImgFile, lWidth, lHeight, lDepth);
	unsigned char *image1 = new unsigned char[lWidth*lHeight];
	unsigned char *image2 = new unsigned char[lWidth*lHeight];
	ReadBMPImgFileData((CString)srcImgFile, image1);	//��ȡԴͼ����
	memset(image2, 0, lWidth*lHeight);	//���ͼ���ʼ��
	if (bSaveImg)
	{
		CopyFile(ToWideChar(srcImgFile), ToWideChar(stepImgFile1), false);
		SaveDataToTextFile(stepTxtFile1, image1, lWidth, lHeight);
	}

	//��2������ֵ�˲�
	MidFilter(image1, image2, lWidth, lHeight);	//��ֵ�˲�
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile2, image2);
		SaveDataToTextFile(stepTxtFile2, image2, lWidth, lHeight);
	}

	//��3����ֱ��ͼ���⻯
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//�Ե�2���˲����ΪԴͼ����
	HistoNormalize(image1, image2, lWidth, lHeight);	//ֱ��ͼ���⻯
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile3, image2);
		SaveDataToTextFile(stepTxtFile3, image2, lWidth, lHeight);
	}

	//��4�����������
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//�Ե�3�����⻯���ΪԴͼ����
	float *tmpDirection = new float[lWidth*lHeight];
	float *direction = new float[lWidth*lHeight];
	ImgDirection(image1, tmpDirection, lWidth, lHeight);	//�������
	DircLowPass(tmpDirection, direction, lWidth, lHeight);	//�����ͨ�˲�
	if (bSaveImg)
	{
		const int DIRECTION_SCALE = 100;	// ������ת�������������ڽ����ʾ��
		SaveDataToImageFile(srcImgFile, stepImgFile4, direction, DIRECTION_SCALE);
		SaveDataToTextFile(stepTxtFile4, direction, lWidth, lHeight);
	}
	delete[] tmpDirection;

	//��5����Ƶ�ʼ���
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//�Ե�3�����⻯���ΪԴͼ����
	float *frequency = new float[lWidth*lHeight];
	Frequency(image1, direction, frequency, lWidth, lHeight);	//Ƶ�ʼ���
	if (bSaveImg)
	{
		const int FREQUENCY_SCALE = 1000;	// Ƶ�ʽ��ת�������������ڽ����ʾ��
		SaveDataToImageFile(srcImgFile, stepImgFile5, frequency, FREQUENCY_SCALE);
		SaveDataToTextFile(stepTxtFile5, frequency, lWidth, lHeight);
	}

	//��6�����������
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//�Ե�3�����⻯���ΪԴͼ����
	unsigned char * mask = new unsigned char[lWidth*lHeight];
	GetMask(image1, direction, frequency, mask, lWidth, lHeight);	//�������
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile6, mask);
		SaveDataToTextFile(stepTxtFile6, mask, lWidth, lHeight);
	}

	//��7����Gabor�˲���ǿ
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//�Ե�3�����⻯���ΪԴͼ����
	GaborEnhance(image1, direction, frequency, mask, image2, lWidth, lHeight);	//��ǿ
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile7, image2);
		SaveDataToTextFile(stepTxtFile7, image2, lWidth, lHeight);
	}
	delete[] direction;
	delete[] frequency;
	delete[] mask;

	//��8������ֵ��
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//�Ե�7��Gabor�˲����ΪԴͼ����
	BinaryImg(image1, image2, lWidth, lHeight, 128);	//��ֵ��
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile8, image2);
		SaveDataToTextFile(stepTxtFile8, image2, lWidth, lHeight);
	}

	//��9����ϸ��
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//�Ե�8����ֵ�����ΪԴͼ����
	Thinning(image1, image2, lWidth, lHeight, 128);	//ϸ��
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile9, image2);
		SaveDataToTextFile(stepTxtFile9, image2, lWidth, lHeight);
	}
	unsigned char *thin = new unsigned char[lWidth*lHeight];
	memcpy(thin, image2, sizeof(unsigned char)*lWidth*lHeight);		//����ϸ�����

																	//��10����������ȡ
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//�Ե�9��ϸ�����ΪԴͼ����
	int minuCount = Extract(image1, image2, lWidth, lHeight);	//������ȡ
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile10, image2);
		SaveDataToTextFile(stepTxtFile10, image2, lWidth, lHeight);
	}

	//��11������������
	memcpy(image1, image2, sizeof(unsigned char)*lWidth*lHeight);	//�Ե�10��������ȡ���ΪԴͼ����
	MINUTIAE *minutiaes = new MINUTIAE[minuCount];
	memset(minutiaes, sizeof(MINUTIAE), minuCount);
	MinuFilter(image1, thin, minutiaes, minuCount, lWidth, lHeight);	//��������
	delete[] thin;
	SaveMinutiae(minutiaes, minuCount, stepMdlFile11);	//�������������ļ�
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

	//��12�����������
	int sNo = GetNewIndexInDB();	//��ȡ���ݿ���ָ�Ƽ�¼���
	char dbImgFile[MAX_PATH] = { 0 };	//���ݿ���Դͼ�ļ���
	char dbMdlFile[MAX_PATH] = { 0 };	//���ݿ���ģ���ļ���
	sprintf(dbImgFile, "%s%d.bmp", DB_DIR, sNo);	//����Դͼ�ļ������������ݿ��ļ����ڣ��Ա��������
	sprintf(dbMdlFile, "%s%d.mdl", DB_DIR, sNo);	//����ģ���ļ������������ݿ��ļ����ڣ��Ա��������

	if (minuCount>0)
	{
		//����ԭʼָ��ͼ��
		CopyFile(ToWideChar(srcImgFile), ToWideChar(dbImgFile), false);

		//����ָ������ģ���ļ�
		CopyFile(ToWideChar(stepMdlFile11), ToWideChar(dbMdlFile), false);

		//ָ�ƵǼ���Ϣд�����ݿ������ļ�
		FILE *index = fopen(DB_INDEX_TXT, "a");	//׷��ģʽд��
		fprintf(index, "%d %s %s %s\n", sNo, dbImgFile, dbMdlFile, regName);
		fclose(index);
	}

	//�ͷſռ�
	delete[] image1;
	delete[] image2;
	delete[] minutiaes;
	MessageBox(L"ָ�ƵǼǳɹ�");
	sprintf(info, "ָ�ƵǼǳɹ�");
	return 0;
}

void CFingerDlg::OnBnClickedBtnAddImage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ʼ�����������Ϣ
	char info[MAX_PATH] = { 0 };

	//��ȡ�����������ݣ��Ǽ���������
	UpdateData(true);
	if (m_name.GetLength() == 0) {
		//MessageBox(_T("����������"), _T("��ʾ"));//��ʾ��Ϣ
		MessageBox(L"����������");
		return;
	}
	//�Ľ��㣺��������ѡ��Ҫ�򿪵��ļ�
	//ѡ��ͼ��
	//char *srcImgFile= "D:\\fingerimages\\L01_01.bmp";	

	//����ͼ��
	char*srcImgFile = openImagePath();

	//ָ�ƵǼ�
	bool bSaveImg = false;	//�Ƿ񱣴��м���
	char *outImgFile = new char[MAX_PATH];
	//ָ���������ͼ���ļ���
	Enroll(ToChar(m_name.GetBuffer()), srcImgFile, outImgFile, info, bSaveImg);	//ָ�ƵǼ�			
																				//MessageBox(_T("�Ǽǳɹ�"), _T("��ʾ"));//��ʾ��Ϣ 
																				//MessageBox(L"�Ǽǳɹ�");
	m_staticInfo.SetWindowText(ToWideChar(info));
	//��ʾͼ��
	ShowImageInCtrl(m_picCtrl1, srcImgFile);	//��ʾԭʼָ��ͼ��
												//ShowImageInCtrl(m_picCtrl2, outImgFile);	//��ʾʶ����ͼ��

}

void CFingerDlg::OnBnClickedBtnRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ʼ�����������Ϣ
	if (liu == 0) {
		MessageBox(_T("δ�����ɼ���"), _T("��ʾ"));
		return;
	}
	char info[MAX_PATH] = { 0 };

	//��ȡ�����������ݣ��Ǽ���������
	UpdateData(true);

	//ʵʱ�ɼ�ͼ��,���û�ָ������

	//char*srcImgFile = NULL;
	char *srcImgFile = new char[MAX_PATH];
	srcImgFile = saveImagePath();
	m_zkfpEng.SaveBitmap(ToWideChar(srcImgFile));

	//ָ�ƵǼ�
	bool bSaveImg = false;	//�Ƿ񱣴��м���
	char *outImgFile = new char[MAX_PATH];	//ָ���������ͼ���ļ���
	Enroll(ToChar(m_name.GetBuffer()), srcImgFile, outImgFile, info, bSaveImg);	//ָ�ƵǼ�

																				//��ʾ���������Ϣ
	m_staticInfo.SetWindowText(ToWideChar(info));

	//��ʾͼ��
	ShowImageInCtrl(m_picCtrl1, srcImgFile);	//��ʾԭʼָ��ͼ��
	ShowImageInCtrl(m_picCtrl2, "empty.bmp");	//��ʾʶ����ͼ��
}

int CFingerDlg::Identify(char * srcImgFile, char * outImgFile, char * info, bool bSaveImg)
{//��0���������м����ļ���
 //�м��������ļ���
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
	//�м���ͼ���ļ���
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

	//ָ������ģ���ļ���
	char stepMdlFile11[MAX_PATH] = { STEP_IMG_11_MDL };
	//ָ�ƿ�Ԥ�죨�ж�ָ�ƿ��Ƿ�Ϊ�գ�
	EmptyDB();
	//��1����ͼ�����룬��ȡԴͼ���ݺͲ�����Ϣ
	int iWidth, iHeight, iDepth;
	ReadBMPImageFilePara((CString)srcImgFile, iWidth, iHeight, iDepth);//��ȡԴͼ������Ϣ
	unsigned char*image1 = new unsigned char[iWidth*iHeight];
	unsigned char*image2 = new unsigned char[iWidth*iHeight];
	ReadBMPImgFileData((CString)srcImgFile, image1);//��ȡԴͼ����
	memset(image2, 0, iWidth*iHeight);//���ͼ��ʼ��
	if (bSaveImg) {
		CopyFile(ToWideChar(srcImgFile), ToWideChar(stepImgFile1), false);
		SaveDataToTextFile(stepTxtFile1, image1, iWidth, iHeight);
	}

	//��2������ֵ�˲�
	MidFilter(image1, image2, iWidth, iHeight);//��ֵ�˲�
	if (bSaveImg) {
		SaveDataToImageFile(srcImgFile, stepImgFile2, image2);
		SaveDataToTextFile(stepTxtFile2, image2, iWidth, iHeight);
	}

	//��3����ֱ��ͼ���⻯
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//�Ե�2���˲����ΪԴͼ����
	HistoNormalize(image1, image2, iWidth, iHeight);//ֱ��ͼ���⻯
	if (bSaveImg) {
		SaveDataToImageFile(srcImgFile, stepImgFile3, image2);
		SaveDataToTextFile(stepImgFile3, image2, iWidth, iHeight);
	}

	//��4�����������
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//�Ե�3�����⻯���ΪԴͼ����
	float*tmpDirection = new float[iWidth*iHeight];
	float*direction = new float[iWidth*iHeight];
	ImgDirection(image1, tmpDirection, iWidth, iHeight);//�������
	DircLowPass(tmpDirection, direction, iWidth, iHeight);//�����ͨ�˲�
	if (bSaveImg) {
		const int DIRECTION_SCALE = 100;//������ת�������������ڽ����ʾ��
		SaveDataToImageFile(srcImgFile, stepImgFile4, direction, DIRECTION_SCALE);
		SaveDataToTextFile(stepTxtFile4, direction, iWidth, iHeight);
	}
	delete[] tmpDirection;

	//��5����Ƶ�ʼ���
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);// �Ե�3�����⻯���ΪԴͼ����
	float*frequency = new float[iWidth*iHeight];
	Frequency(image1, direction, frequency, iWidth, iHeight);//Ƶ�ʼ���
	if (bSaveImg) {
		const int FREQUENCY_SCALE = 1000;//Ƶ�ʽ��ת�������������ڽ����ʾ��
		SaveDataToImageFile(srcImgFile, stepImgFile5, frequency, FREQUENCY_SCALE);
		SaveDataToTextFile(stepImgFile5, frequency, iWidth, iHeight);
	}


	//��6��:�������
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);
	unsigned char*mask = new unsigned char[iWidth*iHeight];
	GetMask(image1, direction, frequency, mask, iWidth, iHeight);//�������
	if (bSaveImg) {
		SaveDataToImageFile(srcImgFile, stepImgFile6, mask);
		SaveDataToTextFile(stepImgFile6, mask, iWidth, iHeight);
	}

	//��7����Gabor�˲���ǿ
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);
	GaborEnhance(image1, direction, frequency, mask, image2, iWidth, iHeight);//��ǿ
	if (bSaveImg) {
		SaveDataToImageFile(srcImgFile, stepImgFile7, image2);
		SaveDataToTextFile(stepImgFile7, image2, iWidth, iHeight);
	}
	delete[] direction;
	delete[] frequency;
	delete[] mask;
	//��8������ֵ��
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);
	BinaryImg(image1, image2, iWidth, iHeight, 128);//��ֵ��
	if (bSaveImg) {
		SaveDataToImageFile(srcImgFile, stepImgFile8, image2);
		SaveDataToTextFile(stepTxtFile8, image2, iWidth, iHeight);
	}

	//�ھŲ���ϸ��
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);
	Thinning(image1, image2, iWidth, iHeight, 128);//ϸ��
	if (bSaveImg) {
		SaveDataToImageFile(srcImgFile, stepImgFile9, image2);
		SaveDataToTextFile(stepTxtFile9, image2, iWidth, iHeight);
	}

	unsigned char *thin = new unsigned char[iWidth*iHeight];
	memcpy(thin, image2, sizeof(unsigned char)*iWidth*iHeight);

	//��10����������ȡ
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);
	int minuCount = Extract(image1, image2, iWidth, iHeight);//������ȡ
	if (bSaveImg) {
		SaveDataToImageFile(srcImgFile, stepImgFile10, image2);
		SaveDataToTextFile(stepTxtFile10, image2, iWidth, iHeight);
	}

	//��11����
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);
	MINUTIAE *minutiaes = new MINUTIAE[minuCount];
	memset(minutiaes, sizeof(MINUTIAE), minuCount);
	MinuFilter(image1, thin, minutiaes, minuCount, iWidth, iHeight);//��������
	delete[] thin;
	SaveMinutiae(minutiaes, minuCount, stepImgFile11);//�������������ļ�
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

	//��12��������ʶ��
	int id = 0;
	char name[MAX_PATH] = { 0 }, src[MAX_PATH] = { 0 }, mdl[MAX_PATH] = { 0 };
	float maxSimilar = -1;
	int maxID = -1;
	char maxName[MAX_PATH] = { 0 }, maxSrc[MAX_PATH] = { 0 };
	MINUTIAE *minutiaes2 = NULL;
	int minuCount2 = 0;
	FILE *index = fopen(DB_INDEX_TXT, "r");//��ָ�ƿ������ļ�
	while (!feof(index))
	{
		//��ȡָ�Ƽ�¼��Ϣ��ָ�Ʊ��/ָ��ͼ���ļ���/����ģ���ļ���/�Ǽ���������
		fscanf(index, "%d %s %s %s\n", &id, src, mdl, name);
		//������ģ���ļ��ж�ȡָ������
		minuCount2 = ReadMinutiae(mdl, &minutiaes2);
		//����ƥ��
		float similar = MinuSimilarity(iWidth, iHeight, minutiaes, minuCount, minutiaes2, minuCount2);

		//�������ƶ���ߵ�ָ�Ƽ�¼��Ϣ
		if (similar > maxSimilar) {
			maxSimilar = similar;
			maxID = id;
			sprintf(maxName, name);
			sprintf(maxSrc, src);
		}
	}

	fclose(index);//�ر��ļ�
	delete[] minutiaes;
	delete[] minutiaes2;

	//����ʶ����

	const float SIMILAR_THRED = 0.1;//ƥ�����ƶ���ֵ��С����ֵ����Ϊ��ƥ�䣩
	if (maxID < 0 || maxSimilar < SIMILAR_THRED) {
		sprintf(info, "ʶ��ʧ��.");
		MessageBox(L"ʶ��ʧ��");
		return -12;
	}

	strcpy(outImgFile, maxSrc);//����ʶ����ͼ���ļ���
	if (bSaveImg) {
		CopyFile(ToWideChar(maxSrc), ToWideChar(stepImgFile12), false);//����ʶ����ͼ��
	}
	string s2(maxName);
	string s = "ʶ��ɹ��� ʶ����������" + s2 + "���ƶ�Ϊ:" + to_string(maxSimilar);
	CString cs(s.c_str());
	MessageBox(cs);
	sprintf(info, "ʶ��ɹ��� ʶ����������[%s],Ŀ��ָ��[%s],���ƶ�[%.2f].", maxName, maxSrc, maxSimilar);
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep12a()
{

	//��ʼ�����������Ϣ
	char info[MAX_PATH] = { 0 };

	//��ý�����������
	UpdateData(true);

	//�������
	Step12_Enroll(ToChar(m_name.GetBuffer()), info);

	//��ʾ���������Ϣs
	m_staticInfo.SetWindowText(ToWideChar(info));

	//��ʾͼ��
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_1);	//��ʾԭʼָ��ͼ��
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_11);	//��ʾָ������ͼ��

}

//��ָ̬��ͼ��ʶ�����
void CFingerDlg::OnBnClickedBtnMatchImage()
{
	//��ʼ�����������Ϣ
	char info[MAX_PATH] = { 0 };
	//�Զ�ѡ��ѡ��ͼ��

	//char*srcImgFile = NULL;
	//����ͼ��
	char *srcImgFile = openImagePath();

	//ָ��ʶ��
	bool bSaveImg = false;//�Ƿ񱣴��м���ͼ��
	char outImgFile[MAX_PATH] = { 0 };//ʶ����ͼ���ļ���
	Identify(srcImgFile, outImgFile, info, bSaveImg);//ָ��ʶ��

													 //��ʾ���������Ϣ
	m_staticInfo.SetWindowTextW(ToWideChar(info));
	//��ʾͼ��
	ShowImageInCtrl(m_picCtrl1, srcImgFile);//��ʾԭʼָ��ͼ��
	ShowImageInCtrl(m_picCtrl2, outImgFile);//��ʾʶ����ͼ��

}

//����ָ�Ʋɼ�����ָ��ʶ��
void CFingerDlg::OnBnClickedBtnIdentify()
{
	//��ʼ�����������Ϣ
	if (liu== 0) {
		MessageBox(_T("δ�����ɼ���"), _T("��ʾ"));
		return;
	}
	char info[MAX_PATH] = { 0 };
	//ʵʱ�ɼ�ͼ��

	//char*srcImgFile = NULL;
	char *srcImgFile = "capt.bmp";
	m_zkfpEng.SaveBitmap(ToWideChar(srcImgFile));

	//ָ��ʶ��
	bool bSaveImg = false;//�Ƿ񱣴��м���ͼ��
	char *outImgFile = new char[MAX_PATH];//ʶ����ͼ���ļ���
	Identify(srcImgFile, outImgFile, info, bSaveImg);//ָ��ʶ��
													 //��ʾ�������ͼ��
	m_staticInfo.SetWindowText(ToWideChar(info));
	//��ʾͼ��
	ShowImageInCtrl(m_picCtrl1, srcImgFile);//��ʾԭʼָ��ͼ��
	ShowImageInCtrl(m_picCtrl2, outImgFile);//��ʾʶ����ͼ��
}

