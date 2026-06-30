#include "ModelManager.h"

Model* ModelManager::load(const std::string& path)
{
    auto it = models.find(path);

    if(it != models.end())
    {
        return it -> second.get();
    }
    
    auto model = std::make_unique<Model>();

    if(!model->load(path))
    {
        return nullptr;
    }

    Model* ptr = model.get();

    models[path] = std::move(model);
    
    return ptr;
}