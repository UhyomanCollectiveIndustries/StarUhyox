#pragma once

#include "../Core/Transform.h"
#include "../Graphics/Model.h"

class GameObject
{
public:
    /** ゲーム上の位置・回転・拡大縮小 */
    Transform transform;

    /** FBX補正 */
    Transform modelTransform;

    Model* model = nullptr;

public:
    virtual ~GameObject() = default;

    // 更新
    virtual void update(float deltaTime);

    // 描画
    virtual void draw(unsigned int modelLoc);
    
    /** モデルの適用 */
    void setModel(Model* model);
};