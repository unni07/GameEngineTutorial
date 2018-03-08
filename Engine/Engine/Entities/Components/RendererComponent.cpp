#include "RendererComponent.h"
#include <Rendering\Renderer.h>
#include <Math\matrix2DH.h>
#include <Entities\Entity.h>
namespace Entities {
	//RendererComponent::RendererComponent()
//{
//}
//
//
//RendererComponent::~RendererComponent()
//{
//}

	void Entities::RendererComponent::setData(Rendering::Renderable * renderable)
	{
		this->renderable = renderable;
	}

	void RendererComponent::update()
	{
		renderable->where = Math::matrix2DH::translate(getParent()->position) * Math::matrix2DH::rotateZ(getParent()->orientation);
	}

}