# BoxEngine

BoxEngine is application to build 2D and 3D general applications like games using the scripting language lua.

This engine is ideal to build applications using the abstract layers implemented with OpenGL with fast prototypes
Its uses the GameObject architecture to build the scenes with script attached to give it behaviour.

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

# Screen Shoots

## Playing in editor mode

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/3eb808f2-61cb-47f0-b12e-2b0ff5ed5aa6)

![image](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/e5222e7d-badf-4ced-a4ad-9bd14c697449)

# Scripting API Documentation

Read the scripting api documentation [here](https://github.com/RodrigoPAml/BoxEngine/blob/main/docs/api.md)

# First game

The first came is called "Air Fither and game be found in games folder

It's a game about destroying enemies airplane and getting the better possible score

![1](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/2ebb77d7-cc41-4283-a906-1e16ce172ae5)


![2](https://github.com/RodrigoPAml/BoxEngine/assets/41243039/0d4bcb86-7090-43f3-9c04-753486ce9c49)






