#pragma once
#include "afxdialogex.h"
#include <afx.h>
// C_Dimage 대화 상자
#define ImgBorad 650
#define nWhite 250
class C_Dimage : public CDialogEx
{
	DECLARE_DYNAMIC(C_Dimage)

public:
	C_Dimage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~C_Dimage();
	CWnd* m_pParent;
	CImage m_image;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_C_Dimage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()


private:
	void initImage();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void drawCircle(CPoint pt);
	BOOL isincircle(int x, int y, int nCenterX, int nCenterY, int nRadius);
	BOOL validPoint(int x, int y);
	void saveImage();
	void Load_Image();
	CPoint findCenter();
	void DrawCross(float x, float y);
};
