﻿
// SC_ChatServerDlg.h: 헤더 파일
//

#pragma once
#include "ServerSocket.h"


// CSCChatServerDlg 대화 상자
class CSCChatServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CSCChatServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	virtual ~CSCChatServerDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SC_CHATSERVER_DIALOG };
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
	CString m_strInput;
public:
	afx_msg void OnEnChangeEditInput();
	afx_msg void OnBnClickedButtonInput();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
	CListBox m_strRoom;

public:
	int AddMessage(CString msg);

private:
	CServerSocket* m_pServerSocket;
	CClientSocket* m_pClientSocket;
	CList<CClientSocket*> m_ClientSocketList;
	BOOL m_bIsHost;

public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
};
