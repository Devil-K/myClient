#if !defined(AFX_MESSAGEVIEW_H__CE48A3BF_8857_4716_8E0A_60B83C1D7086__INCLUDED_)
#define AFX_MESSAGEVIEW_H__CE48A3BF_8857_4716_8E0A_60B83C1D7086__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MessageView view

class MessageView : public CListView
{
protected:
	MessageView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(MessageView)

// Attributes
public:

// Operations
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MessageView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~MessageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(MessageView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMessage(WPARAM wparam, LPARAM lparam  = 0);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGEVIEW_H__CE48A3BF_8857_4716_8E0A_60B83C1D7086__INCLUDED_)
