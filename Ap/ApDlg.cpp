
// ApDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Ap.h"
#include "ApDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CApDlg 对话框




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


// CApDlg 消息处理程序

BOOL CApDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog(); 

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	//加载资源文件中的HTML,IDR_HTML1就是HTML文件在资源文件中的ID  
	CRect rcCreate(0,0,0,0);
	GetClientRect(rcCreate);
	m_itemview->Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDD_AP_DIALOG,NULL);
	CString  self_path;  
	GetModuleFileName(NULL, self_path.GetBufferSetLength(MAX_PATH+1), MAX_PATH+1);  
	self_path=self_path.Left(self_path.ReverseFind(_T('\\'))+1)+"web\\index.html";

	m_itemview->Navigate(self_path, NULL, NULL, NULL, NULL);  


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CApDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CApDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CApDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	return CDialogEx::DestroyWindow();
}
