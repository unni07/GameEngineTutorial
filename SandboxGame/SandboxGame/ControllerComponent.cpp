#include "ControllerComponent.h"
#include <Input\KeyInput.h>
#include "MyMenuChoice.h"
#include <Entities\Entity.h>
#include <Entities\Components\PhysicsComponent.h>
#include <cmath>
#include <Math\vector3D.h>
#include <Math\matrix2DH.h>
using Math::vector3D;
using Math::matrix2DH;
namespace Entities
{
	//ControllerComponent::ControllerComponent()
	//{
	//}
	//
	//
	//ControllerComponent::~ControllerComponent()
	//{
	//}

	void ControllerComponent::update()
	{
		const float ANGULAR_VELOCITY = 0.1f;
		if (input.actionsHot(Input::RotateLeft))
			physics->angularVelocity = ANGULAR_VELOCITY;
		else if (input.actionsHot(Input::RotateRight))
			physics->angularVelocity = -ANGULAR_VELOCITY;
		else
		{
			physics->angularVelocity = 0.0f;
		}
		if (input.actionsHot(Input::Accelerate))
		{
			//physics->acceleration = matrix2DH::rotateZ(getParent()->orientation) * vector3D(1, 0, 0);
			physics->acceleration = vector3D(-sin(getParent()->orientation), cos(getParent()->orientation));
		}
	}
	bool ControllerComponent::initialize()
	{
		physics = getParent()->getComponent<PhysicsComponent>();
		return physics != 0;
	}
}