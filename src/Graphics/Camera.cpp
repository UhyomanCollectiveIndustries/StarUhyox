#include "Camera.h"

//コンストラクタ
Camera::Camera(){
    target = glm::vec3(0.0f);
}

glm::mat4 Camera::GetViewMatrix(){
    return glm::lookAt(
        transform.position,
        target,
        glm::vec3(0.0f,1.0f,0.0f)
    );
}