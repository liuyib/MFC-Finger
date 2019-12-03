// ManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Finger.h"
#include "ManagerDlg.h"
#include "afxdialogex.h"
#include <string>
#include<fstream>
#include<vector>
#include"Login.h"
using namespace std;

// ManagerDlg �Ի���

IMPLEMENT_DYNAMIC(ManagerDlg, CDialog)

ManagerDlg::ManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG4, pParent)
{

}

ManagerDlg::~ManagerDlg()
{
}

void ManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT7, qiandaoxinxi);
}


BEGIN_MESSAGE_MAP(ManagerDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &ManagerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ManagerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &ManagerDlg::OnBnClickedButton3)
//	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &ManagerDlg::OnTcnSelchangeTab1)
//ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &ManagerDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// ManagerDlg ��Ϣ�������

CString getNowTImeH1() {
	CString str; //��ȡϵͳʱ�� ����

	CTime tm; tm = CTime::GetCurrentTime();

	str = tm.Format("%Y_%m_%d");

	return str;
}
vector<string> splitc(const string &s, const string &seperator) {
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//�ҵ��ַ������׸������ڷָ�������ĸ��
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

		//�ҵ���һ���ָ������������ָ���֮����ַ���ȡ����
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
CString getNowTImeA() {
	CString str; //��ȡϵͳʱ�� ����

	CTime tm; tm = CTime::GetCurrentTime();

	str = tm.Format("%Y-%m-%d %X");

	return str;
}

void writeInto(const char *fileName)
{
	ifstream in;
	char line[1024] = { '\0' };
	in.open("Database\\login.txt");
	int i = 0;
	string tempStr;
	while (in.getline(line, sizeof(line)))
	{
		i++;
		vector<string> arr = splitc(line, ",");
		tempStr += arr[1] + ",null" + "," + to_string(0);
		tempStr += '\n';
	}
	in.close();
	ofstream out;
	out.open(fileName);
	out.flush();
	out << tempStr;
	out.close();
}
void ManagerDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString timee = getNowTImeH1();
	char * ttt;

	LPCTSTR p = timee.GetBuffer(0);
	timee.ReleaseBuffer();
	ttt = new char[timee.GetLength() + 1];
	strcpy_s(ttt, timee.GetLength() + 1, CT2CA(p));
	//...  
	string bbb = "Database\\" + (string)ttt + ".txt";
	FILE *fp = fopen(bbb.c_str(), "a");
	writeInto(bbb.data());
	MessageBox(_T("�ɹ�����ǩ��"));
}

void ManagerDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString timee = getNowTImeH1();
	char * ttt;
	LPCTSTR p = timee.GetBuffer(0);
	timee.ReleaseBuffer();
	ttt = new char[timee.GetLength() + 1];
	strcpy_s(ttt, timee.GetLength() + 1, CT2CA(p));
	//...  
	string bbb = "Database\\" + (string)ttt + ".txt";
	FILE *fp = fopen(bbb.c_str(), "a");
	writeInto(bbb.data());
	MessageBox(_T("�������³ɹ�"));
}


void ManagerDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString timee = getNowTImeH1();
	char * ttt;

	LPCTSTR p = timee.GetBuffer(0);
	timee.ReleaseBuffer();
	ttt = new char[timee.GetLength() + 1];
	strcpy_s(ttt, timee.GetLength() + 1, CT2CA(p));
	string bbb = "Database\\" + (string)ttt + ".txt";
	ifstream fin(bbb);
	if (!fin)
	{
		MessageBox(_T("����δ����ǩ��"));
		return;
	}
	else
	{
		CString str1;
		GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowText(str1);
		
		char * ttt1;

		LPCTSTR p1 = str1.GetBuffer(0);
		str1.ReleaseBuffer();
		ttt1 = new char[str1.GetLength() + 1];
		strcpy_s(ttt1, str1.GetLength() + 1, CT2CA(p1));
		vector<string> ve = splitc((string)ttt1, "/");
		string ddd = "Database\\" + ve[0] +"_"+ve[1]+"_"+ve[2]+ ".txt";
		fstream fin(ddd);
		string readlinea;
		int isPipei = 0;
		string tempStr= "ѧ��\tʱ��\t\t����\n";;
		int isnull = 0;
		while (getline(fin, readlinea)) {
			
			vector<string> arr = splitc(readlinea, ",");
			const char*  card = arr[0].data();
			const char*  time = arr[1].data();
			const char*  isqian = arr[2].data();
			//const char* password = arr[2].data();
			/*char *name = "admin";
			char *password = "admin";*/
			CString temp1 = (CString)card;
			string ta = "";
			int b = atoi(arr[2].c_str());
			if (b == 0) {
				ta = "ȱ��";
			}
			else if (b == 1) {
				ta = "����";
			}
			else
			{
				ta = "����";
			}
			
			isnull = 1;
			tempStr += arr[0] + "\t" + arr[1] + "\t" + ta+"\n";
		}
		if (isnull==0) {
			CEdit*  pEdit2 = (CEdit*)GetDlgItem(IDC_EDIT7);//��ȡ��Ӧ�ı༭��ID
			pEdit2->SetWindowText(_T("�����κ�����")); //����Ĭ����ʾ������ 
		}
		else
		{
			CEdit*  pEdit2 = (CEdit*)GetDlgItem(IDC_EDIT7);//��ȡ��Ӧ�ı༭��ID
			pEdit2->SetWindowText((CString)tempStr.c_str()); //����Ĭ����ʾ������ 
		}
		
		//MessageBox((CString)tempStr.c_str());
		//AfxMessageBox(str);qiandaoxinxi
	}
}
