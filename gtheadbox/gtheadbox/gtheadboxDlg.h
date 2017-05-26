
// gtheadboxDlg.h : 헤더 파일
//

#pragma once


// CgtheadboxDlg 대화 상자
class CgtheadboxDlg : public CDialogEx
{
// 생성입니다.
public:
	CgtheadboxDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GTHEADBOX_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	int current_id = 1;
	CString folder_path;
	//FILE *fp;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CImage m_Img;
	int frame_num;

	afx_msg void OnClickedButtonLoad();

protected:
	void OpenImage(CString strImagePath);
public:
	afx_msg void OnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnClickedButtonClear();
	afx_msg void OnClickedSave();
	afx_msg void OnClickedButtonPrev();
	afx_msg void OnClickedButtonNext();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

