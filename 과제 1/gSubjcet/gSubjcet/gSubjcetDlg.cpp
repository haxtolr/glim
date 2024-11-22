
// gSubjcetDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "gSubjcet.h"
#include "gSubjcetDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

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


// CgSubjcetDlg 대화 상자

CgSubjcetDlg::CgSubjcetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GSUBJCET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgSubjcetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgSubjcetDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CgSubjcetDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CgSubjcetDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CgSubjcetDlg::OnBnClickedBtnOpen)
END_MESSAGE_MAP()


// CgSubjcetDlg 메시지 처리기

BOOL CgSubjcetDlg::OnInitDialog()
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
	MoveWindow(0, 0, 800, 720);
	m_Dimage = new C_Dimage(this); // C_Dimage 클래스 포인터 생성
	m_Dimage->Create(IDD_C_Dimage, this); // access 가능
	m_Dimage->ShowWindow(SW_SHOW); // 
	m_Dimage->MoveWindow(0, 0, ImgBorad, ImgBorad); // C_Dimage 대화 상자 크기 설정

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CgSubjcetDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CgSubjcetDlg::OnPaint()
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
HCURSOR CgSubjcetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CgSubjcetDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_Dimage) 
	{
		delete m_Dimage;
	}
}

void CgSubjcetDlg::OnBnClickedBtnDraw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString Csx1, Csy1;

	GetDlgItemText(IDC_X1, Csx1);
	GetDlgItemText(IDC_Y1, Csy1);

	int iX1 = _ttoi(Csx1);
	int iY1 = _ttoi(Csy1);

	CPoint pStart(iX1, iY1);
	if (iX1 > ImgBorad || iY1 > ImgBorad) {
		MessageBox(_T("좌표값이 범위를 벗어났습니다."));
		return;
	}
	m_Dimage->drawCircle(pStart);
}

void CgSubjcetDlg::OnBnClickedBtnAction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString Csx1, Csy1, Csx2, Csy2;

	GetDlgItemText(IDC_X1, Csx1);
	GetDlgItemText(IDC_Y1, Csy1);
	GetDlgItemText(IDC_X2, Csx2);
	GetDlgItemText(IDC_Y2, Csy2);

	int iX1 = _ttoi(Csx1);
	int iY1 = _ttoi(Csy1);

	int iX2 = _ttoi(Csx2);
	int iY2 = _ttoi(Csy2);

	CPoint pStart(iX1, iY1);
	CPoint pEnd(iX2, iY2);

	if ((iX1 > ImgBorad || iY1 > ImgBorad) || (iX1 > iX2 || iY1 > iY2)) {
		MessageBox(_T("좌표값이 범위를 벗어났습니다."));
		return;
	}
	setCirCle(pStart, pEnd);
}

void CgSubjcetDlg::setCirCle(CPoint pStart, CPoint pEnd) {

	static int nSttx = pStart.x;
	static int nStty = pStart.y;
	
	int nEndx = pEnd.x;
	int nEndy = pEnd.y;

	while (nSttx < nEndx || nStty < nEndy) {
		CPoint pt(nSttx, nStty);
		m_Dimage->drawCircle(pt);
		nSttx += 10;
		nStty += 10;
		printf("x: %d y: %d\n", nSttx, nStty);
	}
}

void CgSubjcetDlg::OnBnClickedBtnOpen()
{
	if (m_Dimage->m_image)
	{
		m_Dimage->m_image.Destroy();
	}
	m_Dimage->Load_Image();
}