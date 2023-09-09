#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {

	class ConnectionManager;
	typedef std::shared_ptr<ConnectionManager> ConnectionManagerPtr;
	typedef std::weak_ptr<ConnectionManager> ConnectionManagerWeakPtr;

	/// <summary>
	/// Connection Manager.
	/// </summary>
	class ConnectionManager
	{
	private:
		// Functions for scripts and gos
		Connection::GoScriptConnectionPtr goScript;
		// Functions for input
		Connection::InputConnectionPtr input;
		// Functions for logs
		Connection::LogConnectionPtr logs;
		// Functions for engine
		Connection::EngineConnectionPtr engine;
		// Functions for cam2d
		Connection::Camera2DConnectionPtr cam2d;
		// Functions for cam3d
		Connection::Camera3DConnectionPtr cam3d;
		// Functions for time
		Connection::TimeConnectionPtr time;
		// Functions for dir/files
		Connection::DirectoryConnectionPtr directory;
		// Functions for open images
		Connection::ImageConnectionPtr image;
		// Functions for command directly to opengl
		Connection::CommandConnectionPtr command;
		// Functions for shaders of opengl
		Connection::ShaderConnectionPtr shader;
		// Functions for textures of opengl
		Connection::TextureConnectionPtr texture;
		// Functions for vertex of opengl
		Connection::VertexConnectionPtr vertex;
		// Functions for framebuffer of opengl
		Connection::FramebufferConnectionPtr framebuffer;
		// Functions for drawing basics
		Connection::DrawingConnectionPtr drawing;
		// Functions for window
		Connection::WindowConnectionPtr window;
		// Functions for audio
		Connection::AudioConnectionPtr audio;
		// Functions for fonts
		Connection::FontConnectionPtr font;

		lua_State* state = nullptr;
	public:
		ConnectionManager(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);
		int GetStackSize();

		void CreateScriptData(GameObjectPtr go, ScriptPtr script);
		void UpdateScriptData(GameObjectPtr go, ScriptPtr script);
		void DeleteScriptData(GameObjectPtr go, ScriptPtr script);
	};
}}