#include <BoxEngine.hpp>
#include "ConnectionManager.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {
	
	ConnectionManager::ConnectionManager(lua_State* state)
	{
		using namespace Connection;

		this->goScript = GoScriptConnectionPtr(new GoScriptConnection(state));
		GoScriptConnection::Set(this->goScript);

		this->input = InputConnectionPtr(new InputConnection(state));
		InputConnection::Set(this->input);

		this->logs = LogConnectionPtr(new LogConnection(state));
		LogConnection::Set(this->logs);

		this->engine = EngineConnectionPtr(new EngineConnection(state));
		EngineConnection::Set(this->engine);

		this->cam2d = Camera2DConnectionPtr(new Camera2DConnection(state));
		Camera2DConnection::Set(this->cam2d);
	
		this->cam3d = Camera3DConnectionPtr(new Camera3DConnection(state));
		Camera3DConnection::Set(this->cam3d);

		this->directory = DirectoryConnectionPtr(new DirectoryConnection(state));
		DirectoryConnection::Set(this->directory);

		this->time = TimeConnectionPtr(new TimeConnection(state));
		TimeConnection::Set(this->time);

		this->image = ImageConnectionPtr(new ImageConnection(state));
		ImageConnection::Set(this->image);

		this->command = CommandConnectionPtr(new CommandConnection(state));
		CommandConnection::Set(this->command);

		this->shader = ShaderConnectionPtr(new ShaderConnection(state));
		ShaderConnection::Set(this->shader);

		this->texture = TextureConnectionPtr(new TextureConnection(state));
		TextureConnection::Set(this->texture);

		this->vertex = VertexConnectionPtr(new VertexConnection(state));
		VertexConnection::Set(this->vertex);

		this->framebuffer = FramebufferConnectionPtr(new FramebufferConnection(state));
		FramebufferConnection::Set(this->framebuffer);

		this->drawing = DrawingConnectionPtr(new DrawingConnection(state));
		DrawingConnection::Set(this->drawing);

		this->window = WindowConnectionPtr(new WindowConnection(state));
		WindowConnection::Set(this->window);

		this->audio = AudioConnectionPtr(new AudioConnection(state));
		AudioConnection::Set(this->audio);

		this->font = FontConnectionPtr(new FontConnection(state));
		FontConnection::Set(this->font);

		this->math = MathConnectionPtr(new MathConnection(state));
		MathConnection::Set(this->math);

		this->object = ObjectConnectionPtr(new ObjectConnection(state));
		ObjectConnection::Set(this->object);

		this->render = RendererConnectionPtr(new RendererConnection(state));
		RendererConnection::Set(this->render);

		auto engineContent = Utils::Directory::ReadFile(Utils::Directory::GetResourcePath() + "/scripts/engine.lua");
		luaL_dostring(state, engineContent.c_str());

		this->state = state;
	}

	void ConnectionManager::Bind()
	{
		this->goScript->Bind();
		this->input->Bind();
		this->engine->Bind();
		this->logs->Bind();
		this->cam2d->Bind();
		this->cam3d->Bind();
		this->directory->Bind();
		this->time->Bind();
		this->image->Bind();
		this->command->Bind();
		this->shader->Bind();
		this->texture->Bind();
		this->vertex->Bind();
		this->framebuffer->Bind();
		this->drawing->Bind();
		this->window->Bind();
		this->audio->Bind();
		this->font->Bind();
		this->math->Bind();
		this->object->Bind();
		this->render->Bind();
	}

	void ConnectionManager::SetCurrentGo(GameObjectPtr go)
	{
		this->goScript->SetCurrentGo(go);
		this->logs->SetCurrentGo(go);
	}

	void ConnectionManager::SetCurrentScript(ScriptPtr script)
	{
		this->goScript->SetCurrentScript(script);
	}

	int ConnectionManager::GetStackSize()
	{
		if (this->state == nullptr)
			return 0;

		return lua_gettop(this->state);
	}
	
	void ConnectionManager::CreateScriptData(GameObjectPtr go, ScriptPtr script)
	{
		lua_getglobal(this->state, script->GetName().c_str());

		lua_pushstring(this->state, go->GetId().c_str());
		lua_newtable(this->state);
		lua_settable(this->state, -3);

		lua_getglobal(this->state, script->GetName().c_str());
		lua_getfield(this->state, -1, go->GetId().c_str());

		for (auto item : script->GetScriptData())
		{
			if (item.GetType() == ScriptDataType::boolean)
				LuaUtils::RegTable(this->state, item.GetName().c_str(), item.GetValue() == "1");
			else if (item.GetType() == ScriptDataType::button)
				LuaUtils::RegTable(this->state, item.GetName().c_str(), false);
			else if (item.GetType() == ScriptDataType::string)
				LuaUtils::RegTable(this->state, item.GetName().c_str(), item.GetValue());
			else if (item.GetType() == ScriptDataType::number)
				LuaUtils::RegTable(this->state, item.GetName().c_str(), atof(item.GetValue().c_str()));
		}

		lua_pop(this->state, 3);
	}

	// This function should be moved to editor in the future, because is editor resposability to do that
	void ConnectionManager::UpdateScriptData(GameObjectPtr go, ScriptPtr script)
	{
		if (!script->IsLoaded())
			return;

		auto& datas = script->GetScriptData();

		// Find new variable to show in inspector
		lua_getglobal(this->state, script->GetName().c_str());
		lua_getfield(this->state, -1, go->GetId().c_str());
		lua_pushnil(this->state);

		if (lua_istable(this->state, -2))
		{
			while (lua_next(this->state, -2) != 0)
			{
				std::string key = "";

				if (lua_type(this->state, -2) == LUA_TSTRING)
				{
					key = lua_tostring(this->state, -2);

					if (std::find_if(datas.begin(), datas.end(), [key](ScriptData& item) {return item.GetName() == key; }) == datas.end())
					{
						if (lua_type(this->state, -1) == LUA_TNUMBER)
						{
							ScriptData data = ScriptData(key, std::to_string(lua_tonumber(this->state, -1)), ScriptDataType::number);

							if (script->HaveDataNotPersisted(data.GetName()))
								data.SetPersist(false);

							if (script->HaveDataNotShowed(data.GetName()))
								data.SetShowEditor(false);

							datas.push_back(data);
						}
						else if (lua_type(this->state, -1) == LUA_TSTRING)
						{
							ScriptData data = ScriptData(key, lua_tostring(this->state, -1), ScriptDataType::number);

							if (script->HaveDataNotPersisted(data.GetName()))
								data.SetPersist(false);

							if (script->HaveDataNotShowed(data.GetName()))
								data.SetShowEditor(false);

							datas.push_back(data);
						}
						else if (lua_type(this->state, -1) == LUA_TBOOLEAN)
						{
							ScriptData data = ScriptData(key, lua_toboolean(this->state, -1) == true ? "1" : "0", ScriptDataType::boolean);

							if (script->HaveDataNotPersisted(data.GetName()))
								data.SetPersist(false);

							if (script->HaveDataNotShowed(data.GetName()))
								data.SetShowEditor(false);

							datas.push_back(data);
						}
					}
				}

				lua_pop(this->state, 1);
			}
			lua_pop(this->state, 1);
		}
		lua_pop(this->state, 1);

		// Iterate all variables, if modified set value
		// Then verify its type if still can be tracked
		std::vector<ScriptData> toRemove;
		for (auto& item : datas)
		{
			lua_getglobal(this->state, script->GetName().c_str());
			lua_getfield(this->state, -1, go->GetId().c_str());

			if (item.IsModified())
			{
				item.SetModified(false);

				if (item.GetType() == ScriptDataType::button)
					LuaUtils::RegTable(this->state, item.GetName().c_str(), item.GetValue() == "1");
				else if (item.GetType() == ScriptDataType::boolean)
					LuaUtils::RegTable(this->state, item.GetName().c_str(), item.GetValue() == "1");
				else if (item.GetType() == ScriptDataType::string)
					LuaUtils::RegTable(this->state, item.GetName().c_str(), item.GetValue());
				else if (item.GetType() == ScriptDataType::number)
					LuaUtils::RegTable(this->state, item.GetName().c_str(), atof(item.GetValue().c_str()));

				lua_pop(this->state, 2);
				continue;
			}

			lua_getfield(this->state, -1, item.GetName().c_str());

			if (lua_isboolean(this->state, -1) && item.GetType() != ScriptDataType::button)
			{
				bool boolean = lua_toboolean(this->state, -1);

				item.SetValue(boolean == true ? "1" : "0");
				item.SetType(ScriptDataType::boolean);
			}
			else if (lua_type(this->state, -1) == LUA_TNUMBER)
			{
				double number = lua_tonumber(this->state, -1);

				item.SetValue(std::to_string(number));
				item.SetType(ScriptDataType::number);
			}
			else if (lua_type(this->state, -1) == LUA_TSTRING)
			{
				std::string str = lua_tostring(this->state, -1);

				item.SetValue(str);
				item.SetType(ScriptDataType::string);
			}
			else if(item.GetType() != ScriptDataType::button)
				toRemove.push_back(item);
			
			lua_pop(this->state, 3);
		}

		for (ScriptData data : toRemove)
			datas.erase(std::remove_if(datas.begin(), datas.end(), [&data](ScriptData item) {return data.GetName() == item.GetName(); }), datas.end());
	}
	
	void ConnectionManager::DeleteScriptData(GameObjectPtr go, ScriptPtr script)
	{
		lua_getglobal(this->state, script->GetName().c_str());
		LuaUtils::RegTable(this->state, go->GetId().c_str());
	}
	
	std::unordered_map<long, Modules::GPU::TexturePtr> ConnectionManager::GetTextures()
	{
		return this->texture->GetTextures();
	}
}}}
