#pragma once

class Bullet;
struct StageObject;

struct CollisonEvent 
{
    //Pool運用のため生ポインタを用いる
    Bullet* bullet;

    StageObject* StageObject;
};
