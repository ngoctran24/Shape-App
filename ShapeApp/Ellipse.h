class CEllipse: public CShape
{
	Point T;
	double rx, ry;
public:
	CEllipse(double x, double y, double a, double b) :T(x,y), rx(a), ry(b) {}
	void draw(HDC hdc) const { Ellipse(hdc, T.getX()-rx, T.getY()-ry, T.getX()+rx, T.getY()+ry); }
	void move(double dx, double dy) { T.move(dx, dy); }
	void scale(double s) { rx *= s; ry *= s; }
	bool pointInShape(Point F);
};

class CCircle : public CShape
{
	Point T;
	double r;
public:
	CCircle(double x, double y, double a) :T(x, y), r(a) {}
	void draw(HDC hdc) const { Ellipse(hdc, T.getX() - r, T.getY() - r, T.getX() + r, T.getY() + r); }
	void move(double dx, double dy) { T.move(dx, dy); }
	void scale(double s) { r *= s; }
	bool pointInShape(Point F);
};

class CSemiCircle : public CShape
{
	Point ptCenter;
	double r;
public:
	CSemiCircle(double x, double y, double a) : ptCenter(x, y), r(a) {}
	void draw(HDC hdc) const { Pie(hdc, ptCenter.getX() - r, ptCenter.getY() - r, ptCenter.getX() + r, ptCenter.getY() + r, ptCenter.getX() + r, ptCenter.getY(), ptCenter.getX() - 3 * r, ptCenter.getY()); }
	void move(double dx, double dy) { ptCenter.move(dx, dy); }
	void scale(double s) { r *= s; }
	bool pointInShape(Point F);
};


