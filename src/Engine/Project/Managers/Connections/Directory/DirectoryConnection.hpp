#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {
namespace Connection {

	class DirectoryConnection;
	typedef std::shared_ptr<DirectoryConnection> DirectoryConnectionPtr;
	typedef std::weak_ptr<DirectoryConnection> DirectoryConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle directory functions.
	/// </summary>
	class DirectoryConnection
	{
	private:
		lua_State* state;

		/// <summary>
		/// The current visited go by the engine
		/// </summary>
		GameObjectWeakPtr currentGo;

		/// <summary>
		/// Global reference.
		/// </summary>
		static std::weak_ptr<DirectoryConnection> current;
	public:
		DirectoryConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static DirectoryConnectionPtr Get();
		static void Set(DirectoryConnectionPtr instance);
	private:
		static int ReadFile(lua_State* L);

		static int CreateFile(lua_State* L);
		static int CreateFolder(lua_State* L);

		static int Move(lua_State* L);
		static int Copy(lua_State* L);
		static int Delete(lua_State* L);

		static int IsFile(lua_State* L);
		static int IsDir(lua_State* L);
		static int Exists(lua_State* L);

		static int GetCurrentPath(lua_State* L);
		static int GetBasePath(lua_State* L);
		static int GetAssetsPath(lua_State* L);
		static int GetLogsPath(lua_State* L);

		static int ListDirectories(lua_State* L);

		static int RemovePartsFromPath(lua_State* L);
		static int GetExtensionFromPath(lua_State* L);
		static int GetLastPartFromPath(lua_State* L);
		static int GetLastPartFromPathNoExt(lua_State* L);

		static int Exec(lua_State* L);
	};
}}}