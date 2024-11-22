
// gSubjcetDlg.h: 헤더 파일
//

#include "C_Dimage.h"
#include <stdio.h>
#pragma once

#define ImgBorad 650

// CgSubjcetDlg 대화 상자
class CgSubjcetDlg : public CDialogEx
{
// 생성입니다.
public:
	CgSubjcetDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	
	C_Dimage* m_Dimage; // C_Dimage 클래스 포인터 선언

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GSUBJCET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
	void setCirCle(CPoint pStart, CPoint pEnd);
	afx_msg void OnBnClickedBtnOpen();
};
