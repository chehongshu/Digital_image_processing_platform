
#include "stdafx.h"
#include "MyImage.h"
#include "ImageCheView.h"
#include "ImageChe.h"
#include "MainFrm.h"
#include "ImageCheDoc.h"
#include <stack>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__; 
#endif
/*************************************************************************
*
* 函数名称：
*	DIBWidth()
*
* 参数:
*	LPSTR	lpDIB	- 指向DIB对象的指针
*
* 返回值:
*	DWORD			- DIB中图像的宽度
*
* 说明:
*	该函数返回DIB中图像的宽度。对于Windows 3.0 DIB，返回BITMAPINFOHEADER
* 中的biWidth值；对于其它返回BITMAPCOREHEADER中的bcWidth值。
*
************************************************************************/
BYTE DIBBitCount(LPSTR lpDIB)
{
	BYTE bBitCount;

	// 读取象素的位数
	if (IS_WIN30_DIB(lpDIB))
	{
		// 读取biBitCount值
		bBitCount = (BYTE)((LPBITMAPINFOHEADER)lpDIB)->biBitCount;
	}
	else
	{
		// 读取biBitCount值
		bBitCount = (BYTE)((LPBITMAPCOREHEADER)lpDIB)->bcBitCount;
	}

	return bBitCount;
}
DWORD DIBWidth(LPSTR lpDIB)
{
	// 指向BITMAPINFOHEADER结构的指针（Win3.0）
	LPBITMAPINFOHEADER lpbmi;

	// 指向BITMAPCOREHEADER结构的指针
	LPBITMAPCOREHEADER lpbmc;

	// 获取指针
	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	// 返回DIB中图像的宽度
	if (IS_WIN30_DIB(lpDIB))
	{
		// 对于Windows 3.0 DIB，返回lpbmi->biWidth
		return lpbmi->biWidth;
	}
	else
	{
		// 对于其它格式的DIB，返回lpbmc->bcWidth
		return (DWORD)lpbmc->bcWidth;
	}
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

DWORD DIBHeight(LPSTR lpDIB)
{
	// 指向BITMAPINFOHEADER结构的指针（Win3.0）
	LPBITMAPINFOHEADER lpbmi;

	// 指向BITMAPCOREHEADER结构的指针
	LPBITMAPCOREHEADER lpbmc;

	// 获取指针
	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	// 返回DIB中图像的宽度
	if (IS_WIN30_DIB(lpDIB))
	{
		// 对于Windows 3.0 DIB，返回lpbmi->biHeight
		return lpbmi->biHeight;
	}
	else
	{
		// 对于其它格式的DIB，返回lpbmc->bcHeight
		return (DWORD)lpbmc->bcHeight;
	}
}

/*************************************************************************
* 显示图像
* 函数名称：
*	PaintDIB()
*
* 参数:
*	HDC			hDC			- 输出设备DC的句柄
*	LPRECT		lpDCRect	- 绘制矩形区域
*	HDIB		hDIB		- 指向DIB对象的句柄
*	LPRECT		lpDIBRect	- 要输出的DIB区域
*	CPalette*	pPal		- 指向DIB对象调色板的指针
*
* 返回值:
*	BOOL					- 绘制成功返回TRUE，否则返回FALSE。
*
* 说明:
*	该函数主要用来绘制DIB对象。其中调用了StretchDIBits()或者
* SetDIBitsToDevice()来绘制DIB对象。输出的设备由由参数hDC指
* 定；绘制的矩形区域由参数lpDCRect指定；输出DIB的区域由参数
* lpDIBRect指定。
*
************************************************************************/
BOOL PaintDIB(HDC hDC, LPRECT lpDCRect, HDIB hDIB, LPRECT lpDIBRect)
{
	LPSTR lpDIBHdr;				// BITMAPINFOHEADER指针
	LPSTR lpDIBBits;				// DIB象素指针
	BOOL blSuccess = FALSE;		// 成功标志
		
	if (hDC == NULL || lpDCRect == NULL || lpDIBRect == NULL)// 判断输入参数是否有误
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	
	if (hDIB == NULL)// 判断DIB对象是否为空
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	lpDIBHdr = (LPSTR)::GlobalLock((HGLOBAL)hDIB);// 锁定DIB
	lpDIBBits = FindDIBBits(lpDIBHdr);// 找到DIB图像象素起始位置
	
	::SetStretchBltMode(hDC, COLORONCOLOR);// 设置显示模式
										   // 判断是调用StretchDIBits()还是SetDIBitsToDevice()来绘制DIB对象
	if ((RECTWIDTH(lpDCRect) == RECTWIDTH(lpDIBRect)) &&
		(RECTHEIGHT(lpDCRect) == RECTHEIGHT(lpDIBRect)))
	{
		// 原始大小，不用拉伸。
		blSuccess = ::SetDIBitsToDevice(hDC,  						// hDC
			lpDCRect->left,				// DestX
			lpDCRect->top,				// DestY
			RECTWIDTH(lpDCRect),			// nDestWidth
			RECTHEIGHT(lpDCRect),		// nDestHeight
			lpDIBRect->left,				// SrcX
			(int)DIBHeight(lpDIBHdr) -
			lpDIBRect->top -
			RECTHEIGHT(lpDIBRect),	// SrcY
			0,							// nStartScan
			(WORD)DIBHeight(lpDIBHdr),	// nNumScans
			lpDIBBits,					// lpBits
			(LPBITMAPINFO)lpDIBHdr,		// lpBitsInfo
			DIB_RGB_COLORS);				// wUsage
	}
	else
	{
		// 非原始大小，拉伸。
		blSuccess = ::StretchDIBits(hDC,							// hDC
			lpDCRect->left,					// DestX
			lpDCRect->top,					// DestY
			RECTWIDTH(lpDCRect),				// nDestWi+dth
			RECTHEIGHT(lpDCRect),			// nDestHeight
			lpDIBRect->left,					// SrcX
			lpDIBRect->top,					// SrcY
			RECTWIDTH(lpDIBRect),			// wSrcWidth
			RECTHEIGHT(lpDIBRect),			// wSrcHeight
			lpDIBBits,						// lpBits
			(LPBITMAPINFO)lpDIBHdr,			// lpBitsInfo
			DIB_RGB_COLORS,					// wUsage
			SRCCOPY);						// dwROP
	}
	// 解除锁定
	::GlobalUnlock((HGLOBAL)hDIB);
	return blSuccess;
}

/*************************************************************************
*
* 函数名称：
*	FindDIBBits()
*
* 参数:
*	LPSTR	lpDIB	- 指向DIB对象的指针
*
* 返回值:
*	LPSTR			- 指向DIB图像象素起始位置
*
* 说明:
*	该函数计算DIB中图像象素的起始位置，并返回指向它的指针。
*
************************************************************************/

LPSTR FindDIBBits(LPSTR lpDIB)
{
	return (lpDIB + (*((LPDWORD)lpDIB)) + PaletteSize(lpDIB));
}

/*************************************************************************
*
* 函数名称：
*	PaletteSize()
*
* 参数:
*	LPSTR	lpDIB	- 指向DIB对象的指针
*
* 返回值:
*	WORD			- DIB中调色板的大小
*
* 说明:
*	该函数返回DIB中调色板的大小。对于Windows 3.0 DIB，返回颜色数目×
* RGBQUAD的大小；对于其它返回颜色数目×RGBTRIPLE的大小。
*
************************************************************************/

WORD PaletteSize(LPSTR lpDIB)
{
	// 计算DIB中调色板的大小
	if (IS_WIN30_DIB(lpDIB))
	{
		//返回颜色数目×RGBQUAD的大小
		return (WORD)(DIBNumColors(lpDIB) * sizeof(RGBQUAD));
	}
	else
	{
		//返回颜色数目×RGBTRIPLE的大小
		return (WORD)(DIBNumColors(lpDIB) * sizeof(RGBTRIPLE));
	}
}
/*************************************************************************
*
* 函数名称：
*	FindPalette()
*
* 参数:
*	LPSTR	lpDIB	- 指向DIB对象的指针
*
* 返回值:
*	LPSTR			- 指向DIB调色板的起始位置
*
* 说明:
*	该函数计算DIB中调色板的起始位置，并返回指向它的指针。
*
************************************************************************/

LPSTR FindPalette(LPSTR lpDIB)
{
	return (DIBNumColors(lpDIB) == 0 ? NULL : lpDIB + (*((LPDWORD)lpDIB)));
}

/*************************************************************************
*
* 函数名称：
*	DIBNumColors()
*
* 参数:
*	LPSTR	lpDIB	- 指向DIB对象的指针
*
* 返回值:
*	WORD			- 返回调色板中颜色的种数
*
* 说明:
*	该函数返回DIB中调色板的颜色的种数。对于单色位图，返回2，
* 对于16色位图，返回16，对于256色位图，返回256；对于真彩色
* 位图（24位），没有调色板，返回0。
*
************************************************************************/

WORD DIBNumColors(LPSTR lpDIB)
{
	BYTE bBitCount;

	// 对于Windows的DIB, 实际颜色的数目可以比象素的位数要少。
	// 对于这种情况，则返回一个近似的数值。

	// 判断是否是WIN3.0 DIB
	if (IS_WIN30_DIB(lpDIB))
	{
		DWORD dwClrUsed;

		// 读取dwClrUsed值
		dwClrUsed = ((LPBITMAPINFOHEADER)lpDIB)->biClrUsed;

		if (dwClrUsed != 0)
		{
			// 如果dwClrUsed（实际用到的颜色数）不为0，直接返回该值
			return (WORD)dwClrUsed;
		}
	}

	// 读取象素的位数
	if (IS_WIN30_DIB(lpDIB))
	{
		// 读取biBitCount值
		bBitCount = (BYTE)((LPBITMAPINFOHEADER)lpDIB)->biBitCount;
	}
	else
	{
		// 读取biBitCount值
		bBitCount = (BYTE)((LPBITMAPCOREHEADER)lpDIB)->bcBitCount;
	}

	// 按照象素的位数计算颜色数目
	switch (bBitCount)
	{
	case 1:
		return 2;

	case 4:
		return 16;

	case 8:
		return 256;

	default:
		return 0;
	}
}

inline LONG IF_BilinearInterpolation(LPSTR lpDIBBits, BYTE bBitCount, LONG lWidth, LONG lHeight, double dX, double dY)
{
	// 四个最临近像素的坐标(j1, i1), (j2, i1), (j1, i2), (j2, i2)
	LONG i1, i2;
	LONG j1, j2;

	// 四个最临近像素值
	BYTE bP1, bP2, bP3, bP4;

	// 二个插值中间值
	BYTE bP12, bP34;

	// RGB分量返回值
	LONG lRGB;

	// DIB图像每行的字节数
	LONG lLineByteNum;

	// 计算DIB图像每行的字节数
	lLineByteNum = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	// 根据不同情况分别处理
	if (dX<-1.0 || dX >= (double)lWidth || dY<-1.0 || dY >= (double)lHeight)
	{
		// 要计算的点不在源图范围内，直接返回bwmDIBWhite。
		if (bBitCount == 8)
		{
			// 对单通道色图
			return 255;
		}
		else
		{
			// 对三通道色图
			return (255 << 16) | (255 << 8) | 255;	//即连续三个bwmDIBWhite
		}
	}
	else
	{
		// 计算四个最临近像素的坐标
		j1 = (LONG)dX;
		j2 = j1 + 1;
		if (j1<0)
		{
			j1 = 0;
		}
		if (j2>lWidth - 1)
		{
			j2 = lWidth - 1;
		}
		i1 = (LONG)dY;
		i2 = i1 + 1;
		if (i1<0)
		{
			i1 = 0;
		}
		if (i2>lHeight - 1)
		{
			i2 = lHeight - 1;
		}

		// 计算四个最临近像素值
		if (bBitCount == 8)
		{
			// 对单通道色图
			bP1 = ((BYTE*)lpDIBBits)[lLineByteNum*(lHeight - 1 - i1) + j1];
			bP2 = ((BYTE*)lpDIBBits)[lLineByteNum*(lHeight - 1 - i1) + j2];
			bP3 = ((BYTE*)lpDIBBits)[lLineByteNum*(lHeight - 1 - i2) + j1];
			bP4 = ((BYTE*)lpDIBBits)[lLineByteNum*(lHeight - 1 - i2) + j2];
			bP12 = DoubleToByte(bP1 + (dX - j1)*(bP2 - bP1));
			bP34 = DoubleToByte(bP3 + (dX - j1)*(bP4 - bP3));
			return DoubleToByte(bP12 + (dY - i1)*(bP34 - bP12));
		}
		else
		{
			// 对三通道色图
			bP1 = ((BYTE*)lpDIBBits)[lLineByteNum*(lHeight - 1 - i1) + j1 * 3 + scBlue];
			bP2 = ((BYTE*)lpDIBBits)[lLineByteNum*(lHeight - 1 - i1) + j2 * 3 + scBlue];
			bP3 = ((BYTE*)lpDIBBits)[lLineByteNum*(lHeight - 1 - i2) + j1 * 3 + scBlue];
			bP4 = ((BYTE*)lpDIBBits)[lLineByteNum*(lHeight - 1 - i2) + j2 * 3 + scBlue];
			bP12 = DoubleToByte(bP1 + (dX - j1)*(bP2 - bP1));
			bP34 = DoubleToByte(bP3 + (dX - j1)*(bP4 - bP3));
			lRGB = DoubleToByte(bP12 + (dY - i1)*(bP34 - bP12));
			lRGB <<= 8;
			bP1 = ((BYTE*)lpDIBBits)[lLineByteNum*(lHeight - 1 - i1) + j1 * 3 + scGreen];
			bP2 = ((BYTE*)lpDIBBits)[lLineByteNum*(lHeight - 1 - i1) + j2 * 3 + scGreen];
			bP3 = ((BYTE*)lpDIBBits)[lLineByteNum*(lHeight - 1 - i2) + j1 * 3 + scGreen];
			bP4 = ((BYTE*)lpDIBBits)[lLineByteNum*(lHeight - 1 - i2) + j2 * 3 + scGreen];
			bP12 = DoubleToByte(bP1 + (dX - j1)*(bP2 - bP1));
			bP34 = DoubleToByte(bP3 + (dX - j1)*(bP4 - bP3));
			lRGB |= DoubleToByte(bP12 + (dY - i1)*(bP34 - bP12));
			lRGB <<= 8;
			bP1 = ((BYTE*)lpDIBBits)[lLineByteNum*(lHeight - 1 - i1) + j1 * 3 + scRed];
			bP2 = ((BYTE*)lpDIBBits)[lLineByteNum*(lHeight - 1 - i1) + j2 * 3 + scRed];
			bP3 = ((BYTE*)lpDIBBits)[lLineByteNum*(lHeight - 1 - i2) + j1 * 3 + scRed];
			bP4 = ((BYTE*)lpDIBBits)[lLineByteNum*(lHeight - 1 - i2) + j2 * 3 + scRed];
			bP12 = DoubleToByte(bP1 + (dX - j1)*(bP2 - bP1));
			bP34 = DoubleToByte(bP3 + (dX - j1)*(bP4 - bP3));
			lRGB |= DoubleToByte(bP12 + (dY - i1)*(bP34 - bP12));
			return lRGB;
		}
	}
	return 0;
}
/* fly CODE*/
/**************************************************************************

**************************************************************************/
BYTE PaiXu(BYTE *p, int m)
{
	int i = 0, j = 0;
	BYTE n = 0;
	for (i = 0;i < m;i++)
	{
		for (j = 0;j < m - i - 1;j++)
		{
			if (p[j] > p[j + 1])
			{
				n = p[j];
				p[j] = p[j + 1];
				p[j + 1] = n;
			}
		}
	}
	return p[m / 2];
}
/*************************************************************************
*
* 函数名称：
*	HGLOBAL NXBJZtogramProcess(LPSTR lpDIB,double Q)
*   逆谐波均值滤波 
* 参数:
*	LPSTR	lpDIB	- 指向DIB对象的指针
*
* 返回值:
*	LPSTR			- 指向DIB调色板的起始位置
*
* 说明:
*	该函数计算DIB中调色板的起始位置，并返回指向它的指针。
* Q 为传进来的阶数 
************************************************************************/

HGLOBAL NXBJZtogramProcess(LPSTR lpDIB,double Q)
{

	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	double temp3 = 0.0, temp4 = 0;
	int mm = 0, k = -1, t = -1;
	char a[9] = { 0,1,0,1,1,1,0,1,0 };
	for (i = 1; i < lHeight - 1; i++)// 模板处理
	{
		bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
		for (j = 1; j < lWidth - 1; j++)
		{
			if (bBitCount == 8)
			{
				for (k = -1;k < 2;k++)
				{
					bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
					if (k != 0)
					{
						temp3 += pow(((double)(bpSrc[(j)] + 10)), Q + 1);
						temp4 += pow(((double)(bpSrc[(j)] + 10)), Q);
					}
					else
					{
						for (t = -1;t < 2;t++)
						{
							temp3 += pow(((double)(bpSrc[(j + t)] + 10)), Q + 1);
							temp4 += pow(((double)(bpSrc[(j + t)] + 10)), Q);
						}
					}

				}
				temp3 = temp3 / temp4;
				temp3 = temp3 - 10;
				if (temp3<0)
				{
					temp3 = 0;
				}
				else
				{
					if (temp3>255)
					{
						temp3 = 255;
					}
				}
				bpDst[j] = (BYTE)temp3;
				temp3 = 0.0;
				temp4 = 0.0;
			}
			else
			{
				for (mm = 0;mm < 3;mm++)
				{
					//九个点
					/*
					for (k = -1;k < 2;k++)
					{

					bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);//
					for (t = -1;t < 2;t++)
					{
					temp3 += pow(((double) (bpSrc[(j + t) * 3 + mm]+10)), Q + 1);
					temp4 += pow(((double) (bpSrc[(j + t) * 3 + mm]+10)), Q);
					temp3 +=1/((double) (bpSrc[(j + t) * 3 + mm]+10));
					}
					}

					*/
					//5 个点处理
					for (k = -1;k < 2;k++)
					{
						bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
						if (k != 0)
						{
							temp3 += pow(((double)(bpSrc[(j) * 3 + mm] + 10)), Q + 1);
							temp4 += pow(((double)(bpSrc[(j) * 3 + mm] + 10)), Q);
						}
						else
						{
							for (t = -1;t < 2;t++)
							{
								temp3 += pow(((double)(bpSrc[(j + t) * 3 + mm] + 10)), Q + 1);
								temp4 += pow(((double)(bpSrc[(j + t) * 3 + mm] + 10)), Q);
							}
						}

					}
					temp3 = temp3 /temp4;
					temp3 = temp3 - 10;
					if (temp3<0)
					{
						temp3 = 0;
					}
					else
					{
						if (temp3>255)
						{
							temp3 = 255;
						}
					}
					bpDst[j * 3 + mm] = (BYTE)temp3;
					temp3 = 0.0;
					temp4 = 0.0;
				}
			}
		}
	}
	return hDIB;
}
/*************************************************************************
*
* 函数名称：
*	HGLOBAL XBJZtogramProcess(LPSTR lpDIB)
*   逆谐波均值滤波
* 参数:
*	LPSTR	lpDIB	- 指向DIB对象的指针
*
* 返回值:
*	LPSTR			- 指向DIB调色板的起始位置
*
* 说明:
*	该函数计算DIB中调色板的起始位置，并返回指向它的指针。
*  谐波均值滤波
************************************************************************/
HGLOBAL XBJZtogramProcess(LPSTR lpDIB)
{

	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	double temp3 = 0.0;
	int mm = 0, k = -1, t = -1;
	for (i = 1; i < lHeight - 1; i++)// 模板处理
	{
		bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
		for (j = 1; j < lWidth - 1; j++)
		{
			if (bBitCount == 8)
			{
				for (k = -1;k < 2;k++)
				{
					bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
					if (k != 0)
					{
						temp3 += 1 / ((double)(bpSrc[j] + 1000));
					}
					else
					{
						for (t = -1;t < 2;t++)
						{
							temp3 += 1 / ((double)(bpSrc[j + t] + 1000));
						}
					}

				}
				temp3 = 5.0 / temp3;// pow(temp3, 0.2);
				temp3 = temp3 - 1000;
				if (temp3<0)
				{
					temp3 = 0;
				}
				else
				{
					if (temp3>255)
					{
						temp3 = 255;
					}
				}
				bpDst[j] = (BYTE)temp3;
				temp3 = 0.0;
			}
			else
			{

				for (mm = 0;mm < 3;mm++)
				{
					for (k = -1;k < 2;k++)
					{
						bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);// 
						if (k != 0)
						{
							temp3 += 1 / ((double)(bpSrc[(j) * 3 + mm] + 1000));
						}
						else
						{
							for (t = -1;t < 2;t++)
							{
								temp3 += 1 / ((double)(bpSrc[(j + t) * 3 + mm] + 1000));
							}
						}

					}
					temp3 = 5.0 / temp3;
					temp3 = temp3 - 1000;
					if (temp3<0)
					{
						temp3 = 0;
					}
					else
					{
						if (temp3>255)
						{
							temp3 = 255;
						}
					}
					bpDst[j * 3 + mm] = (BYTE)temp3;
					temp3 = 0.0;
				}
			}
		}
	}
	return hDIB;
}
/*************************************************************************
*
* 函数名称：
*	HGLOBAL JHJZLBtogramProcess(LPSTR lpDIB)
*   几何均值滤波
* 参数:
*	LPSTR	lpDIB	- 指向DIB对象的指针
*
* 返回值:
*	LPSTR			- 指向DIB调色板的起始位置
*
* 说明:
*	该函数计算DIB中调色板的起始位置，并返回指向它的指针。
************************************************************************/
HGLOBAL JHJZLBtogramProcess(LPSTR lpDIB)
{

	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	double temp3 = 1.0;
	int mm = 0, k = -1, t = -1;
	for (i = 1; i < lHeight - 1; i++)// 模板处理
	{
		bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
		for (j = 1; j < lWidth - 1; j++)
		{
			if (bBitCount == 8)
			{
				for (k = -1;k < 2;k++)
				{
					bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);// 
					if (k != 0)
					{
						temp3 *= (bpSrc[(j)] + 1000);
					}
					else
					{
						for (t = -1;t < 2;t++)
						{
							temp3 *= (bpSrc[(j + t)] + 1000);
						}
					}

				}
				temp3 = pow(temp3, 0.2);
				temp3 = temp3 - 1000;
				if (temp3<0)
				{
					temp3 = 0;
				}
				else
				{
					if (temp3>255)
					{
						temp3 = 255;
					}
				}
				bpDst[j] = (BYTE)temp3;
				temp3 = 1.0;
			}
			else
			{
				for (mm = 0;mm < 3;mm++)
				{
				
					/*
					九个点
					for (k = -1;k < 2;k++)
					{
					//k = 1;
					bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);//
					for (t = -1;t < 2;t++)
					{
					temp3 *= (bpSrc[(j + t) * 3 + mm]+1000);
					}
					}
					temp3 = pow(temp3, 0.11111111111);
					*/
					/* 5 个点处理*/
					for (k = -1;k < 2;k++)
					{
						bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);// 
						if (k != 0)
						{
							temp3 *= (bpSrc[(j) * 3 + mm] + 1000);
						}
						else
						{
							for (t = -1;t < 2;t++)
							{
								temp3 *= (bpSrc[(j + t) * 3 + mm] + 1000);
							}
						}

					}
					temp3 = pow(temp3, 0.2);
					temp3 = temp3 - 1000;
					if (temp3<0)
					{
						temp3 = 0;
					}
					else
					{
						if (temp3>255)
						{
							temp3 = 255;
						}
					}
					bpDst[j * 3 + mm] = (BYTE)temp3;
					temp3 = 1.0;
				}
			}
		}
	}
	return hDIB;
}
/*************************************************************************
*
* 函数名称：
HGLOBAL SSJZLBtogramProcess(LPSTR lpDIB ,int n)
*   邻域均值滤波
* 参数:
*	LPSTR	lpDIB	- 指向DIB对象的指针
*
* 返回值:
*	LPSTR			- 指向DIB调色板的起始位置
*
* 说明:
*	该函数计算DIB中调色板的起始位置，并返回指向它的指针。
************************************************************************/
HGLOBAL SSJZLBtogramProcess(LPSTR lpDIB ,int n)
{

	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	double temp = 1.0;
	int mm = 0, k = -1, t = -1;
	if (n == 0)
	{
		for (i = 1; i < lNewHeight - 1; i++)// 模板处理
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			for (j = 1; j < lNewWidth - 1; j++)
			{
				if (bBitCount == 8)
				{
					for (k = -1;k < 2;k++)
					{
						bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
						if (k != 0)
						{
							t = 0;
							temp += bpSrc[j + t];
						}
						else
						{
							for (t = -1;t < 2;t++)
							{
								temp += bpSrc[j + t];
							}
						}
					}
					temp = temp / 5;
					bpDst[j] = (BYTE)temp;
					temp = 0;
				}
				else
				{
					for (mm = 0;mm < 3;mm++)
					{
						for (k = -1;k < 2;k++)
						{
							bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
							if (k != 0)
							{
								t = 0;
								temp += bpSrc[(j + t) * 3 + mm];
							}
							else
							{
								for (t = -1;t < 2;t++)
								{
									temp += bpSrc[(j + t) * 3 + mm];
								}
							}
						}
						temp = temp / 5;
						bpDst[j * 3 + mm] = (BYTE)temp;
						temp = 0;
					}
				}
			}
		}
	}
	else
	{
		for (i = 1; i < lNewHeight - 1; i++)// 模板处理
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			for (j = 1; j < lNewWidth - 1; j++)
			{
				if (bBitCount == 8)
				{
					for (k = -1;k < 2;k++)
					{
						bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
						for (t = -1;t < 2;t++)
						{
							temp += bpSrc[j + t];
						}
					}
					temp = temp / 9;
					bpDst[j] = (BYTE)temp;
					temp = 0;
				}
				else
				{
					for (mm = 0;mm < 3;mm++)
					{
						for (k = -1;k < 2;k++)
						{
							bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
							for (t = -1;t < 2;t++)
							{
								temp += bpSrc[(j + t) * 3 + mm];
							}
						}
						temp = temp / 9;
						bpDst[j * 3 + mm] = (BYTE)temp;
						temp = 0;
					}
				}
			}
		}
	}
	return hDIB;

}
/****以此时像素点为中心取一个方框九个像素值*****/
void GetNinePixels(int* Pixels, BYTE *bpSrc, LONG lLineBytes, LONG j, int color)
{
	if (color>2)
	{
		//  灰度图
		Pixels[0] = bpSrc[j - lLineBytes - 1];
		Pixels[1] = bpSrc[j - lLineBytes];
		Pixels[2] = bpSrc[j - lLineBytes + 1];
		Pixels[3] = bpSrc[j - 1];
		Pixels[4] = bpSrc[j];
		Pixels[5] = bpSrc[j + 1];
		Pixels[6] = bpSrc[j + lLineBytes - 1];
		Pixels[7] = bpSrc[j + lLineBytes];
		Pixels[8] = bpSrc[j + lLineBytes + 1];
	}
	else
	{
		// R G B 图
		Pixels[0] = bpSrc[(j - 1) * 3 + color - lLineBytes];
		Pixels[1] = bpSrc[(j) * 3 + color - lLineBytes];
		Pixels[2] = bpSrc[(j + 1) * 3 + color - lLineBytes];
		Pixels[3] = bpSrc[(j - 1) * 3 + color];
		Pixels[4] = bpSrc[j * 3 + color];
		Pixels[5] = bpSrc[(j + 1) * 3 + color];
		Pixels[6] = bpSrc[(j - 1) * 3 + color + lLineBytes];
		Pixels[7] = bpSrc[(j) * 3 + color + lLineBytes];
		Pixels[8] = bpSrc[(j + 1) * 3 + color + lLineBytes];
	}


}
/***算术平均滤波核心算法***/
int Arithmetic_filtering(int* Pixels)
{
	int Arithmetic_result = 0;
	Arithmetic_result = Pixels[0] + Pixels[1] + Pixels[2] + Pixels[3] + Pixels[4] + Pixels[5] + Pixels[6] + Pixels[7] + Pixels[8];
	Arithmetic_result /= 9;
	return Arithmetic_result;
}
/*************************************************************************
* 函数名称：HGLOBAL SSJZtogramProcess(LPSTR lpDIB)
* 参数:lpDIB 原图像指针
*	该函数用来对图像进行算术均值滤波处理。
*/
HGLOBAL SSJZtogramProcess(LPSTR lpDIB)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	int Nine_Pixels[9] = { 0 };
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	for (i = 1; i < lHeight - 1; i++)// 模板处理
	{
		bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
		for (j = 1; j < lWidth - 1; j++)
		{
			if (bBitCount == 8)
			{
				GetNinePixels(Nine_Pixels, bpSrc, lLineBytes, j, 3);
				bpDst[j] = Arithmetic_filtering(Nine_Pixels);
			}
			else
			{
				GetNinePixels(Nine_Pixels, bpSrc, lLineBytes, j, scRed);
				bpDst[j * 3 + scRed] = Arithmetic_filtering(Nine_Pixels);

				GetNinePixels(Nine_Pixels, bpSrc, lLineBytes, j, scGreen);
				bpDst[j * 3 + scGreen] = Arithmetic_filtering(Nine_Pixels);

				GetNinePixels(Nine_Pixels, bpSrc, lLineBytes, j, scBlue);
				bpDst[j * 3 + scBlue] = Arithmetic_filtering(Nine_Pixels);
			}
		}
	}
	return hDIB;
}
/****几何平均滤波核心算法******/
int Geometry_filtering(int* Pixels)
{
	double pixels_gemetry = 1;
	int gemetry_int;
	for (int i = 0; i < 9; i++)
	{
		pixels_gemetry *= Pixels[i];

	}
	pixels_gemetry = pow(pixels_gemetry, 1.0 / 9);
	gemetry_int = (int)pixels_gemetry;
	gemetry_int = gemetry_int;
	return gemetry_int;
}
/*************************************************************************
* 函数名称：HGLOBAL JHJZtogramProcess(LPSTR lpDIB)
* 参数:lpDIB 原图像指针
*	该函数用来对图像进行几何滤波处理。
*/
HGLOBAL JHJZtogramProcess(LPSTR lpDIB)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	int Nine_Pixels[9] = { 0 };
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	for (i = 1; i < lHeight - 1; i++)// 模板处理
	{
		bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
		for (j = 1; j < lWidth - 1; j++)
		{
			if (bBitCount == 8)
			{
				GetNinePixels(Nine_Pixels, bpSrc, lLineBytes, j, 3);
				bpDst[j] = Geometry_filtering(Nine_Pixels);
			}
			else
			{

				GetNinePixels(Nine_Pixels, bpSrc, lLineBytes, j, scRed);
				bpDst[j * 3 + scRed] = Geometry_filtering(Nine_Pixels);

				GetNinePixels(Nine_Pixels, bpSrc, lLineBytes, j, scGreen);
				bpDst[j * 3 + scGreen] = Geometry_filtering(Nine_Pixels);

				GetNinePixels(Nine_Pixels, bpSrc, lLineBytes, j, scBlue);
				bpDst[j * 3 + scBlue] = Geometry_filtering(Nine_Pixels);

			}
		}
	}
	return hDIB;
}
/*************************************************************************
* 函数名称：HGLOBAL ZhognzhitogramProcess(LPSTR lpDIB)
* 参数:lpDIB 原图像指针
*	该函数用来对图像进行中值滤波处理。
*/
HGLOBAL ZhognzhitogramProcess(LPSTR lpDIB)
{

	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	int Lenght = 9;
	BYTE* temp = new BYTE[Lenght];
	char a[9] = { 0,1,0,1,1,1,0,1,0 };
	int mm = 0, k = -1, t = -1, y = 0;
	for (i = 1; i < lHeight - 1; i++)// 模板处理
	{
		bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
		for (j = 1; j < lWidth - 1; j++)
		{
			if (bBitCount == 8)
			{
				y = 0;
				for (k = -1;k<2;k++)
				{
					bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
					for (t = -1;t<2;t++)
					{
						temp[y] = bpSrc[(j + t)];
						y++;
					}
				}
				bpDst[j] = PaiXu(temp, Lenght);
			}
			else
			{
				for (mm = 0;mm<3;mm++)
				{
					y = 0;
					for (k = -1;k<2;k++)
					{
						bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
						for (t = -1;t<2;t++)
						{
							temp[y] = bpSrc[(j + t) * 3 + mm];
							y++;
						}
					}
					bpDst[j * 3 + mm] = PaiXu(temp, Lenght);
				}
			}
		}
	}
	return hDIB;
}

/*************************************************************************
*
* 函数名称：
HGLOBAL YuzhitogramProcess(LPSTR lpDIB, int yuzhi)
阈值处理
* 参数:
*	LPSTR	lpDIB	- 指向DIB对象的指针
*
* 返回值:
*	LPSTR			- 指向DIB调色板的起始位置
*
* 说明:
*	该函数计算DIB中调色板的起始位置，并返回指向它的指针。
************************************************************************/
HGLOBAL YuzhitogramProcess(LPSTR lpDIB, int yuzhi)
{

	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	int junzhi;
	for (i = 0; i<lHeight; i++)
	{
		bpDst = (BYTE*)bpNewDIBBits + lNewLineBytes*i;
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*i;// 指向本行的象素指针
		for (j = 0; j<lWidth; j++)
		{
			if (bBitCount == 8)
			{
				bpDst[j]= bpSrc[j] > yuzhi ? 255 : 0;
			}
			else
			{
				junzhi = (bpSrc[j * 3 + scBlue] + bpSrc[j * 3 + scGreen] + bpSrc[j * 3 + scRed]) / 3;
				bpDst[j * 3 + scBlue] = bpDst[j * 3 + scGreen] = bpDst[j * 3 + scRed] = junzhi > yuzhi ? 255 : 0;
			}
		}
	}
	return hDIB;
}

/*************************************************************************
*
* 函数名称：
*	GeoProcess()
*
* 参数:
*	LPSTR	lpDIB		- 指向DIB的指针
*
* 返回值:
*	HGLOBAL				- 成功返回新图像的句柄，否则返回NULL。
*
* 说明:
*	该函数用来对图像进行几何处理。
*
**************************************************************************/

HGLOBAL GeoProcess(LPSTR lpDIB)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}

	// DIB图像的颜色位数
	BYTE bBitCount;

	// 源DIB图像的宽度和高度
	LONG lWidth;
	LONG lHeight;

	// 几何处理后DIB图像的宽度和高度
	LONG lNewWidth;
	LONG lNewHeight;

	// 几何处理后DIB图像每行的字节数
	LONG lNewLineBytes;

	// 指向源DIB图像的指针
	BYTE *bpDIBBits;

	// 几何处理后新DIB图像句柄
	HDIB hDIB;

	// 指向几何处理DIB图像对应像素的指针
	BYTE *bpDst;

	// 指向几何处理DIB图像的指针
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	// 指向BITMAPINFOHEADER结构的指针（Win3.0）
	LPBITMAPINFOHEADER lpbmi;

	// 指向BITMAPCOREHEADER结构的指针
	LPBITMAPCOREHEADER lpbmc;

	// 循环变量（像素在新DIB图像中的坐标）
	LONG i;
	LONG j;

	// 像素在源DIB图像中的坐标
	double i0;
	double j0;

	// DIB图像每行的字节数
	LONG lLineBytes;

	// 找到源DIB图像像素起始位置
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);

	// 获取DIB图像的宽度和高度
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);

	// 获取DIB图像的颜色位数
	bBitCount = DIBBitCount(lpDIB);

	// 计算DIB图像每行的字节数
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	// 计算新DIB图像实际宽度和高度
	//lNewWidth=f(lWidth, lHeight);
	//lNewHeight=f(lWidth, lHeight);
	lNewWidth = lWidth;
	lNewHeight = lHeight;

	// 计算新DIB图像每行的字节数
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	// 分配内存，以保存新DIB图像
	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));

	// 判断是否内存分配失败
	if (hDIB == NULL)
	{
		// 分配内存失败
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}

	// 锁定内存
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);

	// 复制DIB图像信息头和调色板
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));

	// 找到新DIB图像像素起始位置
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);

	// 获取指针
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	// 更新DIB图像中DIB图像的高度和宽度
	if (IS_WIN30_DIB(lpNewDIB))
	{
		// 对于Windows 3.0 DIB图像
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		// 对于其它格式的DIB图像
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	if (bBitCount == 8)
	{
		// 对单通道色图
		for (i = 0; i<lNewHeight; i++)
		{
			// 指向本行的像素指针
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);

			// 计算该像素在源DIB图像中的坐标
			//i0=f(i);
			i0 = i;

			for (j = 0; j<lNewWidth; j++)
			{
				// 计算该像素在源DIB图像中的坐标
				//j0=f(j);
				j0 = j;

				// 判断是否在源图范围内
				if (j0 >= -1.0 && j0<(double)lWidth && i0 >= -1.0 && i0<(double)lHeight)
				{
					bpDst[j] = (BYTE)IF_BilinearInterpolation((LPSTR)bpDIBBits, bBitCount, lWidth, lHeight, j0, i0);
				}
				else
				{
					// 对于源图中没有的像素，直接赋值为bwmDIBWhite
					bpDst[j] = (BYTE)255;
				}
			}
		}
	}
	else
	{
		// 对三通道色图

		for (i = 0; i<lNewHeight; i++)
		{
			// 指向本行的像素指针
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);

			// 计算该像素在源DIB图像中的坐标
			//i0=f(i);
			i0 = i;

			for (j = 0; j<lNewWidth; j++)
			{
				// 计算该像素在源DIB图像中的坐标
				//j0=f(j);
				j0 = j;

				// 判断是否在源图范围内
				if (j0 >= -1.0 && j0<(double)lWidth && i0 >= -1.0 && i0<(double)lHeight)
				{
					LONG lTmpRGB = IF_BilinearInterpolation((LPSTR)bpDIBBits, bBitCount, lWidth, lHeight, j0, i0);
					bpDst[j * 3 + scBlue] = (BYTE)(lTmpRGB >> 16);
					bpDst[j * 3 + scGreen] = (BYTE)((lTmpRGB&((LONG)255 << 8)) >> 8);
					bpDst[j * 3 + scRed] = (BYTE)(lTmpRGB&(LONG)255);
				}
				else
				{
					// 对于源图中没有的像素，直接赋值为bwmDIBWhite
					bpDst[j * 3 + scBlue] = bpDst[j * 3 + scGreen] = bpDst[j * 3 + scRed] = (BYTE)255;
				}
			}
		}
	}

	return hDIB;
}

/*

平移
*/
HGLOBAL PY_GeoProcess(LPSTR lpDIB, unsigned int hang)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	LPSTR lpDIBBits;
	HDIB hDIB;
	BYTE *bpDst, *bpSrc;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;
	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	LONG lLineBytes;
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);

	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	lNewWidth = lWidth;
	lNewHeight = lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));
	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	//lpDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);

	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	//bpDIBBits = (BYTE*)FindDIBBits((LPSTR)lpDIB);
	lpDIBBits = FindDIBBits(lpDIB);

	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;
	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	if (bBitCount == 8)
	{
		for (i = 0; i<lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*i;
			for (j = 0; j<lNewWidth; j++)
			{
			
					if (i<(LONG)hang)
					{
						bpDst[j]=255;
					}
					else
					{
						bpSrc = (BYTE*)lpDIBBits + lLineBytes*(i - hang);
						bpDst[j] = bpSrc[j];
		
					}
				
			}
		}
	}
	else
	{
		for (i = 0; i<lNewHeight; i++)
		{
			bpDst = (BYTE*)bpNewDIBBits + lNewLineBytes*i;
			for (j = 0; j<lNewWidth; j++)
			{
				if (i<(LONG)hang)
				{
					bpDst[j * 3 + scBlue] = bpDst[j * 3 + scGreen] = bpDst[j * 3 + scRed] = (BYTE)255;
				}
				else
				{
					bpSrc = (BYTE*)lpDIBBits + lLineBytes*(i - hang);
					bpDst[j * 3 + scBlue] = bpSrc[j * 3 + scBlue];
					bpDst[j * 3 + scGreen] = bpSrc[j * 3 + scGreen];
					bpDst[j * 3 + scRed] = bpSrc[j * 3 + scRed];
				}
			}
		}
	}
	return hDIB;
}

/*
循环平移
*/
HGLOBAL XHPY_GeoProcess(LPSTR lpDIB, unsigned int hang)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *bpLst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;
	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	LONG lLineBytes;
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	lNewWidth = lWidth;
	lNewHeight = lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));
	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;
	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	if (bBitCount == 8)
	{

		for (i = 0; i<lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*i;
			bpLst = bpDIBBits + lNewLineBytes*((i + hang) % lNewHeight);
			for (j = 0; j<lNewWidth; j++)
			{
				bpDst[j] = bpLst[j];
			}
		}
	}
	else
	{
		for (i = 0; i<lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*i;
			bpLst = bpDIBBits + lNewLineBytes*((i + hang) % lNewHeight);
			for (j = 0; j<lNewWidth; j++)
			{
				bpDst[j * 3 + scBlue] = bpLst[j * 3 + scBlue];
				bpDst[j * 3 + scGreen] = bpLst[j * 3 + scGreen];
				bpDst[j * 3 + scRed] = bpLst[j * 3 + scRed];
			}
		}
	}
	return hDIB;
}
#define PI 3.1415926
/*************************************************************************
*
* 函数名称：
HGLOBAL XZ_GeoProcess(LPSTR lpDIB, double du)
*
* 参数:
*	LPSTR	lpDIB		- 指向DIB的指针
*
* 返回值:
*	HGLOBAL				- 成功返回新图像的句柄，否则返回NULL。
*
* 说明:
*	该函数用来对图像进行旋转处理。
*
**************************************************************************/
HGLOBAL XZ_GeoProcess(LPSTR lpDIB, double du)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	LPSTR bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *bpSrc;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;
	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	LONG lLineBytes;
	bpDIBBits =FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	lNewWidth = lWidth;
	lNewHeight = lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));
	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;
	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	double x0 = 0, y0 = 0, x1 = 0, y1 = 0;
	du = (du / 180)*PI;

	for (i = 0; i < lNewHeight; i++)
	{
		bpDst = bpNewDIBBits + lNewLineBytes*(lHeight - 1 - i);
		for (j = 0; j < lNewWidth; j++)
		{
			x0 = (j - (lWidth / 2))*cos(du) - (i - (lHeight / 2))*sin(du);
			y0 = (j - (lWidth / 2))*sin(du) + (i - (lHeight / 2))*cos(du);
			x1 = (lNewWidth / 2) + x0;
			y1 = (lNewHeight / 2) + y0;
			
			if (bBitCount == 8)
			{
				if ((y1 < lHeight) && (y1 >= 0) && (x1 < lWidth) && (x1 >= 0))
				{
					bpSrc = SXXZZ(lLineBytes, bpDIBBits, lHeight, lWidth, bBitCount, y1, x1);
					bpDst[j] = bpSrc[0];

				}
				else
				{
					bpDst[j] = 255;
				}
			}
			else
			{
				if ((y1 < lHeight) && (y1 >= 0) && (x1 < lWidth) && (x1 >= 0))
				{
					bpSrc = SXXZZ(lLineBytes, bpDIBBits, lHeight, lWidth, bBitCount, y1, x1);
					bpDst[j * 3 + scBlue] = bpSrc[scBlue];
					bpDst[j * 3 + scGreen] = bpSrc[scGreen];
					bpDst[j * 3 + scRed] = bpSrc[scRed];
				}
				else
				{
					bpDst[j * 3 + scBlue] = bpDst[j * 3 + scGreen] = bpDst[j * 3 + scRed] = 255;
				}
			}
		}
	}
	return hDIB;
}
/**************
双线性差值函数
**************/
BYTE * SXXZZ(LONG lLineBytes, LPSTR lpDIBBits, LONG lHeight, LONG lWidth, BYTE bBitCount, double i1, double j1)
{
	BYTE *Src;
	BYTE temp[3] = { 255 };
	double temp2[3] = { 0 }, temp1[3] = { 0 }, temp4[3] = { 0 }, temp3[3] = { 0 };
	double Result1[3], Result2[3];
	LONG j = 0, i = 0;
	i = (LONG)i1;
	j = (LONG)j1;
	int m = 0;
	if (bBitCount != 8 && bBitCount != 24)
	{
		AfxMessageBox("图像不符合8位图或24位图", MB_OK);
		return  FALSE;
	}
	if (bBitCount == 8)
	{
		if ((i < lHeight - 1) && (j < lWidth - 1))
		{
			Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - i);
			temp3[0] = Src[j];
			temp4[0] = Src[1 + j];
			temp1[0] = (temp4[0] * (j1 - j) + temp3[0] * (j + 1 - j1));
			Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - (i + 1));

			temp3[0] = Src[j];
			temp4[0] = Src[1 + j];
			temp2[0] = (temp4[0] * (j1 - j) + temp3[0] * (j + 1 - j1));
			Result1[0] = (temp2[0] * (i1 - i) + temp1[0] * (i + 1 - i1));

			Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - i);
			temp3[0] = Src[j];
			Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - (i + 1));
			temp4[0] = Src[j];
			temp1[0] = (temp4[0] * (i1 - i) + temp3[0] * (i + 1 - i1));
			Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - i);
			temp3[0] = Src[1 + j];
			Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - (i + 1));
			temp4[0] = Src[1 + j];
			temp2[0] = (temp4[0] * (i1 - i) + temp3[0] * (i + 1 - i1));

			Result2[0] = (temp2[0] * (j1 - j) + temp1[0] * (j + 1 - j1));
			temp[0] = (BYTE)((Result2[0] + Result1[0]) / 2);
		}
		else
		{
			if ((i > lHeight - 1) && (j < lWidth - 1))
			{
				Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - i);
				temp3[0] = Src[j];
				temp4[0] = Src[1 + j];
				temp1[0] = (temp4[0] * (j1 - j) + temp3[0] * (j + 1 - j1));
				temp[0] = (BYTE)temp1[0];
			}
			if ((i < lHeight - 1) && (j > lWidth - 1))
			{
				Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - i);
				temp3[0] = Src[j];
				Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - (i + 1));
				temp4[0] = Src[j];
				temp1[0] = (temp4[0] * (i1 - i) + temp3[0] * (i + 1 - i1));
				temp[0] = (BYTE)temp1[0];
			}
			if ((i > lHeight - 1) && (j > lWidth - 1))
			{
				Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - i);
				temp[0] = Src[j];
			}
		}
	}
	if (bBitCount == 24)
	{
		if ((i<lHeight-1)&&(j<lWidth-1))
		{
			Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - i);
			for (m = 0;m < 3;m++)
			{
				temp3[m] = Src[j * 3 + m];
				temp4[m] = Src[(1 + j) * 3 + m];
				temp1[m] = (temp4[m] * (j1 - j) + temp3[m] * (j + 1 - j1));
			}
			Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - (i + 1));
			for (m = 0;m < 3;m++)
			{
				temp3[m] = Src[j * 3 + m];
				temp4[m] = Src[(1 + j) * 3 + m];
				temp2[m] = (temp4[m] * (j1 - j) + temp3[m] * (j + 1 - j1));
			}
			for (m = 0;m < 3;m++)
			{
				Result1[m] = (temp2[m] * (i1 - i) + temp1[m] * (i + 1 - i1));
			}

			for (m = 0;m < 3;m++)
			{
				Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - i);
				temp3[m] = Src[j * 3 + m];
				Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - (i + 1));
				temp4[m] = Src[j * 3 + m];
				temp1[m] = (temp4[m] * (i1 - i) + temp3[m] * (i + 1 - i1));
			}
			for (m = 0;m < 3;m++)
			{
				Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - i);
				temp3[m] = Src[(1 + j) * 3 + m];
				Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - (i + 1));
				temp4[m] = Src[(1 + j) * 3 + m];
				temp2[m] = (temp4[m] * (i1 - i) + temp3[m] * (i + 1 - i1));
			}
			for (m = 0;m < 3;m++)
			{
				Result2[m] = (temp2[m] * (j1 - j) + temp1[m] * (j + 1 - j1));
			}
			for (m = 0;m < 3;m++)
			{
				temp[m] = (BYTE)((Result2[m] + Result1[m]) / 2);
			}
		}
		else
		{
			if ((i > lHeight - 1) && (j < lWidth - 1))
			{
				Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - i);
				for (m = 0;m < 3;m++)
				{
					temp3[m] = Src[j * 3 + m];
					temp4[m] = Src[(1 + j) * 3 + m];
					temp1[m] = (temp4[m] * (j1 - j) + temp3[m] * (j + 1 - j1));
				}
				for (m = 0;m < 3;m++)
				{
					temp[m] = (BYTE)temp1[m];
				}
			}
			if ((i < lHeight - 1) && (j > lWidth - 1))
			{
				for (m = 0;m < 3;m++)
				{
					Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - i);
					temp3[m] = Src[j * 3 + m];
					Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - (i + 1));
					temp4[m] = Src[j * 3 + m];
					temp1[m] = (temp4[m] * (i1 - i) + temp3[m] * (i + 1 - i1));
				}
				for (m = 0;m < 3;m++)
				{
					temp[m] = (BYTE)temp1[m];
				}
			}
			if ((i > lHeight - 1) && (j > lWidth - 1))
			{
				Src = (BYTE*)lpDIBBits + lLineBytes*((lHeight - 1) - i);
				for (m = 0;m < 3;m++)
				{
					temp[m] = Src[j * 3 + m];
				}
			}
		}
		
	}
	return temp;
}
/*************************************************************************
*
* 函数名称：
HGLOBAL HistAvetogramProcess(LPSTR lpDIB)
*
* 参数:
*	LPSTR	lpDIB		- 指向DIB的指针
*
* 返回值:
*	HGLOBAL				- 成功返回新图像的句柄，否则返回NULL。
*
* 说明:
*	该函数用来对图像进行直方图处理。
*
**************************************************************************/
HGLOBAL HistAvetogramProcess(LPSTR lpDIB)
{

	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	LPSTR lpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *bpSrc;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;
	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	LONG lLineBytes;
	lpDIBBits = FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	lNewWidth = lWidth;
	lNewHeight = lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));
	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;
	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	int m = 0;
	LONG map[256] = { 0 };
	unsigned char temp = 0;
	for (i = 0;i<lHeight;i++)
	{
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);// 指向本行的象素指针
		for (j = 0; j < lWidth; j++)
		{
			if (bBitCount == 8)
			{
				temp = bpSrc[j] ;
				map[temp]++;
			}
			else
			{
				temp = (bpSrc[j * 3 + scBlue] + bpSrc[j * 3 + scGreen] + bpSrc[j * 3 + scRed]) / 3;
				map[temp]++;
			}
		}
	}
	for (i = 0; i < lNewHeight; i++)
	{
		bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);// 指向本行的象素指针
		for (j = 0; j < lNewWidth; j++)
		{
			if (bBitCount == 8)
			{
				temp = bpSrc[j];
				bpDst[j] = (unsigned char)(((double)map[temp] / (double)(lNewWidth*lNewHeight)) * 255);
			}
			else
			{
				temp = (bpSrc[j * 3 + scBlue] + bpSrc[j * 3 + scGreen] + bpSrc[j * 3 + scRed]) / 3;
				bpDst[j * 3 + scBlue] = bpDst[j * 3 + scGreen] = bpDst[j * 3 + scRed] = (unsigned char)(((double)map[temp] / (double)(lNewWidth*lNewHeight)) * 255);
			}
		}
	}
	return hDIB;
}
/*************************************************************************
*
* 函数名称：
BOOL HistFazhiProcess(LPSTR lpDIBBits, BYTE bBitCount, LONG lWidth, LONG lHeight, int nThre)
*
* 参数:
*	
*
* 返回值:
*	
*
* 说明:
*	该函数用来对图像进行直方图阈值处理。
*
**************************************************************************/
BOOL HistFazhiProcess(LPSTR lpDIBBits, BYTE bBitCount, LONG lWidth, LONG lHeight, int nThre)
{
	if (lpDIBBits == NULL || (bBitCount != 8 && bBitCount != 24) || lWidth <= 0 || lHeight <= 0)
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE *bpSrc;
	LONG i;
	LONG j;
	LONG lLineBytes;
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	for (i = 0; i<lHeight; i++)
	{
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*i;
		for (j = 0; j<lWidth; j++)
		{
			if (bBitCount == 8)
			{
				if (bpSrc[j]>nThre)bpSrc[j] = 255; else bpSrc[j] = 0;
			}
			else
			{
				if (bpSrc[j * 3 + scBlue]>nThre)bpSrc[j * 3 + scBlue] = 255; else bpSrc[j * 3 + scBlue] = 0;
				if (bpSrc[j * 3 + scGreen]>nThre)bpSrc[j * 3 + scGreen] = 255; else bpSrc[j * 3 + scGreen] = 0;
				if (bpSrc[j * 3 + scRed]>nThre)bpSrc[j * 3 + scRed] = 255; else bpSrc[j * 3 + scRed] = 0;
			}
		}
	}

	return TRUE;
}
/*************************************************************************
*
* 函数名称：
BOOL HistXxingProcess(LPSTR lpDIBBits, BYTE bBitCount, LONG lWidth, LONG lHeight, double dK, int nB)
*
* 参数:
*
*
* 返回值:
*
*
* 说明:
*	该函数用来对图像进行直方图进行线性变换处理处理。
*
**************************************************************************/
BOOL HistXxingProcess(LPSTR lpDIBBits, BYTE bBitCount, LONG lWidth, LONG lHeight, double dK, int nB)
{
	if (lpDIBBits == NULL || (bBitCount != 8 && bBitCount != 24) || lWidth <= 0 || lHeight <= 0)
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE *bpSrc;
	LONG i;
	LONG j;
	LONG x;
	LONG lLineBytes;
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	for (i = 0; i<lHeight; i++)
	{
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*i;
		for (j = 0; j<lWidth; j++)
		{
			if (bBitCount == 8)
			{
				bpSrc[j] = bpSrc[j] * dK + nB;
			}
			else
			{
				x = bpSrc[j * 3 + scBlue] * dK + nB;
				if (x > 255)x = 255;
				if (x < 0)x = 0;
				bpSrc[j * 3 + scBlue] = x;
				x = bpSrc[j * 3 + scGreen] * dK + nB;
				if (x > 255)x = 255;
				if (x < 0)x = 0;
				bpSrc[j * 3 + scGreen] = x;
				x = bpSrc[j * 3 + scRed] * dK + nB;
				if (x > 255)x = 255;
				if (x < 0)x = 0;
				bpSrc[j * 3 + scRed] = x;
			}
		}
	}
	return TRUE;
}
/*************************************************************************
*
* 函数名称：
HGLOBAL BianJietogramProcess(LPSTR lpDIB)*
* 参数:
*	LPSTR	lpDIB		- 指向DIB的指针
*
* 返回值:
*	HGLOBAL				- 成功返回新图像的句柄，否则返回NULL。
*
* 说明:
*	该函数用来对图像进行边界处理。
*
**************************************************************************/

HGLOBAL BianJietogramProcess(LPSTR lpDIB)
{

	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	int mm = 0, k = -1, t = -1, ss = 0;
	for (i = 1; i < lHeight - 1; i++)// 模板处理
	{
		bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
		for (j = 1; j < lWidth - 1; j++)
		{
			if (bBitCount == 8)
			{
				ss = 0;
				for (k = -1;k < 2;k++)
				{
					bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
					for (t = -1;t < 2;t++)
						ss += t*bpSrc[(j + t)];
				}
				bpDst[j] = BYTE(abs(ss));
			}
			else
			{
				for (mm = 0;mm < 3;mm++)
				{
					ss = 0;
					for (k = -1;k < 2;k++)
					{
						bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
						for (t = -1;t < 2;t++)
							ss += t*bpSrc[(j + t) * 3 + mm];
					}
					bpDst[j * 3 + mm] = BYTE(abs(ss));
				}
			}
		}
	}
	return hDIB;
}
/*************************************************************************
* 函数名称：HGLOBAL KYStogramProcess(LPSTR lpDIB)
* 参数:
*	LPSTR	lpDIBBits	- 指向DIB数据区的指针
*	BYTE	bBitCount	- 图像的颜色位数
*	LONG	lWidth		- 源图像宽度（象素数）
*	LONG	lHeight		- 源图像高度（象素数）
* 返回值:
*	BOOL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数用来对图像进行开运算。
**************************************************************************/
/****以此时像素点为中心取一个十字心五个像素值*****/
int Inflation_algorithm(int* Pixels, BYTE *bpSrc, LONG lLineBytes, LONG j, int color)
{
	int now_Pixel_value = 0;
	if (color>2)
	{
		//  灰度图
		Pixels[0] = bpSrc[j - lLineBytes];
		Pixels[1] = bpSrc[j - 1];
		Pixels[2] = bpSrc[j];
		Pixels[3] = bpSrc[j + 1];
		Pixels[4] = bpSrc[j + lLineBytes];
	}
	else
	{
		// R G B 图
		Pixels[0] = bpSrc[(j) * 3 + color - lLineBytes];
		Pixels[1] = bpSrc[(j - 1) * 3 + color];
		Pixels[2] = bpSrc[j * 3 + color];
		Pixels[3] = bpSrc[(j + 1) * 3 + color];
		Pixels[4] = bpSrc[(j) * 3 + color + lLineBytes];
	}
	if (Pixels[0] == 0 || Pixels[1] == 0 || Pixels[2] == 0 || Pixels[3] == 0 || Pixels[4] == 0)
		now_Pixel_value = 0;
	else
		now_Pixel_value = 255;
	return now_Pixel_value;
}
HGLOBAL KYStogramProcess(LPSTR lpDIB)
{

	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;
	int Five_Pixels[5] = { 0 };
	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	int mm = 0, k = -1, t = -1;
	for (i = 1; i < lHeight - 1; i++)// 模板处理
	{
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
		bpDst = bpNewDIBBits + lLineBytes*(lHeight - 1 - i);
		for (j = 1;j< lWidth - 1;j++)
		{
			if (bBitCount == 8)
			{
				bpDst[j] = Inflation_algorithm(Five_Pixels, bpSrc, lLineBytes, j, 3);
			}
			else
			{
				bpDst[j * 3 + scRed] = Inflation_algorithm(Five_Pixels, bpSrc, lLineBytes, j, scRed);
				bpDst[j * 3 + scGreen] = Inflation_algorithm(Five_Pixels, bpSrc, lLineBytes, j, scGreen);
				bpDst[j * 3 + scBlue] = Inflation_algorithm(Five_Pixels, bpSrc, lLineBytes, j, scBlue);
			}
		}
	}
	return hDIB;
}
/*************************************************************************
* 函数名称：HGLOBAL BasicErosionForBinary(LPSTR lpDIB)
* 参数:
*	LPSTR	lpDIBBits	- 指向DIB数据区的指针
*	BYTE	bBitCount	- 图像的颜色位数
*	LONG	lWidth		- 源图像宽度（象素数）
*	LONG	lHeight		- 源图像高度（象素数）
* 返回值:
*	BOOL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数用来对图像进行腐蚀。
**************************************************************************/
HGLOBAL BasicErosionForBinary(LPSTR lpDIB)
{

	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	int mm = 0, k = -1, t = -1;
	char flag = 0;
	for (i = 1; i < lHeight - 1; i++)
	{
		bpDst = (BYTE*)bpNewDIBBits + lLineBytes*(lHeight - 1 - i);
		for (j = 1;j< lWidth - 1;j++)
		{
			if (bBitCount == 8)
			{
				flag = 0;
				if (!bpDst[j])
				{
					for (k = -1;k < 2;k++)
					{
						bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
						if (k != 0)
						{
							if (bpSrc[j] != 0)
							{
								flag = 1;
								goto next2;
							}
						}
						else
						{
							for (t = -1;t < 2;t++)
							{
								if (t != 0)
								{
									if (bpSrc[(j + t)] != 0)
									{
										flag = 1;
										goto next2;
									}
								}
							}
						}
					}
				}
				next2:	if (flag)
				{
					bpDst[j] = 255;
				}
			}
			else
			{
				for (mm = 0;mm < 3;mm++)
				{
					flag = 0;
					if (!bpDst[j * 3 + mm])
					{
						for (k = -1;k < 2;k++)
						{
							bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
							if (k != 0)
							{
								if (bpSrc[j * 3 + mm] != 0)
								{
									flag = 1;
									goto next3;
								}
							}
							else
							{
								for (t = -1;t < 2;t++)
								{
									if (t != 0)
									{
										if (bpSrc[(j + t) * 3 + mm] != 0)
										{
											flag = 1;
											goto next3;
										}
									}
								}
							}
						}
					}
				     next3:	if (flag)
				{
					bpDst[j * 3 + mm] = 255;
				}
				}
			}
		}
	}
	return hDIB;
}
/*************************************************************************
* 函数名称：HGLOBAL BasicErosionForBinary(LPSTR lpDIB)
* 参数:
*	LPSTR	lpDIBBits	- 指向DIB数据区的指针
*	BYTE	bBitCount	- 图像的颜色位数
*	LONG	lWidth		- 源图像宽度（象素数）
*	LONG	lHeight		- 源图像高度（象素数）
* 返回值:
*	BOOL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数用来对图像进行膨胀。
**************************************************************************/
HGLOBAL BasicDilationForBinary(LPSTR lpDIB)
{

	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	
	char flag = 0;
	int mm = 0, k = -1, t = -1;
	for (i = 1; i < lNewHeight - 1; i++)
	{
		bpDst = (BYTE*)bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
		for (j = 1;j< lNewWidth - 1;j++)
		{
			if (bBitCount == 8)
			{
				flag = 0;
				if (bpDst[j])
				{
					for (k = -1;k < 2;k++)
					{
						bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
						if (k != 0)
						{
							if (bpSrc[j] == 0)
							{
								flag = 1;
								goto next1;
							}
						}
						else
						{
							for (t = -1;t < 2;t++)
							{
								if (t != 0)
								{
									if (bpSrc[(j + t)] == 0)
									{
										flag = 1;
										goto next1;
									}
								}
							}
						}
					}
				}
				next1:	if (flag)
				{
					bpDst[j] = 0;
				}
			}
			else
			{
				for (mm = 0;mm < 3;mm++)
				{
					flag = 0;
					if (bpDst[j * 3 + mm])
					{
						for (k = -1;k < 2;k++)
						{
							bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
							if (k != 0)
							{
								if (bpSrc[j * 3 + mm] == 0)
								{
									flag = 1;
									goto next;
								}
							}
							else
							{
								for (t = -1;t < 2;t++)
								{
									if (t != 0)
									{
										if (bpSrc[(j + t) * 3 + mm] == 0)
										{
											flag = 1;
											goto next;
										}
									}
								}
							}
						}
					}
				next:	if (flag)
				{
					bpDst[j * 3 + mm] = 0;
				}
				}
			}
		}
	}
	return hDIB;
}
/*开运算 先做腐蚀 在做膨胀 两者次数相同*/
HGLOBAL BinaryOpen(LPSTR lpDIB)
{
	HGLOBAL MyhDIB = NULL, MyhDIB2 = NULL;
	MyhDIB=BasicErosionForBinary(lpDIB);
	LPSTR lpDIB_1=NULL;
	lpDIB_1 =(LPSTR)::GlobalLock(MyhDIB);
	if (!lpDIB_1)
	{
		MyhDIB2 = BasicDilationForBinary(lpDIB_1);
		LocalUnlock(lpDIB_1);// 释放内存
		LocalFree(MyhDIB);
		if (!MyhDIB2)
			return MyhDIB2;
		else
			return NULL;
	}
	LocalUnlock(lpDIB_1);// 释放内存
	LocalFree(MyhDIB);
	return NULL;
}
/*
闭运算 先做膨胀 在做腐蚀 两者次数相等
*/
HGLOBAL BinaryClose(LPSTR lpDIB)
{
	HGLOBAL MyhDIB = NULL, MyhDIB2 = NULL;
	MyhDIB = BasicDilationForBinary(lpDIB);
	LPSTR lpDIB_1 = NULL;
	lpDIB_1 = (LPSTR)::GlobalLock(MyhDIB);
	if (!lpDIB_1)
	{
		MyhDIB2 = BasicErosionForBinary(lpDIB_1);
		LocalUnlock(lpDIB_1);// 释放内存
		LocalFree(MyhDIB);
		if (!MyhDIB2)
			return MyhDIB2;
		else
			return NULL;
	}
	LocalUnlock(lpDIB_1);// 释放内存
	LocalFree(MyhDIB);
	return NULL;
}
HGLOBAL FillHoles(LPSTR lpDIB,CPoint point)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;

	}
	stack <POINT>point_stack;
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;
	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;
	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	for (i = 1; i < lHeight - 1; i++)// 模板处理
	{
		bpDst = bpNewDIBBits + lLineBytes*(lHeight - 1 - i);
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
		for (j = 0; j < lWidth; j++)
		{
			bpDst[j] = bpSrc[j];
		}
	}
	//  鼠标指定点行数
	bpDst = bpNewDIBBits + lLineBytes*(lHeight - 1 - point.y);
	//  鼠标指定点的像素为白时
	if (bpDst[point.x] == 255)
	{
		point_stack.push(point);
		while (!point_stack.empty())
		{
			POINT button_point;
			button_point = point_stack.top();
			bpDst = bpNewDIBBits + lLineBytes*(lHeight - 1 - button_point.y);
			bpDst[button_point.x] = 0;

			point_stack.pop();
			if (((button_point.x > 0) && (button_point.x < lWidth)) || ((button_point.y > 0) && (button_point.y < lHeight)))
			{
				if (bpDst[button_point.x - 1] == 255) { POINT Left_point; Left_point.x = button_point.x - 1; Left_point.y = button_point.y; point_stack.push(Left_point); }
				if (bpDst[button_point.x + 1] == 255) { POINT Right_point; Right_point.x = button_point.x + 1; Right_point.y = button_point.y; point_stack.push(Right_point); }
				bpDst = bpNewDIBBits + lLineBytes*(lHeight - 1 - (button_point.y - 1));
				if (bpDst[button_point.x] == 255) { POINT Upper_point; Upper_point.x = button_point.x; Upper_point.y = button_point.y - 1; point_stack.push(Upper_point); }
				bpDst = bpNewDIBBits + lLineBytes*(lHeight - 1 - (button_point.y + 1));
				if (bpDst[button_point.x] == 255) { POINT Lower_point; Lower_point.x = button_point.x; Lower_point.y = button_point.y + 1; point_stack.push(Lower_point); }
			}


		}
	}
	return hDIB;
}
/*************************************************************************
* 函数名称：HGLOBAL XXtogramProcess(LPSTR lpDIB, double k, double b)
* 参数:
*	LPSTR	lpDIBBits	- 指向DIB数据区的指针
*	BYTE	bBitCount	- 图像的颜色位数
*	LONG	lWidth		- 源图像宽度（象素数）
*	LONG	lHeight		- 源图像高度（象素数）
* 返回值:
*	BOOL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数用来对图像进行线性。
**************************************************************************/
HGLOBAL XXtogramProcess(LPSTR lpDIB , double k, double b)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *bpLst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;
	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	LONG lLineBytes;
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	lNewWidth = lWidth;
	lNewHeight = lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));
	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;
	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	double val;
	BYTE temp[256] = {0};
	for (i = 0; i < 256; i++)
	{
		val = i*k + b;
		if (val > 255)
			val = 255;
		else
			if (val < 0)
				val = 0;
		temp[i] = (BYTE)val;
	}
	if (bBitCount == 8)
	{
		
		for (i = 0; i<lNewHeight; i++)
		{
			bpLst = bpDIBBits + lLineBytes*(lHeight - 1 - i);
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight-1-i);
			for (j = 0; j<lNewWidth; j++)
			{
				bpDst[j] = temp[bpLst[j]];
			}
		}
	}
	else
	{
	 for (i = 0; i<lNewHeight; i++)
			{
				bpLst = bpDIBBits + lLineBytes*(lHeight - 1 - i);
				bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
				for (j = 0; j<lNewWidth; j++)
				{
					bpDst[j * 3 + scBlue] = temp[bpLst[j * 3 + scBlue]];
					bpDst[j * 3 + scGreen] = temp[bpLst[j * 3 + scGreen]];
					bpDst[j * 3 + scRed] = temp[bpLst[j * 3 + scRed]];
				}
			}
	}
	return hDIB;
}
/*************************************************************************
* 函数名称：HGLOBAL BinaryInterEdge(LPSTR lpDIB)
* 参数:

* 说明:
*	该函数用来对图像边界处理。
原图减去腐蚀后的图
**************************************************************************/
HGLOBAL BinaryInterEdge(LPSTR lpDIB)
{

	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *bpSrc;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;
	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	LONG lLineBytes;
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	lNewWidth = lWidth;
	lNewHeight = lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));
	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;
	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	char flag = 0;

	int mm = 0, k = -1, t = -1;
	/*原图的腐蚀*/
	for (i = 0; i < lNewHeight; i++)
	{
		bpDst = (BYTE*)bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
		for (j =0;j< lWidth ;j++)
		{
			if (bBitCount == 8)
			{

				flag = 0;
				if (!bpDst[j])
				{
					for (k = -1;k < 2;k++)
					{
						bpSrc = (BYTE*)bpDIBBits + lLineBytes*(lHeight - 1 - i + k);
						if (k != 0)
						{
							if (bpSrc[j] != 0)
							{
								flag = 1;
								goto next2;
							}
						}
						else
						{
							for (t = -1;t < 2;t++)
							{
								if (t != 0)
								{
									if (bpSrc[(j + t)] != 0)
									{
										flag = 1;
										goto next2;
									}
								}
							}
						}
					}
				}
			next2:	if (flag)
			{
				bpDst[j] = 255;
			}
			}
			else
			{
				for (mm = 0;mm < 3;mm++)
				{
					flag = 0;
					if (!bpDst[j * 3 + mm])
					{
						for (k = -1;k < 2;k++)
						{
							bpSrc = (BYTE*)bpDIBBits + lLineBytes*(lHeight - 1 - i + k);
							if (k != 0)
							{
								if (bpSrc[j * 3 + mm] != 0)
								{
									flag = 1;
									goto next3;
								}
							}
							else
							{
								for (t = -1;t < 2;t++)
								{
									if (t != 0)
									{
										if (bpSrc[(j + t) * 3 + mm] != 0)
										{
											flag = 1;
											goto next3;
										}
									}
								}
							}
						}
					}
				next3:	if (flag)
				{
					bpDst[j * 3 + mm] = 255;
				}
				}
			}
		}
	}
	/*原图减去腐蚀后的图像*/
	for (i = 0; i < lHeight; i++)
	{
		bpDst = (BYTE*)bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
		bpSrc = (BYTE*)bpDIBBits + lLineBytes*(lHeight - 1 - i);
		for (j = 0;j< lNewWidth;j++)
		{
			if (bBitCount == 8)
			{
				bpSrc[j] = 255 + bpSrc[j] - bpDst[j];
			}
			else
			{
				for (mm = 0;mm < 3;mm++)
				{
					bpSrc[j * 3 + mm] = 255 + bpSrc[j * 3 + mm] - bpDst[j * 3 + mm];
				}
			}
		}
	}	
	return hDIB;
}
/*************************************************************************
* 函数名称：HGLOBAL BinaryOutEdge(LPSTR lpDIB)
* 参数:

* 说明:
*	该函数用来对图像边界处理。
膨胀后的图减去原图
**************************************************************************/
HGLOBAL BinaryOutEdge(LPSTR lpDIB)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *bpSrc;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;
	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	LONG lLineBytes;
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	lNewWidth = lWidth;
	lNewHeight = lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));
	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;
	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	char flag = 0;
	int mm = 0, k = -1, t = -1;
	/*对原图进行膨胀*/
	for (i = 0; i < lHeight; i++)
	{
		bpDst = (BYTE*)bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
		for (j = 0;j< lWidth ;j++)
		{
			if (bBitCount == 8)
			{
				flag = 0;
				if (bpDst[j])
				{
					for (k = -1;k < 2;k++)
					{
						bpSrc = (BYTE*)bpDIBBits + lLineBytes*(lHeight - 1 - i + k);
						if (k != 0)
						{
							if (bpSrc[j] == 0)
							{
								flag = 1;
								goto next1;
							}
						}
						else
						{
							for (t = -1;t < 2;t++)
							{
								if (t != 0)
								{
									if (bpSrc[(j + t)] == 0)
									{
										flag = 1;
										goto next1;
									}
								}
							}
						}
					}
				}
				next1:	if (flag)
				{
					bpDst[j] = 0;
				}
			}
			else
			{
				for (mm = 0;mm < 3;mm++)
				{
					flag = 0;
					if (bpDst[j * 3 + mm])
					{
						for (k = -1;k < 2;k++)
						{
							bpSrc = (BYTE*)bpDIBBits + lLineBytes*(lHeight - 1 - i + k);
							if (k != 0)
							{
								if (bpSrc[j * 3 + mm] == 0)
								{
									flag = 1;
									goto next;
								}
							}
							else
							{
								for (t = -1;t < 2;t++)
								{
									if (t != 0)
									{
										if (bpSrc[(j + t) * 3 + mm] == 0)
										{
											flag = 1;
											goto next;
										}
									}
								}
							}
						}
					}
				next:	if (flag)
				{
					bpDst[j * 3 + mm] = 0;
				}
				}
			}
		}
	}
	/*膨胀后的图减去原图*/
	for (i = 0; i < lNewHeight; i++)
	{
		bpDst = (BYTE*)bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
		bpSrc = (BYTE*)bpDIBBits + lLineBytes*(lHeight - 1 - i);
		for (j = 0;j< lWidth;j++)
		{
			if (bBitCount == 8)
			{
				bpDst[j] = 255 - bpSrc[j] + bpDst[j];
			}
			else
			{
				for (mm = 0;mm < 3;mm++)
				{
					bpDst[j * 3 + mm] = 255  -bpSrc[j * 3 + mm] + bpDst[j * 3 + mm];
				}
			}
		}
	}
	//LocalUnlock(lpNewDIB);
	::GlobalUnlock(lpNewDIB);
	return hDIB;
}
HGLOBAL BinaryContour(LPSTR lpDIB)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	LONG i;
	LONG j;
	char flag = 0;
	int mm = 0, k = -1, t = -1;

	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpDIBBits;
	BYTE *bpSrc;
	LONG lLineBytes;
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));


	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;
	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	lNewWidth = lWidth;
	lNewHeight = lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));
	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;
	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	
	/*原图的腐蚀*/
	for (i = 0; i < lNewHeight; i++)
	{
		bpDst = (BYTE*)bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
		for (j = 0;j< lWidth;j++)
		{
			if (bBitCount == 8)
			{

				flag = 0;
				if (!bpDst[j])
				{
					for (k = -1;k < 2;k++)
					{
						bpSrc = (BYTE*)bpDIBBits + lLineBytes*(lHeight - 1 - i + k);
						if (k != 0)
						{
							if (bpSrc[j] != 0)
							{
								flag = 1;
								goto next2;
							}
						}
						else
						{
							for (t = -1;t < 2;t++)
							{
								if (t != 0)
								{
									if (bpSrc[(j + t)] != 0)
									{
										flag = 1;
										goto next2;
									}
								}
							}
						}
					}
				}
			next2:	if (flag)
			{
				bpDst[j] = 255;
			}
			}
			else
			{
				for (mm = 0;mm < 3;mm++)
				{
					flag = 0;
					if (!bpDst[j * 3 + mm])
					{
						for (k = -1;k < 2;k++)
						{
							bpSrc = (BYTE*)bpDIBBits + lLineBytes*(lHeight - 1 - i + k);
							if (k != 0)
							{
								if (bpSrc[j * 3 + mm] != 0)
								{
									flag = 1;
									goto next3;
								}
							}
							else
							{
								for (t = -1;t < 2;t++)
								{
									if (t != 0)
									{
										if (bpSrc[(j + t) * 3 + mm] != 0)
										{
											flag = 1;
											goto next3;
										}
									}
								}
							}
						}
					}
				next3:	if (flag)
				{
					bpDst[j * 3 + mm] = 255;
				}
				}
			}
		}
	}

	LONG lNewWidth_2;
	LONG lNewHeight_2;
	LONG lNewLineBytes_2;
	HDIB hDIB_2;
	BYTE *bpDst_2;
	BYTE *lpNewDIB_2;
	BYTE *bpNewDIBBits_2;
	LPBITMAPINFOHEADER lpbmi_2;
	LPBITMAPCOREHEADER lpbmc_2;

	lNewWidth_2 = lWidth;
	lNewHeight_2 = lHeight;
	lNewLineBytes_2 = (bBitCount == 8 ? WIDTHBYTES(lNewWidth_2 * 8) : WIDTHBYTES(lNewWidth_2 * 24));
	hDIB_2 = (HDIB)::GlobalAlloc(GHND, lNewLineBytes_2*lNewHeight_2 * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB_2 == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB_2 = (BYTE*)::GlobalLock((HGLOBAL)hDIB_2);
	memcpy(lpNewDIB_2, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits_2 = (BYTE*)FindDIBBits((LPSTR)lpNewDIB_2);
	lpbmi_2 = (LPBITMAPINFOHEADER)lpNewDIB_2;
	lpbmc_2 = (LPBITMAPCOREHEADER)lpNewDIB_2;
	if (IS_WIN30_DIB(lpNewDIB_2))
	{
		lpbmi_2->biWidth = lNewWidth_2;
		lpbmi_2->biHeight = lNewHeight_2;
	}
	else
	{
		lpbmc_2->bcWidth = (unsigned short)lNewWidth_2;
		lpbmc_2->bcHeight = (unsigned short)lNewHeight_2;
	}
	/*原图的膨胀*/
	for (i = 0; i < lHeight; i++)
	{
		bpDst_2 = (BYTE*)bpNewDIBBits_2 + lNewLineBytes_2 *(lNewHeight_2 - 1 - i);
		for (j = 0;j< lWidth;j++)
		{
			if (bBitCount == 8)
			{
				flag = 0;
				if (bpDst_2[j])
				{
					for (k = -1;k < 2;k++)
					{
						bpSrc = (BYTE*)bpDIBBits + lLineBytes*(lHeight - 1 - i + k);
						if (k != 0)
						{
							if (bpSrc[j] == 0)
							{
								flag = 1;
								goto next1;
							}
						}
						else
						{
							for (t = -1;t < 2;t++)
							{
								if (t != 0)
								{
									if (bpSrc[(j + t)] == 0)
									{
										flag = 1;
										goto next1;
									}
								}
							}
						}
					}
				}
			next1:	if (flag)
			{
				bpDst_2[j] = 0;
			}
			}
			else
			{
				for (mm = 0;mm < 3;mm++)
				{
					flag = 0;
					if (bpDst_2[j * 3 + mm])
					{
						for (k = -1;k < 2;k++)
						{
							bpSrc = (BYTE*)bpDIBBits + lLineBytes*(lHeight - 1 - i + k);
							if (k != 0)
							{
								if (bpSrc[j * 3 + mm] == 0)
								{
									flag = 1;
									goto next;
								}
							}
							else
							{
								for (t = -1;t < 2;t++)
								{
									if (t != 0)
									{
										if (bpSrc[(j + t) * 3 + mm] == 0)
										{
											flag = 1;
											goto next;
										}
									}
								}
							}
						}
					}
				next:	if (flag)
				{
					bpDst_2[j * 3 + mm] = 0;
				}
				}
			}
		}
	}
	
	/*膨胀后的图减去腐蚀后的图*/
	for (i = 0; i < lNewHeight; i++)
	{
		bpDst = (BYTE*)bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
		bpDst_2 = (BYTE*)bpNewDIBBits_2 + lNewLineBytes_2*(lNewHeight_2 - 1 - i);
		for (j = 0;j< lNewWidth;j++)
		{
			if (bBitCount == 8)
			{
				bpDst[j] = 255 + bpDst_2[j] - bpDst[j];
			}
			else
			{
				for (mm = 0;mm < 3;mm++)
				{
					bpDst[j * 3 + mm] = 255 + bpDst_2[j * 3 + mm] - bpDst[j * 3 + mm];
				}
			}

		}
	}
	LocalUnlock(lpNewDIB_2);
	LocalUnlock(lpNewDIB);
	LocalFree(hDIB_2);
	return hDIB;
}
//直方图处理
BOOL HistAvetogramProcess_select(LPSTR lpDIBBits, BYTE bBitCount, LONG lWidth, LONG lHeight, int selection)
{
	if (lpDIBBits == NULL || (bBitCount != 8 && bBitCount != 24) || lWidth <= 0 || lHeight <= 0)
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE *bpSrc;
	// 循环变量
	LONG i;
	LONG j;
	int m = 0;
	LONG lLineBytes;// 图像每行的字节数
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));// 计算图像每行的字节数
	LONG map[256] = { 0 };
	unsigned char temp = 0;
	for (i = 0;i < lHeight;i++)
	{
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*i;// 指向本行的象素指针
		for (j = 0; j < lWidth; j++)
		{
			if (bBitCount == 8)
			{
				temp = bpSrc[j];
				map[temp]++;
			}
			else
			{
				temp = (bpSrc[j * 3 + scBlue] + bpSrc[j * 3 + scGreen] + bpSrc[j * 3 + scRed]) / 3;
				map[temp]++;
			}
		}
	}
	for (m = 0;m < 256;m++)
	{
		temp = (unsigned char)(((double)map[m] / (double)(lWidth*lHeight)) * 255);
		map[m] = temp;
	}
	for (i = 0; i < lHeight; i++)
	{
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*i;// 指向本行的象素指针
		for (j = 0; j < lWidth; j++)
		{
			if (bBitCount == 8)
			{
				temp = bpSrc[j ] ;
				bpSrc[j] =(BYTE)map[temp];
			}
			else
			{
				temp = (bpSrc[j * 3 + scBlue] + bpSrc[j * 3 + scGreen] + bpSrc[j * 3 + scRed]) / 3;
				bpSrc[j * 3 + scBlue] = bpSrc[j * 3 + scGreen] = bpSrc[j * 3 + scRed] = (BYTE)map[temp];
			}
		}
	}
	return TRUE;
}
BOOL HistAvetogramProcess_RED(LPSTR lpDIBBits, BYTE bBitCount, LONG lWidth, LONG lHeight)
{
	// 判断输入参数是否有误
	if (lpDIBBits == NULL || (bBitCount != 8 && bBitCount != 24) || lWidth <= 0 || lHeight <= 0)
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	// 指向源图像的指针
	BYTE *bpSrc;
	// 循环变量
	LONG i;
	LONG j;
	int m = 0;
	LONG lLineBytes;//图像每行的字节数
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));// 计算图像每行的字节数
	LONG map[256] = { 0 };
	unsigned char temp = 0;
	//for (m=0;m<3;m++)
	//{
	for (i = 0;i < lHeight;i++)
	{
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*i;// 指向本行的象素指针
		for (j = 0; j < lWidth; j++)
		{
			if (bBitCount == 8)
			{
				// 对256色位图（需要对bpSrc[j]进行处理）
			}
			else
			{
				temp = bpSrc[j * 3 + scRed];
				map[temp]++;
			}
		}
	}
	for (m = 0;m < 256;m++)
	{
		temp = (unsigned char)(((double)map[m] / (double)(lWidth*lHeight)) * 255);
		map[m] = temp;
	}
	for (i = 0; i < lHeight; i++)
	{
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*i;// 指向本行的象素指针
		for (j = 0; j < lWidth; j++)
		{
			if (bBitCount == 8)
			{
			}
			else
			{
				temp = bpSrc[j * 3 + scRed];
				bpSrc[j * 3 + scRed] = (BYTE)map[temp];
			}
		}
	}
	return TRUE;
}
BOOL HistAvetogramProcess_Blue(LPSTR lpDIBBits, BYTE bBitCount, LONG lWidth, LONG lHeight)
{
	// 判断输入参数是否有误
	if (lpDIBBits == NULL || (bBitCount != 8 && bBitCount != 24) || lWidth <= 0 || lHeight <= 0)
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	// 指向源图像的指针
	BYTE *bpSrc;
	// 循环变量
	LONG i;
	LONG j;
	int m = 0;
	LONG lLineBytes;// 图像每行的字节数
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));// 计算图像每行的字节数
	LONG map[256] = { 0 };
	unsigned char temp = 0;
	//for (m=0;m<3;m++)
	//{
	for (i = 0;i < lHeight;i++)
	{
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*i;// 指向本行的象素指针
		for (j = 0; j < lWidth; j++)
		{
			if (bBitCount == 8)
			{
				// 对256色位图（需要对bpSrc[j]进行处理）
			}
			else
			{
				temp = bpSrc[j * 3 + scRed];
				map[temp]++;
			}
		}
	}
	//}
	for (m = 0;m < 256;m++)
	{
		temp = (unsigned char)(((double)map[m] / (double)(lWidth*lHeight)) * 255);
		map[m] = temp;
	}
	for (i = 0; i < lHeight; i++)
	{
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*i;// 指向本行的象素指针
		for (j = 0; j < lWidth; j++)
		{
			if (bBitCount == 8)
			{
				// 对256色位图（需要对bpSrc[j]进行处理）
			}
			else
			{
				temp = bpSrc[j * 3 + scBlue];
				bpSrc[j * 3 + scBlue] = (BYTE)map[temp];
			}
		}
	}
	return TRUE;
}
BOOL HistAvetogramProcess_Green(LPSTR lpDIBBits, BYTE bBitCount, LONG lWidth, LONG lHeight)
{
	// 判断输入参数是否有误
	if (lpDIBBits == NULL || (bBitCount != 8 && bBitCount != 24) || lWidth <= 0 || lHeight <= 0)
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	// 指向源图像的指针
	BYTE *bpSrc;
	// 循环变量
	LONG i;
	LONG j;
	int m = 0;
	LONG lLineBytes;// 图像每行的字节数
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));// 计算图像每行的字节数
	LONG map[256] = { 0 };
	unsigned char temp = 0;
	//for (m=0;m<3;m++)
	//{
	for (i = 0;i < lHeight;i++)
	{
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*i;// 指向本行的象素指针
		for (j = 0; j < lWidth; j++)
		{
			if (bBitCount == 8)
			{
				// 对256色位图（需要对bpSrc[j]进行处理）
			}
			else
			{
				temp = bpSrc[j * 3 + scRed];
				map[temp]++;
			}
		}
	}
	for (m = 0;m < 256;m++)
	{
		temp = (unsigned char)(((double)map[m] / (double)(lWidth*lHeight)) * 255);
		map[m] = temp;
	}
	for (i = 0; i < lHeight; i++)
	{
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*i;// 指向本行的象素指针
		for (j = 0; j < lWidth; j++)
		{
			if (bBitCount == 8)
			{
				// 对256色位图（需要对bpSrc[j]进行处理）
			}
			else
			{
				temp = bpSrc[j * 3 + scGreen];
				bpSrc[j * 3 + scGreen] = (BYTE)map[temp];
			}
		}
	}
	return TRUE;
}
/*************************************************************************
* 函数名称：HGLOBAL GradSharp(LPSTR lpDIB,BYTE threshold)
*	LPSTR	lpDIBBits	- 指向DIB数据区的指针
*	BYTE	bBitCount	- 图像的颜色位数
*	LONG	lWidth		- 源图像宽度（象素数）
*	LONG	lHeight		- 源图像高度（象素数）
* 返回值:
*	BOOL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数梯度锐化。
**************************************************************************/
HGLOBAL GradSharp(LPSTR lpDIB,BYTE threshold)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	BYTE *bpSrc1, *bpSrc2, *bpSrc3, *bpSrc4;// 指向源图像的指针
	int mm = 0;
	double temp = 0;
	for (i = 1; i < lHeight - 1; i++)// 模板处理
	{
		bpDst = bpNewDIBBits + lLineBytes*(lHeight - 1 - i);
		bpSrc1 = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
		bpSrc2 = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
		bpSrc3 = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + 1);
		bpSrc4 = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + 1);
		for (j = 1; j < lWidth - 1; j++)
		{
			temp = 0;
			if (bBitCount == 8)
			{
				temp = abs(bpSrc1[j] - bpSrc3[j + 1]) + abs(bpSrc2[j + 1] - bpSrc4[j]);
				if (temp + 120 < 255)
				{
					if (temp > threshold)
					{
						bpDst[j] = (BYTE)(temp + 120);
					}
				}
				else
				{
					bpDst[j] = 255;
				}
			}
			else
			{

				for (mm = 0;mm < 3;mm++)
				{
					temp = abs(bpSrc1[j * 3 + mm] - bpSrc3[(j + 1) * 3 + mm]) + abs(bpSrc2[(j + 1) * 3 + mm] - bpSrc4[j * 3 + mm]);
					if (temp + 120 < 255)
					{
						if (temp > threshold)
						{
							bpDst[j * 3 + mm] = (BYTE)(temp + 120);
						}
					}
					else
					{
						bpDst[j * 3 + mm] = 255;
					}
				}
			}
		}
	}
	return hDIB;
}

/*************************************************************************
* 函数名称：HGLOBAL LapTemplateSharp(LPSTR lpDIB, double K)
* 参数:
*	LPSTR	lpDIBBits	- 指向DIB数据区的指针
*	BYTE	bBitCount	- 图像的颜色位数
*	LONG	lWidth		- 源图像宽度（象素数）
*	LONG	lHeight		- 源图像高度（象素数）
* 返回值:
*	BOOL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数利用拉普拉斯锐化。
**************************************************************************/
HGLOBAL LapTemplateSharp(LPSTR lpDIB, double K)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	int a[9] = { 0,-1,0,-1,4,-1,0,-1,0 }, b[9] = { -1,1,-1,1,8,-1,-1,1,-1 };
	double temp = 0;
	int mm = 0, k = -1, t = -1, y = 0;
	for (i = 1; i < lHeight - 1; i++)// 模板处理
	{
		for (j = 1; j < lWidth - 1; j++)
		{
			bpDst = bpNewDIBBits + lLineBytes*(lHeight - 1 - i);
			if (bBitCount == 8)
			{
				temp = 0;
				y = 0;
				for (k = -1;k<2;k++)
				{
					bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
					for (t = -1;t<2;t++)
					{
						temp += bpSrc[(j + t)] * a[y];
						y++;
					}
				}
				temp = temp * K;
				temp = fabs(temp);
				if (temp > 255)
				{
					bpDst[j] = 255; 
				}
				else
				{
					//bpDst[j] = (BYTE)(temp + 0.5);
				}
			}
			else
			{
				for (mm = 0;mm<3;mm++)
				{
					temp = 0;
					y = 0;
					for (k = -1;k<2;k++)
					{
						bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
						for (t = -1;t<2;t++)
						{
							temp += bpSrc[(j + t) * 3 + mm] * a[y];
							y++;
						}
					}
					temp = temp * K;
					temp = fabs(temp);
					if (temp > 255)
					{
						bpDst[j * 3 + mm] = 255; 
					}
					else
					{
					}


				}
			}
		}
	}
	return hDIB;
}
/*************************************************************************
* 函数名称：HGLOBAL RobertsTemplateSharp(LPSTR lpDIB)
* 参数:
*	LPSTR	lpDIBBits	- 指向DIB数据区的指针
* 返回值:
*	HGLOBAL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数利用Roberts算子处理
**************************************************************************/
HGLOBAL RobertsTemplateSharp(LPSTR lpDIB)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
		
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	BYTE *bpSrc1;// 指向源图像的指针
	int temp[9] = { 0 };
	for (i = 1; i < lHeight - 1; i++)// 模板处理
	{
		bpDst = bpNewDIBBits + lLineBytes*(lHeight - 1 - i);
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
		for (j = 1; j < lWidth - 1; j++)
		{
		
			if (bBitCount == 8)
			{
				// 对256色位图（需要对bpSrc[j]进行处理）
				temp[0] = bpSrc[j - lLineBytes - 1];
				temp[1] = bpSrc[j - lLineBytes];
				temp[2] = bpSrc[j - lLineBytes + 1];
				temp[3] = bpSrc[j - 1];
				temp[4] = bpSrc[j];
				temp[5] = bpSrc[j + 1];
				temp[6] = bpSrc[j + lLineBytes - 1];
				temp[7] = bpSrc[j + lLineBytes];
				temp[8] = bpSrc[j + lLineBytes + 1];
				double ux = temp[0] * (1) + temp[3] * (2) + temp[6] * (1) + temp[2] * (-1) + temp[5] * (-2) + temp[8] * (-1);
				double uy = temp[0] * (1) + temp[1] * (2) + temp[2] * (1) + temp[6] * (-1) + temp[7] * (-2) + temp[8] * (-1);
				if (ux < 0) ux = -ux;
				if (uy < 0) uy = -uy;
				bpDst[j] = sqrt(ux*ux+uy*uy);
			}
			else
			{
				temp[0] = bpSrc[(j - 1) * 3 + scRed - lLineBytes];
				temp[1] = bpSrc[(j) * 3 + scRed - lLineBytes];
				temp[2] = bpSrc[(j + 1) * 3 + scRed - lLineBytes];
				temp[3] = bpSrc[(j - 1) * 3 + scRed];
				temp[4] = bpSrc[j * 3 + scRed];
				temp[5] = bpSrc[(j + 1) * 3 + scRed];
				temp[6] = bpSrc[(j - 1) * 3 + scRed + lLineBytes];
				temp[7] = bpSrc[(j) * 3 + scRed + lLineBytes];
				temp[8] = bpSrc[(j + 1) * 3 + scRed + lLineBytes];
				double ux = temp[0] * (-1) + temp[3] * (-2) + temp[6] * (-1) + temp[2] * (1) + temp[5] * (2) + temp[8] * (1);
				double uy = temp[0] * (-1) + temp[1] * (-2) + temp[2] * (-1) + temp[6] * (1) + temp[7] * (2) + temp[8] * (1);
				bpDst[j * 3 + scRed] = sqrt(ux*ux + uy*uy);
				temp[0] = bpSrc[(j - 1) * 3 + scGreen - lLineBytes];
				temp[1] = bpSrc[(j) * 3 + scGreen - lLineBytes];
				temp[2] = bpSrc[(j + 1) * 3 + scGreen - lLineBytes];
				temp[3] = bpSrc[(j - 1) * 3 + scGreen];
				temp[4] = bpSrc[j * 3 + scGreen];
				temp[5] = bpSrc[(j + 1) * 3 + scGreen];
				temp[6] = bpSrc[(j - 1) * 3 + scGreen + lLineBytes];
				temp[7] = bpSrc[(j) * 3 + scGreen + lLineBytes];
				temp[8] = bpSrc[(j + 1) * 3 + scGreen + lLineBytes];
				ux = temp[0] * (-1) + temp[3] * (-2) + temp[6] * (-1) + temp[2] * (1) + temp[5] * (2) + temp[8] * (1);
				uy = temp[0] * (-1) + temp[1] * (-2) + temp[2] * (-1) + temp[6] * (1) + temp[7] * (2) + temp[8] * (1);
				bpDst[j * 3 + scGreen] = sqrt(ux*ux + uy*uy);
				temp[0] = bpSrc[(j - 1) * 3 + scBlue - lLineBytes];
				temp[1] = bpSrc[(j) * 3 + scBlue - lLineBytes];
				temp[2] = bpSrc[(j + 1) * 3 + scBlue - lLineBytes];
				temp[3] = bpSrc[(j - 1) * 3 + scBlue];
				temp[4] = bpSrc[j * 3 + scBlue];
				temp[5] = bpSrc[(j + 1) * 3 + scBlue];
				temp[6] = bpSrc[(j - 1) * 3 + scBlue + lLineBytes];
				temp[7] = bpSrc[(j) * 3 + scBlue + lLineBytes];
				temp[8] = bpSrc[(j + 1) * 3 + scBlue + lLineBytes];
				ux = temp[0] * (-1) + temp[3] * (-2) + temp[6] * (-1) + temp[2] * (1) + temp[5] * (2) + temp[8] * (1);
				uy = temp[0] * (-1) + temp[1] * (-2) + temp[2] * (-1) + temp[6] * (1) + temp[7] * (2) + temp[8] * (1);
				bpDst[j * 3 + scBlue] = sqrt(ux*ux + uy*uy);
				
			}
		}
	}
	return hDIB;
}
/*************************************************************************
* 函数名称：HGLOBAL PrewittTemplateSharp(LPSTR lpDIB)
* 参数:
*	LPSTR	lpDIBBits	- 指向DIB数据区的指针
* 返回值:
*	HGLOBAL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数利用Prewitt算子处理
**************************************************************************/
HGLOBAL PrewittTemplateSharp(LPSTR lpDIB)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;

	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	BYTE *bpSrc1;// 指向源图像的指针
	int temp[9] = { 0 };
	int temp_d = 0;
	for (i = 1; i < lHeight - 1; i++)// 模板处理
	{
		bpDst = bpNewDIBBits + lLineBytes*(lHeight - 1 - i);
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
		for (j = 1; j < lWidth - 1; j++)
		{

			if (bBitCount == 8)
			{
				// 对256色位图（需要对bpSrc[j]进行处理）
				temp[0] = bpSrc[j - lLineBytes - 1];
				temp[1] = bpSrc[j - lLineBytes];
				temp[2] = bpSrc[j - lLineBytes + 1];
				temp[3] = bpSrc[j - 1];
				temp[4] = bpSrc[j];
				temp[5] = bpSrc[j + 1];
				temp[6] = bpSrc[j + lLineBytes - 1];
				temp[7] = bpSrc[j + lLineBytes];
				temp[8] = bpSrc[j + lLineBytes + 1];
				double ux = temp[0] * (-1) + temp[3] * (-1) + temp[6] * (-1) + temp[2] * (1) + temp[5] * (1) + temp[8] * (1);
				double uy = temp[0] * (-1) + temp[1] * (-1) + temp[2] * (-1) + temp[6] * (1) + temp[7] * (1) + temp[8] * (1);
				temp_d = sqrt(ux*ux + uy*uy);
				if (temp_d > 255)
					temp_d = 255;
				bpDst[j] = temp_d;
			}
			else
			{
				temp[0] = bpSrc[(j - 1) * 3 + scRed - lLineBytes];
				temp[1] = bpSrc[(j) * 3 + scRed - lLineBytes];
				temp[2] = bpSrc[(j + 1) * 3 + scRed - lLineBytes];
				temp[3] = bpSrc[(j - 1) * 3 + scRed];
				temp[4] = bpSrc[j * 3 + scRed];
				temp[5] = bpSrc[(j + 1) * 3 + scRed];
				temp[6] = bpSrc[(j - 1) * 3 + scRed + lLineBytes];
				temp[7] = bpSrc[(j) * 3 + scRed + lLineBytes];
				temp[8] = bpSrc[(j + 1) * 3 + scRed + lLineBytes];
				double ux = temp[0] * (-1) + temp[3] * (-1) + temp[6] * (-1) + temp[2] * (1) + temp[5] * (1) + temp[8] * (1);
				double uy = temp[0] * (-1) + temp[1] * (-1) + temp[2] * (-1) + temp[6] * (1) + temp[7] * (1) + temp[8] * (1);
				bpDst[j * 3 + scRed] = sqrt(ux*ux + uy*uy);
				temp[0] = bpSrc[(j - 1) * 3 + scGreen - lLineBytes];
				temp[1] = bpSrc[(j) * 3 + scGreen - lLineBytes];
				temp[2] = bpSrc[(j + 1) * 3 + scGreen - lLineBytes];
				temp[3] = bpSrc[(j - 1) * 3 + scGreen];
				temp[4] = bpSrc[j * 3 + scGreen];
				temp[5] = bpSrc[(j + 1) * 3 + scGreen];
				temp[6] = bpSrc[(j - 1) * 3 + scGreen + lLineBytes];
				temp[7] = bpSrc[(j) * 3 + scGreen + lLineBytes];
				temp[8] = bpSrc[(j + 1) * 3 + scGreen + lLineBytes];
				ux = temp[0] * (-1) + temp[3] * (-1) + temp[6] * (-1) + temp[2] * (1) + temp[5] * (1) + temp[8] * (1);
				uy = temp[0] * (-1) + temp[1] * (-1) + temp[2] * (-1) + temp[6] * (1) + temp[7] * (1) + temp[8] * (1);
				bpDst[j * 3 + scGreen] = sqrt(ux*ux + uy*uy);
				temp[0] = bpSrc[(j - 1) * 3 + scBlue - lLineBytes];
				temp[1] = bpSrc[(j) * 3 + scBlue - lLineBytes];
				temp[2] = bpSrc[(j + 1) * 3 + scBlue - lLineBytes];
				temp[3] = bpSrc[(j - 1) * 3 + scBlue];
				temp[4] = bpSrc[j * 3 + scBlue];
				temp[5] = bpSrc[(j + 1) * 3 + scBlue];
				temp[6] = bpSrc[(j - 1) * 3 + scBlue + lLineBytes];
				temp[7] = bpSrc[(j) * 3 + scBlue + lLineBytes];
				temp[8] = bpSrc[(j + 1) * 3 + scBlue + lLineBytes];
				ux = temp[0] * (-1) + temp[3] * (-1) + temp[6] * (-1) + temp[2] * (1) + temp[5] * (1) + temp[8] * (1);
				uy = temp[0] * (-1) + temp[1] * (-1) + temp[2] * (-1) + temp[6] * (1) + temp[7] * (1) + temp[8] * (1);
				bpDst[j * 3 + scBlue] = sqrt(ux*ux + uy*uy);
			}
		}
	}
	return hDIB;
}
/*************************************************************************
* 函数名称：HGLOBAL SobelTemplateSharp(LPSTR lpDIB)
* 参数:
*	LPSTR	lpDIBBits	- 指向DIB数据区的指针
* 返回值:
*	HGLOBAL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数利用Sobel算子处理
**************************************************************************/
HGLOBAL SobelTemplateSharp(LPSTR lpDIB)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;

	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	int temp[9] = { 0 };
	int temp_d = 0;
	for (i = 1; i < lHeight - 1; i++)// 模板处理
	{
		bpDst = bpNewDIBBits + lLineBytes*(lHeight - 1 - i);
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
		for (j = 1; j < lWidth - 1; j++)
		{

			if (bBitCount == 8)
			{
				// 对256色位图（需要对bpSrc[j]进行处理）
				temp[0] = bpSrc[j];
				temp[1] = bpSrc[j + 1];
				temp[2] = bpSrc[j + lLineBytes];
				temp[3] = bpSrc[j + lLineBytes + 1];
				double ux = temp[0] * (-1) + temp[3] * (1);
				double uy = temp[2] - temp[1];
				if (ux < 0) ux = -ux;
				if (uy < 0) uy = -uy;
				bpDst[j] = sqrt(ux*ux+uy*uy);
			}
			else
			{
				temp[0] = bpSrc[j * 3 + scRed];
				temp[1] = bpSrc[(j + 1) * 3 + scRed];
				temp[2] = bpSrc[j * 3 + scRed + lLineBytes];
				temp[3] = bpSrc[(j + 1) * 3 + scRed + lLineBytes];
				double ux = temp[0] * (-1) + temp[3] * (1);
				double uy = temp[2] - temp[1];
				if (ux < 0) ux = -ux;
				if (uy < 0) uy = -uy;
				bpDst[j * 3 + scRed] = sqrt(ux*ux + uy*uy);
				temp[0] = bpSrc[j * 3 + scBlue];
				temp[1] = bpSrc[(j + 1) * 3 + scBlue];
				temp[2] = bpSrc[j * 3 + scBlue + lLineBytes];
				temp[3] = bpSrc[(j + 1) * 3 + scBlue + lLineBytes];
				ux = temp[0] * (-1) + temp[3] * (1);
				uy = temp[2] - temp[1];
				if (ux < 0) ux = -ux;
				if (uy < 0) uy = -uy;
				bpDst[j * 3 + scBlue] = sqrt(ux*ux + uy*uy);
				temp[0] = bpSrc[j * 3 + scGreen];
				temp[1] = bpSrc[(j + 1) * 3 + scGreen];
				temp[2] = bpSrc[j * 3 + scGreen + lLineBytes];
				temp[3] = bpSrc[(j + 1) * 3 + scGreen + lLineBytes];
				ux = temp[0] * (-1) + temp[3] * (1);
				uy = temp[2] - temp[1];
				if (ux < 0) ux = -ux;
				if (uy < 0) uy = -uy;
				bpDst[j * 3 + scGreen] = sqrt(ux*ux + uy*uy);
			}
		}
	}
	return hDIB;
}

/*************************************************************************
* 函数名称：HGLOBAL BasicErosionForBinary(LPSTR lpDIB)
* 参数:
*	LPSTR	lpDIBBits	- 指向DIB数据区的指针
*	BYTE	bBitCount	- 图像的颜色位数
*	LONG	lWidth		- 源图像宽度（象素数）
*	LONG	lHeight		- 源图像高度（象素数）
* 返回值:
*	BOOL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数利用边界检测 prewitt 算子对图像进行边缘检测。
**************************************************************************/
HGLOBAL threshOtus(LPSTR lpDIB, double K)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}


	int histArray_Red[256] = { 0 };
	int histArray_Blue[256] = { 0 };
	int histArray_Green[256] = { 0 };

	double temp = 0;
	int mm = 0, k = -1, t = -1, y = 0;
	for (i = 0; i < lHeight; i++)// 模板处理
	{
		bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - i);
		for (j = 0; j < lWidth; j++)
		{
			if (bBitCount == 8)
			{
			}
			else
			{
				histArray_Blue[bpSrc[j * 3 + scBlue]]++;
				histArray_Red[bpSrc[j * 3 + scRed]]++;
				histArray_Green[bpSrc[j * 3 + scGreen]]++;
			}
		}
	}
	double sum = lLineBytes*lHeight;
	double count0 = 0, u0 = 0, u1 = 0, w0 = 0, w1 = 0, devi = 0, MaxDevi = 0, maxT = 0;
	for (i = 0; i < 255;i++)
	{
		u0 = 0;
		count0 = 0;
		for (j = 0;j < i;j++)
		{
			u0 += i*histArray_Red[i];
			count0 += histArray_Red[i];
		}
		u0 = u0 / count0;
		w0 = (double)count0 / sum;

		u1 = 0;
		for (j = i + 1;j < 256;j++)
		{
			u1 += i*histArray_Red[i];

		}
		u1 = u1 / (sum - count0);
		w1 = 1 - w0;
		devi = w0*w1*(u1 - u0)*(u1 - u0);
		if (devi > MaxDevi)
		{
			MaxDevi = devi;
			maxT = i;
		}
	}

	for (i = 0; i < lNewHeight; i++)// 模板处理
	{
		for (j = 0; j < lNewWidth; j++)
		{
			bpDst = bpNewDIBBits + lLineBytes*(lNewHeight -1- i);
			if (bBitCount == 8)
			{

			}
			else
			{
				if (bpDst[j * 3 + scRed] > maxT)
				{
					bpDst[j * 3 + scRed] = 255;
				}
				else
				{
					bpDst[j * 3 + scRed] = 0;
				}
			}
		}
	}
	return hDIB;
}

/*************************************************************************
* 函数名称：HGLOBAL BasicErosionForBinary(LPSTR lpDIB)
* 参数:
*	LPSTR	lpDIBBits	- 指向DIB数据区的指针
*	BYTE	bBitCount	- 图像的颜色位数
*	LONG	lWidth		- 源图像宽度（象素数）
*	LONG	lHeight		- 源图像高度（象素数）
* 返回值:
*	BOOL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数利用边界检测 prewitt 算子对图像进行边缘检测。
**************************************************************************/
HGLOBAL Prewitt(LPSTR lpDIB)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	int a[9] = { -1,0,1, -1,0,1, -1,0,1 }, b[9] = { 1,1,1,0,0,0,-1,-1,-1 };
	double temp_x = 0, temp_y = 0, temp = 0;
	int mm = 0, k = -1, t = -1, y = 0;
	for (i = 1; i < lHeight - 1; i++)// 模板处理
	{
		bpDst = bpNewDIBBits + lLineBytes*(lHeight - 1 - i);
		for (j = 1; j < lWidth - 1; j++)
		{
			
			if (bBitCount == 8)
			{

				temp = 0;
				temp_x = 0;
				y = 0;
				for (k = -1;k<2;k++)
				{
					bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
					for (t = -1;t<2;t++)
					{
						temp_x += bpSrc[(j + t)] * a[y];
						y++;
					}
				}
				temp_y = 0;
				y = 0;
				for (k = -1;k<2;k++)
				{
					bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
					for (t = -1;t<2;t++)
					{
						temp_y += bpSrc[(j + t)] * b[y];
						y++;
					}
				}

				temp = sqrt(temp_x*temp_x + temp_y*temp_y) + 0.5;
				if (temp > 255)
				{
					temp = 255;
				}
				bpDst[j] = (BYTE)temp;
			}
			else
			{
				for (mm = 0;mm<3;mm++)
				{
					temp = 0;
					temp_x = 0;
					y = 0;
					for (k = -1;k<2;k++)
					{
						bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
						for (t = -1;t<2;t++)
						{
							temp_x += bpSrc[(j + t) * 3 + mm] * a[y];
							y++;
						}
					}
					temp_y = 0;
					y = 0;
					for (k = -1;k<2;k++)
					{
						bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i + k);
						for (t = -1;t<2;t++)
						{
							temp_y += bpSrc[(j + t) * 3 + mm] * b[y];
							y++;
						}
					}

					temp = sqrt(temp_x*temp_x + temp_y*temp_y) + 0.5;
					if (temp > 255)
					{
						temp = 255;
					}
					bpDst[j * 3 + mm] = (BYTE)temp;

				}
			}
		}
	}
	return hDIB;
}
/*************************************************************************
* 函数名称：HGLOBAL BasicErosionForBinary(LPSTR lpDIB)
* 参数:
*	LPSTR	lpDIBBits	- 指向DIB数据区的指针
*	BYTE	bBitCount	- 图像的颜色位数
*	LONG	lWidth		- 源图像宽度（象素数）
*	LONG	lHeight		- 源图像高度（象素数）
* 返回值:
*	BOOL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数用来对图像进行马赛克处理。
**************************************************************************/
HGLOBAL MosaictogramProcess(LPSTR lpDIB, int n)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	// 计算新DIB图像实际宽度和高度
	lNewWidth =lWidth;
	lNewHeight = lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	double  temp = 0;
	BYTE PP[3] = { 0 };
	int mm = 0, k = -1, t = -1;
	for (i = 0; i < lHeight - n; i += n)// 模板处理
	{
		for (j = 0; j < lWidth - n; j += n)
		{

			if (bBitCount == 8)
			{
				for (k = 0;k < n;k++)
				{
					bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - (i + k));
					for (t = 0;t < n;t++)
					{
						temp += bpSrc[j + t];
					}
				}
				temp = temp / (n*n);
				for (k = 0;k < n;k++)
				{
					bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - (i + k));
					for (t = 0;t < n;t++)
					{
						bpDst[j + t] = (BYTE)temp;
					}
				}

				temp = 0;
			}
			else
			{
				for (mm = 0;mm < 3;mm++)
				{
					for (k = 0;k < n;k++)
					{
						bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - (i + k));
						for (t = 0;t < n;t++)
						{
							temp += bpSrc[(j + t) * 3 + mm];
						}
					}
					temp = temp / (n*n);
					PP[mm] = (BYTE)temp;
					temp = 0;
				}
				for (mm = 0;mm < 3;mm++)
				{
					for (k = 0;k < n;k++)
					{
						bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - (i + k));
						for (t = 0;t < n;t++)
						{
							bpDst[(j + t) * 3 + mm] = PP[mm];
						}
					}
				}
			}
		}
	}
	return hDIB;
	
}
/*
图像缩放
*/
HGLOBAL ZoomDblLinear(LPSTR lpDIB,double Kx,double Ky)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	double i0;
	double j0;
	
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	// 计算新DIB图像实际宽度和高度
	lNewWidth = (LONG)(lWidth*Kx);
	lNewHeight = (LONG)(lHeight*Ky);
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	if (bBitCount == 8)
	{
		for (i = 0; i<lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			i0 = (double)i / Ky;
			for (j = 0; j<lNewWidth; j++)
			{
				j0 = (double)j / Kx;
				if ((i0<lHeight) && (i0 >= 0) && (j0<lWidth) && (j0 >= 0))
				{
					bpSrc = SXXZZ(lLineBytes, lpDIBBits, lHeight, lWidth, bBitCount, i0, j0);
					bpDst[j] = bpSrc[0];
				}
				else
				{
					bpDst[j] = (BYTE)255;
				}
			}
		}
	}
	else
	{
		for (i = 0; i<lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			i0 = (double)i / Ky;
			for (j = 0; j<lNewWidth; j++)
			{
				j0 = (double)j/Kx;
				if ((i0<lHeight) && (i0>= 0) && (j0<lWidth)&&(j0 >= 0))
				{
					bpSrc = SXXZZ(lLineBytes, lpDIBBits, lHeight, lWidth,bBitCount, i0, j0);
					bpDst[j * 3 + scBlue] = bpSrc[scBlue];
					bpDst[j * 3 + scGreen] = bpSrc[scGreen];
					bpDst[j * 3 + scRed] = bpSrc[scRed];
				}
				else
				{
					bpDst[j * 3 + scBlue] = bpDst[j * 3 + scGreen] = bpDst[j * 3 + scRed] = 255;
				}
			}
		}
	}

	return hDIB;
}
/*************************************************************************
* 函数名称：BOOL GetHist(LPSTR lpDIBBits, BYTE bBitCount,  LONG lHeight, LONG lWidth, unsigned int * p,BYTE tongdao)
* 返回值:无
* 说明:
*	该函数用来获取色素值得分布情况，将其存放到数组中。
**************************************************************************/
BOOL GetHist(LPSTR lpDIBBits, BYTE bBitCount,  LONG lHeight, LONG lWidth, unsigned int * p,BYTE tongdao)
{
	if (lpDIBBits == NULL || (bBitCount != 8 && bBitCount != 24) || lWidth <= 0 || lHeight <= 0)// 判断输入参数是否有误
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE *bpSrc;// 指向源图像的指针
	LONG i;// 循环变量
	LONG j;
	LONG lLineBytes;// 图像每行的字节数
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));// 计算DIB图像每行的字节数
	int mm = 0, k = -1, t = -1;
	BYTE temp = 0;
	for (i = 0;i < 256;i++)
		p[i] = 0;
	if ((tongdao > 3) && (bBitCount != 8))
		return false;
	if (bBitCount == 8)
	{
		for (i = 0; i < lHeight; i++)// 模板处理
		{
			bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight-1 - i);
			for (j = 0; j < lWidth; j++)
			{
				p[bpSrc[j]]++;
			}
		}
	}
	else
	{
		if (tongdao > 2)
		{
			for (i = 0; i < lHeight; i++)// 模板处理
			{
				bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight-1 - i);
				for (j = 0; j < lWidth; j++)
				{
					temp = (BYTE)((bpSrc[j * 3 + 0] + bpSrc[j * 3 + 1] + bpSrc[j * 3 + 2]) / 3);
					p[temp]++;
				}
			}
		}
		else
		{
			for (i = 0; i < lHeight; i++)// 模板处理
			{
				bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight-1 - i);
				for (j = 0; j < lWidth; j++)
				{
					temp = bpSrc[j * 3 + tongdao];
					p[temp]++;
				}
			}
		}
	}
	return TRUE;
}
/*************************************************************************
* 函数名称：void Get_JunZhiAndFangCha(unsigned int *p, unsigned int Length,double *JunZhi,double *FangCha)
* 返回值:无
* 说明:
*	该函数用来根据色素值得分布情况求出该色素整幅图中的均值和方差不对图像进行处理。
**************************************************************************/
void Get_JunZhiAndFangCha(unsigned int *p, unsigned int Length,double *JunZhi,double *FangCha)
{
	unsigned int i;
	double sum=0, temp1 = 0,temp2=0;
	for (i = 0;i < Length;i++)
	{
		sum += p[i];
	}
	for (i = 0;i < Length;i++)
	{
		temp1 += i*p[i];
	}
	*JunZhi = temp1 / sum;
	temp1 = temp1 / sum;
	for (i = 0;i < Length;i++)
	{
		temp2 += pow(i - temp1, 2)* p[i];
	}
	temp2 = temp2 / sum;
	*FangCha = temp2;
}
/*************************************************************************
* 函数名称：BOOL HistProcess_Red(LPSTR lpDIB, double *JunZhi, double *FangCha)
* 返回值:
*	BOOL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数用来对24位色图Red通道处理，获取图像的灰度分布情况，并画出灰度分布图，并求出灰度均值和方差。
但不对图像进行处理值获取相应的信息
**************************************************************************/
BOOL HistProcess_Red(LPSTR lpDIB,double *JunZhi,double *FangCha)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	LPSTR lpDIBBits;
	LONG lLineBytes;
	lpDIBBits = FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	double Junzhi = 0, fangcha = 0;

	Hist* pHist = new Hist();
	//pHist->Create(IDD_DIALOG_Hist); 放在了 Histde 构造函数中
	//pTD->Create(IDD_DIALOG1); //创建一个非模态对话框  
	//pTD->ShowWindow(SW_SHOWNORMAL); //
	pHist->Colour = scRed;
	pHist->hist = new unsigned int[256];
	GetHist(lpDIBBits, bBitCount, lHeight, lWidth, pHist->hist, scRed);
	Get_JunZhiAndFangCha(pHist->hist, 256, &Junzhi, &fangcha);
	*JunZhi = Junzhi;
	*FangCha = fangcha;
	CString str1, str2;
	str1.Format("%.2f", Junzhi);
	str2.Format("%.2f", fangcha);
	if (pHist->GetSafeHwnd())
	{
		pHist->TongDao.SetWindowText("红色");
		pHist->JunZhi.SetWindowText(str1);
		pHist->FangCha.SetWindowText(str2);
	}
	else
	{
		AfxMessageBox(_T("无法获得地图树控件句柄!"));
		return false;
	}
	pHist->ShowWindow(SW_SHOWNORMAL);
	return TRUE;
}
/*************************************************************************
* 函数名称：BOOL HistProcess_Blue(LPSTR lpDIB, double *JunZhi, double *FangCha)
* 返回值:
*	BOOL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数用来对24位色图Blue通道处理，获取图像的灰度分布情况，并画出灰度分布图，并求出灰度均值和方差。
但不对图像进行处理值获取相应的信息
**************************************************************************/
BOOL HistProcess_Blue(LPSTR lpDIB, double *JunZhi, double *FangCha)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	LPSTR lpDIBBits;
	LONG lLineBytes;
	lpDIBBits = FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	double Junzhi = 0, fangcha = 0;
	Hist* pHist = new Hist();
	pHist->Colour = scBlue;
	pHist->hist = new unsigned int[256];
	GetHist(lpDIBBits, bBitCount, lHeight, lWidth, pHist->hist, scBlue);
	Get_JunZhiAndFangCha(pHist->hist, 256, &Junzhi, &fangcha);
	*JunZhi = Junzhi;
	*FangCha = fangcha;
	CString str1, str2;
	str1.Format("%.2f", Junzhi);
	str2.Format("%.2f", fangcha);
	if (pHist->GetSafeHwnd())
	{
		pHist->TongDao.SetWindowText("蓝色");
		pHist->JunZhi.SetWindowText(str1);
		pHist->FangCha.SetWindowText(str2);
	}
	else
	{
		AfxMessageBox(_T("无法获得地图树控件句柄!"));
		return false;
	}
	pHist->ShowWindow(SW_SHOWNORMAL);
	//pHist->MyGetData();
	return TRUE;
}
/*************************************************************************
* 函数名称：BOOL HistProcess_Green(LPSTR lpDIB, double *JunZhi, double *FangCha)
* 返回值:
*	BOOL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数用来对24位色图Green通道处理，获取图像的灰度分布情况，并画出灰度分布图，并求出灰度均值和方差。
但不对图像进行处理值获取相应的信息
**************************************************************************/
BOOL HistProcess_Green(LPSTR lpDIB, double *JunZhi, double *FangCha)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	LPSTR lpDIBBits;
	LONG lLineBytes;
	lpDIBBits = FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	double Junzhi = 0, fangcha = 0;
	Hist* pHist = new Hist();
	pHist->Colour = scGreen;
	pHist->hist = new unsigned int[256];
	GetHist(lpDIBBits, bBitCount, lHeight, lWidth, pHist->hist, scGreen);
	Get_JunZhiAndFangCha(pHist->hist, 256, &Junzhi, &fangcha);
	*JunZhi = Junzhi;
	*FangCha = fangcha;
	CString str1, str2;
	str1.Format("%.2f", Junzhi);
	str2.Format("%.2f", fangcha);
	if (pHist->GetSafeHwnd())
	{
		pHist->TongDao.SetWindowText("绿色");
		pHist->JunZhi.SetWindowText(str1);
		pHist->FangCha.SetWindowText(str2);
	}
	else
	{
		AfxMessageBox(_T("无法获得地图树控件句柄!"));
		return false;
	}
	pHist->ShowWindow(SW_SHOWNORMAL);
	//pHist->MyGetData();
	return TRUE;
}
/*************************************************************************
* 函数名称：BOOL HistProcess_RGB(LPSTR lpDIB, double *JunZhi, double *FangCha)
* 返回值:
*	BOOL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数用来对24位色图混合通道处理，获取图像的灰度分布情况，并画出灰度分布图，并求出灰度均值和方差。
但不对图像进行处理值获取相应的信息
**************************************************************************/
BOOL HistProcess_RGB(LPSTR lpDIB, double *JunZhi, double *FangCha)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	LPSTR lpDIBBits;
	LONG lLineBytes;
	lpDIBBits = FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	double Junzhi = 0, fangcha = 0;
	Hist* pHist = new Hist();
	pHist->Colour = 3;
	pHist->hist = new unsigned int[256];
	GetHist(lpDIBBits, bBitCount, lHeight, lWidth, pHist->hist,3);
	Get_JunZhiAndFangCha(pHist->hist, 256, &Junzhi, &fangcha);
	*JunZhi = Junzhi;
	*FangCha = fangcha;
	CString str1, str2;
	str1.Format("%.2f", Junzhi);
	str2.Format("%.2f", fangcha);
	if (pHist->GetSafeHwnd())
	{
		pHist->TongDao.SetWindowText("混合通道");
		pHist->JunZhi.SetWindowText(str1);
		pHist->FangCha.SetWindowText(str2);
	}
	else
	{
		AfxMessageBox(_T("无法获得地图树控件句柄!"));
		return false;
	}
	pHist->ShowWindow(SW_SHOWNORMAL);
	//pHist->MyGetData();
	return TRUE;
}

/*************************************************************************
* 函数名称：BOOL HistProcess_Huidu(LPSTR lpDIB, double *JunZhi, double *FangCha)
* 返回值:
*	BOOL				- 成功返回TRUE，否则返回FALSE。
* 说明:
*	该函数用来对8位色图处理，获取图像的灰度分布情况，并画出灰度分布图，并求出灰度均值和方差。
但不对图像进行处理值获取相应的信息
**************************************************************************/
BOOL HistProcess_Huidu(LPSTR lpDIB, double *JunZhi, double *FangCha)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	LPSTR lpDIBBits;
	LONG lLineBytes;
	lpDIBBits = FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	double Junzhi = 0, fangcha = 0;
	Hist* pHist = new Hist();
	pHist->Colour = 4;
	pHist->hist = new unsigned int[256];
	GetHist(lpDIBBits, bBitCount, lHeight, lWidth, pHist->hist, 4);
	Get_JunZhiAndFangCha(pHist->hist, 256, &Junzhi, &fangcha);
	*JunZhi = Junzhi;
	*FangCha = fangcha;
	CString str1, str2;
	str1.Format("%.2f", Junzhi);
	str2.Format("%.2f", fangcha);
	if (pHist->GetSafeHwnd())
	{
		pHist->TongDao.SetWindowText("绿色");
		pHist->JunZhi.SetWindowText(str1);
		pHist->FangCha.SetWindowText(str2);
	}
	else
	{
		AfxMessageBox(_T("无法获得地图树控件句柄!"));
		return false;
	}
	pHist->ShowWindow(SW_SHOWNORMAL);
	return TRUE;
}
HGLOBAL HistProcess(LPSTR lpDIB, BYTE yuzhi)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	BYTE temp;

	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	if (bBitCount == 8)
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{

				if (bpSrc[j] >= yuzhi)
					bpDst[j] = 255;
				else
					bpDst[j] = 0;
			}
		}
	}
	else
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{
				temp = (BYTE)((bpSrc[j * 3 + scBlue] + bpSrc[j * 3 + scGreen] + bpSrc[j * 3 + scRed]) / 3);
				if (temp >= yuzhi)
					bpDst[j * 3 + scBlue] = bpDst[j * 3 + scGreen] = bpDst[j * 3 + scRed] = 255;
				else
					bpDst[j * 3 + scBlue] = bpDst[j * 3 + scGreen] = bpDst[j * 3 + scRed] = 0;

			}
		}
	}

	return hDIB;
}
HGLOBAL zhuangzhiProcess(LPSTR lpDIB)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lHeight;
	lNewHeight = (LONG)lWidth;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	if (bBitCount == 8)
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			
			for (j = 0; j < lNewWidth; j++)
			{
				bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - j);
				bpDst[j] = bpSrc[i];
			}
		}
	}
	else
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			
			for (j = 0; j < lNewWidth; j++)
			{
				bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - j);
				bpDst[j * 3 + scBlue] =  bpSrc[i * 3 + scBlue];
				bpDst[j * 3 + scGreen] = bpSrc[i * 3 + scGreen];
				bpDst[j * 3 + scRed] = bpSrc[i* 3 + scRed];
			}
		}
	}
	return hDIB;
}
HGLOBAL fuxiangProcess(LPSTR lpDIB)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	if (bBitCount == 8)
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{
				bpDst[j] = 255 - bpDst[j];
			}
		}
	}
	else
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{
				bpDst[j * 3 + scBlue] = 255 - bpSrc[j * 3 + scBlue];
				bpDst[j * 3 + scGreen] = 255 - bpSrc[j * 3 + scGreen];
				bpDst[j * 3 + scRed] = 255 - bpSrc[j * 3 + scRed];
			}
		}
	}

	return hDIB;
}
HGLOBAL shuipingjingxiangProcess(LPSTR lpDIB)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG) lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	if (bBitCount == 8)
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{
				bpDst[j] = bpSrc[lNewWidth-1-j];
			}
		}
	}
	else
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{
				
				bpDst[j * 3 + scBlue] = bpSrc[(lNewWidth - 1 - j) * 3 + scBlue];
				bpDst[j * 3 + scGreen] = bpSrc[(lNewWidth - 1 - j) * 3 + scGreen];
				bpDst[j * 3 + scRed] = bpSrc[(lNewWidth - 1 - j) * 3 + scRed];
			}
		}
	}
	return hDIB;
}
HGLOBAL chuizhijingxiangProcess(LPSTR lpDIB)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	if (bBitCount == 8)
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpSrc = bpDIBBits + lLineBytes*(i);
			for (j = 0; j < lNewWidth; j++)
			{
				bpDst[j] = bpSrc[j];
			}
		}
	}
	else
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpSrc = bpDIBBits + lLineBytes*(i);
			for (j = 0; j < lNewWidth; j++)
			{

				bpDst[j * 3 + scBlue] = bpSrc[(j) * 3 + scBlue];
				bpDst[j * 3 + scGreen] = bpSrc[(j) * 3 + scGreen];
				bpDst[j * 3 + scRed] = bpSrc[(j) * 3 + scRed];
			}
		}
	}
	return hDIB;
}
HGLOBAL HistJunHengProcess(LPSTR lpDIB)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	// 计算新DIB图像实际宽度和高度
	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	unsigned int * p = new unsigned int[256];
	double sum = 0;
	if (bBitCount == 8)
	{
		
		double *pp = new double[256];
		GetHist(lpDIBBits, bBitCount, lHeight, lWidth, p, 4);
		for (i = 0;i < 256;i++)
		{
			sum += p[i];
			pp[i] = sum / (lNewWidth*lNewHeight);
		}
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{
				bpDst[j] = (BYTE)(255 * pp[bpSrc[j]]);
			}
		}
		delete[]pp;
	}
	else
	{
		double *pp_R = new double[256];
		double *pp_G = new double[256];
		double *pp_B = new double[256];
		GetHist(lpDIBBits, bBitCount, lHeight, lWidth, p, scBlue);
		for (i = 0;i < 256;i++)
		{
			sum += p[i];
			pp_B[i] = sum/(lNewWidth*lNewHeight);
		}
		GetHist(lpDIBBits, bBitCount, lHeight, lWidth, p, scRed);
		for (i = 0;i < 256;i++)
		{
			sum += p[i];
			pp_R[i] = sum / (lNewWidth*lNewHeight);
		}
		GetHist(lpDIBBits, bBitCount, lHeight, lWidth, p, scGreen);
		for (i = 0;i < 256;i++)
		{
			sum += p[i];
			pp_G[i] = sum / (lNewWidth*lNewHeight);
		}
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{

				bpDst[j * 3 + scBlue] = (BYTE)(255 * pp_B[bpSrc[(j) * 3 + scBlue]]);
				bpDst[j * 3 + scGreen] = (BYTE)(255 * pp_G[bpSrc[(j) * 3 + scGreen]]);
				bpDst[j * 3 + scRed] = (BYTE)(255 * pp_R[bpSrc[(j) * 3 + scRed]]);
				//bpDst[j * 3 + scGreen] = bpSrc[(j) * 3 + scGreen];
				//bpDst[j * 3 + scRed] = bpSrc[(j) * 3 + scRed];
			}
		}
		delete[]pp_B;
		delete[]pp_G;
		delete[]pp_R;
	}
	delete[]p;
	return hDIB;
}
HGLOBAL DuiShuStrechProcess(LPSTR lpDIB,double a,double b,double c)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	// 计算新DIB图像实际宽度和高度
	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	double temp1 = 0, temp2 = 0,temp=0;
	int m = 0;
	if (bBitCount == 8)
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{
				temp1 = log(bpSrc[j] + 1) / log(2);
				temp2 = b*log(c) / log(2);
				temp = a + temp1 / temp2;
				if (temp > 255)
					temp = 255;
				else
					if (temp < 0)
						temp = 0;
				
				bpDst[j] = (BYTE)temp;
			}
		}
	}
	else
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{
				for (m = 0;m < 3;m++)
				{
					temp1 = log(bpSrc[j * 3 + m] + 1.0) / log(2.0);
					temp2 = b*log(c)/log(2.0);
					temp = a + temp1 /temp2;
					if (temp > 255)
						temp = 255;
					else
						if (temp < 0)
							temp = 0;

				 bpDst[j * 3+m] = (BYTE)temp;
				}
			}
		}
		
	}
	return hDIB;
}
HGLOBAL ZhiShuStrechProcess(LPSTR lpDIB, double a, double b, double c)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	// 计算新DIB图像实际宽度和高度
	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	double temp1 = 0, temp2 = 0, temp = 0;
	int m = 0;
	if (bBitCount == 8)
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{
				
				temp1 = c*(bpSrc[j] -a);
				temp = pow(b,temp1)-1;
				
				if (temp > 255)
					temp = 255;
				else
					if (temp < 0)
						temp = 0;

				bpDst[j] = (BYTE)temp;
			}
		}
	}
	else
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{
				for (m = 0;m < 3;m++)
				{
					temp1 = c*(bpSrc[j * 3 + m] - a);
					temp = pow(b, temp1) - 1;
					if (temp > 255)
						temp = 255;
					else
						if (temp < 0)
							temp = 0;

					bpDst[j * 3 + m] = (BYTE)temp;
				}
			}
		}

	}
	return hDIB;
}
/************************************************
*
* 函数名称：
HGLOBAL ScanShow(LPSTR lpDIB)
阈值处理
* 参数:
*	LPSTR	lpDIB	- 指向DIB对象的指针
*
* 返回值:
*	LPSTR			- 指向DIB调色板的起始位置
*
* 说明:
*	图像的的扫描显示。
*****************************************************/
HGLOBAL ScanShow(LPSTR lpDIB)
{
	/*
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
	AfxMessageBox("输入参数有误！", MB_OK);
	return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LPSTR lpDIBBits;
	LONG lLineBytes;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	BYTE *bpDIBBits;
	HDIB hDIB;
	BYTE *bpDst;
	BYTE *lpNewDIB;
	BYTE *bpNewDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	lNewWidth = (LONG)lWidth;
	lNewHeight = (LONG)lHeight;
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = (HDIB)::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
	AfxMessageBox("内存分配有误！", MB_OK);
	return NULL;
	}
	lpNewDIB = (BYTE*)::GlobalLock((HGLOBAL)hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits((LPSTR)lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	if (IS_WIN30_DIB(lpNewDIB))
	{
	lpbmi->biWidth = lNewWidth;
	lpbmi->biHeight = lNewHeight;
	}
	else
	{
	lpbmc->bcWidth = (unsigned short)lNewWidth;
	lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	int junzhi;
	for (i = 0; i<lHeight; i++)
	{
	bpDst = (BYTE*)bpNewDIBBits + lNewLineBytes*i;
	bpSrc = (BYTE*)lpDIBBits + lLineBytes*i;// 指向本行的象素指针
	for (j = 0; j<lWidth; j++)
	{
	if (bBitCount == 8)
	{
	bpDst[j] = bpSrc[j] > yuzhi ? 255 : 0;
	}
	else
	{
	junzhi = (bpSrc[j * 3 + scBlue] + bpSrc[j * 3 + scGreen] + bpSrc[j * 3 + scRed]) / 3;
	bpDst[j * 3 + scBlue] = bpDst[j * 3 + scGreen] = bpDst[j * 3 + scRed] = junzhi > yuzhi ? 255 : 0;
	}
	}
	}
	*/
	return NULL;
	
	
}
/************************************************
*
* 函数名称：
HGLOBAL ScanShow(LPSTR lpDIB)
阈值处理
* 参数:
*	LPSTR	lpDIB	- 指向DIB对象的指针
*
* 返回值:
*	LPSTR			- 指向DIB调色板的起始位置
*
* 说明:
*	图像的的扫描显示。
*****************************************************/
void FFT1D(ComplexNumber *ArrayBuf, int Length)
{
	ComplexNumber *Buf1 = new ComplexNumber[Length];//开辟内存空间 存储数据
	memcpy(Buf1, ArrayBuf, sizeof(ComplexNumber)*Length);
	ComplexNumber *Buf2 = new ComplexNumber[Length];
	//对ArrayBuf元素进行抽取排序
	int t1, t2;
	int r = 0, k = 1;
	int i;
	for (r = 1;pow(2, r) < Length;r++)
	{
		t1 = pow(2, r);
		t2 = pow(2, r - 1);
		for (k = 0;k<t1;k++)
			for (i = 0;i<Length / t1;i++)
				Buf2[k*Length / t1 + i] = Buf1[(k / 2)*(Length / t2) + i * 2 + k % 2];//* 2 * Length / t2 +
		memcpy(Buf1, Buf2, sizeof(ComplexNumber)*Length);
	}
	//蝶形算法FFT变换
	ComplexNumber temp;//中间变量
	double imag = 0, real = 0;
	for (r = 1;pow(2, r) <= Length;r++)
	{
		t1 = pow(2, r);
		//蝶形运算的复数乘旋转因子
		for (k = 0;k<Length / t1;k++)
		{
			for (i = t1 / 2;i < t1;i++)
			{
				temp.real = cos(-2 * PI*(i - t1 / 2) / t1);//利用欧拉公式 把旋转因子转换为复数一般形式
				temp.imag = sin(-2 * PI*(i - t1 / 2) / t1);
				Buf1[k*t1 + i] = Buf2[k*t1 + i] * temp;//注意 运算对象不能是指针
													   //Buf1[k*t1 + i].real = Buf2[k*t1 + i].real*real - Buf2[k*t1 + i].imag*imag;
													   //Buf1[k*t1 + i].imag = Buf2[k*t1 + i].real*imag - Buf2[k*t1 + i].imag*real;
			}
		}
		//蝶形运算的复数加法运算
		for (k = 0;k<Length / t1;k++)
		{
			for (i = 0;i < t1 / 2;i++)
				Buf2[k*t1 + i] = Buf1[k*t1 + i] + Buf1[k*t1 + i + t1 / 2];//注意 运算对象不能是指针
			for (i = t1 / 2;i < t1;i++)
				Buf2[k*t1 + i] = Buf1[k*t1 + i - t1 / 2] - Buf1[k*t1 + i];
		}
		memcpy(Buf1, Buf2, sizeof(ComplexNumber)*Length);
	}
	memcpy(ArrayBuf, Buf2, sizeof(ComplexNumber)*Length);
	delete[]Buf1;
	delete[]Buf2;
}

void FFT1D2(ComplexNumber *ArrayBuf, int Length)
{

	ComplexNumber *Buf1 = new ComplexNumber[Length];//开辟内存空间 存储数据
													//memcpy(Buf1, ArrayBuf, sizeof(ComplexNumber)*Length);
	ComplexNumber *Buf2 = new ComplexNumber[Length];
	//对ArrayBuf元素进行抽取排序
	int t1, t2;
	int r = 0, k = 0, wei = 0, i = 0;
	//抽取
	k = Length - 1;//实际位数是Length-1的位数长度
	while (k>0)
	{
		wei++;
		k = k >> 1;
	}
	int temp3 = 0, temp2 = 0;
	for (k = 0;k < Length;k++)
	{
		temp2 = k;
		for (r = 1;temp2>0;r++)
		{
			if (temp2 & 1)
			{
				temp3 += 1 << (wei - r);
			}
			temp2 = temp2 >> 1;
		}
		Buf2[k] = Buf1[k] = ArrayBuf[temp3];
		temp3 = 0;
	}
	//memcpy(Buf1, Buf2, sizeof(ComplexNumber)*Length);
	//蝶形算法FFT变换
	ComplexNumber temp;//中间变量
	double t3 = 0;
	for (r = 1;pow(2, r) <= Length;r++)
	{
		t3 = pow(2, r);
		t1 = (int)t3;
		//蝶形运算的复数乘旋转因子
		for (k = 0;k<Length/t1;k++)//当r=1时为0级 而r=m+1;而t1=pow(2,r)为旋转因子的N，i-(t1/2)代表旋转因子取值r(注意i从t1/2取值，每级旋转因子相乘正好取到每组的下半部分)
		{
			for (i = t1 / 2;i < t1;i++)
			{
				temp.real = cos(-2 * PI*(i - t3 / 2) / t3);//利用欧拉公式 把旋转因子转换为复数一般形式
				temp.imag = sin(-2 * PI*(i - t3 / 2) / t3);
				Buf2[k*t1 + i] = Buf1[k*t1 + i] * temp;//注意 运算对象不能是指针
													   //Buf1[k*t1 + i].real = Buf2[k*t1 + i].real*real - Buf2[k*t1 + i].imag*imag;
													   //Buf1[k*t1 + i].imag = Buf2[k* t1+ i].real*imag - Buf2[k*t1 + i].imag*real;
			}

		}
		//蝶形运算的复数加法运算
		for (k = 0;k<Length / t1;k++)
		{
			for (i = 0;i < t1 / 2;i++)
				Buf1[k*t1 + i] = Buf2[k*t1 + i] + Buf2[k*t1 + i + t1 / 2];//注意 运算对象不能是指针
			for (i = t1 / 2;i < t1;i++)
				Buf1[k*t1 + i] = Buf2[k*t1 + i - t1 / 2]-Buf2[k*t1 + i];
		}
		memcpy(Buf2, Buf1, sizeof(ComplexNumber)*Length);
	}
	memcpy(ArrayBuf, Buf1, sizeof(ComplexNumber)*Length);
	delete[]Buf1;
	delete[]Buf2;
}
/*
一维傅里叶变换的逆变换
*/
void IFFT1D(ComplexNumber *ArrayBuf, int Length)
{
	int i = 0;
	for (i = 0;i<Length;i++)//求复数的共轭
	{
		ArrayBuf[i].imag = -ArrayBuf[i].imag;
	}
	FFT1D(ArrayBuf, Length);//对共轭求FFT变换
	for (i = 0;i<Length;i++)//求复数的共轭并处以N
	{
		ArrayBuf[i] = ArrayBuf[i] / Length;//使用除法运算符的重载 / real imag 都除以同一个变量
	}
}
/*
图像的二维傅里叶变换
*/
BOOL FFT2D(LPSTR lpDIBBits, BYTE bBitCount, LONG lHeight, LONG lWidth, CImageCheDoc * pDoc)
{

	BYTE *bpSrc;
	double temp1 = 0, temp2 = 0, temp = 0;
	int m = 0;
	LONG length = 0, j, i, lLineBytes;
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	LONG i0 = 0, j0 = 0;
	if (bBitCount == 8)
	{
		pDoc->imageFFTbuf = new ComplexNumber[lHeight*lWidth];
		ComplexNumber *FFT1Dbuf = new ComplexNumber[lHeight];
		ComplexNumber *FFT1Dbuf2 = new ComplexNumber[lWidth];
		for (i = 0; i < lHeight; i++)
		{
			bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
			length = lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lWidth; j++)
			{
				pDoc->imageFFTbuf[length + j].real = bpSrc[j];
				pDoc->imageFFTbuf[length + j].imag = 0;
			}
		}

		for (j = 0; j < lWidth; j++) //进行纵向一维傅里叶变换
		{
			for (i = 0; i < lHeight; i++)
			{
				length = lLineBytes*(lHeight - 1 - i);
				FFT1Dbuf[lHeight - 1 - i] = pDoc->imageFFTbuf[length + j];
			}
			FFT1D(FFT1Dbuf, lHeight);
			//FFT1D2(FFT1Dbuf, lHeight);
			for (i = 0; i < lHeight; i++)
			{
				length = lLineBytes*(lHeight - 1 - i);
				pDoc->imageFFTbuf[length + j] = FFT1Dbuf[lHeight - 1 - i];
			}
		}

		for (i = 0; i < lHeight; i++)//进行横向一维变换
		{
			length = lLineBytes*(lHeight - 1 - i);
			memcpy(FFT1Dbuf2, pDoc->imageFFTbuf + length, sizeof(ComplexNumber)*lWidth);
			FFT1D(FFT1Dbuf2, lWidth);
			//FFT1D2(FFT1Dbuf, lHeight);
			memcpy(pDoc->imageFFTbuf + length, FFT1Dbuf2, sizeof(ComplexNumber)*lWidth);
			
		}
		//频域信息转换为幅值信息 存回新图像
		for (i = 0; i < lHeight; i++)
		{
			if (i < lHeight / 2)
				i0 = i + lHeight / 2;
			else
				i0 = i - lHeight / 2;
			bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
			length = lLineBytes*(lHeight - 1 - i0);
			for (j = 0; j < lWidth; j++)
			{
				if (j < lWidth / 2)
					j0 = j + lWidth / 2;
				else
					j0 = j - lWidth / 2;
				temp = pDoc->imageFFTbuf[length + j0].ComplexNumber_sqrt();
				temp = temp / 500;
				if (temp > 255)
					temp = 255;
				else
					if (temp < 0)
						temp = 0;

				bpSrc[j] = (BYTE)temp;
			}
		}
		delete[]FFT1Dbuf;
		delete[]FFT1Dbuf2;
		//delete[]imageFFTbuf;
	}
	else
	{
		pDoc->imageFFTbuf = new ComplexNumber[lHeight*lWidth * 3];
		ComplexNumber *IFFT1Dbuf = new ComplexNumber[lHeight];
		ComplexNumber *IFFT1Dbuf2 = new ComplexNumber[lWidth];
		for (m = 0;m < 3;m++)
		{

			for (i = 0; i < lHeight; i++)
			{
				bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
				length = lLineBytes*(lHeight - 1 - i);
				for (j = 0; j < lWidth; j++)
				{
					pDoc->imageFFTbuf[length + j * 3 + m].real = bpSrc[j * 3 + m];
					pDoc->imageFFTbuf[length + j * 3 + m].imag = 0;
				}
			}

			for (j = 0; j < lWidth; j++) //进行纵向一维傅里叶变换
			{
				//进行一维变换
				for (i = 0; i < lHeight; i++)
				{
					length = lLineBytes*(lHeight - 1 - i);
					IFFT1Dbuf[lHeight - 1 - i] = pDoc->imageFFTbuf[length + j * 3 + m];
				}
				FFT1D(IFFT1Dbuf, lHeight);

				for (i = 0; i < lHeight; i++)
				{
					length = lLineBytes*(lHeight - 1 - i);
					pDoc->imageFFTbuf[length + j * 3 + m] = IFFT1Dbuf[lHeight - 1 - i];
				}
			}


			/*
			for (i = 0; i < lHeight; i++)//进行横向一维变换
			{
			length = lLineBytes*(lHeight - 1 - i);
			///for (j = 0; j < lWidth; j++) //进行横向一维傅里叶变换
			//{
			//	FFT1Dbuf2[j] = imageFFTbuf[length + j];
			//memcpy(FFT1Dbuf2, imageFFTbuf+length + j, sizeof());
			memcpy(FFT1Dbuf2, imageFFTbuf + length, sizeof(ComplexNumber)*lWidth);
			// }
			FFT1D2(FFT1Dbuf2, lWidth);
			//for (j = 0; j < lWidth; j++) //进行横向一维傅里叶变换
			//{
			//	imageFFTbuf[length + j]=FFT1Dbuf2[j];
			memcpy(imageFFTbuf + length, FFT1Dbuf2, sizeof(ComplexNumber)*lWidth);
			//}
			}
			*/
			for (i = 0; i < lHeight; i++)//进行横向一维变换
			{
				length = lLineBytes*(lHeight - 1 - i);
				for (j = 0; j < lWidth; j++) //进行横向一维傅里叶变换
				{
					IFFT1Dbuf2[j] = pDoc->imageFFTbuf[length + j * 3 + m];
				}
				FFT1D(IFFT1Dbuf2, lWidth);
				for (j = 0; j < lWidth; j++) //进行横向一维傅里叶变换
				{
					pDoc->imageFFTbuf[length + j * 3 + m] = IFFT1Dbuf2[j];
				}
			}

			//频域信息转换为幅值信息 存回新图像
			for (i = 0; i < lHeight; i++)
			{
				if (i < lHeight / 2)
					i0 = i + lHeight / 2;
				else
					i0 = i - lHeight / 2;
				bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
				length = lLineBytes*(lHeight - 1 - i0);
				for (j = 0; j < lWidth; j++)
				{
					if (j < lWidth / 2)
						j0 = j + lWidth / 2;
					else
						j0 = j - lWidth / 2;
					temp = pDoc->imageFFTbuf[length + j0 * 3 + m].ComplexNumber_sqrt();
					temp = temp / 500;
					if (temp > 255)
						temp = 255;
					else
						if (temp < 0)
							temp = 0;

					bpSrc[j * 3 + m] = (BYTE)temp;
				}
			}
		}
		delete[]IFFT1Dbuf;
		delete[]IFFT1Dbuf2;
		//delete[]imageIFFTbuf;
	}
	return true;
}
HGLOBAL Fourier(LPSTR lpDIB, CImageCheDoc* pDoc)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LONG lLineBytes;
	BYTE *bpDIBBits;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	HGLOBAL hDIB;
	BYTE *bpDst;
	LPSTR lpNewDIB;
	BYTE *bpNewDIBBits;
	LPSTR lpDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));

	
	i = 1;
	while (i < lHeight)
	{
		*(pDoc->NewHeight) = i = i << 1;
	}
	i = 1;
	while (i < lWidth)
	{
		*(pDoc->NewWidth) = i = i << 1;
	}
	lNewWidth = *(pDoc->NewWidth);
	lNewHeight = *(pDoc->NewHeight);
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = ::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (LPSTR)::GlobalLock(hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits(lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;
	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	//对抽取不是2的指数形式的图进行填充
	if (bBitCount == 8)
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{
				if ((i < lHeight) && (j < lWidth))
				{
					bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
					bpDst[j] = bpSrc[j];
				}
				else
					bpDst[j] = 255;
			}
		}
	}
	else
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{
				if ((i < lHeight) && (j < lWidth))
				{
					bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
					bpDst[j * 3 + scRed] = bpSrc[j * 3 + scRed];
					bpDst[j * 3 + scBlue] = bpSrc[j * 3 + scBlue];
					bpDst[j * 3 + scGreen] = bpSrc[j * 3 + scGreen];
				}
				else
					bpDst[j * 3 + scGreen] = bpDst[j * 3 + scBlue] = bpDst[j * 3 + scRed] = 255;
			}
		}
	}

	lpDIBBits = FindDIBBits(lpNewDIB);
	FFT2D(lpDIBBits, bBitCount, lNewHeight, lNewWidth , pDoc);
	//ComplexNumber * imageIFFTbuf = NULL;
	//IFFT2D(imageFFTbuf,lpDIBBits,  bBitCount, lNewHeight, lNewWidth,imageIFFTbuf);
	return hDIB;
}
BOOL IFFT2D(ComplexNumber * imageFFTbuf, LPSTR lpDIBBits, BYTE bBitCount, LONG lHeight, LONG lWidth, ComplexNumber *imageIFFTbuf)
{
	if (imageFFTbuf == NULL)
	{
		AfxMessageBox("未对图像进行傅里叶变换，请先对图像进行傅里叶变换", MB_OK);
		return FALSE;
	}
	BYTE *bpSrc;
	double temp1 = 0, temp2 = 0, temp = 0;
	int m = 0;
	LONG length = 0, j, i, lLineBytes;
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	LONG i0 = 0, j0 = 0;
	if (bBitCount == 8)
	{
		imageIFFTbuf = new ComplexNumber[lHeight*lWidth];
		ComplexNumber *IFFT1Dbuf = new ComplexNumber[lHeight];
		ComplexNumber *IFFT1Dbuf2 = new ComplexNumber[lWidth];

		memcpy(imageIFFTbuf, imageFFTbuf, sizeof(ComplexNumber)*lWidth*lHeight);
		for (j = 0; j < lWidth; j++) //进行纵向一维傅里叶变换
		{
			//进行一维变换
			for (i = 0; i < lHeight; i++)
			{
				length = lLineBytes*(lHeight - 1 - i);
				IFFT1Dbuf[lHeight - 1 - i] = imageIFFTbuf[length + j];
			}
			IFFT1D(IFFT1Dbuf, lHeight);
			for (i = 0; i < lHeight; i++)
			{
				length = lLineBytes*(lHeight - 1 - i);
				imageIFFTbuf[length + j] = IFFT1Dbuf[lHeight - 1 - i];
			}
		}

		for (i = 0; i < lHeight; i++)//进行横向一维变换
		{
			length = lLineBytes*(lHeight - 1 - i);
			memcpy(IFFT1Dbuf2, imageIFFTbuf + length, sizeof(ComplexNumber)*lWidth);
			IFFT1D(IFFT1Dbuf2, lWidth);
			memcpy(imageIFFTbuf + length, IFFT1Dbuf2, sizeof(ComplexNumber)*lWidth);
		}
		//频域信息转换为幅值信息 存回新图像
		for (i = 0; i < lHeight; i++)
		{
			bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
			length = lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lWidth; j++)
			{
				temp = imageIFFTbuf[length + j].ComplexNumber_sqrt();
				//temp = temp / 5;
				if (temp > 255)
					temp = 255;
				else
					if (temp < 0)
						temp = 0;

				bpSrc[j] = (BYTE)temp;
			}
		}
		delete[]IFFT1Dbuf;
		delete[]IFFT1Dbuf2;
		delete[]imageIFFTbuf;
		imageIFFTbuf = NULL;
	}
	else
	{
		imageIFFTbuf = new ComplexNumber[lHeight*lWidth * 3];
		ComplexNumber *IFFT1Dbuf = new ComplexNumber[lHeight];
		ComplexNumber *IFFT1Dbuf2 = new ComplexNumber[lWidth];
		memcpy(imageIFFTbuf, imageFFTbuf, sizeof(ComplexNumber)*lWidth*lHeight * 3);
		for (m = 0;m < 3;m++)
		{
			for (j = 0; j < lWidth; j++) //进行纵向一维傅里叶变换
			{
				for (i = 0; i < lHeight; i++)
				{
					length = lLineBytes*(lHeight - 1 - i);
					IFFT1Dbuf[lHeight - 1 - i] = imageIFFTbuf[length + j * 3 + m];
				}
				IFFT1D(IFFT1Dbuf, lHeight);
				for (i = 0; i < lHeight; i++)
				{
					length = lLineBytes*(lHeight - 1 - i);
					imageIFFTbuf[length + j * 3 + m] = IFFT1Dbuf[lHeight - 1 - i];
				}
			}


			/*
			for (i = 0; i < lHeight; i++)//进行横向一维变换
			{
			length = lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lWidth; j++) //进行横向一维傅里叶变换
			{
			FFT1Dbuf2[j] = imageIFFTbuf[length + j];
			}
			FFT1D2(FFT1Dbuf2, lWidth);
			for (j = 0; j < lWidth; j++) //进行横向一维傅里叶变换
			{
			imageIFFTbuf[length + j] = FFT1Dbuf2[j];
			}
			}
			*/
			for (i = 0; i < lHeight; i++)//进行横向一维变换
			{
				length = lLineBytes*(lHeight - 1 - i);
				for (j = 0; j < lWidth; j++) //进行横向一维傅里叶变换
				{
					IFFT1Dbuf2[j] = imageIFFTbuf[length + j * 3 + m];
				}
				IFFT1D(IFFT1Dbuf2, lWidth);
				for (j = 0; j < lWidth; j++) //进行横向一维傅里叶变换
				{
					imageIFFTbuf[length + j * 3 + m] = IFFT1Dbuf2[j];
				}
			}
			//频域信息转换为幅值信息 存回新图像
			for (i = 0; i < lHeight; i++)
			{
				bpSrc = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
				length = lLineBytes*(lHeight - 1 - i);
				for (j = 0; j < lWidth; j++)
				{
					temp = imageIFFTbuf[length + j].ComplexNumber_sqrt();
					if (temp > 255)
						temp = 255;
					else
						if (temp < 0)
							temp = 0;
					bpSrc[j * 3 + m] = (BYTE)temp;
				}
			}
		}
		delete[]IFFT1Dbuf;
		delete[]IFFT1Dbuf2;
		delete[]imageIFFTbuf;
		imageIFFTbuf = NULL;
	}
	return true;
}
HGLOBAL IFourierEx(LPSTR lpDIB, ComplexNumber * imageFFTbuf, ComplexNumber * imageIFFTbuf, LONG FFTHeight, LONG FFTWidth)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	if (imageFFTbuf == NULL)
	{
		AfxMessageBox("未对图像进行傅里叶变换，请先对图像进行傅里叶变换", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LONG lLineBytes;
	BYTE *bpDIBBits;

	BYTE bNewBitCount;
	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	HGLOBAL hDIB;
	BYTE *bpDst;
	//BYTE *lpNewDIB;
	LPSTR lpNewDIB;
	BYTE *bpNewDIBBits;
	//LPSTR lNewpDIBBits;
	LPSTR lpDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bNewBitCount = bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	// 计算新DIB图像实际宽度和高度
	lNewWidth = FFTWidth;
	lNewHeight = FFTHeight;
	lNewLineBytes = (bNewBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));
	hDIB = ::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (LPSTR)::GlobalLock(hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits(lpNewDIB);
	lpDIBBits = FindDIBBits(lpNewDIB);
	IFFT2D(imageFFTbuf, lpDIBBits, bBitCount, lNewHeight, lNewWidth, imageIFFTbuf);

	/*开辟一个新的图像存储空间*/
	BYTE *bpDst2;
	HGLOBAL hDIB2;
	LPSTR lpNewDIB2;
	BYTE *bpNewDIBBits2;
	LPSTR lpDIBBits2;
	BYTE bNewBitCount2 = bBitCount;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	LONG lNewWidth2 = lWidth;
	LONG lNewHeight2 = lHeight;
	LONG lNewLineBytes2 = (bNewBitCount2 == 8 ? WIDTHBYTES(lNewWidth2 * 8) : WIDTHBYTES(lNewWidth2 * 24));

	hDIB2 = ::GlobalAlloc(GHND, lNewLineBytes2*lNewHeight2 * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB2 == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB2 = (LPSTR)::GlobalLock(hDIB2);
	memcpy(lpNewDIB2, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));

	bpNewDIBBits2 = (BYTE*)FindDIBBits(lpNewDIB2);
	//lpDIBBits2 = FindDIBBits(lpNewDIB2);

	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB2;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB2;
	if (IS_WIN30_DIB(lpNewDIB2))
	{
		lpbmi->biWidth = lNewWidth2;
		lpbmi->biHeight = lNewHeight2;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth2;
		lpbmc->bcHeight = (unsigned short)lNewHeight2;
	}
	//对抽取不是2的指数形式的图进行填充
	if (bBitCount == 8)
	{
		for (i = 0; i < lNewHeight2; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpDst2 = bpNewDIBBits2 + lNewLineBytes2*(lNewHeight2 - 1 - i);
			for (j = 0; j < lNewWidth2; j++)
			{
				bpDst2[j] = bpDst[j];
			}
		}
	}
	else
	{
		for (i = 0; i < lNewHeight2; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpDst2 = bpNewDIBBits2 + lNewLineBytes2*(lNewHeight2 - 1 - i);
			for (j = 0; j < lNewWidth2; j++)
			{
				bpDst2[j * 3 + scRed] = bpDst[j * 3 + scRed];
				bpDst2[j * 3 + scBlue] = bpDst[j * 3 + scBlue];
				bpDst2[j * 3 + scGreen] = bpDst[j * 3 + scGreen];
			}
		}
	}
	LocalUnlock(lpNewDIB);
	LocalFree(hDIB);
	return hDIB2;
}

//离散余弦变换
//#include <complex> 
/*
原函数：
Length 进行余弦变换的的图像的高度或者宽度的幂指数
图像的宽高必须为2的指数
widet=pow(2,length);
自己函数：直接把Length作为图像宽或者高传入
*/
BOOL DCT(double *f,double *F,int Length)
{
	int i = 0;
	double dtemp;
	ComplexNumber *array = new ComplexNumber[Length*2];//利用数据的2N点FFT变换可以得到该数据的离散正余弦变换
	if (array == NULL)
		return true;
	memset(array,0,sizeof(ComplexNumber)*Length*2);
	for (i = 0;i < Length;i++)
	{
		array[i].real = f[i];
		array[i].imag = 0;
	}
	FFT1D(array, Length*2);//调用快速傅里叶变换
   //调整系数
	//u=0是
	dtemp = sqrt(1.0/Length);
	F[0] = array[0].real*dtemp;
	dtemp = sqrt(2.0/Length);
	for (i = 1;i < Length;i++)
	{
		F[i] = (array[i].real*cos(i*PI / (Length * 2)) + array[i].imag*sin(i*PI / (Length * 2)))*dtemp;
	}
	delete[]array;
	return true;
}
/*
离散余弦反变换
*/
BOOL IDCT( double *F, double *f, int Length)
{
	int i = 0;
	double dtemp, d0;
	ComplexNumber *array = new ComplexNumber[Length * 2];//利用数据的2N点FFT变换可以得到该数据的离散正余弦变换
	if (array == NULL)
		return false;
	memset(array, 0, sizeof(ComplexNumber)*Length * 2);
	for (i = 0;i < Length;i++)
	{
		array[i].real = F[i]*cos(i*PI / (Length * 2));
		array[i].imag = F[i]*sin(i*PI / (Length * 2));
	}
	IFFT1D(array, Length * 2);//调用快速傅里叶变换
							 //调整系数
							 //u=0是
	dtemp = sqrt(2.0/ Length);
	d0 = (sqrt(1.0 / Length) - dtemp)*F[0];
	for (i = 0;i < Length;i++)
	{
		f[i] = d0 + array[i].real*dtemp*Length * 2;
	}
	delete[]array;
	return true;
}
BOOL DCT_2D(LPSTR lpDIBBits, BYTE bBitCount, LONG lHeight, LONG lWidth, CImageCheDoc * pDoc)
{
	LONG i, j;
	BYTE *bpDst;
	LONG lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	double *temp = NULL;
	BOOL IsTure = NULL;
    temp=new double[lHeight];
	if (temp == NULL)
		return false;
	double *temp2 = new double[lHeight];
	if (temp2 == NULL)
		return false;
	int m = 0;double num = 0;
	if (bBitCount == 8)
	{
		if (pDoc->DCT_F!= NULL)
		{
			delete[]pDoc->DCT_F;
			pDoc->DCT_F = NULL;
		}
		pDoc->DCT_F = new double[lHeight*lWidth];
		if (pDoc->DCT_F == NULL)
			return false;
		
		double *DCT_F_buf = new double[lHeight*lWidth];
		if (DCT_F_buf == NULL)
			return false;
		for (i = 0;i < lHeight;i++)
		{
			bpDst = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lWidth; j++)
			{
				DCT_F_buf[lWidth*(lHeight - 1 - i) + j] = bpDst[j];
			}
		}
		for (i = 0;i < lHeight;i++)
		{
			IsTure=DCT(DCT_F_buf + lWidth*(lHeight - 1 - i), pDoc->DCT_F + lWidth*(lHeight - 1 - i), lWidth);
			if (!IsTure)
				return false;
			IsTure = NULL;
		}
		//memcpy(pDoc->DCT_f, pDoc->DCT_F, sizeof(double)*lHeight*lWidth);
		for (j = 0;j < lWidth;j++)
		{
			for (i = 0;i < lHeight;i++)
				temp[lHeight - 1 - i] = pDoc->DCT_F[(lHeight - 1 - i)*lWidth + j];
			IsTure=DCT(temp, temp2, lHeight);
			if (!IsTure)
				return false;
			IsTure = NULL;
			for (i = 0;i < lHeight;i++)
				pDoc->DCT_F[(lHeight - 1 - i)*lWidth + j] = temp2[lHeight - 1 - i];
		}
		for (i = 0; i < lHeight; i++)
		{
			bpDst = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lWidth; j++)
			{
				num = fabs(pDoc->DCT_F[(lHeight - 1 - i)*lWidth + j]);
				bpDst[j] = (BYTE)num;
			}
		}
		delete[]DCT_F_buf;
		DCT_F_buf = NULL;
	}
	else
	{
		if (pDoc->DCT_F != NULL)
		{
			delete[]pDoc->DCT_F;
			pDoc->DCT_F = NULL;
		}
		pDoc->DCT_F = new double[lHeight*lWidth * 3];
		if (pDoc->DCT_F == NULL)
			return false;
		double *temp3 = new double[lHeight*lWidth];
		if (temp3 == NULL)
			return false;
		double *temp4 = new double[lHeight*lWidth];
		if (temp4 == NULL)
			return false;
		for (m=0;m<3;m++)
		{
			for (i = 0;i < lHeight;i++)
			{
				bpDst = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
				for (j = 0; j < lWidth; j++)
				{
					temp3[lWidth*(lHeight - 1 - i) + j] = bpDst[j * 3 + m];
				}
			}
			for (i = 0;i < lHeight;i++)
			{
				IsTure=DCT(temp3 + lWidth*(lHeight - 1 - i), temp4 + lWidth*(lHeight - 1 - i), lWidth);
				if (!IsTure)
					return false;
				IsTure = NULL;
			}
			//memcpy(temp3, temp4, sizeof(double)*lHeight*lWidth);
			for (j = 0;j < lWidth;j++)
			{
				for (i = 0;i < lHeight;i++)
					temp[lHeight - 1 - i] = temp4[(lHeight - 1 - i)*lWidth + j];
				IsTure=DCT(temp, temp2, lHeight);
				if (!IsTure)
					return false;
				IsTure = NULL;
				for (i = 0;i < lHeight;i++)
					temp4[(lHeight - 1 - i)*lWidth + j] = temp2[lHeight - 1 - i];
			}
			for (i = 0;i < lHeight;i++)
			{
				bpDst =(BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
				for (j = 0; j < lWidth; j++)
				{
					pDoc->DCT_F[lWidth*(lHeight - 1 - i) + j*3+m] = temp4[lWidth*(lHeight - 1 - i) + j];
					num = fabs(pDoc->DCT_F[lWidth*(lHeight - 1 - i) + j * 3 + m]); 
					bpDst[j * 3 + m] = (BYTE)num;
				}
			}

		}
		delete[]temp3;
		temp3 = NULL;
		delete[]temp4;
	}
	delete[]temp;
	temp = NULL;
	delete[]temp2;
	temp2 = NULL;
	return true;
}
HGLOBAL img_DCT(LPSTR lpDIB, CImageCheDoc* pDoc)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LONG lLineBytes;
	BYTE *bpDIBBits;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	HGLOBAL hDIB;
	BYTE *bpDst;
	LPSTR lpNewDIB;
	BYTE *bpNewDIBBits;
	LPSTR lpDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	i = 1;
	while (i < lHeight)
	{
		*(pDoc->NewHeight) = i = i << 1;
	}
	i = 1;
	while (i < lWidth)
	{
		*(pDoc->NewWidth) = i = i << 1;
	}
	lNewWidth = *(pDoc->NewWidth);
	lNewHeight = *(pDoc->NewHeight);
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));
	hDIB = ::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (LPSTR)::GlobalLock(hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits(lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;
	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	//对抽取不是2的指数形式的图进行填充
	if (bBitCount == 8)
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{
				if ((i < lHeight) && (j < lWidth))
				{
					bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
					bpDst[j] = bpSrc[j];
				}
				else
					bpDst[j] = 255;
			}
		}
	}
	else
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{
				if ((i < lHeight) && (j < lWidth))
				{
					bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
					bpDst[j * 3 + scRed] = bpSrc[j * 3 + scRed];
					bpDst[j * 3 + scBlue] = bpSrc[j * 3 + scBlue];
					bpDst[j * 3 + scGreen] = bpSrc[j * 3 + scGreen];
				}
				else
					bpDst[j * 3 + scGreen] = bpDst[j * 3 + scBlue] = bpDst[j * 3 + scRed] = 255;
			}
		}
	}
	lpDIBBits = FindDIBBits(lpNewDIB);
	BOOL IsTure = NULL;
	IsTure=DCT_2D( lpDIBBits,  bBitCount, lNewHeight, lNewWidth,pDoc);
	if(!IsTure)
	return NULL;

	return hDIB;
}

BOOL IDCT2D(LPSTR lpDIBBits, BYTE bBitCount, LONG lHeight, LONG lWidth, CImageCheDoc * pDoc)
{
	LONG i, j;
	BYTE *bpDst;
	LONG lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	double *temp = NULL;
	temp = new double[lHeight];
	if (temp == NULL)
		return false;
	double *temp2 = new double[lHeight];
	if (temp2 == NULL)
		return false;
	int m = 0;double num = 0;
	if (bBitCount == 8)
	{
		if (pDoc->DCT_f != NULL)
		{
			delete[]pDoc->DCT_f;
			pDoc->DCT_f = NULL;
		}
		pDoc->DCT_f = new double[lHeight*lWidth];
		if (pDoc->DCT_f == NULL)
			return false;
		for (i = 0;i < lHeight;i++)
		{
			IDCT(pDoc->DCT_F + lWidth*(lHeight - 1 - i),pDoc->DCT_f + lWidth*(lHeight - 1 - i), lWidth);
		}
		//memcpy(pDoc->DCT_f, pDoc->DCT_f, sizeof(double)*lHeight*lWidth);
		for (j = 0;j < lWidth;j++)
		{
			for (i = 0;i < lHeight;i++)
				temp[lHeight - 1 - i] = pDoc->DCT_f[(lHeight - 1 - i)*lWidth + j];
			IDCT(temp, temp2, lHeight);
			for (i = 0;i < lHeight;i++)
				pDoc->DCT_f[(lHeight - 1 - i)*lWidth + j] = temp2[lHeight - 1 - i];
		}
		for (i = 0; i < lHeight; i++)
		{
			bpDst = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
			for (j = 0; j < lWidth; j++)
			{
				num = fabs(pDoc->DCT_f[(lHeight - 1 - i)*lWidth + j]);
				bpDst[j] = (BYTE)num;
			}
		}
	}
	else
	{
		if (pDoc->DCT_f != NULL)
		{
			delete[]pDoc->DCT_f;
			pDoc->DCT_f = NULL;
		}
		pDoc->DCT_f = new double[lHeight*lWidth * 3];
		if (pDoc->DCT_f == NULL)
			return false;
		double *temp3 = new double[lHeight*lWidth];
		if (temp3 == NULL)
			return false;
		double *temp4 = new double[lHeight*lWidth];
		if (temp4 == NULL)
			return false;
		for (m = 0;m<3;m++)
		{
			for (i = 0;i < lHeight;i++)
			{
				bpDst = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
				for (j = 0; j < lWidth; j++)
				{
					temp3[lWidth*(lHeight - 1 - i) + j] = pDoc->DCT_f[lWidth*(lHeight - 1 - i) + j * 3 + m];
				}
			}
			for (i = 0;i < lHeight;i++)
			{
				IDCT(temp3 + lWidth*(lHeight - 1 - i), temp4 + lWidth*(lHeight - 1 - i), lWidth);
			}
			//memcpy(temp3, temp4, sizeof(double)*lHeight*lWidth);
			for (j = 0;j < lWidth;j++)
			{
				for (i = 0;i < lHeight;i++)
					temp[lHeight - 1 - i] = temp4[(lHeight - 1 - i)*lWidth + j];
				IDCT(temp, temp2, lHeight);
				for (i = 0;i < lHeight;i++)
					temp4[(lHeight - 1 - i)*lWidth + j] = temp2[lHeight - 1 - i];
			}
			for (i = 0;i < lHeight;i++)
			{
				bpDst = (BYTE*)lpDIBBits + lLineBytes*(lHeight - 1 - i);
				for (j = 0; j < lWidth; j++)
				{
					pDoc->DCT_f[lWidth*(lHeight - 1 - i) + j * 3 + m] = temp4[lWidth*(lHeight - 1 - i) + j];
					num = fabs(pDoc->DCT_f[lWidth*(lHeight - 1 - i) + j * 3 + m]);
					bpDst[j * 3 + m] = (BYTE)num;
				}
			}

		}
		delete[]temp3;
		temp3 = NULL;
		delete[]temp4;
		//delete[]pDoc->DCT_f;
		//pDoc->DCT_f = NULL;
	}
	delete[]temp;
	temp = NULL;
	delete[]temp2;
	temp2 = NULL;
	return true;
}

HGLOBAL img_IDCT(LPSTR lpDIB, CImageCheDoc* pDoc)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	if (pDoc->DCT_F == NULL)
	{
		AfxMessageBox("未对图像进行离散余弦变换，请先对图像进行离散余弦变换", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LONG lLineBytes;
	BYTE *bpDIBBits;

	BYTE bNewBitCount;
	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	HGLOBAL hDIB;
	BYTE *bpDst;
	//BYTE *lpNewDIB;
	LPSTR lpNewDIB;
	BYTE *bpNewDIBBits;
	//LPSTR lNewpDIBBits;
	LPSTR lpDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bNewBitCount = bBitCount = DIBBitCount(lpDIB);

	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	// 计算新DIB图像实际宽度和高度
	lNewWidth = *pDoc->NewWidth;
	lNewHeight = *pDoc->NewHeight;
	lNewLineBytes = (bNewBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));
	hDIB = ::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (LPSTR)::GlobalLock(hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits(lpNewDIB);
	lpDIBBits = FindDIBBits(lpNewDIB);
	BOOL IsTure = NULL;
	IsTure = IDCT2D(lpDIBBits, bNewBitCount, lNewHeight, lNewWidth, pDoc);
	if (!IsTure)
		return NULL;
	/*开辟一个新的图像存储空间*/
	BYTE *bpDst2;
	HGLOBAL hDIB2;
	LPSTR lpNewDIB2;
	BYTE *bpNewDIBBits2;
	LPSTR lpDIBBits2;
	BYTE bNewBitCount2 = bBitCount;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	LONG lNewWidth2 = lWidth;
	LONG lNewHeight2 = lHeight;
	LONG lNewLineBytes2 = (bNewBitCount2 == 8 ? WIDTHBYTES(lNewWidth2 * 8) : WIDTHBYTES(lNewWidth2 * 24));

	hDIB2 = ::GlobalAlloc(GHND, lNewLineBytes2*lNewHeight2 * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB2 == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB2 = (LPSTR)::GlobalLock(hDIB2);
	memcpy(lpNewDIB2, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));

	bpNewDIBBits2 = (BYTE*)FindDIBBits(lpNewDIB2);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB2;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB2;
	if (IS_WIN30_DIB(lpNewDIB2))
	{
		lpbmi->biWidth = lNewWidth2;
		lpbmi->biHeight = lNewHeight2;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth2;
		lpbmc->bcHeight = (unsigned short)lNewHeight2;
	}
	//对抽取不是2的指数形式的图进行填充
	if (bBitCount == 8)
	{
		for (i = 0; i < lNewHeight2; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpDst2 = bpNewDIBBits2 + lNewLineBytes2*(lNewHeight2 - 1 - i);
			for (j = 0; j < lNewWidth2; j++)
			{
				bpDst2[j] = bpDst[j];
			}
		}
	}
	else
	{
		for (i = 0; i < lNewHeight2; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			bpDst2 = bpNewDIBBits2 + lNewLineBytes2*(lNewHeight2 - 1 - i);
			for (j = 0; j < lNewWidth2; j++)
			{
				bpDst2[j * 3 + scRed] = bpDst[j * 3 + scRed];
				bpDst2[j * 3 + scBlue] = bpDst[j * 3 + scBlue];
				bpDst2[j * 3 + scGreen] = bpDst[j * 3 + scGreen];
			}
		}
	}
	LocalUnlock(lpNewDIB);
	LocalFree(hDIB);
	return hDIB2;
}


HGLOBAL RestoreExt(LPSTR lpDIB, CImageCheDoc* pDoc)
{
	if (lpDIB == NULL || (DIBBitCount(lpDIB) != 8 && DIBBitCount(lpDIB) != 24))
	{
		AfxMessageBox("输入参数有误！", MB_OK);
		return FALSE;
	}
	BYTE bBitCount;
	LONG lWidth;
	LONG lHeight;
	BYTE *bpSrc;
	LONG lLineBytes;
	BYTE *bpDIBBits;

	LONG lNewWidth;
	LONG lNewHeight;
	LONG lNewLineBytes;
	HGLOBAL hDIB;
	BYTE *bpDst;
	LPSTR lpNewDIB;
	BYTE *bpNewDIBBits;
	LPSTR lpDIBBits;

	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	LONG i;
	LONG j;
	lpDIBBits = FindDIBBits(lpDIB);
	bpDIBBits = (BYTE*)FindDIBBits(lpDIB);
	lWidth = DIBWidth(lpDIB);
	lHeight = DIBHeight(lpDIB);
	bBitCount = DIBBitCount(lpDIB);
	lLineBytes = (bBitCount == 8 ? WIDTHBYTES(lWidth * 8) : WIDTHBYTES(lWidth * 24));
	i = 1;
	while (i < lHeight)
	{
		*(pDoc->NewHeight) = i = i << 1;
	}
	i = 1;
	while (i < lWidth)
	{
		*(pDoc->NewWidth) = i = i << 1;
	}
	lNewWidth = *(pDoc->NewWidth);
	lNewHeight = *(pDoc->NewHeight);
	lNewLineBytes = (bBitCount == 8 ? WIDTHBYTES(lNewWidth * 8) : WIDTHBYTES(lNewWidth * 24));

	hDIB = ::GlobalAlloc(GHND, lNewLineBytes*lNewHeight * sizeof(BYTE) + (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	if (hDIB == NULL)
	{
		AfxMessageBox("内存分配有误！", MB_OK);
		return NULL;
	}
	lpNewDIB = (LPSTR)::GlobalLock(hDIB);
	memcpy(lpNewDIB, lpDIB, (*(LPDWORD)lpDIB) + PaletteSize(lpDIB));
	bpNewDIBBits = (BYTE*)FindDIBBits(lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;
	if (IS_WIN30_DIB(lpNewDIB))
	{
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}
	//对抽取不是2的指数形式的图进行填充
	if (bBitCount == 8)
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{
				if ((i < lHeight) && (j < lWidth))
				{
					bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
					bpDst[j] = bpSrc[j];
				}
				else
					bpDst[j] = 255;
			}
		}
	}
	else
	{
		for (i = 0; i < lNewHeight; i++)
		{
			bpDst = bpNewDIBBits + lNewLineBytes*(lNewHeight - 1 - i);
			for (j = 0; j < lNewWidth; j++)
			{
				if ((i < lHeight) && (j < lWidth))
				{
					bpSrc = bpDIBBits + lLineBytes*(lHeight - 1 - i);
					bpDst[j * 3 + scRed] = bpSrc[j * 3 + scRed];
					bpDst[j * 3 + scBlue] = bpSrc[j * 3 + scBlue];
					bpDst[j * 3 + scGreen] = bpSrc[j * 3 + scGreen];
				}
				else
					bpDst[j * 3 + scGreen] = bpDst[j * 3 + scBlue] = bpDst[j * 3 + scRed] = 255;
			}
		}
	}

	lpDIBBits = FindDIBBits(lpNewDIB);
	FFT2D(lpDIBBits, bBitCount, lNewHeight, lNewWidth, pDoc);
	return hDIB;
}


