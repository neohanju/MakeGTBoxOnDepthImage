
// GTMakerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GTMaker.h"
#include "GTMakerDlg.h"
#include "afxdialogex.h"
#include <strsafe.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define KINECT_WIDTH  (512)
#define KINECT_HEIGHT (424)

bool FilePathSortAscendComparator(const CString str1, const CString str2)
{
	return str1.CompareNoCase(str2) <= 0;
}

bool CGTMetadata::writefile(const CString strPath)
{
	try
	{
		std::ofstream outputFile;
		outputFile.open(strPath);
		outputFile << (int)vecObjects.size() << "\n";
		for (int i = 0; i < (int)vecObjects.size(); i++)
		{
			outputFile << vecObjects[i].id << " ";
			outputFile << std::fixed << std::setprecision(1) << vecObjects[i].depth << " ";
			outputFile << std::fixed << std::setprecision(1) << vecObjects[i].x << " ";
			outputFile << std::fixed << std::setprecision(1) << vecObjects[i].y << " ";
			outputFile << std::fixed << std::setprecision(1) << vecObjects[i].w << " ";
			outputFile << std::fixed << std::setprecision(1) << vecObjects[i].h << "\n";
		}		
		outputFile.close();
	}
	catch (int e)
	{
		return false;
	}
	return true;
}

bool CGTMetadata::readfile(const CString strPath)
{
	CString strCurLine;
	try
	{
		CStdioFile file(strPath, CFile::modeRead | CFile::typeText);
		file.ReadString(strCurLine);
		this->numObject = _ttoi(strCurLine);
		while (true)
		{
			if (!file.ReadString(strCurLine)) { break; }
			CGTObjectInfo newObject;
			int curPos = 0;
			CString restoken = strCurLine.Tokenize(_T(" "), curPos);
			newObject.id = _ttoi(restoken);

			restoken = strCurLine.Tokenize(_T(" "), curPos);
			newObject.depth = _ttoi(restoken);

			restoken = strCurLine.Tokenize(_T(" "), curPos);
			newObject.x = _ttoi(restoken);

			restoken = strCurLine.Tokenize(_T(" "), curPos);
			newObject.y = _ttoi(restoken);

			restoken = strCurLine.Tokenize(_T(" "), curPos);
			newObject.w = _ttoi(restoken);

			restoken = strCurLine.Tokenize(_T(" "), curPos);
			newObject.h = _ttoi(restoken);			

			this->vecObjects.push_back(newObject);
		}		
		file.Close();
		assert(this->numObject == (int)this->vecObjects.size());		
	}
	catch (int e)
	{
		return false;
	}
	return true;	
}


CGTMakerDlg::CGTMakerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GTMAKER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGTMakerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_FRAME_IMAGE, m_csImageFrame);
}

BEGIN_MESSAGE_MAP(CGTMakerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CGTMakerDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_FRAME_PREV, &CGTMakerDlg::OnBnClickedButtonFramePrev)
	ON_BN_CLICKED(IDC_BUTTON_FRAME_NEXT, &CGTMakerDlg::OnBnClickedButtonFrameNext)
	ON_BN_CLICKED(IDC_BUTTON_ID_UP, &CGTMakerDlg::OnBnClickedButtonIdUp)
	ON_BN_CLICKED(IDC_BUTTON_ID_DOWN, &CGTMakerDlg::OnBnClickedButtonIdDown)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CGTMakerDlg::OnBnClickedButtonClear)
	ON_EN_CHANGE(IDC_EDIT_FRAME, &CGTMakerDlg::OnEnChangeEditFrame)
	ON_EN_CHANGE(IDC_EDIT_ID, &CGTMakerDlg::OnEnChangeEditId)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDOK, &CGTMakerDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CGTMakerDlg message handlers

BOOL CGTMakerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_bFrameRead = false;
	m_bDataChanged = false;
	m_nCurFramePos = 0;
	m_nCurID = 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGTMakerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGTMakerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


bool CGTMakerDlg::OpenDirectory(const CString strDir)
{
	m_vecStrFilePath.clear();

	CString tpath = strDir + _T("\\*.png");
	

	// searching class
	CFileFind finder;
	CString fileName;
	BOOL bWorking = finder.FindFile(tpath);	
	while (bWorking)
	{			
		bWorking = finder.FindNextFile();		
		if (finder.IsArchived())
		{				
			CString _fileName = finder.GetFileName();				
			if (_fileName == _T(".") ||
				_fileName == _T("..") ||
				_fileName == _T("Thumbs.db"))
			{
				continue;
			}				
			m_vecStrFilePath.push_back(finder.GetFilePath());
		}			
	}
	// sort file list (0 -> N)
	std::sort(m_vecStrFilePath.begin(), m_vecStrFilePath.end(), FilePathSortAscendComparator);

	m_nNumFrames = m_vecStrFilePath.size();
	m_bFrameRead = m_nNumFrames > 0 ? true : false;

	return m_bFrameRead;
}


bool CGTMakerDlg::ReadFrame(int position)
{
	if (!m_bFrameRead) { return false; }
	ASSERT(position >= 0 && position < m_nNumFrames);
	m_imgFrame.Destroy();
	m_imgFrame.Load(m_vecStrFilePath[position]);
		
	// read metadata
	CFileFind finder;
	CString strMetadataFilePath = m_vecStrFilePath[position];
	strMetadataFilePath.Replace(_T(".png"), _T(".txt"));
	m_cCurMetadata.clear();
	if (finder.FindFile(strMetadataFilePath))
	{
		m_cCurMetadata.readfile(strMetadataFilePath);
	}
	m_bDataChanged = false;

	CString str;
	str.Format(_T("%d"), position);
	SetDlgItemText(IDC_EDIT_FRAME, str);
	str.Format(_T("%d"), m_nCurID);
	SetDlgItemText(IDC_EDIT_ID, str);

	// draw frame
	this->ShowFrame();

	return true;
}


void CGTMakerDlg::SaveMetadata()
{
	if (m_bDataChanged)
	{ 
		CString strMetadataFilePath = m_vecStrFilePath[m_nCurFramePos];
		strMetadataFilePath.Replace(_T(".png"), _T(".txt"));
		m_cCurMetadata.writefile(strMetadataFilePath);
	}	
}


void CGTMakerDlg::ShowFrame()
{
	CDC *dc = m_csImageFrame.GetDC();
	RECT clientRect;
	m_csImageFrame.GetClientRect(&clientRect);
	m_imgFrame.Draw(dc->m_hDC, 0, 0, KINECT_WIDTH, KINECT_HEIGHT);

	CBrush brush;
	brush.CreateStockObject(NULL_BRUSH);
	CBrush *oldBrush = dc->SelectObject(&brush);
	for (int i = 0; i < (int)m_cCurMetadata.vecObjects.size(); i++)
	{		
		COLORREF penColor = RGB(170, 170, 170);
		if (m_cCurMetadata.vecObjects[i].id == m_nCurID)
		{ 
			penColor = RGB(255, 0, 0);
		}
		CPen pen;
		pen.CreatePen(PS_DOT, 3, penColor);
		CPen* oldPen = dc->SelectObject(&pen);

		// box
		dc->Rectangle(
			m_cCurMetadata.vecObjects[i].x, 
			m_cCurMetadata.vecObjects[i].y, 
			m_cCurMetadata.vecObjects[i].x + m_cCurMetadata.vecObjects[i].w - 1,
			m_cCurMetadata.vecObjects[i].y + m_cCurMetadata.vecObjects[i].h - 1);

		// ID
		CString strID;
		strID.Format(_T("%d"), m_cCurMetadata.vecObjects[i].id);
		dc->SetTextColor(penColor);
		dc->SetBkColor(RGB(0, 0, 0));		
		dc->TextOut(
			m_cCurMetadata.vecObjects[i].x, 
			m_cCurMetadata.vecObjects[i].y, 
			strID);

		dc->SelectObject(oldPen);
	}
	dc->SelectObject(oldBrush);
}


void CGTMakerDlg::OnBnClickedButtonLoad()
{
	TCHAR szFilter[] = _T("Image (*.BMP, *.PNG *.JPG) | *.BMP;*.png;*.JPG | All Files(*.*)|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, szFilter);
	dlg.m_ofn.lpstrInitialDir = _T(".");  // default position of file dialog	
	if (IDOK == dlg.DoModal())
	{
		CString folderPath, strFilePath = dlg.GetPathName();		
		int pos = strFilePath.ReverseFind('\\');
		if (pos != -1)
		{
			folderPath = strFilePath.Left(pos);
		}
		this->OpenDirectory(folderPath);
		m_strBasePath = folderPath;

		// find current frame index
		m_nCurFramePos = 0;
		for (int i = 0; i < (int)m_vecStrFilePath.size(); i++)
		{
			if (0 == strFilePath.Compare(m_vecStrFilePath[i]))
			{
				m_nCurFramePos = i;
				break;
			}
		}
		this->ReadFrame(m_nCurFramePos);
	}	
}


void CGTMakerDlg::OnBnClickedButtonFramePrev()
{
	if (!m_bFrameRead) { return; }
	this->SaveMetadata();
	m_nCurFramePos = (std::max)(0, m_nCurFramePos - 1);	
	this->ReadFrame(m_nCurFramePos);
}


void CGTMakerDlg::OnBnClickedButtonFrameNext()
{
	if (!m_bFrameRead) { return; }
	this->SaveMetadata();
	m_nCurFramePos = (std::min)(m_nCurFramePos + 1, m_nNumFrames - 1);	
	this->ReadFrame(m_nCurFramePos);
}


void CGTMakerDlg::OnBnClickedButtonIdUp()
{
	if (!m_bFrameRead) { return; }
	m_nCurID++;
	CString str;
	str.Format(_T("%d"), m_nCurID);
	SetDlgItemText(IDC_EDIT_ID, str);

	ShowFrame();
}


void CGTMakerDlg::OnBnClickedButtonIdDown()
{
	if (!m_bFrameRead) { return; }
	m_nCurID = (std::max)(m_nCurID - 1, 0);
	CString str;
	str.Format(_T("%d"), m_nCurID);
	SetDlgItemText(IDC_EDIT_ID, str);

	ShowFrame();
}


void CGTMakerDlg::OnBnClickedButtonClear()
{
	if (m_cCurMetadata.numObject > 0) { m_bDataChanged = true; }
	m_cCurMetadata.clear();
	ShowFrame();
}


void CGTMakerDlg::OnEnChangeEditFrame()
{
	if (!m_bFrameRead) { return; }
	SaveMetadata();

	CString strRead;
	GetDlgItemText(IDC_EDIT_FRAME, strRead);	
	int prevFramePos = m_nCurFramePos;	
	m_nCurFramePos = (std::max)(0, (std::min)(_ttoi(strRead), m_nNumFrames - 1));
	if (prevFramePos != m_nCurFramePos)
	{		
		ReadFrame(m_nCurFramePos);		
	}
}


void CGTMakerDlg::OnEnChangeEditId()
{
	if (!m_bFrameRead) { return; }
	CString strRead;
	GetDlgItemText(IDC_EDIT_ID, strRead);
	m_nCurID = (std::max)(0, _ttoi(strRead));
	ShowFrame();
}


BOOL CGTMakerDlg::PreTranslateMessage(MSG *pMsg)
{
	if (WM_KEYDOWN == pMsg->message)
	{
		switch (pMsg->wParam)
		{
		case VK_LEFT:
			OnBnClickedButtonFramePrev();
			break;
		case VK_RIGHT:
			OnBnClickedButtonFrameNext();
			break;
		case VK_UP:
			OnBnClickedButtonIdUp();
			break;
		case VK_DOWN:
			OnBnClickedButtonIdDown();
			break;
		default:
			// do nothing
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CGTMakerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rect;
	GetDlgItem(IDC_STATIC_FRAME_IMAGE)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	if (m_bFrameRead && (point.x >= rect.left) && (point.x <= rect.right) 
		&& (point.y >= rect.top) && (point.y <= rect.bottom))
	{
		CGTObjectInfo newObject;
		newObject.id = m_nCurID;
		COLORREF rgb = m_imgFrame.GetPixel(point.x - rect.left, point.y - rect.top);
		BYTE r_value = GetRValue(rgb);  // R = G = B in depth image
		double boxWidth = (double)r_value * 0.3;
		newObject.depth = (255.0 - (double)r_value) * 8000.0;
		newObject.x = point.x - boxWidth * 0.5;
		newObject.y = point.y - boxWidth * 0.5;
		newObject.w = boxWidth;
		newObject.h = boxWidth;

		bool bFound = false;
		for (int i = 0; i < (int)m_cCurMetadata.vecObjects.size(); i++)
		{
			if (m_cCurMetadata.vecObjects[i].id == m_nCurID)
			{
				m_cCurMetadata.vecObjects[i] = newObject;
				bFound = true;
				break;
			}
		}
		if (!bFound) { m_cCurMetadata.vecObjects.push_back(newObject); }	
		m_bDataChanged = true;

		ShowFrame();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CGTMakerDlg::OnBnClickedOk()
{
	this->SaveMetadata();

	CDialogEx::OnOK();
}


//()()
//('')HAANJU.YOO
