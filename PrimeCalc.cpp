#include "stdafx.h"
#include "PrimeCalc.h"
#include <algorithm>

using namespace std;

#ifdef _DEBUG
#define ASSERT(P) do { if(!(P)) MessageBox(NULL, L"Assertion Failed!", L"Assertion \"" L#P L"\" failed!", MB_ICONHAND); } while(false)
#else
#define ASSERT(P)
#endif

template <class T>
class WndObject
{
	//Cant copy
	WndObject(const WndObject&);
	WndObject& operator = (const WndObject&);
public:
	WndObject() : m_obj(nullptr){}
	WndObject(T obj):m_obj(obj){}

	//Move
	WndObject(WndObject && that) : m_obj(NULL) { using std::swap; swap(m_obj, that.m_obj); }
	WndObject& operator = (WndObject && that) { using std::swap; swap(m_obj, that.m_obj); return *this; }

	~WndObject() { if (m_obj) DeleteObject(m_obj); }

	T operator*() const { return m_obj; }

private:
	T m_obj;
};

int Width(const RECT& rect) { return rect.right - rect.left; }
int Height(const RECT& rect) { return rect.bottom - rect.top; }
POINT Center(const RECT& rect)
{
	POINT pt;
	pt.x = rect.left + Width(rect) / 2;
	pt.y = rect.top + Height(rect) / 2;
	return pt;
}


// number = 4 (spiral * spiral + spiral)
// spiral = (sqrt(number + 1) - 1) / 2

/*
15 14 13 12 11
16  3  2  1 10
17  4  .  0 9
18  5  6  7 8
19 20 21 22 23 24

0 -> spiral 0
8 -> spiral 1
24 -> spiral 2
*/

int CalcNumber(int spiral) { return 4 * (spiral * spiral + spiral); }
int CalcSpiral(int number) { return (int)((sqrt(number + 1) - 1) / 2); }
POINT CalcPoint(int number)
{
	int spiral					= CalcSpiral(number);
	int numberSpiralBegin		= CalcNumber(spiral);
	int numberOffsetSpiralBegin	= number - numberSpiralBegin;
	POINT pt;
	pt.x = spiral + 1;
	pt.y = spiral;
	int spiralSize		= CalcNumber(spiral + 1) - numberSpiralBegin;
	int spiralEdgeSize	= spiralSize / 4;
	int edgeOfNumber	= numberOffsetSpiralBegin / spiralEdgeSize;

	int numberOffsetOfCorner = numberOffsetSpiralBegin - spiralEdgeSize * edgeOfNumber;
	switch (edgeOfNumber)
	{
	case 0: //Up
		pt.y -= numberOffsetOfCorner;
		break;
	case 1: //Left
		pt.x -= numberOffsetOfCorner;
		pt.y -= spiralEdgeSize;
		break;
	case 2: //Down
		pt.x -= spiralEdgeSize;
		pt.y -= spiralEdgeSize - numberOffsetOfCorner;
		break;
	case 3: //Right
		pt.x -= spiralEdgeSize - numberOffsetOfCorner;
		break;
	default: ASSERT(false); //Should not happen
	}

	return pt;
}

void DrawPrimeSpiral(HDC hdc, const RECT& rect)
{
	WndObject<HBRUSH> brush = CreateSolidBrush(RGB(0,0,0));
	FillRect(hdc, &rect, *brush);
//	Sleep(1000);
//	brush = CreateSolidBrush(RGB(255, 0, 0));
//	FillRect(hdc, &rect, *brush);

	int wh = max(Width(rect), Height(rect));
	int end = wh * wh;
	POINT pt = Center(rect);
	for (int i = 0; i < end; ++i)
	{
		
	}
}

/*
				17 16 15 14 13
                18  5  4  3 12
                19  6  1  2 11
				20  7  8  9 10
				21 22 23 24 25
*/