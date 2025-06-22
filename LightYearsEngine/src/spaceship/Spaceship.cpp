#include "spaceship/spaceship.h"

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor{ owningWorld, texturePath }
	{
	}
	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
	}
	void Spaceship::SetVelocity(const sf::Vector2f& newVel)
	{
		mVelocity = newVel;
	}
	void Spaceship::Shoot()
	{

	}
}