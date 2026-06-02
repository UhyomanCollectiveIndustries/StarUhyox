#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#include <iostream>

bool Model::load(const std::string& path)
{
    Assimp::Importer importer;

    const aiScene* scene =
    importer.ReadFile(
        "assets/models/test.fbx",
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

    for(unsigned int i=0;
        i < scene->mNumMeshes;
        i++)
    {
            aiMesh* ai_mesh =
                scene->mMeshes[i];

            std::vector<glm::vec3> vertices;
            std::vector<unsigned int> indices;
        

        //頂点取得
        for(unsigned int i=0;
            i < ai_mesh->mNumVertices;
            i++)
        {
            vertices.push_back(
                    glm::vec3(
                        ai_mesh->mVertices[i].x,
                        ai_mesh->mVertices[i].y,
                        ai_mesh->mVertices[i].z
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
        Mesh mesh;

        mesh.setUp(
            vertices,
            indices
        );

        meshes.push_back(mesh);
    }

    return true;
}