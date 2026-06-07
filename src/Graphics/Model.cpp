#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#include <iostream>


//デストラクタ
Model::~Model(){
    for(auto mesh : meshes)
    {
        delete mesh;
    }
}

//モデル読み込み
bool Model::load(const std::string& path)
{
    Assimp::Importer importer;

    //FBXファイル読み込み
    const aiScene* scene =
    importer.ReadFile(
        path,
        aiProcess_Triangulate
    );

    if(!scene)
    {
        std::cout
            << importer.GetErrorString()
            <<std::endl;
        return false;
    }

    //Mesh生成
    std::cout
        << "Model Count="
        << scene->mNumMeshes
        << std::endl;

    for(unsigned int meshIndex=0;
        meshIndex < scene->mNumMeshes;
        meshIndex++)
    {
        aiMesh* ai_mesh =
            scene->mMeshes[meshIndex];

        std::vector<glm::vec3> vertices;
        std::vector<unsigned int> indices;

        //頂点取得
        for(unsigned int v=0;
            v < ai_mesh->mNumVertices;
            v++)
        {
            vertices.push_back(
                    glm::vec3(
                        ai_mesh->mVertices[v].x,
                        ai_mesh->mVertices[v].y,
                        ai_mesh->mVertices[v].z
                    )
            );
        }

        //インデックス取得
        for(unsigned int i=0;
            i < ai_mesh->mNumFaces;
            i++)
        {
            aiFace face =
                ai_mesh->mFaces[i];

            for(unsigned int j=0;
                j < face.mNumIndices;
                j++)
            {
                indices.push_back(
                    face.mIndices[j]
                );
            }
        }

        //Mesh作成
        Mesh* mesh = new Mesh();

        mesh->setUp(
            vertices,
            indices
        );

        meshes.push_back(mesh);
    }

    return true;
}

void Model::draw()
{
    for(auto& mesh : meshes)
    {
        mesh->draw();
    }
}