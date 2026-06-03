#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>


//================================
// Meshクラス
// 1つのメッシュ(頂点+インデックス)
//     をGPUに転送して描画
//===============================
class Mesh
{
public:

    //コンストラクタ
    Mesh();
    //デストラクタ
    ~Mesh();

    //頂点データのセットアップ
    //@param vertices 頂点座標の配列
    //@param indices 頂点インデックス配列
    void setUp(
        const std::vector<glm::vec3>& vertices,
        const std::vector<unsigned int>& indices
    );

    //描画
    void draw();

private:
    //=============================
    // OpenGLバッファ
    //=============================

    //頂点の設定を保持
    unsigned int vao = 0;
    //頂点データ
    unsigned int vbo = 0;

    //インデックス
    unsigned int ebo = 0;

    //描画するインデックス数
    unsigned int indexCount = 0;
};