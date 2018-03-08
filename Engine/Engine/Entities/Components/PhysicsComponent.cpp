#include "PhysicsComponent.h"
#include <Entities\Entity.h>
#include <Time\GameClock.h>



//
//
//PhysicsComponent::~PhysicsComponent()
//{
//}
namespace Entities
{
	PhysicsComponent::PhysicsComponent()
	{
		angularVelocity = 0.0f;
	}
	void Entities::PhysicsComponent::update()
	{
		velocity += acceleration * gameClock.dt();
		acceleration = Math::vector3D();
		getParent()->position += velocity * gameClock.dt();
		getParent()->orientation += angularVelocity;
	}
}