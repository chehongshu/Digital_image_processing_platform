
#pragma once
#include "Myimage.h"
#include "ComplexNumber.h"
class CImageCheDoc : public CDocument
{
protected: // 仅从序列化创建

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

// 实现
public:
	virtual ~CImageCheDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HDIB m_hDIB;
	CSize m_sizeDoc;
	
// 生成的消息映射函数
	//添加
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
