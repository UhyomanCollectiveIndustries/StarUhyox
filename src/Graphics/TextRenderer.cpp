#include "TextRenderer.h"
#include <iostream>

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

TextRenderer::TextRenderer(
    const std::string& fontPath,
    unsigned int fontSize)
{
    // FreeType初期化
    FT_Init_FreeType(&ft);

    // フォント読み込み
    FT_New_Face(
        ft,
        "assets/fonts/Orbitron-Black.ttf",
        0,
        &face
    );

    // フォントサイズ設定
    FT_Set_Pixel_Sizes(face,0,48);

    // ASCIIロード
    LoadCharacters();
}

void TextRenderer::LoadCharacters()
{
    // バイト境界を1に設定
    //  4byte境界だと4の倍数でないピクセルで文字が崩れることがあるため
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    // ASCII文字をすべて読み込む
    for(unsigned char c = 0; c<128; c++)
    {
        // FreeTypeで文字を1文字ずつ読み込みレンダリング
        if(FT_Load_Char(face,c,FT_LOAD_RENDER))
        {
            std::cout<< "Failed to load Glyph :"
                    << c << std::endl;
            
            continue;
        }

        // OpenGLテクスチャ作成
                GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // glyph->bitmap をOpenGLへ送る
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED, // FreeTypeは白黒画像であるため
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        // テクスチャ設定
        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_S,
            GL_CLAMP_TO_EDGE
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_T,
            GL_CLAMP_TO_EDGE
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            GL_LINEAR
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            GL_LINEAR
        );

        // Character構造体生成
        Character character =
        {
            texture,
            glm::ivec2(
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows
            ),
            glm::ivec2(
                face->glyph->bitmap_left,
                face->glyph->bitmap_top
            ),
            static_cast<GLuint>(
                face->glyph->advance.x
            )
        };

        // mapへ保存
        characters.insert(
            std::make_pair(c, character)
        );
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}