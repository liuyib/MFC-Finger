#pragma once
#include<fstream>
#include<memory.h>
#include<string.h>
#include<iostream>
#include<atlimage.h>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;
// vs 编码为gbk
void Sort(unsigned char*data, int dsize) {
	unsigned char temp = 0;
	for (int i = 0; i < dsize; i++) {
		for (int j = dsize - 1; j > i; j--) {
			if (data[j] < data[j - 1]) {
				temp = data[j];
				data[j] = data[j - 1];
				data[j - 1] = temp;
			}
		}
	}
}


wchar_t*ToWideChar(char *str) {
	int num = MultiByteToWideChar(0, 0, str, -1, NULL, 0);
	wchar_t *wideStr = new wchar_t[num];
	MultiByteToWideChar(0, 0, str, -1, wideStr, num);
	return wideStr;
}

int ReadBMPImgFilePara(char* fileName, int &width, int &height, int &depth) {
	// 载入图像
	CImage image;
	HRESULT hResult = image.Load(ToWideChar(fileName));
	if (FAILED(hResult) || (image.IsNull())) {
		return -1;
	}
	// 获得图像参数
	width = image.GetWidth();
	height = image.GetHeight();
	depth = image.GetBPP();
	if (depth != 8) {
		return -2;
	}
	// 释放变量空间
	image.Destroy();

	return 0;
}

int ReadBMPImgFileData(char *fileName, unsigned char *data) {
	// 载入图像
	CImage image;
	HRESULT hResult = image.Load(ToWideChar(fileName));
	if (FAILED(hResult) || image.IsNull()) {
		return -1;
	}
	int width = image.GetWidth();
	int height = image.GetHeight();
	int depth = image.GetBPP();
	if (depth != 8) {
		return -2;
	}
	memset(data, 0, width*height);
	//读取图像数据
	int pitch = image.GetPitch();
	unsigned char *pData1 = (unsigned char*)image.GetBits();
	unsigned char* pData2 = data;
	unsigned char gray = 0;

	unsigned char *pRow1, *pRow2, *pPix1, *pPix2;
	for (int y = 0; y < height; y++) {
		pRow1 = pData1 + pitch * y;
		pRow2 = pData2 + width * y;
		for (int x = 0; x < width; x++) {
			pPix1 = pRow1 + x;
			gray = *pPix1;

			pPix2 = pRow2 + x;
			*pPix2 = gray;
		}
	}

	// 释放空间
	image.Destroy();
	return 0;
}
int WriteBMPImgFile(char *dstFileName, unsigned char** pusImgData) {
	FILE *fp = fopen(dstFileName, "r+b");
	if (!fp) {
		return -1;
	}

	int imgType, iWidth, iHeight;
	int iStartPos = 0;
	fseek(fp, 10L, SEEK_SET);
	fread((char*)(&iStartPos), 4, 1, fp);
	fseek(fp, 18L, SEEK_SET);
	fread((char*)(&iWidth), 4, 1, fp);
	fread((char*)(&iHeight), 4, 1, fp);
	unsigned short temp;
	fseek(fp, 28L, SEEK_SET);
	fread((char*)(&temp), 2, 1, fp);
	imgType = temp;
	if (imgType != 8) {
		return -2;
	}
	unsigned char* usImgData = *pusImgData;
	int iWidthInFile = 0;
	if (iWidth % 4 > 0) {
		iWidthInFile = iWidth - iWidth % 4 + 4;
	}
	else {
		iWidthInFile = iWidth;
	}
	for (int i = iHeight - 1; i >= 0; i--) {
		fseek(fp, iStartPos, SEEK_SET);
		fwrite((usImgData + i * iWidth), 1, iWidth, fp);
		iStartPos += iWidthInFile;
	}
	fclose(fp);
	return 0;
}
int SaveDataToImageFile(char* srcFile, char* dstFile, unsigned char* data) {
	CopyFile(ToWideChar(srcFile), ToWideChar(dstFile), false);
	WriteBMPImgFile(dstFile, &data);
	return 0;
}
int SaveDataToImageFile(char* srcFile, char* dstFile, float* data, float scale) {
	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcFile, iWidth, iHeight, iDepth);
	CopyFile(ToWideChar(srcFile), ToWideChar(dstFile), false);
	unsigned char *tmpData = new unsigned char[iWidth*iHeight];
	for (int i = 0; i<int(iWidth*iHeight); i++) {
		tmpData[i] = unsigned char((scale* data[i]));
	}

	WriteBMPImgFile(dstFile, &tmpData);
	delete[] tmpData;
	return 0;
}
int SaveDataToTextFile(char* dstFile, unsigned char*data, int width, int height) {
	ofstream fout(dstFile, ios::out);
	if (!fout) {
		return -1;
	}
	// 按指定格式向文件写入数据
	int space = 5;
	for (int i = 0; i < height*width; i++) {
		fout << setw(space) << int(data[i]);
		if (i*width == (width - 1)) {
			fout << endl;
		}
	}
	fout.close();
	return 0;
}
int SaveDataToTextFile(char* dstFile, float *data, int width, int height) {
	ofstream fout(dstFile, ios::out);
	if (!fout) {
		return -1;
	}
	int preci = 6;
	int space = 16;
	fout.precision(preci);
	for (int i = 0; i < height*width - 1; i++) {
		fout << "  " << setw(space) << data[i];
		if (i%width == (width - 1)) {
			fout << endl;
		}
	}
	fout.close();
	return 0;
}
int ReadDatafromTextFile(char* srcFile, unsigned char* data, int iWidth, int iHeight) {
	// 打开源文件
	ifstream fin(srcFile, ios::in);
	if (!fin) {
		return -1;
	}
	// 读取数据
	int d = 0;
	for (int i = 0; i < iHeight*iWidth; i++) {
		fin >> d;
		data[i] = (unsigned char)d;
	}
	// 关闭文件
	fin.close();
	return 0;
}


int ReadDatafromTextFile(char* srcFile, float* data, int iWidth, int iHeight) {
	ifstream fin(srcFile, ios::in);
	if (!fin) {
		return -1;
	}
	for (int i = 0; i < iHeight*iWidth; i++) {
		fin >> data[i];
	}
	fin.close();
	return 0;
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

vector<string> splitc(const string &s, const string &seperator) {
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


CString getNowTImeH1() {
	CString str; //获取系统时间 　　

	CTime tm; tm = CTime::GetCurrentTime();

	str = tm.Format("%Y_%m_%d");

	return str;
}

CString getNowTImeA() {
	CString str; //获取系统时间 　　

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

