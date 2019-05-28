#if !defined(AFX_GROUPDIALOG_H__81CD1117_3A64_4618_9920_B526CF78F7D3__INCLUDED_)
#define AFX_GROUPDIALOG_H__81CD1117_3A64_4618_9920_B526CF78F7D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GroupDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGroupDialog dialog

class CGroupDialog : public CDialog
{
// Construction
public:
	CGroupDialog(int group_index = 1, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGroupDialog)
	enum { IDD = IDD_GROUP_DIALOG };
	BOOL	active;
	float	dead_band;
	CString	group_name;
	long	local_id;
	UINT	time_bias;
	UINT	update_rate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGroupDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUPDIALOG_H__81CD1117_3A64_4618_9920_B526CF78F7D3__INCLUDED_)
