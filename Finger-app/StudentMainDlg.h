#pragma once
#include "afxwin.h"
#include<vector>
#include<string>
#include "FingerDlg.h"
#define STEP_IMG1 "temp\\shibie_Source.bmp"
// StudentMainDlg �Ի���

class StudentMainDlg : public CDialog
{
	DECLARE_DYNAMIC(StudentMainDlg)

public:
	StudentMainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~StudentMainDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL StudentMainDlg::OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	/*CEdit s_name;
	CEdit s_card;
	CEdit S_time;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedOk();*/
	CEdit s_name;
	CEdit s_card;
	CEdit S_time;
	CStatic m_info;//��ʾ����Ϣ
	CStatic m_pic;//ͼƬ
	CZKFPEngX m_zkfpEng;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
CString getNowTIme();
void modifyContentInFile(char *fileName, CString linecard, int a);