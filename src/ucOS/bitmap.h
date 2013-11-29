#ifndef _BITMAP_H
#define _BITMAP_H
/*
typedef struct _strPoint
{
	int x;
	int y;
}Point;*/

//struct Rect
//{
//	int x1;
//	int y1;
//	int x2;
//	int y2;
//};
/*
typedef struct _strRect
{
	int x1;
	int y1;
	int x2;
	int y2;
}Rect;*/

// 使得(x1, y1)成为左上角点，(x2, y2)成为右下角点。
/*
void NormalizeRect(Rect * pRect)
{
	int temp;
	if (pRect->x1 > pRect->x2)
	{
		temp = pRect->x1;
		pRect->x1 = pRect->x2;
		pRect->x2 = temp;
	}
	if (pRect->y1 > pRect->y2)
	{
		temp = pRect->y1;
		pRect->y1 = pRect->y2;
		pRect->y2 = temp;
	}
}*/

typedef struct _strRGB
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}RGB;

typedef struct _strRGB16
{
	unsigned char clrLow;
	unsigned char clrHigh;
}RGB16;

typedef struct _strBMP24
{
	unsigned char * pArray;
	int width;
	int height;
}BMP24;

typedef struct _strBMP16
{
	const unsigned char * pArray;
	int width;
	int height;
}BMP16;

// 破环性颠倒
void ReverseBMP24(BMP24 bmp);
RGB16 ParseRGB24to16(unsigned char r, unsigned char g, unsigned char b);
void DrawBitMap();

#endif
