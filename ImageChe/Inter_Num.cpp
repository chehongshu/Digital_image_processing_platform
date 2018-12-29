// Inter_Num.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageChe.h"
#include "Inter_Num.h"
#include "afxdialogex.h"
IMPLEMENT_DYNAMIC(Inter_Num, CDialogEx)
Inter_Num::Inter_Num(CWnd* pParent)
	: CDialogEx(IDD_Dlg_JHCL, pParent)
	, Num(0)
	, select(0)
	, Inter_num2(0)
	, CEdit_num3(0)
{
	this->Init();
}
Inter_Num::~Inter_Num()
{
}

void Inter_Num::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Num, CEdit_Num);
	DDX_Control(pDX, IDC_Str_Num, CStatic_Num);
	DDX_Text(pDX, IDC_Num, Num);
	DDX_Control(pDX, IDB_G123, LinYu);
	DDX_Control(pDX, IDC_RADIO1, Radio5);
	DDX_Control(pDX, IDC_RADIO2, Radio9);
	DDX_Radio(pDX, IDC_RADIO1, select);
	DDX_Control(pDX, IDC_Num2, Inter_Num2);
	DDX_Control(pDX, IDC_Static2, Static2);
	DDX_Text(pDX, IDC_Num2, Inter_num2);
	DDX_Control(pDX, IDC_EDIT_3, CEdit_3);
	DDX_Control(pDX, IDC_STATIC_3, CStatic_3);
	DDX_Text(pDX, IDC_EDIT_3, CEdit_num3);

}
BEGIN_MESSAGE_MAP(Inter_Num, CDialogEx)
	//ON_EN_CHANGE(IDC_EDIT1, &Inter_Num::OnEnChangeEdit1)
END_MESSAGE_MAP()
BOOL Inter_Num::Init()
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
		AfxHookWindowCreate(this);//CreateRunDlgIndirect(lpDialogTemplate, CWnd::FromHandle(hWndParent), hInst) �����Ի��� ���������� 
	if (!CreateRunDlgIndirect(MylpDialogTemplate, CWnd::FromHandle(MyhWndParent), MyhInst) && !m_bClosedByEndDialog)  // û�е��öԻ��� ��ʼ������ �ؼ���δ���� // �����Ի��򼰿ؼ� 
	{
		CreateRunDlgIndirect(MylpDialogTemplate, CWnd::FromHandle(MyhWndParent), AfxGetInstanceHandle());//���öԻ����ʼ������
	}
	}
		CATCH_ALL(e)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed.\n");
		//DELETE_EXCEPTION(e);
		MessageBox("�Ի���Ϊ��ʼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
		m_nModalResult = -1;
		return false;
	}
	END_CATCH_ALL
		return m_nModalResult;
}
BOOL Inter_Num::CreateRunDlgIndirect(LPCDLGTEMPLATE lpDialogTemplate, CWnd* pParentWnd, HINSTANCE hInst)
{
	IsInit = CreateDlgIndirect(lpDialogTemplate, pParentWnd, hInst);// ���öԻ����ʼ������
	return IsInit;
}
INT_PTR Inter_Num::MyGetData()
{

	if (IsInit)
	{
		if (m_nFlags & WF_CONTINUEMODAL)
		{
			DWORD dwFlags = MLF_SHOWONIDLE;
			if (GetStyle() & DS_NOIDLEMSG)
				dwFlags |= MLF_NOIDLEMSG;
			VERIFY(RunModalLoop(dwFlags) == m_nModalResult);//��ʾ�Ի��� ��ȡ���� ���ضԻ���
		}
		if (m_hWnd != NULL)
			SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW |
						 SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}
	else
	{
		MessageBox("�Ի���Ϊ��ʼ����", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);// ��ʾ�û�
	}
	if (m_nModalResult != -1)
		m_bClosedByEndDialog = FALSE;

	if (MybEnableMainWnd)
		MypMainWnd->EnableWindow(TRUE);
	if (MybEnableParent)
		::EnableWindow(MyhWndParent, TRUE);
	if (MyhWndParent != NULL && ::GetActiveWindow() == m_hWnd)
		::SetActiveWindow(MyhWndParent);
	DestroyWindow();
	PostModal();
	if (m_lpszTemplateName != NULL || m_hDialogTemplate != NULL)
		UnlockResource(MyhDialogTemplate);
	if (m_lpszTemplateName != NULL)
		FreeResource(MyhDialogTemplate);
	return m_nModalResult;
}
void Inter_Num::DeteleDlg()
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
/*
if (du.GetSafeHwnd())
{
du.CEdit_Num.ShowWindow(SW_HIDE);
du.CStatic_Num.ShowWindow(SW_HIDE);
}
*/


void Inter_Num::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
