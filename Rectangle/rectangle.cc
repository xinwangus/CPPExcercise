// Given two rectangles, calculate the overlap area size.
#include <iostream>

using namespace std;

#define MAX(a, b) ((a > b)? a : b)
#define MIN(a, b) ((a > b)? b : a)

class Range {
public:
	Range(int si, int li);
	virtual ~Range();

	bool overlap(const Range& in, Range&out);

	int s;
	int l;
};

Range::Range(int si, int li)
{
	s = MIN(si, li);
	l = MAX(si, li);
}

Range::~Range()
{
}

bool 
Range::overlap(const Range& in, Range&out)
{
	bool ret = false;
	if ((l <= in.s) || (s >= in.l)) {
		return ret;
	}
	ret = true;
	out.s = MAX(s, in.s);
	out.l = MIN(l, in.l);
	assert(out.s <= out.l);
	return ret;
}

class Rectangle {
public:
	Rectangle (Range& xi, Range& yi);
	virtual ~Rectangle();
	int area();
	Range x;
	Range y;
};

Rectangle::Rectangle(Range& xi, Range& yi)
: x(xi.s, xi.l), y(yi.s, yi.l)
{
}

Rectangle::~Rectangle()
{
}

int Rectangle::area()
{
	return (x.l - x.s)*(y.l - y.s);
}

int main ()
{
	Range x1(1,5);
	Range y1(2,6);
	Range x2(3,7);
	Range y2(1,5);

	Rectangle* r1 = new Rectangle(x1, y1);
	Rectangle* r2 = new Rectangle(x2, y2);
	
	Range xo(0,0);
	Range yo(0,0);

	bool overlap = r1->x.overlap(r2->x, xo);
	if (overlap) {
		overlap = r1->y.overlap(r2->y, yo);
		if (overlap) {
			Rectangle* ol = new Rectangle(xo, yo);
			cout << "overlap area X range is: (" << xo.s << " , " << xo.l << ")" << endl;
			cout << "overlap area Y range is: (" << yo.s << " , " << yo.l << ")" << endl;
			cout << "overlap area is: " << ol->area() << endl;
			return 0;
		}
	}
	cout << "not overlapping!" << endl;
	return 0;
}
