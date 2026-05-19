#pragma once

class Bullet;
struct StageObject;

struct CollisionEvent 
{
    //Pool運用のため生ポインタを用いる
    Bullet* bullet;

    StageObject* StageObject;
};