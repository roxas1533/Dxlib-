#pragma once
#include<math.h>
#define PI 3.141592653589793
enum DRAWTYPE
{
	BOX = 0,
	CIRCLE = 1,
};

class Vector2 {
public:
	double x;
	double y;
	Vector2(double x, double y) :x(x), y(y) {}
};
Vector2 operator -(const Vector2& x, const Vector2& y) {
	return Vector2(x.x - y.x, x.y - y.y);
}

float Cross(Vector2 a, Vector2 b) {
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

class Effect :public Rect {
public:
	bool isDead;
	DRAWTYPE type;
	int alpha;
	Effect(int x, int y, int w, int h, int color, DRAWTYPE t) :Rect(x, y, w, h, color), type(t) {
		isDead = false;
		alpha = 255;
	}

	void draw() {
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		if (type == CIRCLE)DrawCircle(x, y, width, color, true);
		else DrawBox(x, y, height, width, color, true);

		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	void update() {
	}
};

class Trace :public Effect {
public:
	Trace(const Rect const r, DRAWTYPE t) :Effect(r.x, r.y, r.width, r.height, r.color, t) {
		isDead = false;
		alpha = 255;
	}
	void draw() {
		Effect::update();
	}
	void update() {
		//alpha -= 10;
		width -= 0.3;
		height -= 0.3;
		if (alpha <= 0 || width <= 0)isDead = true;
	}
};