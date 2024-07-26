#pragma once

#include "CSocCom.h"
#include <list>
#define UM_ACCEPT WM_USER+1

// CSocServer 명령 대상
// 서버용 소켓
class CSocServer : public CSocket
{
public:
	CSocServer();
	virtual ~CSocServer();

	// 연결요청을 한 클라이언트 서버와 실제 연결이 되는 소켓
	CSocCom m_socCom[MAX_CLIENT_COUNT]; 

	// 통신 소켓 리턴
	CSocCom* GetAcceptSocCom();

	std::list<int> m_index; // 접속한 클라이언트의 인덱스를 저장하는 리스트

	//메인 윈도우 핸들
	HWND m_hWnd;

	//소켓 클래스와 메인 윈도우를 연결시킴
	void CSocServer::Init(HWND hWnd);

	//클라이언트 접속 요청 처리
	virtual void OnAccept(int nErrorCode);
};


