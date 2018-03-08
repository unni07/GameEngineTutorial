#pragma once
#include <Entities\Component.h>
#include <Misc\TypeDefs.h>
#include <Math\vector3D.h>
namespace Entities
{
	class PhysicsComponent;
	class __declspec(dllexport) BoundaryHandlerComponent : public Component
	{
		JE::uint NUM_BOUNDARY_VERTS;
		const Math::vector3D* boundaryVerts;
		PhysicsComponent* physics;
		Math::vector3D oldPosition;
	public:
		BoundaryHandlerComponent();
		bool initialize();
		void setData(Math::vector3D* boundaryVerts, JE::uint numBoundaryVerts);
		bool shutdown();
		void update();
	};
}

