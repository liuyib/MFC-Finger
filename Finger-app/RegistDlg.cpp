// RegistDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Finger.h"
#include "RegistDlg.h"
#include "afxdialogex.h"
#include "Login.h"
#include "CZKFPEngX.h"//����ָ�Ʋɼ���SDK
using namespace std;
int sexa=0;
// CRegistDlg �Ի���

IMPLEMENT_DYNAMIC(CRegistDlg, CDialog)

CRegistDlg::CRegistDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG2, pParent)
	, male(0)
	, female(0)
{
	
}

void CRegistDlg::OnImageReceivedZkfpengx(BOOL * AImageValid)
{
	HDC hdc = this->GetDC()->m_hDC;//�����ʾ�豸�����Ļ����ľ��
	int x = 170;//ͼ����������ϽǺ�����
	int y = 80;//ͼ����������Ͻ�������
	int width = m_zkfpEng.get_ImageWidth();//ͼ��������Ŀ��
	int height = m_zkfpEng.get_ImageHeight();//ͼ��������ĸ߶�
											 //makebmp();
	//ShowImageInCtrl(r_picimg_1, "empty.bmp");
	//ShowImageInCtrl(r_picimg_2, "empty.bmp");//���ͼƬ
	m_zkfpEng.PrintImageAt(int(hdc), x, y, width - 10, height);//����ͼ��
															   //m_staticInfo.SetWindowText(ToWideChar(""));//����֣�

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
END_MESSAGE_MAP()


// CRegistDlg ��Ϣ�������
vector<string> splita(const string &s, const string &seperator) {
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

void CRegistDlg::OnBnClickedOk()
{

	//ע����֤
	CString c_name;
	r_name.GetWindowText(c_name);
	if (c_name.GetLength() == 0)
	{
		MessageBox(_T("����������"));
		return;
	}
	CString c_card;
	r_card.GetWindowText(c_card);
	if (c_card.GetLength() == 0)
	{
		MessageBox(_T("������ѧ��"));
		return;
	}
	CString c_subject;
	r_subject.GetWindowText(c_subject);
	if (c_subject.GetLength() == 0)
	{
		MessageBox(_T("������רҵ"));
		return;
	}
	CString c_class;
	r_class.GetWindowText(c_class);
	if (c_class.GetLength() == 0)
	{
		MessageBox(_T("������༶"));
		return;
	}
	
	if(sexa==0)
	{
		MessageBox(_T("��ѡ���Ա�"));
		return;
	}

	CString rm_pass;
	r_pass.GetWindowText(rm_pass);
	if (rm_pass.GetLength() == 0)
	{
		MessageBox(_T("����������"));
		return;
	}
	CString rm_repass;
	r_repass.GetWindowText(rm_repass);
	if (rm_repass.GetLength() == 0)
	{
		MessageBox(_T("������ȷ������"));
		return;
	}
	if (rm_pass.Compare(rm_repass)) {
		MessageBox(_T("�����ȷ�����벻һ��"));
		return;
	}
	/*out << "This is another line.\n";
	out.close();*/
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
		/*char *name = "admin";
		char *password = "admin";*/
		CString temp1 = (CString)name;
		
		if (temp1.Compare(rm_name)==0) {
			finda = 1;
			MessageBox(_T("���û���ע��"));
			break;
		}
		id++;
		//GetDlgItemTextW(m_user,c_user);
		//m_user.GetWindowText(c_user);
	}
	in.close();
	if (finda == 0) {
		fstream fout("Database\\login.txt", ios::app);
		
		fout <<(id+1) <<","<<strSt1 << "," << strSt2 << "," << strSt3 << "," << strSt4 << "," <<strSt5<<","<< sexa <<","<<""<< endl;
		MessageBox(_T("ע��ɹ�"));
		fout.close();
	}
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}

void insertPicture() {
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	void connect();
	//��ʼ�����������Ϣ
	char info[MAX_PATH] = { 0 };

	//��ȡ�����������ݣ��Ǽ���������
	//UpdateData(true);

	//����ͼ��
	char*srcImgFile = getimgnameandsave();

	//ָ�ƵǼ�
	bool bSaveImg = false;	//�Ƿ񱣴��м���
	char *outImgFile = new char[MAX_PATH];
	//ָ���������ͼ���ļ���
	//Enroll(ToChar(m_name.GetBuffer()), srcImgFile, outImgFile, info, bSaveImg);	//ָ�ƵǼ�			
																				//MessageBox(_T("�Ǽǳɹ�"), _T("��ʾ"));//��ʾ��Ϣ 
																				//MessageBox(L"�Ǽǳɹ�");
	//m_staticInfo.SetWindowText(ToWideChar(info));
	//��ʾͼ��
	//ShowImageInCtrl(r_picimg_1, srcImgFile);	//��ʾԭʼָ��ͼ��
												//ShowImageInCtrl(m_picCtrl2, outImgFile);	//��ʾʶ����ͼ��
}

void CRegistDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	sexa = 2;
}

char* getimgnameandsave()
{
	//char *srcImgFile = NULL;
	BOOL isOpen = TRUE;//ΪTRUE����ʾ���ļ��Ի���ΪFALSE����ʾ�����ļ��Ի���
	//CString defaulDir = L"D:\\fingerimages";//Ĭ�ϴ򿪵��ļ�·��
	//CString fileName = L"L01_01.bmp";//Ĭ�ϴ򿪵��ļ���
	//CString filter = L"�ļ���*.bmp;*.png;*.jpeg��|*.bmp;*.png;*.jpeg||";//�ļ����˵����ͣ�
	//CFileDialog openFileDlg(isOpen, defaulDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	//openFileDlg.GetOFN().lpstrInitialDir = L"D:\\fingerimages\\L01_01.bmp";
	//INT_PTR result = openFileDlg.DoModal();
	
	CString filePath =  L"registimgs\\" + time(0);
	
	//����ͼ��
	char *srcImgFile = new char[filePath.GetLength() + 1];
	LPCTSTR p = filePath.GetBuffer(0);
	filePath.ReleaseBuffer();
	strcpy_s(srcImgFile, filePath.GetLength() + 1, CT2CA(p));
	return srcImgFile;
}
int ShowImageInCtrl(CStatic & picCtrl, char * filename)
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


void CRegistDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int z = 2;

	z = m_zkfpEng.InitEngine();//����ָ�Ʋɼ�����
	MessageBox(_T("�밴ѹָ��ʶ����."), _T("��ʾ"));//��ʾ��Ϣ
	Sleep(3000);
	int a = 1;
	if (z == 0) {
		MessageBox(_T("ָ�ƻ�ȡ�ɹ�."), _T("��ʾ"));//��ʾ��Ϣ

		
		//��ע��ѧ������ָ�Ʋɼ�
		CString rm_name;
		r_name.GetWindowText(rm_name);
		CString rm_card;
		r_card.GetWindowText(rm_card);
		//����
		//CString fileName = L"L01_01.bmp";//Ĭ�ϴ򿪵��ļ���
		CString defaulDir = L"./fingerimages";//Ĭ�ϴ򿪵��ļ�·��
		CString filename = rm_name + rm_card + ".bmp";

		CString filePath = defaulDir + "\\" + filename;
		//ָ�����ƣ�ָ��·��
		m_zkfpEng.SaveBitmap(filePath);
		char stepImgFile1[MAX_PATH] = { STEP_IMG };
		CopyFile(filePath, ToWideChar(stepImgFile1), false);//�����ļ���Դ��Ŀ��

		
															//��ͼƬ��չʾͼƬ
		ShowImageInCtrl(r_picimg_1, STEP_IMG);
		int a = 0;
		a++;
		return;
	}
	else if (z == 1) {
		MessageBox(_T("ָ��ʶ�������������ʧ��."), _T("��ʾ"));//��ʾ��Ϣ 
	}
	else if (z == 2) {
		MessageBox(_T("û������ָ��ʶ����."), _T("��ʾ"));//��ʾ��Ϣ 
	}
	else
	{
		MessageBox(L"a" + z);
	}
}


void CRegistDlg::OnEnChangeEdit7()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
