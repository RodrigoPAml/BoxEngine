#pragma once

#define TOPBAR_Y 35

// GLM
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// GLAD
#include <glad/glad.h>

// GLFW3
#include <GLFW/glfw3.h>

// ImGui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

//ImPlot
#include <implot.h>

// Json
#include <json_nlohmann.hpp>

// Lua JIT
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

// C++ Headers
#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>
#include <functional>
#include <filesystem>
#include <exception>
#include <source_location>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <ostream>
#include <mutex>
#include <fstream>
#include <memory>
#include <queue>
#include <any>
#include <set>
#include <map>

// Canvas Engine
#include <Engine/Data/UtilsData.hpp>
#include <Engine/Utils/Time.hpp>

#include <Engine/Data/DebugEnums.hpp>
#include <Engine/Data/DebugData.hpp>
#include <Engine/Data/DebugCallbacks.hpp>
#include <Engine/Data/DebugUtils.hpp>

#include <Engine/Debug/Logging.hpp>
#include <Engine/Debug/Debugging.hpp>

#include <Engine/Data/GPUEnums.hpp>
#include <Engine/Data/GPUData.hpp>
#include <Engine/Data/GPUUtils.hpp>

#include <Engine/Utils/Image.hpp>
#include <Engine/Utils/Directory.hpp>

#include <Engine/GPU/Texture.hpp>
#include <Engine/GPU/Shader.hpp>

#include <Engine/Data/FramebufferData.hpp>
#include <Engine/Data/FramebufferUtils.hpp>

#include <Engine/GPU/Framebuffer.hpp>
#include <Engine/GPU/Vertex.hpp>
#include <Engine/GPU/Command.hpp>

#include <Engine/Data/WindowEnums.hpp>
#include <Engine/Data/WindowData.hpp>
#include <Engine/Data/WindowCallbacks.hpp>

#include <Engine/Window/GUI.hpp>
#include <Engine/Window/Window.hpp>

#include <Engine/Data/InputEnums.hpp>
#include <Engine/Data/InputUtils.hpp>
#include <Engine/Data/InputCallbacks.hpp>

#include <Engine/Input/Mouse.hpp>
#include <Engine/Input/Keyboard.hpp>

#include <Engine/Data/CameraEnums.hpp>
#include <Engine/Data/CameraData.hpp>
#include <Engine/Data/CameraUtils.hpp>

#include <Engine/Camera/Camera2D.hpp>
#include <Engine/Camera/Camera3D.hpp>

#include <Engine/Utils/Generator.hpp>

#include <Engine/Drawing/TextureRenderer.hpp>
#include <Engine/Drawing/Primitives2D.hpp>
#include <Engine/Drawing/Primitives3D.hpp>

#include <Engine/Data/ProjectEnums.hpp>
#include <Engine/Data/ProjectUtils.hpp>

#include <Engine/Project/Entities/ScriptData.hpp>
#include <Engine/Project/Entities/Script.hpp>
#include <Engine/Data/ProjectCallbacks.hpp>
#include <Engine/Project/Entities/GameObject.hpp>
#include <Engine/Serialization/Serialization.hpp>
#include <Engine/Project/Entities/GoExecution.hpp>
#include <Engine/Project/Entities/GoMovement.hpp>
#include <Engine/Data/ProjectData.hpp>

#include <Engine/Utils/Lua.hpp>

#include <Engine/Project/Managers/Connections/Window/WindowConnection.hpp>
#include <Engine/Project/Managers/Connections/Drawing/DrawingConnection.hpp>
#include <Engine/Project/Managers/Connections/Framebuffer/FramebufferConnection.hpp>
#include <Engine/Project/Managers/Connections/Vertex/VertexConnection.hpp>
#include <Engine/Project/Managers/Connections/Texture/TextureConnection.hpp>
#include <Engine/Project/Managers/Connections/Shader/ShaderConnection.hpp>
#include <Engine/Project/Managers/Connections/Command/CommandConnection.hpp>
#include <Engine/Project/Managers/Connections/Image/ImageConnection.hpp>
#include <Engine/Project/Managers/Connections/Directory/DirectoryConnection.hpp>
#include <Engine/Project/Managers/Connections/Time/TimeConnection.hpp>
#include <Engine/Project/Managers/Connections/Camera/Camera3DConnection.hpp>
#include <Engine/Project/Managers/Connections/Camera/Camera2DConnection.hpp>
#include <Engine/Project/Managers/Connections/Input/InputConnection.hpp>
#include <Engine/Project/Managers/Connections/Log/LogConnection.hpp>
#include <Engine/Project/Managers/Connections/Utils/UtilsConnection.hpp>
#include <Engine/Project/Managers/Connections/Scene/GoScriptConnection.hpp>

#include <Engine/Project/Managers/ConnectionManager.hpp>
#include <Engine/Project/Managers/ScriptManager.hpp>
#include <Engine/Project/Managers/GoManager.hpp>
#include <Engine/Project/Project.hpp>

// Editor
#include <Editor/Data/EditorData.hpp>

#include <Editor/Interfaces/Layout.hpp>
#include <Editor/Layouts/BottomWindow/InfoTab.hpp>
#include <Editor/Layouts/BottomWindow/LogTab.hpp>
#include <Editor/Layouts/BottomWindow/FilesTab.hpp>
#include <Editor/Layouts/BottomWindow/BottomWindow.hpp>

#include <Editor/Layouts/Inspector/Inspector.hpp>
#include <Editor/Layouts/GameTree/GameTree.hpp>

#include <Editor/Layouts/TopBar/TopBar.hpp>

#include <Editor/Editor.hpp>
#include <Editor/ProjectManager/ProjectManager.hpp>
