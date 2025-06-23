#include "gameplay/GameStage.h"

namespace ly
{
	GameStage::GameStage(World* world)
		: mWorld{world},
		mStageFinished{false}
	{
	}
	void GameStage::StartStage()
	{
		LOG("Stage started");
	}
	void GameStage::TickStage(float deltaTime)
	{
	}
	void GameStage::FinishStage()
	{
		onStageFinished.Broadcast();
		mStageFinished = true;
		StageFinished();
	}
	void GameStage::StageFinished()
	{
		LOG("Stage Finished");
	}
}