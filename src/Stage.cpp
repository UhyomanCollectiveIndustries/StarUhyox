#include "Stage.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Stage::Stage(){
    for(int z = 0;z > -100;z -= 10){
        worldObjects.push_back(
            glm::vec3(
                -3.0f, 0.0f, (float)z)
        );

        worldObjects.push_back(
            glm::vec3(
                3.0f,0.0f,(float)z)
        );
    }
}

void Stage::draw(GLuint modelLoc){
    for (const auto& pos : worldObjects)
    {
        glm::mat4 model = glm::translate(
            glm::mat4(1.0f),
            pos
        );

        glUniformMatrix4fv(
            modelLoc,
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}