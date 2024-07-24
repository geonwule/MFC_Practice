#pragma once
#include <afxsock.h>

class CServerSocket : public CAsyncSocket
{
public:
	CServerSocket(CDialog* pDialog);
	virtual void OnAccept(int nErrorCode);

private:
	CDialog* m_pDialog;
public:
	int test();
};

class CClientSocket : public CAsyncSocket
{
public:
	CClientSocket(CDialog* pDialog);
	virtual void OnReceive(int nErrorCode);

private:
	CDialog* m_pDialog;
};
