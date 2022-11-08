// winlogin.cpp: 实现文件
//
#define _CRT_SECURE_NO_WARNINGS 1
#include "pch.h"
#include "face.h"
#include "afxdialogex.h"
#include "winlogin.h"

#include<opencv2/opencv.hpp>
using namespace cv;

#include"tools.h"

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")


#include"faceTool.h"
#include"WinWelcome.h"
#include<vector>

extern MHandle faceModel;//人脸识别模块

static VideoCapture cap;//定义一个摄像头变量

// winlogin 对话框

IMPLEMENT_DYNAMIC(winlogin, CDialogEx)

winlogin::winlogin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FACE_DIALOG_Dl, pParent)
{

}

winlogin::~winlogin()
{
}

BOOL winlogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	LoadPicture(m_imgBG, IDB_PNG4);
	m_btn_sl.Init(IDB_PNG5, 4, BTN_TYPE_NORMAL);
	/*char name[256];*/
	CString name;

	for (int i = 0; i < 16; i++)
	{
	/*	sprintf(name, "res/snow/snow_%d.bmp", i);*/
		name.Format(L"C:/code/face/face/res/snow/snow_%d.bmp", i);
		m_snows[i]=(HBITMAP)LoadImage(0, name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	//启动定时器
	SetTimer(1, 30, NULL);

	::MoveWindow(m_xh.m_hWnd, 440, 0, 640, 609, 1); 
	return 0;
}

void winlogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_sl);
	DDX_Control(pDX, IDC_XH, m_xh);
	DDX_Control(pDX, IDC_PHOTO_REAL, m_sxt);
}


BEGIN_MESSAGE_MAP(winlogin, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &winlogin::OnBnClickedButton1)
END_MESSAGE_MAP()


// winlogin 消息处理程序


void winlogin::OnPaint()
{
	drawPicOnPait(&m_imgBG, this, 0, 0);
}
//识别函数
bool faceCheck(const char* fileName,  char* userName)
{
	vector <CString> vctPath;
	WIN32_FIND_DATA fileData;
	HANDLE file = FindFirstFile(L"users/*.jpg", &fileData);
	if (file != INVALID_HANDLE_VALUE)
	{
		vctPath.push_back(fileData.cFileName);
		while (FindNextFile(file, &fileData))
		{
			vctPath.push_back(fileData.cFileName);
		}

	}
	IplImage* img1 = cvLoadImage(fileName);
	for (int i = 0; i < vctPath.size(); i++)
	{
		USES_CONVERSION;
		char *otherName = T2A(vctPath[i]);

		char name[256];
		sprintf_s(name, sizeof(name), "users/%s", otherName);

		IplImage *img2 = cvLoadImage(name);
		float ret = faceCompare(faceModel,img1,img2);

		if (ret >= 0.95)
		{
			string tmpStr = otherName;
		 	string nameStr = tmpStr.substr(0, tmpStr.length() - 4);
			strcpy(userName, nameStr.c_str());

			return true;
		}

	}
	


	return false;
}



void winlogin::OnTimer(UINT_PTR nIDEvent)
{
	
	static int snowIndex = 0;
	static int count = 0;
	static char userName[256] = "";
	static bool success = false;


	if (nIDEvent == 1)
	{
		m_xh.SetBitmap(m_snows[snowIndex]);
		snowIndex = (snowIndex + 1) % 16;
	}
	else if (nIDEvent == 2)
	{
		refreshCamera(&cap, m_hWnd, IDC_PHOTO_REAL);
		count++;
		
		if (count == 10)
		{
			const char* fileName = "tmp.jpg";
			paiZhao(&cap, fileName);
			//人脸识别
			if (faceCheck(fileName, userName))
			{
				//播放登录的声音
				mciSendString(L"C:/code/face/face/res/login.mp3", 0, 0, 0);
				success = true;


			}
		}

		else if (count == 20)
		{
				count = 0;
				KillTimer(2);
				cap.release();

				if (success)
				{
					strcpy(m_job,strtok(userName, "-"));
					strcpy(m_userName, strtok(NULL, "-"));
					m_yanzhi = atoi(strtok(NULL, "-"));

					m_logined = true;
					CDialogEx::OnOK();
				}
				else
				{
					MessageBox(L"登陆失败！");
					SetTimer(1, 100, NULL);
					m_logined = false;
				}
		}

		
	}

	CDialogEx::OnTimer(nIDEvent);

}


void winlogin::OnBnClickedButton1()
{
	KillTimer(1);
	cap.open(0);
	
	// 把雪花图片设置成幕布
	HBITMAP pic=(HBITMAP) LoadImage(0, L"C:/code/face/face/res/wall.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_xh.SetBitmap(pic);

	::MoveWindow(m_sxt.m_hWnd, 440, 64, 640, 480, 1);
	SetTimer(2, 100, NULL);

}

