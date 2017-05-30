
// GTMakerDlg.h : header file
//

#pragma once
#include <vector>

class CGTObjectInfo
{
public:
	CGTObjectInfo() : id(0), depth(0), x(0.0), y(0.0), w(0.0), h(0.0) {}
	static double GetHeadBoxWidth(double depth);
	int id;
	double depth;
	double x;
	double y;
	double w;
	double h;
};

class CGTMetadata
{
public:
	CGTMetadata() : numObject(0), frameIndex(0) {}
	void clear() 
	{ 
		this->numObject = 0;
		this->vecObjects.clear();
	}
	bool writefile(const CString strPath);
	bool readfile(const CString strPath);

	int numObject;
	int frameIndex;
	std::vector<CGTObjectInfo> vecObjects;
};


// CGTMakerDlg dialog
class CGTMakerDlg : public CDialogEx
{
	//---------------------------------------------------------------------
	// METHODS
	//---------------------------------------------------------------------
public:
	CGTMakerDlg(CWnd* pParent = NULL);	// standard constructor

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GTMAKER_DIALOG };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);									
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonFramePrev();
	afx_msg void OnBnClickedButtonFrameNext();
	afx_msg void OnBnClickedButtonIdUp();
	afx_msg void OnBnClickedButtonIdDown();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnEnChangeEditFrame();
	afx_msg void OnEnChangeEditId();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedOk();

	BOOL PreTranslateMessage(MSG *pMsg);
	
protected:
	bool OpenDirectory(const CString strDir);
	bool ReadFrame(int position);
	void SaveMetadata();
	void ShowFrame();

	//---------------------------------------------------------------------
	// VARIABLES
	//---------------------------------------------------------------------
	HICON m_hIcon;
	bool m_bFrameRead;
	bool m_bDataChanged;

	CStatic m_csImageFrame;
	CImage m_imgFrame;

	int m_nNumFrames;
	int m_nCurFramePos;
	int m_nCurID;	

	CString m_strBasePath;
	std::vector<CString> m_vecStrFilePath;

	CGTMetadata m_cCurMetadata;		
};


//()()
//('')HAANJU.YOO
