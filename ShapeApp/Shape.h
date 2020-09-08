#include "Point.h"
#include "stdafx.h"


class CShape
{
public:
	virtual void draw(HDC hdc) const = NULL {};
	virtual void move(double dx, double dy) = NULL {};
	virtual void scale(double s) = NULL {};
	virtual bool pointInShape(Point F) = NULL {};
};	

double areaTria(Point A, Point B, Point C);
void fill(CShape* pS, HDC hdc, int flag);