#include <DxLib.h>
#include <stdio.h>
#include "Rect.h"

class Player :public Rect {
	using Rect::Rect;
	const float playerSpeed = 5;
public:
	void update() {
		Rect::update();
		key();
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
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);//��S��ʂɃZ�b�g
	SetGraphMode(640, 480, 32);//��ʃT�C�Y�w��
	SetOutApplicationLogValidFlag(FALSE);//Log.txt�𐶐����Ȃ��悤�ɐݒ�
	if (DxLib_Init() == 1) { return -1; }//�������Ɏ��s���ɃG���[��f�����ďI��

	Player player(320, 450, 30, 30, 0xFFFFFF);

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//����ʏ���
		SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�
		player.update();
		player.draw();
		ScreenFlip();//����ʂ�\��ʂɃR�s�[
	}

	DxLib_End();
	return 0;
}