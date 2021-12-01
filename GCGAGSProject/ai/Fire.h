#pragma once
#include "Explorer.h"
class Fire :
    public Explorer
{
public:
	Fire();
	~Fire() override;
	void Update(void)override;
	void Draw()override;
	void Init()override;
	void SetMoveDir(Vector2 dir)
	{
		moveDir_ = dir;
	}
	void SetEneF(void);
private:
	void Damage(Explorer& target)override;
	Vector2 moveDir_;
	float timecount_;
};

