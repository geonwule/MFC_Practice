#include "pch.h"
#include "CSocServer.h"

CSocServer::CSocServer() {}

CSocServer::~CSocServer() {}

void CSocServer::Init(HWND hWnd) {
	m_hWnd = hWnd;
}

void CSocServer::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	SendMessage(m_hWnd, UM_ACCEPT, 0, 0);
	CSocket::OnAccept(nErrorCode);
}
