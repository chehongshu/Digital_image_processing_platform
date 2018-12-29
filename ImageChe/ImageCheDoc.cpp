

#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "ImageChe.h"
#endif

#include "ImageCheDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CImageCheDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageCheDoc, CDocument)
END_MESSAGE_MAP()

CImageCheDoc::CImageCheDoc()
{
	NewHeight = new LONG[1];
	NewWidth = new LONG[1];
}

CImageCheDoc::~CImageCheDoc()
{
	if (this->imageFFTbuf != NULL)
	{
		delete[]this->imageFFTbuf;
		this->imageFFTbuf = NULL;
	}
	if (this->imageIFFTbuf != NULL)
	{
		delete[]this->imageIFFTbuf;
		this->imageIFFTbuf = NULL;
	}
	if (this->DCT_F != NULL)
	{
		delete[]this->DCT_F;
		this->DCT_F = NULL;
	}
	if (this->DCT_f!= NULL)
	{
		delete[]this->DCT_f;
		this->DCT_f = NULL;
	}
	delete NewHeight;
	delete NewWidth;
	
}

BOOL CImageCheDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}
// CImageCheDoc 序列化
HDIB CImageCheDoc::GetHDIB() const
{
	return m_hDIB;
}
void CImageCheDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		
	}
	else
	{
		
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CImageCheDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CImageCheDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CImageCheDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS
// CImageCheDoc 诊断

#ifdef _DEBUG
void CImageCheDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageCheDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif 
// CImageCheDoc 命令
BOOL CImageCheDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	//HDIB m_hDIB;
	CFile file;
	CFileException fe;
	if (!file.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))//打开一个文档 并没有读取里面的内容
	{
		ReportSaveLoadException(lpszPathName, &fe, FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		return FALSE;
	}
	DeleteContents();// 保持文档空白
	TRY 
	{
		m_hDIB=ReadDIBFile(file);//读取图像内容
	}
	CATCH (CMemoryException, eLoad)
	{
		file.Abort();
		return FALSE;
	}
	END_CATCH
    InitDIBData();// 初始化DIB
	if (m_hDIB == NULL)
	{
		//CString strMsg;
		//strMsg = "读取图像时出错！可能是不支持该类型的图像文件！";
		//MessageBox(NULL, strMsg, "系统提示", MB_ICONINFORMATION | MB_OK);
		return FALSE;
	}
	SetPathName(lpszPathName);// 设置文件名称
	SetModifiedFlag(FALSE);// 设置脏标记
	// 在状态栏显示当前操作
	//CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	//CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	//pStatus->SetPaneText(1, "图像载入完毕。", TRUE);
	return TRUE;
}
HDIB CImageCheDoc::ReadDIBFile(CFile& file)
{
	BITMAPFILEHEADER bmfHeader;
	DWORD dwBitsSize;
	HDIB hDIB;
	LPSTR lpDIB;
	dwBitsSize = (DWORD)file.GetLength();// 获取DIB（文件）长度（字节）								
	if (file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader)) // 尝试读取DIB文件头
	{
		//AfxMessageBox("文件头读取有误！", MB_OK);
		return NULL;
	}
	if (bmfHeader.bfType != DIB_HEADER_MARKER)// 判断是否是DIB对象，检查头两个字节是否是"BM"
	{
	//MessageBox("sjhsef",MB_OK,NULL);
		return NULL;
	}

	hDIB = (HDIB)::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwBitsSize);// 为DIB分配内存
	if (hDIB == 0)
	 return NULL;
	
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)hDIB);// 锁定

	if (file.Read(lpDIB, dwBitsSize - sizeof(BITMAPFILEHEADER)) != dwBitsSize - sizeof(BITMAPFILEHEADER))// 读象素 // 大小不对。
	{
		::GlobalUnlock((HGLOBAL)hDIB);// 解除锁定
		::GlobalFree((HGLOBAL)hDIB);// 释放内存
		//AfxMessageBox("文件内容读取有误！", MB_OK);
		return NULL;
	}
	::GlobalUnlock((HGLOBAL)hDIB);// 解除锁定
	return hDIB;
}
// 初始化DIB对象
void CImageCheDoc::InitDIBData()
{
	if (m_hDIB == NULL)// 如果DIB对象为空，直接返回
	  return;
	LPSTR lpDIB = (LPSTR)::GlobalLock((HGLOBAL)m_hDIB);// 锁定图像内存区
	if (DIBWidth(lpDIB) > INT_MAX || DIBHeight(lpDIB) > INT_MAX)// 判断图像是否过大
	{
		// 释放DIB对象
		::GlobalUnlock((HGLOBAL)m_hDIB);
		::GlobalFree((HGLOBAL)m_hDIB);
		m_hDIB = NULL;
		// 报错
		//CString strMsg;
		//strMsg = "BMP图像太大！";
	//MessageBox(NULL, strMsg, "error", MB_ICONINFORMATION | MB_OK);
		return;
	}
	// 记录文档大小
	m_sizeDoc = CSize((int)DIBWidth(lpDIB), (int)DIBHeight(lpDIB));

	// 图像内存区解锁
	::GlobalUnlock((HGLOBAL)m_hDIB);
}
/*************************************************************************
* 函数名称：
*	DIBWidth()
* 参数:
*	LPSTR	lpDIB	- 指向DIB对象的指针
* 返回值:
*	DWORD			- DIB中图像的宽度
* 说明:
*	该函数返回DIB中图像的宽度。对于Windows 3.0 DIB，返回BITMAPINFOHEADER
* 中的biWidth值；对于其它返回BITMAPCOREHEADER中的bcWidth值。
************************************************************************/
DWORD CImageCheDoc::DIBWidth(LPSTR lpDIB)
{
	LPBITMAPINFOHEADER lpbmi;// 指向BITMAPINFOHEADER结构的指针（Win3.0）
	LPBITMAPCOREHEADER lpbmc;// 指向BITMAPCOREHEADER结构的指针
	lpbmi = (LPBITMAPINFOHEADER)lpDIB;// 获取指针
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	if (IS_WIN30_DIB(lpDIB))// 返回DIB中图像的宽度
		return lpbmi->biWidth;// 对于Windows 3.0 DIB，返回lpbmi->biWidth
	else
		return (DWORD)lpbmc->bcWidth;// 对于其它格式的DIB，返回lpbmc->bcWidth
	
}
/*************************************************************************
*
* 函数名称：
*	DIBHeight()
*
* 参数:
*	LPSTR	lpDIB	- 指向DIB对象的指针
*
* 返回值:
*	DWORD			- DIB中图像的高度
*
* 说明:
*	该函数返回DIB中图像的高度。对于Windows 3.0 DIB，返回BITMAPINFOHEADER
* 中的biHeight值；对于其它返回BITMAPCOREHEADER中的bcHeight值。
*
************************************************************************/
DWORD CImageCheDoc::DIBHeight(LPSTR lpDIB)
{
	LPBITMAPINFOHEADER lpbmi;// 指向BITMAPINFOHEADER结构的指针（Win3.0）
	LPBITMAPCOREHEADER lpbmc;// 指向BITMAPCOREHEADER结构的指针
	// 获取指针
	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;
	if (IS_WIN30_DIB(lpDIB))// 返回DIB中图像的宽度	
		return lpbmi->biHeight;// 对于Windows 3.0 DIB，返回lpbmi->biHeight
	else
		return (DWORD)lpbmc->bcHeight;// 对于其它格式的DIB，返回lpbmc->bcHeight
}
void CImageCheDoc::ReplaceHDIB(HDIB hDIB)
{
	// 替换DIB，在功能粘贴中用到该函数
	if (m_hDIB != NULL)
		::GlobalFree((HGLOBAL)m_hDIB);// 非空，则清除
	m_hDIB = hDIB;
}