#include "Mesh.h"

#include <iostream>

//コンストラクタ
Mesh::Mesh()
{
}

//デストラクタ
//GPUリリース解放
Mesh::~Mesh()
{
    if(vao)
        glDeleteVertexArrays(1, &vao);

    if(vbo)
        glDeleteBuffers(1, &vbo);

    if(ebo)
        glDeleteBuffers(1, &ebo);

    std::cout
        << "Delete VAO="
        << vao
        << std::endl;
}

//セットアップ
void Mesh::setUp(
    const std::vector<glm::vec3>& vertices,
    const std::vector<unsigned int>& indices
)
{
    //描画に使うインデックス数を保存
    indexCount =
        static_cast<unsigned int>(
            indices.size()
        );
    
    //VAO/VBO/EBO生成
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    //--------------
    // VBO設定(VBO)
    //--------------
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(glm::vec3),
        vertices.data(),
        GL_STATIC_DRAW
    );

    //---------------------
    // EBO設定(インデックス)
    //---------------------
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW
    );

    //--------------
    // 頂点属性設定
    //--------------
    glVertexAttribPointer(
        0,                  //location
        3,                  //vec3
        GL_FLOAT,
        GL_FALSE,
        sizeof(glm::vec3),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    //VAO解除
    glBindVertexArray(0);

    std::cout
        << "VAO=" << vao
        << " VBO=" << vbo
        << " EBO=" << ebo
        << std::endl;
}

//描画
void Mesh::draw()
{
    //VAOをバインドして描画
    glBindVertexArray(vao);
    
    glDrawElements(
        GL_TRIANGLES,
        indexCount,
        GL_UNSIGNED_INT,
        nullptr
    );

    glBindVertexArray(0);
}