#pragma once
#include "weapon/Shooter.h"
#include "SFML/System.hpp"

namespace ly
{
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, float cooldownTime = 1.f, const sf::Vector2f& localPositionOffset = { 0.f, 0.f }, float localRotationOffset = 0.f);
		virtual bool IsOnCooldown() const override;
	private:
		virtual void ShootImpl() override;
		sf::Clock mCooldownClock;
		float mCooldownTime;
		sf::Vector2f mLocalPositionOffset;
		float mLocalRotationOffset;

	};
}