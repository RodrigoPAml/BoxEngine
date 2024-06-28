#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Font {

	struct Character
	{
		unsigned int textureID; // ID handle of the glyph texture
		glm::ivec2 size;      // Size of glyph
		glm::ivec2 bearing;   // Offset from baseline to left/top of glyph
		unsigned int advance;   // Horizontal offset to advance to next glyph
	};

	class Font;
	typedef std::shared_ptr<Font> FontPtr;

	/// <summary>
	/// Represents an instance of an font file
	/// Retrieved from https://learnopengl.com/In-Practice/Text-Rendering
	/// </summary>
	class Font
	{
	private:
		// Total Instances 
		static int TotalInstances;

		// Is initialized
		static bool IsInit;

		// Libeary
		static FT_Library lib;

		// Mesh for each character
		static unsigned int vao, vbo;

		// Common shader to draw 
		static GPU::ShaderPtr shader;

		// Character info
		std::map<GLchar, Character> characters;

		// Font state
		glm::vec2 position = { 0, 0 };
		glm::vec2 scale = { 1, 1 };
		glm::vec3 color = { 1, 0, 0 };
		std::string text = "";

		glm::vec2 calculatedTextSize = { 0, 0 };
		bool loaded = false;
	public:
		Font(std::string path, int width, int height);
		~Font();

		glm::vec2 GetPosition() const;
		void SetPosition(const glm::vec2& pos);

		glm::vec2 GetScale() const;
		void SetScale(const glm::vec2& scale);

		glm::vec3 GetColor() const;
		void SetColor(const glm::vec3& color);

		std::string GetText() const;
		void SetText(const std::string& text);

		glm::vec2 GetTextSize();

		void Draw();

		static void Release();
		static int GetInstaceCount();
	private:
		bool Load(std::string path, int width, int height);
		void AllocShader();
	};
}}}