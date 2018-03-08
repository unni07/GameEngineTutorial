#pragma once

namespace Input
{
	class IKeyMapper
	{
	public:
		//virtual int getActionFor(int key) const = 0;
		virtual int getkeyFor(int action) const = 0;
	};
}