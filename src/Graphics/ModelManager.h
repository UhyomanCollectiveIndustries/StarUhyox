#pragma once

#include "Model.h"

#include <unordered_map>
#include <memory>
#include <string>

/**
 * モデルマネージャークラス
 * モデルのロード
 * モデルの管理
 */
class ModelManager
{
public:
    /** モデルのロード */
    Model* load(const std::string& path);

private:
    std::unordered_map<
        std::string,
        std::unique_ptr<Model>
    > models;
};