#pragma once
#include <vector>
#include <string>
#include "WFUtility.h"
#include "MapMng.h"
#include "CronoMng.h"
#include "SoundMng.h"
#include "EnemyMove.h"

enum class MoveDir
{
	None,
	Up,
	Right,
	Down,
	Left,
};

enum class ObjectID
{
	none,
	Adventurer,
	Knight,
	Pawn,
	Monster,
	Spike,
	Gate,
	Desmodus,
	Rook,
	Fire,
	EFire,
	Goal,
};

class Explorer
{
public:
	Explorer();
	virtual ~Explorer();
	virtual void Update(void);
	virtual void Draw();
	virtual void Init();

	virtual void SetMoveVec(std::vector<Vector2> vec) {};

	virtual void HitCheck(Explorer& target);
	//void HitCheck(Vector2 pos, ObjectID id,float atk);

	virtual void ReSetPos(Vector2 pos)
	{
		nowMoveVec_ = 0;
		pos_ = WFUtility::VecIntToVecFlt(pos);
		pos_.x = pos_.x * 32;
		pos_.y = pos_.y * 32;
		defpos_ = pos;
	}

	void DefPos(void)
	{
		pos_ = WFUtility::VecIntToVecFlt(defpos_);
		nowMoveVec_ = 0;
		hp_ = 1;
		MoveF_ = true;
		pos_.x = pos_.x * 32 + mapPos_.x;
		pos_.y = pos_.y * 32 + mapPos_.y;
	}

	void SetHp(float num)
	{
		hp_ = num;
	}

	static void SetMapMos(Vector2 pos)
	{
		mapPos_ = pos;
	}

	void SetDir(MoveDir dir)
	{
		dir_ = dir;
	}

	MoveDir GetDir(void) const noexcept
	{
		return dir_;
	}

	Vector2 GetPos(void) const noexcept
	{
		return WFUtility::VecFltToVecInt(pos_);
	}

	ObjectID GetObjectID(void) const noexcept
	{
		return id_;
	}

	float GetHP(void) const noexcept
	{
		return hp_;
	}

	float GetDefHp_(void) const noexcept
	{
		return defhp_;
	}

	void AddHP(int num)
	{
		hp_ += num;
	}

	void SetAtk(int atk)
	{
		atk_ = static_cast<float>(atk);
	}

	float GetAtk(void) const noexcept
	{
		return atk_;
	}

	void SetSleep(void) noexcept
	{
		MoveF_ = false;
		MoveFCon_ = 0.0f;
	}
	bool IsSleep(void) const noexcept
	{
		return !MoveF_;
	}

	Vector2 GetDefPos(void) const noexcept
	{
		return defpos_;
	}

	void HitAttack(float atk);

	virtual void SetStatus(int num)=0;
	void BuildEnemyMoveDate(mapChipDate date, Vector2 size,Vector2 pos);
protected:
	virtual void Damage(Explorer& target) = 0;

	void ChangeNone();
	void DefoltMove(float deltaTime);

	void MoveMagic(Vector2& mdir, float deltaTime);

	void MoveNext(Vector2& tpos);

	bool DoMove();
	bool DrawCheck(Vector2& pos)const;

	Vector2flt pos_;
	Vector2 defpos_;
	static Vector2 mapPos_;

	int nowMoveVec_;
	float hp_;
	float defhp_;
	float atk_;
	MoveDir dir_;

	bool MoveF_;
	float MoveFCon_;
	float MoveFMAX_;

	ObjectID id_;

	bool oneTimeRetreatF_;

	std::unique_ptr<EnemyMove> enemymove_;
	void SetMoveing(std::vector<Vector2>& vec);
};
