#include <DxLib.h>
#include <stdio.h>

int x = 0;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	ChangeWindowMode(TRUE);//��S��ʂɃZ�b�g
	SetGraphMode(640, 480, 32);//��ʃT�C�Y�w��
	SetOutApplicationLogValidFlag(FALSE);//Log.txt�𐶐����Ȃ��悤�ɐݒ�
	if (DxLib_Init() == 1) { return -1; }//�������Ɏ��s���ɃG���[��f�����ďI��

	//
	//�����ŉ摜�E����ǂݍ���
	//

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//����ʏ���
		SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�

		DrawBox(x, 0, x+100, 100,0xFFFFFF,true);
		x++;
		ScreenFlip();//����ʂ�\��ʂɃR�s�[
	}

	DxLib_End();
	return 0;
}