#pragma once

#include "Mesh.h"

#include <string>
#include <vector>

//=========================================
// Modelクラス
// 複数Meshの集合(3Dモデル全体)を管理する
//=========================================
class Model
{
public:

    //モデルの読み込み
    //@param path モデルパス
    bool load(const std::string& path);

    //描画
    void draw();

private:

    //モデルを構成するメッシュ群
    std::vector<Mesh> meshes;
};