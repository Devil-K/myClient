// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "CUS_OPCClient.h"

#include "OPCClientDoc.h"
#include "LeftView.h"
#include "UPDATE.h"
#include "MySQL_DIALOG.h"
//#include "GroupDialog.h"
//#include "CAboutDlg.h"
//#include "CAboutDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern OPCClientDoc* theDoc;
/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_COMMAND(ConnectDB, OnConnectDB)
	ON_COMMAND(VersionUP, OnVersionUP)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here
	m_dwDefaultStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASLINES
		| TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS;
	M_MySQL=0;
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	OPCClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

OPCClientDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(OPCClientDoc)));
	return (OPCClientDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CTreeCtrl& tree = GetTreeCtrl();

	if(image_list.Create(IDB_BITMAP1, 16, 0, RGB(255, 0, 255))){
		image_list.SetBkColor(GetSysColor(COLOR_WINDOW));

		tree.SetImageList(&image_list, TVSIL_NORMAL);
	}

	return 0;
}

void CLeftView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CTreeView::OnUpdate(pSender, lHint, pHint);

	CTreeCtrl& tree = GetTreeCtrl();
	
	int image1 = 0, image2 = 1;
	switch(lHint){
		case ADD_SERVER:
			{
				COPCServer* server = (COPCServer*)pHint;
				if(server){
					OPCServerInfo* server_info = server->get_server_info();
					if(server_info){
						HTREEITEM item = TVI_ROOT;
						if(server->is_connected())
							image1 = 0;
						else
							image1 = 1;
						image2 = 2;
						item = tree.InsertItem(
							server_info->m_ProgID, 
							image1, 
							image2, 
							TVI_ROOT, 
							TVI_LAST);
						server->tree_item = item;
						tree.SetItemData(item, (DWORD)server);
						tree.SelectItem(item);
						tree.EnsureVisible(item);
					}
				}
			}
			break;
		case ADD_GROUP:
			{
				COPCGroup* group = (COPCGroup*)pHint;
				if(group){
					COPCServer* server = group->get_parent();
					if(server && server->tree_item){
						HTREEITEM item = server->tree_item;
						if(server->is_connected())
							image1 = 3;
						else
							image1 = 4;
						image2 = 5;
						item = tree.InsertItem(
							group->get_name(),
							image1,
							image2,
							item,
							TVI_LAST);
						group->tree_item = item;
						tree.SetItemData(item, (DWORD)group);
						tree.SelectItem(item);
						tree.EnsureVisible(item);
					}
				}
			}
			break;
		case UPDATE_ALL:
			{
				tree.DeleteAllItems();
				POSITION server_pos = theDoc->servers.GetHeadPosition();
				while(server_pos){
					COPCServer* server = theDoc->servers.GetNext(server_pos);
					if(server){
						OPCServerInfo* server_info = server->get_server_info();
						if(!server_info)
							continue;
					
						if(server->is_connected())
							image1 = 0;
						else
							image1 = 1;
						image2 = 2;
						HTREEITEM root_item = tree.InsertItem(
							server_info->m_ProgID,
							image1,
							image2,
							TVI_ROOT,
							TVI_LAST);
						server->tree_item = root_item;
						tree.SetItemData(root_item, (DWORD)server);
						tree.SelectItem(root_item);
						tree.EnsureVisible(root_item);
						
						POSITION group_pos = server->groups.GetHeadPosition();
						while(group_pos){
							COPCGroup* group = server->groups.GetNext(group_pos);
							if(group){
								server->set_current_group(group);
								
								if(server->is_connected())
									image1 = 3;
								else
									image1 = 4;
								image2 = 5;
								HTREEITEM item = tree.InsertItem(
									group->get_name(),
									image1,
									image2,
									root_item,
									TVI_LAST);
								tree.SetItemData(item, (DWORD)group);
								tree.SelectItem(item);
								tree.EnsureVisible(item);
							}
						}	
					}
				}
			}
			break;
		case CLEAR_ALL:
			tree.DeleteAllItems();
			break;
		default:
			break;
			/*
			{
				tree.DeleteAllItems();
				POSITION server_pos = theDoc->servers.GetHeadPosition();
				while(server_pos){
					COPCServer* server = theDoc->servers.GetNext(server_pos);
					if(server){
						OPCServerInfo* server_info = server->get_server_info();
						if(!server_info)
							continue;
						
						HTREEITEM root_item = tree.InsertItem(
							server_info->m_ProgID,
							0,
							1,
							TVI_ROOT,
							TVI_LAST);
						server->tree_item = root_item;
						tree.SetItemData(root_item, (DWORD)server);
						tree.SelectItem(root_item);
						tree.EnsureVisible(root_item);
						
						POSITION group_pos = server->groups.GetHeadPosition();
						while(group_pos){
							COPCGroup* group = server->groups.GetNext(group_pos);
							if(group){
								server->set_current_group(group);
								
								HTREEITEM item = tree.InsertItem(
									group->get_name(),
									2,
									3,
									root_item,
									TVI_LAST);
								tree.SetItemData(item, (DWORD)group);
								tree.SelectItem(item);
								tree.EnsureVisible(item);
							}
						}	
					}
				}
			}
			break;
			*/
	}
}

void CLeftView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pResult)
		*pResult = 0;

	CTreeCtrl& tree = GetTreeCtrl();
	HTREEITEM item = tree.GetSelectedItem();
	if(item == NULL)
		return;

	HTREEITEM parent_item = tree.GetParentItem(item);
	if(parent_item != NULL){	//选中Group节点
		COPCGroup* group = (COPCGroup*)tree.GetItemData(item);
		if(group){
			theDoc->UpdateAllViews(this, UPDATE_GROUP, (CObject*)group);
			if(group->parent)
				theDoc->current_server = group->parent;
		}
	}
	else{				//Server节点
		COPCServer* server = (COPCServer*)tree.GetItemData(item);
		if(server){
			theDoc->UpdateAllViews(this, UPDATE_SERVER, (CObject*)server);
			theDoc->current_server = server;
		}
	}

}

void CLeftView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(pResult)
		*pResult = 0;
	
	CTreeCtrl& tree = GetTreeCtrl();

	GetParentFrame()->ActivateFrame();
	CPoint point;
	GetCursorPos(&point);
	CPoint client_point(point);
	ScreenToClient(&client_point);
	
	HTREEITEM item = tree.HitTest(client_point);
	if(item){
		HTREEITEM parent_item = tree.GetParentItem(item);
		if(parent_item){		//选中group
			COPCServer* server = (COPCServer*)tree.GetItemData(parent_item);
			COPCGroup* group = (COPCGroup*)tree.GetItemData(item);
			if(server && group){
				theDoc->current_server = server;
				server->set_current_group(group);
			}
		}
		else{
			COPCServer* server = (COPCServer*)tree.GetItemData(item);
			if(server)
				theDoc->current_server = server;
		}
		
		tree.SelectItem(item);
		
		CMenu menu;
		if(menu.LoadMenu(IDR_OPC_MENU)){
			menu.GetSubMenu(0)->TrackPopupMenu(
				TPM_LEFTALIGN|TPM_RIGHTBUTTON,
				point.x,
				point.y,
				AfxGetMainWnd());
		}
	}
}


void CLeftView::OnConnectDB() 
{
	// TODO: Add your command handler code here
	MySQL_DIALOG dig;
	dig.DoModal();
	
}

//DEL void CLeftView::OnAppAbout() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL //	CAboutDlg about;
//DEL //	about.DoModal();
//DEL }

/*void CLeftView::OnVersionUP() 
{
	// TODO: Add your command handler code here
	GroupDialog hg;
	hg.DoModal();
}*/

void CLeftView::OnVersionUP() 
{
	// TODO: Add your command handler code here
	UPDATE a1;
	a1.DoModal();
}
