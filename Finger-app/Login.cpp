// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Finger.h"
#include "Login.h"
#include "afxdialogex.h" 

#include <sapi.h>
#include <sphelper.h>
#pragma comment(lib,sapi.lib) 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;
// CLogin �Ի���

IMPLEMENT_DYNAMIC(CLogin, CDialog)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, m_user);
	DDX_Control(pDX, IDC_EDIT4, m_pass);
}


BEGIN_MESSAGE_MAP(CLogin, CDialog)
	ON_BN_CLICKED(IDOK, &CLogin::OnBnClickedOk)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK2, &CLogin::OnBnClickedOk2)
//	ON_EN_CHANGE(IDC_EDIT3, &CLogin::OnEnChangeEdit3)
ON_BN_CLICKED(IDC_RADIO1, &CLogin::OnBnClickedRadio1)
ON_BN_CLICKED(IDC_RADIO2, &CLogin::OnBnClickedRadio2)
ON_BN_CLICKED(IDOK5, &CLogin::OnBnClickedOk5)
ON_BN_CLICKED(IDOK3, &CLogin::OnBnClickedOk3)
ON_EN_CHANGE(IDC_EDIT3, &CLogin::OnEnChangeEdit3)
END_MESSAGE_MAP()

CString usera;
CString namea;
int guanliyuan = 0;

//��½
void CLogin::OnBnClickedOk()
{
	if (guanliyuan == 0) {
		MessageBox(_T("��ѡ�����"));
	}
	else if (guanliyuan == 1) {
		// ��ͨ�û�(ѧ��)��½
		CString c_user;
		m_user.GetWindowText(c_user);
		CString c_pass;
		m_pass.GetWindowText(c_pass);
		int ispipei = login(c_user, c_pass);
		if ((c_pass.GetLength() == 0) || c_user.GetLength() == 0) {
			MessageBox(_T("�������û�������"));
		}
		if (ispipei == 1) {
			MessageBox(_T("��¼�ɹ�"));
			usera = c_user;
			// ��ת��ѧ������
			StudentMainDlg studentDlg;
			studentDlg.DoModal();
		}
		else if (ispipei == 2) {
			MessageBox(_T("���û�������,��ע��"));
			CRegistDlg m_registDlg;
			m_registDlg.DoModal();

		}
		else
		{
			MessageBox(_T("�û����������"));
		}
	}
	else if (guanliyuan==2)
	{
		// ����Ա(��ʦ)��½
		CString c_user;
		m_user.GetWindowText(c_user);
		CString c_pass;
		m_pass.GetWindowText(c_pass);
		if (c_user == "admin"&&c_pass == "admin") {
			
			MessageBox(_T("����Ա��½�ɹ�"));
			ManagerDlg mana;
			mana.DoModal();
		}
		else
		{
			MessageBox(_T("�û����������"));
		}
	}
	
	
}
vector<string> split(const string &s, const string &seperator) {
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

// �����û����������½
int login(CString user,CString pass) {
	fstream fin("./Database\\login.txt");
	string readlinea;
	int isPipei = 0;
	while (getline(fin,readlinea))
	{
		
		vector<string> arr = split(readlinea, ",");
		const char* card = arr[1].data();
		const char* password = arr[2].data();
		const char* name = arr[3].data();
		CString temp1 = (CString)card;
		CString temp2 = (CString)password;
		CString temp3 = (CString)name;
		if (user.Compare(temp1)==0 && pass.Compare(temp2)==0) {
			// ƥ��ɹ�
			isPipei = 1;
			namea = temp3;
			break;
		}
		if (user.Compare(temp1)) {
			isPipei = 2;
		}		
	}
	fin.close();
	return isPipei;
}
int saveData(char * dstFile, float * data, int width, int height)
{
	ofstream fout(dstFile, ios::out);//
	
	fout.close();

	return 0;
}


HBRUSH CLogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	static CBrush gBr;
	static bool isInited;
	if (!isInited)
	{
		CBitmap bitmap;
		bitmap.LoadBitmapW(IDB_BITMAP5);
		gBr.CreatePatternBrush(&bitmap);
		COLORREF clearColor = -1;
		bitmap.DeleteObject();
		isInited = true;
	}
	if (pWnd == this)
	{
		pDC->SetBkMode(TRANSPARENT);
		return gBr;
	}
	else
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(WHITE_BRUSH);
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

// ע��button�߼�
void CLogin::OnBnClickedOk2()
{
	CString str1 = L"./fingerimages";
	CreateDirectory(str1, NULL);
	CString str2 = L"./temp";
	CreateDirectory(str2, NULL);
	CString str3 = L"./Database";
	CreateDirectory(str3, NULL);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRegistDlg m_registDlg;
	m_registDlg.DoModal();
}
bool getvoice(CString s) {
	ISpVoice * pVoice = NULL; //��ʼ��COM 
	if (FAILED(CoInitialize(NULL)))
	{
		AfxMessageBox(_T("��ʼ����������ʧ��"), MB_OKCANCEL | MB_ICONQUESTION);
		return false;
	}
	//��ʼ��SAPI 
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	ISpObjectToken * pSpObjectToken = NULL;
	if (SUCCEEDED(SpFindBestToken(SPCAT_VOICES, L"language=804", NULL, &pSpObjectToken)))//804�������� 
	{
		pVoice->SetVoice(pSpObjectToken);//������С
		pVoice->SetRate(-2);//����
		pSpObjectToken->Release();
	}
	else {
		AfxMessageBox(_T("û�а�װ΢��������!"), MB_OKCANCEL | MB_ICONQUESTION);
		return false;
	}
	//�ʶ��༭���е����� 
	if (SUCCEEDED(hr))
	{
		//CString strText = s;//�������ʶ��Ļ� ����������   
		hr = pVoice->Speak(s.AllocSysString(), 0, NULL);
		pVoice->Release(); pVoice = NULL;
	}
}


void CLogin::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	guanliyuan = 1;

}


void CLogin::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	guanliyuan = 2;
}


void CLogin::OnBnClickedOk5()
{
	// TODO: Add your control notification handler code here
	exit(0);
}


void CLogin::OnBnClickedOk3()
{
	if (guanliyuan == 0) {
		MessageBox(_T("��ѡ�����"));
	}
	else if (guanliyuan == 1) {
		// ��ͨ�û�(ѧ��)��½
		CString c_user;
		m_user.GetWindowText(c_user);
		CString c_pass;
		m_pass.GetWindowText(c_pass);
		int ispipei = login(c_user, c_pass);
		if ((c_pass.GetLength() == 0) || c_user.GetLength() == 0) {
			MessageBox(_T("�������û�������"));
		}
		if (ispipei == 1) {
			MessageBox(_T("��¼�ɹ�"));
			usera = c_user;
			// ��ת��ѧ������
			StudentMainDlg studentDlg;
			studentDlg.DoModal();
		}
		else if (ispipei == 2) {
			MessageBox(_T("���û�������,��ע��"));
			CRegistDlg m_registDlg;
			m_registDlg.DoModal();

		}
		else
		{
			MessageBox(_T("�û����������"));
		}
	}
	else if (guanliyuan == 2)
	{
		// ����Ա(��ʦ)��½
		CString c_user;
		m_user.GetWindowText(c_user);
		CString c_pass;
		m_pass.GetWindowText(c_pass);
		if (c_user == "admin"&&c_pass == "admin") {

			MessageBox(_T("����Ա��½�ɹ�"));
			ManagerDlg mana;
			mana.DoModal();
		}
		else
		{
			MessageBox(_T("�û����������"));
		}
	}
}



void CLogin::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
