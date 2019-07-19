
// ApDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Ap.h"
#include "ApDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CApDlg �Ի���




CApDlg::CApDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CApDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_itemview =new CItemView;
}

void CApDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CApDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CApDlg ��Ϣ�������

BOOL CApDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog(); 

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	//������Դ�ļ��е�HTML,IDR_HTML1����HTML�ļ�����Դ�ļ��е�ID  
	CRect rcCreate(0,0,0,0);
	GetClientRect(rcCreate);
	m_itemview->Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDD_AP_DIALOG,NULL);
	CString  self_path;  
	GetModuleFileName(NULL, self_path.GetBufferSetLength(MAX_PATH+1), MAX_PATH+1);  
	self_path=self_path.Left(self_path.ReverseFind(_T('\\'))+1)+"web\\index.html";

	m_itemview->Navigate(self_path, NULL, NULL, NULL, NULL);  


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CApDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CApDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CApDlg::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	return CDialogEx::DestroyWindow();
}
