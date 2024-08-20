
// StockServerDlg.h: 헤더 파일
//

#pragma once
#include <vector>
#include "Observer.h"
#include "CSocServer.h"

// CStockServerDlg 대화 상자
class CStockServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CStockServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STOCKSERVER_DIALOG };
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

	float m_fprice1;
	float m_fprice2;
	float m_fprice3;
	float m_fprice4;

	CString m_strID;
	CString m_strPrice;
	int setPrice(int id, CString price);
	int upPrice(int id);
	int downPrice(int id);

	int m_clientID;
	CSocServer m_socServer;
	std::vector<Observer*> m_observers;

public:
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonSet();
private:
	int notifyPrice(int id);
public:
	CString getPrice(int id);
protected:
	afx_msg LRESULT OnAccpet(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam);
};
