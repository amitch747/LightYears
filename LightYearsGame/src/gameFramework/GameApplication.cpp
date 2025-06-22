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

		weak<Spaceship> testSpaceship = newWorld.lock()->SpawnActor<Spaceship>();
		testSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
		testSpaceship.lock()->SetActorLocation(sf::Vector2f{ 100.f, 50.f });


		counter = 0.f;
	}
	void GameApplication::Tick(float deltaTime)
	{
		counter += deltaTime;
		if (counter > 10.f)
		{
			if (!testPlayerSpaceShip.expired())
			{
				testPlayerSpaceShip.lock()->Destroy();
			}
		}
	}
}