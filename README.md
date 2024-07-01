# BoxEngine

BoxEngine is an engine designed to build both 2D and 3D general applications, such as games, using the Lua scripting language. This engine is ideal for creating applications quickly, thanks to its abstract layers implemented with OpenGL, which facilitate fast prototyping.

## Key Features:
- **GameObject Architecture**: Construct your scene using a GameObject architecture, where scripts are attached to objects to define their behavior.
- **C++ Core**: The engine is built in C++ for performance, with Lua as the scripting language, featuring a Just-In-Time (JIT) compiler.
- **Dual Mode Operation**: Projects can be run in two modes:
  - **Production Mode**: Execute the project by passing the folder as an argument.
  - **Editor Mode**: Utilize a built-in editor for project development.

# Features

## Scripting features

Read the scripting api documentation [here](https://github.com/RodrigoPAml/BoxEngine/blob/main/docs/api.md)

* Input module (keyboard and mouse)
* Audio module (2d and 3d audios)
* Font module (with support for any .ttf)
* Camera module (support for 2d and 3d camera manipulations)
* Debug/logging module (logging support also in scripting)
* Texture module (allows to manipulate texture with the GPU)
* Shader module (allows to create and use shader with the GPU)
* Vertex module (allows to allocate mesh with the GPU)
* Framebuffer module (manipulate framebuffer via GPU)
* Primitives module (allows to draw basic shapes in 2d and 3d, including to draw textures)
* Scene module (allows to instantiate GO and scripts and manipulate the game scene)
* Import module (allows to import 3d object files, currently have a basic version)
* Renderer module (allows to draw 3d models, currently have a basic version)
* GUI module (to do, basically por ImGui inside framebuffer)
* Physics module (to do)

## Editor features

* Open and create projects
* Play and Editor mode which can be detected via script/GO to manipulate the scene
* Manipulate game scene via Game Tree (create GO, duplicate, delete)
* Logs tab to help debug the editor and the application
* Files tab to help manipulate project files (game assets)
* Info tab to see engine internal information (instance of mesh, textures, fps, frametime)
* Inspector to allow manipulate a game object, add scripts and modify project settings 
* Integration with VS Code for scripting (recommend using Lua server extension)
* Script debugging and much more

## Script example

Basic script behaviour when attached to game object

```lua
function teste.start()
    local this = engine.current()
   
    engine.log('starting')
    engine.log('My GO id is' .. engine.go.current())
    engine.log('My script name is' .. engine.script.current())

    this.var = 'abc'
end

function teste.update()
   engine.log('updating')
end

function teste.destroy()
    engine.log('destroyed')
end
```

# Libraries used

* GLFW https://www.glfw.org/ (Window manipulation)
* GLAD https://glad.dav1d.de/ (OpenGL initialization)
* FreeType https://freetype.org/ (Font lib)
* ImGui https://github.com/ocornut/imgui (GUI lib)
* ImPlot https://github.com/epezent/implot (GUI Plots)
* Irrklang https://www.ambiera.com/irrklang/ (Audio lib)
* Assimp https://github.com/assimp/assimp (load 3d models)
* GLM https://github.com/g-truc/glm (math library)
* Nlohmann JSON https://github.com/nlohmann/json (json manipulation)
* STB_IMAGE https://github.com/nothings/stb/blob/master/stb_image.h (image lib)
* LUA JIT https://luajit.org/ (jitted scripit language) 

# Projects

The projects can be found in the projects/external folder, where you have to do a ```git submodule init``` and then a ```git submodule update```

## First 2D Game

The first game is called "Air Figther" and game be found in games folder

It's a game about destroying enemies airplane and getting to destroy a final boss

This game was made to validade the engine release and can find it [here](https://github.com/RodrigoPAml/AirFighter)

![1](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/13caab37-b00e-419d-be03-69e44108b269)

![2](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/051d48c1-22e7-407a-9e16-b421f5f43b9c)

## Fractal project

One implemented fractal and one retrieved from shader toy (link in shader file)

Repository in [here](https://github.com/RodrigoPAml/MandelbrotFractal)

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/b17b1fe9-c4b1-42d4-8a97-e17d224e339d)

My fractal

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/8baca372-0148-4342-9be8-33c5525ec58a)

## 3D Scene

Open an 3d object an draw it with renderer, this is in the projects/example folder

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/07b75cc4-aba1-4a98-867f-966723d3260b)

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/7432d2b5-7668-4091-81fb-5f6ddd405722)

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/c7d1a849-4961-4036-87f7-e98db5d4b2dc)

## 2D Ray Tracing

The first attemp to implement ray tracing in OpenGL using BoxEngine

Repository in [here](https://github.com/RodrigoPAml/RayTracer2D)

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/ca12a844-35c0-4eb0-8313-531769a752e9)

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/9aa1bf2f-e6f2-4be2-8def-2f60422ab165)

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/9fde6875-9403-4905-b1ce-dd26ae086da1)






