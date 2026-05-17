#include "Bullet.h"

//初期化
void Bullet::init(glm::vec3 startPos,glm::vec3 dir){
    isActive = true;
    position = startPos;
    velocity = dir;
}

//更新
void Bullet::update(float deltaTime){
    //前方へ飛んでいく
    position += velocity*deltaTime;
}

//描画
void Bullet::draw(GLuint modelLoc,GLuint vao){
    if(!isActive)return;

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        position
    );

    model = glm::scale(
        model,
        glm::vec3(0.2f)
    );

    glUniformMatrix4fv(
        modelLoc,
        1,
        GL_FALSE,
        glm::value_ptr(model)
    );

    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES,0,36);
}