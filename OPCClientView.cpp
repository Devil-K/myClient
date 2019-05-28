// OPCClientView.cpp : implementation of the OPCClientView class
//

#include "stdafx.h"
#include "CUS_OPCClient.h"

#include "OPCClientDoc.h"
#include "OPCClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern OPCClientDoc* theDoc;

enum {COL_NAME, COL_TYPE, COL_VALUE, COL_QUALITY, COL_TIME};
/////////////////////////////////////////////////////////////////////////////
// OPCClientView

IMPLEMENT_DYNCREATE(OPCClientView, CListView)

BEGIN_MESSAGE_MAP(OPCClientView, CListView)
	//{{AFX_MSG_MAP(OPCClientView)
	ON_WM_CREATE()
	ON_MESSAGE(WM_DATACHANGE, OnDataChanged)
	ON_WM_TIMER()
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OPCClientView construction/destruction

OPCClientView::OPCClientView()
{
	// TODO: add construction code here
	m_dwDefaultStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT;
}

OPCClientView::~OPCClientView()
{
}

BOOL OPCClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// OPCClientView drawing

void OPCClientView::OnDraw(CDC* pDC)
{
	OPCClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void OPCClientView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// OPCClientView diagnostics

#ifdef _DEBUG
void OPCClientView::AssertValid() const
{
	CListView::AssertValid();
}

void OPCClientView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

OPCClientDoc* OPCClientView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(OPCClientDoc)));
	return (OPCClientDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// OPCClientView message handlers
void OPCClientView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}

int OPCClientView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CListCtrl& list = GetListCtrl();
	list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);	//set extend style

	if(image_list.Create(IDB_BITMAP1, 16, 0, RGB(255, 0, 255))){
		image_list.SetBkColor(GetSysColor(COLOR_WINDOW));

		list.SetImageList(&image_list, LVSIL_NORMAL);
	}

	//
	while(list.DeleteColumn(0));
	
	list.InsertColumn(COL_NAME, "Name", LVCFMT_LEFT, 150, 0);
	list.InsertColumn(COL_TYPE, "Type", LVCFMT_LEFT, 75, 0);
	list.InsertColumn(COL_VALUE, "Value", LVCFMT_LEFT, 120, 0);
	list.InsertColumn(COL_QUALITY, "Quality", LVCFMT_LEFT, 80, 0);
	list.InsertColumn(COL_TIME, "Time", LVCFMT_LEFT, 120, 0);
	
	theDoc->data_hwnd = GetSafeHwnd();

	SetTimer(1, 3000, NULL);

	return 0;
}

void OPCClientView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CListCtrl& list = GetListCtrl();
	
	//操作数据库类
	MySQL_DIALOG m_MysqlDlg;

	switch(lHint){
	case CLEAR_ALL:
		list.DeleteAllItems();
		break;
	case UPDATE_SERVER:
		{
			list.DeleteAllItems();
			COPCServer* server = (COPCServer*)pHint;
			if(server == NULL)
				return;
			
			list.SetRedraw(false);
			POSITION group_pos = server->groups.GetHeadPosition();
			while(group_pos){
				COPCGroup* group = server->groups.GetNext(group_pos);
				if(group){
					POSITION item_pos = group->items.GetHeadPosition();
					while(item_pos){
						Item* item = group->items.GetNext(item_pos);
						if(item){
							int index = list.InsertItem(0, item->name);//item中的名称
							CString strType = _T("VT_EMPTY");
							switch(item->value.vt){
							case VT_I2:
								strType = _T("int");
								break;
							case VT_UI1:
								strType = _T("uint");
								break;
							case VT_I4:
								strType = _T("long");
								break;
							case VT_R4:
								strType = _T("float");
								break;
							case VT_R8:
								strType = _T("double");
								break;
							case VT_BOOL:
								strType = _T("bool");
								break;
							case VT_BSTR:
								strType = _T("string");
								break;
							default:
								strType = _T("unknown");
								break;
							}
							list.SetItemText(index, COL_TYPE, strType);
							list.SetItemData(index, (DWORD)item);
						}
					}
				}
			}
			list.SetRedraw(true);
		}
		break;
	case UPDATE_GROUP:
		{
			list.SetRedraw(false);
			list.DeleteAllItems();
			COPCGroup* group = (COPCGroup*)pHint;
			if(group){
				POSITION item_pos = group->items.GetHeadPosition();
				while(item_pos){
					Item* item = group->items.GetNext(item_pos);
					if(item){
						int index = list.InsertItem(0, item->name);
						CString strType = _T("VT_EMPTY");
						switch(item->value.vt){
						case VT_I2:
							strType = _T("int");
							break;
						case VT_UI1:
							strType = _T("uint");
							break;
						case VT_I4:
							strType = _T("long");
							break;
						case VT_R4:
							strType = _T("float");
							break;
						case VT_R8:
							strType = _T("double");
							break;
						case VT_BOOL:
							strType = _T("bool");
							break;
						case VT_BSTR:
							strType = _T("string");
							break;
						default:
							strType = _T("unknown");
							break;
						}
						list.SetItemText(index, COL_TYPE, strType);
						list.SetItemData(index, (DWORD)item);
					}
				}
			}
			list.SetRedraw(true);
		}
		break;
	case UPDATE_ITEM_VALUE:
		{
			list.SetRedraw(false);

			int item_count = list.GetItemCount();
			for(int i = 0; i < item_count; i++)
			{
				Item* item = (Item*)list.GetItemData(i);
				if(item == NULL)
					continue;
				
				CString strType = _T("VT_EMPTY");
				CString strValue(_T("?"));
				switch(item->value.vt){
				case VT_I2:
					strType = _T("int");
					strValue.Format(_T("%d"), item->value.iVal);   //item中的值
					break;
				case VT_UI1:
					strType = _T("uint");
					strValue.Format(_T("%d"),item->value.bVal);
					break;
				case VT_I4:
					strType = _T("long");
					strValue.Format(_T("%d"), item->value.lVal);
					break;
				case VT_R4:
					strType = _T("float");
					strValue.Format(_T("%f"), item->value.fltVal);
					break;
				case VT_R8:
					strType = _T("double");
					strValue.Format(_T("%f"), item->value.dblVal);
					break;
				case VT_BOOL:
					strType = _T("bool");
					strValue = item->value.boolVal ? _T("1") : _T("0");
					break;
				case VT_BSTR:
					strType = _T("string");
					strValue = item->value.bstrVal;
					break;
				default:
					strType = _T("unknown");
					strValue = _T("");
					break;
				}
				list.SetItemText(i, COL_TYPE, strType);
				list.SetItemText(i, COL_VALUE, strValue);
				
				CString strQuality = _T("Uncertain");
				switch(item->quality){
				case OPC_QUALITY_GOOD:
					strQuality = _T("Good");
					break;
				case OPC_QUALITY_BAD:
					strQuality = _T("Bad");
					break;
				case OPC_QUALITY_UNCERTAIN:
					strQuality = _T("Uncertain");
					break;
				default:
					strQuality = _T("Uncertain");
					break;
				}
				list.SetItemText(i, COL_QUALITY,strQuality);

				CTime time(item->timestamp);
				list.SetItemText(i, COL_TIME, time.Format(_T("%c")));
                
				m_MysqlDlg.InsertDB(item->name,item->value.iVal,time.Format(_T("%c")));//获得名称和int的值  ,time.Format(_T("%c"))
				//m_MysqlDlg.InsertDB(item->name,item->value.iVal,time.Format(_T("%c")));
			}

			list.SetRedraw(true);
		}
		break;
	default:
		break;
	}
}

//数据变化
void OPCClientView::OnDataChanged(WPARAM wParam, LPARAM lParam)
{
	theDoc->UpdateAllViews(NULL, UPDATE_ITEM_VALUE, NULL);
}

void OPCClientView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CListView::OnTimer(nIDEvent);
}

void OPCClientView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	if(theDoc->current_server){
		COPCGroup* group = theDoc->current_server->get_current_group();
		if(group){
			Item* item = (Item*)pNMListView->lParam;
			if(item)
				group->current_item = item;
			else
				group->current_item = NULL;
		}	
	}
	
	if(pResult)
		*pResult = 0;
}

void OPCClientView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CMenu menu;
	if(menu.LoadMenu(IDR_ITEM_MENU)){
		menu.GetSubMenu(0)->TrackPopupMenu(
			TPM_LEFTALIGN|TPM_RIGHTBUTTON,
			point.x, 
			point.y,
			AfxGetMainWnd());
	}
}


