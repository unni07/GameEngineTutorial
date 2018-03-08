#pragma once
//#include <Qt\qobject.h>
#include <QT/qtimer.h>
#include<Rendering/Renderer.h>
#include <Math\vector3D.h>
#include <Entities\Entity.h>
#include <Entities\Components\RendererComponent.h>
#include <Entities\Components\PhysicsComponent.h>
#include "ControllerComponent.h"
#include "MyKeyMapper.h"
#include <Entities\Components\BoundaryHandlerComponent.h>
namespace Rendering { class Renderable; }


class MyGame : public QObject
{
	Q_OBJECT
private:
	Input::MyKeyMapper keyMapper;
	Entities::Entity ship;
	Entities::RendererComponent shipRenderer;
	Entities::PhysicsComponent shipPhysics;
	Entities::ControllerComponent shipController;
	Entities::BoundaryHandlerComponent shipBoundaryHandler;

	QTimer myTimer;


	
	Rendering::Renderer renderer;
	Rendering::Renderable * shipRenderable;
	Rendering::Renderable * lerpRenderable;

	static const JE::uint NUM_SHIP_VERTS = 3;
	Math::vector3D shipVerts[NUM_SHIP_VERTS];
	static const uint NUM_SHIP_INDICES = 3;
	ushort shipIndices[NUM_SHIP_INDICES];

	static const JE::uint NUM_BOUNDARY_VERTS = 4;
	Math::vector3D boundaryVerts[NUM_BOUNDARY_VERTS];
	static const uint NUM_BOUNDARY_INDICES = 8;
	ushort boundaryIndices[NUM_BOUNDARY_INDICES];

	bool initializeShip();
	bool sendBoundaryDataToRenderer();
private slots:
	void update();

public:
	//MyGame();
	/*~MyGame();*/
	bool initialize();
	bool shutdown();
	void go();
};

