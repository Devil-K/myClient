// ServerDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CUS_OPCClient.h"
#include "ServerDialog.h"
#include "opcclientdoc.h"	//document head file
#include <LMCONS.H>
#include <lmserver.h>
//#include <winnetwk.h>		//network

const CLSID CLSID_OPCServerList = {0x13486D51,0x4821,0x11D2,{0xA4,0x94,0x3C,0xB3,0x06,0xC1,0x00,0x00}};
#define __GUID_DEFINED__
#include "OPCDa_Cats.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern OPCClientDoc* theDoc;

/////////////////////////////////////////////////////////////////////////////
// CServerDialog dialog


CServerDialog::CServerDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerDialog)
	m_strNodeName = _T("");
	m_strServerName = _T("");
	//}}AFX_DATA_INIT
	
	server_info = 0;
	cat_id = CATID_OPCDAServer20;
	memset(&clsid, 0, sizeof(clsid));
	enumerated = false;
}
CServerDialog::CServerDialog(OPCServerInfo* info, CWnd* pParent)
:CDialog(CServerDialog::IDD, pParent)
{
	server_info = info;

	if(server_info){
		m_strNodeName = server_info->m_NodeName;
		m_strServerName = server_info->m_ProgID;
		memcpy(&clsid, &info->m_clsid, sizeof(clsid));
	}
	else{
		m_strNodeName = _T("");
		m_strServerName = _T("");
		memset(&clsid, 0, sizeof(clsid));
	}

	cat_id = CATID_OPCDAServer20;
	
	enumerated = false;
}


void CServerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerDialog)
	DDX_Control(pDX, IDC_LST_SERVER, m_lstServer);
	DDX_CBString(pDX, IDC_CBO_NODE, m_strNodeName);
	DDV_MaxChars(pDX, m_strNodeName, 128);
	DDX_Text(pDX, IDC_EDT_SERVERNAME, m_strServerName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServerDialog, CDialog)
	//{{AFX_MSG_MAP(CServerDialog)
	ON_BN_CLICKED(IDC_RAD_SERVER1, OnRadServer1)
	ON_BN_CLICKED(IDC_RAD_SERVER2, OnRadServer2)
	ON_LBN_SELCHANGE(IDC_LST_SERVER, OnSelchangeLstServer)
	ON_LBN_DBLCLK(IDC_LST_SERVER, OnDblclkLstServer)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_CBN_DROPDOWN(IDC_CBO_NODE, OnDropdownCboNode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerDialog message handlers
//选OPC1.0
void CServerDialog::OnRadServer1() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	cat_id = CATID_OPCDAServer10;

	GetOPCServers(m_strNodeName.GetBuffer(0));
}
//OPC2.0
void CServerDialog::OnRadServer2() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	cat_id = CATID_OPCDAServer20;

	GetOPCServers(m_strNodeName.GetBuffer(0));
}

//选择服务器
void CServerDialog::OnSelchangeLstServer() 
{
	// TODO: Add your control notification handler code here
	try{
		CListBox* list = (CListBox*)GetDlgItem(IDC_LST_SERVER);
		if(list){
			int list_pos = list->GetCurSel();
			OPCServerInfo* info = (OPCServerInfo*)list->GetItemData(list_pos);
			if(list_pos >= 0 && info != NULL){
				server_info = info;

				m_strServerName = info->m_ProgID;
				m_strNodeName = info->m_NodeName;
				if(m_strNodeName.CompareNoCase(_T("127.0.0.1")) == 0)
					m_strNodeName = _T("");

				UpdateData(false);
			}
		}
	}
	catch(...){
	}
}

void CServerDialog::OnDblclkLstServer() 
{
	// TODO: Add your control notification handler code here
	
}

//刷新服务器列表
void CServerDialog::OnBtnRefresh() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	GetOPCServers(m_strNodeName.GetBuffer(0));
}

//获取服务器列表
void CServerDialog::GetOPCServers(LPCSTR sz_node)
{
	USES_CONVERSION;
	CWaitCursor wait;

	CListBox* list = (CListBox*)GetDlgItem(IDC_LST_SERVER);
	if(!list)
		return;
	list->ResetContent();

	IOPCServerList*	server_list = 0;
	COSERVERINFO	si;
	MULTI_QI	qi;
	
	si.dwReserved1 = 0;
	si.dwReserved2 = 0;
	if(sz_node && sz_node[0] != 0)
		si.pwszName = T2OLE(sz_node);
	else
		si.pwszName = NULL;
	si.pAuthInfo = NULL;

	qi.pIID = &IID_IOPCServerList;
	qi.pItf = NULL;
	qi.hr = 0;
	
	HRESULT hr = CoCreateInstanceEx(
		CLSID_OPCServerList,
		NULL,
		CLSCTX_ALL,
		&si,
		1,
		&qi);
	if(FAILED(hr) || FAILED(qi.hr)){
		CString msg(_T("Error connecting to OPC 2.0 Server Browser."));
		if( !m_strNodeName.IsEmpty() )
			msg.Format(_T("Error connecting to OPC 2.0 Server Browser on %s."), (LPCTSTR)m_strNodeName);
		
		if( hr == REGDB_E_CLASSNOTREG )
		{
			CString msg(_T("Please install the OPC 2.0 Components."));
			if( !m_strNodeName.IsEmpty() )
				msg.Format(_T("Please install the OPC 2.0 Components on %s."), (LPCTSTR)m_strNodeName);
		}
		
		if( FAILED(hr) )
			theDoc->ReportError(msg, hr);
		else
			theDoc->ReportError(msg, qi.hr);
	}
	else{
		server_list = (IOPCServerList*)qi.pItf;
		IEnumGUID* enum_guid = NULL;
		hr = server_list->EnumClassesOfCategories(
			1,
			&cat_id,
			1,
			&cat_id,
			&enum_guid);
		if(SUCCEEDED(hr)){
			unsigned long count = 0;
			CLSID cls_id[NEXT_COUNT];
			
			do{
				hr = enum_guid->Next(NEXT_COUNT, cls_id, &count);
				for(unsigned int index = 0; index < count; index ++){
					LPOLESTR prog_id;
					LPOLESTR user_type;
					HRESULT hr2 = server_list->GetClassDetails(cls_id[index], &prog_id, &user_type);
					if(SUCCEEDED(hr2)){
						OPCServerInfo* info = new OPCServerInfo(prog_id, user_type, cls_id[index]);
						if(info){
							info->m_NodeName = sz_node;
							server_infos.AddTail(info);
							server_info = info;
						}

						CString name;
						name.Format(_T("%s"),(LPCTSTR)info->m_ProgID);
						int list_pos = list->AddString(name);
						list->SetItemData(list_pos, (DWORD)info);

						if(m_strServerName == info->m_ProgID)
							list->SetCurSel(list_pos);

						CoTaskMemFree(prog_id);
						CoTaskMemFree(user_type);
					}
				}
			}while(hr == S_OK);

			enum_guid->Release();
			server_list->Release();
		}
		else{
			CString msg(_T("EnumClassesOfCategories failed:"));
			theDoc->ReportError(msg, hr);
		}
	}
	if(list->GetCount() > 0){
		list->SetCurSel(0);
		OnSelchangeLstServer();
	}
	
	//OPC 1.0
	if( cat_id != CATID_OPCDAServer10 )
		return;
	
	HKEY hk = HKEY_CLASSES_ROOT;
	if( sz_node )
	{
		DWORD dwR = RegConnectRegistry ((LPTSTR)sz_node, HKEY_CLASSES_ROOT, &hk);
		if( dwR != ERROR_SUCCESS )
			return;
	}
	
	TCHAR key[MAX_KEYLEN];
	DWORD size = MAX_KEYLEN;
	FILETIME ft;
	for( int index=0; RegEnumKeyEx(hk, index, key, &size, 0, NULL, NULL, &ft)==ERROR_SUCCESS; index++)
	{
		HKEY hProgID=0;
		if(RegOpenKeyEx(hk, key, 0, KEY_QUERY_VALUE, &hProgID )==ERROR_SUCCESS )
		{
			// Find OPC key
			HKEY hOPC=0;
			if(RegOpenKeyEx(hProgID, _T("OPC"), 0, KEY_QUERY_VALUE, &hOPC)==ERROR_SUCCESS )
			{
				// Found OPC key, save this information
				CLSID clsid;
				DWORD type=REG_SZ;
				HKEY hCLSID=0;
				if(RegOpenKeyEx(hProgID, _T("CLSID"), 0, KEY_QUERY_VALUE, &hCLSID)==ERROR_SUCCESS )
				{
					TCHAR clsidString[MAX_KEYLEN];
					size=MAX_KEYLEN;
					if(RegQueryValueEx(hCLSID, key, 0, &type, (BYTE*)clsidString, &size )==ERROR_SUCCESS )
					{
						hr = CLSIDFromString( T2OLE(clsidString), &clsid );
						if( FAILED(hr))
						{
							theDoc->ReportError( _T("CLSIDFromString: "), hr );
							continue;
						}
					}
				}
				
				TCHAR desc[MAX_KEYLEN];
				size=MAX_KEYLEN;
				RegQueryValueEx(hOPC, key, 0, &type, (BYTE*)desc, &size);
				OPCServerInfo* pServerInfo = new OPCServerInfo(T2OLE(key), L"", clsid );
				server_infos.AddTail( pServerInfo );
				int pos = list->AddString( pServerInfo->m_ProgID );
				list->SetItemData( pos, (DWORD)pServerInfo );
				if( m_strServerName == key )
					list->SetCurSel(pos);
				RegCloseKey( hOPC );
			}
			RegCloseKey( hProgID );
		}
		size = MAX_KEYLEN;
	}
	
	if(list->GetCount() > 0){
		list->SetCurSel(0);
		OnSelchangeLstServer();
	}
}

BOOL CServerDialog::OnInitDialog() 
{
	CWaitCursor wait;

	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CheckRadioButton(IDC_RAD_SERVER2, IDC_RAD_SERVER1, IDC_RAD_SERVER2);

	GetOPCServers();
	//调试时能打开控制台输出
	AllocConsole();
	freopen("CONOUT$","a+",stdout);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//枚举网络节点
bool CServerDialog::EnumerateNodes(LPNETRESOURCE lpnr)
{
	CComboBox* pNodes = (CComboBox*)GetDlgItem(IDC_CBO_NODE);
	ASSERT(pNodes);
	
	HANDLE hEnum = 0;
	DWORD dwResult = WNetOpenEnum(RESOURCE_GLOBALNET,
		RESOURCETYPE_ANY,
		RESOURCEUSAGE_CONTAINER,
		lpnr,              // NULL first time this function is called
		&hEnum);           // handle to resource
	
	if (dwResult != NO_ERROR)
	{
		return FALSE;
	}
	
	DWORD cbBuffer = 16384;      // 16K buffer
	LPNETRESOURCE lpnrLocal = (LPNETRESOURCE) GlobalAlloc(GPTR, cbBuffer);
	do
	{
		DWORD cEntries = 0xFFFFFFFF; // enumerate all possible entries
		dwResult = WNetEnumResource(hEnum,
			&cEntries,
			lpnrLocal,
			&cbBuffer);
		
		if (dwResult == NO_ERROR)
		{
			for( DWORD i = 0; i < cEntries; i++)
			{
				// If this NETRESOURCE is a container, call the function
				// recursively.
				if(RESOURCEUSAGE_CONTAINER ==
					(lpnrLocal[i].dwUsage & RESOURCEUSAGE_CONTAINER))
				{
					if(RESOURCEDISPLAYTYPE_SERVER == lpnrLocal[i].dwDisplayType )
					{
						CString node(lpnrLocal[i].lpRemoteName);
						int index = node.Find( _T("\\") );
						if( index > -1 )
							node = node.Mid(index+2);
						if( pNodes )
							pNodes->AddString(node);
					}
					else
					{
						EnumerateNodes(&lpnrLocal[i]);
						break;   // ONLY enumerate the first "Container"
					}
				}
			}
		}
		else if (dwResult != ERROR_NO_MORE_ITEMS)
		{
			break;
		}
	}
	while(dwResult != ERROR_NO_MORE_ITEMS);
	
	GlobalFree((HGLOBAL) lpnrLocal);
	
	dwResult = WNetCloseEnum(hEnum);
	
	pNodes->SetWindowText(m_strNodeName);
	
	if (dwResult != NO_ERROR)
	{
		return FALSE;
	}
	return true;
}

void CServerDialog::OnDropdownCboNode() 
{
	// TODO: Add your control notification handler code here
	if(!enumerated){
		CWaitCursor wait;

		EnumerateNodes(NULL);

		enumerated = true;
	}
}

//获取OPCServerInfo
OPCServerInfo* CServerDialog::GetServerInfo()
{
	return server_info;
}
