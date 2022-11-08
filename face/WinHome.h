#pragma once
#include "afxdialogex.h"


// WinHome 对话框

class WinHome : public CDialogEx
{
	DECLARE_DYNAMIC(WinHome)

public:
	WinHome(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~WinHome();
	BOOL OnInitDialog();



// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FACE_DIALOG_HOME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_img_head;
	CStatic m_text_name;
	CStatic m_text_yanzhi;
	CStatic m_text_job;
	CStatic m_text_bib;
	CStatic m_text_qq;


	char m_user_name[64];
	int m_yan_zhi;
	char m_job[64];
	
	CFont m_font;
	ATL::CImage imgR;
};
