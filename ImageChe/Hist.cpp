
#include "stdafx.h"
#include "ImageChe.h"
#include "Hist.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(Hist, CDialogEx)

Hist::Hist(CWnd* pParent )
	: CDialogEx(IDD_DIALOG_Hist, pParent)
{
	this->Create(IDD_DIALOG_Hist);
	//this->Init();
	//hist = new unsigned int[256];
}
/*
Hist::Hist(CWnd* pParent, int colour)
: CDialogEx(IDD_DIALOG_Hist, pParent)
{
this->Init();
//hist = new unsigned int[256];
}
*/


Hist::~Hist()
{
	//delete[] hist;
}

void Hist::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_tongdao, TongDao);
	DDX_Control(pDX, IDC_STATIC_junzhi, JunZhi);
	DDX_Control(pDX, IDC_STATIC_fangcha, FangCha);
	DDX_Control(pDX, IDC_STATIC_HistRect, Hist_Rect);
}
BEGIN_MESSAGE_MAP(Hist, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()

/*
void Hist::OnPaint()
{
if (hist == NULL)
{
AfxMessageBox("直方图内存不存在！", MB_OK);
return;
}
CPaintDC dc(this);

CRect clinetRect;
//Hist_Rect.GetWindowRect(&clinetRect);
GetDlgItem(IDC_STATIC_HistRect)->GetWindowRect(&clinetRect);
ScreenToClient(&clinetRect);
BeginWaitCursor();
dc.SelectStockObject(NULL_BRUSH);
dc.Rectangle(clinetRect.left - 1, clinetRect.top, clinetRect.right +3, clinetRect.bottom+1);
unsigned int max = 0;
int i = 0;
for (i = 0;i < 256;i++)
{
if (this->hist[i]>max)
max=this->hist[i];
}
double x = clinetRect.Height();
for (i = 0;i < 256;i++)
{
this->hist[i] = (unsigned int )(this->hist[i] * (x/max));
}
for (i = clinetRect.left;i < clinetRect.left+256;i++)
{
dc.MoveTo(i, clinetRect.bottom);
dc.LineTo(i, clinetRect.bottom - this->hist[i- clinetRect.left]);
}
EndWaitCursor();
}
*/
void Hist::OnPaint()
{
	if (this->hist ==NULL)
		return;
	CPaintDC dc(this);
	CRect rectpic;
	GetDlgItem(IDC_STATIC_HistRect)->GetWindowRect(&rectpic);
	int  x, y;
	x = rectpic.Width();
	y = rectpic.Height();
	CWnd  *pWnd = GetDlgItem(IDC_STATIC_HistRect);
	CDC  *pDC = pWnd->GetDC();
	CPen *RedPen = new  CPen();
	switch (Colour)
	{
		case 0:
			RedPen->CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			break;
		case 1:
			RedPen->CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
			break;
		case 2:
			RedPen->CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			break;
		case 3:
			RedPen->CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			break;
		case 4:
			RedPen->CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			break;
		default :
			RedPen->CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				break;

	}
	CGdiObject *RedOlderPen = pDC->SelectObject(RedPen);
	//ScreenToClient(&clinetRect);
	//BeginWaitCursor();

	//dc.SelectStockObject(NULL_BRUSH);
	//dc.Rectangle(rectpic.left - 1, rectpic.top, rectpic.right + 3, rectpic.bottom + 1);
	
	int x1 =5, y1= 5, x2= x-5, y2 = y-5 ;
	double  heght = 0;
	heght = y2 - y1;
	pDC->Rectangle(x1, y1, x2, y2);
	//pDC->Rectangle(x1, y1, x2, y2);
	pDC->MoveTo(x1+5, y1+5);
	pDC->LineTo(x1+5, y2-5);
	pDC->LineTo(x2-5, y2-5);
	pDC->MoveTo(x2-5, y2-5);
	pDC->LineTo(x2 - 5-3, y2 - 5-3);
	pDC->MoveTo(x2 - 5, y2 - 5);
	pDC->LineTo(x2 - 5-3, y2 - 5 + 3);
	pDC->MoveTo(x1 + 5, y1 + 5);
	pDC->LineTo(x1+5-3, y1 + 5+3);
	pDC->MoveTo(x1+5, y1+5);
	pDC->LineTo(x1+5+3,y1+5+3);
	CString str;
	int i;
	x = x1 + 5;
	double Max = 0;
	for (i = 0;i < 256;i++)
	{
		if (this->hist[i] > Max)
			Max = this->hist[i];
	}
	for (i = 0;i<256;i++)
	{
		pDC->MoveTo(x + i, y2 - 5);
		y = (int)(y2 - 5 - ((double)this->hist[i] / Max)*heght);
		if (y < y1 + 5)
			y = y1 + 5;
		pDC->LineTo(x + i, y);
	}
	pDC->SelectObject(RedOlderPen);
	delete RedPen;
	ReleaseDC(pDC);
	delete[]this->hist;
	this->hist = NULL;
	return;
}
void Hist::OnPaint2()
{
	//int  Red[256] = { 50 };
	CPaintDC dc(this);
	CRect rectpic;
	GetDlgItem(IDC_STATIC_HistRect)->GetWindowRect(&rectpic);//IDC_STATIC_HistRect 绘图控件必须为picture控件
	int  x, y;
	x = rectpic.Width();
	y = rectpic.Height();
	CWnd  *pWnd = GetDlgItem(IDC_STATIC_HistRect);
	CDC  *pDC = pWnd->GetDC();
	CPen  *RedPen = new  CPen();
	RedPen->CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	CGdiObject *RedOlderPen = pDC->SelectObject(RedPen);
	pDC->Rectangle(9, 16, 312, 147);
	pDC->MoveTo(15, 20);
	pDC->LineTo(15, 128);
	pDC->LineTo(305, 128);
	pDC->MoveTo(305, 128);
	pDC->LineTo(300, 123);
	pDC->MoveTo(305, 128);
	pDC->LineTo(300, 133);
	pDC->MoveTo(15, 20);
	pDC->LineTo(10, 25);
	pDC->MoveTo(15, 20);
	pDC->LineTo(20, 25);
	CString str;
	int i;
	for (i = 0;i <= 5;i++)//绘制坐标
	{
		str.Format("%d", i * 50);
		pDC->SetTextColor(RGB(255, 0, 255));
		pDC->TextOut(15 + 48 * i, 130, str);
		pDC->MoveTo(15 + 48 * i, 128);
		pDC->LineTo(15 + 48 * i, 125);
	}
	for (i = 0;i <= 5;i++)
	{
		pDC->MoveTo(15, 128 - 20 * i);
		pDC->LineTo(18, 128 - 20 * i);
	}
	for (i = 1;i<256;i++)
	{
		pDC->MoveTo(15 + i, 128);
		if ((128 - 16)>(this->hist[i]/40))
			pDC->LineTo(15 + i, 128 - (this->hist[i] / 40));
		else
			pDC->LineTo(15 + i, 16);
	}
	pDC->SelectObject(RedOlderPen);
	delete RedPen;
	ReleaseDC(pDC);
	return;
}
BOOL Hist::Init()
{
	ASSERT(m_lpszTemplateName != NULL || m_hDialogTemplate != NULL ||
		   m_lpDialogTemplate != NULL);

	MylpDialogTemplate = m_lpDialogTemplate;

	MyhDialogTemplate = m_hDialogTemplate;

	MyhInst = AfxGetResourceHandle();
	if (m_lpszTemplateName != NULL)//
	{
		MyhInst = AfxFindResourceHandle(m_lpszTemplateName, RT_DIALOG);
		HRSRC hResource = ::FindResource(MyhInst, m_lpszTemplateName, RT_DIALOG);
		MyhDialogTemplate = LoadResource(MyhInst, hResource);
	}
	if (MyhDialogTemplate != NULL)//
		MylpDialogTemplate = (LPCDLGTEMPLATE)LockResource(MyhDialogTemplate);
	if (MylpDialogTemplate == NULL)
		return -1;

	MyhWndParent = PreModal();
	AfxUnhookWindowCreate();

	MybEnableParent = FALSE;

	MypMainWnd = NULL;

	MybEnableMainWnd = FALSE;
	if (MyhWndParent && MyhWndParent != ::GetDesktopWindow() && ::IsWindowEnabled(MyhWndParent))
	{
		::EnableWindow(MyhWndParent, FALSE);
		MybEnableParent = TRUE;
		MypMainWnd = AfxGetMainWnd();
		if (MypMainWnd && MypMainWnd->IsFrameWnd() && MypMainWnd->IsWindowEnabled())
		{
			MypMainWnd->EnableWindow(FALSE);
			MybEnableMainWnd = TRUE;
		}
	}
	TRY
	{
		AfxHookWindowCreate(this);//CreateRunDlgIndirect(lpDialogTemplate, CWnd::FromHandle(hWndParent), hInst) 创建对话框 并接收数据 
	if (!CreateRunDlgIndirect(MylpDialogTemplate, CWnd::FromHandle(MyhWndParent), MyhInst) && !m_bClosedByEndDialog)  // 没有调用对话框 初始化函数 控件还未创建 // 创建对话框及控件 
	{
		CreateRunDlgIndirect(MylpDialogTemplate, CWnd::FromHandle(MyhWndParent), AfxGetInstanceHandle());//掉用对话框初始化函数
	}
	}
		CATCH_ALL(e)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed.\n");
		//DELETE_EXCEPTION(e);
		MessageBox("对话框为初始化！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		m_nModalResult = -1;
		return false;
	}
	END_CATCH_ALL
		return m_nModalResult;
}
BOOL Hist::CreateRunDlgIndirect(LPCDLGTEMPLATE lpDialogTemplate, CWnd* pParentWnd, HINSTANCE hInst)
{
	IsInit = CreateDlgIndirect(lpDialogTemplate, pParentWnd, hInst);// 调用对话框初始化函数
	return IsInit;
}
INT_PTR Hist::MyGetData()
{

	if (IsInit)
	{
		if (m_nFlags & WF_CONTINUEMODAL)
		{
			DWORD dwFlags = MLF_SHOWONIDLE;
			if (GetStyle() & DS_NOIDLEMSG)
				dwFlags |= MLF_NOIDLEMSG;
			VERIFY(RunModalLoop(dwFlags) == m_nModalResult);//显示对话框并 读取数据 隐藏对话框
		}
		if (m_hWnd != NULL)
			SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW |
						 SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}
	else
	{
		MessageBox("对话框为初始化！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
	}
	if (m_nModalResult != -1)
		m_bClosedByEndDialog = FALSE;

	if (MybEnableMainWnd)
		MypMainWnd->EnableWindow(TRUE);
	if (MybEnableParent)
		::EnableWindow(MyhWndParent, TRUE);
	if (MyhWndParent != NULL && ::GetActiveWindow() == m_hWnd)
		::SetActiveWindow(MyhWndParent);
	//DestroyWindow();
	//PostModal();
	//if (m_lpszTemplateName != NULL || m_hDialogTemplate != NULL)
	//	UnlockResource(MyhDialogTemplate);
	//if (m_lpszTemplateName != NULL)
	//	FreeResource(MyhDialogTemplate);
	return m_nModalResult;
}
void Hist::DeteleDlg()
{
	if (MybEnableMainWnd)
		MypMainWnd->EnableWindow(TRUE);
	if (MybEnableParent)//
		::EnableWindow(MyhWndParent, TRUE);
	if (MyhWndParent != NULL && ::GetActiveWindow() == m_hWnd)
		::SetActiveWindow(MyhWndParent);
	DestroyWindow();
	PostModal();
	if (m_lpszTemplateName != NULL || m_hDialogTemplate != NULL)
		UnlockResource(MyhDialogTemplate);
	if (m_lpszTemplateName != NULL)
		FreeResource(MyhDialogTemplate);
	IsInit = false;
}
void Hist::OnEnChangeEdit1()
{
	
}
int Hist::RunModalLoop(DWORD dwFlags)
{
	ASSERT(::IsWindow(m_hWnd)); // window must be created
	ASSERT(!(m_nFlags & WF_MODALLOOP)); // window must not already be in modal state

										// for tracking the idle time state
	BOOL bIdle = TRUE;
	LONG lIdleCount = 0;
	BOOL bShowIdle = (dwFlags & MLF_SHOWONIDLE) && !(GetStyle() & WS_VISIBLE);
	HWND hWndParent = ::GetParent(m_hWnd);
	m_nFlags |= (WF_MODALLOOP | WF_CONTINUEMODAL);
	MSG *pMsg = AfxGetCurrentMessage();

	// acquire and dispatch messages until the modal state is done
	for (;;)
	{
		ASSERT(ContinueModal());

		// phase1: check to see if we can do idle work

		while (bIdle &&
			   !::PeekMessage(pMsg, NULL, NULL, NULL, PM_NOREMOVE))
		{
			ASSERT(ContinueModal());

			// show the dialog when the message queue goes idle
			//以后每次显示对话框
			if (bShowIdle)
			{
				ShowWindow(SW_SHOWNORMAL);
				UpdateWindow();
				bShowIdle = FALSE;
			}

			// call OnIdle while in bIdle state
			if (!(dwFlags & MLF_NOIDLEMSG) && hWndParent != NULL && lIdleCount == 0)
			{
				// send WM_ENTERIDLE to the parent
				::SendMessage(hWndParent, WM_ENTERIDLE, MSGF_DIALOGBOX, (LPARAM)m_hWnd);
			}
			if ((dwFlags & MLF_NOKICKIDLE) ||
				!SendMessage(WM_KICKIDLE, MSGF_DIALOGBOX, lIdleCount++))
			{
				// stop idle processing next time
				bIdle = FALSE;
			}
		}

		// phase2: pump messages while available
		//第一次显示对话框
		do
		{
			ASSERT(ContinueModal());

			// pump message, but quit on WM_QUIT
			if (!AfxPumpMessage())// 
			{
				AfxPostQuitMessage(0);
				return -1;
			}

			// show the window when certain special messages rec'd
			if (bShowIdle && (pMsg->message == 0x118 || pMsg->message == WM_SYSKEYDOWN))
			{  // 第一次显示框体和控件
				ShowWindow(SW_SHOWNORMAL);//显示窗口 框体 不显示控件
				UpdateWindow();// 更新数据 显示控件
				bShowIdle = FALSE;
				goto ExitModal;
			}

			if (!ContinueModal())// 对话框的确定 取消 按钮的消息映射 函数退出
				goto ExitModal;

			// 重设没值输入 继续循环  reset "no idle" state after pumping "normal" message
			if (AfxIsIdleMessage(pMsg))
			{
				bIdle = TRUE;
				lIdleCount = 0;
			}

		} while (::PeekMessage(pMsg, NULL, NULL, NULL, PM_NOREMOVE));
	}
	//隐藏对话框的程序在上面 读取对话框控件数据
ExitModal:
	m_nFlags &= ~(WF_MODALLOOP | WF_CONTINUEMODAL);
	return m_nModalResult;
}
