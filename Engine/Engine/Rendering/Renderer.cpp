#include <glew.h>
#include "Renderer.h"
#include <cassert>
namespace Rendering {
	Renderer::Renderer()
	{
	}


	Renderer::~Renderer()
	{
	}

	bool Renderer::initialize()
	{
		vertexBufferID = -1;
		indexBufferID = -1;
		numGeometries = 0;
		numRenderables = 0;
		show();
		return true;
	}

	bool Renderer::shutdown()
	{
		if(vertexBufferID != -1)
			glDeleteBuffers(1, &vertexBufferID);
		if(indexBufferID != -1)
			glDeleteBuffers(1, &indexBufferID);
		return true;
	}

	Geometry * Rendering::Renderer::addGeometry(Math::vector3D * verts, uint numVerts, 
												ushort * indices, uint numIndices, GLenum renderMode)
	{
		assert(numGeometries != NUM_MAX_GEOMETRIES);
		assert(numVerts <= MAX_VERTS);
		Geometry& g = geometries[numGeometries++];
		g.vertices = verts;
		g.numVerts = numVerts;
		g.indices = indices;
		g.numIndices = numIndices;
		g.renderMode = renderMode;
		return &g;
	}

	Renderable * Rendering::Renderer::addRenderable(Geometry * geometry)
	{
		assert(numRenderables != NUM_MAX_RENDERABLES);
		Renderable &r = renderables[numRenderables++];
		r.what = geometry;

		return &r;
	}
	void Renderer::renderScene()
	{
		glDraw();
	}
	Math::matrix2DH Renderer::getAspectCorrectionMatrix() const
	{
		float aspectRatio  = static_cast<float>(width() / height());
		Math::matrix2DH scale;
		if (aspectRatio > 1)
			return Math::matrix2DH::scale(1 / aspectRatio, 1);
		else
			return Math::matrix2DH::scale(1, aspectRatio);
		//return scale;
	}
	void Renderer::initializeGL()
	{
		GLenum status = glewInit();
		assert(status == 0);
		
		glClearColor(0, 0, 0, 1);
		
		glGenBuffers(1, &vertexBufferID);
		glGenBuffers(1, &indexBufferID);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

		glBufferData(GL_ARRAY_BUFFER, MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	void Renderer::paintEvent()
	{
	}
	void Renderer::paintGL()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		Math::vector3D transformedVerts[MAX_VERTS];
		for (uint i = 0; i < numRenderables; i++)
		{
			Renderable& r = renderables[i];
			//Indices
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(ushort)*r.what->numIndices, (void*)(r.what->indices));

			//vertices
			Math::matrix2DH op = getAspectCorrectionMatrix() * r.where;
			for (uint j = 0; j < r.what->numVerts; j++)
			{
				transformedVerts[j] = op * r.what->vertices[j];				
			}
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Math::vector3D) * r.what->numVerts, transformedVerts);
			glDrawElements(r.what->renderMode, r.what->numIndices, GL_UNSIGNED_SHORT, 0);
		}
	}
}
