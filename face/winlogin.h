#pragma once
#include "afxdialogex.h"
#include"ButtonPNG.h"
#include<atlimage.h>
#define _CRT_SECURE_NO_WARNINGS 1



// winlogin 对话框

class winlogin : public CDialogEx
{
	DECLARE_DYNAMIC(winlogin)

public:
	winlogin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~winlogin();
	BOOL OnInitDialog();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FACE_DIALOG_Dl };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	ButtonPNG m_btn_sl;
	CImage m_imgBG;
	afx_msg void OnPaint();
	HBITMAP m_snows[16];
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_xh;
	afx_msg void OnBnClickedButton1();
	CStatic m_sxt;
	char m_job[64];
	char m_userName[64];
	int m_yanzhi;
	bool m_logined;
	
};
