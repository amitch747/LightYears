#include "vfx/Explosion.h"
#include "framework/MathUtility.h"
#include "vfx/Particle.h"
#include "framework/World.h"
namespace ly
{
	Explosion::Explosion(int particleAmt, float lifeTimeMin, float lifeTimeMax, float sizeMax, float sizeMin, float speedMax, float speedMin, const sf::Color& particleColor, const List<std::string>& particleImagePaths)
		: mParticleAmt{ particleAmt },
		mLifeTimeMin{ lifeTimeMin },
		mLifeTimeMax{ lifeTimeMax },
		mSizeMax{ sizeMax },
		mSizeMin{ sizeMin },
		mSpeedMax{ speedMax },
		mSpeedMin{ speedMin },
		mParticleColor{ particleColor },
		mParticleImagePaths{ particleImagePaths }
	{
	}
	void Explosion::SpawnExplosion(World* world, const sf::Vector2f& location)
	{
		if (!world)
		{
			return;
		}


		for (int i = 0; i < mParticleAmt; ++i)
		{
			std::string particleImagePath = mParticleImagePaths[(int)RandomRange(0, mParticleImagePaths.size())];
			weak<Particle> newParticle = world->SpawnActor<Particle>(particleImagePath);

			newParticle.lock()->RandomLifeTime(mLifeTimeMin, mLifeTimeMax);
			newParticle.lock()->SetActorLocation(location);
			newParticle.lock()->RandomSize(mSizeMin, mSizeMax);
			newParticle.lock()->RandomVelocity(mSpeedMin, mSpeedMax);
			newParticle.lock()->GetSprite().setColor(mParticleColor);
		}
	}

}

