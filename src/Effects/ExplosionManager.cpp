#include "ExplosionManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

void ExplosionManager::spawn(const glm::vec3 posiotion){
    for(auto& e : explosions){
        if(!e.isActive){
            e.isActive = true;
            e.position = posiotion;
            e.lifeTime = 1.0f;

            break;
        }
    }
}

void ExplosionManager::update(float deltaTime){
    for(auto& e : explosions){
        if(!e.isActive)
            continue;

        e.lifeTime -= deltaTime;

        if(e.lifeTime <= 0.0f){
            e.isActive = false;
        }
    }
}

void ExplosionManager::draw(GLuint modelLoc,GLuint vao){
    for(auto& e : explosions){
        if(!e.isActive)
            continue;

            glBindVertexArray(vao);

            for(auto& e : explosions)
            {
                if(!e.isActive)
                    continue;

                glm::mat4 model = glm::translate(
                    glm::mat4(1.0f),
                    e.position
                );

                model = glm::scale(
                    model,
                    glm::vec3(1.5f)
                );

                glUniformMatrix4fv(
                    modelLoc,
                    1,
                    GL_FALSE,
                    glm::value_ptr(model)
                );

                glDrawArrays(
                    GL_TRIANGLES,
                    0,
                    36
                );
            }
    }
}