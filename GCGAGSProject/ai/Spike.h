#pragma once
#include "Explorer.h"
class Spike :
	public Explorer
{
public:
	Spike();
	~Spike() override;
	void Update(void)override;
	void Draw()override;
	void Init()override;
	void SetStatus(int num) override;
private:
	void Damage(Explorer& target)override;
};
