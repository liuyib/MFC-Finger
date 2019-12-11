// RegistDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Finger.h"
#include "RegistDlg.h"
#include "afxdialogex.h"
//#include "step.h"

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

void CRegistDlg::OnImageReceivedZkfpengx(BOOL * AImageVaild)
{
	m_zkfpEng.SaveBitmap(_T("outfile\\capt.bmp"));
	char *info = "";
	USES_CONVERSION;
	//strFile = "outfile\\capt.bmp";
	//char * beginfilename = T2A(strFile);
	/*Step1_LoadBmpImage(beginfilename, info);
	ShowImageInCtrl(r_picimg_1, beginfilename);*/
}

CRegistDlg::~CRegistDlg()
{
}

void CRegistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRegistDlg, CDialog)
END_MESSAGE_MAP()


// CRegistDlg 消息处理程序


