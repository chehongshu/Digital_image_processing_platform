#pragma once


// DialogHist �Ի���

class DialogHist : public CDialogEx
{
	DECLARE_DYNAMIC(DialogHist)

public:
	DialogHist(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogHist();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAHist };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int Mode;
	int Thre;
	double K;
	double B;
};
