#include <Windows.h>
#include <cassert>
#include "MyKeyMapper.h"
#include "MyMenuChoice.h"

namespace Input
{
	/*int MyKeyMapper::getActionFor(int key)
	{
		switch (key)
		{
		case Accelerate:
			return VK_UP;
		case RotateLeft:
			return VK_LEFT;
		case RotateRight:
			return VK_RIGHT;
		}
		assert(false);
		return -1;
	}*/
	int MyKeyMapper::getkeyFor(int action) const
	{
		switch (action)
		{
		case Accelerate:
			return VK_UP;
		case RotateLeft:
			return VK_LEFT;
		case RotateRight:
			return VK_RIGHT;
		}
		return 0;
	}
}