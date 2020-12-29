#pragma once
#include "Nodes/Node.h"
class NodeTemplate :
    public Node
{
public:
    void OnUpdate() override;
    void OnRender(sf::RenderWindow* aWindow) override;
};

