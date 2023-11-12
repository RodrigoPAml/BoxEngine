#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace GPU {

	/// <summary>
	/// Represents a texture in GPU memory.
	/// </summary>
	class Texture
	{
	private:
		/// <summary>
		/// Texture identifier.
		/// </summary>
		unsigned int id;

		/// <summary>
		/// Texture Size
		/// </summary>
		glm::vec<2, unsigned int> size;

		/// <summary>
		/// The number of samples
		/// </summary>
		int samples = 0;

		/// <summary>
		/// Texture chosen internal format
		/// </summary>
		int internalType = GL_TEXTURE_2D;

		static int TotalInstances;
	public:
		Texture(const TextureDataConfiguration& configuration, Utils::ImagePtr texture);
		Texture(const TextureConfiguration& configuration);
		Texture(const MultisampleTextureConfiguration& configuration);

		~Texture();

		/// <summary>
		/// Return the texture id.
		/// </summary>
		unsigned int GetId() const;

		/// <summary>
		/// Activate texture in slot.
		/// </summary>
		void Use(const unsigned int slot) const;

		/// <summary>
		/// Internal type GL_TEXTURE_2D or GL_TEXTURE_2D_MULTISAMPLE
		/// </summary>
		int GetInternalType() const;

		/// <summary>
		/// If the texture is multi sampled
		/// </summary>
		/// <returns></returns>
		bool IsMultiSampled() const;

		/// <summary>
		/// If the texture is multi sampled this is the number of samples
		/// </summary>
		/// <returns></returns>
		int GetNumberOfSamples() const;

		/// <summary>
		/// Returnt texture size
		/// </summary>
		/// <returns></returns>
		glm::vec<2, unsigned int> GetSize() const;

		/// <summary>
		/// Disable texture in slot.
		/// </summary>
		/// <param name="slot"></param>
		static void DisableTextureUnit(const unsigned int slot);

		/// <summary>
		/// Get max slots for textures.
		/// </summary>
		static unsigned int GetMaxTextureUnits();

		/// <summary>
		/// Get current existing textures
		/// </summary>
		static int GetInstanceCount();
	};

	typedef std::shared_ptr<Texture> TexturePtr;
	typedef std::weak_ptr<Texture> TextureRef;
}}}
