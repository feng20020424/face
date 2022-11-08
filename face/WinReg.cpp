// WinReg.cpp: 实现文件
//

#include "pch.h"
#include "face.h"
#include "afxdialogex.h"
#include "WinReg.h"
#include<opencv2/opencv.hpp>
using namespace cv;

#include"tools.h"

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")


#include"faceTool.h"
#include"WinWelcome.h"


extern MHandle faceModel;//人脸识别模块

static VideoCapture cap;//定义一个摄像头变量




// WinReg 对话框

IMPLEMENT_DYNAMIC(WinReg, CDialogEx)

WinReg::WinReg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FACE_DIALOG_ZC, pParent)
{

}

WinReg::~WinReg()
{
}

void WinReg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_butMouse);
	DDX_Control(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_XH, m_snowBG);
	DDX_Control(pDX, IDC_PHOTO_REAL, m_sxt);
}


BEGIN_MESSAGE_MAP(WinReg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &WinReg::OnEnChangeEdit1)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &WinReg::OnBnClickedButton1)
END_MESSAGE_MAP()


// WinReg 消息处理程序


void WinReg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

BOOL WinReg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	LoadPicture(m_faceBg, IDB_PNG4);
	m_butMouse.Init(IDB_PNG5, 4, BTN_TYPE_NORMAL);

	CString name;
	for (int i = 0; i < 16; i++)
	{
		name.Format(L"C:/code/face/face/res/snow/snow_%d.bmp", i);
		m_snows[i] = (HBITMAP)LoadImage(0, name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		SetTimer(1, 30, NULL);
	}
	CFont font;
	font.CreatePointFont(200, L"花文行楷");
	m_name.SetFont(&font);
	::MoveWindow(m_snowBG. m_hWnd, 440, 0, 640, 609, 1);
	::MoveWindow(m_sxt.m_hWnd, 440, 64, 640, 480, 1);
	srand(time(NULL));

	return 0;
}


void WinReg::OnPaint()
{
	drawPicOnPait(&m_faceBg, this, 0, 0);
}


void WinReg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static int snowIndex = 0;
	static int count = 0;
	if (nIDEvent == 1)
	{
		m_snowBG.SetBitmap(m_snows[snowIndex]);
		snowIndex = (snowIndex + 1) % 16;
	}
	else if (nIDEvent == 2)
	{
		//使用摄像头拍摄头像并进行显示
		refreshCamera(&cap, m_hWnd, IDC_PHOTO_REAL);
		count++;
		if (count == 1)
		{
			mciSendString(L"play C:/code/face/face/res/zhuche.mp3",0,0,0);
		}
		else if (count == 30)
		{
			paiZhao(&cap, "tmp.jpg");
			count = 0;
			KillTimer(2);//关闭定时器
			cap.release();//关闭摄像头



			//计算人脸相似度
			IplImage* img1 = cvLoadImage("tmp.jpg");
			IplImage* img2 = cvLoadImage("C:/code/face/face/res/neijun.jpg");
			float xishu = faceCompare(faceModel, img1, img2);
			int yanzhi = xishu * 1000 + 80 + rand() % 15;
			if (yanzhi <= 0)
			{
				yanzhi = 60;
			}
			else if (yanzhi >= 1000)
			{
				yanzhi = 99;
			}
			//生成职业

			const char* jobs[] = { "精神病院长","精神病主任","精神科实习生" };

			//
			CString editName;
			m_name.GetWindowText(editName);
			USES_CONVERSION;
			char* editName2 = T2A(editName);

			char cmd[521];
			sprintf_s(cmd, sizeof(cmd), "move tmp.jpg users\\%s-%s-%d.jpg", jobs[rand() % 3], jobs[rand() % 3], editName2, yanzhi);
			system(cmd);

			WinWelcome win;
			win.DoModal();

			CDialogEx::OnOK();
		}


	}


	CDialogEx::OnTimer(nIDEvent);
}


void WinReg::OnBnClickedButton1()
{

	if (m_name.GetWindowTextLength() == 0)
	{
		MessageBox(L"请输入用户名");
		return;

	}


	KillTimer(1);



	//使用opencv处理摄像头
	HBITMAP pic=(HBITMAP)LoadImage(0, L"C:/code/face/face/res/wall.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_snowBG.SetBitmap(pic);

	cap.open(0);

	SetTimer(2, 100, NULL);

}
