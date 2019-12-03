// StudentMainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Finger.h"
#include "StudentMainDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include<string>
#include<vector>
#include"Login.h"
#include "CZKFPEngX.h"//����ָ�Ʋɼ���SDK


int isclass = 0;
// StudentMainDlg �Ի���
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
	CEdit*  pEdit = (CEdit*)GetDlgItem(IDC_EDIT5);//��ȡ��Ӧ�ı༭��ID
	pEdit->SetWindowText(sc_user); //����Ĭ����ʾ������ 
	CEdit*  pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT2);//��ȡ��Ӧ�ı༭��ID
	extern CString usera;
	pEdit1->SetWindowText(usera); //����Ĭ����ʾ������ 

	CEdit*  pEdit2 = (CEdit*)GetDlgItem(IDC_EDIT1);//��ȡ��Ӧ�ı༭��ID
	extern CString namea;
	pEdit2->SetWindowText(namea); //����Ĭ����ʾ������ 
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
	CString str; //��ȡϵͳʱ�� ����

	CTime tm; tm = CTime::GetCurrentTime();

	str = tm.Format("%Y-%m-%d %X");

	return str;
}
// StudentMainDlg ��Ϣ�������
CString getNowTImeH() {
	CString str; //��ȡϵͳʱ�� ����

	CTime tm; tm = CTime::GetCurrentTime();

	str = tm.Format("%Y_%m_%d");

	return str;
}

void StudentMainDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	isclass = 1;
}


void StudentMainDlg::OnBnClickedRadio3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	isclass = 2;
}
int ishasbegin=0;
vector<string> splitb(const string &s, const string &seperator) {
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
/************************************************************************/
/* �޸��ļ�ĳ������
���룺�ļ��� fileName   �к�   lineNum ,�޸ĵ����� content
������ļ��� fileName
�޷���ֵ
tip��1,lineNum�ӵ�һ�п�ʼ 2.content��Ҫ���ϻ��з�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox(_T("����Ա��δ����ǩ��"));
		return;
	}
	fin.close();
	modifyContentInFile(bbb.data(), usera, isclass);

	if (ishasbegin == 1) {
		if (isclass == 1) {
			MessageBox(_T("�Ͽ�ǩ���ɹ�"));
		}
		else {
			MessageBox(_T("�¿�ǩ���ɹ�"));
		}
		
	}
	else if (ishasbegin == 2) {
		MessageBox(_T("����ǩ���ɹ��������ظ�ǩ��"));
	}
	else if (ishasbegin == 3) {
		MessageBox(_T("�����Ͽ�ǩ��"));
	}
	else {
		MessageBox(_T("��δ����༶������ϵ����Ա���°༶����"));
	}
	
}
int ShowImageInCtrl1(CStatic & picCtrl, char * filename)
{

	//���ϵͳ������ԭ����ʾ��ͼ������
	//HDC hdc = this->GetDC()->m_hDC;//�����ʾ�豸�����Ļ����ľ��
	//int x = 160;//ͼ����������ϽǺ�����
	//int y = 80;//ͼ����������Ͻ�������
	//m_zkfpEng.PrintImageAt(int(hdc), x, y, 0, 0);//����ͼ��//ûʵ��
	//����ͼ��
	CImage image;
	HRESULT hResult = image.Load(ToWideChar(filename));
	int width = image.GetWidth();//ͼ����
	int height = image.GetHeight();//ͼ��߶�
								   //������ʾ����
	CRect rect;//������ζ���
	picCtrl.GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������
	CDC *pDc = picCtrl.GetWindowDC();//���picture�ؼ������û������
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);//����λͼ����ģʽ
													//��ʾͼ��
	image.StretchBlt(pDc->m_hDC, rect, SRCCOPY);//��ͼ�񻭵�picture�ؼ���ʾ�ľ�������
												//���¿ؼ���ʾ
	picCtrl.Invalidate(false);//���¿ؼ���ʾ
							  //�ͷű����ռ�
	image.Destroy();
	picCtrl.ReleaseDC(pDc);//�ͷ�picture�ؼ������û������


	return 0;
}
void StudentMainDlg::OnBnClickedButton1()
{
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int z = 2;
	z = m_zkfpEng.InitEngine();//����ָ�Ʋɼ�����
	MessageBox(_T("�밴ѹָ��ʶ����."), _T("��ʾ"));//��ʾ��Ϣ
	Sleep(3000);
	int a = 1;
	if (z == 0) {
		//MessageBox(_T("�ɼ������ӳɹ�."), _T("��ʾ"));//��ʾ��Ϣ
		 MessageBox(L"�ɼ�ָ�Ƴɹ�");


		//��ע��ѧ������ָ�Ʋɼ�
		
	
		//����
		//CString fileName = L"L01_01.bmp";//Ĭ�ϴ򿪵��ļ���
		CString defaulDir = L"./fingerimages";//Ĭ�ϴ򿪵��ļ�·��
		CString filename = L"1.bmp";

		CString filePath = defaulDir + "\\" + filename;
		//ָ�����ƣ�ָ��·��
		m_zkfpEng.SaveBitmap(filePath);
		char stepImgFile1[MAX_PATH] = { STEP_IMG1 };
		CopyFile(filePath, ToWideChar(stepImgFile1), false);//�����ļ���Դ��Ŀ��

															//��ͼƬ��չʾͼƬ
		ShowImageInCtrl1(m_pic, STEP_IMG1);
		int a = 0;
		a++;
		return;
	}
	else if (z == 1) {
		//MessageBox(_T("ָ��ʶ�������������ʧ��."), _T("��ʾ"));//��ʾ��Ϣ 
		MessageBox(L"ָ��ʶ�������������ʧ��");
	}
	else if (z == 2) {
		//MessageBox(_T("û������ָ��ʶ����."), _T("��ʾ"));//��ʾ��Ϣ 
		MessageBox(L"û������ָ��ʶ����");
	}
	else
	{
		MessageBox(L"a" + z);
	}
}
