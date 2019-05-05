
// FTP_ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FTP_Client.h"
#include "FTP_ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CFTP_ClientDlg �Ի���



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


// CFTP_ClientDlg ��Ϣ�������

void CFTP_ClientDlg::OnConnect()
{
	if(!socket_client.Create())
	{
		AfxMessageBox(_T("socket����ʧ�ܣ�") );
		return;
	}
	UpdateData(true);    //��ȡ�û���д���������˿ڡ��û���������

	//���ӷ�����
	if(!socket_client.Connect(m_host,m_port))
	{
		AfxMessageBox(_T("socket���ӷ�����ʧ��"));
		return;
	}
	MySockRecv();                       //�Լ���װ�ĺ���
	CString send_msg;

	//�����û���
	send_msg = "USER";
	send_msg += "m_username";
	send_msg += "\r\n";
	MySockSend(send_msg);
	MySockRecv();

	//��������
	send_msg = "PASS";
	send_msg += "m_password";
	send_msg += "\r\n";
	MySockSend(send_msg);
	MySockRecv();

	//����4���ı��༭���1����ť
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

//��װ���������
void CFTP_ClientDlg::MySockSend(CString send_msg)
{
	if(SOCKET_ERROR == socket_client.Send(send_msg,send_msg.GetLength()))
	{
		AfxMessageBox(_T("������Ϣʧ��"));
		return;
	}
	//��������ӵ�list��
	CString show_msg = "���";
	show_msg += send_msg;
	m_listinfo.AddString(show_msg);
}

BOOL CFTP_ClientDlg::Pasv_mode()
{
	//�����µ�socket
	if(!socket_temp.Create())
	{
		AfxMessageBox(L"socket_temp����ʧ��");
		return;
	}

	CString send_msg;

	send_msg = "PASV\r\n";             //���PASV
	MySockSend(send_msg);

	char buf_rcv[128] = "";
	if(SOCKET_ERROR == socket_client.Receive(buf_rcv,128))
	{
		AfxMessageBox(L"���ݽ���ʧ��");
		socket_temp.Close();
		return false;
	}

	//����Ӧ��Ϣ��ӵ��б��
	CString show_msg = "��Ӧ��";
	show_msg += buf_rcv;
	m_listinfo.AddString(show_msg);

	//��ȡ�¿��Ķ˿ںţ���������·���ֵ����
	//227 Entering Passive mode (192,168,0,101,194,73)
	//���㹫ʽ���¿��˿ں� = 194
}

void CFTP_ClientDlg::Parse_list()
{
}

void CFTP_ClientDlg::fileStore(CString filename)
{
}


//��װ������Ӧ����
void CFTP_ClientDlg:: MySockRecv()
{
	char buf_rcv[128] = "";
	if(SOCKET_ERROR == socket_client.Receive(buf_rcv,127))
	{
		AfxMessageBox(L"������Ϣʧ��");
		return;
	}
	//����Ϣ��ʾ��list��
	CString show_msg= "��Ӧ��";
	show_msg += buf_rcv;
	m_listinfo.AddString(show_msg);
}

BOOL CFTP_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFTP_ClientDlg::OnPaint()
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
HCURSOR CFTP_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


