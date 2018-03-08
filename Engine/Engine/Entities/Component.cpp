#include "Component.h"

using namespace Entities;

//Component::Component()
//{
//}
//
//
//Component::~Component()
//{
//}

Entity * Entities::Component::getParent() const
{
	return parent;
}
