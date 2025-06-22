#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "player/PlayerSpaceship.h"

#include "config.h"


// Implement GetApplication()
ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}

namespace ly
{
	GameApplication::GameApplication()
		: Application{600, 980, "Billions", sf::Style::Titlebar | sf::Style::Close}
	{
		AssetManager::Get().SetAssetRootDirectoy(GetResourceDir());

		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();
		testPlayerSpaceShip = newWorld.lock()->SpawnActor<PlayerSpaceship>();
		testPlayerSpaceShip.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		//testPlayerSpaceShip.lock()->setActorRotation(90.f);

		counter = 0;
	}
	void GameApplication::Tick(float deltaTime)
	{
		//counter += deltaTime;
		//if (counter > 2.f)
		//{
		//	if (!actorToDestroy.expired())
		//	{
		//		// Need to lock again since SpawnActor<Actor>() returns a <weak>
		//		actorToDestroy.lock()->Destroy();
		//	}
		//}
	}
}