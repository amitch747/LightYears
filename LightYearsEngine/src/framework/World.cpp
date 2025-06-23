#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "gameplay/GameStage.h"

namespace ly
{
	World::World(Application* owningApp)
		:mOwningApp{owningApp},
		mBeganPlay{false},
		mActors{},
		mPendingActors{},
		mCurrentStageIndex{ -1 },
		mGameStages{}
	{

	}
	void World::BeginPlayInternal()
	{
		if (!mBeganPlay)
		{
			mBeganPlay = true;
			BeginPlay();
			InitGameStages();
			NextGameStage();
		}
	}
	void World::TickInternal(float deltaTime)
	{
		for (shared<Actor> actor : mPendingActors)
		{
			mActors.push_back(actor);
			actor->BeginPlayInternal();
		}
		mPendingActors.clear();
		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
				iter->get()->TickInternal(deltaTime);
				++iter;
		}
		if (mCurrentStageIndex >= 0 && mCurrentStageIndex < mGameStages.size())
		{
			mGameStages[mCurrentStageIndex]->TickStage(deltaTime);
		}

		Tick(deltaTime);
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto actor : mActors)
		{
			actor->Render(window);
		}
	}

	World::~World()
	{

	}
	
	sf::Vector2u World::GetWindowSize() const
	{
		return mOwningApp->GetWindowSize();
	}

	void World::CleanCycle()
	{
		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			if (iter->get()->IsPendingDestroy())
			{
				// erase() returns next iterator, no need to increment in for loop
				iter = mActors.erase(iter);
			}
			else
			{
				++iter;
			}
		}

		for (auto iter = mGameStages.begin(); iter != mGameStages.end();)
		{
			if (iter->get()->IsStageFinished())
			{
				iter = mGameStages.erase(iter);
			}
			else
			{
				++iter;
			}
		}


	}

	void World::AddStage(const shared<GameStage>& newStage)
	{
		mGameStages.push_back(newStage);
	}

	void World::BeginPlay()
	{
		//LOG("Began play"); 
	}
	void World::Tick(float deltaTime)
	{
		//LOG("Tick at frame rate %f", 1.f/deltaTime);
	}

	void World::InitGameStages()
	{

	}

	void World::AllGameStageFinished()
	{
	}

	void World::NextGameStage()
	{
		++mCurrentStageIndex;
		if (mCurrentStageIndex >= 0 && mCurrentStageIndex < mGameStages.size())
		{
			mGameStages[mCurrentStageIndex]->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
			mGameStages[mCurrentStageIndex]->StartStage();
		}
		else
		{
			AllGameStageFinished();
		}

	}


}
