#include "enemy/Vanguard.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	Vanguard::Vanguard(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		:EnemySpaceship{ owningWorld, texturePath },
		mShooter{ new BulletShooter{this, 1.f, {-45.f, 0.f}, 180.f } }
	{
		SetVelocity(velocity);
	}
	void Vanguard::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}
	void Vanguard::Shoot()
	{
		mShooter->Shoot();
	}
}