// CUS_OPCClient.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CUS_OPCClient.h"

#include "MainFrm.h"
#include "OPCClientDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OPCClientApp

BEGIN_MESSAGE_MAP(OPCClientApp, CWinApp)
	//{{AFX_MSG_MAP(OPCClientApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OPCClientApp construction

OPCClientApp::OPCClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only OPCClientApp object

OPCClientApp theApp;
CRITICAL_SECTION item_cs;

/////////////////////////////////////////////////////////////////////////////
// OPCClientApp initialization

BOOL OPCClientApp::InitInstance()
{
	// {F930FA46-B8C5-4004-A4AF-9D73319EE202}
	//static const GUID <<name>> = 
	//{ 0xf930fa46, 0xb8c5, 0x4004, { 0xa4, 0xaf, 0x9d, 0x73, 0x31, 0x9e, 0xe2, 0x2 } };

	HANDLE mutex_handle = ::CreateMutex(
		NULL, 
		FALSE,
		"{F930FA46-B8C5-4004-A4AF-9D73319EE202}");
	if(GetLastError() == ERROR_ALREADY_EXISTS)
		return FALSE;
	else{
		CloseHandle(mutex_handle);
		mutex_handle = 0;
	}
	
	if(!AfxOleInit())
		return false;
	
	InitializeCriticalSection(&item_cs);

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();		// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("CMX_OPCClient"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(OPCClientDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CLeftView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	
	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);
	/*
	if(cmdInfo.m_strFileName.IsEmpty()){
		CString file_name(GetProfileString(_T("Recent File List"), _T("File1")));
		if(!file_name.IsEmpty()){
			CFileStatus file_status;
			if(CFile::GetStatus(file_name, file_status)){
				cmdInfo.m_strFileName = file_name;
				cmdInfo.m_nShellCommand = CCommandLineInfo::FileOpen;
			}
		}
	}
	*/

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->CenterWindow();
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void OPCClientApp::OnAppAbout()
{
	CAboutDlg aboutDlg;						//ÏÔÊ¾ÏûÏ¢¿ò
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// OPCClientApp message handlers


int OPCClientApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	DeleteCriticalSection(&item_cs);

	return CWinApp::ExitInstance();
}
