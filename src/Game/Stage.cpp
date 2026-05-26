#include "Stage.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Stage::Stage(){
    for(int z = 0;z > -100;z -= 10){
        StageObject left;

        //ステージ左側の立方体
        left.position =
            glm::vec3(
                -3.0f,
                0.0f,
                (float)z
            );
            
        worldObjects.push_back(left);

        //ステージ右側の立方体
        StageObject right;

        right.position =
            glm::vec3(
                3.0f,
                0.0f,
                (float)z
            );

        worldObjects.push_back(right);
    }
}

void Stage::draw(GLuint modelLoc){
        for (const auto& obj : worldObjects)
        {
            //アクティブ状態でないオブジェクトを描画しない
            if(!obj.isActive)
                continue;

            glm::mat4 model = glm::translate(
                glm::mat4(1.0f),
                obj.position
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