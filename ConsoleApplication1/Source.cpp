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
		DrawCircle(x, y,width, 0x6666FF, true);
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
std::vector<Bullet> bullets;
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
			Bullet b(x+i*25+5, y, 5, 5, 0xFFFF00);
			b.setVelocity(10, 270);
			bullets.push_back(b);
		}
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);//��S��ʂɃZ�b�g
	SetGraphMode(WIDTH, HEIGHT, 32);//��ʃT�C�Y�w��
	SetOutApplicationLogValidFlag(FALSE);//Log.txt�𐶐����Ȃ��悤�ɐݒ�
	if (DxLib_Init() == 1) { return -1; }//�������Ɏ��s���ɃG���[��f�����ďI��

	Player player(320, 450, 30, 30, 0xFFFFFF);

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//����ʏ���
		SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�
		time++;
		std::vector<Bullet>::iterator it =bullets.begin();
		while (it != bullets.end()) {
			it->update();
			it->draw();
			if (it->isDead) {
				it = bullets.erase(it);
			}
			else ++it;
		}
		player.update();
		player.draw();
		ScreenFlip();//����ʂ�\��ʂɃR�s�[
	}

	DxLib_End();
	return 0;
}