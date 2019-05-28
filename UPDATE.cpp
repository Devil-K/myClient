// UPDATE.cpp : implementation file
//

#include "stdafx.h"
#include "CUS_OPCClient.h"
#include "UPDATE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// UPDATE dialog


UPDATE::UPDATE(CWnd* pParent /*=NULL*/)
	: CDialog(UPDATE::IDD, pParent)
{
	//{{AFX_DATA_INIT(UPDATE)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void UPDATE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(UPDATE)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(UPDATE, CDialog)
	//{{AFX_MSG_MAP(UPDATE)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// UPDATE message handlers
