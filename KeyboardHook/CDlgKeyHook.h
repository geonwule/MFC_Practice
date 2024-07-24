#pragma once
#include "afxdialogex.h"


// CDlgKeyHook 대화 상자

class CDlgKeyHook : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgKeyHook)

public:
	CDlgKeyHook(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgKeyHook();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_KEY_HOOK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonKeyHook();
	afx_msg void OnBnClickedButtonKeyUnhook();
};
