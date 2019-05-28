#if !defined(AFX_SERVERDIALOG_H__E5F50C66_5945_48E9_AF02_F10954CEBBA1__INCLUDED_)
#define AFX_SERVERDIALOG_H__E5F50C66_5945_48E9_AF02_F10954CEBBA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerDialog.h : header file
//
#include "opcserver.h"

/////////////////////////////////////////////////////////////////////////////
// CServerDialog dialog

class CServerDialog : public CDialog
{
// Construction
public:
	OPCServerInfo* GetServerInfo();
	bool EnumerateNodes(LPNETRESOURCE lpnr);
	CServerDialog(CWnd* pParent = NULL);   // standard constructor
	CServerDialog(OPCServerInfo* server_info, CWnd* pParent = NULL);

	~CServerDialog(){
		while(!server_infos.IsEmpty())
			delete server_infos.RemoveHead();
	}
// Dialog Data
	//{{AFX_DATA(CServerDialog)
	enum { IDD = IDD_SERVER_DIALOG };
	CListBox	m_lstServer;
	CString	m_strNodeName;
	CString	m_strServerName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CServerDialog)
	afx_msg void OnRadServer1();
	afx_msg void OnRadServer2();
	afx_msg void OnSelchangeLstServer();
	afx_msg void OnDblclkLstServer();
	afx_msg void OnBtnRefresh();
	virtual BOOL OnInitDialog();
	afx_msg void OnDropdownCboNode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:	
	void GetOPCServers(LPCSTR sz_node = NULL);

protected:
	OPCServerInfo*		server_info;
	ServerInfoList		server_infos;

	CLSID			cat_id;
	CLSID			clsid;

	bool			enumerated;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERDIALOG_H__E5F50C66_5945_48E9_AF02_F10954CEBBA1__INCLUDED_)
