
// SocketServerDlgDlg.h : ͷ�ļ�
//

#pragma once
#include "ListenSocket.h"
// CSocketServerDlgDlg �Ի���
class CSocketServerDlgDlg : public CDialogEx
{
// ����
public:
	CSocketServerDlgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SOCKETSERVERDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtStart();
private:
	CListenSocket m_srvrSocket;
public:
	afx_msg void OnBnClickedButtonStop();
};
