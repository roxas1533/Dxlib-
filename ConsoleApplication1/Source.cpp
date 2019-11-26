#include <DxLib.h>
#include <stdio.h>
#include<vector>
#include "Rect.h"
#include "game.h"
#define WIDTH 640
#define HEIGHT 480

class Bullet :public Rect {
public:
	bool isDead;
	Bullet(int x, int y, int w, int h, int c) :Rect(x, y, w, h, c) {
		isDead = false;
	}
	void draw() {
		DrawCircle(x, y, width, 0x6666FF, true);
	}
	void update() {
		Rect::update();
		if (x<0 || x + width>WIDTH || y<0 || y + height>HEIGHT)isDead = true;
	}
	void setVelocity(float r, float angle) {
		veloX = PtoC(r, angle).x;
		veloY = PtoC(r, angle).y;
	}
};
class Enemy :public Rect {
public:
	bool isDead;
	Enemy(int x, int y, int w, int h) :Rect(x, y, w, h, 0xFF4444) {
		veloY = GetRand(70) / 10.0 + 1.0;
		isDead = false;
	}
	void draw() {
		DrawBox(x, y, x+width, y+height, color, true);
	}
	void update() {
		Rect::update();
		if (y > HEIGHT)isDead = true;
	}
};
std::vector<Bullet> bullets;
std::vector<Enemy> enemys;
int time = 0;
class Player :public Rect {
	using Rect::Rect;
	const float playerSpeed = 5;
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
	}

	void shot() {
		for (int i = 0; i < 2; i++) {
			Bullet b(x + i * 25 + 5, y, 5, 5, 0xFFFF00);
			b.setVelocity(10, 270);
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
		if (time % 30 == 0) {
			enemys.push_back(Enemy(GetRand(WIDTH), -20, 20, 20));
		}
		std::vector<Bullet>::iterator it = bullets.begin();
		while (it != bullets.end()) {
			it->update();
			it->draw();
			if (it->isDead) {
				it = bullets.erase(it);
			}
			else ++it;
		}
		std::vector<Enemy>::iterator ene = enemys.begin();
		while (ene != enemys.end()) {
			ene->update();
			ene->draw();
			if (ene->isDead) {
				ene = enemys.erase(ene);
			}
			else ++ene;
		}
		player.update();
		player.draw();
		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();
	return 0;
}