#pragma once
#include "Explorer.h"
class Monster :
	public Explorer
{
public:
	Monster();
	~Monster() override;
	void Update(void)override;
	void Draw()override;
	void Init()override;
private:
	void Damage(Explorer& target)override;
};
