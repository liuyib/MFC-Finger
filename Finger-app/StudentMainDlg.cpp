// StudentMainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Finger.h"
#include "StudentMainDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include<string>
#include<vector>
#include"Login.h"
#include "CZKFPEngX.h"//引入指纹采集器SDK


int isclass = 0;
// StudentMainDlg 对话框
using namespace std;
IMPLEMENT_DYNAMIC(StudentMainDlg, CDialog)

StudentMainDlg::StudentMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG3, pParent)
{


	//SetDlgItemText(IDC_EDIT5,L"aaaaaaa");
	//GetDlgItem(IDC_EDIT5)->SetWindowText(sc_user);
}
BOOL StudentMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString sc_user = getNowTIme();
	/*MessageBox(sc_user);
	char *ch;*/

	//ch = (LPSTR)(LPCTSTR)sc_user;
	CEdit*  pEdit = (CEdit*)GetDlgItem(IDC_EDIT5);//获取相应的编辑框ID
	pEdit->SetWindowText(sc_user); //设置默认显示的内容 
	CEdit*  pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT2);//获取相应的编辑框ID
	extern CString usera;
	pEdit1->SetWindowText(usera); //设置默认显示的内容 

	CEdit*  pEdit2 = (CEdit*)GetDlgItem(IDC_EDIT1);//获取相应的编辑框ID
	extern CString namea;
	pEdit2->SetWindowText(namea); //设置默认显示的内容 
	return TRUE;
}
StudentMainDlg::~StudentMainDlg()
{

}

void StudentMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, s_name);
	DDX_Control(pDX, IDC_EDIT2, s_card);
	DDX_Control(pDX, IDC_EDIT5, S_time);
	DDX_Control(pDX, IDC_STATIC_IMG_2, m_pic);
	DDX_Control(pDX, IDC_ZKFPENGX1, m_zkfpEng);
}


BEGIN_MESSAGE_MAP(StudentMainDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &StudentMainDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &StudentMainDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDOK, &StudentMainDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &StudentMainDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

CString getNowTIme() {
	CString str; //获取系统时间 　　

	CTime tm; tm = CTime::GetCurrentTime();

	str = tm.Format("%Y-%m-%d %X");

	return str;
}
// StudentMainDlg 消息处理程序
CString getNowTImeH() {
	CString str; //获取系统时间 　　

	CTime tm; tm = CTime::GetCurrentTime();

	str = tm.Format("%Y_%m_%d");

	return str;
}

void StudentMainDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	isclass = 1;
}


void StudentMainDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	isclass = 2;
}
int ishasbegin=0;
vector<string> splitb(const string &s, const string &seperator) {
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
/************************************************************************/
/* 修改文件某行内容
输入：文件名 fileName   行号   lineNum ,修改的内容 content
输出：文件名 fileName
无返回值
tip：1,lineNum从第一行开始 2.content需要加上换行符
*/
/************************************************************************/
void modifyContentInFile(const char *fileName, CString linecard, int a)
{
	ifstream in;
	char line[1024] = { '\0' };
	in.open(fileName);
	int i = 0;
	string tempStr;
	while (in.getline(line, sizeof(line)))
	{
		i++;
		vector<string> arr = splitb(line, ",");
		const char*  card = arr[0].data();
		const char*  time = arr[1].data();
		const char*  isqian = arr[2].data();
		//const char* password = arr[2].data();
		/*char *name = "admin";
		char *password = "admin";*/
		CString temp1 = (CString)card;
		
		if (linecard.Compare(temp1)){
			
			tempStr += line;
		}
		else
		{
			ishasbegin = 1;
			int b = atoi(arr[2].c_str());
			if (b == a) {
				ishasbegin = 2;
				return;
			}
			if (a == 2 && b == 0) {
				ishasbegin = 3;
			}
			CString timee = getNowTIme();
			char * ttt;

			LPCTSTR p = timee.GetBuffer(0);
			timee.ReleaseBuffer();
			ttt = new char[timee.GetLength() + 1];
			strcpy_s(ttt, timee.GetLength() + 1, CT2CA(p));
			
			tempStr += arr[0] + "," + (string)ttt + "," + to_string(a);
		}
		tempStr += '\n';
	}
	in.close();
	ofstream out;
	out.open(fileName);
	out.flush();
	out << tempStr;
	out.close();
}

void StudentMainDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialog::OnOK();
	extern CString usera;
	CString timee = getNowTImeH();
	char * ttt;
	
	LPCTSTR p = timee.GetBuffer(0);
	timee.ReleaseBuffer();
	ttt = new char[timee.GetLength() + 1];
	strcpy_s(ttt, timee.GetLength() + 1, CT2CA(p));
	//...  
	string bbb = "Database\\" + (string)ttt + ".txt";
	ifstream fin(bbb);
	if (!fin)
	{
		MessageBox(_T("管理员还未发起签到"));
		return;
	}
	fin.close();
	modifyContentInFile(bbb.data(), usera, isclass);

	if (ishasbegin == 1) {
		if (isclass == 1) {
			MessageBox(_T("上课签到成功"));
		}
		else {
			MessageBox(_T("下课签到成功"));
		}
		
	}
	else if (ishasbegin == 2) {
		MessageBox(_T("您已签到成功，不可重复签到"));
	}
	else if (ishasbegin == 3) {
		MessageBox(_T("请先上课签到"));
	}
	else {
		MessageBox(_T("您未加入班级，请联系管理员更新班级名单"));
	}
	
}
int ShowImageInCtrl1(CStatic & picCtrl, char * filename)
{

	//清空系统界面上原先显示的图像文字
	//HDC hdc = this->GetDC()->m_hDC;//获得显示设备上下文环境的句柄
	//int x = 160;//图像绘制区左上角横坐标
	//int y = 80;//图像绘制区左上角纵坐标
	//m_zkfpEng.PrintImageAt(int(hdc), x, y, 0, 0);//绘制图像。//没实现
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
void StudentMainDlg::OnBnClickedButton1()
{
	
	// TODO: 在此添加控件通知处理程序代码
	int z = 2;
	z = m_zkfpEng.InitEngine();//启动指纹采集器；
	MessageBox(_T("请按压指纹识别器."), _T("提示"));//显示信息
	Sleep(3000);
	int a = 1;
	if (z == 0) {
		//MessageBox(_T("采集器连接成功."), _T("提示"));//显示信息
		 MessageBox(L"采集指纹成功");


		//对注册学生进行指纹采集
		
	
		//保存
		//CString fileName = L"L01_01.bmp";//默认打开的文件名
		CString defaulDir = L"./fingerimages";//默认打开的文件路径
		CString filename = L"1.bmp";

		CString filePath = defaulDir + "\\" + filename;
		//指定名称，指定路径
		m_zkfpEng.SaveBitmap(filePath);
		char stepImgFile1[MAX_PATH] = { STEP_IMG1 };
		CopyFile(filePath, ToWideChar(stepImgFile1), false);//复制文件，源，目标

															//在图片上展示图片
		ShowImageInCtrl1(m_pic, STEP_IMG1);
		int a = 0;
		a++;
		return;
	}
	else if (z == 1) {
		//MessageBox(_T("指纹识别驱动程序加载失败."), _T("提示"));//显示信息 
		MessageBox(L"指纹识别驱动程序加载失败");
	}
	else if (z == 2) {
		//MessageBox(_T("没有连接指纹识别器."), _T("提示"));//显示信息 
		MessageBox(L"没有连接指纹识别器");
	}
	else
	{
		MessageBox(L"a" + z);
	}
}
