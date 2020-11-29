#pragma once
#include "Nodes\Node.h"

class NodeManager
{
public:
	static Node* GenerateNode(const std::string& aPreset);
};