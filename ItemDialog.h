#if !defined(AFX_ITEMDIALOG_H__4F44A9BF_8BDC_4007_917A_CE7FCE3BF554__INCLUDED_)
#define AFX_ITEMDIALOG_H__4F44A9BF_8BDC_4007_917A_CE7FCE3BF554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ItemDialog.h : header file
//

class COPCServer;
/////////////////////////////////////////////////////////////////////////////
// CItemDialog dialog

class CItemDialog : public CDialog
{
// Construction
public:
	HRESULT BrowseHere(HTREEITEM item);
	void UpdateFlat();
	CItemDialog(IOPCServer* server, CWnd* pParent = NULL);
	CItemDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CItemDialog)
	enum { IDD = IDD_ITEM_DIALOG };
	CTreeCtrl	m_tree;
	CListBox	m_tag;
	CListBox	m_flat;
	CString		access_path;
	CString		filter;
	CString		item_name;
	
	//}}AFX_DATA
	VARTYPE			m_vt;
	OPCNAMESPACETYPE	name_space_type;
	COPCServer*		opc_server;
	OPCBrowseServerAddressSpace	browse;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CItemDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CItemDialog)
	afx_msg void OnBtnAdditem();
	afx_msg void OnBtnAddall();
	afx_msg void OnBtnProperties();
	afx_msg void OnRadNative();
	afx_msg void OnRadBool();
	afx_msg void OnRadShort();
	afx_msg void OnRadLong();
	afx_msg void OnRadFloat();
	afx_msg void OnRadDouble();
	afx_msg void OnRadString();
	afx_msg void OnItemexpandingTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeFlat();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTagList();
	afx_msg void OnDblclkTagList();
	afx_msg void OnDblclkFlat();
	afx_msg void OnChangeEdtFilter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ITEMDIALOG_H__4F44A9BF_8BDC_4007_917A_CE7FCE3BF554__INCLUDED_)
