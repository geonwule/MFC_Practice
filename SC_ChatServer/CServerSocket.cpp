#include "pch.h"
#include "ServerSocket.h"
#include "SC_ChatServerDlg.h"

CServerSocket::CServerSocket(CDialog* pDialog)
{
	m_pDialog = pDialog;
}

void CServerSocket::OnAccept(int nErrorCode)
{
	CClientSocket* pClientSocket = new CClientSocket(m_pDialog);
	Accept(*pClientSocket);
}

CClientSocket::CClientSocket(CDialog* pDialog)
{
	m_pDialog = pDialog;
}

void CClientSocket::OnReceive(int nErrorCode)
{
	char buf[1024];
	int len = Receive(buf, 1024);
	buf[len] = '\0';

	CString str(buf);
	CSCChatServerDlg* pDlg = (CSCChatServerDlg*)m_pDialog;
	pDlg->AddMessage(str);
}