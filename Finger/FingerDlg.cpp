
// FingerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Finger.h"
#include "FingerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFingerDlg 对话框



CFingerDlg::CFingerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FINGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFingerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFingerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFingerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFingerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CFingerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CFingerDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CFingerDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CFingerDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CFingerDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON9, &CFingerDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CFingerDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CFingerDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CFingerDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CFingerDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON8, &CFingerDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON14, &CFingerDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CFingerDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CFingerDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &CFingerDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CFingerDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CFingerDlg::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, &CFingerDlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON21, &CFingerDlg::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, &CFingerDlg::OnBnClickedButton22)
	ON_EN_CHANGE(IDC_EDIT1, &CFingerDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CFingerDlg 消息处理程序

BOOL CFingerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFingerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFingerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 载入图像
void CFingerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 中值滤波
void CFingerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 均值化
void CFingerDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 方向计算
void CFingerDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 频率计算
void CFingerDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 掩码计算
void CFingerDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
}

// Gabor 增强
void CFingerDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 二值化
void CFingerDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 细化
void CFingerDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 特征提取
void CFingerDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 特征过滤
void CFingerDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 特征入库
void CFingerDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 特征匹配
void CFingerDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 图像--登记
void CFingerDlg::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 图像--识别
void CFingerDlg::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 指纹采集器--启动
void CFingerDlg::OnBnClickedButton16()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 指纹采集器--采集
void CFingerDlg::OnBnClickedButton17()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 指纹采集器--登记
void CFingerDlg::OnBnClickedButton18()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 指纹采集器--识别
void CFingerDlg::OnBnClickedButton19()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 指纹采集器--停止
void CFingerDlg::OnBnClickedButton20()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 指纹库信息
void CFingerDlg::OnBnClickedButton21()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 退出
void CFingerDlg::OnBnClickedButton22()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 姓名输入框
void CFingerDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
