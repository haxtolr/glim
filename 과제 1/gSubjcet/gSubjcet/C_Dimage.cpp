// C_Dimage.cpp: 구현 파일
//

#include "pch.h"
#include "gSubjcet.h"
#include "afxdialogex.h"
#include "C_Dimage.h"
#include <string>
#include <windows.h>

// C_Dimage 대화 상자

IMPLEMENT_DYNAMIC(C_Dimage, CDialogEx)

C_Dimage::C_Dimage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_C_Dimage, pParent)
{
	m_pParent = pParent;
}

C_Dimage::~C_Dimage()
{
}

void C_Dimage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C_Dimage, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// C_Dimage 메시지 처리기

BOOL C_Dimage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	initImage();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void C_Dimage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_image)
	{
		m_image.Draw(dc, 0, 0); 
	}
}

void C_Dimage::initImage()
{
	int nWidth = ImgBorad;
	int nHeight = ImgBorad;
	int nBpp = 8; // 8비트 이미지

	m_image.Create(nWidth, -nHeight, nBpp); // 이미지 생성

	if (nBpp == 8)
	{
		static RGBQUAD rgb[256];

		for (int i = 0; i < 256; i++)
		{
			rgb[i].rgbBlue = rgb[i].rgbGreen = rgb[i].rgbRed = i;
		}
		m_image.SetColorTable(0, 0xff, rgb);
	}

	int nPitch = m_image.GetPitch(); // 이미지의 한 라인의 바이트 수
	unsigned char* fm = (unsigned char*)m_image.GetBits(); // 이미지의 시작 주소

	memset(fm, nWhite, nWidth * nHeight); // 흰색으로 초기화
}

void C_Dimage::drawCircle(CPoint pt) 
{
	int nBlack = 80;
	int nRadius = rand() % 150 + 10; 
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, nWhite, m_image.GetWidth() * m_image.GetHeight());

	int nCenterX = pt.x + nRadius;
	int nCenterY = pt.y + nRadius;
	int nPitch = m_image.GetPitch();

	if (nCenterX > ImgBorad - nRadius || nCenterY > ImgBorad - nRadius || pt.x < 0 || pt.y < 0)
		return;

	for (int j = pt.y; j < pt.y + nRadius * 2; j++)
	{
		for (int i = pt.x; i < pt.x + nRadius * 2; i++)
		{
			if (isincircle(i, j, nCenterX, nCenterY, nRadius)) 
			{
				if (validPoint(i, j))
				{
					fm[j * nPitch + i] = nBlack;
				}
			}
		}
	}

	Invalidate();
	UpdateWindow();
	saveImage();
	Sleep(100);
}

BOOL C_Dimage::isincircle(int x, int y, int nCenterX, int nCenterY, int nRadius) 
{
	bool bResult = false;
	double dX = x - nCenterX; 
	double dY = y - nCenterY; 
	double dDist = dX * dX + dY * dY;
	
	if (dDist < nRadius * nRadius)
	{
		bResult = true;
	}

	return bResult; // 원 내부인지 확인
}

BOOL C_Dimage::validPoint(int x, int y)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));
}

void C_Dimage::saveImage()
{ 
	static int index = 1;

	TCHAR Tpath[MAX_PATH]; //파일 경로를 저장할 변수
	GetModuleFileName(NULL, Tpath, MAX_PATH); 

	std::wstring filePath = Tpath; // 파일 경로를 wstring으로 변환
	size_t pos = filePath.find_last_of(L"\\"); 
	filePath = filePath.substr(0, pos);

	filePath += L"\\image"; // 이미지 폴더 생성
	if (CreateDirectory(filePath.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS)
	{
		filePath += L"\\image" + std::to_wstring(index++) + L".bmp";
		m_image.Save(filePath.c_str());
		printf("success save\n");
	}
	else 
	{
		printf("fail dir\n");
	}
}

void C_Dimage::Load_Image()
{
	CFileDialog dlg(TRUE, _T("bmp"), NULL, OFN_FILEMUSTEXIST, _T("Image Files (*.bmp)|*.bmp;*|All Files (*.*)|*.*||"));
	
	if (dlg.DoModal() == IDOK)
	{
		// 선택한 파일 경로
		CString strFilePath = dlg.GetPathName();
		// 이미지 로드
		CImage L_image;
		HRESULT hr = L_image.Load(strFilePath);

		if (FAILED(hr))
		{
			printf("로드 실패");
			return;
		}

		m_image = L_image;

		Invalidate();
		UpdateWindow();

		CPoint cen = findCenter();
		DrawCross(cen.x, cen.y);
	}
}

CPoint C_Dimage::findCenter()
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	// 이미지의 중심점을 찾기 위한 변수
	
	CRect rect(0, 0, nWidth, nHeight);
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	for (int j = rect.top; j < rect.bottom; j++)
	{
		for (int i = rect.left; i < rect.right; i++)
		{
			if (fm[j * nPitch + i] == 80)
			{
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}
	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;
	printf("CenterX : %f, CenterY : %f\n", dCenterX, dCenterY);
	
	return (CPoint(dCenterX, dCenterY));
}

void C_Dimage::DrawCross(float x, float y)
{
	CDC* pDC = GetDC();
	if (pDC)
	{
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0)); // 빨간색 펜 생성
		CPen* pOldPen = pDC->SelectObject(&pen);

		// 십자가 그리기
		pDC->MoveTo((int)x - 10, (int)y);
		pDC->LineTo((int)x + 10, (int)y);
		pDC->MoveTo((int)x, (int)y - 10);
		pDC->LineTo((int)x, (int)y + 10);

		pDC->SelectObject(pOldPen);

		CString Text_center; // 텍스트 넣는 법
		Text_center.Format(_T("Center (%.1f, %.1f)"), x, y);
		pDC->SetTextColor(RGB(255, 0, 255));
		pDC->TextOutW((int)x + 10, (int)y + 10, Text_center);


		ReleaseDC(pDC);
	}
}