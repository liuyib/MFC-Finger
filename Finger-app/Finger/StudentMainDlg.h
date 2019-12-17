#pragma once
#include "afxwin.h"
#include<vector>
#include<string>
#include "FingerDlg.h"

// StudentMainDlg 对话框

class StudentMainDlg : public CDialog
{
	DECLARE_DYNAMIC(StudentMainDlg)

public:
	StudentMainDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~StudentMainDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL StudentMainDlg::OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnImageReceivedZkfpengx(BOOL FAR* AImageVaild);
public:
	CEdit s_name;
	CEdit s_card;
	CEdit S_time;
	CStatic m_info;//显示打卡信息
	CStatic m_pic;//图片
	CZKFPEngX m_zkfpEng;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	int shibie();
	afx_msg void OnBnClickedButton2();
};
CString getNowTIme();
void modifyContentInFile(char *fileName, CString linecard, int a);
