
// StockClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "StockClient.h"
#include "StockClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CLIENT_DISCONNECT "접속종료"

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


// CStockClientDlg 대화 상자



CStockClientDlg::CStockClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STOCKCLIENT_DIALOG, pParent)
	, m_strStatus(_T(""))
	, m_strIP(_T(""))
	, m_strTime1(_T(""))
	, m_strTime2(_T(""))
	, m_strTime3(_T(""))
	, m_strTime4(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStockClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listBox1);
	DDX_Control(pDX, IDC_LIST2, m_listBox2);
	DDX_Control(pDX, IDC_LIST3, m_listBox3);
	DDX_Control(pDX, IDC_LIST4, m_listBox4);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_strStatus);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Text(pDX, IDC_STATIC_TIME1, m_strTime1);
	DDX_Text(pDX, IDC_STATIC_TIME2, m_strTime2);
	DDX_Text(pDX, IDC_STATIC_TIME3, m_strTime3);
	DDX_Text(pDX, IDC_STATIC_TIME4, m_strTime4);
}

BEGIN_MESSAGE_MAP(CStockClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_RECEIVE, &CStockClientDlg::OnReceive)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CStockClientDlg::OnClickedButtonConnect)
	ON_BN_CLICKED(IDCANCEL, &CStockClientDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CStockClientDlg 메시지 처리기

BOOL CStockClientDlg::OnInitDialog()
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
	m_socClient.Create();
	m_socClient.Init(m_hWnd);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CStockClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == SC_CLOSE) {
		m_socClient.Send(CLIENT_DISCONNECT, 256);
		this->EndDialog(IDCANCEL);
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CStockClientDlg::OnPaint()
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
HCURSOR CStockClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



afx_msg LRESULT CStockClientDlg::OnReceive(WPARAM wParam, LPARAM lParam)
{
	char pTmp[256];
	memset(pTmp, 0, sizeof(pTmp));

	m_socClient.Receive(pTmp, 256);
	CString strTmp(pTmp);
	
	while (1) {
		int CRLFPos = strTmp.Find(_T("\r\n"));
		if (CRLFPos == -1) break;

		CString strValue = strTmp.Left(CRLFPos);
		strTmp = strTmp.Mid(CRLFPos + 1);

		int commaPos = strValue.Find(_T(","));
		if (commaPos != -1) {
			CString strID = strValue.Left(commaPos);
			CString strPrice = strValue.Mid(commaPos + 1);
			int iID = _ttoi(strID);

			switch (iID) {
			case 1:
				m_listBox1.ResetContent();
				m_listBox1.AddString(strPrice);
				GetCurrentTimeAsCString(m_strTime1);
				break;

			case 2:
				m_listBox2.ResetContent();
				m_listBox2.AddString(strPrice);
				GetCurrentTimeAsCString(m_strTime2);
				break;

			case 3:
				m_listBox3.ResetContent();
				m_listBox3.AddString(strPrice);
				GetCurrentTimeAsCString(m_strTime3);
				break;

			case 4:
				m_listBox4.ResetContent();
				m_listBox4.AddString(strPrice);
				GetCurrentTimeAsCString(m_strTime4);
				break;

			default:
				AfxMessageBox(_T("메시지 수신 오류"));
				break;
			}
		}
		else {
			AfxMessageBox(_T("메시지 수신 오류"));
		}

		UpdateData(FALSE);
	}
	

	return 0;
}


void CStockClientDlg::OnClickedButtonConnect()
{
	UpdateData(TRUE);
	
	if (m_socClient.Connect(m_strIP, 5000) == FALSE) {
		AfxMessageBox(_T("접속 불가"));
	}
	else {
		m_strStatus = _T("접속 성공");
		UpdateData(FALSE);
	}
}


void CStockClientDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_socClient.Send(CLIENT_DISCONNECT, 256);
	AfxMessageBox(_T("Disconnect Send"));
	this->EndDialog(IDCANCEL);
	CDialogEx::OnCancel();
}
