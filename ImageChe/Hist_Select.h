#pragma once
#include "afxwin.h"
class Hist_Select : public CDialogEx
{
	DECLARE_DYNAMIC(Hist_Select)

public:
	Hist_Select(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Hist_Select();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_select };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	public:
	//afx_msg void OnBnClickedCheckGreen();
//	CButton Caise;
	CButton HuiDu;
//	unsigned char RGB_3;
//	unsigned char Huidu;
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
	CButton Channal_B;
	int Blue;
	CButton Channal_G;
	int Green;
	CButton Hunhe;
	int hunhe;
	int huidu;
	int Red;
	CButton Channal_R;
};
