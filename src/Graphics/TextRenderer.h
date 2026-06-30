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
    /** コンストラクタ */
    TextRenderer(
        const std::string& fontPath,
        unsigned int fontSize
    );

    /** デストラクタ */
    ~TextRenderer();

    void createBuffers();

    /** シェーダの適用 */
    void setShader(GLuint program);

    /** 文字の描画 */
    void drawText(
        const std::string& text,    // 表示するテキスト
        float x,                    // 表示するx座標
        float y,                    // 表示するy座標
        float scale,                // 表示するテキストのスケール
        glm::vec3 color             // 表示するテキストの色
    );

private:
    /** ASCIIロード */
    void LoadCharacters();

private:
    FT_Library ft;
    FT_Face face;

    std::unordered_map<char,Character> characters;

    GLuint VAO = 0;
    GLuint VBO = 0;

    GLuint shaderProgram = 0;
};
