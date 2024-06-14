#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	class ObjectConnection;
	typedef std::shared_ptr<ObjectConnection> ObjectConnectionPtr;
	typedef std::weak_ptr<ObjectConnection> ObjectConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle window functions.
	/// </summary>
	class ObjectConnection
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
		static std::weak_ptr<ObjectConnection> current;
	public:
		ObjectConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static ObjectConnectionPtr Get();
		static void Set(ObjectConnectionPtr instance);

		static Importer::ObjectPtr FindObj(long id);
	private:
		static int Open(lua_State* L);
		static int Create(lua_State* L);
		static int Destroy(lua_State* L);
		static int Get(lua_State* L);

		static int GetMeshes(lua_State* L);
		static int GetMaterials(lua_State* L);
	};
}}}}