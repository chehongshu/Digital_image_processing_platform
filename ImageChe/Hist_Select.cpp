// Hist_Select.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageChe.h"
#include "Hist_Select.h"
#include "afxdialogex.h"


// Hist_Select �Ի���

IMPLEMENT_DYNAMIC(Hist_Select, CDialogEx)

Hist_Select::Hist_Select(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_select, pParent)
	, Blue(0)
	, Green(0)
	, hunhe(0)
	, huidu(0)
	, Red(0)
{
	this->Init();
}

Hist_Select::~Hist_Select()
{
}

void Hist_Select::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_huidu, HuiDu);
	DDX_Check(pDX, IDC_CHECK_huidu, huidu);
	DDX_Control(pDX, IDC_CHECK_G, Channal_B);
	DDX_Check(pDX, IDC_CHECK_G, Blue);
	DDX_Control(pDX, IDC_CHECK_Green, Channal_G);
	DDX_Check(pDX, IDC_CHECK_Green, Green);
	DDX_Control(pDX, IDC_CHECK_Hunhe, Hunhe);
	DDX_Check(pDX, IDC_CHECK_Hunhe, hunhe);
	DDX_Control(pDX, IDC_CHECK_R, Channal_R);
	DDX_Check(pDX, IDC_CHECK_R, Red);

}
BEGIN_MESSAGE_MAP(Hist_Select, CDialogEx)
	//ON_BN_CLICKED(IDC_CHECK_Green, &Hist_Select::OnBnClickedCheckGreen)
END_MESSAGE_MAP()
BOOL Hist_Select::Init()
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
BOOL Hist_Select::CreateRunDlgIndirect(LPCDLGTEMPLATE lpDialogTemplate, CWnd* pParentWnd, HINSTANCE hInst)
{
	IsInit = CreateDlgIndirect(lpDialogTemplate, pParentWnd, hInst);// ���öԻ����ʼ������
	return IsInit;
}
INT_PTR Hist_Select::MyGetData()
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
void Hist_Select::DeteleDlg()
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
void Hist_Select::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}