// DialogHist.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageChe.h"
#include "DialogHist.h"
#include "afxdialogex.h"


// DialogHist �Ի���

IMPLEMENT_DYNAMIC(DialogHist, CDialogEx)

DialogHist::DialogHist(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIAHist, pParent)
	, Mode(0)
	, Thre(0)
	, K(0)
	, B(0)
{

}

DialogHist::~DialogHist()
{
}

void DialogHist::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, Mode);
	DDX_Text(pDX, IDC_EDIT1, Thre);
	DDX_Text(pDX, IDC_EDIT2, K);
	DDX_Text(pDX, IDC_EDIT3, B);
}


BEGIN_MESSAGE_MAP(DialogHist, CDialogEx)
END_MESSAGE_MAP()


// DialogHist ��Ϣ�������
