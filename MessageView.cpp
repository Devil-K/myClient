// MessageView.cpp : implementation file
//

#include "stdafx.h"
#include "CUS_OPCClient.h"
#include "MessageView.h"
//#include "message.h"		//class Message header file
#include "opcclientdoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum {COL_TIME, COL_MESSAGE};
extern OPCClientDoc* theDoc;
/////////////////////////////////////////////////////////////////////////////
// MessageView

IMPLEMENT_DYNCREATE(MessageView, CListView)

MessageView::MessageView()
{
	m_dwDefaultStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT;
}

MessageView::~MessageView()
{
}


BEGIN_MESSAGE_MAP(MessageView, CListView)
	//{{AFX_MSG_MAP(MessageView)
	ON_WM_CREATE()
	ON_MESSAGE(WM_MESSAGE, OnMessage)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MessageView drawing

void MessageView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// MessageView diagnostics

#ifdef _DEBUG
void MessageView::AssertValid() const
{
	CListView::AssertValid();
}

void MessageView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MessageView message handlers

int MessageView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CListCtrl& list = GetListCtrl();
	
	//set extend style
	list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	
	while(list.DeleteColumn(0));

	list.InsertColumn(COL_TIME, "Time", LVCFMT_LEFT, 150);
	list.InsertColumn(COL_MESSAGE, "Message", LVCFMT_LEFT, 395);

	theDoc->msg_hwnd = GetSafeHwnd();
	return 0;
}

void MessageView::OnMessage(WPARAM wparam, LPARAM lparam)
{
	Message* msg = (Message*)lparam;
	if(!msg)
		return;
	
	CListCtrl& list = GetListCtrl();
	
	CTime time(msg->time);
	
	int index = list.InsertItem(0, time.Format(_T("%c")));
	list.SetItemText(index, COL_MESSAGE, msg->sz_message);
	list.EnsureVisible(index, true);
}	

void MessageView::OnDestroy() 
{
	CListView::OnDestroy();
	
	// TODO: Add your message handler code here
	theDoc->msg_hwnd = 0;
}
