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

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

// Lua JIT
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

// IrrKlang sound
#include <irrKlang.h>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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

// Engine modules
#include <Modules/Data/UtilsData.hpp>
#include <Modules/Utils/Time.hpp>

#include <Modules/Data/DebugEnums.hpp>
#include <Modules/Data/DebugData.hpp>
#include <Modules/Data/DebugCallbacks.hpp>
#include <Modules/Data/DebugUtils.hpp>

#include <Modules/Debug/Logging.hpp>
#include <Modules/Debug/Debugging.hpp>

#include <Modules/Data/GPUEnums.hpp>
#include <Modules/Data/GPUData.hpp>
#include <Modules/Data/GPUUtils.hpp>

#include <Modules/Utils/Image.hpp>
#include <Modules/Utils/Directory.hpp>

#include <Modules/GPU/Texture.hpp>
#include <Modules/GPU/Shader.hpp>

#include <Modules/Data/FramebufferData.hpp>
#include <Modules/Data/FramebufferUtils.hpp>

#include <Modules/GPU/Framebuffer.hpp>
#include <Modules/GPU/Vertex.hpp>
#include <Modules/GPU/Command.hpp>

#include <Modules/Data/WindowEnums.hpp>
#include <Modules/Data/WindowData.hpp>
#include <Modules/Data/WindowCallbacks.hpp>

#include <Modules/Window/GUI.hpp>
#include <Modules/Window/Window.hpp>

#include <Modules/Data/InputEnums.hpp>
#include <Modules/Data/InputUtils.hpp>
#include <Modules/Data/InputCallbacks.hpp>

#include <Modules/Input/Mouse.hpp>
#include <Modules/Input/Keyboard.hpp>

#include <Modules/Data/CameraEnums.hpp>
#include <Modules/Data/CameraData.hpp>
#include <Modules/Data/CameraUtils.hpp>

#include <Modules/Camera/Camera2D.hpp>
#include <Modules/Camera/Camera3D.hpp>

#include <Modules/Utils/Generator.hpp>

#include <Modules/Drawing/TextureRenderer.hpp>
#include <Modules/Drawing/Primitives2D.hpp>
#include <Modules/Drawing/Primitives3D.hpp>

#include <Modules/Audio/Audio.hpp>
#include <Modules/Font/Font.hpp>

#include <Modules/Importer/Material.hpp>
#include <Modules/Importer/Mesh.hpp>
#include <Modules/Importer/Object.hpp>
#include <Modules/Importer/Importer.hpp>

// Engine main files
#include <Engine/Data/ProjectEnums.hpp>
#include <Engine/Data/ProjectUtils.hpp>

#include <Engine/Project/Entities/ScriptData.hpp>
#include <Engine/Project/Entities/Script.hpp>
#include <Engine/Data/ProjectCallbacks.hpp>
#include <Engine/Project/Entities/GameObject.hpp>
#include <Engine/Serialization/Serialization.hpp>
#include <Engine/Project/Entities/GoExecution.hpp>
#include <Engine/Data/ProjectData.hpp>

#include <Engine/LuaUtils/Lua.hpp>

#include <Engine/Project/Connections/Window/WindowConnection.hpp>
#include <Engine/Project/Connections/Drawing/DrawingConnection.hpp>
#include <Engine/Project/Connections/Framebuffer/FramebufferConnection.hpp>
#include <Engine/Project/Connections/Vertex/VertexConnection.hpp>
#include <Engine/Project/Connections/Texture/TextureConnection.hpp>
#include <Engine/Project/Connections/Shader/ShaderConnection.hpp>
#include <Engine/Project/Connections/Command/CommandConnection.hpp>
#include <Engine/Project/Connections/Image/ImageConnection.hpp>
#include <Engine/Project/Connections/Directory/DirectoryConnection.hpp>
#include <Engine/Project/Connections/Time/TimeConnection.hpp>
#include <Engine/Project/Connections/Camera/Camera3DConnection.hpp>
#include <Engine/Project/Connections/Camera/Camera2DConnection.hpp>
#include <Engine/Project/Connections/Input/InputConnection.hpp>
#include <Engine/Project/Connections/Log/LogConnection.hpp>
#include <Engine/Project/Connections/Engine/EngineConnection.hpp>
#include <Engine/Project/Connections/Scene/GoScriptConnection.hpp>
#include <Engine/Project/Connections/Audio/AudioConnection.hpp>
#include <Engine/Project/Connections/Font/FontConnection.hpp>
#include <Engine/Project/Connections/Math/MathConnection.hpp>
#include <Engine/Project/Connections/Importer/ImporterConnection.hpp>

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
