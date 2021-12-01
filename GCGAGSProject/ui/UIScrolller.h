#pragma once
#include <vector>
#include <map>
#include <memory>
#include <utility>
#include "gameUI/ScrollUIBase.h"
enum class MapDropDateID;
class UIScrolller
{
public:
	UIScrolller();
	~UIScrolller();

	void Update(void);
	void SpawnUI(void);
	void Draw(void);

	void Init(void);

private:

	int scrollX_;
	int screenSizeY_;
	int defPosX_;
	std::vector<std::unique_ptr<ScrollUIBase>> UIVector_;
	std::map<MapDropDateID, std::pair<bool,int>> uiF_;

	int screenH_;
};

