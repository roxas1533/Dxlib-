#pragma once
class Rect
{
public:
	float x;
	float y;
	int width;
	int height;
	float veloX;
	float veloY;
	int color;
	Rect(int x, int y, int w, int h,int c) :y(y), width(w), height(h),color(c) {
		this->x = x - w / 2;
		this->veloX = 0;
		this->veloY = 0;
	}
	virtual void update() {
		x += veloX;
		y += veloY;
	}
};
