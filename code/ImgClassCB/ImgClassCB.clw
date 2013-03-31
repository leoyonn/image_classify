; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ImgClassCB.h"
LastPage=0

ClassCount=12
Class1=CDirectoryTreeBar
Class2=CDirTreeCtrl
Class3=CMainFrame
Class4=CPreviewBar
Class5=CImgClassCBApp
Class6=CAboutDlg
Class7=CImgClassCBDoc
Class8=CImgClassCBView

ResourceCount=7
Resource1=IDD_DLG_ViewResult
Resource2=IDD_DLG_TrainDlg
Resource3=IDR_MAINFRAME
Class9=CTestDlg
Class10=CFeatureExDlg
Resource4=IDD_DLG_TestDlg
Class11=CTrainDlg
Resource5=IDD_DLG_FeatureEx
Resource6=IDD_ABOUTBOX
Class12=CViewResults
Resource7=IDR_MAINFRAME (English (U.S.))

[CLS:CDirectoryTreeBar]
Type=0
BaseClass=CSizingControlBarG
HeaderFile=DirectoryTreeBar.h
ImplementationFile=DirectoryTreeBar.cpp
Filter=W
VirtualFilter=WC
LastObject=CDirectoryTreeBar

[CLS:CDirTreeCtrl]
Type=0
BaseClass=CTreeCtrl
HeaderFile=DirTreeCtrl.h
ImplementationFile=DirTreeCtrl.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CPreviewBar]
Type=0
BaseClass=CSizingControlBarG
HeaderFile=PreviewBar.h
ImplementationFile=PreviewBar.cpp
Filter=W
VirtualFilter=WC
LastObject=CPreviewBar

[CLS:CImgClassCBApp]
Type=0
BaseClass=CWinApp
HeaderFile=ImgClassCB.h
ImplementationFile=ImgClassCB.cpp
Filter=N
VirtualFilter=AC
LastObject=ID_MENU_ViewResult

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ImgClassCB.cpp
ImplementationFile=ImgClassCB.cpp
LastObject=CAboutDlg
Filter=D
VirtualFilter=dWC

[CLS:CImgClassCBDoc]
Type=0
BaseClass=CDocument
HeaderFile=ImgClassCBDoc.h
ImplementationFile=ImgClassCBDoc.cpp
LastObject=CImgClassCBDoc

[CLS:CImgClassCBView]
Type=0
BaseClass=CListView
HeaderFile=ImgClassCBView.h
ImplementationFile=ImgClassCBView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CImgClassCBView

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342373889
Control2=IDC_STATIC,static,1342177283
Control3=IDC_STATIC,static,1342308480
Control4=IDC_STATIC,static,1342308352
Control5=IDC_BTN_EMAIL,button,1342242816
Control6=IDC_BTN_README,button,1342373888

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_STOP_THREAD
Command3=ID_APP_ABOUT
CommandCount=3

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[MNU:IDR_MAINFRAME]
Type=1
Class=CImgClassCBApp
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_MENU_FeatureExtract
Command4=ID_MENU_Train
Command5=ID_MENU_Test
Command6=ID_MENU_ViewResult
Command7=ID_VIEW_TOOLBAR
Command8=ID_VIEW_STATUS_BAR
Command9=ID_VIEW_DIRECTORY_BAR
Command10=ID_VIEW_PREVIEW_BAR
Command11=ID_APP_ABOUT
CommandCount=11

[DLG:IDD_DLG_FeatureEx]
Type=1
Class=CFeatureExDlg
ControlCount=26
Control1=IDC_EDT_INTRAIN,edit,1350633600
Control2=IDC_EDT_INTEST,edit,1350633600
Control3=IDC_EDT_OUTTRAIN,edit,1350633600
Control4=IDC_EDT_OUTTEST,edit,1350633600
Control5=IDC_BTN_INTRAINBRO,button,1476395008
Control6=IDC_BTN_INTESTBRO,button,1476395008
Control7=IDC_BTN_OUTTRAINBRO,button,1476460544
Control8=IDC_BTN_OUTTESTBRO,button,1476460544
Control9=IDC_RAD_0,button,1342373897
Control10=IDC_RAD_1,button,1342242825
Control11=IDC_RAD_2,button,1342242825
Control12=IDC_RAD_3,button,1342242825
Control13=IDC_RAD_4,button,1342242825
Control14=IDC_RAD_5,button,1476395017
Control15=IDC_RAD_6,button,1342242825
Control16=IDC_RAD_7,button,1342242825
Control17=IDC_RAD_11,button,1342242825
Control18=IDC_RAD_9,button,1342242825
Control19=IDOK,button,1342242817
Control20=IDCANCEL,button,1342242816
Control21=IDC_STATIC,button,1342177287
Control22=IDC_STATIC,button,1342177287
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352

[CLS:CFeatureExDlg]
Type=0
HeaderFile=FeatureExDlg.h
ImplementationFile=FeatureExDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CFeatureExDlg
VirtualFilter=dWC

[DLG:IDD_DLG_TrainDlg]
Type=1
Class=CTrainDlg
ControlCount=26
Control1=IDC_EDT_INFeatTrain,edit,1484849280
Control2=IDC_EDT_OutFeatTrain,edit,1484849280
Control3=IDC_BTN_InFeatTrainBro,button,1476460544
Control4=IDC_BTN_OutFeatTrainBro,button,1476460544
Control5=IDC_RAD_0,button,1342308361
Control6=IDC_RAD_1,button,1342177289
Control7=IDC_RAD_20,button,1342177289
Control8=IDC_RAD_3,button,1342177289
Control9=IDC_RAD_4,button,1342177289
Control10=IDC_RAD_5,button,1342177289
Control11=IDC_RAD_6,button,1342177289
Control12=IDC_RAD_7,button,1342177289
Control13=IDC_RAD_8,button,1342177289
Control14=IDC_RAD_9,button,1342177289
Control15=IDC_RAD_11,button,1342308361
Control16=IDC_RAD_12,button,1342177289
Control17=IDC_RADIO12,button,1476395017
Control18=IDC_RADIO13,button,1476395017
Control19=IDC_RADIO14,button,1476395017
Control20=IDOK,button,1342242817
Control21=IDCANCEL,button,1342242816
Control22=IDC_STATIC,button,1342177287
Control23=IDC_STATIC,button,1342177287
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,button,1342177287

[CLS:CTrainDlg]
Type=0
HeaderFile=TrainDlg.h
ImplementationFile=TrainDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDT_INFeatTrain
VirtualFilter=dWC

[DLG:IDD_DLG_TestDlg]
Type=1
Class=CTestDlg
ControlCount=26
Control1=IDC_EDT_INFeatTest,edit,1484849280
Control2=IDC_EDT_OutFeatTest,edit,1484849280
Control3=IDC_BTN_InFeatTestBro,button,1476460544
Control4=IDC_BTN_OutFeatTestBro,button,1476460544
Control5=IDC_RAD_0,button,1342308361
Control6=IDC_RAD_1,button,1342177289
Control7=IDC_RAD_2,button,1342177289
Control8=IDC_RAD_3,button,1342177289
Control9=IDC_RAD_4,button,1342177289
Control10=IDC_RAD_5,button,1342177289
Control11=IDC_RAD_6,button,1342177289
Control12=IDC_RAD_7,button,1342177289
Control13=IDC_RAD_8,button,1342177289
Control14=IDC_RAD_9,button,1342177289
Control15=IDC_RAD_11,button,1342308361
Control16=IDC_RAD_12,button,1342177289
Control17=IDC_RADIO12,button,1476395017
Control18=IDC_RADIO13,button,1476395017
Control19=IDC_RADIO14,button,1476395017
Control20=IDOK,button,1342242817
Control21=IDCANCEL,button,1342242816
Control22=IDC_STATIC,button,1342177287
Control23=IDC_STATIC,button,1342177287
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,button,1342177287

[CLS:CTestDlg]
Type=0
HeaderFile=TestDlg.h
ImplementationFile=TestDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CTestDlg
VirtualFilter=dWC

[DLG:IDD_DLG_ViewResult]
Type=1
Class=CViewResults
ControlCount=29
Control1=IDC_EDT_INResultFile,edit,1350631552
Control2=IDC_BTN_InResultFileBro,button,1342242816
Control3=IDC_RAD_0,button,1342308361
Control4=IDC_RAD_1,button,1342177289
Control5=IDC_RAD_20,button,1342177289
Control6=IDC_RAD_3,button,1342177289
Control7=IDC_RAD_4,button,1342177289
Control8=IDC_RAD_5,button,1342177289
Control9=IDC_RAD_6,button,1342177289
Control10=IDC_RAD_7,button,1342177289
Control11=IDC_RAD_8,button,1342177289
Control12=IDC_RAD_9,button,1342177289
Control13=IDC_RAD_11,button,1342308361
Control14=IDC_RAD_12,button,1342177289
Control15=IDC_RADIO12,button,1476395017
Control16=IDC_RADIO13,button,1476395017
Control17=IDC_RADIO14,button,1476395017
Control18=IDOK,button,1342242817
Control19=IDCANCEL,button,1342242816
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,button,1342177287
Control22=IDC_BTN_ConMatText,button,1342242816
Control23=IDC_STATIC,button,1342177287
Control24=IDC_STATIC,button,1342177287
Control25=IDC_STATIC,button,1342177287
Control26=IDC_BTN_ConMatImg,button,1342242816
Control27=IDC_PICTURE,static,1342177294
Control28=IDC_BTN_LoadRRW,button,1342242816
Control29=IDC_BTN_ViewResultTxt,button,1342242816

[CLS:CViewResults]
Type=0
HeaderFile=ViewResults.h
ImplementationFile=ViewResults.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RAD_0
VirtualFilter=dWC

