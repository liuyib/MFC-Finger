// RegistDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Finger.h"
#include "RegistDlg.h"
#include "afxdialogex.h"
#include "Login.h"
#include "CZKFPEngX.h"//引入指纹采集器SDK
using namespace std;
int sexa=0;
// CRegistDlg 对话框

IMPLEMENT_DYNAMIC(CRegistDlg, CDialog)

CRegistDlg::CRegistDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG2, pParent)
	, male(0)
	, female(0)
{
	
}

void CRegistDlg::OnImageReceivedZkfpengx(BOOL * AImageValid)
{
	HDC hdc = this->GetDC()->m_hDC;//获得显示设备上下文环境的句柄
	int x = 170;//图像绘制区左上角横坐标
	int y = 80;//图像绘制区左上角纵坐标
	int width = m_zkfpEng.get_ImageWidth();//图像绘制区的宽度
	int height = m_zkfpEng.get_ImageHeight();//图像绘制区的高度

	m_zkfpEng.PrintImageAt(int(hdc), x, y, width - 10, height);//绘制图像。

}

CRegistDlg::~CRegistDlg()
{
}


void CRegistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, r_name);
	DDX_Control(pDX, IDC_EDIT2, r_card);
	DDX_Control(pDX, IDC_EDIT6, r_subject);
	DDX_Control(pDX, IDC_EDIT5, r_class);
	DDX_Control(pDX, IDC_EDIT3, r_pass);
	DDX_Control(pDX, IDC_EDIT7, r_repass);
	DDX_Control(pDX, IDC_STATIC_IMG_1, r_picimg_1);
	/*DDX_Control(pDX, IDC_IMG1, r_picimg_2);
	DDX_Control(pDX, IDC_STATIC_IMG_2, r_picimg_3);*/
	DDX_Control(pDX, IDC_ZKFPENGX1, m_zkfpEng);
}


BEGIN_MESSAGE_MAP(CRegistDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CRegistDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &CRegistDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &CRegistDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_BUTTON1, &CRegistDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT7, &CRegistDlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT1, &CRegistDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CRegistDlg 消息处理程序
vector<string> splita(const string &s, const string &seperator) {
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.size() && flag == 0) {
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x]) {
					++i;
					flag = 0;
					break;
				}
		}

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x]) {
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}

// 确定button逻辑
void CRegistDlg::OnBnClickedOk()
{

	//注册验证
	CString c_name;
	r_name.GetWindowText(c_name);
	if (c_name.GetLength() == 0)
	{
		MessageBox(_T("请输入姓名"));
		return;
	}
	CString c_card;
	r_card.GetWindowText(c_card);
	if (c_card.GetLength() == 0)
	{
		MessageBox(_T("请输入学号"));
		return;
	}
	CString c_subject;
	r_subject.GetWindowText(c_subject);
	if (c_subject.GetLength() == 0)
	{
		MessageBox(_T("请输入专业"));
		return;
	}
	CString c_class;
	r_class.GetWindowText(c_class);
	if (c_class.GetLength() == 0)
	{
		MessageBox(_T("请输入班级"));
		return;
	}
	
	if(sexa==0)
	{
		MessageBox(_T("请选择性别"));
		return;
	}

	CString rm_pass;
	r_pass.GetWindowText(rm_pass);
	if (rm_pass.GetLength() == 0)
	{
		MessageBox(_T("请输入密码"));
		return;
	}
	CString rm_repass;
	r_repass.GetWindowText(rm_repass);
	if (rm_repass.GetLength() == 0)
	{
		MessageBox(_T("请输入确认密码"));
		return;
	}
	if (rm_pass.Compare(rm_repass)) {
		MessageBox(_T("密码和确认密码不一致"));
		return;
	}

	CString rm_name;
	r_name.GetWindowText(rm_name);
	CString rm_card;
	r_card.GetWindowText(rm_card);
	CString rm_subject;
	r_subject.GetWindowText(rm_subject);
	CString rm_class;
	r_class.GetWindowText(rm_class);
	string strSt1 = CT2A(rm_card.GetBuffer(0));
	string strSt2= CT2A(rm_pass.GetBuffer(0));
	string strSt3 = CT2A(rm_name.GetBuffer(0));
	string strSt4= CT2A(rm_subject.GetBuffer(0));
	string strSt5 = CT2A(rm_class.GetBuffer(0));
	bool finda = 0;
	string readlinea;
	fstream in("Database\\login.txt");
	int id = 0;
	while (getline(in, readlinea))
	{
		vector<string> arr = splita(readlinea, ",");
		const char* name = arr[1].data();
		CString temp1 = (CString)name;
		
		if (temp1.Compare(rm_name)==0) {
			finda = 1;
			MessageBox(_T("该用户已注册"));
			break;
		}
		id++;
	}
	in.close();
	if (finda == 0) {
		fstream fout("Database\\login.txt", ios::app);
		
		fout <<(id+1) <<","<<strSt1 << "," << strSt2 << "," << strSt3 << "," << strSt4 << "," <<strSt5<<","<< sexa <<","<<""<< endl;
		MessageBox(_T("注册成功"));
		fout.close();
	}
	
}


void CRegistDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	sexa = 1;
}

wchar_t * ToWideChar(char * str)
{
	int num = MultiByteToWideChar(0, 0, str, -1, NULL, 0);
	wchar_t *wideStr = new wchar_t[num];
	MultiByteToWideChar(0, 0, str, -1, wideStr, num);
	return wideStr;
}
void CRegistDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	sexa = 2;
}


// 将图片显示在空间中
int ShowImageInCtrl(CStatic & picCtrl, char * filename)
{
	//载入图像
	CImage image;
	HRESULT hResult = image.Load(ToWideChar(filename));
	int width = image.GetWidth();//图像宽度
	int height = image.GetHeight();//图像高度
								   //设置显示区域
	CRect rect;//定义矩形对象
	picCtrl.GetClientRect(&rect);//获得pictrue控件所在的矩形区域
	CDC *pDc = picCtrl.GetWindowDC();//获得picture控件的设置环境句柄
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);//设置位图拉伸模式
													//显示图像
	image.StretchBlt(pDc->m_hDC, rect, SRCCOPY);//将图像画到picture控件表示的矩形区域
												//更新控件显示
	picCtrl.Invalidate(false);//更新控件显示
							  //释放变量空间
	image.Destroy();
	picCtrl.ReleaseDC(pDc);//释放picture控件的设置环境句柄


	return 0;
}

// 录取button逻辑
void CRegistDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int z = 2;

	z = m_zkfpEng.InitEngine();//启动指纹采集器；
	MessageBox(_T("请按压指纹识别器."), _T("提示"));//显示信息
	Sleep(3000);
	int a = 1;
	if (z == 0) {
		MessageBox(_T("指纹获取成功."), _T("提示"));//显示信息

		
		//对注册学生进行指纹采集
		CString rm_name;
		r_name.GetWindowText(rm_name);
		CString rm_card;
		r_card.GetWindowText(rm_card);
		//保存
		CString defaulDir = L"./fingerimages";//默认打开的文件路径
		CString filename = rm_name + rm_card + ".bmp";

		CString filePath = defaulDir + "\\" + filename;
		//指定名称，指定路径
		m_zkfpEng.SaveBitmap(filePath);
		char stepImgFile1[MAX_PATH] = { STEP_IMG };
		CopyFile(filePath, ToWideChar(stepImgFile1), false);//复制文件，源，目标

		//在图片上展示图片
		ShowImageInCtrl(r_picimg_1, STEP_IMG);
		int a = 0;
		a++;
		return;
	}
	else if (z == 1) {
		MessageBox(_T("指纹识别驱动程序加载失败."), _T("提示"));//显示信息 
	}
	else if (z == 2) {
		MessageBox(_T("没有连接指纹识别器."), _T("提示"));//显示信息 
	}
	else
	{
		MessageBox(L"a" + z);
	}
}


void CRegistDlg::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CRegistDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
