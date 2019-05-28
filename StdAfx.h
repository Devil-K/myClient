// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__69E344C3_3763_4876_8212_5ADD90147F04__INCLUDED_)
#define AFX_STDAFX_H__69E344C3_3763_4876_8212_5ADD90147F04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN				// Exclude rarely-used stuff from Windows headers
#define _WIN32_DCOM				// This includes new DCOM calls

/*
#include <afxwin.h>				// MFC core and standard components
#include <afxext.h>				// MFC extensions
#include <afxcview.h>
#include <afxdisp.h>				// MFC Automation classes
#include <afxdtctl.h>				// MFC support for Internet Explorer 4 Common Controls
#include <afxtempl.h>
*/

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#include <afxcmn.h>         // MFC support for Windows Common Controls
#include <afxtempl.h>       // MFC template collections
#include <afxcview.h>
#include <atlbase.h>        // ATL conversion functions

#include "lock.h"				//lock
extern CRITICAL_SECTION item_cs;

/*
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>				// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
*/

//#include <atlbase.h>

#include "opcwrap.h"

unsigned long const NEXT_COUNT = 100;
unsigned int const  MAX_KEYLEN = 256;

#define WM_DATACHANGE	WM_USER + 1		//数据变化
#define WM_DATAWRITE	WM_USER + 2		//写操作
#define WM_OPCSHUTDOWN	WM_USER + 3		//服务器关闭
#define WM_MESSAGE		WM_USER + 4		//错误消息

//视图刷新
enum VIEW_UPDATE{
	ADD_SERVER = 1,			//添加server
	ADD_GROUP,			//添加Group
	ADD_ITEM,			//添加Item
	UPDATE_SERVER,			//刷新Server,显示该Server所有点
	UPDATE_GROUP,			//刷新Group,显示该Group下所有点
	UPDATE_ITEM_VALUE,		//更新点值
	UPDATE_ALL,			//更新所有
	CLEAR_ALL
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__69E344C3_3763_4876_8212_5ADD90147F04__INCLUDED_)
