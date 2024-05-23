#include <BoxEngine.hpp>
#include "Font.hpp"

namespace BoxEngine {
namespace Modules {
namespace Font {

	int Font::TotalInstances = 0;
	bool Font::IsInit = false;
	FT_Library Font::lib;
    unsigned int Font::vao = 0;
    unsigned int Font::vbo = 0;
    GPU::ShaderPtr Font::shader = nullptr;

	Font::Font(std::string path, int width, int height)
	{
		TotalInstances++;

        if (!IsInit)
        {
            if (FT_Init_FreeType(&lib) == 0)
            {
                IsInit = true;
                AllocShader();
            }
            else
                Debug::Logging::LogException("[Font]: Failed to initialize font module", Debug::LogOrigin::Engine);
        }

        if (IsInit)
            this->loaded = this->Load(path, width, height);
	}

	Font::~Font()
	{
		TotalInstances--;

        if (!this->loaded)
            return;

        for (auto c = this->characters.begin(); c != this->characters.end(); c++)
        {
            Character ch = c->second;
            glDeleteTextures(1, &ch.textureID);
        }

        Debug::Logging::Log("[Font]: Font destroyed", Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);
	}

    glm::vec2 Font::GetPosition() const
    {
        return this->GetPosition();
    }

    void Font::SetPosition(const glm::vec2& pos)
    {
        this->position = pos;
    }

    glm::vec2 Font::GetScale() const
    {
        return this->scale;
    }

    void Font::SetScale(const glm::vec2& scale)
    {
        this->scale = scale;
    }

    glm::vec3 Font::GetColor() const
    {
        return this->color;
    }

    void Font::SetColor(const glm::vec3& color)
    {
        this->color = color;
    }

    std::string Font::GetText() const
    {
        return this->text;
    }

    void Font::SetText(const std::string& text)
    {
        this->text = text;
    }

    glm::vec2 Font::GetTextSize() const
    {
        return this->calculatedTextSize;
    }

    void Font::Draw()
    {
        if (!IsInit || !this->loaded)
            return;

        Camera::Camera2DPtr current = Camera::Camera2D::GetCurrentCamera();

        if (current == nullptr)
            return;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        shader->Use();
        shader->SetVec3("textColor", this->color);
        shader->SetMat4("projection", current->GetOrthoMatrix());

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(vao);

        std::string::const_iterator c;
        glm::vec2 original = this->position;

        this->calculatedTextSize = { 0, 0 };
        for (c = text.begin(); c != text.end(); c++)
        {
            Character ch = this->characters[*c];

            float xpos = this->position.x + ch.bearing.x * this->scale.x;
            float ypos = position.y - (ch.size.y - ch.bearing.y) * this->scale.y;

            float w = ch.size.x * this->scale.x;
            float h = ch.size.y * this->scale.y;
            
            this->calculatedTextSize.y = std::max(ch.bearing.y * this->scale.y, this->calculatedTextSize.y);

            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };
        
            glBindTexture(GL_TEXTURE_2D, ch.textureID);
            shader->SetInt("text", 0);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            this->position.x += (ch.advance >> 6) * this->scale.x;
        }

        this->calculatedTextSize.x = this->position.x - original.x;
        this->position = original;
        
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Font::Release()
    {
        FT_Done_FreeType(lib);

        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
    }

    int Font::GetInstaceCount()
    {
        return TotalInstances;
    }

    bool Font::Load(std::string path, int width, int height)
    {
        FT_Face face;

       glPixelStorei(GL_PACK_ALIGNMENT, 1);
       glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        if (FT_New_Face(lib, path.c_str(), 0, &face))
        {
            Debug::Logging::LogException("[Font]: Failed to create font from " + path, Debug::LogOrigin::Engine);
            return false;
        }
        else
        {
            FT_Set_Pixel_Sizes(face, width, height);

            for (unsigned char c = 0; c < 128; c++)
            {
                auto glyph_index = FT_Get_Char_Index(face, c);
                
                if (FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT))
                    continue;

                if (FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL))
                    continue;

                unsigned int texture;

                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                Character character = {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<unsigned int>(face->glyph->advance.x)
                };

                this->characters.insert(std::pair<char, Character>(c, character));
            }
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        FT_Done_Face(face);

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        Debug::Logging::Log("[Font]: Font created from " + path, Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);

        return true;
    }

    void Font::AllocShader()
    {
        std::string vertShader = "#version 330 core\n"
            "layout(location = 0) in vec4 vertex\n;"
            "out vec2 TexCoords;\n"

            "uniform mat4 projection;\n"

            "void main()\n"
            "{\n"
            "   gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
            "   TexCoords = vertex.zw;\n"
            "};\n";

        std::string fragShader = "#version 330 core\n"
            "in vec2 TexCoords;\n"
            "out vec4 color;\n"

            "uniform sampler2D text;\n"
            "uniform vec3 textColor;\n"

            "void main()\n"
            "{\n"
            "   vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n"
            "   color = vec4(textColor, 1.0) * sampled;\n"
            "}";

        this->shader = GPU::ShaderPtr(new GPU::Shader(vertShader, fragShader, ""));
    }
}}}