// OPCClientView.h : interface of the OPCClientView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPCCLIENTVIEW_H__4224CAC4_09AE_467F_BB08_9E70F3292902__INCLUDED_)
#define AFX_OPCCLIENTVIEW_H__4224CAC4_09AE_467F_BB08_9E70F3292902__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MySQL_DIALOG.h"

class OPCClientView : public CListView
{
protected: // create from serialization only
	OPCClientView();
	DECLARE_DYNCREATE(OPCClientView)

// Attributes
public:
	OPCClientDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OPCClientView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~OPCClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(OPCClientView)						//定义了 ONCreate 申明
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDataChanged(WPARAM wParam, LPARAM lParam = 0);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()

private:
	CImageList	image_list;
};

#ifndef _DEBUG  // debug version in OPCClientView.cpp
inline OPCClientDoc* OPCClientView::GetDocument()
   { return (OPCClientDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPCCLIENTVIEW_H__4224CAC4_09AE_467F_BB08_9E70F3292902__INCLUDED_)
