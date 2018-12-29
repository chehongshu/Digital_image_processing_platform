


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
	// ��׼��ӡ����
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
	BeginWaitCursor();// ��ʾ�ȴ����
	CImageCheDoc* pDoc = GetDocument();	// ��ȡ�ĵ��Ͷ�Ӧ��DIB
	ASSERT_VALID(pDoc);
	HDIB hDIB = pDoc->GetHDIB();
	if (hDIB != NULL)// ���DIB�ǿգ��ͽ��д���
	{
	LPSTR lpDIB = (LPSTR)::GlobalLock((HGLOBAL)hDIB);// ����ͼ���ڴ���
	int cxDIB = (int)DIBWidth(lpDIB);// ��ȡDIB�ߴ�
	int cyDIB = (int)DIBHeight(lpDIB);
	::GlobalUnlock((HGLOBAL)hDIB);// ����ͼ���ڴ���
	CRect rcDIB;
	rcDIB.top = rcDIB.left = 0;
	rcDIB.right = cxDIB;
	rcDIB.bottom = cyDIB;
	CRect rcDest;
	if (pDC->IsPrinting())// ���Ҫ��ӡ���������ͼ���λ�úʹ�С���Ա����ҳ��
	{
	int cxPage = pDC->GetDeviceCaps(HORZRES);// ��ȡ��ӡҳ���ˮƽ���(����)
	int cyPage = pDC->GetDeviceCaps(VERTRES);// ��ȡ��ӡҳ��Ĵ�ֱ�߶�(����)
	int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);// ��ȡ��ӡ��ÿӢ��������
	int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

	// �����ӡͼ���С�����ţ�����ҳ���ȵ���ͼ���С��
	rcDest.top = rcDest.left = 0;
	rcDest.bottom = (int)(((double)cyDIB * cxPage * cyInch)
	/ ((double)cxDIB * cxInch));
	rcDest.right = cxPage;

	// �����ӡͼ��λ�ã���ֱ���У�
	int temp = cyPage - (rcDest.bottom - rcDest.top);
	rcDest.bottom += temp / 2;
	rcDest.top += temp / 2;
	}
	else//����ӡ����������
	{
	rcDest = rcDIB;
	}

	PaintDIB(pDC->m_hDC, &rcDest, pDoc->GetHDIB(), &rcDIB);// ���ڻ�ͼ���� // ���DIB
	}
	EndWaitCursor();// �ָ��������
}

void CImageCheView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageCheView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CImageCheView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CImageCheView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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

CImageCheDoc* CImageCheView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageCheDoc)));
	return (CImageCheDoc*)m_pDocument;
}
#endif

/*
������Ϣӳ�����
*/
/*************************************************************************
*
* �������ƣ�
*	OnUpDownMove()
* ˵��:
*	ͼ�������ƽ�ơ�
************************************************************************/
void CImageCheView::OnUpDownMove()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("��");

	}
	else
		MessageBox(_T("�޷���õ�ͼ���ؼ����!"));
	if (UPWOWN_Hang.MyGetData() != IDOK)
	{
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "����ƽ�ƴ���...", TRUE);
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
		pStatus->SetPaneText(1, "����ƽ�ƴ�����ϡ�", TRUE);
	}
	else
	{
		MessageBox("����ƽ�ƴ���ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnXunHuanPingYi()
* ˵��:
*	ͼ�������ѭ��ƽ�ơ�
************************************************************************/
void CImageCheView::OnXunHuanPingYi()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("��");

	}
	else
		MessageBox(_T("�޷���õ�ͼ���ؼ����!"));
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
	pStatus->SetPaneText(1, "����ѭ��ƽ�ƴ���...", TRUE);
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
		pStatus->SetPaneText(1, "����ѭ��ƽ�ƴ�����ϡ�", TRUE);
	}
	else
	{
		MessageBox("����ѭ��ƽ�ƴ���ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*****************************************
* �������ƣ�
*	:OnXuanZhuan()
* ˵��:
*	ͼ�����ת��
******************************************/
void CImageCheView::OnXuanZhuan()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("��");

	}
	else
	{
		MessageBox(_T("�޷���õ�ͼ���ؼ����!"));
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
	pStatus->SetPaneText(1, "��ת...", TRUE);
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
		pStatus->SetPaneText(1, "��ת��ϡ�", TRUE);
	}
	else
	{
		MessageBox("��תʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*****************************************
* �������ƣ�
*	:OnLinYuJunZhi()
* ˵��:
*	ͼ��������ֵ�˲���
******************************************/
void CImageCheView::OnLinYuJunZhi()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
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
		MessageBox(_T("�޷���õ�ͼ���ؼ����!"));
		return;
	}
	if (LinYuSelect.MyGetData() != IDOK)
	{
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "�����ֵ�˲�����...", TRUE);
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
		pStatus->SetPaneText(1, "�����ֵ�˲�������ϡ�", TRUE);
	}
	else
	{
		MessageBox("�����ֵ�˲�����ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*****************************************
* �������ƣ�
*	OnSuanShu()
* ˵��:
*	ͼ���������ֵ�˲���
******************************************/
void CImageCheView::OnSuanShu()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "��������...", TRUE);
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
		pStatus->SetPaneText(1, "����������ϡ�", TRUE);
	}
	else
	{
		MessageBox("��������ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*****************************************
* �������ƣ�
*	OnJiHe
* ˵��:
*	ͼ��ļ��ξ�ֵ�˲���
******************************************/
void CImageCheView::OnJiHe()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "���δ���...", TRUE);
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
		pStatus->SetPaneText(1, "���δ�����ϡ�", TRUE);
	}
	else
	{
		MessageBox("���δ���ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*****************************************
* �������ƣ�
*	:OnLinYuJunZhi()
* ˵��:
*	ͼ��������ֵ�˲���
******************************************/
void CImageCheView::OnXieBo()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "г������...", TRUE);
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
		pStatus->SetPaneText(1, "г��������ϡ�", TRUE);
	}
	else
	{
		MessageBox("г��000����ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnUpDownMove()
* ˵��:
*	ͼ�����г������
************************************************************************/
void CImageCheView::OnNiXieBo()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��0
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}

	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("����");

	}
	else
	{
		MessageBox(_T("�޷���õ�ͼ���ؼ����!"));
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
	pStatus->SetPaneText(1, "��г������...", TRUE);
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
		pStatus->SetPaneText(1, "��г��������ϡ�", TRUE);
	}
	else
	{
		MessageBox("��г������ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnZhongZhiLvBo()
* ˵��:
*	ͼ�����ֵ�˲���
************************************************************************/
void CImageCheView::OnZhongZhiLvBo()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "��ֵ�˲�����...", TRUE);
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
		pStatus->SetPaneText(1, "��ֵ�˲�������ϡ�", TRUE);
	}
	else
	{
		MessageBox("��ֵ�˲�����ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnYuZhi()
* ˵��:
*	ͼ�����ֵ����
************************************************************************/
void CImageCheView::OnYuZhi()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("��ֵ");

	}
	else
	{
		MessageBox(_T("�޷���õ�ͼ���ؼ����!"));
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
	pStatus->SetPaneText(1, "��ֵ������...", TRUE);
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
		pStatus->SetPaneText(1, "��ֵ��������ϡ�", TRUE);
	}
	else
	{
		MessageBox("��ֵ������ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnXX()
* ˵��:
*	ͼ������Դ���
************************************************************************/
void CImageCheView::OnXX()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	Inter_Num k_b;
	if (k_b.GetSafeHwnd())
	{
	
		k_b.Inter_Num2.ShowWindow(SW_SHOW);
		k_b.Static2.ShowWindow(SW_SHOW);
		k_b.Static2.SetWindowText("б��");
		k_b.CEdit_Num.ShowWindow(SW_SHOW);
		k_b.CStatic_Num.ShowWindow(SW_SHOW);
		k_b.CStatic_Num.SetWindowText("�ؾ�");
	}
	else
	{
		MessageBox(_T("�޷���õ�ͼ���ؼ����!"));
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
	pStatus->SetPaneText(1, "���Դ�����...", TRUE);
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
		pStatus->SetPaneText(1, "���Դ�������ϡ�", TRUE);
	}
	else
	{
		MessageBox("���Դ�����ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*************************************************************************
*
* �������ƣ�
*	OnPengZhang()
* ˵��:
*	ͼ������͡�
************************************************************************/

void CImageCheView::OnPengZhang()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "���ʹ���...", TRUE);
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
		pStatus->SetPaneText(1, "���ʹ�����ϡ�", TRUE);
	}
	else
	{
		MessageBox("���ʹ���ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*************************************************************************
*
* �������ƣ�
*	OnFuShi()
* ˵��:
*	ͼ��ĸ�ʴ��
************************************************************************/
void CImageCheView::OnFuShi()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "��ʴ����...", TRUE);
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
		pStatus->SetPaneText(1, "��ʴ������ϡ�", TRUE);
	}
	else
	{
		MessageBox("��ʴ����ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnKaiYunSuan()
* ˵��:
*	ͼ��Ŀ����㡣
************************************************************************/

void CImageCheView::OnKaiYunSuan()
{

	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "�����㴦��...", TRUE);
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
		pStatus->SetPaneText(1, "�����㴦����ϡ�", TRUE);
	}
	else
	{
		MessageBox("�����㴦��ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*************************************************************************
*
* �������ƣ�
*	OnBiYunSuan()
* ˵��:
*	ͼ��ı����㡣
************************************************************************/
void CImageCheView::OnBiYunSuan()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "�����㴦��...", TRUE);
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
		pStatus->SetPaneText(1, "�����㴦����ϡ�", TRUE);
	}
	else
	{
		MessageBox("�����㴦��ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	
* ˵��:
*	ͼ���������䡣
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
* �������ƣ�OnLButtonDown(UINT nFlags, CPoint point)
*
* ˵��:
*	  ���������ĺ��� �������������
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

		CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
		LPSTR lpDIB;// ָ��DIB��ָ��
		LPSTR lpDIBBits;// ָ��DIB����ָ��
		lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
		lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
		if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
		{
			MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
			::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
			return;
		}
		BeginWaitCursor();
		CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		CStatusBar *pStatus = &pFrame->m_wndStatusBar;
		pStatus->SetPaneText(1, "������䴦��...", TRUE);
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
			pStatus->SetPaneText(1, "������䴦����ϡ�", TRUE);
		}
		else
		{
			MessageBox("������䴦��ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
			pStatus->SetPaneText(1, "", TRUE);
		}
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		EndWaitCursor();
	}
}

/*************************************************************************
*
* �������ƣ�
*	OnInterEdge()
* ˵��:
*	ͼ��ı߽紦��
************************************************************************/
void CImageCheView::OnInterEdge()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "�߽紦��...", TRUE);
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
		pStatus->SetPaneText(1, "�߽紦����ϡ�", TRUE);
	}
	else
	{
		MessageBox("�߽紦��ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnOutEdge()
* ˵��:
*	ͼ��ı߽硣
************************************************************************/
void CImageCheView::OnOutEdge()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "�߽紦��...", TRUE);
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
		pStatus->SetPaneText(1, "�߽紦����ϡ�", TRUE);
	}
	else
	{
		MessageBox("�߽紦��ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnContour()
* ˵��:
*	ͼ��ı߽紦��
************************************************************************/
void CImageCheView::OnContour()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "�߽紦��...", TRUE);
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
		pStatus->SetPaneText(1, "�߽紦����ϡ�", TRUE);
	}
	else
	{
		MessageBox("�߽紦��ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnGradSharp()
* ˵��:
*	ͼ����ݶ��񻯡�
************************************************************************/
void CImageCheView::OnGradSharp()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("��ֵ");

	}
	else
	{
		MessageBox(_T("�޷���õ�ͼ���ؼ����!"));
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
	pStatus->SetPaneText(1, "���δ���...", TRUE);
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
		pStatus->SetPaneText(1, "���δ�����ϡ�", TRUE);
	}
	else
	{
		MessageBox("���δ���ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnLapTemplateSharp()
* ˵��:
*	ͼ���������˹�񻯡�
************************************************************************/
void CImageCheView::OnLapTemplateSharp()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("ϵ��");

	}
	else
	{
		MessageBox(_T("�޷���õ�ͼ���ؼ����!"));
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
	pStatus->SetPaneText(1, "������˹�񻯴���...", TRUE);
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
		pStatus->SetPaneText(1, "������˹�񻯴���", TRUE);
	}
	else
	{
		MessageBox("������˹�񻯴���ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*************************************************************************
*
* �������ƣ�
*	OnRobertsOperator()
* ˵��:
*	Roberts����
************************************************************************/
void CImageCheView::OnRobertsOperator()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "Roberts���Ӵ���...", TRUE);
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
		pStatus->SetPaneText(1, "Roberts���Ӵ���", TRUE);
	}
	else
	{
		MessageBox("Roberts���Ӵ���ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnPrewittOperator()
* ˵��:
*	Prewitt����
************************************************************************/
void CImageCheView::OnPrewittOperator()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "Prewitt���Ӵ���...", TRUE);
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
		pStatus->SetPaneText(1, "Prewitt���Ӵ���", TRUE);
	}
	else
	{
		MessageBox("Prewitt���Ӵ���ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*************************************************************************
*
* �������ƣ�
*	OnSobelOperator()
* ˵��:
*	Sobel����
************************************************************************/
void CImageCheView::OnSobelOperator()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "Sobel���Ӵ���...", TRUE);
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
		pStatus->SetPaneText(1, "Sobel���Ӵ���", TRUE);
	}
	else
	{
		MessageBox("Sobel���Ӵ���ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*************************************************************************
* �������ƣ�
*	OnBianYuanJianCe()
* ˵��:
*	ͼ��ı߽��⡣
************************************************************************/
void CImageCheView::OnBianYuanJianCe()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("ϵ��");

	}
	else
	{
		MessageBox(_T("�޷���õ�ͼ���ؼ����!"));
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
	pStatus->SetPaneText(1, "�߽���...", TRUE);
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
		pStatus->SetPaneText(1, "��Ե�����ϡ�", TRUE);
	}
	else
	{
		MessageBox("��Ե���ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnMosaic()
* ˵��:
*	ͼ��������˴���
************************************************************************/

void CImageCheView::OnMosaic()
{
	CImageCheDoc* pDoc = GetDocument();// ��ȡ�ĵ�
	LPSTR lpDIB;// ָ��DIB��ָ��
	LPSTR lpDIBBits;// ָ��DIB����ָ��
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());// ����DIB
	lpDIBBits = FindDIBBits(lpDIB);// �ҵ�DIBͼ��������ʼλ��
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)// �ж��Ƿ���256ɫ����24λɫλͼ
	{
		MessageBox("ֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());// �������
		return;
	}
	Inter_Num UPWOWN_Hang;
	if (UPWOWN_Hang.GetSafeHwnd())
	{
		UPWOWN_Hang.CEdit_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.ShowWindow(SW_SHOW);
		UPWOWN_Hang.CStatic_Num.SetWindowText("��С");

	}
	else
	{
		MessageBox(_T("�޷���õ�ͼ���ؼ����!"));
		return;
	}
	if (UPWOWN_Hang.MyGetData() != IDOK)
	{
		MessageBox(_T("��������ʧ��"));
		return;
	}
	if (UPWOWN_Hang.Num <0)
	{
		MessageBox(_T("������һ������0������"));
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "�����˴���...", TRUE);
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
		pStatus->SetPaneText(1, "�����˴�����ϡ�", TRUE);
	}
	else
	{
		MessageBox("�����˴���ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnSuoFang()
* ˵��:
*	ͼ��ĸ�ʴ��
************************************************************************/
void CImageCheView::OnSuoFang()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "��ʴ����...", TRUE);
	Inter_Num Num;
	if (Num.GetSafeHwnd())
	{
		Num.CEdit_Num.ShowWindow(SW_SHOW);
		Num.CStatic_Num.ShowWindow(SW_SHOW);
		Num.CStatic_Num.SetWindowText("�������ű���");

		Num.Inter_Num2.ShowWindow(SW_SHOW);
		Num.Static2.ShowWindow(SW_SHOW);
		Num.Static2.SetWindowText("�������ű���");
		

	}
	else
	{
		MessageBox(_T("�޷���õ�ͼ���ؼ����!"));
		return;
	}
	if (Num.MyGetData() != IDOK)
	{
		return;
	}
	if ((Num.Num <=0)||(Num.Inter_num2 <=0))
	{
		MessageBox("���������0��ֵ", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		return;
	}
	HDIB hNewDIB= (HDIB)ZoomDblLinear(lpDIB, Num.Num, Num.Inter_num2);
	if (hNewDIB != NULL)
	{
		/*
	    ���µĴ�����ʾ�������ͼ��
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
		// ����DIBͼ���С�͵�ɫ��
		//pDoc->InitDIBData();
		//pDoc->SetModifiedFlag(TRUE);
		//pDoc->UpdateAllViews(NULL);
		pStatus->SetPaneText(1, "��ʴ������ϡ�", TRUE);
	}
	else
	{
		MessageBox("��ʴ����ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
* �������ƣ�
*	OnRGBHist()
* ˵��:
*	ͼ���ֱ��ͼ����
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
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	  pStatus->SetPaneText(1, "ֱ��ͼ����...", TRUE);
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
		MessageBox(_T("�޷���õ�ͼ���ؼ����!"));
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
* �������ƣ�
*	OnFuXiang()
* ˵��:
*	ͼ��ĸ��ࡣ
************************************************************************/
void CImageCheView::OnFuXiang()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "���ദ��...", TRUE);
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
		pStatus->SetPaneText(1, "���ദ����ϡ�", TRUE);
	}
	else
	{
		MessageBox("���ദ��ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnZhuangzhi()
* ˵��:
*	ͼ���ת�á�
************************************************************************/
void CImageCheView::OnZhuangzhi()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "ת�ô���...", TRUE);
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
		pStatus->SetPaneText(1, "ת�ô�����ϡ�", TRUE);
	}
	else
	{
		MessageBox("ת�ô���ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnshuiPingJingXiang()
* ˵��:
*	ͼ���ˮƽ����
************************************************************************/
void CImageCheView::OnshuiPingJingXiang()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "ˮƽ������...", TRUE);
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
		pStatus->SetPaneText(1, "ˮƽ��������ϡ�", TRUE);
	}
	else
	{
		MessageBox("ˮƽ������ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnChuiZhiJingXiang()
* ˵��:
*	ͼ��Ĵ�ֱ����
************************************************************************/
void CImageCheView::OnChuiZhiJingXiang()
{
	CImageCheDoc* pDoc = GetDocument();
	LPSTR lpDIB;
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHDIB());
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "��ֱ������...", TRUE);
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
		pStatus->SetPaneText(1, "��ֱ��������ϡ�", TRUE);
	}
	else
	{
		MessageBox("��ֱ������ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	Onhuidu()
* ˵��:
*	ͼ��ĻҶȴ���
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
		MessageBox("��ͼ���ǻҶ�ͼ��", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		return;
	}
	if (DIBNumColors(lpDIB) != 256 && DIBBitCount(lpDIB) != 24)
	{
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "�ҶȾ�ֵ����...", TRUE);
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
		pStatus->SetPaneText(1, "�Ҷȴ�����ϡ�", TRUE);
	}
	else
	{
		MessageBox("�Ҷȴ�����ϣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnZFTJunHeng()
* ˵��:
*	ͼ���ֱ��ͼ���⡣
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
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "ֱ��ͼ���⴦��...", TRUE);
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
		pStatus->SetPaneText(1, "ֱ��ͼ���⴦����ϡ�", TRUE);
	}
	else
	{
		MessageBox("ֱ��ͼ���⴦��ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnDuiShuStrech()
* ˵��:
*	ͼ��Ķ������졣
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
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
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
	MessageBox(_T("�޷���õ�ͼ���ؼ����!"));
	return;
	}
	if (Num->MyGetData() != IDOK)
	{
	  return;
	}
	if ((Num->Num ==0)||(Num->CEdit_num3 == 1))
	{
	MessageBox("������b������0��c������1��ֵ", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
	return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "�������촦��...", TRUE);
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
		pStatus->SetPaneText(1, "�������촦����ϡ�", TRUE);
	}
	else
	{
		MessageBox("�������촦��ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnZhishu()
* ˵��:
*	ͼ���ָ�����졣
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
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
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
		MessageBox(_T("�޷���õ�ͼ���ؼ����!"));
		return;
	}
	if (Num->MyGetData() != IDOK)
	{
		return;
	}
	if ((Num->Num <0) || (Num->CEdit_num3 <0))
	{
		MessageBox("������b������0��c����0��ֵ", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "ָ�����촦��...", TRUE);
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
		pStatus->SetPaneText(1, "ָ�����촦����ϡ�", TRUE);
	}
	else
	{
		MessageBox("ָ�����촦��ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}

/*************************************************************************
*
* �������ƣ�
*	OnBianJie()
* ˵��:
*	ͼ��ı߽紦��
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
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "�߽紦��...", TRUE);
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
		pStatus->SetPaneText(1, "�߽紦����ϡ�", TRUE);
	}
	else
	{
		MessageBox("�߽紦��ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	OnZhafangtu()
* ˵��:
*	ͼ���ֱ��ͼ��
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
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "ֱ��ͼ����...", TRUE);
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
		pStatus->SetPaneText(1, "ֱ��ͼ������ϡ�", TRUE);
	}
	else
	{
		MessageBox("ֱ��ͼ����ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}
/*************************************************************************
*
* �������ƣ�
*	Onzhifangtuchuli()
* ˵��:
*	ֱ��ͼ����
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
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ��ֱ��ͼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
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
	pStatus->SetPaneText(1, "ֱ��ͼ����...", TRUE);
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
		pStatus->SetPaneText(1, "ֱ��ͼ������ϡ�", TRUE);
	}
	else
	{
		MessageBox("ֱ��ͼ����ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
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
		UPWOWN_Hang.CStatic_Num.SetWindowText("��С");

	}
	else
	{
		MessageBox(_T("�޷���õ�ͼ���ؼ����!"));
		return;
	}
	if (UPWOWN_Hang.MyGetData() != IDOK)
	{
		MessageBox(_T("��������ʧ��"));
		return;
	}
	if (UPWOWN_Hang.Num <0)
	{
		MessageBox(_T("������һ������0������"));
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
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "����Ҷ�任����...", TRUE);
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
		pStatus->SetPaneText(1, "����Ҷ�任������ϡ�", TRUE);
	}
	else
	{
		MessageBox("����Ҷ�任����ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
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
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "����Ҷ��任����...", TRUE);
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
		pStatus->SetPaneText(1, "����Ҷ���滻������ϡ�", TRUE);
	}
	else
	{
		MessageBox("����Ҷ��任����ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
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
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "��ɢ���ұ任����...", TRUE);
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
		pStatus->SetPaneText(1, "��ɢ���Ҵ�����ϡ�", TRUE);
	}
	else
	{
		MessageBox("��ɢ���Ҵ���ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
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
		MessageBox("Ŀǰֻ֧��256ɫ����24λɫλͼ�ļ��δ���", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
		return;
	}
	BeginWaitCursor();
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetPaneText(1, "��ɢ���ҷ��任����...", TRUE);
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
		pStatus->SetPaneText(1, "��ɢ���ҷ��任������ϡ�", TRUE);
	}
	else
	{
		MessageBox("��ɢ���ҷ��任����ʧ�ܣ�", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		pStatus->SetPaneText(1, "", TRUE);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHDIB());
	EndWaitCursor();
}








