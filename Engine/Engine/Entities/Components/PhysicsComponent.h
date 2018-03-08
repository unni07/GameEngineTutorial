#pragma once
#include <Entities\Component.h>
#include <Math\Vector3D.h>
namespace Entities {
	class __declspec(dllexport) PhysicsComponent :public Component
	{
	public:
		float angularVelocity;
		Math::vector3D velocity;
		Math::vector3D acceleration;
		void update();
		PhysicsComponent();
		/*~PhysicsComponent();*/
	};
}

