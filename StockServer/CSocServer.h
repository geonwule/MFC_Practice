#pragma once

#include "CSocClient.h"
#include <afxsock.h>

#define UM_ACCEPT WM_USER + 2

class CSocServer : public CSocket
{

public:
	CSocServer();
	~CSocServer();

	HWND m_hWnd;
	void CSocServer::Init(HWND hWnd);

	virtual void OnAccept(int nErrorCode);
};

