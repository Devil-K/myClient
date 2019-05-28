// GroupDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CUS_OPCClient.h"
#include "GroupDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGroupDialog dialog


CGroupDialog::CGroupDialog(int group_index, CWnd* pParent /*=NULL*/)
	: CDialog(CGroupDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGroupDialog)
	active = TRUE;
	dead_band = 0.0f;
	group_name.Format(_T("Group%d"), group_index);
	local_id = 0;
	time_bias = 0;
	update_rate = 1000;
	//}}AFX_DATA_INIT
}


void CGroupDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGroupDialog)
	DDX_Check(pDX, IDC_CHK_ACTIVE, active);
	DDX_Text(pDX, IDC_EDT_DEADBAND, dead_band);
	DDV_MinMaxFloat(pDX, dead_band, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDT_GROUPNAME, group_name);
	DDV_MaxChars(pDX, group_name, 256);
	DDX_Text(pDX, IDC_EDT_LOCALID, local_id);
	DDV_MinMaxLong(pDX, local_id, 0, 32768);
	DDX_Text(pDX, IDC_EDT_TIMEBIAS, time_bias);
	DDV_MinMaxUInt(pDX, time_bias, 0, 1440);
	DDX_Text(pDX, IDC_EDT_UPDATERATE, update_rate);
	DDV_MinMaxUInt(pDX, update_rate, 1000, 10000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGroupDialog, CDialog)
	//{{AFX_MSG_MAP(CGroupDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGroupDialog message handlers
