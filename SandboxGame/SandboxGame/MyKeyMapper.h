#pragma once
#include<Input\IkeyMapper.h>
namespace Input
{
	class MyKeyMapper : public IKeyMapper
	{
	public:
		/*MyKeyMapper();
		~MyKeyMapper();*/

		//int getActionFor(int key);
		int getkeyFor(int action) const;
	};
}

