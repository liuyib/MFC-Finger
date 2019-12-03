#pragma once
#include "afxwin.h"


// ManagerDlg 对话框

class ManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(ManagerDlg)

public:
	ManagerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ManagerDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
//	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic qiandaoxinxi;
};
