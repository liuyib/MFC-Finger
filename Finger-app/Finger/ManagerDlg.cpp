// ManagerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Finger.h"
#include "ManagerDlg.h"
#include "afxdialogex.h"
#include <string>
#include<fstream>
#include<vector>
#include "file.h"
#include"Login.h"

// ManagerDlg 对话框

IMPLEMENT_DYNAMIC(ManagerDlg, CDialog)

ManagerDlg::ManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG4, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

ManagerDlg::~ManagerDlg()
{
}

void ManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT7, qiandaoxinxi);
}


BEGIN_MESSAGE_MAP(ManagerDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &ManagerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ManagerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &ManagerDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// ManagerDlg 消息处理程序
void ManagerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString timee = getNowTImeH1();
	char * ttt;

	LPCTSTR p = timee.GetBuffer(0);
	timee.ReleaseBuffer();
	ttt = new char[timee.GetLength() + 1];
	strcpy_s(ttt, timee.GetLength() + 1, CT2CA(p));
	//...  
	string bbb = "Database\\" + (string)ttt + ".txt";
	FILE *fp = fopen(bbb.c_str(), "a");
	writeInto(bbb.data());
	MessageBox(_T("成功发起签到"));
}
void ManagerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CString timee = getNowTImeH1();
	char * ttt;
	LPCTSTR p = timee.GetBuffer(0);
	timee.ReleaseBuffer();
	ttt = new char[timee.GetLength() + 1];
	strcpy_s(ttt, timee.GetLength() + 1, CT2CA(p));
	//...  
	string bbb = "Database\\" + (string)ttt + ".txt";
	FILE *fp = fopen(bbb.c_str(), "a");
	writeInto(bbb.data());
	MessageBox(_T("名单更新成功"));
}

void ManagerDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString timee = getNowTImeH1();
	char * ttt;

	LPCTSTR p = timee.GetBuffer(0);
	timee.ReleaseBuffer();
	ttt = new char[timee.GetLength() + 1];
	strcpy_s(ttt, timee.GetLength() + 1, CT2CA(p));
	string bbb = "Database\\" + (string)ttt + ".txt";
	ifstream fin(bbb);
	if (!fin)
	{
		MessageBox(_T("您还未发起签到"));
		return;
	}
	else
	{
		CString str1;
		GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowText(str1);

		char * ttt1;

		LPCTSTR p1 = str1.GetBuffer(0);
		str1.ReleaseBuffer();
		ttt1 = new char[str1.GetLength() + 1];
		strcpy_s(ttt1, str1.GetLength() + 1, CT2CA(p1));
		vector<string> ve = splitc((string)ttt1, "/");
		string ddd = "Database\\" + ve[0] + "_" + ve[1] + "_" + ve[2] + ".txt";
		fstream fin(ddd);
		string readlinea;
		int isPipei = 0;
		string tempStr = "学号\t时间\t\t详情\n";
		int isnull = 0;
		while (getline(fin, readlinea)) {

			vector<string> arr = splitc(readlinea, ",");
			const char*  card = arr[0].data();
			const char*  time = arr[1].data();
			const char*  isqian = arr[2].data();
			CString temp1 = (CString)card;
			string ta = "";
			int b = atoi(arr[2].c_str());
			if (b == 0) {
				ta = "缺课";
			}
			else if (b == 1) {
				ta = "到课";
			}
			else
			{
				ta = "早退";
			}

			isnull = 1;
			tempStr += arr[0] + "\t" + arr[1] + "\t" + ta + "\n";
		}
		if (isnull == 0) {
			CEdit*  pEdit2 = (CEdit*)GetDlgItem(IDC_EDIT7);//获取相应的编辑框ID
			pEdit2->SetWindowText(_T("暂无任何数据")); //设置默认显示的内容 
		}
		else
		{
			CEdit*  pEdit2 = (CEdit*)GetDlgItem(IDC_EDIT7);//获取相应的编辑框ID
			pEdit2->SetWindowText((CString)tempStr.c_str()); //设置默认显示的内容 
		}

	}
}

