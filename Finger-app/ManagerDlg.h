#pragma once
#include "afxwin.h"


// ManagerDlg �Ի���

class ManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(ManagerDlg)

public:
	ManagerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ManagerDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
//	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic qiandaoxinxi;
};
