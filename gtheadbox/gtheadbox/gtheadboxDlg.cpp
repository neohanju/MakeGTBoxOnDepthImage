
// gtheadboxDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "gtheadbox.h"
#include "gtheadboxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WIDTH	512
#define HEIGHT	424
// CgtheadboxDlg 대화 상자



CgtheadboxDlg::CgtheadboxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GTHEADBOX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgtheadboxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgtheadboxDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CgtheadboxDlg::OnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CgtheadboxDlg::OnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CgtheadboxDlg::OnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CgtheadboxDlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CgtheadboxDlg::OnClickedButtonClear)
	ON_BN_CLICKED(IDC_SAVE, &CgtheadboxDlg::OnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CgtheadboxDlg::OnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CgtheadboxDlg::OnClickedButtonNext)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CgtheadboxDlg 메시지 처리기

BOOL CgtheadboxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CString str;
	str.Format(_T("%d"), current_id);
	SetDlgItemText(IDC_CURRENT_ID, str);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CgtheadboxDlg::OnPaint()
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
HCURSOR CgtheadboxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CgtheadboxDlg::OnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szFilter[] = _T("Image Files (BMP,JPEG,JPG,JPE,JPG...) | *.BMP;*.JPEG;*.JPG;*.JPE;*.PGM | All Files(*.*)|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, szFilter);	
	dlg.m_ofn.lpstrInitialDir = _T(".");  // default position of file dialog	
	if (IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();
		this->OpenImage(strPathName);
	}
	SetDlgItemText(IDC_FRAME_NUM, dlg.GetFileTitle());
	
	folder_path = dlg.GetFolderPath();
	frame_num = _ttoi(dlg.GetFileTitle());
	
	//fp = fopen("1.txt", "w");
}

void CgtheadboxDlg::OpenImage(CString strImagePath)
{
	CWnd *pWnd = (CWnd*)GetDlgItem(IDC_PIC);
	CDC *dc = pWnd->GetDC();
	CStatic *staticSize = (CStatic *)GetDlgItem(IDC_PIC);
	CRect rect;

	staticSize->GetClientRect(rect);
	m_Img.Destroy();
	m_Img.Load(strImagePath);
	m_Img.Draw(dc->m_hDC, 0, 0, WIDTH, HEIGHT); //Image 크기 조절
	
}

void CgtheadboxDlg::OnClickedButtonPrev()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	frame_num--;

	str.Format(_T("%06d"),frame_num);
	SetDlgItemText(IDC_FRAME_NUM, str);
	str.Format(_T("%s\\%06d.jpg"), folder_path, frame_num);

	CWnd *pWnd = (CWnd*)GetDlgItem(IDC_PIC);
	CDC *dc = pWnd->GetDC();
	CStatic *staticSize = (CStatic *)GetDlgItem(IDC_PIC);
	CRect rect;

	

	staticSize->GetClientRect(rect);
	m_Img.Destroy();
	m_Img.Load(str);
	m_Img.Draw(dc->m_hDC, 0, 0, WIDTH, HEIGHT); //Image 크기 조절
	
}


void CgtheadboxDlg::OnClickedButtonNext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	frame_num++;

	str.Format(_T("%06d"), frame_num);
	SetDlgItemText(IDC_FRAME_NUM, str);
	str.Format(_T("%s\\%06d.jpg"), folder_path, frame_num);

	CWnd *pWnd = (CWnd*)GetDlgItem(IDC_PIC);
	CDC *dc = pWnd->GetDC();
	CStatic *staticSize = (CStatic *)GetDlgItem(IDC_PIC);
	CRect rect;

	
	staticSize->GetClientRect(rect);
	m_Img.Destroy();
	m_Img.Load(str);
	m_Img.Draw(dc->m_hDC, 0, 0, WIDTH, HEIGHT); //Image 크기 조절	
	
}


void CgtheadboxDlg::OnClickedButtonUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	current_id++;

	CString str;
	str.Format(_T("%d"), current_id);
	SetDlgItemText(IDC_CURRENT_ID, str);
}


void CgtheadboxDlg::OnBnClickedButtonDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(current_id > 1)
		current_id--;

	CString str;
	str.Format(_T("%d"), current_id);
	SetDlgItemText(IDC_CURRENT_ID, str);
}


void CgtheadboxDlg::OnClickedButtonClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	current_id = 1;

	CString str;
	str.Format(_T("%d"), current_id);
	SetDlgItemText(IDC_CURRENT_ID, str);

	//txt파일 작성 초기화 코드 삽입.

}


void CgtheadboxDlg::OnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//txt파일 작성 코드.
	//fclose(fp);

}




void CgtheadboxDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;

	GetDlgItem(IDC_PIC)->GetWindowRect(&rect); //사진 나오는 부분 바깥에 출력해주는 viewer 크기 전부다 받아오는 코드
	ScreenToClient(&rect);
	if ( (point.x >= rect.left) && (point.x <= rect.right) && (point.y >= rect.top) && (point.y <= rect.bottom))
	{
		SetCursor(::LoadCursor(NULL, IDC_CROSS));
	}
	else
	{
		SetCursor(::LoadCursor(NULL, IDC_ARROW));
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CgtheadboxDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//fprintf(fp,"%d	%d	%d	",current_id, point.x, point.y);
	//fprintf(fp,"10	10\n");
	
	CDialogEx::OnLButtonDown(nFlags, point);
}



