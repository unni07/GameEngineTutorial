#pragma once
#include<Misc\TypeDefs.h>

using namespace JE;
namespace Math 
{
	class vector3D; 
}

namespace Rendering
{
	class Geometry
	{
		friend class Renderer;

		const Math::vector3D* vertices;
		uint numVerts;
		const ushort* indices;
		uint numIndices;
		GLenum renderMode;
	};
}