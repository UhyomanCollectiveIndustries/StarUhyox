#include "SoundSystem.h"

#include <iostream>

#include "../../libs/soloud/include/soloud.h"
#include "../../libs/soloud/include/soloud_wav.h"

//コンストラクタ
SoundSystem::SoundSystem()
{
    //SoLoudのインスタンスを生成
    m_soLoud = new SoLoud::Soloud();
    //SoLoudの初期化
    m_soLoud->init();
}

//デストラクタ
SoundSystem::~SoundSystem()
{
    //ロードした音声データのメモリを解放
    for(auto& pair : m_soundMap){
        delete pair.second;
    }
    m_soundMap.clear();

    //音声エンジン(SoLoud)の終了処理と解放
    if(m_soLoud)
    {
        m_soLoud->deinit();
        delete m_soLoud;
        m_soLoud = nullptr;
    }
}

//音声ファイルを事前にロード
bool SoundSystem::LoadSound(
    const std::string& key,
    const std::string& filePath
)
{
    //すでに同じキーが存在する場合はスキップ
    if(m_soundMap.find(key) != m_soundMap.end())
    {
        return true;
    }

    //新しい音声バッファを作成してファイルを開く
    SoLoud::Wav* wav = new SoLoud::Wav();
    SoLoud::result result = wav->load(filePath.c_str());

    if(result != SoLoud::SO_NO_ERROR)
    {
        std::cerr << "Failed to load sound: " << filePath << std::endl;
        delete wav;
        return false;
    }

    //マップに保存
    m_soundMap[key] = wav;
    return true;
}

//音声の再生
void SoundSystem::Play(const std::string& key)
{
    auto it = m_soundMap.find(key);
    if(it == m_soundMap.end())
    {
        std::cerr << "[SoundSystem] 再生エラー: '" << key << "' はロードされていません。" << std::endl;
        return;
    }

    //音声の再生
    m_soLoud -> play(*(it->second));
}


//衝突
void SoundSystem::OnCollision(
    const CollisionEvent& e
)
{
    //デモ:ウィンドウにBOOMと出力
    std::cout << "BOOM!" << std::endl;

    Play("boom");
}