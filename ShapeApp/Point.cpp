#include "stdafx.h"
#include "Point.h"

void Point::draw(HDC hdc) 
{
	HPEN hpen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HBRUSH hbr = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hpen);
	SelectObject(hdc, hbr);
	Ellipse(hdc, x - 10, y - 10, x + 10, y + 10);
	for (int i = -5; i <= 5; i++)
		SetPixel(hdc, x + i, y, RGB(0, 0, 0));
	for (int i = -5; i <= 5; i++)
		SetPixel(hdc, x, y + i, RGB(0, 0, 0));
	DeleteObject(hpen);
	DeleteObject(hbr);
} 
double Point::calcULateDistance(Point b) const 
{ 
	double dx = x - b.x, dy = y - b.y; 
	return sqrt(dx * dx + dy * dy); 
}
