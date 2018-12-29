
#pragma once
#include "Myimage.h"
#include "ComplexNumber.h"
class CImageCheDoc : public CDocument
{
protected: // �������л�����

	DECLARE_DYNCREATE(CImageCheDoc)

public:
//////
CImageCheDoc();
	HDIB GetHDIB() const;
public:
ComplexNumber * imageFFTbuf = NULL;
ComplexNumber * imageIFFTbuf = NULL;
LONG *NewWidth = NULL;
LONG *NewHeight = NULL;
double *DCT_f = NULL;
double *DCT_F = NULL;

	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	BOOL OnOpenDocument(LPCTSTR lpszPathName);
	HDIB ReadDIBFile(CFile& file);
	void InitDIBData();
	DWORD DIBHeight(LPSTR lpDIB);
	DWORD DIBWidth(LPSTR lpDIB);
	void ReplaceHDIB(HDIB hDIB);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif 

// ʵ��
public:
	virtual ~CImageCheDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HDIB m_hDIB;
	CSize m_sizeDoc;
	
// ���ɵ���Ϣӳ�亯��
	//���
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
