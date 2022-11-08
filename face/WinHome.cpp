// WinHome.cpp: 实现文件
//

#include "pch.h"
#include "face.h"
#include "afxdialogex.h"
#include "WinHome.h"
#include<graphics.h>
#include"tools.h"

// WinHome 对话框

IMPLEMENT_DYNAMIC(WinHome, CDialogEx)

WinHome::WinHome(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FACE_DIALOG_HOME, pParent)
{

}

WinHome::~WinHome()
{
}

BOOL WinHome::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	char fileName[256];
	sprintf_s(fileName, sizeof(fileName), "users/%s-%s-%d.jpg",m_job,m_user_name,m_yan_zhi);

	IMAGE img1, img2;
	loadimage(&img1, CString(fileName), 200, 150, true);

	loadimage(&img2, L"res/yz2.png");
	putimagePNG(0, 0, &img2, &img1);
	saveimage(L"hc.jpg", &img1);
	imgR.Load(L"hc.jpg");
	m_img_head.SetBitmap(imgR);

	m_font.CreatePointFont(200, L"宋体");

	m_text_name.SetFont(&m_font);
	m_text_name.SetWindowText(CString(m_user_name));

	m_text_yanzhi.SetFont(&m_font);
	CString yanzhi;

	yanzhi.Format(L"颜值：%d",m_yan_zhi);
	m_text_yanzhi.SetWindowText(yanzhi);

	m_text_job.SetFont(&m_font);
	m_text_job.SetWindowText(CString(m_job));

	m_text_bib.SetFont(&m_font);
	m_text_bib.SetWindowText(L"马牛逼666666");

	m_text_qq.SetFont(&m_font);
	m_text_qq.SetWindowText(L"66666666666");




	return 0;
}

void WinHome::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMG, m_img_head);
	DDX_Control(pDX, IDC_TEXT_NAME, m_text_name);
	DDX_Control(pDX, IDC_TEXT_YANZHI, m_text_yanzhi);
	DDX_Control(pDX, IDC_TEXT_JOB, m_text_job);
	DDX_Control(pDX, IDC_TEXT_BIB, m_text_bib);
	DDX_Control(pDX, IDC_TEXT_QQ, m_text_qq);
}


BEGIN_MESSAGE_MAP(WinHome, CDialogEx)
END_MESSAGE_MAP()


// WinHome 消息处理程序
