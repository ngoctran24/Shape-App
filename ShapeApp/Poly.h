class CPLine
{    
public:
	virtual void draw(HDC hdc) = NULL {};
	virtual void pointOnLine(CShape* aS[][7], int* flag, int* arr, int n) = NULL {};
};

class StraightLine : public CPLine
{
private:
    Point A, B;
public:
	StraightLine(Point AA, Point BB) : A(AA), B(BB) {}
    void draw(HDC hdc);
    void pointOnLine(CShape* aS[][7], int* flag, int* arr, int n);
};

class Curve : public CPLine
{
private:
    Point A, B, C, D;
public:
	Curve(Point* X[]) : A(*X[1]), B(*X[2]), C(*X[3]), D(*X[4]) {}
    void draw(HDC hdc);
    void pointOnLine(CShape* aS[][7], int* flag, int* arr, int n);
};
