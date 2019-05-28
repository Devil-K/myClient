#if !defined(AFX_UPDATE_H__E93DC177_3B2C_4AE7_8A6F_829EAE071DC9__INCLUDED_)
#define AFX_UPDATE_H__E93DC177_3B2C_4AE7_8A6F_829EAE071DC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UPDATE.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// UPDATE dialog

class UPDATE : public CDialog
{
// Construction
public:
	UPDATE(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(UPDATE)
	enum { IDD = IDD_UPDATE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(UPDATE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(UPDATE)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATE_H__E93DC177_3B2C_4AE7_8A6F_829EAE071DC9__INCLUDED_)
