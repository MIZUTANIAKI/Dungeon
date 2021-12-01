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
private:
	void Damage(Explorer& target)override;
};
