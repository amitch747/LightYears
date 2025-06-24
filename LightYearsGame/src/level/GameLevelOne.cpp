#include "level/GameLevelOne.h"
#include "enemy/Vanguard.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "player/PlayerSpaceship.h"
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include "enemy/VanguardStage.h"
#include "gameplay/WaitStage.h"
namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		:World{owningApp}
	{
		testPlayerSpaceShip = SpawnActor<PlayerSpaceship>();
		testPlayerSpaceShip.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));

	}
	void GameLevelOne::BeginPlay()
	{
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<VanguardStage>{new VanguardStage{ this }});
		AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddStage(shared<VanguardStage>{new VanguardStage{ this }});

	}	
}