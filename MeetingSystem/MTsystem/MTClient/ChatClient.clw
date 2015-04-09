; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTextEdit
LastTemplate=CEdit
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "chatclient.h"
LastPage=0

ClassCount=15
Class1=CChatClientApp
Class2=CAboutDlg
Class3=CChatClientDoc
Class4=CChatClientView
Class5=CLogin
Class6=CMainFrame
Class7=COnlineBar
Class8=COnlineList
Class9=CToolTipWnd

ResourceCount=14
Resource1=IDD_ABOUTBOX
Resource2=IDD_SENDDLG
Resource3=IDR_CNTR_INPLACE
Resource4=IDR_WHSTYLE
Resource5=IDD_PROPPAGE_DLine1 (English (U.S.))
Resource6=IDR_MAINFRAME
Class10=CWhiteBoard
Resource7=IDD_ONLINEDLG
Resource8=IDD_PROPPAGE_DLine2 (English (U.S.))
Resource9=IDD_DIgWhiteborad
Resource10=IDD_WRITE_TEXT
Class11=CDLineDlg1
Class12=CDLineDlg2
Resource11=IDR_WHITEBAORD
Resource12=IDD_SETUP
Class13=CTextWriteDlg
Resource13=IDR_TOOLBAROFWHITEBOARD
Class14=CTextFontDlg
Class15=CTextEdit
Resource14=ID_TEXT_FONT

[CLS:CChatClientApp]
Type=0
BaseClass=CWinApp
HeaderFile=ChatClient.h
ImplementationFile=ChatClient.cpp
Filter=N
VirtualFilter=AC
LastObject=CChatClientApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ChatClient.cpp
ImplementationFile=ChatClient.cpp
LastObject=CAboutDlg

[CLS:CChatClientDoc]
Type=0
BaseClass=CRichEditDoc
HeaderFile=ChatClientDoc.h
ImplementationFile=ChatClientDoc.cpp
Filter=N
VirtualFilter=DC
LastObject=CChatClientDoc

[CLS:CChatClientView]
Type=0
BaseClass=CRichEditView
HeaderFile=ChatClientView.h
ImplementationFile=ChatClientView.cpp
Filter=C
VirtualFilter=VWC
LastObject=ID_EDIT_CUT

[CLS:CLogin]
Type=0
BaseClass=CDialog
HeaderFile=Login.h
ImplementationFile=Login.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC

[CLS:COnlineBar]
Type=0
BaseClass=CDialogBar
HeaderFile=OnlineBar.h
ImplementationFile=OnlineBar.cpp

[CLS:COnlineList]
Type=0
BaseClass=CListCtrl
HeaderFile=OnlineList.h
ImplementationFile=OnlineList.cpp
LastObject=COnlineList

[CLS:CToolTipWnd]
Type=0
BaseClass=CWnd
HeaderFile=ToolTipWnd.h
ImplementationFile=ToolTipWnd.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SETUP]
Type=1
Class=CLogin
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_NAME,combobox,1344340226
Control5=IDC_STATIC,static,1342308352
Control6=IDC_SERVER,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_IMAGE,combobox,1344340226

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDC_CONNECT
Command2=IDC_DISCONNECT
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_FILE_PRINT
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_MAINFRAME]
Type=1
Class=CChatClientView
Command1=IDC_CONNECT
Command2=IDC_DISCONNECT
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_PASTE_SPECIAL
Command15=ID_EDIT_SELECT_ALL
Command16=ID_EDIT_FIND
Command17=ID_EDIT_REPEAT
Command18=ID_EDIT_REPLACE
Command19=ID_OLE_INSERT_NEW
Command20=ID_OLE_EDIT_LINKS
Command21=ID_OLE_EDIT_PROPERTIES
Command22=ID_OLE_VERB_FIRST
Command23=ID_VIEW_TOOLBAR
Command24=ID_VIEW_STATUS_BAR
Command25=ID_WB_POPUP
Command26=ID_APP_ABOUT
CommandCount=26

[MNU:IDR_CNTR_INPLACE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
CommandCount=9

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_SELECT_ALL
Command2=ID_EDIT_COPY
Command3=ID_EDIT_FIND
Command4=ID_EDIT_REPLACE
Command5=ID_FILE_NEW
Command6=ID_FILE_OPEN
Command7=ID_FILE_PRINT
Command8=ID_FILE_SAVE
Command9=ID_EDIT_PASTE
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_CANCEL_EDIT_CNTR
Command13=ID_EDIT_REPEAT
Command14=ID_NEXT_PANE
Command15=ID_PREV_PANE
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=IDC_SEND
Command19=ID_OLE_EDIT_PROPERTIES
Command20=ID_EDIT_CUT
Command21=ID_EDIT_UNDO
CommandCount=21

[ACL:IDR_CNTR_INPLACE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_CANCEL_EDIT_CNTR
CommandCount=7

[DLG:IDD_SENDDLG]
Type=1
Class=CChatClientView
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_TO,combobox,1344340226
Control3=IDC_SEND,button,1342242816
Control4=IDC_TYPE,combobox,1344339970
Control5=IDC_SECRET,button,1342242819
Control6=IDC_FILTER,button,1342242819
Control7=IDC_STATIC,static,1342308352
Control8=IDC_TEXT,edit,1350631552
Control9=IDC_COLOR,button,1342242816

[DLG:IDD_ONLINEDLG]
Type=1
Class=?
ControlCount=0

[DLG:IDD_DIgWhiteborad]
Type=1
Class=CWhiteBoard
ControlCount=4
Control1=IDC_STATIC_WHITEBK,static,1342177294
Control2=IDC_EDIT_WHITEBOARCOLOSNOWSEL,edit,1484785792
Control3=IDC_BTNWCOLOSSEL,button,1342177291
Control4=IDC_RESHOWCOLOR,RICHEDIT,1484851328

[CLS:CWhiteBoard]
Type=0
HeaderFile=WhiteBoard.h
ImplementationFile=WhiteBoard.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_HS_VERTICAL
VirtualFilter=dWC

[MNU:IDR_WHITEBAORD]
Type=1
Class=?
Command1=ID_WHITEBORD_QUIT
Command2=ID_WHITEBORD__DRWALINE
Command3=ID_WHITEBOAR_DREAPO
Command4=ID_WHITENORD_DRAWREC
Command5=ID_WHITEBOARD_DRAWCIRCLE
CommandCount=5

[TB:IDR_TOOLBAROFWHITEBOARD]
Type=1
Class=?
Command1=ID_DRAW_LINE
Command2=ID_DRAW_CRCLELINE
Command3=ID_DRAW_PLINE
Command4=ID_DRAW_RGN
Command5=ID_DRAW_CIRCLE
Command6=ID_DRAW_CIRCLEL
CommandCount=6

[DLG:IDD_PROPPAGE_DLine1 (English (U.S.))]
Type=1
Class=CDLineDlg1
ControlCount=26
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RADIO_Ps_Solid,button,1342308361
Control3=IDC_RADIO2,button,1342177289
Control4=IDC_RADIO3,button,1342177289
Control5=IDC_RADIO4,button,1342177289
Control6=IDC_RADIO5,button,1342177289
Control7=IDC_RADIO15,button,1342177289
Control8=IDC_RADIO16,button,1342177289
Control9=IDC_STATIC_ShowPenStyle,static,1342177287
Control10=IDC_STATIC,button,1342177287
Control11=IDC_EDIT_LineWidth,edit,1350631552
Control12=IDC_SPIN_DDLineWidth,msctls_updown32,1342177334
Control13=IDC_STATIC,button,1342177287
Control14=IDC_RADIO6_bs_hollow,button,1342308361
Control15=IDC_RADIO7_bs_solid,button,1342177289
Control16=IDC_RADIO8_hatched,button,1342177289
Control17=IDC_STATIC,button,1342177287
Control18=IDC_RADIO9_HS_BDIAGONAL,button,1342308361
Control19=IDC_RADIO11_HS_DIAGCROSS,button,1342177289
Control20=IDC_RADIO13_HS_FDIAGONAL,button,1342177289
Control21=IDC_RADIO10_HS_CROSS,button,1342177289
Control22=IDC_RADIO14_HS_HORIZONTAL,button,1342177289
Control23=IDC_RADIO_HS_VERTICAL,button,1342177289
Control24=IDC_STATIC_ShowBrushResult,static,1342177287
Control25=IDC_COMBO_BackgroundMode,combobox,1344340227
Control26=IDC_STATIC,button,1342177287

[DLG:IDD_PROPPAGE_DLine2 (English (U.S.))]
Type=1
Class=CDLineDlg2
ControlCount=38
Control1=IDC_STATIC_Black,static,1350570766
Control2=IDC_STATIC_RarkRed,static,1350570766
Control3=IDC_STATIC_DrakGreen,static,1350570766
Control4=IDC_STATIC_DarkYellow,static,1350570766
Control5=IDC_STATIC_DrakBlue,static,1350570766
Control6=IDC_STATIC_Yellow,static,1350570766
Control7=IDC_STATIC_DarkGray,static,1350570766
Control8=IDC_STATIC_LightRray,static,1350570766
Control9=IDC_STATIC_White,static,1350570766
Control10=IDC_STATIC_Red,static,1350570766
Control11=IDC_STATIC_Blue,static,1350570766
Control12=IDC_STATIC_BITMAP5,static,1350570766
Control13=IDC_STATIC_Green,static,1350570766
Control14=IDC_STATIC_BITMAP6,static,1350570766
Control15=IDC_STATIC_BITMAP9,static,1350570766
Control16=IDC_STATIC_BITMAP10,static,1350570766
Control17=IDC_EDIT_Red,edit,1350633600
Control18=IDC_STATIC_Red2,static,1350570766
Control19=IDC_STATIC_Green2,static,1350570766
Control20=IDC_EDIT_Green,edit,1350633600
Control21=IDC_STATIC_Blue2,static,1350570766
Control22=IDC_EDIT_Blue,edit,1350633600
Control23=IDC_SPIN_Red,msctls_updown32,1073741856
Control24=IDC_SPIN_Green,msctls_updown32,1073741856
Control25=IDC_SPIN_Blue,msctls_updown32,1073741856
Control26=IDC_SLIDER_Red,msctls_trackbar32,1342242821
Control27=IDC_SLIDER_Green,msctls_trackbar32,1342242821
Control28=IDC_SLIDER_Blue,msctls_trackbar32,1342242821
Control29=IDC_STATIC_ShowColor,static,1350569992
Control30=IDC_STATIC,button,1342177287
Control31=IDC_BUTTON_Select,button,1342242816
Control32=IDC_BUTTON_ColorDlg,button,1342242816
Control33=IDC_CHECK_Pen,button,1342242819
Control34=IDC_CHECK_Brush,button,1342242819
Control35=IDC_CHECK_Background,button,1342242819
Control36=IDC_ShowPenColor,static,1350569991
Control37=IDC_ShowBrushColor,static,1350569991
Control38=IDC_ShowBackground,static,1350569991

[CLS:CDLineDlg1]
Type=0
HeaderFile=DLineDlg11.h
ImplementationFile=DLineDlg11.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CDLineDlg1

[CLS:CDLineDlg2]
Type=0
HeaderFile=DLineDlg21.h
ImplementationFile=DLineDlg21.cpp
BaseClass=CPropertyPage
Filter=D

[TB:IDR_WHSTYLE]
Type=1
Class=?
Command1=ID_LINEWIDE_ONE
Command2=ID_LINEWIDE_TWO
Command3=ID_LINEWIDE_THREE
Command4=ID_HS_BDIAGONAL
Command5=ID_HS_DIAGCROSS
Command6=ID_HS_FDIAGONAL
Command7=ID_HS_CROSS
Command8=ID_HS_HORZIONTAL
Command9=ID_HS_VERTICAL
Command10=ID_HS_SOLID
CommandCount=10

[DLG:IDD_WRITE_TEXT]
Type=1
Class=CTextWriteDlg
ControlCount=5
Control1=IDOKTEXT,button,1342242817
Control2=IDCANCELTEXT,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TEXT_EDIT,edit,1350631552
Control5=IDC_BUTTON_FONT,button,1342242816

[CLS:CTextWriteDlg]
Type=0
HeaderFile=TextWriteDlg.h
ImplementationFile=TextWriteDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CTextWriteDlg
VirtualFilter=dWC

[DLG:ID_TEXT_FONT]
Type=1
Class=CTextFontDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_FONTHIGHT,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_FONTWIDE,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_FONTBETWEEN,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_TEXTANGEL,edit,1350631552
Control12=IDC_EDIT_FONTANGEL,edit,1350631552

[CLS:CTextFontDlg]
Type=0
HeaderFile=TextFontDlg.h
ImplementationFile=TextFontDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CTextFontDlg
VirtualFilter=dWC

[CLS:CTextEdit]
Type=0
HeaderFile=TextEdit.h
ImplementationFile=TextEdit.cpp
BaseClass=CEdit
Filter=W

