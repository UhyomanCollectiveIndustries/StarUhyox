#include "CollisionManager.h"

#include <glm/glm.hpp>
//#include <glm/gtx/norm.hpp>

//弾とステージオブジェクトの衝突判定
void CollisionManager::checkBulletVsStage(
    BulletManager& bullets,
    Stage& stage){
        //アクティブ状隊の弾を全て調べる
        bullets.bullets.forEachActive([&](Bullet& bullet){
            //ステージオブジェクトを全て調べる
            for(auto& obj : stage.worldObjects){
                //ステージオブジェクトがアクティブ状隊でなければ無視
                if(!obj.isActive)
                    continue;

                //衝突判定はSphereCollisionで実現
                //  弾とステージオブジェクトの距離を計算
                //  glm::distanceの内部
                //       d = √(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2
                float dist =
                    glm::distance(
                        bullet.position,
                        obj.position
                    );
                //距離がステージオブジェクトの半径以内にあれば衝突を検知
                //  弾とステージオブジェクトのアクティブ状態を両方falseに
                if(dist < obj.radius){
                    bullet.isActive = false;
                    obj.isActive = false;

                    break;
                }
            }           
        });
}