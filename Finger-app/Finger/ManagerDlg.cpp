// ManagerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Finger.h"
#include "ManagerDlg.h"
#include "afxdialogex.h"


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
}


BEGIN_MESSAGE_MAP(ManagerDlg, CDialog)
END_MESSAGE_MAP()


// ManagerDlg 消息处理程序
