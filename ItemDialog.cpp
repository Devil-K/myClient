// ItemDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CUS_OPCClient.h"
#include "ItemDialog.h"
#include "opcserver.h"
#include "opcclientdoc.h"		//OPCClientDoc

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern OPCClientDoc* theDoc;
/////////////////////////////////////////////////////////////////////////////
// CItemDialog dialog


CItemDialog::CItemDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CItemDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CItemDialog)
	access_path = _T("");
	filter = _T("");
	item_name = _T("");
	m_vt = VT_EMPTY;
	//}}AFX_DATA_INIT
}


CItemDialog::CItemDialog(IOPCServer *server, CWnd *pParent)
	:CDialog(CItemDialog::IDD, pParent)
{
	if(server)
		browse.Attach(server);

	access_path = _T("");
	filter = _T("");
	item_name = _T("");
	m_vt = VT_EMPTY;
	
}
void CItemDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CItemDialog)
	DDX_Control(pDX, IDC_TREE, m_tree);
	DDX_Control(pDX, IDC_TAG_LIST, m_tag);
	DDX_Control(pDX, IDC_FLAT, m_flat);
	DDX_Text(pDX, IDC_EDT_ACCESSPATH, access_path);
	DDX_Text(pDX, IDC_EDT_FILTER, filter);
	DDX_Text(pDX, IDC_EDT_ITEMNAME, item_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CItemDialog, CDialog)
	//{{AFX_MSG_MAP(CItemDialog)
	ON_BN_CLICKED(IDC_BTN_ADDITEM, OnBtnAdditem)
	ON_BN_CLICKED(IDC_BTN_ADDALL, OnBtnAddall)
	ON_BN_CLICKED(IDC_BTN_PROPERTIES, OnBtnProperties)
	ON_BN_CLICKED(IDC_RAD_NATIVE, OnRadNative)
	ON_BN_CLICKED(IDC_RAD_BOOL, OnRadBool)
	ON_BN_CLICKED(IDC_RAD_SHORT, OnRadShort)
	ON_BN_CLICKED(IDC_RAD_LONG, OnRadLong)
	ON_BN_CLICKED(IDC_RAD_FLOAT, OnRadFloat)
	ON_BN_CLICKED(IDC_RAD_DOUBLE, OnRadDouble)
	ON_BN_CLICKED(IDC_RAD_STRING, OnRadString)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE, OnItemexpandingTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
	ON_LBN_SELCHANGE(IDC_FLAT, OnSelchangeFlat)
	ON_LBN_SELCHANGE(IDC_TAG_LIST, OnSelchangeTagList)
	ON_LBN_DBLCLK(IDC_TAG_LIST, OnDblclkTagList)
	ON_LBN_DBLCLK(IDC_FLAT, OnDblclkFlat)
	ON_EN_CHANGE(IDC_EDT_FILTER, OnChangeEdtFilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CItemDialog message handlers

void CItemDialog::OnBtnAdditem() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor wait;
	UpdateData();
	
	Lock wait_cs(&item_cs);

	if(theDoc){
		Item* item = new Item;
		ASSERT(item);
		item->name = item_name;
		item->access_path = access_path;
		item->native_type = m_vt;
		item->quality = OPC_QUALITY_GOOD;
		item->active = true;

		COPCServer* server = theDoc->current_server;
		if(server != NULL){
			COPCGroup* group = server->get_current_group();
			if(group != NULL){
				item = group->add_item(item);
				
				if(item)
					theDoc->UpdateAllViews(NULL, UPDATE_GROUP, (CObject*)group);
			}
		}
	}
}

void CItemDialog::OnBtnAddall() 
{
	// TODO: Add your control notification handler code here
	USES_CONVERSION;

	CWaitCursor wait;
	Lock wait_cs(&item_cs);
	
	if(!theDoc)
		return;
	COPCServer* server = theDoc->current_server;
	if(!server)
		return;
	COPCGroup* group = server->get_current_group();
	if(group == NULL)
		return;
	
	int tag_count = m_tag.GetCount();
	//Item*	items = new Item[tag_count];
	//ASSERT(items);

	for(int i = 0; i < tag_count; i++){
		
		HTREEITEM tree_item = m_tree.GetSelectedItem();
		HRESULT hr = BrowseHere(tree_item);

		item_name.Empty();
		m_tag.GetText(i, item_name);
		//UpdateData(false);

		//从Server端读取该点
		LPWSTR item_id = NULL;
		hr = browse.GetItemID(T2OLE(item_name.GetBuffer(0)), &item_id);
		if(SUCCEEDED(hr)){
			item_name = item_id;
			CoTaskMemFree(item_id);
		}

		UpdateData(false);
		
		hr = S_OK;
		for(int i = 0; i < 16 && SUCCEEDED(hr); i++){
			hr = browse.ChangeBrowsePosition(
				OPC_BROWSE_UP,
				L"");
		}

		Item* item = new Item;
		//Item* item = items + i;
		if(item){
			item->name = item_name;
			item->access_path = access_path;
			item->native_type = m_vt;
			item->quality = OPC_QUALITY_GOOD;
			item->active = true;

			group->add_item(item);
		}
	}

	//DWORD dwCount = group->add_items(tag_count, items);

	theDoc->UpdateAllViews(NULL, UPDATE_GROUP, (CObject*)group);
}

void CItemDialog::OnBtnProperties() 
{
	// TODO: Add your control notification handler code here
	
}

void CItemDialog::OnRadNative() 
{
	// TODO: Add your control notification handler code here
	m_vt = VT_EMPTY;
	if(name_space_type == OPC_NS_HIERARCHIAL)
		OnSelchangedTree(NULL, NULL);
	else
		UpdateFlat();
}

void CItemDialog::OnRadBool() 
{
	// TODO: Add your control notification handler code here
	m_vt = VT_BOOL;
	if(name_space_type == OPC_NS_HIERARCHIAL)
		OnSelchangedTree(NULL, NULL);
	else
		UpdateFlat();
}

void CItemDialog::OnRadShort() 
{
	// TODO: Add your control notification handler code here
	m_vt = VT_I2;
	if(name_space_type == OPC_NS_HIERARCHIAL)
		OnSelchangedTree(NULL, NULL);
	else
		UpdateFlat();
}

void CItemDialog::OnRadLong() 
{
	// TODO: Add your control notification handler code here
	m_vt = VT_I4;
	if(name_space_type == OPC_NS_HIERARCHIAL)
		OnSelchangedTree(NULL, NULL);
	else
		UpdateFlat();
}

void CItemDialog::OnRadFloat() 
{
	// TODO: Add your control notification handler code here
	m_vt = VT_R4;
	if(name_space_type == OPC_NS_HIERARCHIAL)
		OnSelchangedTree(NULL, NULL);
	else
		UpdateFlat();
}

void CItemDialog::OnRadDouble() 
{
	// TODO: Add your control notification handler code here
	m_vt = VT_R8;
	if(name_space_type == OPC_NS_HIERARCHIAL)
		OnSelchangedTree(NULL, NULL);
	else
		UpdateFlat();
}

void CItemDialog::OnRadString() 
{
	// TODO: Add your control notification handler code here
	m_vt = VT_BSTR;
	if(name_space_type == OPC_NS_HIERARCHIAL)
		OnSelchangedTree(NULL, NULL);
	else
		UpdateFlat();
}

void CItemDialog::OnItemexpandingTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	// TODO: Add your control notification handler code here
	USES_CONVERSION;
	
	if(!browse.IsOk())
		return;

	CWaitCursor wait;
	
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM start = pNMTreeView->itemNew.hItem;
	if(!start)
		return;

	DWORD expand = m_tree.GetItemData(start);
	if(!expand){	//没有展开
		m_tree.SetItemData(start, 1);

		HTREEITEM item = m_tree.GetNextItem(start, TVGN_CHILD);
		while(item){		//删除已有的child
			m_tree.DeleteItem(item);
			item = m_tree.GetNextItem(start, TVGN_CHILD);
		}

		//插入新点
		HRESULT hr = BrowseHere(start);
		if(SUCCEEDED(hr)){
			IEnumString* enum_string = NULL;
			hr = browse.BrowseOPCItemIDs(
				OPC_BRANCH,
				L"*",
				VT_EMPTY,
				0,
				&enum_string);
			if(SUCCEEDED(hr)){
				LPWSTR	name[NEXT_COUNT];
				ULONG	count = 0;
				do{
					hr = enum_string->Next(NEXT_COUNT, &name[0], &count);
					for(ULONG index = 0; index < count; index++){
						CString item_name(name[index]);
						HTREEITEM item = m_tree.InsertItem(item_name, start);
						m_tree.SetItemData(item, 0);
						m_tree.InsertItem(_T("Dummy"), item);
						CoTaskMemFree(name[index]);
					}
				}while(hr == S_OK);
				enum_string->Release();
			}
		}

		hr = S_OK;
		for(int i = 0; i < 16 && SUCCEEDED(hr); i++){
			hr = browse.ChangeBrowsePosition(
				OPC_BROWSE_UP,
				L"");
		}
	}

	if(pResult)
		*pResult = 0;
}

void CItemDialog::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	USES_CONVERSION;
	if(!browse.IsOk())
		return;
	
	CButton* button_add_all = (CButton*)GetDlgItem(IDC_BTN_ADDALL);
	ASSERT(button_add_all);

	CWaitCursor wait;
	HTREEITEM item = m_tree.GetSelectedItem();
	HRESULT hr = BrowseHere(item);
	if(SUCCEEDED(hr)){
		m_tag.ResetContent();
		
		IEnumString* enum_string = 0;
		hr = browse.BrowseOPCItemIDs(
			OPC_LEAF,
			T2OLE(filter.GetBuffer(0)),
			m_vt,
			0,
			&enum_string);
		if(SUCCEEDED(hr)){
			LPWSTR name[NEXT_COUNT];
			ULONG count = 0;
			do{
				hr = enum_string->Next(NEXT_COUNT, &name[0], &count);
				for(ULONG index = 0; index < count; index++){
					CString tag_name(name[index]);
					m_tag.AddString(tag_name);

					CoTaskMemFree(name[index]);
				}
				
			}while(hr == S_OK);
			enum_string->Release();
		}
	}
	
	hr = S_OK;
	for(int i = 0; i < 16 && SUCCEEDED(hr); i++){
		hr = browse.ChangeBrowsePosition(
			OPC_BROWSE_UP,
			L"");
	}

	if(pResult)
		*pResult = 0;
}

void CItemDialog::OnSelchangeFlat() 
{
	// TODO: Add your control notification handler code here
	USES_CONVERSION;
	if(!browse.IsOk())
		return;
	
	CWaitCursor wait;
	
	item_name.Empty();
	int sel = m_flat.GetCurSel();
	if(sel != LB_ERR){
		m_flat.GetText(sel, item_name);
	}
	else
		return;

	LPWSTR item_id = NULL;
	HRESULT hr = browse.GetItemID(T2OLE(item_name.GetBuffer(0)), &item_id);
	if(SUCCEEDED(hr)){
		item_name = item_id;

		UpdateData(false);

		CoTaskMemFree(item_id);
	}

	
	
}


BOOL CItemDialog::OnInitDialog() 
{
	USES_CONVERSION;
	CWaitCursor wait;
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_BTN_PROPERTIES)->EnableWindow(false);
	CheckRadioButton(IDC_RAD_NATIVE, IDC_RAD_STRING, IDC_RAD_NATIVE);

	if(!browse.IsOk()){
		m_tag.ShowWindow(false);
		m_tree.ShowWindow(false);
		m_flat.ShowWindow(true);

		m_flat.AddString( _T("Browsing not supported") );

		return true;
	}
	else{
	}
	
	HRESULT hr = browse.QueryOrganization(&name_space_type);
	if(FAILED(hr)){
		browse.Detach();
		return TRUE;
	}

	if(name_space_type == OPC_NS_HIERARCHIAL){	//tree
		HTREEITEM root = m_tree.InsertItem(_T("root"));
		m_tree.SetItemData(root, 1);
		IEnumString* enum_string = NULL;

		hr = browse.BrowseOPCItemIDs(
			OPC_BRANCH,
			L"*",
			m_vt,
			0,
			&enum_string);
		if(SUCCEEDED(hr)){
			LPWSTR	name[NEXT_COUNT];
			ULONG	count = 0;
			
			do{
				hr = enum_string->Next(
					NEXT_COUNT,
					&name[0],
					&count);
				
				for(ULONG index = 0; index < count; index ++){
					CString item_name(name[index]);
					HTREEITEM item = m_tree.InsertItem(item_name, root);
					m_tree.SetItemData(item, 0);
					m_tree.InsertItem("Dummy", item);
					CoTaskMemFree(name[index]);
				}
			}while(hr == S_OK);
			enum_string->Release();
		}
		m_tree.SelectItem(root);
		m_tree.Expand(root, TVE_EXPAND);
	}
	else{
		m_tag.ShowWindow(false);
		m_tree.ShowWindow(false);
		m_flat.ShowWindow(true);

		UpdateFlat();
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//更新Flat
void CItemDialog::UpdateFlat()
{
	USES_CONVERSION;
	if(!browse.IsOk())
		return;

	CWaitCursor wait;
	m_flat.ResetContent();

	IEnumString* enum_string = NULL;
	HRESULT hr = browse.BrowseOPCItemIDs(
		OPC_FLAT,
		T2OLE(filter.GetBuffer(0)),
		m_vt,
		0,
		&enum_string);
	if(SUCCEEDED(hr)){
		LPWSTR item_id[NEXT_COUNT];
		ULONG	count = 0;
		do{
			hr = enum_string->Next(NEXT_COUNT, &item_id[0], &count);
			for(ULONG index = 0; index < count; index ++){
				CString name =(item_id[index]);
				m_flat.AddString(name);
			}
		}while(hr == S_OK);
		enum_string->Release();
	}

	m_flat.SetCurSel(0);
}

//
HRESULT CItemDialog::BrowseHere(HTREEITEM item)
{
	USES_CONVERSION;
	if(!browse.IsOk())
		return E_FAIL;

	HRESULT hr = S_OK;
	if(item != NULL){
		HTREEITEM parent = m_tree.GetParentItem(item);
		hr = BrowseHere(parent);
		if(SUCCEEDED(hr)){
			CString node(m_tree.GetItemText(item));
			if(node != _T("root")){
				hr = browse.ChangeBrowsePosition(
					OPC_BROWSE_DOWN,
					T2OLE(node.GetBuffer(0)));
			}
		}
	}

	return hr;
}

void CItemDialog::OnSelchangeTagList() 
{
	// TODO: Add your control notification handler code here
	USES_CONVERSION;
	if(!browse.IsOk())
		return;
	
	CButton* button = (CButton*)GetDlgItem(IDC_BTN_PROPERTIES);

	CWaitCursor wait;
	HTREEITEM item = m_tree.GetSelectedItem();
	HRESULT hr = BrowseHere(item);

	item_name.Empty();
	int sel = m_tag.GetCurSel();
	if(sel != LB_ERR){
		m_tag.GetText(sel, item_name);
		if(button)
			button->EnableWindow(false);
	}
	else
		return;

	//从Server端读取该点
	LPWSTR item_id = NULL;
	hr = browse.GetItemID(T2OLE(item_name.GetBuffer(0)), &item_id);
	if(SUCCEEDED(hr)){
		item_name = item_id;
		CoTaskMemFree(item_id);

		if(button)
			button->EnableWindow(false/*true*/);	//将来改成true
	}
	UpdateData(false);

	hr = S_OK;
	for(int i = 0; i < 16 && SUCCEEDED(hr); i++){
		hr = browse.ChangeBrowsePosition(
			OPC_BROWSE_UP,
			L"");
	}
}

void CItemDialog::OnDblclkTagList() 
{
	// TODO: Add your control notification handler code here
	OnBtnAdditem();
}

void CItemDialog::OnDblclkFlat() 
{
	// TODO: Add your control notification handler code here
	OnBtnAdditem();
}

void CItemDialog::OnChangeEdtFilter() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();

	if(name_space_type == OPC_NS_HIERARCHIAL)
		OnSelchangedTree(NULL, NULL);
	else
		UpdateFlat();
}
