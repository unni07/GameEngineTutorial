#pragma once
namespace Entities
{
	class Entity;
	class __declspec(dllexport) Component
	{
		friend class Entity;
		Entity* parent;
	public:
		/*Component();
		~Component();*/
		Entity * getParent() const;
		virtual void update() {}
		virtual bool initialize() { return true; }
		virtual bool shutdown() { return true; }
	};
}

