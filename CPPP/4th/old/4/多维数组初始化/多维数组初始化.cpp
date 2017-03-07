#include <iostream>
using namespace std;
class Point {
	int x, y;
public:
	void set(int a, int b) {x = a, y = b}
	void print() const { cout "("<<x<<", "<<y<<")\n"; }
	friend Point operator+(const Point& a, const Point& b);
	friend Point add(const Point& a, const Point& b);
};
Point operator+(const Point& a, const Point& b) {
	Point s;
	s.set(a.x + b.x, a.y + b.y);
	return s;
}
Point add(const Point& a,const Point&b) {
	Point s;
	s.set(a.x + b.x, a.y + b.y);
	return s;
}
int main()
{
	Point a, b;
	a.set(3, 2);
	b.set(1, 5);
	(a + b).print();
	operator+(a, b).print();
	add(a, b).print();
}



	















