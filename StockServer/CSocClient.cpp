#include "pch.h"
#include "CSocClient.h"


CSocClient::CSocClient(const int id, HWND hWnd) : _id(id), m_hWnd(hWnd) {}

CSocClient::~CSocClient() {}

void CSocClient::Init(HWND hWnd) {
	m_hWnd = hWnd;
}

void CSocClient::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	SendMessage(m_hWnd, UM_RECEIVE, _id, 0);
	Observer::OnReceive(nErrorCode);
}

int CSocClient::getID() const {
	return _id;
}