#pragma once
#include <Entities\Component.h>

namespace Entities
{
	class PhysicsComponent;
	class ControllerComponent : public Component
	{
		PhysicsComponent * physics;
	public:
		/*ControllerComponent();
		~ControllerComponent();*/
		void update();
		bool initialize();
	};
}
