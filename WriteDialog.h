#if !defined(AFX_WRITEDIALOG_H__3CBB3561_9C46_4426_B034_3339063F3EDA__INCLUDED_)
#define AFX_WRITEDIALOG_H__3CBB3561_9C46_4426_B034_3339063F3EDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WriteDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWriteDialog dialog

class CWriteDialog : public CDialog
{
// Construction
public:
	CWriteDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWriteDialog)
	enum { IDD = IDD_WRITE_DIALOG };
	BOOL	m_async;
	CString	m_value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWriteDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWriteDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WRITEDIALOG_H__3CBB3561_9C46_4426_B034_3339063F3EDA__INCLUDED_)
