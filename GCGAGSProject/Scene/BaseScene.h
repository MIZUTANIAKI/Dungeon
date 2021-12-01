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
	/// �X�V����
	/// </summary>
	/// <param name="own">������Ă���V�[��</param>
	/// <returns></returns>
	virtual UNBS Update(UNBS own) = 0;
	virtual ~BaseScene(); 

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name=""></param>
	virtual void Draw(void) = 0;

	/// <summary>
	/// �V�[����ʎ擾
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	virtual SCN_ID GetSCNID(void);
protected:
	SCN_ID scnID_;
};
