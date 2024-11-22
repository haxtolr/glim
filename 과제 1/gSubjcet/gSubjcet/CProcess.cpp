// CProcess.cpp: 구현 파일
//

#include "pch.h"
#include "gSubjcet.h"
#include "CProcess.h"


// CProcess

CProcess::CProcess()
{
}

CProcess::~CProcess()
{
}


// CProcess 멤버 함수
void CProcess::getCenter(CImage& pImage)
{
	//8비트 하얀색 배경의 회색 원의 중심을 찾기
	int nWidth = pImage.GetWidth();
	int nHeight = pImage.GetHeight();
	int nPitch = pImage.GetPitch();
	unsigned char* fm = (unsigned char*)pImage.GetBits();
	int nTh = 0x81;

	CRect rect(0, 0, nWidth, nHeight);
	int nSumx = 0;
	int nSumy = 0;
	int nCount = 0;

	for (int j = rect.left; j < rect.right; j++)
	{
		for (int i = rect.top; i < rect.bottom; i++)
		{
			if (fm[j * nPitch + i] < nTh)
			{
				nSumx += i;
				nSumy += j;
				nCount++;
			}
		}
	}

	if (nCount > 0)
	{
		int nCenterX = nSumx / nCount;
		int nCenterY = nSumy / nCount;
		printf("CenterX: %d, CenterY: %d\n", nCenterX, nCenterY);
	}
	else
	{
		printf("CenterX: %d, CenterY: %d\n", -1, -1);
	}
}