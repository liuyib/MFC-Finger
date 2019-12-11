// RegistDlg.cpp: 实现文件
//
#pragma once
#include "stdafx.h"
#include "Finger.h"
#include "RegistDlg.h"
#include "afxdialogex.h"
#include "step.h"

using namespace std;
int sexa = 0;
// CRegistDlg 对话框

IMPLEMENT_DYNAMIC(CRegistDlg, CDialog)

CRegistDlg::CRegistDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG2, pParent)
	, male(0)
	, female(0)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

int da1 = 0;
CString strFile1 = _T("");
int mode = 0;// 1是导入图片 2是指纹采集

void CRegistDlg::OnImageReceivedZkfpengx(BOOL * AImageVaild)
{
	m_zkfpEng.SaveBitmap(_T("outfile\\capt.bmp"));
	char *info = "";
	USES_CONVERSION;
	CString strFile = L"outfile\\capt.bmp";
	char * beginfilename = T2A(strFile);
	Step1_LoadBmpImage(beginfilename, info);
	ShowImageInCtrl(r_picimg_1, beginfilename);
}

CRegistDlg::~CRegistDlg()
{
}

void CRegistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, r_name);
	DDX_Control(pDX, IDC_EDIT2, r_card);
	DDX_Control(pDX, IDC_EDIT6, r_subject);
	DDX_Control(pDX, IDC_EDIT5, r_class);
	DDX_Control(pDX, IDC_EDIT3, r_pass);
	DDX_Control(pDX, IDC_EDIT7, r_repass);
	DDX_Control(pDX, IDC_STATIC_IMG_1, r_picimg_1);
	/*DDX_Control(pDX, IDC_IMG1, r_picimg_2);
	DDX_Control(pDX, IDC_STATIC_IMG_2, r_picimg_3);*/
	DDX_Control(pDX, IDC_ZKFPENGX1, m_zkfpEng);
}


BEGIN_MESSAGE_MAP(CRegistDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CRegistDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CRegistDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &CRegistDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &CRegistDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_BUTTON1, &CRegistDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CRegistDlg 消息处理程序

void CRegistDlg::dengji()
{
	char *info = "";
	USES_CONVERSION;
	CString str;
	r_name.GetWindowText(str);
	char * name = T2A(str);
	int len = strlen(name);
	if (len == 0) {
		MessageBox(_T("请输入登记名."), _T("提示"));
		return;
	}
	char * beginfilename = T2A(strFile1);
	strFile1 = "outfile\\capt.bmp";
	beginfilename = T2A(strFile1);
	Step1_LoadBmpImage(beginfilename, info);
	Step2_MidFilter(beginfilename, info);
	Step3_HistoNormalize(info);
	Step4_Direction(info);
	Step5_Frequency(info);
	Step6_GetMask(info);
	Step7_GaborEnhance(info);
	Step8_Binary(info);
	Step9_Thinning(info);
	Step10_MinuExtract(info);
	Step11_MinuFilter(info);
	r_name.GetWindowText(str);
	name = T2A(str);
	beginfilename = T2A(strFile1);
	Step12_Enroll(beginfilename, name, info);
}

// 确定button逻辑
void CRegistDlg::OnBnClickedOk()
{

	//注册验证
	CString c_name;
	r_name.GetWindowText(c_name);
	if (c_name.GetLength() == 0)
	{
		MessageBox(_T("请输入姓名"));
		return;
	}
	CString c_card;
	r_card.GetWindowText(c_card);
	if (c_card.GetLength() == 0)
	{
		MessageBox(_T("请输入学号"));
		return;
	}
	CString c_subject;
	r_subject.GetWindowText(c_subject);
	if (c_subject.GetLength() == 0)
	{
		MessageBox(_T("请输入专业"));
		return;
	}
	CString c_class;
	r_class.GetWindowText(c_class);
	if (c_class.GetLength() == 0)
	{
		MessageBox(_T("请输入班级"));
		return;
	}

	if (sexa == 0)
	{
		MessageBox(_T("请选择性别"));
		return;
	}

	CString rm_pass;
	r_pass.GetWindowText(rm_pass);
	if (rm_pass.GetLength() == 0)
	{
		MessageBox(_T("请输入密码"));
		return;
	}
	CString rm_repass;
	r_repass.GetWindowText(rm_repass);
	if (rm_repass.GetLength() == 0)
	{
		MessageBox(_T("请输入确认密码"));
		return;
	}
	if (rm_pass.Compare(rm_repass)) {
		MessageBox(_T("密码和确认密码不一致"));
		return;
	}

	CString rm_name;
	r_name.GetWindowText(rm_name);
	CString rm_card;
	r_card.GetWindowText(rm_card);
	CString rm_subject;
	r_subject.GetWindowText(rm_subject);
	CString rm_class;
	r_class.GetWindowText(rm_class);
	string strSt1 = CT2A(rm_card.GetBuffer(0));
	string strSt2 = CT2A(rm_pass.GetBuffer(0));
	string strSt3 = CT2A(rm_name.GetBuffer(0));
	string strSt4 = CT2A(rm_subject.GetBuffer(0));
	string strSt5 = CT2A(rm_class.GetBuffer(0));
	bool finda = 0;
	string readlinea;
	fstream in("Database\\login.txt");
	int id = 0;
	while (getline(in, readlinea))
	{
		vector<string> arr = splita(readlinea, ",");
		const char* name = arr[1].data();
		CString temp1 = (CString)name;

		if (temp1.Compare(rm_name) == 0) {
			finda = 1;
			MessageBox(_T("该用户已注册"));
			break;
		}
		id++;
	}
	in.close();
	if (finda == 0) {
		fstream fout("Database\\login.txt", ios::app);

		fout << (id + 1) << "," << strSt1 << "," << strSt2 << "," << strSt3 << "," << strSt4 << "," << strSt5 << "," << sexa << "," << "" << endl;
		
		dengji();
		
		MessageBox(_T("注册成功"));
		fout.close();
	}

}
void CRegistDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	sexa = 1;
}


void CRegistDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	sexa = 2;
}





// 录取button逻辑
void CRegistDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int z = 2;

	z = m_zkfpEng.InitEngine();//启动指纹采集器；
	MessageBox(_T("请按压指纹识别器."), _T("提示"));//显示信息
	Sleep(3000);
	int a = 1;
	if (z == 0) {
		MessageBox(_T("指纹获取成功."), _T("提示"));//显示信息


		int a = 0;
		a++;
		return;
	}
	else if (z == 1) {
		MessageBox(_T("指纹识别驱动程序加载失败."), _T("提示"));//显示信息 
	}
	else if (z == 2) {
		MessageBox(_T("没有连接指纹识别器."), _T("提示"));//显示信息 
	}
	else
	{
		MessageBox(L"a" + z);
	}
}




void CRegistDlg::OnBnClickedButton2()
{
	mode = 1;
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), NULL);
	da1 = 1;
	char *info = "";
	if (dlgFile.DoModal())
	{
		strFile1 = dlgFile.GetPathName();
	}
	USES_CONVERSION;
	char * beginfilename = T2A(strFile1);

	Step1_LoadBmpImage(beginfilename, info);


	char *srcImgFile = beginfilename;
	char dstImgFile[MAX_PATH] = { 0 };
	char regName[MAX_PATH] = { 0 };
	sprintf(regName, "capt");
	sprintf(dstImgFile, "%s%s.bmp", "outfile//", regName);
	CopyFile(ToWideChar(srcImgFile), ToWideChar(dstImgFile), false);

	ShowImageInCtrl(r_picimg_1, beginfilename);
	MessageBox(_T("指纹录入成功."), _T("提示"));//显示信息
}
