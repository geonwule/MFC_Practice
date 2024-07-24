#include "pch.h"
#include "ServerSocket.h"
#include "SC_ChatServerDlg.h" //CSCChatServerDlg

CServerSocket::CServerSocket(CSCChatServerDlg* pDialog)
{
	m_pDialog = pDialog;
}

void CServerSocket::OnAccept(int nErrorCode)
{
	CClientSocket* pClientSocket = new CClientSocket(m_pDialog);
	if (Accept(*pClientSocket))
	{
		m_pDialog->AddClient(pClientSocket);
		AfxMessageBox(_T("Client Connected"));
	}
	else
		delete pClientSocket;
}

CClientSocket::CClientSocket(CSCChatServerDlg* pDialog)
{
	m_pDialog = pDialog;
	//AsyncSelect(FD_READ | FD_CLOSE);
}

void CClientSocket::OnReceive(int nErrorCode)
{
	if (nErrorCode != 0) {
		AfxMessageBox(_T("OnReceive Error"));
		return;
	}

	char szBuffer[1024];
	ZeroMemory(szBuffer, 1024);

	if (Receive(szBuffer, 1024) > 0)
	{
		AfxMessageBox(_T("OnReceive ") + CString(szBuffer));
		CString strMessage;
		strMessage.Format(_T("fd(%d): %s"), 5, CString(szBuffer));
		m_pDialog->AddMessage(strMessage);
	}
	else
	{
		AfxMessageBox(_T("Receive Error"));
		Close();
	}
}