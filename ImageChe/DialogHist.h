#pragma once


// DialogHist 对话框

class DialogHist : public CDialogEx
{
	DECLARE_DYNAMIC(DialogHist)

public:
	DialogHist(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogHist();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAHist };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int Mode;
	int Thre;
	double K;
	double B;
};
