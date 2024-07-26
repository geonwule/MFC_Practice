// CSocServer.cpp: 구현 파일
//

#include "pch.h"
#include "ChatServer.h"
#include "CSocServer.h"


// CSocServer

CSocServer::CSocServer()
{
}

CSocServer::~CSocServer()
{
}


// CSocServer 멤버 함수
// 소켓 클래스에서는 소켓의 메시지 (On으로 시작하는 함수) 만을 처리하고, 실제 동작은 메인프로그램에서 수행
// 소켓 클래스와 메인윈도우를 연결시키는것이 필요 -> Init 함수
void CSocServer::Init(HWND hWnd)
{
	// 메인 윈도우 포인터 받기
	m_hWnd = hWnd;
}

// 클라이언트에서 접속 요청이 올 경우 OnAccept 함수가 호출됨
// OnAccept 함수가 호출되면 접속 요청할 한 소켓과 다른 소켓을 연결하기 위해 Accept 함수를 호출 한 뒤 메인 윈도우에 OnAccept 함수가 호출되었다는것을 알려줌
void CSocServer::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	Accept(m_socCom[m_index.front()]); // m_socCom은 연결요청을 한 클라이언트 서버와 실제 연결이 되는 소켓
	SendMessage(m_hWnd, UM_ACCEPT, 0, 0); // 메인 윈도우에 UM_ACCEPT라는 사용자 정의 메시지를 보냄
	CSocket::OnAccept(nErrorCode);
}

// 메인 윈도우에서는 m_socCom을 얻어서 통신을 처리
CSocCom* CSocServer::GetAcceptSocCom() {
	// 통신소켓을 return
	// 반환되는 통신 소켓은 클라이언트와 연결됨
	return &m_socCom[m_index.front()];
}
