#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include "afxwin.h"
#include "RegistDlg.h"
#include "StudentMainDlg.h"
#include "ManagerDlg.h"
// CLogin �Ի���

class CLogin : public CDialog
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogin();


// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk2();
//	afx_msg void OnEnChangeEdit3();
	CEdit m_user;
	CEdit m_pass;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedOk5();
	afx_msg void OnBnClickedOk3();
};
int login(CString user, CString pass);
bool getvoice(CString s);