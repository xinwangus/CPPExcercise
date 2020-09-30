// Given two rectangles, calculate the overlap area size.
#include <iostream>

using namespace std;

#define MAX(a, b) (((a) > (b))? (a) : (b))
#define MIN(a, b) (((a) > (b))? (b) : (a))

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
	int ss = MAX(s, in.s);
	int ll = MIN(l, in.l);
	if (ss >= ll) {
		return false;
	}
	out.s = ss;
	out.l = ll;
	return true;
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
	Range xo(0,0);
	Range yo(0,0);

	bool overlap = x1.overlap(x2, xo);
	if (overlap) {
		overlap = y1.overlap(y2, yo);
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
