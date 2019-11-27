#pragma once
#include<math.h>
#define PI 3.141592653589793
class Vector2 {
public:
	double x;
	double y;
	Vector2(double x, double y) :x(x), y(y) {}

};
Vector2 operator -(const Vector2& x, const Vector2& y) {
	return Vector2(x.x - y.x, x.y - y.y);
}

float Cross(Vector2 a,Vector2 b) {
	return (a.x * b.y) - (a.y * b.x);
}

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

//collision
bool collison(Rect p, Rect q) {
	if (p.x <= q.x + q.width && q.x <= p.x + p.width && p.y <= q.y + q.height && q.y <= p.y + p.height)return true;
	return false;
}