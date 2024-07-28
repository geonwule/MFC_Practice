
// GeonSignPKIDlg.h: 헤더 파일
//

#pragma once


// CGeonSignPKIDlg 대화 상자
class CGeonSignPKIDlg : public CDialogEx
{
// 생성입니다.
public:
	CGeonSignPKIDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GEONSIGNPKI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strCA;
	CString m_strRA;
	CString m_strOCSP;
	afx_msg void OnClickedButtonCaRegister();
	afx_msg void OnClickedButtonCaRevoke();
	CA m_CA;
	RA m_RA;
	afx_msg void OnClickedButtonRaRegister();
	afx_msg void OnClickedButtonRaUnregister();
	afx_msg void OnClickedButtonOcspCheck();
	OCSP m_OCSP;
};
