#include "stdafx.h"
#include "Point.h"
#include "Shape.h"
#include "Poly.h"

void StraightLine::draw(HDC hdc)
{
	HPEN hpen;
	hpen = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
	SelectObject(hdc, hpen);
	POINT line[2] = { { A.getX(), A.getY() }, { B.getX(), B.getY() } };
	Polyline(hdc, line, 2);
	DeleteObject(hpen);
}
void StraightLine::pointOnLine(CShape* aS[][7], int* flag, int* arr, int n)
{
	Point tmp;
	int temp = 0;
	for (double u = 0.0; u <= 1.0; u += 0.03125)
	{
		tmp.setX(A.getX() + u * (B.getX() - A.getX()));
		tmp.setY(A.getY() + u * (B.getY() - A.getY()));
		for (int i = 0; i < n; i++)
		{
			if (!(flag[i] % 2) && aS[i][arr[i]]->pointInShape(tmp))
			{
				flag[i]++;
				temp++;
			}
		}
		if (temp == n) break;
	}
}

void Curve::draw(HDC hdc)
{
	HPEN hpen, hpen1;
	hpen = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
	SelectObject(hdc, hpen);
	POINT line[4] = { { A.getX(), A.getY() }, { B.getX(), B.getY() }, { C.getX(), C.getY() }, { D.getX(), D.getY() } };
	PolyBezier(hdc, line, 4);

	hpen1 = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SelectObject(hdc, hpen1);
	for (int i = 0; i < 3; i++)
	{
		POINT line1[] = { { line[i].x, line[i].y }, { line[i + 1].x, line[i + 1].y } };
		Polyline(hdc, line1, 2);
	}
	DeleteObject(hpen);
	DeleteObject(hpen1);
}
void Curve::pointOnLine(CShape* aS[][7], int* flag, int* arr, int n)
{
	Point tmp;
	int temp = 0;
    for(double u
		= 0.0; u <= 1.0; u += 0.03125)
    {
        tmp.setX(pow(1 - u, 3)*A.getX() + 3*u*pow(1 - u, 2)*B.getX() + 3*pow(u,2)*(1 - u)*C.getX() + pow(u,3)*D.getX());
        tmp.setY(pow(1 - u, 3)*A.getY() + 3*u*pow(1 - u, 2)*B.getY() + 3*pow(u,2)*(1 - u)*C.getY() + pow(u,3)*D.getY());
		for (int i = 0; i < n; i++)
		{
			if (!(flag[i] % 2) && aS[i][arr[i]]->pointInShape(tmp))
			{
				flag[i]++;
				temp++;
			}
		}
		if (temp == n) break;
    }
}
