
// FingerDlg.cpp : ʵ���ļ�
//
#pragma once
#include "stdafx.h"
#include "Finger.h"
#include "FingerDlg.h"
#include "afxdialogex.h"
#include "step.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFingerDlg �Ի���



CFingerDlg::CFingerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFingerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFingerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_srcIMG1, m_picCtrl1);
	DDX_Control(pDX, IDC_srcIMG2, m_picCtrl2);
	DDX_Control(pDX, IDC_srcIMG3, m_picCtrl3);
	DDX_Control(pDX, IDC_srcIMG4, m_picCtrl4);
	DDX_Control(pDX, IDC_srcIMG5, m_picCtrl5);
	DDX_Control(pDX, IDC_srcIMG6, m_picCtrl6);
	DDX_Control(pDX, IDC_srcIMG7, m_picCtrl7);
	DDX_Control(pDX, IDC_srcIMG8, m_picCtrl8);
	DDX_Control(pDX, IDC_srcIMG9, m_picCtrl9);
	DDX_Control(pDX, IDC_srcIMG10, m_picCtrl10);
	DDX_Control(pDX, IDC_srcIMG11, m_picCtrl11);
	DDX_Control(pDX, IDC_ZKFPENGX1, m_zkfpEng);
	DDX_Text(pDX, IDC_EDIT1, m_name);
}

BEGIN_MESSAGE_MAP(CFingerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK2, &CFingerDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDOK3, &CFingerDlg::OnBnClickedOk3)
	ON_BN_CLICKED(IDOK4, &CFingerDlg::OnBnClickedOk4)
	ON_BN_CLICKED(IDOK6, &CFingerDlg::OnBnClickedOk6)
	ON_BN_CLICKED(IDOK9, &CFingerDlg::OnBnClickedOk9)
	ON_BN_CLICKED(IDOK7, &CFingerDlg::OnBnClickedOk7)
	ON_BN_CLICKED(IDOK12, &CFingerDlg::OnBnClickedOk12)
	ON_BN_CLICKED(IDOK5, &CFingerDlg::OnBnClickedOk5)
	ON_BN_CLICKED(IDOK10, &CFingerDlg::OnBnClickedOk10)
	ON_BN_CLICKED(IDOK11, &CFingerDlg::OnBnClickedOk11)
	ON_BN_CLICKED(IDOK13, &CFingerDlg::OnBnClickedOk13)
	ON_BN_CLICKED(IDOK8, &CFingerDlg::OnBnClickedOk8)
	ON_BN_CLICKED(IDOK14, &CFingerDlg::OnBnClickedOk14)
	ON_BN_CLICKED(IDqidong, &CFingerDlg::OnBnClickedqidong)
	ON_BN_CLICKED(IDcaiji, &CFingerDlg::OnBnClickedcaiji)
	ON_BN_CLICKED(IDshibie, &CFingerDlg::OnBnClickedshibie)
	ON_BN_CLICKED(IDdengji, &CFingerDlg::OnBnClickeddengji)
	ON_BN_CLICKED(IDtingzhi, &CFingerDlg::OnBnClickedtingzhi)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON3, &CFingerDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CFingerDlg, CDialog)
	ON_EVENT(CFingerDlg, IDC_ZKFPENGX1, 8, OnImageReceivedZkfpengx, VTS_PBOOL)
END_EVENTSINK_MAP()

// CFingerDlg ��Ϣ�������

BOOL CFingerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString defaultPath("databases");
	CString folderPath("outfile");

	if (!PathIsDirectory(defaultPath))  // �Ƿ��������ļ���
	{
		::CreateDirectory(defaultPath, 0);
	}
	if (!PathIsDirectory(folderPath))  // �Ƿ��������ļ���
	{
		::CreateDirectory(folderPath, 0);
	}
	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

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

int da = 0;
CString strFile = _T("");


void CFingerDlg::OnImageReceivedZkfpengx(BOOL FAR* AImageValid) {
	m_zkfpEng.SaveBitmap(_T("outfile\\capt.bmp"));
	char *info = "";
	USES_CONVERSION;
	strFile = "outfile\\capt.bmp";
	char * beginfilename = T2A(strFile);
	Step1_LoadBmpImage(beginfilename, info);
	ShowImageInCtrl(m_picCtrl1, beginfilename);
}
void CFingerDlg::OnBnClickedOk2()
{
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), NULL);
	da = 1;
	char *info = "";
	if (dlgFile.DoModal())
	{
		strFile = dlgFile.GetPathName();
	}
	USES_CONVERSION;
	char * beginfilename = T2A(strFile);

	Step1_LoadBmpImage(beginfilename, info);

	ShowImageInCtrl(m_picCtrl1, beginfilename);

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFingerDlg::OnBnClickedOk3()
{
	if (da == 0) {
		MessageBox(_T("���ȵ���ͼƬ."), _T("��ʾ"));
		return;
	}
	da++;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char *info = "";
	USES_CONVERSION;
	char * beginfilename = T2A(strFile);
	Step2_MidFilter(beginfilename, info);
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_2);
}


void CFingerDlg::OnBnClickedOk4()
{
	if (da == 0) {
		MessageBox(_T("���ȵ���ͼƬ."), _T("��ʾ"));
		return;
	}
	else if (da < 2) {
		OnBnClickedOk3();
	}
	da++;
	// TODO: �ڴ���ӿؼ�֪ͨ��������
	char *info = "";
	Step3_HistoNormalize(info);
	ShowImageInCtrl(m_picCtrl3, STEP_IMG_3);
}


void CFingerDlg::OnBnClickedOk6()
{
	if (da == 0) {
		MessageBox(_T("���ȵ���ͼƬ."), _T("��ʾ"));
		return;
	}
	else if (da < 3) {
		OnBnClickedOk4();
	}
	da++;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char *info = "";

	Step4_Direction(info);
	ShowImageInCtrl(m_picCtrl4, STEP_IMG_4);
}


void CFingerDlg::OnBnClickedOk9()
{
	if (da == 0) {
		MessageBox(_T("���ȵ���ͼƬ."), _T("��ʾ"));
		return;
	}
	else if (da < 4) {
		OnBnClickedOk6();
	}
	da++;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char *info = "";
	Step5_Frequency(info);
	ShowImageInCtrl(m_picCtrl5, STEP_IMG_5);
}


void CFingerDlg::OnBnClickedOk7()
{
	if (da == 0) {
		MessageBox(_T("���ȵ���ͼƬ."), _T("��ʾ"));
		return;
	}
	else if (da < 5) {
		OnBnClickedOk9();
	}
	da++;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char *info = "";
	Step6_GetMask(info);
	ShowImageInCtrl(m_picCtrl6, STEP_IMG_6);
}


void CFingerDlg::OnBnClickedOk12()
{
	if (da == 0) {
		MessageBox(_T("���ȵ���ͼƬ."), _T("��ʾ"));
		return;
	}
	else if (da < 6) {
		OnBnClickedOk7();
	}
	da++;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char *info = "";
	Step7_GaborEnhance(info);
	ShowImageInCtrl(m_picCtrl7, STEP_IMG_7);
}

void CFingerDlg::OnBnClickedOk5()
{
	if (da == 0) {
		MessageBox(_T("���ȵ���ͼƬ."), _T("��ʾ"));
		return;
	}
	else if (da < 7) {
		OnBnClickedOk12();
	}
	da++;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char *info = "";
	Step8_Binary(info);
	ShowImageInCtrl(m_picCtrl8, STEP_IMG_8);
}


void CFingerDlg::OnBnClickedOk10()
{
	if (da == 0) {
		MessageBox(_T("���ȵ���ͼƬ."), _T("��ʾ"));
		return;
	}
	else if (da < 8) {
		OnBnClickedOk5();
	}
	da++;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char *info = "";
	Step9_Thinning(info);
	ShowImageInCtrl(m_picCtrl9, STEP_IMG_9);
}


void CFingerDlg::OnBnClickedOk11()
{
	if (da == 0) {
		MessageBox(_T("���ȵ���ͼƬ."), _T("��ʾ"));
		return;
	}
	else if (da < 9) {
		OnBnClickedOk10();
	}
	da++;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char *info = "";
	Step10_MinuExtract(info);
	ShowImageInCtrl(m_picCtrl10, STEP_IMG_10);
}


void CFingerDlg::OnBnClickedOk13()
{
	if (da == 0) {
		MessageBox(_T("���ȵ���ͼƬ."), _T("��ʾ"));
		return;
	}
	else if (da < 10) {
		OnBnClickedOk11();
	}
	da++;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char *info = "";
	Step11_MinuFilter(info);
	ShowImageInCtrl(m_picCtrl11, STEP_IMG_11);
}


void CFingerDlg::OnBnClickedOk8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char *info = "";
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT1);
	CString str;
	pBoxOne->GetWindowText(str);
	USES_CONVERSION;
	char * name = T2A(str);
	int len = strlen(name);
	if (len == 0){
		MessageBox(_T("������Ǽ���."), _T("��ʾ"));
		return;
	}
	if (da == 0) {
		MessageBox(_T("���ȵ���ͼƬ."), _T("��ʾ"));
		return;
	}
	else if (da < 13) {
		OnBnClickedOk11();
	}
	da++;
	 
	char * beginfilename = T2A(strFile);
	Step12_Enroll(beginfilename, name, info);
	::MessageBox(NULL, _T("ָ��������!"), _T("ִ�����"), MB_OK);
}


void CFingerDlg::OnBnClickedOk14()
{
	char *info = "";
	USES_CONVERSION;
	char * beginfilename = T2A(strFile);
	Step12_Identify(beginfilename, info);
}


HBRUSH CFingerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	static CBrush gBr;
	static bool isInited = false;
	if (!isInited)
	{
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP1);
		gBr.CreatePatternBrush(&bitmap);
		COLORREF clearColor = -1;
		bitmap.DeleteObject();
		isInited = true;
	}
	if (pWnd == this)
	{
		pDC->SetBkMode(TRANSPARENT);
		return gBr; //�����ڱ���ʹ���������ˢ
	}
	else
	{
		pDC->SetBkMode(TRANSPARENT);
		return  (HBRUSH)::GetStockObject(NULL_BRUSH); //�����ؼ�ʹ��͸������
	}

	return hbr;
}


void CFingerDlg::OnBnClickedButton3()
{
	CDialogEx::OnOK();
}

void CFingerDlg::OnBnClickedqidong()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	m_zkfpEng.InitEngine();
	MessageBox(_T("�ɼ������ӳɹ�"), _T("��ʾ"));
}


void CFingerDlg::OnBnClickedtingzhi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_zkfpEng.EndEngine();

}


void CFingerDlg::OnBnClickedcaiji()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_zkfpEng.SaveBitmap(_T("outfile\\capt.bmp"));
	char *info = "";
	USES_CONVERSION;
	strFile = "outfile\\capt.bmp";
	char * beginfilename = T2A(strFile);
	Step1_LoadBmpImage(beginfilename, info);
	ShowImageInCtrl(m_picCtrl1, beginfilename);
}


void CFingerDlg::OnBnClickeddengji()
{
	char *info = "";
	USES_CONVERSION;
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT1);
	CString str;
	pBoxOne->GetWindowText(str);
	char * name = T2A(str);
	int len = strlen(name);
	if (len == 0){
		MessageBox(_T("������Ǽ���."), _T("��ʾ"));
		return;
	}
	char * beginfilename = T2A(strFile);
	strFile = "outfile\\capt.bmp";
	beginfilename = T2A(strFile);
	Step1_LoadBmpImage(beginfilename, info);
	ShowImageInCtrl(m_picCtrl1, beginfilename);
	Step2_MidFilter(beginfilename, info);
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_2);
	Step3_HistoNormalize(info);
	ShowImageInCtrl(m_picCtrl3, STEP_IMG_3);
	Step4_Direction(info);
	ShowImageInCtrl(m_picCtrl4, STEP_IMG_4);
	Step5_Frequency(info);
	ShowImageInCtrl(m_picCtrl5, STEP_IMG_5);
	Step6_GetMask(info);
	ShowImageInCtrl(m_picCtrl6, STEP_IMG_6);
	Step7_GaborEnhance(info);
	ShowImageInCtrl(m_picCtrl7, STEP_IMG_7);
	Step8_Binary(info);
	ShowImageInCtrl(m_picCtrl8, STEP_IMG_8);
	Step9_Thinning(info);
	ShowImageInCtrl(m_picCtrl9, STEP_IMG_9);
	Step10_MinuExtract(info);
	ShowImageInCtrl(m_picCtrl10, STEP_IMG_10);
	Step11_MinuFilter(info);
	ShowImageInCtrl(m_picCtrl11, STEP_IMG_11);
	pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT1);
	pBoxOne->GetWindowText(str);
	name = T2A(str);
	beginfilename = T2A(strFile);
	Step12_Enroll(beginfilename, name, info);
	::MessageBox(NULL, _T("ָ��������!"), _T("ִ�����"), MB_OK);
}


void CFingerDlg::OnBnClickedshibie()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char *info = "";
	USES_CONVERSION;
	strFile = "outfile\\capt.bmp";
	char * beginfilename = T2A(strFile);
	Step1_LoadBmpImage(beginfilename, info);
	ShowImageInCtrl(m_picCtrl1, beginfilename);
	Step2_MidFilter(beginfilename, info);
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_2);
	Step3_HistoNormalize(info);
	ShowImageInCtrl(m_picCtrl3, STEP_IMG_3);
	Step4_Direction(info);
	ShowImageInCtrl(m_picCtrl4, STEP_IMG_4);
	Step5_Frequency(info);
	ShowImageInCtrl(m_picCtrl5, STEP_IMG_5);
	Step6_GetMask(info);
	ShowImageInCtrl(m_picCtrl6, STEP_IMG_6);
	Step7_GaborEnhance(info);
	ShowImageInCtrl(m_picCtrl7, STEP_IMG_7);
	Step8_Binary(info);
	ShowImageInCtrl(m_picCtrl8, STEP_IMG_8);
	Step9_Thinning(info);
	ShowImageInCtrl(m_picCtrl9, STEP_IMG_9);
	Step10_MinuExtract(info);
	ShowImageInCtrl(m_picCtrl10, STEP_IMG_10);
	Step11_MinuFilter(info);
	ShowImageInCtrl(m_picCtrl11, STEP_IMG_11);
	beginfilename = T2A(strFile);
	Step12_Identify(beginfilename, info);
}