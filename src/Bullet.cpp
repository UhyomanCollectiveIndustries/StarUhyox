#include "Bullet.h"

//初期化
//  弾を指定の位置・方向で初期化、アクティブ状態にする
//  ObjectPoolからalloc()された直後に呼ばれることを想定
void Bullet::init(glm::vec3 startPos,glm::vec3 dir){
    //プールから取り出したばかりのオブジェクトを有効に
    //アクティブ状態にすることで、update/drawの処理対象に
    isActive = true;
    position = startPos;

    //dirは「方向*速度」の合成済のベクトルを受け取る
    //Bullet側では、そのまま毎フレームの移動量として用いる
    velocity = dir;
}

//更新
//  弾の位置をdeltaTime分だけ、全進させる
void Bullet::update(float deltaTime){
    //アクティブ状態でなければ描画しない
    //  BulletManagerがforEachActive()で絞り込んでいるため、
    //  通常はここにこないが、直接呼ばれた際の安全策として
    if(!isActive)return;

    //前方へ飛んでいく
    position += velocity*deltaTime;
}

//描画
//  弾を小さな立方体として描画
void Bullet::draw(GLuint modelLoc,GLuint vao){
    //アクティブ状態でなければ描画しない
    //  BulletManagerがforEachActive()で絞り込んでいるため、
    //  通常はここにこないが、直接呼ばれた際の安全策として
    if(!isActive)return;

    glm::mat4 model = glm::mat4(1.0f);

    //弾の現在位置へ移動
    model = glm::translate(
        model,
        position
    );

    //プレイヤー機体やワールドオブジェクトより小さく見せるため、0.2倍に縮小
    model = glm::scale(
        model,
        glm::vec3(0.2f)
    );

    //GPU側の"model"uniformを更新して、ワールド変換行列を返す
    glUniformMatrix4fv(
        modelLoc,
        1,
        GL_FALSE,
        glm::value_ptr(model)
    );

    glBindVertexArray(vao);

    //立方体:6面*三角形2枚*3頂点*=36頂点
    glDrawArrays(GL_TRIANGLES,0,36);
}