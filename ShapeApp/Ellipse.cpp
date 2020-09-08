#include "stdafx.h"
#include "Point.h"
#include "Shape.h"
#include "Ellipse.h"

bool CEllipse::pointInShape(Point F) 
{
	double d = (pow(F.getX() - T.getX(), 2) / pow(rx, 2)) + (pow(F.getY() - T.getY(), 2) / pow(ry, 2) - 1);
	return d <= 0;
}

bool CCircle::pointInShape(Point F)
{
	return T.calcULateDistance(F) <= r;
}

bool CSemiCircle::pointInShape(Point F)
{
	if (F.getY() <= ptCenter.getY())
		return ptCenter.calcULateDistance(F) <= r;
	else
		return FALSE;
}