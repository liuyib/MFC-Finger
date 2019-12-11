// StudentMainDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Finger.h"
#include "StudentMainDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include<string>
#include<vector>
#include"Login.h"
#include "file.h"
#include "CZKFPEngX.h"//引入指纹采集器SDK

int isclass = 0;
// StudentMainDlg 对话框
using namespace std;
IMPLEMENT_DYNAMIC(StudentMainDlg, CDialog)

StudentMainDlg::StudentMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG3, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}
BOOL StudentMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString sc_user = getNowTIme();

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


// StudentMainDlg 消息处理程序
int ishasbegin = 0;
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

		if (linecard.Compare(temp1)) {

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

CString getNowTImeH() {
	CString str; //获取系统时间 　　

	CTime tm; tm = CTime::GetCurrentTime();

	str = tm.Format("%Y_%m_%d");

	return str;
}

CString getNowTIme() {
	CString str; //获取系统时间 　　

	CTime tm; tm = CTime::GetCurrentTime();

	str = tm.Format("%Y-%m-%d %X");

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