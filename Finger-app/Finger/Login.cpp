﻿// Login.cpp: 实现文件
//

#include "stdafx.h"
#include "Finger.h"
#include "Login.h"
#include "afxdialogex.h"

using namespace std;
// CLogin 对话框

IMPLEMENT_DYNAMIC(CLogin, CDialog)

CLogin::CLogin(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, m_user);
	DDX_Control(pDX, IDC_EDIT4, m_pass);
}


BEGIN_MESSAGE_MAP(CLogin, CDialog)
	ON_BN_CLICKED(IDOK, &CLogin::OnBnClickedOk)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK2, &CLogin::OnBnClickedOk2)
	//	ON_EN_CHANGE(IDC_EDIT3, &CLogin::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_RADIO1, &CLogin::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CLogin::OnBnClickedRadio2)
	ON_BN_CLICKED(IDOK5, &CLogin::OnBnClickedOk5)
	ON_BN_CLICKED(IDOK3, &CLogin::OnBnClickedOk3)
END_MESSAGE_MAP()


// CLogin 消息处理程序

CString usera;
CString namea;
int guanliyuan = 0;

//登陆
void CLogin::OnBnClickedOk()
{
	if (guanliyuan == 0) {
		MessageBox(_T("请选择身份"));
	}
	else if (guanliyuan == 1) {
		// 普通用户(学生)登陆
		CString c_user;
		m_user.GetWindowText(c_user);
		CString c_pass;
		m_pass.GetWindowText(c_pass);
		int ispipei = login(c_user, c_pass);
		if ((c_pass.GetLength() == 0) || c_user.GetLength() == 0) {
			MessageBox(_T("请输入用户名密码"));
		}
		if (ispipei == 1) {
			MessageBox(_T("登录成功"));
			usera = c_user;
			// 跳转到学生界面
			StudentMainDlg studentDlg;
			studentDlg.DoModal();
		}
		else if (ispipei == 2) {
			MessageBox(_T("该用户不存在,请注册"));
			CRegistDlg m_registDlg;
			m_registDlg.DoModal();

		}
		else
		{
			MessageBox(_T("用户名密码错误"));
		}
	}
	else if (guanliyuan == 2)
	{
		// 管理员(教师)登陆
		CString c_user;
		m_user.GetWindowText(c_user);
		CString c_pass;
		m_pass.GetWindowText(c_pass);
		if (c_user == "admin"&&c_pass == "admin") {

			MessageBox(_T("管理员登陆成功"));
			ManagerDlg mana;
			mana.DoModal();
		}
		else
		{
			MessageBox(_T("用户名密码错误"));
		}
	}


}

vector<string> split(const string &s, const string &seperator) {
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.size() && flag == 0) {
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x]) {
					++i;
					flag = 0;
					break;
				}
		}

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x]) {
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}

// 根据用户名和密码登陆
int login(CString user, CString pass) {
	fstream fin("./Database\\login.txt");
	string readlinea;
	int isPipei = 0;
	while (getline(fin, readlinea))
	{

		vector<string> arr = split(readlinea, ",");
		const char* card = arr[1].data();
		const char* password = arr[2].data();
		const char* name = arr[3].data();
		CString temp1 = (CString)card;
		CString temp2 = (CString)password;
		CString temp3 = (CString)name;
		if (user.Compare(temp1) == 0 && pass.Compare(temp2) == 0) {
			// 匹配成功
			isPipei = 1;
			namea = temp3;
			break;
		}
		if (user.Compare(temp1)) {
			isPipei = 2;
		}
	}
	fin.close();
	return isPipei;
}
int saveData(char * dstFile, float * data, int width, int height)
{
	ofstream fout(dstFile, ios::out);//

	fout.close();

	return 0;
}


HBRUSH CLogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	static CBrush gBr;
	static bool isInited;
	if (!isInited)
	{
		CBitmap bitmap;
		bitmap.LoadBitmapW(IDB_BITMAP5);
		gBr.CreatePatternBrush(&bitmap);
		COLORREF clearColor = -1;
		bitmap.DeleteObject();
		isInited = true;
	}
	if (pWnd == this)
	{
		pDC->SetBkMode(TRANSPARENT);
		return gBr;
	}
	else
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(WHITE_BRUSH);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

// 注册button逻辑
void CLogin::OnBnClickedOk2()
{
	CString str1 = L"./fingerimages";
	CreateDirectory(str1, NULL);
	CString str2 = L"./temp";
	CreateDirectory(str2, NULL);
	CString str3 = L"./Database";
	CreateDirectory(str3, NULL);
	// TODO: 在此添加控件通知处理程序代码
	CRegistDlg m_registDlg;
	m_registDlg.DoModal();
}


void CLogin::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	guanliyuan = 1;

}


void CLogin::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	guanliyuan = 2;
}


void CLogin::OnBnClickedOk5()
{
	// TODO: Add your control notification handler code here
	exit(0);
}


void CLogin::OnBnClickedOk3()
{
	if (guanliyuan == 0) {
		MessageBox(_T("请选择身份"));
	}
	else if (guanliyuan == 1) {
		// 普通用户(学生)登陆
		CString c_user;
		m_user.GetWindowText(c_user);
		CString c_pass;
		m_pass.GetWindowText(c_pass);
		int ispipei = login(c_user, c_pass);
		if ((c_pass.GetLength() == 0) || c_user.GetLength() == 0) {
			MessageBox(_T("请输入用户名密码"));
		}
		if (ispipei == 1) {
			MessageBox(_T("登录成功"));
			usera = c_user;
			// 跳转到学生界面
			StudentMainDlg studentDlg;
			studentDlg.DoModal();
		}
		else if (ispipei == 2) {
			MessageBox(_T("该用户不存在,请注册"));
			CRegistDlg m_registDlg;
			m_registDlg.DoModal();

		}
		else
		{
			MessageBox(_T("用户名密码错误"));
		}
	}
	else if (guanliyuan == 2)
	{
		// 管理员(教师)登陆
		CString c_user;
		m_user.GetWindowText(c_user);
		CString c_pass;
		m_pass.GetWindowText(c_pass);
		if (c_user == "admin"&&c_pass == "admin") {

			MessageBox(_T("管理员登陆成功"));
			ManagerDlg mana;
			mana.DoModal();
		}
		else
		{
			MessageBox(_T("用户名密码错误"));
		}
	}
}
