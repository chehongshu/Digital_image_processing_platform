
// ImageChe.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ImageChe.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "ImageCheDoc.h"
#include "ImageCheView.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageCheApp

BEGIN_MESSAGE_MAP(CImageCheApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CImageCheApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_OPEN, &CImageCheApp::OnFileOpen)
END_MESSAGE_MAP()


// CImageCheApp 构造

CImageCheApp::CImageCheApp()
{
	m_bHiColorIcons = TRUE;

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ImageChe.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}
// 唯一的一个 CImageCheApp 对象
CImageCheApp theApp;
// CImageCheApp 初始化
BOOL CImageCheApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinAppEx::InitInstance();
	 //初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	/*
	顾名思义，AfxEnableControlContainer()函数是允许应用程序作为控件容器来使用，也就是说你可以在这个应用程序中使用ocx之类的控件。对于用MFC向导自动生成的单文档框架程序的C...APP::InitInstance()函数中自动加了这一句 AfxEnableControlContainer();
	如果在程序中使用控件时弹出莫名其妙的错误的时候，看看是不是没有加这一句。
	*/
    AfxEnableControlContainer();
	/*
	启用任务栏交互。
	必须在主窗口中创建之前调用此方法，否则断言并返回 FALSE。
	*/
	EnableTaskbarInteraction();
	
	
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();//上下文菜单管理

	InitKeyboardManager();// 键盘应用
	/*
	InitTooltipManager();//初始化对象
    CMFCToolTipInfo ttParams;
	//ttParams.m_bVislManagerTheme = TRUE;
	//theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
	//	RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	*/
	
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_ImageCheTYPE,
		RUNTIME_CLASS(CImageCheDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CImageCheView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 创建主 MDI 框架窗口
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
    

	/*默认参数为TRUE，表示主窗口以及每一个子窗口（文件窗口）都可以接
	受来自shell的拖放文档。CFrameWnd内有一个OnDropFiles成员函数，负责
	对WM_DROPFILES消息作出响应，它会通知application对象的OnOpenDocument
	函数，并夹带被拖放的档案的名称。*/
	m_pMainWnd->DragAcceptFiles();
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);//此函数想shell注册本程序的文件类型。这个函数搜索Document Template链表中的每一种文件类型，然后把他加到系统所维护的registry中。

    // 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if(cmdInfo.m_strFileName.IsEmpty())//如果命令行为空 就不打开文档
	{
	   cmdInfo.m_nShellCommand =CCommandLineInfo::FileNothing;//取消主窗口在初始化时显示
	}
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 主窗口已初始化，因此显示它并对其进行更新
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CImageCheApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);
	return CWinAppEx::ExitInstance();
}
// CImageCheApp 消息处理程序
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
	public:
//	CListBox AboutText;
//	afx_msg void OnSelchangeListAbout();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LIST1, AboutText);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_LBN_SELCHANGE(IDC_LIST_about, &CAboutDlg::OnSelchangeListAbout)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CImageCheApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CImageCheApp 自定义加载/保存方法

void CImageCheApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CImageCheApp::LoadCustomState()
{
}

void CImageCheApp::SaveCustomState()
{
}
// CImageCheApp 消息处理程序
void CImageCheApp::OnFileOpen()
{
	CString newName;
	ENSURE(m_pDocManager != NULL);
	if (!m_pDocManager->DoPromptFileName(newName, AFX_IDS_OPENFILE,
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, TRUE, NULL))
		return;
	AfxGetApp()->OpenDocumentFile(newName);//调用CWinApp中的CDocMent 的OpenDocumentFile 函数 在到 
	//m_pDocManager->OnFileOpen();

	//ENSURE(m_pDocManager != NULL);
	// m_pDocManager->OnFileOpen();
	//DocManager->OnFileOpen() 内容
	//if (!DoPromptFileName(newName, AFX_IDS_OPENFILE,
	//OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, TRUE, NULL))
	//return; // open cancelled
	//AfxGetApp()->OpenDocumentFile(newName);// 调用CDocument::OnOpenDocument 打开文档 可以重载这个函数
	//DoPromptFileName(newName);
	// 1. 在这里弹出自己的打开文件对话框
	// 2. 直接调用OpenDocumentFile(newName)
	// OpenDocumentFile(newName);*/
}


//void CAboutDlg::OnSelchangeListAbout()
//{
//	int index=m_listText.getCur
//}
