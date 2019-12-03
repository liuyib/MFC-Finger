#pragma once


// Welcome 对话框

class Welcome : public CDialogEx
{
	DECLARE_DYNAMIC(Welcome)

public:
	Welcome(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Welcome();

	CBitmap m_bmp;//客户端登录页面的位图背景图
	CBrush m_brush;//画刷
	CString m_strUser;
	CString m_strPwd;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
