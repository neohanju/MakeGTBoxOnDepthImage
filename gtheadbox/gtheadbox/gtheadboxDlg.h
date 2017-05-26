
// gtheadboxDlg.h : ��� ����
//

#pragma once


// CgtheadboxDlg ��ȭ ����
class CgtheadboxDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CgtheadboxDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GTHEADBOX_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;
	int current_id = 1;
	CString folder_path;
	//FILE *fp;

	// ������ �޽��� �� �Լ�
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

