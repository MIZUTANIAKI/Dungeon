#pragma once
#include<memory>

enum class SCN_ID
{
	SCN_BASE,
	SCN_TITLE,
	SCN_GAME,
	SCN_LOGIN,
	SCN_MAX,
};

class BaseScene;
using UNBS = std::unique_ptr<BaseScene>;
class BaseScene
{
public:
	BaseScene();
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="own">今流れているシーン</param>
	/// <returns></returns>
	virtual UNBS Update(UNBS own) = 0;
	virtual ~BaseScene(); 

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name=""></param>
	virtual void Draw(void) = 0;

	/// <summary>
	/// シーン種別取得
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	virtual SCN_ID GetSCNID(void);
protected:
	SCN_ID scnID_;
};
