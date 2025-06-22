#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
namespace ly
{
	World::World(Application* owningApp)
		:mOwningApp{owningApp},
		mBeganPlay{false},
		mActors{},
		mPendingActors{}
	{

	}
	void World::BeginPlayInternal()
	{
		if (!mBeganPlay)
		{
			mBeganPlay = true;
			BeginPlay();
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
	}

	void World::BeginPlay()
	{
		//LOG("Began play"); 
	}
	void World::Tick(float deltaTime)
	{
		//LOG("Tick at frame rate %f", 1.f/deltaTime);
	}


}
