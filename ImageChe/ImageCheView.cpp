


#include "stdafx.h"
#include "ImageChe.h"

#include "MainFrm.h"
#include "ImageCheDoc.h"
#include "ImageCheView.h"
#include "MyImage.h"
#include "Inter_Num.h"
#include "Hist.h"
#include "Hist_Select.h"
//#include <iostream>
//namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CImageCheView, CScrollView)

BEGIN_MESSAGE_MAP(CImageCheView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageCheView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32801, &CImageCheView::OnUpDownMove)
	ON_COMMAND(ID_32803, &CImageCheView::OnXunHuanPingYi)
	ON_COMMAND(ID_32791, &CImageCheView::OnXuanZhuan)
	ON_COMMAND(ID_32794, &CImageCheView::OnLinYuJunZhi)
	ON_COMMAND(ID_32804, &CImageCheView::OnXieBo)
	ON_COMMAND(ID_Menu32805, &CImageCheView::OnNiXieBo)
	ON_COMMAND(ID_32796, &CImageCheView::OnZhongZhiLvBo)
	ON_COMMAND(ID_32774, &CImageCheView::OnYuZhi)
	ON_COMMAND(ID_32780, &CImageCheView::OnXX)
	ON_COMMAND(ID_32807, &CImageCheView::OnPengZhang)
	ON_COMMAND(ID_32808, &CImageCheView::OnFuShi)
	ON_COMMAND(ID_32809, &CImageCheView::OnKaiYunSuan)
	ON_COMMAND(ID_32810, &CImageCheView::OnBiYunSuan)
	ON_COMMAND(ID_32812, &CImageCheView::OnInterEdge)
	ON_COMMAND(ID_32811, &CImageCheView::OnOutEdge)
	ON_COMMAND(ID_32813, &CImageCheView::OnContour)
	ON_COMMAND(ID_32814, &CImageCheView::OnGradSharp)
	ON_COMMAND(ID_32815, &CImageCheView::OnLapTemplateSharp)
	ON_COMMAND(ID_32817, &CImageCheView::OnBianYuanJianCe)
	ON_COMMAND(ID_32821, &CImageCheView::OnMosaic)
	ON_COMMAND(ID_32790, &CImageCheView::OnSuoFang)
	ON_COMMAND(ID_32785, &CImageCheView::OnRGBHist)
	ON_COMMAND(ID_APP_ABOUT, &CImageCheView::OnAppAbout)
	ON_COMMAND(ID_32772, &CImageCheView::OnFuXiang)
	ON_COMMAND(ID_32788, &CImageCheView::OnZhuangzhi)
	ON_COMMAND(ID_32822, &CImageCheView::OnshuiPingJingXiang)
	ON_COMMAND(ID_32823, &CImageCheView::OnChuiZhiJingXiang)
	ON_COMMAND(ID_32784, &CImageCheView::Onhuidu)
	ON_COMMAND(ID_32786, &CImageCheView::OnZFTJunHeng)
	ON_COMMAND(ID_32778, &CImageCheView::OnDuiShuStrech)
	ON_COMMAND(ID_32779, &CImageCheView::OnZhishu)
	ON_COMMAND(ID_32827, &CImageCheView::OnBianJie)
	ON_COMMAND(ID_32828, &CImageCheView::OnZhafangtu)
	ON_COMMAND(ID_TIAOSHI_DDFF, &CImageCheView::OnTiaoshiDdff)
	ON_COMMAND(ID_32838, &CImageCheView::OnFFT)
	ON_COMMAND(ID_32839, &CImageCheView::OnIFFT)
	ON_COMMAND(ID_32840, &CImageCheView::OnDCT)
	ON_COMMAND(ID_32841, &CImageCheView::OnIDCT)
	ON_COMMAND(zhifangtuchuli, &CImageCheView::Onzhifangtuchuli)
	ON_COMMAND(ID_32847, &CImageCheView::OnRobertsOperator)
	ON_COMMAND(ID_32848, &CImageCheView::OnPrewittOperator)
	ON_COMMAND(ID_32849, &CImageCheView::OnSobelOperator)
	ON_COMMAND(ID_32852, &CImageCheView::OnKaiqiFillHoles)
	ON_COMMAND(ID_32853, &CImageCheView::OnGuanbiFillHoles)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_32854, &CImageCheView::OnSuanShu)
	ON_COMMAND(ID_32855, &CImageCheView::OnJiHe)
END_MESSAGE_MAP()
void CImageCheView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeToal(40000,30000);
	CSize sizePage(sizeToal.cx/4,sizeToal.cy/3);
	CSize sizeLine(sizeToal.cx/100,sizeToal.cy/100);
	SetScrollSizes(MM_HIMETRIC,sizeToal,sizePage,sizeLine);
}
void CImageCheView::OnKeyDown(UINT nChar, UINT nRepCnt ,UINT nFlags)
{
	switch (nChar)
	{
		case VK_UP:
			OnVScroll(SB_LINEUP,0,NULL);
			break;
		case VK_DOWN:
			OnVScroll(SB_LINEDOWN, 0, NULL);
			break;
		case VK_LEFT:
			OnVScroll(SB_LINELEFT, 0, NULL);
			break;
		case VK_RIGHT:
			OnVScroll(SB_LINERIGHT, 0, NULL);
			break;
		case VK_PRIOR:
			OnVScroll(SB_PAGEUP, 0, NULL);
			break;
		case VK_NEXT:
			OnVScroll(SB_PAGEDOWN, 0, NULL);
			break;
		case VK_HOME:
			OnVScroll(SB_TOP, 0, NULL);
			OnHScroll(SB_LEFT, 0, NULL);
			break;
		case VK_END:
			OnVScroll(SB_BOTTOM, 0, NULL);
			OnHScroll(SB_RIGHT, 0, NULL);
			break;
		default:
			break;
	}
	CScrollView::OnKeyDown(nChar,nRepCnt,nFlags);
}
/*
void CImageCheView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CRect rectDevice = m_rect;
	dc.LPtoDP(rectDevice);
	InvalidateRect(rectDevice);
	CScrollView::OnLButtonDown(nFlags,point);
}*/
CImageCheView::CImageCheView()
{
	m_rect = CRect(0,0,1024*3,-1024*3);
}

CImageCheView::~CImageCheView()
{
}

BOOL CImageCheView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

void CImageCheView::OnDraw(CDC* pDC)
{
	//pDC->Ellipse(m_rect);
	BeginWaitCursor();// 显示等待光标
	CImageCheDoc* pDoc = GetDocument();	// 获取文档和对应的DIB
	ASSERT_VALID(pDoc);
	HDIB hDIB = pDoc->GetHDIB();
	if (hDIB != NULL)// 如果DIB非空，就进行处理
	{
	LPSTR lpDIB = (LPSTR)::GlobalLock((HGLOBAL)hDIB);// 锁定图像内存区
	int cxDIB = (int)DIBWidth(lpDIB);// 获取DIB尺寸
	int cyDIB = (int)DIBHeight(lpDIB);
	::GlobalUnlock((HGLOBAL)hDIB);// 解锁图像内存区
	CRect rcDIB;
	rcDIB.top = rcDIB.left = 0;
	rcDIB.right = cxDIB;
	rcDIB.bottom = cyDIB;
	CRect rcDest;
	if (pDC->IsPrinting())// 如果要打印，计算输出图像的位置和大小，以便符合页面
	{
	int cxPage = pDC->GetDeviceCaps(HORZRES);// 获取打印页面的水平宽度(象素)
	int cyPage = pDC->GetDeviceCaps(VERTRES);// 获取打印页面的垂直高度(象素)
	int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);// 获取打印机每英寸象素数
	int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

	// 计算打印图像大小（缩放，根据页面宽度调整图像大小）
	rcDest.top = rcDest.left = 0;
	rcDest.bottom = (int)(((double)cyDIB * cxPage * cyInch)
	/ ((double)cxDIB * cxInch));
	rcDest.right = cxPage;

	// 计算打印图像位置（垂直居中）
	int temp = cyPage - (rcDest.bottom - rcDest.top);
	rcDest.bottom += temp / 2;
	rcDest.top += temp / 2;
	}
	else//不打印则正常处理
	{
	rcDest = rcDIB;
	}

	PaintDIB(pDC->m_hDC, &rcDest, pDoc->GetHDIB(), &rcDIB);// 窗口绘图函数 // 输出DIB
	}
	EndWaitCursor();// 恢复正常光标
}

void CImageCheView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageCheView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CImageCheView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CImageCheView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CImageCheView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageCheView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

#ifdef _DEBUG
void CImageCheView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageCheView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageCheDoc* CImageCheView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageCheDoc)));
	return (CImageCheDoc*)m_pDocument;
}
#endif

/*
窗口消息映射程序
*/
/*************************************************************************
*
* 函数名称：
*	OnUpDownMove()
* 说明:
*	图像的上下平移。
************************************************************************/
void CImageCheView::OnUpDownMove()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("行");

	}
	else
		MessageBox(_T("无法获得地图树控件句柄!"));
	if (UPWOWN_Hang.MyGetData() != IDOK)
	{
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "上下平移处理...", TRUE);
	HDIB hNewDIB = (HDIB)PY_GeoProcess(lpDIB, (unsigned int)UPWOWN_Hang.Num);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "上下平移处理完毕。", TRUE);
	}
	else
	{
		MessageBox("上下平移处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnXunHuanPingYi()
* 说明:
*	图像的上下循环平移。
************************************************************************/
void CImageCheView::OnXunHuanPingYi()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("行");

	}
	else
		MessageBox(_T("无法获得地图树控件句柄!"));
	if (UPWOWN_Hang.MyGetData() != IDOK)
	{
		return;
	}
	if (UPWOWN_Hang.Num<=0)
	{
		if (UPWOWN_Hang.Num == 0)
		{
			return;
		}
		else
		{
			UPWOWN_Hang.Num = -UPWOWN_Hang.Num;
		}
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "上下循环平移处理...", TRUE);
	HDIB hNewDIB = (HDIB)XHPY_GeoProcess(lpDIB, (unsigned int)UPWOWN_Hang.Num);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "上下循环平移处理完毕。", TRUE);
	}
	else
	{
		MessageBox("上下循环平移处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*****************************************
* 函数名称：
*	:OnXuanZhuan()
* 说明:
*	图像的旋转。
******************************************/
void CImageCheView::OnXuanZhuan()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("度");

	}
	else
	{
		MessageBox(_T("无法获得地图树控件句柄!"));
		return;
	}
	if (UPWOWN_Hang.MyGetData() != IDOK)
	{
		return;
	}

	if (UPWOWN_Hang.Num == 0)
	{
		return;
	}

	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "旋转...", TRUE);
	HDIB hNewDIB = (HDIB)XZ_GeoProcess(lpDIB, UPWOWN_Hang.Num);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "旋转完毕。", TRUE);
	}
	else
	{
		MessageBox("旋转失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*****************************************
* 函数名称：
*	:OnLinYuJunZhi()
* 说明:
*	图像的邻域均值滤波。
******************************************/
void CImageCheView::OnLinYuJunZhi()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	Inter_Num LinYuSelect;
	if (LinYuSelect.GetSafeHwnd())
	{
		LinYuSelect.LinYu.ShowWindow(SW_SHOW);
		LinYuSelect.Radio5.ShowWindow(SW_SHOW);
		LinYuSelect.Radio9.ShowWindow(SW_SHOW);
	}
	else
	{
		MessageBox(_T("无法获得地图树控件句柄!"));
		return;
	}
	if (LinYuSelect.MyGetData() != IDOK)
	{
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "邻域均值滤波处理...", TRUE);
	HDIB hNewDIB = (HDIB)SSJZLBtogramProcess(lpDIB, LinYuSelect.select);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "邻域均值滤波处理完毕。", TRUE);
	}
	else
	{
		MessageBox("邻域均值滤波处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*****************************************
* 函数名称：
*	OnSuanShu()
* 说明:
*	图像的算术均值滤波。
******************************************/
void CImageCheView::OnSuanShu()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "算术处理...", TRUE);
	HDIB hNewDIB = (HDIB)SSJZtogramProcess(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "算术处理完毕。", TRUE);
	}
	else
	{
		MessageBox("算术处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*****************************************
* 函数名称：
*	OnJiHe
* 说明:
*	图像的几何均值滤波。
******************************************/
void CImageCheView::OnJiHe()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "几何处理...", TRUE);
	HDIB hNewDIB = (HDIB)JHJZtogramProcess(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "几何处理完毕。", TRUE);
	}
	else
	{
		MessageBox("几何处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*****************************************
* 函数名称：
*	:OnLinYuJunZhi()
* 说明:
*	图像的邻域均值滤波。
******************************************/
void CImageCheView::OnXieBo()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "谐波处理...", TRUE);
	HDIB hNewDIB = (HDIB)XBJZtogramProcess(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "谐波处理完毕。", TRUE);
	}
	else
	{
		MessageBox("谐波000处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnUpDownMove()
* 说明:
*	图像的逆谐波处理。
************************************************************************/
void CImageCheView::OnNiXieBo()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针0
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}

	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("阶数");

	}
	else
	{
		MessageBox(_T("无法获得地图树控件句柄!"));
		return;
	}
	if (UPWOWN_Hang.MyGetData() != IDOK)
	{
		return;
	}
	if (UPWOWN_Hang.Num == 0)
	{
		return;
	}

	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "逆谐波处理...", TRUE);
	HDIB hNewDIB= (HDIB)NXBJZtogramProcess( lpDIB, UPWOWN_Hang.Num);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "逆谐波处理完毕。", TRUE);
	}
	else
	{
		MessageBox("逆谐波处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnZhongZhiLvBo()
* 说明:
*	图像的中值滤波。
************************************************************************/
void CImageCheView::OnZhongZhiLvBo()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "中值滤波处理...", TRUE);
	HDIB hNewDIB = (HDIB)ZhognzhitogramProcess(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "中值滤波处理完毕。", TRUE);
	}
	else
	{
		MessageBox("中值滤波处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnYuZhi()
* 说明:
*	图像的阈值处理。
************************************************************************/
void CImageCheView::OnYuZhi()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("阈值");

	}
	else
	{
		MessageBox(_T("无法获得地图树控件句柄!"));
		return;
	}
	if (UPWOWN_Hang.MyGetData() != IDOK)
	{
		return;
	}
	if (UPWOWN_Hang.Num < 0)
	{
		UPWOWN_Hang.Num = 0;
		//return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "阈值处理处理...", TRUE);
	HDIB hNewDIB = (HDIB)YuzhitogramProcess(lpDIB, (int)UPWOWN_Hang.Num);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "阈值处理处理完毕。", TRUE);
	}
	else
	{
		MessageBox("阈值处理处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnXX()
* 说明:
*	图像的线性处理。
************************************************************************/
void CImageCheView::OnXX()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	Inter_Num k_b;
	if (k_b.GetSafeHwnd())
	{
	
		k_b.Inter_Num2.ShowWindow(SW_SHOW);
		k_b.Static2.ShowWindow(SW_SHOW);
		k_b.Static2.SetWindowText("斜率");
		k_b.CEdit_Num.ShowWindow(SW_SHOW);
		k_b.CStatic_Num.ShowWindow(SW_SHOW);
		k_b.CStatic_Num.SetWindowText("截距");
	}
	else
	{
		MessageBox(_T("无法获得地图树控件句柄!"));
		return;
	}
	if (k_b.MyGetData() != IDOK)
	{
		return;
	}
	if (k_b.Num == 0)
	{
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "线性处理处理...", TRUE);
	HDIB hNewDIB = (HDIB)XXtogramProcess(lpDIB, k_b.Inter_num2, k_b.Num);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "线性处理处理完毕。", TRUE);
	}
	else
	{
		MessageBox("线性处理处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*************************************************************************
*
* 函数名称：
*	OnPengZhang()
* 说明:
*	图像的膨胀。
************************************************************************/

void CImageCheView::OnPengZhang()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "膨胀处理...", TRUE);
	HDIB hNewDIB = (HDIB)KYStogramProcess(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "膨胀处理完毕。", TRUE);
	}
	else
	{
		MessageBox("膨胀处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*************************************************************************
*
* 函数名称：
*	OnFuShi()
* 说明:
*	图像的腐蚀。
************************************************************************/
void CImageCheView::OnFuShi()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "腐蚀处理...", TRUE);
	HDIB hNewDIB = (HDIB)BasicErosionForBinary(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "腐蚀处理完毕。", TRUE);
	}
	else
	{
		MessageBox("腐蚀处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnKaiYunSuan()
* 说明:
*	图像的开运算。
************************************************************************/

void CImageCheView::OnKaiYunSuan()
{

	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "开运算处理...", TRUE);
	HDIB hNewDIB = (HDIB)BinaryOpen(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "开运算处理完毕。", TRUE);
	}
	else
	{
		MessageBox("开运算处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*************************************************************************
*
* 函数名称：
*	OnBiYunSuan()
* 说明:
*	图像的闭运算。
************************************************************************/
void CImageCheView::OnBiYunSuan()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "闭运算处理...", TRUE);
	HDIB hNewDIB = (HDIB)BinaryClose(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "闭运算处理完毕。", TRUE);
	}
	else
	{
		MessageBox("闭运算处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	
* 说明:
*	图像的种子填充。
************************************************************************/
int fillholes_flag;
void CImageCheView::OnKaiqiFillHoles()
{
	fillholes_flag = 1;
}
void CImageCheView::OnGuanbiFillHoles()
{
	fillholes_flag = 0;
}
/*************************************************************************
*
* 函数名称：OnLButtonDown(UINT nFlags, CPoint point)
*
* 说明:
*	  种子填充核心函数 鼠标左键点击函数
************************************************************************/
void CImageCheView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (fillholes_flag)
	{
		CRect  ab;
		GetWindowRect(&ab);
		CView::OnLButtonDown(nFlags, point);
		GetCursorPos(&point);
		point.x = point.x - ab.left;
		point.y = point.y - ab.top;

		if (point.x < 0)point.x = 0;
		if (point.y < 0)point.y = 0;

		CImageCheDoc* pDoc = GetDocument();// 获取文档
		LPSTR lpDIB;// 指向DIB的指针
		LPSTR lpDIBBits;// 指向DIB象素指针
		lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
		lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
		if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
		{
			MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
			::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
			return;
		}
		BeginWaitCursor();
		CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		CStatusBar *pStatus = &pFrame->m_wndStatusBar;
		pStatus->SetPaneText(1, "种子填充处理...", TRUE);
		HDIB hNewDIB = (HDIB)FillHoles(lpDIB, point);
		if (hNewDIB != NULL)
		{
			CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
			if (pDocTemplate == NULL)
				return;
			CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
			if (pDoc2 == NULL)
				return;
			pDocTemplate->SetDefaultTitle(pDoc2);
			pDoc2->ReplaceHDIB(hNewDIB);
			pDoc2->InitDIBData();
			pDoc2->SetModifiedFlag(TRUE);

			CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
			if (NewPFrame == NULL)
				return;
			pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
			pStatus->SetPaneText(1, "种子填充处理完毕。", TRUE);
		}
		else
		{
			MessageBox("种子填充处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
			pStatus->SetPaneText(1, "", TRUE);
		}
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		EndWaitCursor();
	}
}

/*************************************************************************
*
* 函数名称：
*	OnInterEdge()
* 说明:
*	图像的边界处理。
************************************************************************/
void CImageCheView::OnInterEdge()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "边界处理...", TRUE);
	HDIB hNewDIB = (HDIB)BinaryInterEdge(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "边界处理完毕。", TRUE);
	}
	else
	{
		MessageBox("边界处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnOutEdge()
* 说明:
*	图像的边界。
************************************************************************/
void CImageCheView::OnOutEdge()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "边界处理...", TRUE);
	HDIB hNewDIB = (HDIB)BinaryOutEdge(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "边界处理完毕。", TRUE);
	}
	else
	{
		MessageBox("边界处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnContour()
* 说明:
*	图像的边界处理。
************************************************************************/
void CImageCheView::OnContour()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "边界处理...", TRUE);
	HDIB hNewDIB = (HDIB)BinaryContour(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "边界处理完毕。", TRUE);
	}
	else
	{
		MessageBox("边界处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnGradSharp()
* 说明:
*	图像的梯度锐化。
************************************************************************/
void CImageCheView::OnGradSharp()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("阈值");

	}
	else
	{
		MessageBox(_T("无法获得地图树控件句柄!"));
		return;
	}
	if (UPWOWN_Hang.MyGetData() != IDOK)
	{
		return;
	}
	if (UPWOWN_Hang.Num == 0)
	{
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "几何处理...", TRUE);
	HDIB hNewDIB = (HDIB)GradSharp(lpDIB, UPWOWN_Hang.Num);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "几何处理完毕。", TRUE);
	}
	else
	{
		MessageBox("几何处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnLapTemplateSharp()
* 说明:
*	图像的拉普拉斯锐化。
************************************************************************/
void CImageCheView::OnLapTemplateSharp()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("系数");

	}
	else
	{
		MessageBox(_T("无法获得地图树控件句柄!"));
		return;
	}
	if (UPWOWN_Hang.MyGetData() != IDOK)
	{
		return;
	}
	if (UPWOWN_Hang.Num == 0)
	{
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "拉普拉斯锐化处理...", TRUE);
	HDIB hNewDIB = (HDIB)LapTemplateSharp(lpDIB, UPWOWN_Hang.Num);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "拉普拉斯锐化处理。", TRUE);
	}
	else
	{
		MessageBox("拉普拉斯锐化处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*************************************************************************
*
* 函数名称：
*	OnRobertsOperator()
* 说明:
*	Roberts算子
************************************************************************/
void CImageCheView::OnRobertsOperator()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "Roberts算子处理...", TRUE);
	HDIB hNewDIB = (HDIB)RobertsTemplateSharp(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "Roberts算子处理。", TRUE);
	}
	else
	{
		MessageBox("Roberts算子处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnPrewittOperator()
* 说明:
*	Prewitt算子
************************************************************************/
void CImageCheView::OnPrewittOperator()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "Prewitt算子处理...", TRUE);
	HDIB hNewDIB = (HDIB)PrewittTemplateSharp(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "Prewitt算子处理。", TRUE);
	}
	else
	{
		MessageBox("Prewitt算子处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*************************************************************************
*
* 函数名称：
*	OnSobelOperator()
* 说明:
*	Sobel算子
************************************************************************/
void CImageCheView::OnSobelOperator()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "Sobel算子处理...", TRUE);
	HDIB hNewDIB = (HDIB)SobelTemplateSharp(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "Sobel算子处理。", TRUE);
	}
	else
	{
		MessageBox("Sobel算子处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*************************************************************************
* 函数名称：
*	OnBianYuanJianCe()
* 说明:
*	图像的边界检测。
************************************************************************/
void CImageCheView::OnBianYuanJianCe()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("系数");

	}
	else
	{
		MessageBox(_T("无法获得地图树控件句柄!"));
		return;
	}
	if (UPWOWN_Hang.MyGetData() != IDOK)
	{
		return;
	}
	if (UPWOWN_Hang.Num == 0)
	{
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "边界检测...", TRUE);
	HDIB hNewDIB = (HDIB)Prewitt(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "边缘检测完毕。", TRUE);
	}
	else
	{
		MessageBox("边缘检测失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnMosaic()
* 说明:
*	图像的马赛克处理。
************************************************************************/

void CImageCheView::OnMosaic()
{
	CImageCheDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;// 指向DIB的指针
	LPSTR lpDIBBits;// 指向DIB象素指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIB);// 找到DIB图像象素起始位置
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// 判断是否是256色或者24位色位图
	{
		MessageBox("只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);// 提示用户
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// 解除锁定
		return;
	}
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("大小");

	}
	else
	{
		MessageBox(_T("无法获得地图树控件句柄!"));
		return;
	}
	if (UPWOWN_Hang.MyGetData() != IDOK)
	{
		MessageBox(_T("数据输入失败"));
		return;
	}
	if (UPWOWN_Hang.Num <0)
	{
		MessageBox(_T("请输入一个大于0的整数"));
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "马赛克处理...", TRUE);
	HDIB hNewDIB = (HDIB)MosaictogramProcess(lpDIB,(int) UPWOWN_Hang.Num);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "马赛克处理完毕。", TRUE);
	}
	else
	{
		MessageBox("马赛克处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnSuoFang()
* 说明:
*	图像的腐蚀。
************************************************************************/
void CImageCheView::OnSuoFang()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "腐蚀处理...", TRUE);
	Inter_Num Num;
	if (Num.GetSafeHwnd())
	{
		Num.CEdit_Num.ShowWindow(SW_SHOW);
		Num.CStatic_Num.ShowWindow(SW_SHOW);
		Num.CStatic_Num.SetWindowText("横向缩放倍数");

		Num.Inter_Num2.ShowWindow(SW_SHOW);
		Num.Static2.ShowWindow(SW_SHOW);
		Num.Static2.SetWindowText("纵向缩放倍数");
		

	}
	else
	{
		MessageBox(_T("无法获得地图树控件句柄!"));
		return;
	}
	if (Num.MyGetData() != IDOK)
	{
		return;
	}
	if ((Num.Num <=0)||(Num.Inter_num2 <=0))
	{
		MessageBox("请输入大于0的值", "系统提示", MB_ICONINFORMATION | MB_OK);
		return;
	}
	HDIB hNewDIB= (HDIB)ZoomDblLinear(lpDIB, Num.Num, Num.Inter_num2);
	if (hNewDIB != NULL)
	{
		/*
	    在新的窗口显示处理过的图像
		*/
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame=pDocTemplate->CreateNewFrame(pDoc2,NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame,pDoc,true);
		//pDoc->ReplaceHDIB(hNewDIB);
		// 更新DIB图像大小和调色板
		//pDoc->InitDIBData();
		//pDoc->SetModifiedFlag(TRUE);
		//pDoc->UpdateAllViews(NULL);
		pStatus->SetPaneText(1, "腐蚀处理完毕。", TRUE);
	}
	else
	{
		MessageBox("腐蚀处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
* 函数名称：
*	OnRGBHist()
* 说明:
*	图像的直方图处理。
************************************************************************/
void CImageCheView::OnRGBHist()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	BYTE bBitCount;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	bBitCount = DIBBitCount(lpDIB);
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	  pStatus->SetPaneText(1, "直方图处理...", TRUE);
	  double JunZhi = 0, FangCha = 0;
	  Hist_Select select;
	
	if (select.GetSafeHwnd())
	{
		if (bBitCount == 8)
		{
			select.Channal_B.ShowWindow(SW_HIDE);
			select.Channal_G.ShowWindow(SW_HIDE);
			select.Channal_R.ShowWindow(SW_HIDE);
			select.Hunhe.ShowWindow(SW_HIDE);
			//select.HuiDu.ShowWindow(SW_SHOW);
		}
		else
		{
			select.HuiDu.ShowWindow(SW_HIDE);
			//select.HuiDu.ShowWindow(SW_SHOW);
		}
	}
	else
	{
		MessageBox(_T("无法获得地图树控件句柄!"));
		return;
	}
	if (select.MyGetData() != IDOK)
	{
		return;
	}
	if (select.Red)
		HistProcess_Red(lpDIB, &JunZhi, &FangCha);
	if (select.Blue)
		HistProcess_Blue(lpDIB, &JunZhi, &FangCha);
	if (select.Green)
		HistProcess_Green(lpDIB, &JunZhi, &FangCha);
	if (select.hunhe)
		HistProcess_RGB(lpDIB, &JunZhi, &FangCha);
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
#include "About.h"
void CImageCheView::OnAppAbout()
{
	About about;
	about.DoModal();
}
/*************************************************************************
*
* 函数名称：
*	OnFuXiang()
* 说明:
*	图像的负相。
************************************************************************/
void CImageCheView::OnFuXiang()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "负相处理...", TRUE);
	HDIB hNewDIB = (HDIB)fuxiangProcess(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "负相处理完毕。", TRUE);
	}
	else
	{
		MessageBox("负相处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnZhuangzhi()
* 说明:
*	图像的转置。
************************************************************************/
void CImageCheView::OnZhuangzhi()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "转置处理...", TRUE);
	HDIB hNewDIB = (HDIB)zhuangzhiProcess(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "转置处理完毕。", TRUE);
	}
	else
	{
		MessageBox("转置处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnshuiPingJingXiang()
* 说明:
*	图像的水平镜像。
************************************************************************/
void CImageCheView::OnshuiPingJingXiang()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "水平镜像处理...", TRUE);
	HDIB hNewDIB = (HDIB)shuipingjingxiangProcess(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "水平镜像处理完毕。", TRUE);
	}
	else
	{
		MessageBox("水平镜像处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnChuiZhiJingXiang()
* 说明:
*	图像的垂直镜像。
************************************************************************/
void CImageCheView::OnChuiZhiJingXiang()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "垂直镜像处理...", TRUE);
	HDIB hNewDIB = (HDIB)chuizhijingxiangProcess(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "垂直镜像处理完毕。", TRUE);
	}
	else
	{
		MessageBox("垂直镜像处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	Onhuidu()
* 说明:
*	图像的灰度处理。
************************************************************************/
void CImageCheView::Onhuidu()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	BYTE bBitCount;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	bBitCount = DIBBitCount(lpDIB);
	if (bBitCount != 8)
	{
		MessageBox("该图不是灰度图！", "系统提示", MB_ICONINFORMATION | MB_OK);
		return;
	}
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "灰度均值处理...", TRUE);
	double JunZhi = 0, FangCha = 0;
	HistProcess_Huidu(lpDIB, &JunZhi, &FangCha);
	HDIB hNewDIB = (HDIB)HistProcess(lpDIB, JunZhi);

	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);
		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "灰度处理完毕。", TRUE);
	}
	else
	{
		MessageBox("灰度处理完毕！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnZFTJunHeng()
* 说明:
*	图像的直方图均衡。
************************************************************************/
void CImageCheView::OnZFTJunHeng()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	BYTE bBitCount;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	bBitCount = DIBBitCount(lpDIB);
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "直方图均衡处理...", TRUE);
	HDIB hNewDIB = (HDIB)HistJunHengProcess(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "直方图均衡处理完毕。", TRUE);
	}
	else
	{
		MessageBox("直方图均衡处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnDuiShuStrech()
* 说明:
*	图像的对数拉伸。
************************************************************************/
void CImageCheView::OnDuiShuStrech()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	BYTE bBitCount;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	bBitCount = DIBBitCount(lpDIB);
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	
	Inter_Num *Num=new Inter_Num();
	if (Num->GetSafeHwnd())
	{
	Num->CEdit_Num.ShowWindow(SW_SHOW);
	Num->CStatic_Num.ShowWindow(SW_SHOW);
	Num->CStatic_Num.SetWindowText("b");

	Num->Inter_Num2.ShowWindow(SW_SHOW);
	Num->Static2.ShowWindow(SW_SHOW);
	Num->Static2.SetWindowText("a");

	Num->CEdit_3.ShowWindow(SW_SHOW);
	Num->CStatic_3.ShowWindow(SW_SHOW);
	Num->CStatic_3.SetWindowText("c");
	}
	else
	{
	MessageBox(_T("无法获得地图树控件句柄!"));
	return;
	}
	if (Num->MyGetData() != IDOK)
	{
	  return;
	}
	if ((Num->Num ==0)||(Num->CEdit_num3 == 1))
	{
	MessageBox("请输入b不等于0，c不等于1的值", "系统提示", MB_ICONINFORMATION | MB_OK);
	return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "对数拉伸处理...", TRUE);
	HDIB hNewDIB = (HDIB)DuiShuStrechProcess( lpDIB, Num->Inter_num2, Num->Num, Num->CEdit_num3);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "对数拉伸处理完毕。", TRUE);
	}
	else
	{
		MessageBox("对数拉伸处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnZhishu()
* 说明:
*	图像的指数拉伸。
************************************************************************/
void CImageCheView::OnZhishu()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	BYTE bBitCount;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	bBitCount = DIBBitCount(lpDIB);
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}

	Inter_Num *Num = new Inter_Num();
	if (Num->GetSafeHwnd())
	{
		Num->CEdit_Num.ShowWindow(SW_SHOW);
		Num->CStatic_Num.ShowWindow(SW_SHOW);
		Num->CStatic_Num.SetWindowText("b");

		Num->Inter_Num2.ShowWindow(SW_SHOW);
		Num->Static2.ShowWindow(SW_SHOW);
		Num->Static2.SetWindowText("a");

		Num->CEdit_3.ShowWindow(SW_SHOW);
		Num->CStatic_3.ShowWindow(SW_SHOW);
		Num->CStatic_3.SetWindowText("c");
	}
	else
	{
		MessageBox(_T("无法获得地图树控件句柄!"));
		return;
	}
	if (Num->MyGetData() != IDOK)
	{
		return;
	}
	if ((Num->Num <0) || (Num->CEdit_num3 <0))
	{
		MessageBox("请输入b大于于0，c大于0的值", "系统提示", MB_ICONINFORMATION | MB_OK);
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "指数拉伸处理...", TRUE);
	HDIB hNewDIB = (HDIB)ZhiShuStrechProcess(lpDIB, Num->Inter_num2, Num->Num, Num->CEdit_num3);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "指数拉伸处理完毕。", TRUE);
	}
	else
	{
		MessageBox("指数拉伸处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*************************************************************************
*
* 函数名称：
*	OnBianJie()
* 说明:
*	图像的边界处理。
************************************************************************/
void CImageCheView::OnBianJie()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	BYTE bBitCount;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	bBitCount = DIBBitCount(lpDIB);
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "边界处理...", TRUE);
	HDIB hNewDIB = (HDIB)BianJietogramProcess(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "边界处理完毕。", TRUE);
	}
	else
	{
		MessageBox("边界处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	OnZhafangtu()
* 说明:
*	图像的直方图。
************************************************************************/
void CImageCheView::OnZhafangtu()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	BYTE bBitCount;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	bBitCount = DIBBitCount(lpDIB);
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "直方图处理...", TRUE);
	HDIB hNewDIB = (HDIB)HistAvetogramProcess(lpDIB);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "直方图处理完毕。", TRUE);
	}
	else
	{
		MessageBox("直方图处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* 函数名称：
*	Onzhifangtuchuli()
* 说明:
*	直方图处理
************************************************************************/
#include "DialogHist.h"
void CImageCheView::Onzhifangtuchuli()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	LPSTR lpDIBBits;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	lpDIBBits = FindDIBBits(lpDIB);
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的直方图处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	DialogHist dlgPara;
	if (dlgPara.DoModal() != IDOK)
	{
		return;
	}
	int nThre = dlgPara.Thre;
	double dK = dlgPara.K;
	int nB = dlgPara.B;
	int nMode = dlgPara.Mode;
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "直方图处理...", TRUE);
	BOOL blReturnV;
	switch (nMode)
	{
	case 0: blReturnV = HistFazhiProcess(lpDIBBits, DIBBitCount(lpDIB), DIBWidth(lpDIB), DIBHeight(lpDIB), nThre); break;
	case 1:blReturnV = HistXxingProcess(lpDIBBits, DIBBitCount(lpDIB), DIBWidth(lpDIB), DIBHeight(lpDIB), dK, nB); break;
	default:break;

	}
	if (blReturnV)
	{
		pDoc->SetModifiedFlag(TRUE);
		pDoc->UpdateAllViews(NULL);
		pStatus->SetPaneText(1, "直方图处理完毕。", TRUE);
	}
	else
	{
		MessageBox("直方图处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}


void CImageCheView::OnTiaoshiDdff()
{
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("大小");

	}
	else
	{
		MessageBox(_T("无法获得地图树控件句柄!"));
		return;
	}
	if (UPWOWN_Hang.MyGetData() != IDOK)
	{
		MessageBox(_T("数据输入失败"));
		return;
	}
	if (UPWOWN_Hang.Num <0)
	{
		MessageBox(_T("请输入一个大于0的整数"));
		return;
	}
	int len = (int)UPWOWN_Hang.Num;
	ComplexNumber *Buf = new ComplexNumber[len];
	int i = 0;
	for (i = 0;i < len;i++)
	{
		Buf[i].imag = i;
		Buf[i].real = i;
	}
	FFT1D2(Buf,len);
	for (i = 0;i < len;i++)
	{
		//cout << Buf[i].imag << " " << Buf[i].real<< endl;
		Buf[i].imag ;
		Buf[i].real;
	}
}

void CImageCheView::OnFFT()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	BYTE bBitCount;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	bBitCount = DIBBitCount(lpDIB);
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "傅里叶变换处理...", TRUE);
	HDIB hNewDIB = (HDIB)Fourier(lpDIB, pDoc);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc2, true);
		pStatus->SetPaneText(1, "傅里叶变换处理完毕。", TRUE);
	}
	else
	{
		MessageBox("傅里叶变换处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}


void CImageCheView::OnIFFT()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	BYTE bBitCount;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	bBitCount = DIBBitCount(lpDIB);
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "傅里叶逆变换处理...", TRUE);
	HDIB hNewDIB = (HDIB)IFourierEx(lpDIB, pDoc->imageFFTbuf, pDoc->imageIFFTbuf, *pDoc->NewHeight, *pDoc->NewWidth);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc, true);
		pStatus->SetPaneText(1, "傅里叶变逆换处理完毕。", TRUE);
	}
	else
	{
		MessageBox("傅里叶逆变换处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}


void CImageCheView::OnDCT()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	BYTE bBitCount;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	bBitCount = DIBBitCount(lpDIB);
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "离散余弦变换处理...", TRUE);
	HDIB hNewDIB = (HDIB)img_DCT(lpDIB, pDoc);
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc2, true);
		pStatus->SetPaneText(1, "离散余弦处理完毕。", TRUE);
	}
	else
	{
		MessageBox("离散余弦处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}


void CImageCheView::OnIDCT()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	BYTE bBitCount;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	bBitCount = DIBBitCount(lpDIB);
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("目前只支持256色或者24位色位图的几何处理！", "系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "离散余弦反变换处理...", TRUE);
	HDIB hNewDIB = (HDIB)img_IDCT(lpDIB, pDoc);                                                                  
	if (hNewDIB != NULL)
	{
		CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
		if (pDocTemplate == NULL)
			return;
		CImageCheDoc* pDoc2 = (CImageCheDoc*)pDocTemplate->CreateNewDocument();
		if (pDoc2 == NULL)
			return;
		pDocTemplate->SetDefaultTitle(pDoc2);
		pDoc2->ReplaceHDIB(hNewDIB);
		pDoc2->InitDIBData();
		pDoc2->SetModifiedFlag(TRUE);

		CFrameWnd *  NewPFrame = pDocTemplate->CreateNewFrame(pDoc2, NULL);
		if (NewPFrame == NULL)
			return;
		pDocTemplate->InitialUpdateFrame(NewPFrame, pDoc2, true);
		pStatus->SetPaneText(1, "离散余弦反变换处理完毕。", TRUE);
	}
	else
	{
		MessageBox("离散余弦反变换处理失败！", "系统提示", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}








