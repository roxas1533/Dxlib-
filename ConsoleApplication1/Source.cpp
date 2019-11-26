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
	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(640, 480, 32);//画面サイズ指定
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
	if (DxLib_Init() == 1) { return -1; }//初期化に失敗時にエラーを吐かせて終了

	Player player(320, 450, 30, 30, 0xFFFFFF);

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//裏画面消す
		SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に
		player.update();
		player.draw();
		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();
	return 0;
}