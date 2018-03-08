#include "MyGame.h"
#include<Rendering\Renderable.h>
#include <Rendering\Geometry.h>
#include <cstdlib>
#include <Input\KeyInput.h>
#include "MyMenuChoice.h"
#include <Time\GameClock.h>
#include <Misc\Helpers.h>
using namespace Rendering;
using Math::vector3D;
bool MyGame::initializeShip()
{

	vector3D shipVertData[] =
	{
		Math::vector3D(+0.0f, +0.14142135623f,1.0f),
		Math::vector3D(-0.1f, -0.1f,1.0f),
		Math::vector3D(+0.1f, -0.1f,1.0f)

		/*vector3D(+0.0f, +0.14142135623f*0,1.0f*0),
		vector3D(-0.1f*0, -0.1f,1.0f*0),
		vector3D(+0.1f*0, -0.1f,1.0f*0)*/
	};
	ushort shipIndiceData[] = { 0,1,2 };
	if (ARRAY_SIZE(shipVerts) != NUM_SHIP_VERTS)
		return false;

	if (ARRAY_SIZE(shipIndices) != NUM_SHIP_INDICES)
		return false;

	memcpy(shipVerts, shipVertData, sizeof(shipVertData));
	memcpy(shipIndices, shipIndiceData, sizeof(shipIndiceData));

	ship.addComponent(&shipController);
	
	shipBoundaryHandler.setData(boundaryVerts,NUM_BOUNDARY_VERTS);
	ship.addComponent(&shipBoundaryHandler);
	ship.addComponent(&shipPhysics);
	Geometry* shipGeometry = renderer.addGeometry(shipVerts, NUM_SHIP_VERTS, shipIndices, NUM_SHIP_INDICES);
	shipRenderable = renderer.addRenderable(shipGeometry);
	//lerpInstance = renderer.addRenderable(shipGeometry);
	shipRenderer.setData(shipRenderable);
	//ship.initialize();
	
	ship.addComponent(&shipRenderer);	
	return ship.initialize();
}

bool MyGame::sendBoundaryDataToRenderer()
{
	vector3D boundaryVertData[]
	{
		vector3D(+0.0f, +1.0f, +0.0f),
		vector3D(-1.0f, +0.0f, +0.0f),
		vector3D(+0.0f, -1.0f, +0.0f),
		vector3D(+1.0f, +0.0f, +0.0f)

		/*vector3D(+0.0f, +0.0f, +0.0f),
		vector3D(-0.0f, +0.0f, +0.0f),
		vector3D(+0.0f, -0.0f, +0.0f),
		vector3D(+1.0f, +0.0f, +0.0f)*/
	};
	GLushort boundaryIndicesData[] = { 0,1,1,2,2,3,3,0 };
	if (ARRAY_SIZE(boundaryVertData) != NUM_BOUNDARY_VERTS)
		return false;

	if (ARRAY_SIZE(boundaryIndicesData) != NUM_BOUNDARY_INDICES)
		return false;

	memcpy(boundaryVerts, boundaryVertData, sizeof(boundaryVertData));
	memcpy(boundaryIndices, boundaryIndicesData, sizeof(boundaryIndicesData));

	Geometry*boundaryGeometry = renderer.addGeometry(boundaryVerts, NUM_BOUNDARY_VERTS,
		boundaryIndices, NUM_BOUNDARY_INDICES, GL_LINES);
	renderer.addRenderable(boundaryGeometry);

	return true;
}


bool MyGame::initialize()
{
	if (!renderer.initialize())
		return false;
	if (! input.initialize(&keyMapper, Input::MyMenuChoice::MAX))
		return false;
	if (!gameClock.initialize())
		return false;
	if (!initializeShip())
		return false;

	if (!connect(&myTimer, SIGNAL(timeout()), this, SLOT(update())))
		return false;

	if (!sendBoundaryDataToRenderer())
		return false;

	return true;	
}

bool MyGame::shutdown()
{
	bool good = true;
	good &= ship.shutdown();
	good &= input.shutdown();
	good &= renderer.shutdown();
	good &= gameClock.shutdown();
	return good;
}

void MyGame::go()
{
	myTimer.start();
}

void MyGame::update()
{
	/*shipInstance->where = Matrix2DH::translate(shipPosition);
	lerpInstance->where = Matrix2DH::translate(lerperPosition);*/
	gameClock.newFrame();
	input.update();
	ship.update();
	renderer.renderScene();
}
