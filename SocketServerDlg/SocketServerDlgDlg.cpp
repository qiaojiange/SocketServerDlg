
// SocketServerDlgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SocketServerDlg.h"
#include "SocketServerDlgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSocketServerDlgDlg 对话框




CSocketServerDlgDlg::CSocketServerDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSocketServerDlgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketServerDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSocketServerDlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_START, &CSocketServerDlgDlg::OnBnClickedBtStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CSocketServerDlgDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CSocketServerDlgDlg 消息处理程序

BOOL CSocketServerDlgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSocketServerDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSocketServerDlgDlg::OnPaint()
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
HCURSOR CSocketServerDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocketServerDlgDlg::OnBnClickedBtStart()
{
	// TODO: 在此添加控件通知处理程序代码

	BOOL bInit = AfxSocketInit();
	if (!bInit)
	{
		AfxMessageBox(_T("-----Socket创建失败！0000"));
		return ;
	}

	if (m_srvrSocket.m_hSocket == INVALID_SOCKET)
	{
		//创建监听套接字，激发FD_ACCEPT事件,默认端口6100；
		BOOL bFlag = m_srvrSocket.Create(8000,SOCK_STREAM,FD_ACCEPT | FD_READ | FD_WRITE | FD_OOB | FD_CONNECT | FD_CLOSE);//第三个参数表示m_srcvSocket对FD_ACCEPT事件感兴趣
		if(!bFlag){
			AfxMessageBox(_T("Socket创建失败！"));
			m_srvrSocket.Close();
			PostQuitMessage(0);
			return ;
		}
		GetDlgItem(IDC_BT_START)->EnableWindow(FALSE);
		if (!m_srvrSocket.Listen())//如果监听失败
		{
			int nErrorCode = m_srvrSocket.GetLastError();
			if(WSAEWOULDBLOCK!=nErrorCode){
				AfxMessageBox(_T("Socket 错误！"));
				m_srvrSocket.Close();
				PostQuitMessage(0);
			}
		}

	}


}



void CSocketServerDlgDlg::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BT_START)->EnableWindow(TRUE);
	m_srvrSocket.OnClose(0);
}
