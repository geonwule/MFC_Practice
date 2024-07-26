
// ChatClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatClientDlg 대화 상자



CChatClientDlg::CChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATCLIENT_DIALOG, pParent)
	, m_strIP(_T(""))
	, m_strSend(_T(""))
	, m_strPort(_T(""))
	, m_strUserID(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT_PORT, m_strPort);
	DDX_Text(pDX, IDC_EDIT_USERID, m_strUserID);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_RECEIVE, OnReceive)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CChatClientDlg::OnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChatClientDlg::OnClickedButtonSend)
	ON_BN_CLICKED(ID_CANCEL, &CChatClientDlg::OnClickedCancel)
END_MESSAGE_MAP()


// CChatClientDlg 메시지 처리기

BOOL CChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == SC_CLOSE) { // 클라이언트 종료시 서버로 메세지 보냄
		m_socCom.Send(SOC_CLIENT_CONNECT, sizeof(SOC_CLIENT_CONNECT));
		this->EndDialog(IDCANCEL); // 대화상자 종료
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CChatClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 데이터를 보내는것은 소켓 클래스의 멤버함수 Send 이용
// 데이터를 받을 때는 통신 소켓 클래스에 오버라이딩한 OnReceive 메시지 함수를 사용
LRESULT CChatClientDlg::OnReceive(WPARAM wParam, LPARAM lParam)
{
	// 접속된 곳에서 데이터가 도착했을 때
	char pTmp[256];
	CString strTmp;
	memset(pTmp, '\0', sizeof(pTmp));

	//데이터를 pTmp에 받는다.
	m_socCom.Receive(pTmp, sizeof(pTmp));
	strTmp.Format(_T("%s"), pTmp);

	//서버로부터 연결완료 메세지를 받으면
	if (strTmp.Find(_T(SOC_CLIENT_CONNECT)) == 0) {
		//Right 함수를 이용해 가장 오른쪽에 있는 번호 추출. 0은 \n0이다.
		m_strUserID = _T("사용자: ") + strTmp.Right(1);
	}

	//리스트박스에 보여준다.
	int i = m_list.GetCount();
	m_list.InsertString(i, strTmp);

	UpdateData(FALSE); // 에디트 컨트롤에 반영
	return TRUE;
}

// 서버에 접속 요청
// 소켓 클라이언트의 Create함수에서 인자가 있으면 서버로 인식하므로, 인자를 넘기지 않는다. 그러면 클라이언트로 판단해서 동작.
// Create로 소켓을 생성했다면 실제 접속은 Connect 함수를 이용
// 첫번째 인자를 이용해(m_strIP는 에디터 컨트롤과 연결된 멤버변수) 접속할 곳의 IP 주소를 넘기며 두번째 인자를 통해 접속할 포트 번호를 지정
void CChatClientDlg::OnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 접속
	UpdateData(TRUE); // 에디트 컨트롤의 내용을 멤버변수에 반영
	m_socCom.Create(); // 소켓 생성
	
	// IP 주소와 포트번호를 지정
	int iPort = _ttoi(m_strPort);
	m_socCom.Connect(m_strIP, iPort);
	m_socCom.Init(this->m_hWnd); // 메시지를 받을 윈도우 핸들을 지정

}

// [전송] 버튼을 클릭했을 때
void CChatClientDlg::OnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE); // 에디트 컨트롤의 내용을 멤버변수에 반영
	//char pTmp[256];
	//CString strTmp;

	//pTmp에 전송할 데이터 입력
	//memset(pTmp, '\0', sizeof(pTmp));
    //strcpy_s(pTmp, sizeof(pTmp), CT2A(m_strSend));
	//m_strSend = "";
	
	// 전송
	//m_socCom.Send(pTmp, 256); // 데이터 전송
	m_socCom.Send(m_strSend, 256); // 데이터 전송

	// 전송한 데이터도 리스트박스에 보여준다.
	//strTmp.Format(_T("%s"), pTmp);
	//strTmp = m_strSend;
	int i = m_list.GetCount();
	m_list.InsertString(i, m_strSend);
    m_strSend = "";

	UpdateData(FALSE); // 멤버변수의 내용을 에디트 컨트롤에 반영
}


void CChatClientDlg::OnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_socCom.Send(SOC_CLIENT_DISCONNECT, sizeof(SOC_CLIENT_DISCONNECT));
	this->EndDialog(IDCANCEL); // Dialog 닫기
	CDialogEx::OnCancel();
}
