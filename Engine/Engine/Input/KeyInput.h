#pragma once

namespace Input
{
	class IKeyMapper;
	class __declspec(dllexport)KeyInput
	{
		IKeyMapper * keyMapper;
		int maxActionValue;
		int _actionsThisFrame;
		KeyInput() {}
		KeyInput(const KeyInput&);
		KeyInput& operator=(const KeyInput&);
		static KeyInput instance;

	public:
		bool initialize(IKeyMapper * keyMapper, int maxActionValue);
		bool shutdown();
		void update();
		inline int actionsThisFrame() const { return _actionsThisFrame; };
		bool actionsHot(int actions) const;
		static KeyInput& getInstance();
		/*KeyInput();
		~KeyInput();*/
	};
#define input Input::KeyInput::getInstance()

}

