
// StockServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "StockServer.h"
#include "StockServerDlg.h"
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


// CStockServerDlg 대화 상자



CStockServerDlg::CStockServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STOCKSERVER_DIALOG, pParent)
	, m_strID(_T(""))
	, m_strPrice(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStockServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_1, m_listBox1);
	DDX_Control(pDX, IDC_LIST_2, m_listBox2);
	DDX_Control(pDX, IDC_LIST_3, m_listBox3);
	DDX_Control(pDX, IDC_LIST_4, m_listBox4);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_strPrice);
}

BEGIN_MESSAGE_MAP(CStockServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_UP, &CStockServerDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CStockServerDlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CStockServerDlg::OnBnClickedButtonSet)
	ON_MESSAGE(UM_ACCEPT, &CStockServerDlg::OnAccpet)
	ON_MESSAGE(UM_RECEIVE, &CStockServerDlg::OnReceive)
END_MESSAGE_MAP()


// CStockServerDlg 메시지 처리기

BOOL CStockServerDlg::OnInitDialog()
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
	m_fprice1 = 2000.0f;
	m_fprice2 = 1500.0f;
	m_fprice3 = 500.0f;
	m_fprice4 = 3000.0f;

	m_listBox1.AddString(_T("2000.0"));
	m_listBox2.AddString(_T("1500.0"));
	m_listBox3.AddString(_T("500.0"));
	m_listBox4.AddString(_T("3000.0"));
	UpdateData(FALSE);

	m_socServer.Create(5000); // 5000번 포트 생성
	m_socServer.Listen();
	m_socServer.Init(m_hWnd); // 윈도우 연결

	m_clientID = 0;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CStockServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CStockServerDlg::OnPaint()
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
HCURSOR CStockServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CStockServerDlg::setPrice(int id, CString price)
{
	switch (id) {
	case 1:
		m_listBox1.ResetContent();
		m_listBox1.AddString(price);
		m_fprice1 = _ttof(price);
		break;

	case 2:
		m_listBox2.ResetContent();
		m_listBox2.AddString(price);
		m_fprice2 = _ttof(price);
		break;

	case 3:
		m_listBox3.ResetContent();
		m_listBox3.AddString(price);
		m_fprice3 = _ttof(price);
		break;

	case 4 :
		m_listBox4.ResetContent();
		m_listBox4.AddString(price);
		m_fprice4 = _ttof(price);
		break;

	default:
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


int CStockServerDlg::upPrice(int id)
{
	CString strTmp;

	switch (id) {
	case 1:
		m_fprice1 += 1.0f;
		strTmp.Format(_T("%f"), m_fprice1);
		m_listBox1.ResetContent();
		m_listBox1.AddString(strTmp);
		break;

	case 2:
		m_fprice2 += 1.0f;
		strTmp.Format(_T("%f"), m_fprice2);
		m_listBox2.ResetContent();
		m_listBox2.AddString(strTmp);
		break;

	case 3:
		m_fprice3 += 1.0f;
		strTmp.Format(_T("%f"), m_fprice3);
		m_listBox3.ResetContent();
		m_listBox3.AddString(strTmp);
		break;

	case 4:
		m_fprice4 += 1.0f;
		strTmp.Format(_T("%f"), m_fprice4);
		m_listBox4.ResetContent();
		m_listBox4.AddString(strTmp);
		break;

	default:
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


int CStockServerDlg::downPrice(int id)
{
	CString strTmp;

	switch (id) {
	case 1:
		m_fprice1 -= 1.0f;
		strTmp.Format(_T("%f"), m_fprice1);
		m_listBox1.ResetContent();
		m_listBox1.AddString(strTmp);
		break;

	case 2:
		m_fprice2 -= 1.0f;
		strTmp.Format(_T("%f"), m_fprice2);
		m_listBox2.ResetContent();
		m_listBox2.AddString(strTmp);
		break;

	case 3:
		m_fprice3 -= 1.0f;
		strTmp.Format(_T("%f"), m_fprice3);
		m_listBox3.ResetContent();
		m_listBox3.AddString(strTmp);
		break;

	case 4:
		m_fprice4 -= 1.0f;
		strTmp.Format(_T("%f"), m_fprice4);
		m_listBox4.ResetContent();
		m_listBox4.AddString(strTmp);
		break;

	default:
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


void CStockServerDlg::OnBnClickedButtonUp()
{
	UpdateData(TRUE);

	int iID = _ttoi(m_strID);
	if (upPrice(iID) == EXIT_FAILURE) {
		AfxMessageBox(_T("ID 에러 : 1~4를 입력하세요"));
		return;
	}


	notifyPrice(iID);
}


void CStockServerDlg::OnBnClickedButtonDown()
{
	UpdateData(TRUE);

	int iID = _ttoi(m_strID);
	if (downPrice(iID) == EXIT_FAILURE) {
		AfxMessageBox(_T("ID 에러 : 1~4를 입력하세요"));
		return;
	}

	notifyPrice(iID);
}


void CStockServerDlg::OnBnClickedButtonSet()
{
	UpdateData(TRUE);

	int iID = _ttoi(m_strID);

	if (setPrice(iID, m_strPrice) == EXIT_FAILURE) {
		AfxMessageBox(_T("ID 에러 : 1~4를 입력하세요"));
		return;
	}

	notifyPrice(iID);
}


int CStockServerDlg::notifyPrice(int id)
{
	/* 옵저버들(클라이언트)들에게 반복문으로 종목(id)와 가격(price)를 Send
	 "종목,가격" ','를 기준으로 종목과 가격을 나눈다.
	 */
	for (Observer* observer : m_observers) {
		observer->update(id, getPrice(id));
	}
	return 0;
}


CString CStockServerDlg::getPrice(int id)
{
	CString strTmp;

	switch (id) {
	case 1:
		strTmp.Format(_T("%f"), m_fprice1);
		return strTmp;

	case 2:
		strTmp.Format(_T("%f"), m_fprice2);
		return strTmp;

	case 3:
		strTmp.Format(_T("%f"), m_fprice3);
		return strTmp;

	case 4:
		strTmp.Format(_T("%f"), m_fprice4);
		return strTmp;

	default :
		return NULL;
	}
}


afx_msg LRESULT CStockServerDlg::OnAccpet(WPARAM wParam, LPARAM lParam)
{
	m_clientID += 1;
	Observer* newClient = new CSocClient(m_clientID, m_hWnd);
	m_socServer.Accept(*(newClient));
	
	m_observers.push_back(newClient);

	//첫 입장시 종목 4개 전부 보내주기
	newClient->update(1, getPrice(1));
	newClient->update(2, getPrice(2));
	newClient->update(3, getPrice(3));
	newClient->update(4, getPrice(4));

	AfxMessageBox(_T("클라이언트 입장, 전송완료")); //test
	return 0;
}


afx_msg LRESULT CStockServerDlg::OnReceive(WPARAM wParam, LPARAM lParam)
{
	int iID = wParam;
	char pTmp[256];
	memset(pTmp, 0, 256);
	Observer* observer = NULL;
	for (auto obs : m_observers) {
		if (obs->getID() == iID)
		{
			observer = obs;
		}
	}

	if (observer == NULL) { 
		AfxMessageBox(_T("observer = NULL")); //test
		return EXIT_FAILURE; 
	}

	int status = observer->Receive(pTmp, 256);
	CString strTmp(pTmp);
	if (status == 0 || strTmp.Compare(_T(CLIENT_DISCONNECT)) == 0) { // 클라이언트 종료
		for (auto it = m_observers.begin(); it != m_observers.end(); it++) {
			if ((*it)->getID() == wParam) {
				m_observers.erase(it);
				CString strTmp;
				strTmp.Format(_T("%d"), wParam);
				AfxMessageBox(strTmp + _T("접속 종료"));
				break;
			}
		}
	}
	
	return 0;
}
