class CRect: public CShape
{
	Point UL;
	double width, height;
public:
	CRect(double x, double y, double w, double h) : UL(x,y), width(w), height(h) {}
	void draw(HDC hdc) const { Rectangle(hdc, UL.getX(), UL.getY(), UL.getX() + width, UL.getY() - height); }
	void move(double dx, double dy) { UL.move(dx, dy); }
	void scale(double s);
	bool pointInShape(Point F);
};

class CSquare : public CShape
{
	Point UL;
	double edge;
public:
	CSquare(double x, double y, double e) : UL(x, y), edge(e) {}
	void draw(HDC hdc) const { Rectangle(hdc, UL.getX(), UL.getY(), UL.getX() + edge, UL.getY() - edge); }
	void move(double dx, double dy) { UL.move(dx, dy); }
	void scale(double s);
	bool pointInShape(Point F);
};

class CTriangle : public CShape
{
	Point A, B, C;
public:
	CTriangle(double x1, double y1, double x2, double y2, double x3, double y3) : A(x1, y1), B(x2, y2), C(x3, y3) {}
	void draw(HDC hdc) const;
	void move(double dx, double dy);
	void scale(double s);
	bool pointInShape(Point F);
};