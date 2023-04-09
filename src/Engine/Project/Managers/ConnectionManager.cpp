#include <BoxEngine.hpp>
#include "ConnectionManager.hpp"

namespace BoxEngine {
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

		this->utils = UtilsConnectionPtr(new UtilsConnection(state));
		UtilsConnection::Set(this->utils);

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

		this->state = state;
	}

	void ConnectionManager::Bind()
	{
		this->goScript->Bind();
		this->input->Bind();
		this->utils->Bind();
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
	}

	void ConnectionManager::SetCurrentGo(GameObjectPtr go)
	{
		this->goScript->SetCurrentGo(go);
		this->logs->SetCurrentGo(go);
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
				Utils::Lua::RegTable(this->state, item.GetName().c_str(), item.GetValue() == "1");
			else if (item.GetType() == ScriptDataType::string)
				Utils::Lua::RegTable(this->state, item.GetName().c_str(), item.GetValue());
			else if (item.GetType() == ScriptDataType::number)
				Utils::Lua::RegTable(this->state, item.GetName().c_str(), atof(item.GetValue().c_str()));
		}

		lua_pop(this->state, 3);
	}

	void ConnectionManager::UpdateScriptData(GameObjectPtr go, ScriptPtr script)
	{
		std::vector<ScriptData> toRemove;
		for (auto& item : script->GetScriptData())
		{
			lua_getglobal(this->state, script->GetName().c_str());
			lua_getfield(this->state, -1, go->GetId().c_str());

			if (item.IsModified())
			{
				item.SetModified(false);

				if (item.GetType() == ScriptDataType::boolean)
					Utils::Lua::RegTable(this->state, item.GetName().c_str(), false);
				else if (item.GetType() == ScriptDataType::string)
					Utils::Lua::RegTable(this->state, item.GetName().c_str(), item.GetValue());
				else if (item.GetType() == ScriptDataType::number)
					Utils::Lua::RegTable(this->state, item.GetName().c_str(), atof(item.GetValue().c_str()));

				lua_pop(this->state, 2);
				continue;
			}

			lua_getfield(this->state, -1, item.GetName().c_str());

			if (lua_isboolean(this->state, -1))
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
			else 
				toRemove.push_back(item);
			
			lua_pop(this->state, 3);
		}
	}
	
	void ConnectionManager::DeleteScriptData(GameObjectPtr go, ScriptPtr script)
	{
	}
}}
