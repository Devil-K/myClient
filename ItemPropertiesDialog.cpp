// ItemPropertiesDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CUS_OPCClient.h"
#include "ItemPropertiesDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CItemPropertiesDialog dialog


CItemPropertiesDialog::CItemPropertiesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CItemPropertiesDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CItemPropertiesDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CItemPropertiesDialog::CItemPropertiesDialog(Item* pItem, CWnd* pParent)
	:CDialog(CItemPropertiesDialog::IDD, pParent), item(pItem)
{
}

void CItemPropertiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CItemPropertiesDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CItemPropertiesDialog, CDialog)
	//{{AFX_MSG_MAP(CItemPropertiesDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CItemPropertiesDialog message handlers

BOOL CItemPropertiesDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
