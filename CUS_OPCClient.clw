; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=MySQL_DIALOG
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CUS_OPCClient.h"
LastPage=0

ClassCount=14
Class1=OPCClientApp
Class2=OPCClientDoc
Class3=OPCClientView
Class4=CMainFrame

ResourceCount=11
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_UPDATE
Class5=CLeftView
Class6=CAboutDlg
Class7=MessageView
Resource4=IDD_SERVER_DIALOG
Resource5=IDD_ITEM_DIALOG
Resource6=IDD_GROUP_DIALOG
Class8=CServerDialog
Class9=CGroupDialog
Class10=CItemDialog
Resource7=IDD_MySQL_DIALOG
Resource8=IDD_ABOUTBOX (English (U.S.))
Class11=CItemPropertiesDialog
Class12=CWriteDialog
Resource9=IDD_WRITE_DIALOG
Class13=MySQL_DIALOG
Resource10=IDD_ITEM_PROPERTIES
Class14=UPDATE
Resource11=IDR_MAINFRAME (English (U.S.))

[CLS:OPCClientApp]
Type=0
HeaderFile=CUS_OPCClient.h
ImplementationFile=CUS_OPCClient.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:OPCClientDoc]
Type=0
HeaderFile=OPCClientDoc.h
ImplementationFile=OPCClientDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_APP_ABOUT

[CLS:OPCClientView]
Type=0
HeaderFile=OPCClientView.h
ImplementationFile=OPCClientView.cpp
Filter=C
BaseClass=CListView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=VersionUP



[CLS:CLeftView]
Type=0
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
Filter=T
BaseClass=CTreeView
VirtualFilter=VWC
LastObject=AutomaticTrans

[CLS:CAboutDlg]
Type=0
HeaderFile=CUS_OPCClient.cpp
ImplementationFile=CUS_OPCClient.cpp
Filter=D
LastObject=AutomaticTrans

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_APP_ABOUT
CommandCount=13
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
CommandCount=13
Command4=ID_EDIT_UNDO
Command13=ID_PREV_PANE


[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_OPC_SERVER
Command5=ID_OPC_GROUP
Command6=ID_OPC_ITEM
Command7=ID_APP_modify
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_EXPORT
Command6=ID_FILE_EXPORT_LOG
Command7=ID_APP_EXIT
Command8=ID_OPC_SERVER
Command9=ID_OPC_GROUP
Command10=ID_OPC_ITEM
Command11=ConnectDB
Command12=AutomaticTrans
Command13=UpLoad
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=VersionUP
Command17=ID_APP_ABOUT
CommandCount=17

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1476526080
Control5=IDC_STATIC,static,1476526080

[CLS:MessageView]
Type=0
HeaderFile=MessageView.h
ImplementationFile=MessageView.cpp
BaseClass=CListView
Filter=C
LastObject=ID_APP_ABOUT
VirtualFilter=VWC

[DLG:IDD_SERVER_DIALOG]
Type=1
Class=CServerDialog
ControlCount=12
Control1=IDC_EDT_SERVERNAME,edit,1350631552
Control2=IDC_CBO_NODE,combobox,1344340226
Control3=IDC_RAD_SERVER1,button,1342177289
Control4=IDC_RAD_SERVER2,button,1342177289
Control5=IDC_LST_SERVER,listbox,1352728833
Control6=IDOK,button,1342242816
Control7=IDC_BTN_REFRESH,button,1342242816
Control8=IDCANCEL,button,1342242817
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,button,1342177287

[DLG:IDD_GROUP_DIALOG]
Type=1
Class=CGroupDialog
ControlCount=13
Control1=IDC_EDT_GROUPNAME,edit,1350631552
Control2=IDC_EDT_UPDATERATE,edit,1350631552
Control3=IDC_EDT_DEADBAND,edit,1350631552
Control4=IDC_EDT_TIMEBIAS,edit,1350631552
Control5=IDC_EDT_LOCALID,edit,1350631552
Control6=IDC_CHK_ACTIVE,button,1342242819
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352

[DLG:IDD_ITEM_DIALOG]
Type=1
Class=CItemDialog
ControlCount=22
Control1=IDC_EDT_ITEMNAME,edit,1350631552
Control2=IDC_EDT_ACCESSPATH,edit,1350631552
Control3=IDC_EDT_FILTER,edit,1350631552
Control4=IDC_FLAT,listbox,1084293377
Control5=IDC_TREE,SysTreeView32,1350631431
Control6=IDC_TAG_LIST,listbox,1352728833
Control7=IDC_RAD_NATIVE,button,1342177289
Control8=IDC_RAD_BOOL,button,1342177289
Control9=IDC_RAD_SHORT,button,1342177289
Control10=IDC_RAD_LONG,button,1342177289
Control11=IDC_RAD_FLOAT,button,1342177289
Control12=IDC_RAD_DOUBLE,button,1342177289
Control13=IDC_RAD_STRING,button,1342177289
Control14=IDC_BTN_ADDITEM,button,1342242816
Control15=IDC_BTN_ADDALL,button,1342242816
Control16=IDC_BTN_PROPERTIES,button,1342242816
Control17=IDCANCEL,button,1342242817
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352

[CLS:CServerDialog]
Type=0
HeaderFile=ServerDialog.h
ImplementationFile=ServerDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CServerDialog
VirtualFilter=dWC

[CLS:CGroupDialog]
Type=0
HeaderFile=GroupDialog.h
ImplementationFile=GroupDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CGroupDialog
VirtualFilter=dWC

[CLS:CItemDialog]
Type=0
HeaderFile=ItemDialog.h
ImplementationFile=ItemDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_OPC_CONNECT
VirtualFilter=dWC

[DLG:IDD_ITEM_PROPERTIES]
Type=1
Class=CItemPropertiesDialog
ControlCount=2
Control1=IDCANCEL,button,1342242817
Control2=IDC_LIST,SysListView32,1350633473

[CLS:CItemPropertiesDialog]
Type=0
HeaderFile=ItemPropertiesDialog.h
ImplementationFile=ItemPropertiesDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CItemPropertiesDialog
VirtualFilter=dWC

[DLG:IDD_WRITE_DIALOG]
Type=1
Class=CWriteDialog
ControlCount=5
Control1=IDC_EDT_VALUE,edit,1350631552
Control2=IDC_CHK_ASYNC,button,1342242819
Control3=IDOK,button,1342242816
Control4=IDCANCEL,button,1342242817
Control5=IDC_STATIC,static,1342308352

[CLS:CWriteDialog]
Type=0
HeaderFile=WriteDialog.h
ImplementationFile=WriteDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CWriteDialog

[CLS:MySQL_DIALOG]
Type=0
HeaderFile=MySQL_DIALOG.h
ImplementationFile=MySQL_DIALOG.cpp
BaseClass=CDialog
Filter=D
LastObject=DIO_InsertDB
VirtualFilter=dWC

[DLG:IDD_MySQL_DIALOG]
Type=1
Class=MySQL_DIALOG
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_EDIT2,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=DIO_InsertDB,button,1342242817

[DLG:IDD_UPDATE]
Type=1
Class=UPDATE
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDUPDATE,button,1342242816

[CLS:UPDATE]
Type=0
HeaderFile=UPDATE.h
ImplementationFile=UPDATE.cpp
BaseClass=CDialog
Filter=D

