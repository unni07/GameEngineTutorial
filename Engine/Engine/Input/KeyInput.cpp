#include <Windows.h>
#include "KeyInput.h"
#include "IkeyMapper.h"

namespace Input
{
	//KeyInput::KeyInput()
	//{
	//}
	//
	//
	//KeyInput::~KeyInput()
	//{
	//}



	KeyInput KeyInput::instance;
	bool KeyInput::initialize(IKeyMapper * keyMapper, int maxActionValue)
	{
		if (keyMapper == 0 || maxActionValue < 0)
			return false;
		this->keyMapper = keyMapper;
		this->maxActionValue = maxActionValue;
		return true;
	}

	bool KeyInput::shutdown()
	{
		return true;
	}
	void KeyInput::update()
	{
		_actionsThisFrame = 0;

		int possibleActions = 1;
		while (possibleActions != maxActionValue)
		{
			int key = keyMapper->getkeyFor(possibleActions);
			if (GetAsyncKeyState(key))
				_actionsThisFrame |= possibleActions;

			possibleActions <<= 1;
		}
	}
	/*int KeyInput::actionsThisFrame() const
	{
		return actionsThisFrame;
	}*/
	bool KeyInput::actionsHot(int actions) const
	{
		return (_actionsThisFrame & actions) == actions;
	}
	KeyInput& KeyInput::getInstance()
	{
		// TODO: insert return statement here
		return instance;
	}
}
