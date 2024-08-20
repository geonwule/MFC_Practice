#pragma once

#define UM_RECEIVE WM_USER + 1

#include "Observer.h"
#include <string>
#include <cstring>

class CSocClient : public Observer
{
private :
	int _id;
	HWND m_hWnd;

public:
	CSocClient(const int id, HWND hWnd);
	~CSocClient() override;

	void CSocClient::Init(HWND hWnd);

	void update(int id, CString strPrice) override {
		char pTmp[256];
		memset(pTmp, 0, sizeof(pTmp));
		CString strTmp;
		strTmp.Format(_T("%d"), id);
		strTmp += ',';
		strTmp += strPrice;
		strTmp += "\r\n"; //CRLF
		CStringA strAnsiData(strTmp);
		Send(strAnsiData, strAnsiData.GetLength());
		// "1,2000.00"

		//AfxMessageBox(_T("update ") + strTmp); //test
	}

	int getID() const override;

	virtual void OnReceive(int nErrorCode);
};

