// OPCClientDoc.cpp : implementation of the OPCClientDoc class
//

#include "stdafx.h"
#include "CUS_OPCClient.h"

#include "OPCClientDoc.h"

#include "ServerDialog.h"
#include "GroupDialog.h"
#include "ItemDialog.h."
#include "writedialog.h"		//write dialog

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

OPCClientDoc* theDoc;
/////////////////////////////////////////////////////////////////////////////
// OPCClientDoc

IMPLEMENT_DYNCREATE(OPCClientDoc, CDocument)

BEGIN_MESSAGE_MAP(OPCClientDoc, CDocument)
	//{{AFX_MSG_MAP(OPCClientDoc)
	ON_COMMAND(ID_OPC_SERVER, OnOpcServer)
	ON_UPDATE_COMMAND_UI(ID_OPC_SERVER, OnUpdateOpcServer)
	ON_COMMAND(ID_OPC_GROUP, OnOpcGroup)
	ON_UPDATE_COMMAND_UI(ID_OPC_GROUP, OnUpdateOpcGroup)
	ON_COMMAND(ID_OPC_ITEM, OnOpcItem)
	ON_UPDATE_COMMAND_UI(ID_OPC_ITEM, OnUpdateOpcItem)
	ON_COMMAND(ID_OPC_CONNECT, OnOpcConnect)
	ON_UPDATE_COMMAND_UI(ID_OPC_CONNECT, OnUpdateOpcConnect)
	ON_COMMAND(ID_OPC_DISCONNECT, OnOpcDisconnect)
	ON_UPDATE_COMMAND_UI(ID_OPC_DISCONNECT, OnUpdateOpcDisconnect)
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
	ON_COMMAND(ID_FILE_EXPORT_LOG, OnFileExportLog)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORT_LOG, OnUpdateFileExportLog)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORT, OnUpdateFileExport)
	ON_COMMAND(ID_ITEM_PROPERTIES, OnItemProperties)
	ON_UPDATE_COMMAND_UI(ID_ITEM_PROPERTIES, OnUpdateItemProperties)
	ON_COMMAND(ID_ITEM_REMOVE, OnItemRemove)
	ON_UPDATE_COMMAND_UI(ID_ITEM_REMOVE, OnUpdateItemRemove)
	ON_COMMAND(ID_ITEM_WRITE, OnItemWrite)
	ON_UPDATE_COMMAND_UI(ID_ITEM_WRITE, OnUpdateItemWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OPCClientDoc construction/destruction

OPCClientDoc::OPCClientDoc()
{
	// TODO: add one-time construction code here
	msg_hwnd = 0;
	data_hwnd = 0;

	current_server = 0;
	
	auto_open = FALSE;

	AfxOleLockApp();
	theDoc = this;
	
	// Everyone can connect back to IAdviseSink
	HRESULT hr = CoInitializeSecurity(NULL, -1, NULL, NULL,
		RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_IDENTIFY, NULL, EOAC_NONE, NULL);
	if (FAILED(hr)){
		//TRACE(_T("CoInitializeSecurity failed, %lx"), hr);
		theDoc->ReportError(_T("CoInitializeSecurity failed: "), hr);
	}

	/*
	handle_out = CreateFile(
		_T("CONOUT$"),
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
		*/
}

OPCClientDoc::~OPCClientDoc()
{
	AfxOleUnlockApp();
	
	theDoc = 0;

	while(!messages.IsEmpty())
		delete messages.RemoveHead();

	while(!servers.IsEmpty())
		delete servers.RemoveHead();

	//if(handle_out != INVALID_HANDLE_VALUE)
	//	CloseHandle(handle_out);
}

BOOL OPCClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	if(!auto_open){
		auto_open = TRUE;
		//打开最近的文件
		OPCClientApp* app = (OPCClientApp*)AfxGetApp();
		CString file_name(app->GetProfileString(_T("Recent File List"), _T("File1")));
		
		if(!file_name.IsEmpty()){
			CFileException fe;
			LPCSTR lpszPathName = file_name.GetBuffer(0);
			CFile* file = GetFile(lpszPathName,
				CFile::modeRead|CFile::shareDenyWrite, 
				&fe);
			if (file != NULL){
				CArchive archive_file(
					file,
					CArchive::load|CArchive::bNoFlushOnDelete);
				archive_file.m_pDocument = this;
				archive_file.m_bForceFlat = FALSE;
				TRY{
					if(file->GetLength() != 0)
						Serialize(archive_file);
					
					archive_file.Close();
					ReleaseFile(file, FALSE);
				}
				CATCH_ALL(e){
					ReleaseFile(file, TRUE);
				}
				END_CATCH_ALL
			}
		}
	}
	else{
		if(AfxMessageBox("Disconnect all OPC Server and delete all data?", 
			MB_YESNO|MB_ICONQUESTION) != IDYES)
			return FALSE;

		Lock wait(&item_cs);
		
		current_server = NULL;
		while(!servers.IsEmpty())
			delete servers.RemoveHead();

		SetModifiedFlag(TRUE);
		UpdateAllViews(NULL, CLEAR_ALL, 0);
	}
	

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// OPCClientDoc serialization

void OPCClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		int server_count = servers.GetCount();
		ar << server_count;
		POSITION pos = servers.GetHeadPosition();
		while(pos){
			COPCServer* server = servers.GetNext(pos);
			server->Serialize(ar);
		}
	}
	else
	{
		// TODO: add loading code here
		while(!servers.IsEmpty())
			delete servers.RemoveHead();

		int server_count = 0;
		ar >> server_count;
		while(server_count --){
			COPCServer* server = new COPCServer;
			if(server){
				server->Serialize(ar);
				current_server = server;

				servers.AddTail(server);
			}
		}

		UpdateAllViews(NULL, UPDATE_ALL, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////
// OPCClientDoc diagnostics

#ifdef _DEBUG
void OPCClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void OPCClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// OPCClientDoc commands

//报错
void OPCClientDoc::ReportError(Message *msg)
{
	if(msg != NULL)
		messages.AddTail(msg);

	if(msg_hwnd)
		PostMessage(msg_hwnd, WM_MESSAGE, 0, (LPARAM)msg);
}

//报错
void OPCClientDoc::ReportError(LPCSTR sz_err)
{
	Message* msg = new Message(sz_err);
	if(msg){
		messages.AddTail(msg);
		
		if(msg_hwnd)
			PostMessage(msg_hwnd, WM_MESSAGE, 0, (LPARAM)msg);
	}

	//	ReportError(msg);
	
}
//报错
void OPCClientDoc::ReportError(LPCSTR description, HRESULT hr)
{
	CString temp(description);
	temp += _T(" ");
	TCHAR msg[MAX_PATH * 5];
	memset(msg, 0, sizeof(msg));
	DWORD ret = FormatMessage(
		FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
		msg,
		MAX_PATH,
		NULL);
	if(ret){
		for(size_t i = 0; i < sizeof(msg); i++)
			if(msg[i] == 13 || msg[i] == 10)
				msg[i] = 0;

		temp += msg;
	}
	else{
		LPWSTR pwstring = NULL;
		if(current_server && current_server->is_connected()){
			hr = current_server->GetErrorString(
				hr,
				LOCALE_SYSTEM_DEFAULT,
				&pwstring);
			if(SUCCEEDED(hr)){
				temp += pwstring;
				CoTaskMemFree(pwstring);
			}
			else
				temp += _T("OPC Server failed GetErrorString().");
		}
		else temp += _T("Unknown Error.");
	}

	ReportError(temp.GetBuffer(0));
}

//添加OPCServer
void OPCClientDoc::OnOpcServer() 
{
	// TODO: Add your command handler code here
	CServerDialog dialog;
	if(dialog.DoModal() == IDOK){
		OPCServerInfo* info = new OPCServerInfo(*dialog.GetServerInfo());

		
		COPCServer* server = new COPCServer;
		if(!server)
			return;
		
		server->SetServerInfo(info);
		server->connect();
		
		current_server = server;
		servers.AddTail(server);

		UpdateAllViews(NULL, ADD_SERVER, (CObject*)server);

		SetModifiedFlag(TRUE);
	}

	
	
}

void OPCClientDoc::OnUpdateOpcServer(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void OPCClientDoc::OnOpcGroup() 
{
	// TODO: Add your command handler code here
	int group_count = current_server->groups.GetCount();
	group_count ++;
	CGroupDialog dialog(group_count);
	if(dialog.DoModal() == IDOK){
		COPCGroup* group = new COPCGroup(current_server);
		if(group){
			group->set_name(dialog.group_name);
			group->set_update_rate(dialog.update_rate);
			group->set_dead_band(dialog.dead_band);
			group->set_time_bias(dialog.time_bias);
			group->set_local_id(dialog.local_id);
			group->set_active(dialog.active);
			
			group->parent = current_server;
			current_server->add_group(group);

			SetModifiedFlag(TRUE);
		}
	}
}

void OPCClientDoc::OnUpdateOpcGroup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(current_server && current_server->is_connected());
}

void OPCClientDoc::OnOpcItem() 
{
	// TODO: Add your command handler code here
	CItemDialog dialog(current_server->get_opc_server());
	if(dialog.DoModal() == IDOK){
		SetModifiedFlag(TRUE);
	}
}

void OPCClientDoc::OnUpdateOpcItem(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(current_server == NULL){
		pCmdUI->Enable(false);
		return;
	}

	COPCGroup* group = current_server->get_current_group();
	if(group == NULL){
		pCmdUI->Enable(false);
		return;
	}
	
	pCmdUI->Enable(group->opc_group.IsOk());
}



void OPCClientDoc::OnOpcConnect() 
{
	// TODO: Add your command handler code here
	if(current_server && !current_server->is_connected())
		current_server->connect();
}

void OPCClientDoc::OnUpdateOpcConnect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!current_server->is_connected());
}

void OPCClientDoc::OnOpcDisconnect() 
{
	// TODO: Add your command handler code here
	
}

void OPCClientDoc::OnUpdateOpcDisconnect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);
}

//导出配置文件
void OPCClientDoc::OnFileExport() 
{
	// TODO: Add your command handler code here
	CFileDialog dialog(
		false, 
		NULL, 
		_T("cmx_opcclient_items.txt"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		_T("CMX_OPCClient Configure File(*.txt)|*.txt|All Files (*.*)|*.*||"),
		NULL
		);
	if(dialog.DoModal() == IDOK){
		CString file_path_name = dialog.GetPathName();
		if(file_path_name.IsEmpty())
			return;
		
		CFile file;
		if(!file.Open(file_path_name, CFile::modeCreate | CFile::modeWrite))
			return;
		
		file.SeekToEnd();
		
		char* desc[10];
		desc[0] = "//*********************************************************//\r\n";
		desc[1] = "//*             CMX_OPCClient items configrue file        *//\r\n";
		desc[2] = "//*             Chen Maoxiang                             *//\r\n";
		desc[3] = "//*             EMail:chenmaoxiang@gmail.com              *//\r\n";
		desc[4] = "//*             MSN:cubeboxstudio@yahoo.com.cn            *//\r\n";
		desc[5] = "//*             QQ:125180837                              *//\r\n";
		desc[6] = "//*********************************************************//\r\n";
		
		
		for(int i = 0; i < 7; i++)
			file.Write(desc[i], strlen(desc[i]));
		
		char sz_data[MAX_PATH];

		Lock wait(&item_cs);
		POSITION server_pos = servers.GetHeadPosition();
		while(server_pos){
			COPCServer* server = servers.GetNext(server_pos);
			if(!server)
				continue;

			OPCServerInfo* info = server->get_server_info();
			ASSERT(info);
			CString node_name = info->m_NodeName;
			if(node_name.IsEmpty())
				node_name = _T("localhost");
			sprintf(sz_data, "\r\nNode Name: \t%s\r\n", node_name.GetBuffer(0));
			file.Write(sz_data, strlen(sz_data));
			memset(sz_data, 0, sizeof(sz_data));

			sprintf(sz_data, "Server Name: \t%s\r\n", info->m_ProgID.GetBuffer(0));
			file.Write(sz_data, strlen(sz_data));
			memset(sz_data, 0, sizeof(sz_data));

			sprintf(sz_data, "CLSID: \t\t{0X%x,0X%x,0X%x,{0X%02x,0X%02x,0X%02x,0X%02x,0X%02x,0X%02x,0X%02x,0X%02x}}\r\n",
				info->m_clsid.Data1,
				info->m_clsid.Data2,
				info->m_clsid.Data3,
				info->m_clsid.Data4[0],
				info->m_clsid.Data4[1],
				info->m_clsid.Data4[2],
				info->m_clsid.Data4[3],
				info->m_clsid.Data4[4],
				info->m_clsid.Data4[5],
				info->m_clsid.Data4[6],
				info->m_clsid.Data4[7]);
			for(size_t i = 0; i < strlen(sz_data); i++){
				sz_data[i] = toupper(sz_data[i]);
			}

			file.Write(sz_data, strlen(sz_data));
			memset(sz_data, 0, sizeof(sz_data));

			POSITION group_pos = server->groups.GetHeadPosition();
			while(group_pos){
				COPCGroup* group = server->groups.GetNext(group_pos);
				if(!group)
					continue;

				sprintf(sz_data, "\t%s\r\n", group->get_name().GetBuffer(0));
				file.Write(sz_data, strlen(sz_data));
				memset(sz_data, 0, sizeof(sz_data));

				POSITION item_pos = group->items.GetHeadPosition();
				while(item_pos){
					Item* item = group->items.GetNext(item_pos);
					if(!item)
						continue;

					sprintf(sz_data, "\t\t%s\r\n", item->name.GetBuffer(0));
					file.Write(sz_data, strlen(sz_data));
					memset(sz_data, 0, sizeof(sz_data));
				}
			}
			
		}
		
		
		desc[7] = "\r\n//*********************************************************//\r\n";
		desc[8] = "//                          End                            //\r\n";
		desc[9] = "//*********************************************************//\r\n";
		
		for(i = 7; i < 10; i++)
			file.Write(desc[i], strlen(desc[i]));
		file.Close();
	}

}

void OPCClientDoc::OnUpdateFileExport(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void OPCClientDoc::OnFileExportLog() 
{
	// TODO: Add your command handler code here
	
}

void OPCClientDoc::OnUpdateFileExportLog(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);
}

void OPCClientDoc::OnItemProperties() 
{
	// TODO: Add your command handler code here
	
}

void OPCClientDoc::OnUpdateItemProperties(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	/*
	pCmdUI->Enable(current_server
		&& current_server->get_current_group()
		&& current_server->get_current_group()->current_item
		);
	*/
	pCmdUI->Enable(FALSE);
}

void OPCClientDoc::OnItemRemove() 
{
	// TODO: Add your command handler code here
	if(current_server && current_server->get_current_group()){
		COPCGroup* group = current_server->get_current_group();
		group->remove_item();
	}
}

void OPCClientDoc::OnUpdateItemRemove(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(current_server
		&& current_server->get_current_group()
		&& current_server->get_current_group()->current_item
		);
}

void OPCClientDoc::OnItemWrite() 
{
	// TODO: Add your command handler code here
	if(current_server == NULL)
		return;

	CWriteDialog dialog;
	if(dialog.DoModal() == IDOK){
		CWaitCursor wait;
		HRESULT* errors = NULL;
	
		COPCGroup* group = current_server->get_current_group();
		if(group == NULL)
			return;
		Item* item = group->current_item;
		if(item == NULL)
			return;

		DWORD transaction_id = 2;
		COleVariant value(dialog.m_value);
		value.ChangeType(item->value.vt);
		
		if(dialog.m_async){		//异步写入
			if(group->use_cp){	//使用连接点
				OPCAsyncIO2 async2;
				if(async2.Attach(group->opc_group) == S_OK){
					
					HRESULT hr = async2.Write(
						1,
						&item->hServerHandle,
						&value,
						transaction_id,
						&transaction_id,
						&errors);
					if(SUCCEEDED(hr)){
						if(FAILED(errors[0]))
							ReportError(_T("Async Write Error: "), errors[0]);

						CoTaskMemFree(errors);
					}
					else
						ReportError(_T("Async Write Error: "), hr);

					async2.Detach();
				}
			}
			else{		//无连接点
				OPCAsyncIO async;
				if(async.Attach(group->opc_group) == S_OK){
					HRESULT hr = async.Write(
						group->connection2,
						1,
						&item->hServerHandle,
						&value,
						&transaction_id,
						&errors);
					if(SUCCEEDED(hr)){
						if(FAILED(errors[0]))
							ReportError(_T("Async Write Error: "), errors[0]);

						CoTaskMemFree(errors);
					}
					else
						ReportError(_T("Async Write Error: "), hr);
					
					async.Detach();
				}
			}
		}
		else{				//同步写入
			OPCAsyncIO async;
			if(async.Attach(group->opc_group) == S_OK){
				HRESULT hr = async.Write(
					group->connection2,
					1,
					&item->hServerHandle,
					&value,
					&transaction_id,
					&errors);
				if(SUCCEEDED(hr)){
					if(FAILED(errors[0]))
						ReportError(_T("Sync Write Error: "), errors[0]);
					
					CoTaskMemFree(errors);
				}
				else
					ReportError(_T("Sync Write Error: "), hr);
				
				async.Detach();
			}
		}
	}
}

void OPCClientDoc::OnUpdateItemWrite(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable(current_server
		&& current_server->get_current_group()
		&& current_server->get_current_group()->current_item
		);
	
	//pCmdUI->Enable(FALSE);
}
