#include "Entity.h"
#include <cassert>
#include <Entities\Component.h>
#include <Misc\TypeDefs.h>
using namespace Entities;

Entity::Entity()
{
	numComponents = 0;
	orientation = 0.0f;
}

//
//Entity::~Entity()
//{
//}

bool Entities::Entity::initialize()
{
	for (JE::uint i = 0; i < numComponents; i++)
		if (!components[i]->initialize())
			return false;
	return true;
}

bool Entities::Entity::shutdown()
{
	for (JE::uint i = 0; i < numComponents; i++)
		if (!components[i]->shutdown())
			return false;
	return true;
}

void Entities::Entity::addComponent(Component * component)
{
	
	assert(numComponents != NUM_MAX_COMPONENTS);
	components[numComponents++] = component;
	component->parent = this;
}

void Entities::Entity::update()
{
	for (JE::uint i = 0; i < numComponents; i++)
		components[i]->update();
}
