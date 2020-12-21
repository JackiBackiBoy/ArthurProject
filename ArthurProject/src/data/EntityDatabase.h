#pragma once
#include <string>
#include <map>
#include <Nodes\Node.h>
#include "Nodes/Animator.h"
class EntityDatabase
{
public:
	inline static Node* CreateEntity(std::string anEntity, int aVariant = 0)
	{
		Node* tempNode = nullptr;

		if (anEntity == "Bush")
		{
			tempNode = new Animator();
		}

		return tempNode;
	}
};
