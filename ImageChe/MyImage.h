
#ifndef _INC_DIBAPI
#define _INC_DIBAPI
#include "math.h"

#include "Inter_Num.h"
#include "Hist.h"
#include <string.h>
#include "ComplexNumber.h"//复数类
class CImageCheDoc;//在此处声明类 不能在此处包含类头文件 会造成重复包含 声明之后就可以在声明 方法是使用这个类

enum nSourceChannel
{
	scBlue = 0,
	scGreen = 1,
	scRed = 2,
};

/* DIB句柄*************/
DECLARE_HANDLE(HDIB);
/* DIB文件头标志（字符串"BM"，写DIB时用到该常数）**/
#define DIB_HEADER_MARKER ((WORD)('M'<<8)|'B')

#define IS_WIN30_DIB(lpDIB) ((*(LPDWORD)(lpDIB))==sizeof(BITMAPINFOHEADER))// 判断是否是Win 3.0的DIB
// 计算矩形区域的宽度
#define RECTWIDTH(lpRect) ((lpRect)->right-(lpRect)->left)
// 计算矩形区域的高度
#define RECTHEIGHT(lpRect) ((lpRect)->bottom-(lpRect)->top)

/* 在计算图像大小时，采用公式：biSizeImage=biWidth' × biHeight。是biWidth'，
而不是biWidth，这里的biWidth'必须是4的整倍数，表示
大于或等于biWidth的，离4最近的整倍数。WIDTHBYTES就是用来计算
biWidth'
****************************************************/
#define WIDTHBYTES(bits) (((bits)+31)/32*4)
/* 该函数将输入的双精度变量转换为BYTE(unsigned char)型的变量*/
inline BYTE DoubleToByte(double d)
{
	if (d <= 0)
	{
		return (BYTE)0;
	}
	else
	{
		if (d >= 254.5)
		{
			return (BYTE)255;
		}
		else
		{
			return (BYTE)(d + 0.5);
		}
	}
}
DWORD	DIBWidth(LPSTR lpDIB);
DWORD	DIBHeight(LPSTR lpDIB);
BOOL	PaintDIB(HDC hDC, LPRECT lpDCRect, HDIB hDIB, LPRECT lpDIBRect);
LPSTR	FindDIBBits(LPSTR lpDIB);
LPSTR	FindPalette(LPSTR lpDIB);
WORD	DIBNumColors(LPSTR lpDIB);
WORD	PaletteSize(LPSTR lpDIB);
BYTE    DIBBitCount(LPSTR lpDIB);
inline LONG IF_BilinearInterpolation(LPSTR lpDIBBits, BYTE bBitCount, LONG lWidth, LONG lHeight, double dX, double dY);
HGLOBAL SSJZLBtogramProcess(LPSTR lpDIB, int n);
HGLOBAL SSJZtogramProcess(LPSTR lpDIB);
HGLOBAL JHJZtogramProcess(LPSTR lpDIB);
HGLOBAL KYStogramProcess(LPSTR lpDIB);
HGLOBAL NXBJZtogramProcess(LPSTR lpDIB, double Q);
HGLOBAL XBJZtogramProcess(LPSTR lpDIB);
HGLOBAL BianJietogramProcess(LPSTR lpDIB);
HGLOBAL ZhognzhitogramProcess(LPSTR lpDIB);
HGLOBAL YuzhitogramProcess(LPSTR lpDIB, int yuzhi);
HGLOBAL HistAvetogramProcess(LPSTR lpDIB);
BOOL HistFazhiProcess(LPSTR lpDIBBits, BYTE bBitCount, LONG lWidth, LONG lHeight, int nThre);
BOOL HistXxingProcess(LPSTR lpDIBBits, BYTE bBitCount, LONG lWidth, LONG lHeight, double dK, int nB);
BOOL HistAvetogramProcess_select(LPSTR lpDIBBits, BYTE bBitCount, LONG lWidth, LONG lHeight, int selection);
BOOL HistAvetogramProcess_Green(LPSTR lpDIBBits, BYTE bBitCount, LONG lWidth, LONG lHeight);
BOOL HistAvetogramProcess_RED(LPSTR lpDIBBits, BYTE bBitCount, LONG lWidth, LONG lHeight);
BOOL HistAvetogramProcess_Blue(LPSTR lpDIBBits, BYTE bBitCount, LONG lWidth, LONG lHeight);
HGLOBAL BasicErosionForBinary(LPSTR lpDIB);
HGLOBAL BasicDilationForBinary(LPSTR lpDIB);
HGLOBAL BinaryOpen(LPSTR lpDIB);
HGLOBAL BinaryClose(LPSTR lpDIB);
HGLOBAL FillHoles(LPSTR lpDIB, CPoint point);
HGLOBAL BinaryOutEdge(LPSTR lpDIB);
HGLOBAL BinaryInterEdge(LPSTR lpDIB);
HGLOBAL BinaryContour(LPSTR lpDIB);
HGLOBAL XXtogramProcess(LPSTR lpDIB, double k, double b);
HGLOBAL ZhognzhitogramProcess(LPSTR lpDIB);
HGLOBAL	GeoProcess(LPSTR lpDIB);
HGLOBAL PY_GeoProcess(LPSTR lpDIB, unsigned int hang);
HGLOBAL XHPY_GeoProcess(LPSTR lpDIB, unsigned int hang);
HGLOBAL XZ_GeoProcess(LPSTR lpDIB, double du);
BYTE * SXXZZ(LONG lLineBytes, LPSTR lpDIBBits, LONG lHeight, LONG lWidth, BYTE bBitCount, double i1, double j1);
HGLOBAL GradSharp(LPSTR lpDIB, BYTE threshold);
HGLOBAL LapTemplateSharp(LPSTR lpDIB, double K);
HGLOBAL RobertsTemplateSharp(LPSTR lpDIB);
HGLOBAL PrewittTemplateSharp(LPSTR lpDIB);
HGLOBAL SobelTemplateSharp(LPSTR lpDIB);
HGLOBAL threshOtus(LPSTR lpDIB, double K);
HGLOBAL Prewitt(LPSTR lpDIB);
HGLOBAL MosaictogramProcess(LPSTR lpDIB, int n);
HGLOBAL ZoomDblLinear(LPSTR lpDIB, double Kx, double Ky);
BOOL GetHist(LPSTR lpDIBBits, BYTE bBitCount, LONG lHeight, LONG lWidth, unsigned int * p, BYTE tongdao);
void Get_JunZhiAndFangCha(unsigned int *p, unsigned int Length, double *JunZhi, double *FangCha);
BOOL HistProcess_Red(LPSTR lpDIB, double *JunZhi, double *FangCha);
BOOL HistProcess_Blue(LPSTR lpDIB, double *JunZhi, double *FangCha);
BOOL HistProcess_RGB(LPSTR lpDIB, double *JunZhi, double *FangCha);
BOOL HistProcess_Green(LPSTR lpDIB, double *JunZhi, double *FangCha);
BOOL HistProcess_Huidu(LPSTR lpDIB, double *JunZhi, double *FangCha);
HGLOBAL HistProcess(LPSTR lpDIB, BYTE yuzhi);
HGLOBAL fuxiangProcess(LPSTR lpDIB);
HGLOBAL zhuangzhiProcess(LPSTR lpDIB);
HGLOBAL shuipingjingxiangProcess(LPSTR lpDIB);
HGLOBAL chuizhijingxiangProcess(LPSTR lpDIB);
HGLOBAL HistJunHengProcess(LPSTR lpDIB);
HGLOBAL DuiShuStrechProcess(LPSTR lpDIB, double a, double b, double c);
HGLOBAL ZhiShuStrechProcess(LPSTR lpDIB, double a, double b, double c);
HGLOBAL ScanShow(LPSTR lpDIB);
HGLOBAL Fourier(LPSTR lpDIB, CImageCheDoc *pDoc);
void FFT1D(ComplexNumber *ArrayBuf, int Length);
void FFT1D2(ComplexNumber *ArrayBuf, int Length);
void IFFT1D(ComplexNumber *ArrayBuf, int Length);
BOOL FFT2D(LPSTR lpDIBBits, BYTE bBitCount, LONG lHeight, LONG lWidth, CImageCheDoc* pDoc);
BOOL IFFT2D(ComplexNumber * imageFFTbuf, LPSTR lpDIBBits, BYTE bBitCount, LONG lHeight, LONG lWidth, ComplexNumber *imageIFFTbuf);
HGLOBAL IFourierEx(LPSTR lpDIB, ComplexNumber * imageFFTbuf, ComplexNumber * imageIFFTbuf, LONG FFTHeight, LONG FFTWidth);
BOOL DCT(double *f, double *F, int Length);
BOOL IDCT(double *F, double *f, int Length);
BOOL DCT_2D(LPSTR lpDIBBits, BYTE bBitCount, LONG lHeight, LONG lWidth, CImageCheDoc * pDoc);
HGLOBAL img_DCT(LPSTR lpDIB, CImageCheDoc* pDoc);
BOOL IDCT2D(LPSTR lpDIBBits, BYTE bBitCount, LONG lHeight, LONG lWidth, CImageCheDoc * pDoc);
HGLOBAL img_IDCT(LPSTR lpDIB, CImageCheDoc* pDoc);
 #endif 