// About.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageChe.h"
#include "About.h"
#include "afxdialogex.h"


// About 对话框

IMPLEMENT_DYNAMIC(About, CDialogEx)

About::About(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ABOUTBOX, pParent)
{

}

About::~About()
{
}

void About::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(About, CDialogEx)
END_MESSAGE_MAP()



