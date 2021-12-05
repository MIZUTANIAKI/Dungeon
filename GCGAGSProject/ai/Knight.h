#pragma once
#include "Explorer.h"
class Knight :
    public Explorer
{
public:
	Knight();
	~Knight() override;
	void Update(void)override;
	void Draw()override;
	void Init()override;

	void SetMoveVec(std::vector<Vector2> vec)override
	{
		moveVec_.clear();
		moveVec_ = vec;
	};
	std::vector<Vector2> GetMoveVec(void) const noexcept
	{
		return moveVec_;
	};

	void SetGoalPos(Vector2 pos)
	{
		goalPos_ = pos;
	}

	void SetHP(int num)
	{
		defhp_ = static_cast<float>(num);
		hp_ = static_cast<float>(num);
	}
	void SetStatus(int num) override;
private:
	void MoveTo(float deltaTime);
	virtual void Damage(Explorer& target);
	std::vector<Vector2> moveVec_;

	Vector2 goalPos_;
};

