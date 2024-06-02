#include <BoxEngine.hpp>
#include "ScriptDebugger.hpp"

namespace BoxEngine {
namespace Editor {
	
	using namespace Modules;
	using namespace Engine;

	void ScriptDebugger::SetOpen(bool val)
	{
		this->open = val;
	}

	void ScriptDebugger::Update()
	{
		using GUI = Window::GUI;
		 
		if (this->open && !this->configured)
		{
			GUI::SetNextWindowPosition(Window::Window::GetSize() / 2.0f);
			GUI::SetNextWindowSize({ 600, 600 });

            this->configured = true;
		}

		if (open && GUI::BeginWindow("Script Debugger", &open, { Window::GUIWindowFlags::NoCollapse }))
		{
			auto project = Project::Project::GetCurrentProject();

			if (project != nullptr && project->GetState() == Project::ProjectState::Running)
			{
                auto go = project->GetGameObject(this->goId);

                if (go)
                {
                    GUI::Text("GameObject: " + go->GetName() + " (" + go->GetId() + ")");
                    for (auto script : go->GetScripts())
                    {
                        if (script->GetState() != Project::ScriptState::ToStart && script->GetState() != Project::ScriptState::Updating)
                            continue;

                        if (GUI::BeginTreeNode(this->guid + script->GetName(), script->GetName()))
                        {
                            auto L = project->GetLuaState();
                            lua_getglobal(L, script->GetName().c_str());
                            lua_getfield(L, -1, goId.c_str());

                            if (lua_istable(L, -1))
                                PrintTable(L, lua_gettop(L), script->GetName().c_str());

                            lua_pop(L, 2);
                            GUI::EndTreeNode();
                        }
                    }
                }
			}

			this->focused = GUI::IsCurrentWindowFocused();
			GUI::EndWindow();
		}
		else this->focused = false;
	}

    bool ScriptDebugger::IsFocused() const
    {
        return this->focused;
    }

    void ScriptDebugger::SetGo(std::string goId)
    {
        this->goId = goId;
    }

    void ScriptDebugger::PrintPrimitive(lua_State* L, int index)
    {
        using GUI = Window::GUI;
        int type = lua_type(L, index);

        switch (type) 
        {
            case LUA_TSTRING:
                GUI::Text(lua_tostring(L, index));
                break;
            case LUA_TBOOLEAN:
                GUI::Text(lua_toboolean(L, index) ? "true" : "false");
                break;
            case LUA_TNUMBER:
                GUI::Text(std::to_string(lua_tonumber(L, index)));
                break;
            default:
                GUI::Text(lua_typename(L, type));
                break;
        }
    }

    void ScriptDebugger::PrintTable(lua_State* L, int index, const std::string& key) 
    {
        using GUI = Window::GUI;

        lua_pushnil(L);
        while (lua_next(L, index) != 0) 
        {
            std::string item_key;

            if (lua_type(L, -2) == LUA_TSTRING)
                item_key = lua_tostring(L, -2);
            else 
                item_key = "[" + std::to_string(lua_tointeger(L, -2)) + "]";

            if (lua_istable(L, -1)) 
            {
                if (GUI::BeginTreeNode(this->guid + item_key, item_key + " (table)"))
                {
                    PrintTable(L, lua_gettop(L), item_key);
                    GUI::EndTreeNode();
                }
            }
            else 
            {
                GUI::Text(item_key + " = ");
                GUI::ContinueSameLine();
                PrintPrimitive(L, lua_gettop(L));
            }

            lua_pop(L, 1);
        }
    }
}}