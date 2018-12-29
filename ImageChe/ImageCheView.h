
#pragma once
#define RECTWIDTH(lpRect) ((lpRect)->right-(lpRect)->left)
// 计算矩形区域的高度
#define RECTHEIGHT(lpRect) ((lpRect)->bottom-(lpRect)->top)	
class CImageCheView : public CScrollView//public CScrollView,
{
protected: 
	CImageCheView();
	DECLARE_DYNCREATE(CImageCheView)
public:
    CRect m_rect;
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnInitialUpdate();
	CImageCheDoc* GetDocument() const;
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
public:
	virtual ~CImageCheView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	public:
	afx_msg void OnUpDownMove();
	afx_msg void OnXunHuanPingYi();
	afx_msg void OnXuanZhuan();
	afx_msg void OnLinYuJunZhi();
	afx_msg void OnXieBo();
	afx_msg void OnNiXieBo();
	afx_msg void OnZhongZhiLvBo();
	afx_msg void OnYuZhi();
	afx_msg void OnXX();
	afx_msg void OnPengZhang();
	afx_msg void OnFuShi();
	afx_msg void OnKaiYunSuan();
	afx_msg void OnBiYunSuan();
	afx_msg void OnInterEdge();
	afx_msg void OnOutEdge();
	afx_msg void OnContour();
	afx_msg void OnGradSharp();
	afx_msg void OnLapTemplateSharp();
	afx_msg void OnBianYuanJianCe();
	afx_msg void OnMosaic();
	afx_msg void OnSuoFang();
	afx_msg void OnRGBHist();
	afx_msg void OnAppAbout();
	afx_msg void OnFuXiang();
	afx_msg void OnZhuangzhi();
	afx_msg void OnshuiPingJingXiang();
	afx_msg void OnChuiZhiJingXiang();
	afx_msg void Onhuidu();
	afx_msg void OnZFTJunHeng();
	afx_msg void OnDuiShuStrech();
	afx_msg void OnZhishu();
	afx_msg void OnBianJie();
	afx_msg void OnZhafangtu();
	afx_msg void OnTiaoshiDdff();
	afx_msg void OnFFT();
	afx_msg void OnIFFT();
	afx_msg void OnDCT();
	afx_msg void OnIDCT();
	afx_msg void Onzhifangtuchuli();
	afx_msg void OnRobertsOperator();
	afx_msg void OnPrewittOperator();
	afx_msg void OnSobelOperator();
	afx_msg void OnKaiqiFillHoles();
	afx_msg void OnGuanbiFillHoles();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSuanShu();
	afx_msg void OnJiHe();
};

#ifndef _DEBUG  // ImageCheView.cpp 中的调试版本
inline CImageCheDoc* CImageCheView::GetDocument() const
   { return reinterpret_cast<CImageCheDoc*>(m_pDocument); }
#endif

