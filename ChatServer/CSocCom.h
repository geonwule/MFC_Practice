#pragma once

// CSocCom 명령 대상
// 통신용 소켓
#define UM_RECEIVE WM_USER+2
#define MAX_CLIENT_COUNT 3 // 최대 접속가능 수

#define SOC_CLIENT_CONNECT "접속성공"
#define SOC_CLIENT_DISCONNECT "클라이언트 종료"
class CSocCom : public CSocket
{
public:
	CSocCom();
	virtual ~CSocCom(); 

	// 메인 윈도우 핸들
	HWND m_hWnd;

	// 소켓 클래스와 메인 윈도우를 연결시킴
	void CSocCom::Init(HWND hWnd);

	// 데이터가 도착했다는것을 알려줌
	virtual void OnReceive(int nErrorCode);

	int m_index;
};


