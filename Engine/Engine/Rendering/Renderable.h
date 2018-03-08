#pragma once
#include <Math\matrix2DH.h>

namespace Rendering
{
	class Geometry;
	class Renderable
	{
		friend class Renderer;
		const Geometry * what;
	public:
		Math::matrix2DH where;
	};
}