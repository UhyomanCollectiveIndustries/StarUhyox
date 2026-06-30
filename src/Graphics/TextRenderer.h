#pragma once

#include <string>
#include <unordered_map>

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

/** 文字の描画に必要な情報 */
struct Character
{
    GLuint textureID;   // OpenGLテクスチャ

    glm::ivec2 size;    // 文字サイズ

    glm::ivec2 bearing; // 左上からのオフセット

    GLuint advance;     // 次の文字までの距離
};

/** 文字の描画クラス */
class TextRenderer{
public:
    // コンストラクタ
    TextRenderer(
        const std::string& fontPath,
        unsigned int fontSize
    );

private:
    /** ASCIIロード */
    void LoadCharacters();

private:
    FT_Library ft;
    FT_Face face;

    std::unordered_map<char,Character> characters;
};