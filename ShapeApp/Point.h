#pragma once

class Point
{
	double x, y;
public:
	Point(double xx = 0, double yy = 0) : x(xx), y(yy) { }
	double getX() const { return x; }
	double getY() const { return y; }
	void set(double xx, double yy) { x = xx; y = yy; }
	void setX(double xx) { x = xx; }
	void setY(double yy) { y = yy; }
	void draw(HDC hdc);
	void move(double dx, double dy) { x += dx; y += dy; }
	double calcULateDistance(Point b) const;
};

