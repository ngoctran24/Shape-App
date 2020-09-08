#include "stdafx.h"
#include "Shape.h"

double areaTria(Point A, Point B, Point C)
{
	return abs((A.getX() * (B.getY() - C.getY()) + B.getX() * (C.getY() - A.getY()) + C.getX() * (A.getY() - B.getY())) / 2.0);
}

void fill(CShape* pS, HDC hdc, int flag)
{
	HPEN hpen;
	HBRUSH hbr;
	if (!(flag % 2))
	{
		hpen = CreatePen(PS_SOLID, 2 * (flag + 1), RGB(255, 0, 150));
		hbr = CreateSolidBrush(RGB(255, 255, 255));
	}
	else
	{
		hpen = CreatePen(PS_SOLID, 2 * flag, RGB(255, 0, 0));
		hbr = CreateSolidBrush(RGB(0, 255, 255));
	}
	SelectObject(hdc, hpen);
	SelectObject(hdc, hbr);
	pS->draw(hdc);
	DeleteObject(hpen);
	DeleteObject(hbr);
}