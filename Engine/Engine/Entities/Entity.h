#pragma once
#include <Misc\TypeDefs.h>
#include <Math\vector3D.h>
using namespace JE;
namespace Entities
{
	class Component;
	class __declspec(dllexport) Entity
	{
		static const JE::uint NUM_MAX_COMPONENTS = 10;
		Component* components[NUM_MAX_COMPONENTS];
		JE::uint numComponents;
	public:
		Math::vector3D position;
		float orientation;
		bool initialize();
		bool shutdown();
		void addComponent(Component* component);
		void update();
		Entity();
		template<class T>
		T* getComponent() const;
		//~Entity();
	};



	template<class T>
	T* Entity::getComponent() const
	{
		for (uint i = 0; i < numComponents; i++)
		{
			T* ret = dynamic_cast<T*>(components[i]);
			if (ret != 0)
				return ret;
		}
		return NULL;
	}
}

