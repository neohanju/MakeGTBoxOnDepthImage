
// gtheadboxDlg.cpp : ���� ����
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
// CgtheadboxDlg ��ȭ ����



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


// CgtheadboxDlg �޽��� ó����

BOOL CgtheadboxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CString str;
	str.Format(_T("%d"), current_id);
	SetDlgItemText(IDC_CURRENT_ID, str);
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CgtheadboxDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
		
		
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CgtheadboxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CgtheadboxDlg::OnClickedButtonLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	m_Img.Draw(dc->m_hDC, 0, 0, WIDTH, HEIGHT); //Image ũ�� ����
	
}

void CgtheadboxDlg::OnClickedButtonPrev()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	m_Img.Draw(dc->m_hDC, 0, 0, WIDTH, HEIGHT); //Image ũ�� ����
	
}


void CgtheadboxDlg::OnClickedButtonNext()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	m_Img.Draw(dc->m_hDC, 0, 0, WIDTH, HEIGHT); //Image ũ�� ����	
	
}


void CgtheadboxDlg::OnClickedButtonUp()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	current_id++;

	CString str;
	str.Format(_T("%d"), current_id);
	SetDlgItemText(IDC_CURRENT_ID, str);
}


void CgtheadboxDlg::OnBnClickedButtonDown()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(current_id > 1)
		current_id--;

	CString str;
	str.Format(_T("%d"), current_id);
	SetDlgItemText(IDC_CURRENT_ID, str);
}


void CgtheadboxDlg::OnClickedButtonClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	current_id = 1;

	CString str;
	str.Format(_T("%d"), current_id);
	SetDlgItemText(IDC_CURRENT_ID, str);

	//txt���� �ۼ� �ʱ�ȭ �ڵ� ����.

}


void CgtheadboxDlg::OnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//txt���� �ۼ� �ڵ�.
	//fclose(fp);

}




void CgtheadboxDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rect;

	GetDlgItem(IDC_PIC)->GetWindowRect(&rect); //���� ������ �κ� �ٱ��� ������ִ� viewer ũ�� ���δ� �޾ƿ��� �ڵ�
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	//fprintf(fp,"%d	%d	%d	",current_id, point.x, point.y);
	//fprintf(fp,"10	10\n");
	
	CDialogEx::OnLButtonDown(nFlags, point);
}



