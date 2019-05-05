
// FTP_ClientDlg.h : ͷ�ļ�
//

#pragma once


// CFTP_ClientDlg �Ի���
class CFTP_ClientDlg : public CDialogEx
{
// ����
public:
	CFTP_ClientDlg(CWnd* pParent = NULL);	// ��׼���캯��
											
	//�������ӺͿ���
	void MySockRecv();
	void MySockSend(CString send_msg);

	//���ݽ���
	BOOL Pasv_mode();               //���뱻��ģʽ�������б���Ϣ
	void Parse_list();              //�����ļ��б���Ϣ
	void fileStore(CString filename); //�����ļ�����

// �Ի�������
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
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CSocket socket_client;  //�������������������ͽ�����Ӧ
	CSocket socket_temp;   //���ڽ��պͷ�������



	// ���ɵ���Ϣӳ�亯��
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
