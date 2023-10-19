#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	class ImporterConnection;
	typedef std::shared_ptr<ImporterConnection> ImporterConnectionPtr;
	typedef std::weak_ptr<ImporterConnection> ImporterConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle window functions.
	/// </summary>
	class ImporterConnection
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
		/// Objects map
		/// </summary>
		std::unordered_map<long, Importer::ObjectPtr> objs;

		/// <summary>
		/// Global reference.
		/// </summary>
		static std::weak_ptr<ImporterConnection> current;
	public:
		ImporterConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static ImporterConnectionPtr Get();
		static void Set(ImporterConnectionPtr instance);
	private:
		static int Open(lua_State* L);
	};
}}}}