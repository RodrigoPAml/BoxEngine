#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {
namespace Connection {

	class FramebufferConnection;
	typedef std::shared_ptr<FramebufferConnection> FramebufferConnectionPtr;
	typedef std::weak_ptr<FramebufferConnection> FramebufferConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle Framebuffers functions.
	/// </summary>
	class FramebufferConnection
	{
	private:
		lua_State* state;

		/// <summary>
		/// The current visited go by the engine
		/// </summary>
		GameObjectWeakPtr currentGo;

		/// <summary>
		/// Id count
		/// </summary>
		long currentId = 0;

		/// <summary>
		/// Framebuffers map
		/// </summary>
		std::unordered_map<long, GPU::FramebufferPtr> framebuffers;

		/// <summary>
		/// Global reference.
		/// </summary>
		static std::weak_ptr<FramebufferConnection> current;
	public:
		FramebufferConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static FramebufferConnectionPtr Get();
		static void Set(FramebufferConnectionPtr instance);
	private:
		static int CreateFramebuffer(lua_State* L);
		static int DestroyFramebuffer(lua_State* L);

		static int SetCurrent(lua_State* L);
		static int GetCurrent(lua_State* L);

		static int Active(lua_State* L);
		static int GetAttachmentSize(lua_State* L);
		static int GetAttachment(lua_State* L);
		static int ActiveDefault(lua_State* L);

		static int Clear(lua_State* L);
		static int SetClearModes(lua_State* L);
		static int SwitchViewPort(lua_State* L);
	};
}}}