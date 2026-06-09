#pragma once

#include "../Core/Transform.h"
#include "../Graphics/Model.h"

class GameObject
{
public:

    Transform transform;

    Model* model = nullptr;

    virtual ~GameObject() = default;

    //更新
    virtual void update(float deltaTime);

    //描画
    virtual void draw(unsigned int modelLoc);
};