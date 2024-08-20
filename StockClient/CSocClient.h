#pragma once

#define UM_RECEIVE WM_USER + 1

// CSocClient 명령 대상

class CSocClient : public CSocket
{
private:
	HWND m_hWnd;

public:
	CSocClient();
	virtual ~CSocClient();

	void CSocClient::Init(HWND hWnd);
	virtual void OnReceive(int nErrorCode);
};


