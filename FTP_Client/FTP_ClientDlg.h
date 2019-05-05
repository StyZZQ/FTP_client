
// FTP_ClientDlg.h : 头文件
//

#pragma once


// CFTP_ClientDlg 对话框
class CFTP_ClientDlg : public CDialogEx
{
// 构造
public:
	CFTP_ClientDlg(CWnd* pParent = NULL);	// 标准构造函数
											
	//数据连接和控制
	void MySockRecv();
	void MySockSend(CString send_msg);

	//数据接收
	BOOL Pasv_mode();               //进入被动模式，接收列表信息
	void Parse_list();              //解析文件列表信息
	void fileStore(CString filename); //保存文件内容

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FTP_CLIENT_DIALOG };

#endif
	CListBox m_listfile;
	CListBox m_listinfo;
	CString m_host;
	CString m_username;
	CString m_password;
	int m_port;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CSocket socket_client;  //用于向服务器发送命令和接收响应
	CSocket socket_temp;   //用于接收和发送数据



	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnConnect();
	afx_msg void OnDbclkListFile();
	afx_msg void OnUpdate();
	afx_msg void OnStoreFile();
	afx_msg void OnLoadFile();
	afx_msg void OnCancel();
	afx_msg void OnQuit();
};
