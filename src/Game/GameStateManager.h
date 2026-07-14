#pragma once

#include "GameState.h"

/** 
 * ゲームステート管理クラス
 */
class GameStateManager
{
public:
    /**
     * 現在のステートを保持
     * 初期値はTitle
     */
    GameState currentState = GameState::Title;

public:
    /**
     * ステートの変更
     * @param ステート名
     */
    void changeState(GameState state);

    /** ステートのゲッター */
    GameState GetState() const;
};