# BoxEngine

BoxEngine is an engine to build 2D and 3D general applications, like games, using the scripting language lua.

This engine is ideal to build applications using the abstract layers implemented with OpenGL for fast prototypes
It uses the GameObject architecture to build the scene with script attached to give it behaviour.

The engine runs in c++ but the scripting language is in LUA (with JIT compiler), a Brazilian language.

Projects can be run in production mode (pass folder via argument) or editor mode

# Features

## Scripting features

* input module (keyboard and mouse)
* audio module (2d and 3d audios)
* font module (with support for any .ttf)
* camera module (support for 2d and 3d camera manipulations)
* debug/logging module (logging support also in scripting)
* texture module (allows to manipulate texture with the GPU)
* shader module (allows to create and use shader with the GPU)
* vertex module (allows to allocate mesh with the GPU)
* framebuffer module (manipulate framebuffer via GPU)
* primitives module (allows to draw basic shapes in 2d and 3d, including to draw textures)
* scene module (allows to instantiate GO and scripts and manipulate the game scene)
* import module (allows to import 3d object files)
* renderer module (allows to draw 3d models, currently have a basic version)
* GUI module (to do)
* physics module (to do)

## Editor features

* Open an Create projects
* Play and Editor mode wich can be detected via script/go to manipulate the scene
* Manipulate game scene via Game Tree (create go, duplicate, delete)
* Logs tab to help debug the editor and the application
* Files tab to help manipulate project files (game assets)
* Info tab to see engine internal information (instance of mesh, textures, fps, frametime)
* Inspector to allow manipulate a gameobject, add scripts and modify project settings 
* Integration with vs code for scripting (recommend use lua server extension)

## Script example

Basic script behaviour when attached to game object

```lua
function teste.start()
    local this = engine.current()
   
    engine.log('starting')
    engine.log('My go id is' .. engine.go.current())
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

# Screen Shoots

## Playing in editor mode

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/f0d02127-782f-4fb4-9209-b1361e0e2b19)

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/de860063-8b48-4131-ad01-637ad0eb92c2)

# Scripting API Documentation

Read the scripting api documentation [here](https://github.com/RodrigoPAml/BoxEngine/blob/main/docs/api.md)

# Projects

The code is in the Projects folder

## First game

The first game is called "Air Figther" and game be found in games folder

It's a game about destroying enemies airplane and getting the better possible score

This game was made to validade the engine release

![1](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/13caab37-b00e-419d-be03-69e44108b269)

![2](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/051d48c1-22e7-407a-9e16-b421f5f43b9c)

## Fractal project

One implemented fractal and one retrieved from shader toy (link in shader file)

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/b17b1fe9-c4b1-42d4-8a97-e17d224e339d)

My fractal

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/8baca372-0148-4342-9be8-33c5525ec58a)

## 3D Scene

Open an 3d object an draw it with renderer

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/07b75cc4-aba1-4a98-867f-966723d3260b)

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/7432d2b5-7668-4091-81fb-5f6ddd405722)

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/c7d1a849-4961-4036-87f7-e98db5d4b2dc)

## 2D Ray Tracing

The first attemp to implement ray tracing in openGL

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/ca12a844-35c0-4eb0-8313-531769a752e9)

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/9aa1bf2f-e6f2-4be2-8def-2f60422ab165)

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/9fde6875-9403-4905-b1ce-dd26ae086da1)






