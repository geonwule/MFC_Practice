#include "pch.h"
#include "CSocClient.h"


CSocClient::CSocClient(const int id, HWND hWnd) : _id(id), m_hWnd(hWnd) {}

CSocClient::~CSocClient() {}

void CSocClient::Init(HWND hWnd) {
	m_hWnd = hWnd;
}

void CSocClient::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SendMessage(m_hWnd, UM_RECEIVE, _id, 0);
	Observer::OnReceive(nErrorCode);
}

int CSocClient::getID() const {
	return _id;
}