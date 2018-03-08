#pragma once
#include <QtOpenGL\QGLWidget>
#include <Misc\TypeDefs.h>
#include <Rendering\Geometry.h>
#include <Rendering\Renderable.h>
#include <Math\matrix2D.h>

namespace Math { struct vector3D; }
using namespace JE;

namespace Rendering
{
	class Renderable;
	class __declspec(dllexport) Renderer : public QGLWidget
	{
		static const uint NUM_MAX_GEOMETRIES = 10;
		Geometry geometries[NUM_MAX_GEOMETRIES];
		static const uint NUM_MAX_RENDERABLES = 10;
		Renderable renderables[NUM_MAX_RENDERABLES];
		uint numGeometries;
		uint numRenderables;
		static const uint MAX_BUFFER_SIZE = 1024;
		GLuint vertexBufferID;
		GLuint indexBufferID;
		static const uint MAX_VERTS = 10;
	public:
		Renderer();
		~Renderer();
		bool initialize();
		bool shutdown();
		Geometry * addGeometry(Math::vector3D* verts, uint numVerts, ushort* indices, uint numIndices, GLenum renderMode = GL_TRIANGLES);
		Renderable * addRenderable(Geometry* geometry);
		void renderScene();
		Math::matrix2DH getAspectCorrectionMatrix() const;
	protected:
		void initializeGL();
		void paintEvent();
		void paintGL();

	};
}
