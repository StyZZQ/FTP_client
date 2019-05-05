
// FTP_ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FTP_Client.h"
#include "FTP_ClientDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFTP_ClientDlg 对话框



CFTP_ClientDlg::CFTP_ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FTP_CLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFTP_ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFTP_ClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

END_MESSAGE_MAP()


// CFTP_ClientDlg 消息处理程序

void CFTP_ClientDlg::OnConnect()
{
	if(!socket_client.Create())
	{
		AfxMessageBox(_T("socket创建失败！") );
		return;
	}
	UpdateData(true);    //获取用户填写的主机、端口、用户名、密码

	//连接服务器
	if(!socket_client.Connect(m_host,m_port))
	{
		AfxMessageBox(_T("socket连接服务器失败"));
		return;
	}
	MySockRecv();                       //自己封装的函数
	CString send_msg;

	//发送用户名
	send_msg = "USER";
	send_msg += "m_username";
	send_msg += "\r\n";
	MySockSend(send_msg);
	MySockRecv();

	//发送密码
	send_msg = "PASS";
	send_msg += "m_password";
	send_msg += "\r\n";
	MySockSend(send_msg);
	MySockRecv();

	//禁用4个文本编辑框和1个按钮
	GetDlgItem(IDC_HOST)->EnableWindow(false);
	GetDlgItem(IDC_PORT)->EnableWindow(false);
	GetDlgItem(IDC_USERNAME)->EnableWindow(false);
	GetDlgItem(IDC_PASSWD)->EnableWindow(false);
	GetDlgItem(IDC_CONNECT)->EnableWindow(false);

}

void CFTP_ClientDlg::OnDbclkListFile()
{
}

void CFTP_ClientDlg::OnUpdate()
{
}

void CFTP_ClientDlg::OnStoreFile()
{
}

void CFTP_ClientDlg::OnLoadFile()
{
}

void CFTP_ClientDlg::OnCancel()
{
}

void CFTP_ClientDlg::OnQuit()
{
}

//封装发送命令函数
void CFTP_ClientDlg::MySockSend(CString send_msg)
{
	if(SOCKET_ERROR == socket_client.Send(send_msg,send_msg.GetLength()))
	{
		AfxMessageBox(_T("发送消息失败"));
		return;
	}
	//将命令添加到list上
	CString show_msg = "命令：";
	show_msg += send_msg;
	m_listinfo.AddString(show_msg);
}

BOOL CFTP_ClientDlg::Pasv_mode()
{
	//创建新的socket
	if(!socket_temp.Create())
	{
		AfxMessageBox(L"socket_temp创建失败");
		return;
	}

	CString send_msg;

	send_msg = "PASV\r\n";             //命令：PASV
	MySockSend(send_msg);

	char buf_rcv[128] = "";
	if(SOCKET_ERROR == socket_client.Receive(buf_rcv,128))
	{
		AfxMessageBox(L"数据接收失败");
		socket_temp.Close();
		return false;
	}

	//将响应信息添加到列表框
	CString show_msg = "响应：";
	show_msg += buf_rcv;
	m_listinfo.AddString(show_msg);

	//获取新开的端口号，正常情况下返回值类似
	//227 Entering Passive mode (192,168,0,101,194,73)
	//计算公式：新开端口号 = 194
}

void CFTP_ClientDlg::Parse_list()
{
}

void CFTP_ClientDlg::fileStore(CString filename)
{
}


//封装接收响应函数
void CFTP_ClientDlg:: MySockRecv()
{
	char buf_rcv[128] = "";
	if(SOCKET_ERROR == socket_client.Receive(buf_rcv,127))
	{
		AfxMessageBox(L"发送消息失败");
		return;
	}
	//将信息显示在list上
	CString show_msg= "响应：";
	show_msg += buf_rcv;
	m_listinfo.AddString(show_msg);
}

BOOL CFTP_ClientDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFTP_ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFTP_ClientDlg::OnPaint()
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
HCURSOR CFTP_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


