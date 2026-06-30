#pragma once

/**
 * ゲームステートクラス
 * ゲームの状態を定義します
 */
enum class GameState
{
    Title,      // タイトルシーン
    Playing,    // ゲームシーン
    GameOver    // ゲームオーバーシーン
};