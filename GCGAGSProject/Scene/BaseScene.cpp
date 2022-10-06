#include "BaseScene.h"

BaseScene::BaseScene()
{
	scnID_ = SCN_ID::SCN_BASE;
}

BaseScene::~BaseScene()
{
}

SCN_ID BaseScene::GetSCNID(void)
{
	return scnID_;
}
