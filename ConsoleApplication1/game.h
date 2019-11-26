#pragma once
#include<math.h>
#define PI 3.141592653589793
class Vector2 {
public:
	double x;
	double y;
	Vector2(double x, double y) :x(x), y(y) {}
};

double toRad(double degree) {
	return degree * PI / 180.0;
}

double toDegree(double radian) {
	return radian * 180.0 / PI;
}

//Size,Angle
Vector2 PtoC(double s, double angle) {
	Vector2 v(s * cos(toRad(angle)), s * sin(toRad(angle)));
	return v;
}