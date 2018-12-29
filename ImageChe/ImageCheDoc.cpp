

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

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}
// CImageCheDoc ���л�
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

// ����ͼ��֧��
void CImageCheDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CImageCheDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
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
// CImageCheDoc ���

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
// CImageCheDoc ����
BOOL CImageCheDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	//HDIB m_hDIB;
	CFile file;
	CFileException fe;
	if (!file.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))//��һ���ĵ� ��û�ж�ȡ���������
	{
		ReportSaveLoadException(lpszPathName, &fe, FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		return FALSE;
	}
	DeleteContents();// �����ĵ��հ�
	TRY 
	{
		m_hDIB=ReadDIBFile(file);//��ȡͼ������
	}
	CATCH (CMemoryException, eLoad)
	{
		file.Abort();
		return FALSE;
	}
	END_CATCH
    InitDIBData();// ��ʼ��DIB
	if (m_hDIB == NULL)
	{
		//CString strMsg;
		//strMsg = "��ȡͼ��ʱ���������ǲ�֧�ָ����͵�ͼ���ļ���";
		//MessageBox(NULL, strMsg, "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		return FALSE;
	}
	SetPathName(lpszPathName);// �����ļ�����
	SetModifiedFlag(FALSE);// ��������
	// ��״̬����ʾ��ǰ����
	//CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	//CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	//pStatus->SetPaneText(1, "ͼ��������ϡ�", TRUE);
	return TRUE;
}
HDIB CImageCheDoc::ReadDIBFile(CFile& file)
{
	BITMAPFILEHEADER bmfHeader;
	DWORD dwBitsSize;
	HDIB hDIB;
	LPSTR lpDIB;
	dwBitsSize = (DWORD)file.GetLength();// ��ȡDIB���ļ������ȣ��ֽڣ�								
	if (file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader)) // ���Զ�ȡDIB�ļ�ͷ
	{
		//AfxMessageBox("�ļ�ͷ��ȡ����", MB_OK);
		return NULL;
	}
	if (bmfHeader.bfType != DIB_HEADER_MARKER)// �ж��Ƿ���DIB���󣬼��ͷ�����ֽ��Ƿ���"BM"
	{
	//MessageBox("sjhsef",MB_OK,NULL);
		return NULL;
	}

	hDIB = (HDIB)::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwBitsSize);// ΪDIB�����ڴ�
	if (hDIB == 0)
	 return NULL;
	
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)hDIB);// ����

	if (file.Read(lpDIB, dwBitsSize - sizeof(BITMAPFILEHEADER)) != dwBitsSize - sizeof(BITMAPFILEHEADER))// ������ // ��С���ԡ�
	{
		::GlobalUnlock((HGLOBAL)hDIB);// �������
		::GlobalFree((HGLOBAL)hDIB);// �ͷ��ڴ�
		//AfxMessageBox("�ļ����ݶ�ȡ����", MB_OK);
		return NULL;
	}
	::GlobalUnlock((HGLOBAL)hDIB);// �������
	return hDIB;
}
// ��ʼ��DIB����
void CImageCheDoc::InitDIBData()
{
	if (m_hDIB == NULL)// ���DIB����Ϊ�գ�ֱ�ӷ���
	  return;
	LPSTR lpDIB = (LPSTR)::GlobalLock((HGLOBAL)m_hDIB);// ����ͼ���ڴ���
	if (DIBWidth(lpDIB) > INT_MAX || DIBHeight(lpDIB) > INT_MAX)// �ж�ͼ���Ƿ����
	{
		// �ͷ�DIB����
		::GlobalUnlock((HGLOBAL)m_hDIB);
		::GlobalFree((HGLOBAL)m_hDIB);
		m_hDIB = NULL;
		// ����
		//CString strMsg;
		//strMsg = "BMPͼ��̫��";
	//MessageBox(NULL, strMsg, "error", MB_ICONINFORMATION | MB_OK);
		return;
	}
	// ��¼�ĵ���С
	m_sizeDoc = CSize((int)DIBWidth(lpDIB), (int)DIBHeight(lpDIB));

	// ͼ���ڴ�������
	::GlobalUnlock((HGLOBAL)m_hDIB);
}
/*************************************************************************
* �������ƣ�
*	DIBWidth()
* ����:
*	LPSTR	lpDIB	- ָ��DIB�����ָ��
* ����ֵ:
*	DWORD			- DIB��ͼ��Ŀ��
* ˵��:
*	�ú�������DIB��ͼ��Ŀ�ȡ�����Windows 3.0 DIB������BITMAPINFOHEADER
* �е�biWidthֵ��������������BITMAPCOREHEADER�е�bcWidthֵ��
************************************************************************/
DWORD CImageCheDoc::DIBWidth(LPSTR lpDIB)
{
	LPBITMAPINFOHEADER lpbmi;// ָ��BITMAPINFOHEADER�ṹ��ָ�루Win3.0��
	LPBITMAPCOREHEADER lpbmc;// ָ��BITMAPCOREHEADER�ṹ��ָ��
	lpbmi = (LPBITMAPINFOHEADER)lpDIB;// ��ȡָ��
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	if (IS_WIN30_DIB(lpDIB))// ����DIB��ͼ��Ŀ��
		return lpbmi->biWidth;// ����Windows 3.0 DIB������lpbmi->biWidth
	else
		return (DWORD)lpbmc->bcWidth;// ����������ʽ��DIB������lpbmc->bcWidth
	
}
/*************************************************************************
*
* �������ƣ�
*	DIBHeight()
*
* ����:
*	LPSTR	lpDIB	- ָ��DIB�����ָ��
*
* ����ֵ:
*	DWORD			- DIB��ͼ��ĸ߶�
*
* ˵��:
*	�ú�������DIB��ͼ��ĸ߶ȡ�����Windows 3.0 DIB������BITMAPINFOHEADER
* �е�biHeightֵ��������������BITMAPCOREHEADER�е�bcHeightֵ��
*
************************************************************************/
DWORD CImageCheDoc::DIBHeight(LPSTR lpDIB)
{
	LPBITMAPINFOHEADER lpbmi;// ָ��BITMAPINFOHEADER�ṹ��ָ�루Win3.0��
	LPBITMAPCOREHEADER lpbmc;// ָ��BITMAPCOREHEADER�ṹ��ָ��
	// ��ȡָ��
	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;
	if (IS_WIN30_DIB(lpDIB))// ����DIB��ͼ��Ŀ��	
		return lpbmi->biHeight;// ����Windows 3.0 DIB������lpbmi->biHeight
	else
		return (DWORD)lpbmc->bcHeight;// ����������ʽ��DIB������lpbmc->bcHeight
}
void CImageCheDoc::ReplaceHDIB(HDIB hDIB)
{
	// �滻DIB���ڹ���ճ�����õ��ú���
	if (m_hDIB != NULL)
		::GlobalFree((HGLOBAL)m_hDIB);// �ǿգ������
	m_hDIB = hDIB;
}