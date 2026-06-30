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
        fontPath.c_str(),
        0,
        &face
    );

    // フォントサイズ設定
    FT_Set_Pixel_Sizes(face,0,fontSize);

    // ASCIIロード
    LoadCharacters();

    createBuffers();

    std::cout
    << "VAO = "
    << VAO
    << std::endl;

    std::cout
    << "VBO = "
    << VBO
    << std::endl;
}

TextRenderer::~TextRenderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
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

void TextRenderer::createBuffers()
{
    // VAO生成
    glGenVertexArrays(1,&VAO);

    // VBO生成
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    // 6頂点 × (x,y,u,v) = 24float 分だけ確保
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(float) * 6 * 4,
        nullptr,
        GL_DYNAMIC_DRAW
    );

    // layout(location = 0) in vec4 vertex;
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        0,                  // location
        4,                  // vec4
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(float),  // 1頂点 = float4
        (void*)0
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::drawText(
        const std::string& text,
        float x,
        float y,
        float scale,
        glm::vec3 color)
{
    // シェーダを指定
    glUseProgram(shaderProgram);

    // 色を指定
    GLuint textColorLoc =
        glGetUniformLocation(
            shaderProgram,
            "textColor"
        );

    glUniform3f(
        textColorLoc,
        color.r,
        color.g,
        color.b
    );

    // テクスチャユニット0を使用
    glActiveTexture(GL_TEXTURE0);

    // VAOをバインド
    glBindVertexArray(VAO);

    // 文字を1文字ずつ取り出す
    for(char c : text)
    {
        // charactersを取得
        Character ch = characters.at(c);

        // 描画位置の計算
        float xpos =
            x + ch.bearing.x * scale;

        float ypos =
            y -
            (ch.size.y - ch.bearing.y)
            * scale;

        float w =
            ch.size.x * scale;

        float h =
            ch.size.y * scale;

        // Quad生成
        float vertices[6][4] =
        {
            { xpos,     ypos + h, 0.0f, 0.0f },
            { xpos,     ypos,     0.0f, 1.0f },
            { xpos + w, ypos,     1.0f, 1.0f },

            { xpos,     ypos + h, 0.0f, 0.0f },
            { xpos + w, ypos,     1.0f, 1.0f },
            { xpos + w, ypos + h, 1.0f, 0.0f }
        };

        glActiveTexture(GL_TEXTURE0);

        // テクスチャのバインド
        glBindTexture(
            GL_TEXTURE_2D,
            ch.textureID
        );

        // VBO更新
        glBindBuffer(
            GL_ARRAY_BUFFER,
            VBO
        );

        glBufferSubData(
            GL_ARRAY_BUFFER,
            0,
            sizeof(vertices),
            vertices
        );

        glBindBuffer(
            GL_ARRAY_BUFFER,
            0
        );

        // 描画
        glDrawArrays(
            GL_TRIANGLES,
            0,
            6
        );

        // 次の文字位置へ移動
        x +=
            (ch.advance >> 6)
            * scale;
    }

    // 後始末
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D,0);
}

void TextRenderer::setShader(GLuint program)
{
    shaderProgram = program;
}