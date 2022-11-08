#pragma once
#include "afxdialogex.h"
#include "ButtonPNG.h"

// WinReg 对话框

class WinReg : public CDialogEx
{
	DECLARE_DYNAMIC(WinReg)

public:
	WinReg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~WinReg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FACE_DIALOG_ZC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	BOOL OnInitDialog();
	ButtonPNG m_butMouse;
	CEdit m_name;
	CStatic m_snowBG;
	CImage m_faceBg;
	afx_msg void OnPaint();
	HBITMAP m_snows[16];
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	CStatic m_sxt;
};
