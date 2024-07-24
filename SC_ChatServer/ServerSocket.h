#pragma once
#include <afxsock.h>

class CSCChatServerDlg;

class CServerSocket : public CAsyncSocket
{
public:
	CServerSocket(CSCChatServerDlg* pDialog);
	virtual void OnAccept(int nErrorCode);

private:
	CSCChatServerDlg* m_pDialog;
};

class CClientSocket : public CAsyncSocket
{
public:
	CClientSocket(CSCChatServerDlg* pDialog);
	virtual void OnReceive(int nErrorCode);

private:
	CSCChatServerDlg* m_pDialog;
};
