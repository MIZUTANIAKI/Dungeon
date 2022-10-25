#include <DxLib.h>
#include <string>
#include <Windows.h>
#include "Scene/sceneMng.h"
#include "MoneyMng.h"
#include "resource.h"

/* ‚˜64 */

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	system("cd ./Dungeon_owner");
	SetAlwaysRunFlag(true);
	SetWindowIconID(IDI_ICON1);
	SceneMng::Create();
	SceneMng::GetInstance().Run();
 	SceneMng::GetInstance().Destroy();

	DxLib_End();
	return 0;
}