# BoxEngine

BoxEngine is application to build 2D and 3D general applications like games using the scripting language lua.

This engine is ideal to build applications using the abstract layers implemented with OpenGL for fast prototypes
Its uses the GameObject architecture to build the scenes with script attached to give it behaviour.

The engine runs in c++ but the scripting language is in LUA (with JIT compiler), a brazilian language.

Projects can be run in production mode (pass folder via argument) or editor mode

# Features

## Scripting features

* input module (keyboard and mouse)
* audio module (2d and 3d audios)
* font module (with support for any .ttf)
* camera module (support for 2d and 3d camera manipulations)
* debug/logging module (logging suport also in scripting)
* texture module (allows to manipulate texture with the GPU)
* shader module (allows to create and use shader with the GPU)
* vertex module (allows to allocate mesh with the GPU)
* framebuffer module (manipulate framebuffer via GPU)
* primitives module (allows to draw basic shapes in 2d and 3d, including to draw textures)
* scene module (allows to instantiate GO and scripts and manipulate the game scene)
* GUI module (to do)
* import module (to do, allows to import 3d object files)
* physics module (to do)

## Editor features

* Open an Create projects
* Manipulate game scene via Game Tree (create go, duplicate, delete)
* Logs tab to help debug the editor and the application
* Files tab to help manipulate project files (game assets)
* Info tab to see engine internal information (instance of mesh, textures, fps, frametime)
* Inspector to allow manipulate a gameobject, add scripts and modify project settings 
* Integration with vs code for scripting (recommend use lua server extension)

## Script example

Basic script behaviour when attached to game object

```lua
teste = {}

function teste.start()
    local this = teste[go.current()]
   
    log('starting')
    log('My id is' .. go.current())

    this.var = 'abc'
end

function teste.update()
   log('updating')
end

function teste.destroy()
    log('destroy')
end
```

# Libraries used

* GLFW https://www.glfw.org/ (Window manipulation)
* GLAD https://glad.dav1d.de/ (OpenGL initialization)
* FreeType https://freetype.org/ (Font lib)
* ImGui https://github.com/ocornut/imgui (GUI lib)
* ImPlot https://github.com/epezent/implot (GUI Plots)
* https://www.ambiera.com/irrklang/ (Audio lib)
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

# First game

The first came is called "Air Fither and game be found in games folder

It's a game about destroying enemies airplane and getting the better possible score

This game was made to validade the engine release

![1](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/13caab37-b00e-419d-be03-69e44108b269)

![2](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/051d48c1-22e7-407a-9e16-b421f5f43b9c)

Future a 3d game will be released
