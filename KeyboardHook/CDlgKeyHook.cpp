// CDlgKeyHook.cpp: 구현 파일
//

#include "pch.h"
#include "KeyboardHook.h"
#include "afxdialogex.h"
#include "CDlgKeyHook.h"


// CDlgKeyHook 대화 상자

IMPLEMENT_DYNAMIC(CDlgKeyHook, CDialogEx)

CDlgKeyHook::CDlgKeyHook(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_KEY_HOOK, pParent)
{

}

CDlgKeyHook::~CDlgKeyHook()
{
}

void CDlgKeyHook::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgKeyHook, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_KEY_HOOK, &CDlgKeyHook::OnBnClickedButtonKeyHook)
	ON_BN_CLICKED(IDC_BUTTON_KEY_UNHOOK, &CDlgKeyHook::OnBnClickedButtonKeyUnhook)
END_MESSAGE_MAP()


// CDlgKeyHook 메시지 처리기

HHOOK hKeyboardHook = NULL;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        if (wParam == WM_KEYDOWN)
        {
            char ch;
            ch = MapVirtualKey(p->vkCode, MAPVK_VK_TO_CHAR);
            CString str;
            str.Format(_T("%c"), ch);
            OutputDebugString(str); // 디버그창에 키보드입력을 출력
        }
    }
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

void CDlgKeyHook::OnBnClickedButtonKeyHook()
{
	OutputDebugString(L"CDlgKeyHook::OnBnClickedButtonKeyHook\n");
    if (!hKeyboardHook)
    {
        hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, AfxGetInstanceHandle(), 0);
        if (!hKeyboardHook)
            AfxMessageBox(_T("키보드 훅 설정 실패"));
        else
            AfxMessageBox(_T("키보드 훅 설정 성공"));
    }
}


void CDlgKeyHook::OnBnClickedButtonKeyUnhook()
{
	OutputDebugString(L"CDlgKeyHook::OnBnClickedButtonKeyUnhook\n");
    if (hKeyboardHook)
    {
        UnhookWindowsHookEx(hKeyboardHook);
        hKeyboardHook = NULL;
        AfxMessageBox(_T("키보드 훅 해제 성공"));
    }
}
