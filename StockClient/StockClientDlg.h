
// StockClientDlg.h: 헤더 파일
//

#pragma once

#include "CSocClient.h"


// CStockClientDlg 대화 상자
class CStockClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CStockClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STOCKCLIENT_DIALOG };
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
private:
	CListBox m_listBox1;
	CListBox m_listBox2;
	CListBox m_listBox3;
	CListBox m_listBox4;
	CString m_strStatus;
	CString m_strIP;

	CSocClient m_socClient;
protected:
	afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnClickedButtonConnect();
private:
	CString m_strTime1;
	CString m_strTime2;
	CString m_strTime3;
	CString m_strTime4;
public:
	afx_msg void OnBnClickedCancel();
};
