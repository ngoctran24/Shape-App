#include "stdafx.h"
#include "Point.h"
#include "Shape.h"
#include "Rect.h"

void CRect::scale(double s)
{
	UL.move(width*(1-s)/2, height*(1-s)/2);
	width *= s;
	height *= s;
}
bool CRect::pointInShape(Point F)
{
	return ((F.getX() >= UL.getX() && F.getX() <= UL.getX() + width) && (F.getY() >= UL.getY() - height && F.getY() <= UL.getY()));
}

void CSquare::scale(double s)
{
	UL.move(edge * (1 - s) / 2, edge * (1 - s) / 2);
	edge *= s;
}
bool CSquare::pointInShape(Point F)
{
	return ((F.getX() >= UL.getX() && F.getX() <= UL.getX() + edge) && (F.getY() >= UL.getY() - edge && F.getY() <= UL.getY()));
}

void CTriangle::draw(HDC hdc) const
{
	POINT vertices[3] = { {A.getX(), A.getY()}, { B.getX(), B.getY() }, { C.getX(), C.getY() } };
	Polygon(hdc, vertices, 3);
}
void CTriangle::move(double dx, double dy)
{
	A.move(dx, dy);
	B.move(dx, dy);
	C.move(dx, dy);
}
void CTriangle::scale(double s) {
	double mx = (A.getX() + B.getX() + C.getX()) / 3;
	double my = (A.getY() + B.getY() + C.getY()) / 3;
	A.set(mx + (A.getX() - mx) * s, my + (A.getY() - my) * s);
	B.set(mx + (B.getX() - mx) * s, my + (B.getY() - my) * s);
	C.set(mx + (C.getX() - mx) * s, my + (C.getY() - my) * s);
}
bool CTriangle::pointInShape(Point F)
{
	/* CalcULate area of triangle ABC */
	double area = areaTria(A, B, C);
	/* CalcULate area of triangle FAB */
	double area1 = areaTria(F, A, B);
	/* CalcULate area of triangle FAC */
	double area2 = areaTria(F, A, C);
	/* CalcULate area of triangle FBC */
	double area3 = areaTria(F, B, C);
	return abs(area - (area1 + area2 + area3)) <= 0.1;
}
