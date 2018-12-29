#pragma once
#include "afxwin.h"

class Inter_Num : public CDialogEx
{
	DECLARE_DYNAMIC(Inter_Num)
public:
	Inter_Num(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Inter_Num();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_JHCL };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	public:
//编辑控件控制变量
	CEdit CEdit_Num;
	// //文本框控制变量
	CStatic CStatic_Num;
	// 编辑空的输入值
	double Num;

public:
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
	// 邻域点数选择// 邻域点数选择
//	CButton Radio_linyu;
//	int Linyu_5_9;
	CStatic LinYu;
//	int linyuselect;
	CButton Radio5;
	CButton Radio9;
//	int select;
//	int select;
	int select;
	
	CEdit Inter_Num2;
	CStatic Static2;
	double Inter_num2;
	CEdit CEdit_3;
	double CEdit_num3;
	CStatic CStatic_3;
};
