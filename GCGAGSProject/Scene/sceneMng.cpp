#include <vector>
#include <tuple>
#include <string>
#include <map>
#include <DxLib.h>
#include "SoundMng.h"
#include "PadMng.h"
#include "sceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "ImageMng.h"
#include "UIMng.h"
#include "MapMng.h"
#include "MoneyMng.h"
#include "ReadMng.h"
#include "MouseMng.h"
#include "RightHandSearch.h"
#include "CronoMng.h"
#include "KeyMng.h"
#include "StartScene.h"
#include "FPSKeeper.h"
#include "StatusCtr.h"


SceneMng* SceneMng::sInstance = nullptr;


SceneMng::SceneMng() :ScreenSize{ 1280,720 }
{
	shutdownF_ = false;
	SetAlwaysRunFlag(true);
	SetWindowText("DungeonOwner");

	SetLightEnable(FALSE);

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);
	SetDrawScreen(DX_SCREEN_BACK);
	SetCreate3DSoundFlag(true);
	SetFontSize(60);
	//SetBackgroundColor(100, 100, 100);
	SetUseZBufferFlag(TRUE);
	SetCameraNearFar(0.1f, 1000.0f);
	SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
	SetLightAmbColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));

	SetDXArchiveKeyString("DoAkathukiSoftWere");

	SetFogEnable(TRUE);
	SetFogStartEnd(1500.0f, 40000.0f);

	SetFontSize(25);

	lpImglMng.Create();
	lpUIMng.Create();
	lpMapMng.Create();
	lpReadMng.Create();
	lpRHSMng.Create();
	lpMouseMng.Create();
	lpPadMng.Create();
	lpCronoMng.Create();
	lpKeyMng.Create();
	lpSoundMng.Create();
}

SceneMng::~SceneMng()
{
	lpImglMng.Destroy();
	lpUIMng.Destroy();
	lpMapMng.Destroy();
	lpReadMng.Destroy();
	lpRHSMng.Destroy();
	lpMouseMng.Destroy();
	lpPadMng.Destroy();
	lpKeyMng.Destroy();
	lpCronoMng.Destroy();
	lpSoundMng.Destroy();
}

void SceneMng::Draw(void)
{
	activeScene_->Draw();
	SetDrawScreen(DX_SCREEN_BACK);
	DxLib::ClsDrawScreen();
	lpUIMng.FastDraw();
	lpUIMng.Draw();
	lpImglMng.DrawNaw();
	DxLib::ScreenFlip();

}

void SceneMng::Run(void)
{
	if (!SysInit())
	{
		return;
	}
	lpImglMng.ReSetD();

	lpImglMng.LoadGraph("ring1.png");
	lpImglMng.LoadGraph("ring2.png");
	lpImglMng.LoadGraph("mouse.png");
	lpImglMng.LoadGraph("CheckMouse1.png");
	lpImglMng.LoadGraph("CheckMouse2.png");
	lpImglMng.LoadGraph("CheckMouse3.png");
	lpImglMng.LoadGraph("arrow.png");

	LPCSTR fontpath = "font/YuseiMagic-Regular.ttf";
	if (AddFontResourceEx(fontpath, FR_PRIVATE, NULL) <= 0)
	{
		MessageBox(NULL, "フォント読み込みに失敗", "フォント処理1", MB_OK);
		return;
	}
	ChangeFont("Yusei Magic", DX_CHARSET_DEFAULT);
	//activeScene_ = std::make_unique<TitleScene>();
	activeScene_ = std::make_unique<StartScene>();

	lpSoundMng.LoadSound("botan.mp3");
	lpSoundMng.LoadSound("pusbotan.mp3");
	lpSoundMng.LoadSound("kaku.mp3");
	lpSoundMng.LoadSound("koto.mp3");
	lpImglMng.SetBright(lpReadMng.GetDate(setinglist::Bright));
	lpSoundMng.SetSoundVol(lpReadMng.GetDate(setinglist::SoundVol));

	StatusCtr::DelDate();
	FPSKeeper *fps = new FPSKeeper();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && shutdownF_ == false)
	{
		fps->Update();
		lpCronoMng.Start();
		lpMouseMng.Update();
		lpPadMng.Update();
		lpImglMng.ReSetD();
		lpUIMng.Update();
		lpKeyMng.Update();
		activeScene_ = (*activeScene_).Update(std::move(activeScene_));
		lpCronoMng.Last();

		Draw();
		fps->Wait();
	}

	if (RemoveFontResourceEx(fontpath, FR_PRIVATE, NULL))
	{
		//フォント破棄成功
	}
	else 
	{
		MessageBox(NULL, "フォント破棄に失敗", "フォント処理2", MB_OK);
	}

	fontpath = NULL;
	delete fps;
	activeScene_ = nullptr;
	lpImglMng.DeleteGraph("ring1.png");
	lpImglMng.DeleteGraph("ring2.png");
	lpImglMng.DeleteGraph("mouse.png");
	lpImglMng.DeleteGraph("CheckMouse1.png");
	lpImglMng.DeleteGraph("CheckMouse2.png");
	lpImglMng.DeleteGraph("CheckMouse3.png");
}

bool SceneMng::SysInit(void)
{
	ChangeWindowMode(true);										//フルスクリーン
	if (DxLib_Init() == -1)										//DXﾗｲﾌﾞﾗﾘの初期化処理
	{
		return false;
	}

	SetUseDirect3DVersion(DX_DIRECT3D_11);
	SetMouseDispFlag(false);
	SetTransColor(0, 255, 0);
	SetUseMaskScreenFlag(true);
	return true;
}

