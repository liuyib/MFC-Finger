#pragma once


// Welcome �Ի���

class Welcome : public CDialogEx
{
	DECLARE_DYNAMIC(Welcome)

public:
	Welcome(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Welcome();

	CBitmap m_bmp;//�ͻ��˵�¼ҳ���λͼ����ͼ
	CBrush m_brush;//��ˢ
	CString m_strUser;
	CString m_strPwd;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
