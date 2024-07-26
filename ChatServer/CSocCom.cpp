// CSocCom.cpp: 구현 파일
//

#include "pch.h"
#include "ChatServer.h"
#include "CSocCom.h"


// CSocCom

CSocCom::CSocCom()
{
}

CSocCom::~CSocCom()
{
}


// CSocCom 멤버 함수
// 소켓 클래스와 메인 윈도우를 연결시킴
void CSocCom::Init(HWND hWnd) {
	m_hWnd = hWnd;
}

// 데이터가 도착했다는걸 알려주는 가상함수
void CSocCom::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SendMessage(m_hWnd, UM_RECEIVE, m_index, 0); // 메인 윈도우에 UM_RECEIVE라는 사용자 정의 메시지를 보냄
	CSocket::OnReceive(nErrorCode);
}
