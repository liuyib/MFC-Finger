#pragma once
#include "afxwin.h"
#include "CZKFPEngX.h"
#include<time.h>

// CRegistDlg 对话框

class CRegistDlg : public CDialog
{
	DECLARE_DYNAMIC(CRegistDlg)

public:
	CRegistDlg(CWnd* pParent = nullptr);   // 标准构造函数
	afx_msg void OnImageReceivedZkfpengx(BOOL FAR* AImageVaild);
	virtual ~CRegistDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit r_name;
	CEdit r_card;
	CEdit r_subject;
	CEdit r_class;
	afx_msg void OnBnClickedOk();
	int male;
	int female;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio3();
	CEdit r_pass;
	CEdit r_repass;
	CStatic r_picimg_1;
	CStatic r_picimg_2;
	CStatic r_picimg_3;
	CZKFPEngX m_zkfpEng;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton2();
};
wchar_t * ToWideChar(char * str);
