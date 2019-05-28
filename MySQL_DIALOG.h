#if !defined(AFX_MYSQL_DIALOG_H__1B26EDB0_25FA_4892_BB6C_FCB1AC13A77A__INCLUDED_)
#define AFX_MYSQL_DIALOG_H__1B26EDB0_25FA_4892_BB6C_FCB1AC13A77A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySQL_DIALOG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MySQL_DIALOG dialog

class MySQL_DIALOG : public CDialog
{
// Construction
public:
	MySQL_DIALOG(CWnd* pParent = NULL);   // standard constructor

	//插入数据库示例
	void InsertDB(const char* naem,float flv,const char* time);
// Dialog Data
	//{{AFX_DATA(MySQL_DIALOG)
	enum { IDD = IDD_MySQL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

 // MYSQL *mysql = mysql_init(NULL);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MySQL_DIALOG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MySQL_DIALOG)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSQL_DIALOG_H__1B26EDB0_25FA_4892_BB6C_FCB1AC13A77A__INCLUDED_)
