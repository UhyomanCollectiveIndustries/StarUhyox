#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

class Mesh
{
public:

    //コンストラクタ
    Mesh();
    //デストラクタ
    ~Mesh();

    //頂点データのセットアップ
    //@param vertices 頂点座標のリスト
    //@param indices 頂点インデックスのリスト
    void SetUp(
        const std::vector<glm::vec3>& vertices,
        const std::vector<unsigned int>& indices
    );

    //描画
    void Draw();

private:

    //頂点データ
    unsigned int vao = 0;
    //頂点バッファオブジェクト
    unsigned int vbo = 0;

    unsigned int ebo = 0;

    //頂点数
    unsigned int indexCount = 0;
};