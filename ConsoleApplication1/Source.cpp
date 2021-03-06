#include <DxLib.h>
#include <stdio.h>
#include<vector>
#include<list>
#include "Rect.h"
#include "game.h"
#define WIDTH 640
#define HEIGHT 480
#include<memory>
std::list< std::shared_ptr<Effect>> effects;
class Bullet :public Rect {
public:
	int attack;
	bool isDead;
	Bullet(int x, int y, int w, int h, int c) :Rect(x, y, w, h, c) {
		isDead = false;
		attack = 1;
	}
	virtual void draw() {
		DrawCircle(x, y, width, 0x6666FF, true);
	}
	void update() {
		Rect::update();
		if (x<0 || x + width>WIDTH || y<0 || y + height>HEIGHT)isDead = true;
	}
	virtual void setVelocity(float r, float angle) {
		veloX = PtoC(r, angle).x;
		veloY = PtoC(r, angle).y;
	}
};
class Bullet2;
std::vector< std::shared_ptr<Bullet>> bullets;
class Enemy :public Rect {
public:
	int hp;
	bool isDead;
	Enemy(int x, int y, int w, int h) :Rect(x, y, w, h, 0xFF4444) {
		veloY = GetRand(7) + 1.0;
		isDead = false;
		hp = 10;
	}
	void draw() {
		DrawBox(x, y, x + width, y + height, color, true);
	}
	void update() {
		Rect::update();
		if (y > HEIGHT || hp <= 0)isDead = true;
	}
};
std::vector< std::shared_ptr<Enemy>> enemys;
class Bullet2 :public Bullet {
public:
	float angle;
	float r;
	long long id = -1;
	float lastX;
	float lastY;
	const Rect* target;
	Bullet2(int x, int y, int w, int h, int c) :Bullet(x, y, w, h, c), lastX(x), lastY(y) {
		angle = 0;
		this->r = 0;
		target = nullptr;
		attack = 10;
		color = 0x6666FF;
	}
	void draw() {
		DrawCircle(x, y, width, color, true);
	}

	void update() override {
		if (target == nullptr) {
			int size = enemys.size() - 1;
			for (auto&& x : enemys) {
				target = &(*enemys[GetRand(size)]);
			}
			id = (target != nullptr) ? target->id : -1;
		}
		else if (target->id != id) {
			int size = enemys.size() - 1;
			for (auto&& x : enemys) {
				target = &(*enemys[GetRand(size)]);
			}
			id = target->id;
		}
		Vector2 t(500, 500);
		int ang = 10;
		if (target != nullptr) {
			t = Vector2(double(target->x) + target->width / 2, double(target->y) + target->height / 2);
			ang = 10;
		}
		Vector2 vec = Vector2(x, y) - t;
		Vector2 vec2 = Vector2(x, y) - Vector2(x + PtoC(50, angle).x, y + PtoC(50, angle).y);

		if (Cross(vec, vec2) < 0)
			angle += ang;
		else if (Cross(vec, vec2) > 0)
			angle -= ang;
		setVelocity(r, angle);
		Bullet::update();
		for (int i = 0; i <= 4; i++) {
			setXY(4, i);
		}

		lastX = x;
		lastY = y;
	}
	void setXY(int n, int m) {
		Rect r((x * n + lastX * m) / (n + m) + width / 2, (y * n + lastY * m) / (n + m), width, height, color);
		std::shared_ptr<Trace> b(new Trace(r, CIRCLE));
		effects.push_back(b);
	}
	void setVelocity(float r, float angle) {
		Bullet::setVelocity(r, angle);
		this->angle = angle;
		this->r = r;
	}
};

int time = 0;
int count = 0;
int score=0;
class Player :public Rect {
	const float playerSpeed = 5;
	using Rect::Rect;
	int hormingTime;
public:
	void update() {
		Rect::update();
		key();
		if (x < 0) {
			x = 0; veloX = 0;
		}
		if (x + width > WIDTH) {
			x = WIDTH - width; veloX = 0;
		}
		if (y < 0) {
			y = 0; veloY = 0;
		}
		if (y + height > HEIGHT) {
			y = HEIGHT - height; veloY = 0;
		}
		if (hormingTime > 0) {
			hormingTime--;
			if(time%25==0)
			shot2();
		}
	}
	void draw() {
		DrawBox(x, y, x + width, y + height, color, true);
	}
	void key() {
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			veloX = -playerSpeed;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			veloX = playerSpeed;
		}
		if (!CheckHitKey(KEY_INPUT_RIGHT) && !CheckHitKey(KEY_INPUT_LEFT)) {
			veloX = 0;
		}
		if (CheckHitKey(KEY_INPUT_UP)) {
			veloY = -playerSpeed;
		}
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			veloY = playerSpeed;
		}
		if (!CheckHitKey(KEY_INPUT_UP) && !CheckHitKey(KEY_INPUT_DOWN)) {
			veloY = 0;
		}
		if (CheckHitKey(KEY_INPUT_Z) && time % 6 == 0) {
			shot();
		}
		if (CheckHitKey(KEY_INPUT_X) &&count==10) {
			hormingTime = 50;
			count = 0;
		}
	}

	void shot() {
		for (int i = 0; i < 2; i++) {
			std::shared_ptr<Bullet> b(new Bullet(x + i * 25 + 5, y, 5, 5, 0xFFFF00));
			b->setVelocity(10, 270);
			bullets.push_back(b);
		}
	}
	void shot2() {
		for (int i = 0; i < 10; i++) {
			std::shared_ptr<Bullet2> b(new Bullet2(x + width / 2, y, 5, 5, 0xFFFF00));
			b->setVelocity(10, GetRand(90) + 45);
			bullets.push_back(b);
		}
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(WIDTH, HEIGHT, 32);//画面サイズ指定
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
	if (DxLib_Init() == 1) { return -1; }//初期化に失敗時にエラーを吐かせて終了

	Player player(320, 450, 30, 30, 0xFFFFFF);

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//裏画面消す
		SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に
		time++;
		if (time % 10 == 0) {
			std::shared_ptr <Enemy> b(new Enemy(GetRand(WIDTH), -20, 20, 20));
			enemys.push_back(b);
		}
		std::vector<std::shared_ptr<Bullet>>::iterator it = bullets.begin();
		while (it != bullets.end()) {
			(*it)->update();
			(*it)->draw();
			for (auto&& x : enemys) {
				if (collison((*x), **it)) {
					(*it)->isDead = true;
					(*(&x))->hp -= (*it)->attack;
				}
			}
			if ((*it)->isDead) {
				it = bullets.erase(it);
			}
			else ++it;
		}
		std::vector< std::shared_ptr<Enemy>>::iterator ene = enemys.begin();
		while (ene != enemys.end()) {
			(*ene)->update();
			(*ene)->draw();
			if ((*ene)->hp <= 0) {
				score += (int)(10 * ((*ene)->veloY / 4.0));
				count < 10 ? count++ : count += 0;
			}
			if ((*ene)->isDead) {
				ene = enemys.erase(ene);
			}
			else ++ene;
		}
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		std::list< std::shared_ptr<Effect>>::iterator itr = effects.begin();
		while (itr != effects.end()) {
			(*itr)->update();
			(*itr)->draw();
			if ((*itr)->isDead) {
				itr = effects.erase(itr);
			}
			else ++itr;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawBox(WIDTH - 50, 50, WIDTH - 50 + 30, 50 + 350 - 5, 0, true);
		for (int i = 0; i < count; i++)DrawBox(WIDTH - 50, 50 + 35 * (9 - i), WIDTH - 50 + 30, 50 + 35 * (9 - i) + 30, count == 10 ? 0xFFFF00 : 0xFF0000, true);
		DrawBox(WIDTH - 50, 50, WIDTH - 50 + 30, 50 + 350 - 5, 0xFFFFFF, false);
		player.update();
		player.draw();
		DrawFormatString(0, 0, 0xFFFFFF, "SCORE:%05d", score);
		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();
	return 0;
}