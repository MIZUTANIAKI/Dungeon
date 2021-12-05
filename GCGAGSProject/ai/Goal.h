#pragma once
#include "Explorer.h"
#include "Adventurer.h"

class Goal :
	public Explorer
{
public:
	Goal();
	~Goal() override;
	void Update(void)override;
	void Draw()override;
	void Init()override;
	void SetStatus(int num) override;
private:
	void Damage(Explorer& target)override;
	int count_;
};
