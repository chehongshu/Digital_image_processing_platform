#pragma once
#include "afxwin.h"


// Hist �Ի���

class Hist : public CDialogEx
{
	DECLARE_DYNAMIC(Hist)

public:
	Hist(CWnd* pParent = NULL); 
	///Hist::Hist(CWnd* pParent = NULL, int colour);// ��׼���캯��
	virtual ~Hist();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Hist };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	public:
	afx_msg void OnPaint();
	void Hist::OnPaint2();
//	CStatic Hist_Rect;
	//afx_msg void OnBnClickedOk();
	CStatic TongDao;
	CStatic JunZhi;
	CStatic FangCha;

	BOOL  IsInit = false;
	LPCDLGTEMPLATE MylpDialogTemplate;
	HGLOBAL MyhDialogTemplate;
	HINSTANCE MyhInst;

	HWND MyhWndParent;

	BOOL MybEnableParent;
	CWnd* MypMainWnd;
	BOOL MybEnableMainWnd;
	BOOL Init();
	BOOL CreateRunDlgIndirect(LPCDLGTEMPLATE lpDialogTemplate, CWnd* pParentWnd, HINSTANCE hInst);
	INT_PTR MyGetData();
	void DeteleDlg();
	afx_msg void OnEnChangeEdit1();
	unsigned int * hist=NULL;//ָ��洢ֱ��ͼ��ָ��
	CStatic Hist_Rect;
	int Colour=0;
	int Hist::RunModalLoop(DWORD dwFlags);
};
