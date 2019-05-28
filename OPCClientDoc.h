// OPCClientDoc.h : interface of the OPCClientDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPCCLIENTDOC_H__54662924_EDCB_4BBD_B265_796DBA4F6741__INCLUDED_)
#define AFX_OPCCLIENTDOC_H__54662924_EDCB_4BBD_B265_796DBA4F6741__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "opcserver.h"		//COPCServer

#include "message.h"		//系统消息

class OPCClientDoc : public CDocument
{
protected: // create from serialization only
	OPCClientDoc();
	DECLARE_DYNCREATE(OPCClientDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OPCClientDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ReportError(LPCSTR sz_err);
	void ReportError(Message* msg = NULL);
	void ReportError(LPCSTR description, HRESULT hr);

	virtual ~OPCClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(OPCClientDoc)
	afx_msg void OnOpcServer();
	afx_msg void OnUpdateOpcServer(CCmdUI* pCmdUI);
	afx_msg void OnOpcGroup();
	afx_msg void OnUpdateOpcGroup(CCmdUI* pCmdUI);
	afx_msg void OnOpcItem();
	afx_msg void OnUpdateOpcItem(CCmdUI* pCmdUI);
	afx_msg void OnOpcConnect();
	afx_msg void OnUpdateOpcConnect(CCmdUI* pCmdUI);
	afx_msg void OnOpcDisconnect();
	afx_msg void OnUpdateOpcDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnFileExport();
	afx_msg void OnFileExportLog();
	afx_msg void OnUpdateFileExportLog(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileExport(CCmdUI* pCmdUI);
	afx_msg void OnItemProperties();
	afx_msg void OnUpdateItemProperties(CCmdUI* pCmdUI);
	afx_msg void OnItemRemove();
	afx_msg void OnUpdateItemRemove(CCmdUI* pCmdUI);
	afx_msg void OnItemWrite();
	afx_msg void OnUpdateItemWrite(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


public:
	

	HWND		data_hwnd;		//数据数据句柄
	MessageList	messages;		//错误消息
	HWND		msg_hwnd;		//错误消息句柄

	COPCServer*	current_server;
	ServerList	servers;

private:
	BOOL		auto_open;

	//HANDLE		handle_out;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPCCLIENTDOC_H__54662924_EDCB_4BBD_B265_796DBA4F6741__INCLUDED_)
