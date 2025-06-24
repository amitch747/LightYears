#include "player/Reward.h"
#include "player/PlayerSpaceship.h"
#include "framework/World.h"
namespace ly
{
	Reward::Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, float speed)
		:Actor{ world, texturePath },
		mRewardFunc{ rewardFunc },
		mSpeed{speed}
	{
	}
	void Reward::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}
	void Reward::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset({ 0.f, mSpeed * deltaTime });
	}
	void Reward::OnActorBeginOverlap(Actor* otherActor)
	{
		//TODO: clean up casting
		PlayerSpaceship* playerSpaceShip = dynamic_cast<PlayerSpaceship*>(otherActor);
		if (playerSpaceShip != nullptr && !playerSpaceShip->IsPendingDestroy())
		{
			mRewardFunc(playerSpaceShip);
			Destroy();
		}
	}
	weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc)
	{
		weak<Reward> reward = world->SpawnActor<Reward>(texturePath, rewardFunc);
		return reward;
	}
	weak<Reward> CreateHealthReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/pill_green.png", RewardHealth);
	}
	void RewardHealth(PlayerSpaceship* player)
	{
		static float rewardAmt = 10.f;
		if (player && !player->IsPendingDestroy())
		{
			player->GetHealthComp().ChangeHealth(10.f);
		}
	}
}

