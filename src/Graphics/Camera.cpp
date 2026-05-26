#include "Camera.h"

//コンストラクタ
Camera::Camera(){
    position = glm::vec3(0.0f,0.0f,3.0f);

    target = glm::vec3(0.0f);

    up = glm::vec3(0.0f,1.0f,0.0f);
}

glm::mat4 Camera::GetViewMatrix(){
    return glm::lookAt(
        position,
        target,
        up
    );
}