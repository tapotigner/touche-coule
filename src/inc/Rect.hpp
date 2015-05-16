#ifndef __RECT_HPP__
#define __RECT_HPP__

class Rect {
public:
	int x;
	int y;
	int w;
	int h;

	Rect(int a, int b, int c, int d) : x(a), y(b), w(c), h(d) {}
	~Rect() {}
	
};

#endif