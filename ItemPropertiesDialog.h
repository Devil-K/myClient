#if !defined(AFX_ITEMPROPERTIESDIALOG_H__B6CE8CBC_213C_4620_925A_38A5191FC92B__INCLUDED_)
#define AFX_ITEMPROPERTIESDIALOG_H__B6CE8CBC_213C_4620_925A_38A5191FC92B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ItemPropertiesDialog.h : header file
//
#include "opcserver.h"		//class Item
/////////////////////////////////////////////////////////////////////////////
// CItemPropertiesDialog dialog

class CItemPropertiesDialog : public CDialog
{
// Construction
public:
	CItemPropertiesDialog(CWnd* pParent = NULL);   // standard constructor
	CItemPropertiesDialog(Item* pItem, CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(CItemPropertiesDialog)
	enum { IDD = IDD_ITEM_PROPERTIES };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CItemPropertiesDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CItemPropertiesDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	Item*	item;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ITEMPROPERTIESDIALOG_H__B6CE8CBC_213C_4620_925A_38A5191FC92B__INCLUDED_)
