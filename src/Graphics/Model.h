#pragma once

#include "Mesh.h"

#include <string>
#include <vector>

class Model
{
public:

    bool load(const std::string& path);

    void draw();

private:

    std::vector<Mesh> meshes;
};