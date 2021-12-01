#pragma once
#pragma comment(lib, "winmm.lib")
#include "BaseScene.h"
#include "Vector2.h"

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	
	static SceneMng& GetInstance(void)
	{
		
		Create();
		return *sInstance;
	}
	
	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	void Run(void);									

	void SetShutdown(void)
	{
		shutdownF_ = true;
	}
private:
	static SceneMng* sInstance;
	const Vector2 ScreenSize;		//��ʃT�C�Y

	bool SysInit();					//����������
	UNBS activeScene_;				//�������Ă�scene������B
	bool shutdownF_;

	void Draw(void);
	SceneMng();
	~SceneMng(); 

};

