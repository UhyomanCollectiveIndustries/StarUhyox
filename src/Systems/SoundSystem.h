#pragma once

#include "../Core/CollisionEvent.h"

#include <string>
#include <unordered_map>

//SoLoudの前方宣言
//  ヘッダーを軽くするため
namespace SoLoud
{
    class Soloud;
    class Wav;
}

class SoundSystem
{
public:
    //コンストラクタ
    SoundSystem();
    //デストラクタ
    ~SoundSystem();

    //音声ファイルを事前にロード
    //@param key        ゲーム内で呼び出す際の名前
    //@param filePath   音声ファイルへのパス
    bool LoadSound(
        const std::string& key,
        const std::string& filePath
    );

    //音声の再生
    //@param key        ゲーム内で呼び出す際の名前
    void Play(
        const std::string& key
    );

    //衝突
    // 衝突イベントを検知したときに発火
    // @param e 衝突イベント
    void OnCollision(
        const CollisionEvent& e
    );

    
private:
    //SoLoudのインスタンス
    SoLoud::Soloud* m_soLound = nullptr;

    //ロードした音声データ(wav)を管理するマップ
    std::unordered_map<std::string,SoLoud::Wav*>m_soundMap;

};