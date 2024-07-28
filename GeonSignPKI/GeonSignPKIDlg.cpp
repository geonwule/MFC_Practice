
// GeonSignPKIDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GeonSignPKI.h"
#include "GeonSignPKIDlg.h"
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


// CGeonSignPKIDlg 대화 상자



CGeonSignPKIDlg::CGeonSignPKIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GEONSIGNPKI_DIALOG, pParent)
	, m_strCA(_T(""))
	, m_strRA(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGeonSignPKIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CA, m_strCA);
	DDX_Text(pDX, IDC_EDIT_RA, m_strRA);
	DDX_Text(pDX, IDC_EDIT_OCSP, m_strOCSP);
}

BEGIN_MESSAGE_MAP(CGeonSignPKIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CA_REGISTER, &CGeonSignPKIDlg::OnClickedButtonCaRegister)
	ON_BN_CLICKED(IDC_BUTTON_CA_REVOKE, &CGeonSignPKIDlg::OnClickedButtonCaRevoke)
	ON_BN_CLICKED(IDC_BUTTON_RA_REGISTER, &CGeonSignPKIDlg::OnClickedButtonRaRegister)
	ON_BN_CLICKED(IDC_BUTTON_RA_UNREGISTER, &CGeonSignPKIDlg::OnClickedButtonRaUnregister)
	ON_BN_CLICKED(IDC_BUTTON_OCSP_CHECK, &CGeonSignPKIDlg::OnClickedButtonOcspCheck)
END_MESSAGE_MAP()


// CGeonSignPKIDlg 메시지 처리기

BOOL CGeonSignPKIDlg::OnInitDialog()
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

void CGeonSignPKIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGeonSignPKIDlg::OnPaint()
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
HCURSOR CGeonSignPKIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGeonSignPKIDlg::OnClickedButtonCaRegister()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE); // 입력기 데이터 가져옴

	std::string cert = m_CA.GenerateCertificate(std::string(CT2A(m_strCA))); // 인증서 발급
	AfxMessageBox(_T("인증서 발급 완료 : ") + CString(cert.c_str()));
	m_strCA = _T("");
	UpdateData(FALSE); // 입력기 초기화
}


void CGeonSignPKIDlg::OnClickedButtonCaRevoke()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE); // 입력기 데이터 가져옴
	if (m_CA.RevokeCertificate(CERTI_PREFIX + std::string(CT2A(m_strCA))))
	{
		AfxMessageBox(_T("인증서 폐기 완료 : ") + m_strCA);
	}
	else
	{
		AfxMessageBox(_T("인증서 폐기 실패 : ") + m_strCA);
	}

	m_strCA = _T("");
	UpdateData(FALSE); // 입력기 초기화
}


void CGeonSignPKIDlg::OnClickedButtonRaRegister()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	bool result = m_RA.RegisterUser(std::string(CT2A(m_strRA)));
	if (result)
	{
		AfxMessageBox(_T("Register success : ") + m_strRA);
	}
	else
		AfxMessageBox(_T("Register fail"));
	m_strRA = _T("");
	UpdateData(FALSE);
}


void CGeonSignPKIDlg::OnClickedButtonRaUnregister()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	bool result = m_RA.UnregisterUser(std::string(CT2A(m_strRA)));
	if (result)
	{
		AfxMessageBox(_T("UNregister success : ") + m_strRA);
	}
	else
		AfxMessageBox(_T("UNregister fail"));
	m_strRA = _T("");
	UpdateData(FALSE);
}


void CGeonSignPKIDlg::OnClickedButtonOcspCheck()
{
	UpdateData(TRUE);
	e_CertificateStatus status = m_OCSP.CheckCertificateStatus(std::string(CT2A(m_strOCSP)), m_CA);
	CString msg;
	switch (status)
	{
	case GOOD:
		msg = _T("GOOD");
		break;

	case REVOKED:
		msg = _T("REVOKED");
		break;

	case UNKNOWN:
		msg = _T("UNKNOWN");
		break;
	}
	AfxMessageBox(msg);
	m_strOCSP = _T("");
	UpdateData(FALSE);
}
