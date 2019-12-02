#pragma once
#include <DxLib.h>
class Rect
{
public:
	float x;
	float y;
	float width;
	float height;
	float veloX;
	float veloY;
	int color;
	const long long id = GetRand(100000000);
	Rect(int x, int y, int w, int h,int c) :y(y), width(w), height(h),color(c) {
		this->x = x - w / 2;
		this->veloX = 0;
		this->veloY = 0;
	}
protected:
	virtual void update() {
		x += veloX;
		y += veloY;
	}
};
