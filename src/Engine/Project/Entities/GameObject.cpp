#include <BoxEngine.hpp>
#include "GameObject.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {

    int GameObject::Total = 0;

    GameObject::GameObject()
    {
        Total++;
        this->active = false;
        this->toDestroy = false;
    }

    GameObject::~GameObject()
    {
        Total--;
    }

    std::string GameObject::GetId() const
    {
        return this->id;
    }

    void GameObject::SetName(const std::string& name)
    {
        this->name = name;
    }

    std::string GameObject::GetName() const
    {
        return this->name;
    }

    void GameObject::SetActive(const bool active)
    {
        this->active = active;
    }

    bool GameObject::GetActive() const
    {
        return this->active;
    }

    void GameObject::SetFather(const GameObjectPtr& father)
    {
        this->father = father;
    }

    GameObjectPtr GameObject::GetFather() const
    {
        return this->father;
    }

    std::vector<GameObjectPtr>& GameObject::GetChildrens() 
    {
        return this->childrens;
    }

    bool GameObject::AddScript(ScriptPtr script)
    {
        if (std::find_if(this->scripts.begin(), this->scripts.end(), [script](ScriptPtr x) {return script->GetName() == x->GetName(); }) != this->scripts.end())
            return false;

        this->scripts.push_back(script);
        return true;
    }

    void GameObject::RemoveScript(ScriptPtr script)
    {
        this->scripts.erase(std::remove(this->scripts.begin(), this->scripts.end(), script), this->scripts.end());
    }

    std::vector<ScriptPtr>& GameObject::GetScripts()
    {
        return this->scripts;
    }

    void GameObject::ClearScripts()
    {
        this->scripts.clear();
    }

    bool GameObject::IsToDestroy() const
    {
        return this->toDestroy;
    }

    void GameObject::SetToDestroy()
    {
        this->toDestroy = true;
        this->toVisit = true;

        if (this->father != nullptr)
            this->father->SetToVisit(true);

        for (auto& item : this->GetChildrens())
            item->SetToDestroy();
    }

    bool GameObject::IsToVisit() const
    {
        return this->toVisit;
    }

    void GameObject::SetToVisit(bool value)
    {
        if (value == true && this->father != nullptr)
            this->father->SetToVisit(true);

        this->toVisit = value;
    }

    int GameObject::GetCurrentGosCount()
    {
        return Total;
    }
}}}
