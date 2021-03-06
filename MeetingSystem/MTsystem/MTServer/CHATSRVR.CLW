; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COnlineList
LastTemplate=CListCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "chatsrvr.h"
LastPage=0

ClassCount=8
Class1=CServerApp
Class2=CServerDoc
Class3=CServerView
Class4=CMainFrame

ResourceCount=6
Resource1=IDM_CONTEXTMAIN
Resource2=IDD_DISCUSSION (English (U.S.))
Class5=CAboutDlg
Class6=CDiscussionDlg
Resource3=IDD_CLEANSB
Class7=CCleanDlg
Resource4=IDR_MAINFRAME
Class8=COnlineList
Resource5=IDD_ABOUTBOX
Resource6=IDD_ONLINEDLG

[CLS:CServerApp]
Type=0
HeaderFile=chatsrvr.h
ImplementationFile=chatsrvr.cpp
Filter=N
VirtualFilter=AC
LastObject=ID_EDIT_CUT

[CLS:CServerDoc]
Type=0
HeaderFile=srvrdoc.h
ImplementationFile=srvrdoc.cpp
Filter=N
VirtualFilter=DC
LastObject=CServerDoc
BaseClass=CDocument

[CLS:CServerView]
Type=0
HeaderFile=srvrvw.h
ImplementationFile=srvrvw.cpp
Filter=C

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC



[CLS:CAboutDlg]
Type=0
HeaderFile=chatsrvr.cpp
ImplementationFile=chatsrvr.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_SAVE
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_NEXT_PANE
Command8=ID_PREV_PANE
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_CUT
Command12=ID_EDIT_UNDO
CommandCount=12

[CLS:CDiscussionDlg]
Type=0
HeaderFile=dialogs.h
ImplementationFile=dialogs.cpp
Filter=D
VirtualFilter=dWC

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_SAVE
Command3=ID_APP_EXIT
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_VIEW_TOOLBAR
Command9=ID_VIEW_STATUS_BAR
Command10=ID_APP_ABOUT
Command11=IDC_CHECK_CONNS
CommandCount=11

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_SAVE
Command3=ID_APP_EXIT
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_VIEW_TOOLBAR
Command9=ID_VIEW_STATUS_BAR
Command10=ID_APP_ABOUT
CommandCount=10

[DLG:IDD_DISCUSSION (English (U.S.))]
Type=1
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631424
Control3=IDOK,button,1342242817

[DLG:IDD_CLEANSB]
Type=1
Class=CCleanDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CLEANLIST,listbox,1352728833

[CLS:CCleanDlg]
Type=0
HeaderFile=CleanDlg.h
ImplementationFile=CleanDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CLEANLIST
VirtualFilter=dWC

[MNU:IDM_CONTEXTMAIN]
Type=1
Class=CMainFrame
Command1=ID_RESTORE
Command2=ID_KICKOUT
Command3=ID_APP_ABOUT
Command4=ID_APP_EXIT
CommandCount=4

[CLS:COnlineList]
Type=0
HeaderFile=OnlineList.h
ImplementationFile=OnlineList.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=FWC
LastObject=COnlineList

[DLG:IDD_ONLINEDLG]
Type=1
Class=?
ControlCount=0

