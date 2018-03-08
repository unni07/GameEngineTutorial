#include "BoundaryHandlerComponent.h"
#include <Entities\Entity.h>
#include <Entities\Components\PhysicsComponent.h>
using Math::vector3D;

namespace Entities
{
	BoundaryHandlerComponent::BoundaryHandlerComponent()
	{
		boundaryVerts = 0;
		physics = 0;
	}
	bool BoundaryHandlerComponent::initialize()
	{
		physics = getParent()->getComponent<PhysicsComponent>();
		return physics != NULL && boundaryVerts != NULL;
	}

	void BoundaryHandlerComponent::setData(vector3D* boundaryVerts, JE::uint numBoundaryVerts)
	{
		this->boundaryVerts = boundaryVerts;
		NUM_BOUNDARY_VERTS = numBoundaryVerts;
	}

	bool BoundaryHandlerComponent::shutdown()
	{
		return true;
	}
	void BoundaryHandlerComponent::update()
	{
		for (JE::uint i = 0; i < NUM_BOUNDARY_VERTS; i++)
		{
			const vector3D& first = boundaryVerts[i];
			const vector3D& second = boundaryVerts[(i + 1) % NUM_BOUNDARY_VERTS];

			vector3D wall = second - first;
			vector3D normal = wall.perpCcwXY();
			vector3D respectiveShipPosition = getParent()->position - first;
			float dotResult = normal.dot(respectiveShipPosition);

			if (dotResult < 0)
			{
				//shipVelocity = shipVelocity - 2 * shipVelocity.dot(normal)*normal;
				physics->velocity = physics->velocity - 2 * physics->velocity.projectOnto(normal);
				getParent()->position = oldPosition;
			}
			
		}
		oldPosition = getParent()->position;
	}
}
