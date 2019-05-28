// WriteDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CUS_OPCClient.h"
#include "WriteDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWriteDialog dialog


CWriteDialog::CWriteDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CWriteDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWriteDialog)
	m_async = FALSE;
	m_value = _T("");
	//}}AFX_DATA_INIT
}


void CWriteDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWriteDialog)
	DDX_Check(pDX, IDC_CHK_ASYNC, m_async);
	DDX_Text(pDX, IDC_EDT_VALUE, m_value);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWriteDialog, CDialog)
	//{{AFX_MSG_MAP(CWriteDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWriteDialog message handlers
