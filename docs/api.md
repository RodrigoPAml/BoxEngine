# Log Module

## Log
Log into the console
```lua
function log(message: string) end
```

## Warning
Log a warning into the console
```lua
function warn(message: string) end
```

## Error
Log an error into the console
```lua
function error(message: string) end
```

# Utils Module

## GetFPS
Return a number with current fps
```lua
function _utils_.get_fps() end
```

## GetFrameTime
Return a number with current frametime
```lua
function _utils_.get_frametime() end
```

## ToString
Transform any data type into a string and return it
```lua
function _utils_.to_string(object: any) end
```

# Time Module

## GetTimestamp
Return a number with the timestamp in seconds since application started
```lua
function _time_.get_timestamp() end
```

## GetDateTime 
Return a table with current date
```lua
function _time_.get_datetime() end
```
The returned table format is 
```lua
{
    "minute": number,
    "hour": number,
    "second": number,
    "day": number,
    "month": number,
    "year": number,
}
```

# Game Object Module

## Current
Return a number with current game object been executed
```lua
function _go_.current() end
```

## Create
Create a gameobject

Returns the id in case of success else return nil
```lua
function _go_.create(arg: table) end
```

Argument table format
```lua
{
    "name": string, -- optional
    "active": bool, -- optional
    "father_id": number, -- the id of the father go, also optional
}
```

## Destroy
Destroy a gameobject, pass the id by argument

Returns a boolean indicating success 
```lua
function _go_.destroy(id: number) end
```

## Get
Get a gameobject, pass the id by argument

Return a table with the go information if find it, else return nil
```lua
function _go_.get(id: number) end
```
Returned table format
```lua
{
    "id": number,
    "name": string,
    "active": bool,
    "father_id": number,
    "is_to_destroy": bool, -- if the go is destroyed (eg: is going to)
    "scripts": 
    {  -- array of scripts names
        {  -- array item format
            [key: number] : [value: string]
        }
    },
    "childrens": 
    { -- id array of the go childrens
        { -- array item format
             [key: number] : [value: string]
        }
    }
    "
}
```

## Update
Update a gameobject, pass the table by argument with update information

Return a bool indicating success
```lua
function _go_.update(arg: table) end
```

The argument table format
```lua
{
    "name": string, -- optional
    "active": bool, -- optional
}
```

# Script Module

## GetScript
Get the script information from a gameobject

If not find it then return nil
```lua
function _script_.get(goId: number, scriptName: string) end
```

The returned table format
```lua
{
    "name": string,  -- script name
    "path": string, -- loaded path
    "state": string, -- state of the script, see ScriptStateEnum ins Enums section below
    "is_started": bool, -- if the Start() function of the script was called
}
```

## AddScript
Add the script into a gameobject

Return a bool indicating success
```lua
function _script_.add(goId: number, scriptName: string) end
```

## RemoveScript
Remove the script of a gameobject

Return a bool indicating success
```lua
function _script_.remove(goId: number, scriptName: string) end
```

# Camera 2D Module

# Camera 3D Module

# Drawing Module

## Draw2DRect
Draw a 2D rectangle

```lua
function _draw2d_.rect(object: table) end
```

The argument table format
```lua
{
    "position": {x:number, y:number}, -- position, vec2 format
    "size": {x:number, y:number}, -- size, vec2 format
    "color": {x:number, y:number, z:number}, -- color, vec3 format, optional
    "rotation": number, -- rotation in degrees, optional
    "filled": bool, -- fill or not the shape, optional
}
```

## Draw2DCircle
Draw a 2D circle

```lua
function _draw2d_.circle(object: table) end
```

The argument table format
```lua
{
    "position": {x:number, y:number}, -- position, vec2 format
    "size": {x:number, y:number}, -- size, vec2 format
    "color": {x:number, y:number, z:number}, -- color, vec3 format, optional
    "rotation": number, -- rotation in degrees, optional
    "filled": bool, -- fill or not the shape, optional
}
```

## Draw2DTriangle
Draw a 2D triangle

```lua
function _draw2d_.triangle(object: table) end
```

The argument table format
```lua
{
    "position": {x:number, y:number}, -- position, vec2 format
    "size": {x:number, y:number}, -- size, vec2 format
    "color": {x:number, y:number, z:number}, -- color, vec3 format, optional
    "rotation": number, -- rotation in degrees, optional
    "filled": bool, -- fill or not the shape, optional
}
```

## Draw2DLine
Draw a 2D line

```lua
function _draw2d_.line(object: table) end
```

The argument table format
```lua
{
    "position_start": {x:number, y:number}, -- start position, vec2 format
    "position_end": {x:number, y:number}, -- end position, vec2 format
    "color": {x:number, y:number, z:number}, -- color, vec3 format, optional
}
```

## Draw2DPoint
Draw a 2D point

```lua
function _draw2d_.point(object: table) end
```

The argument table format
```lua
{
    "position": {x:number, y:number}, -- position, vec2 format
    "color": {x:number, y:number, z:number}, -- color, vec3 format, optional
}
```

# Window Module

# Directory

# Input

# Image

# Command

#  Shader

# Texture

# Framebuffer

# Vertex

# Enums

## ScriptState
{
    ToLoad, // Script needs to be loaded
    ToStart, // Script needs to start (and its loaded)
    Updating, // Script is running (and its started)
    ToDestroy, // Script needs to be destroy (and its started or updating)
    Destroyed // Script is destroyed (destroyed)
};
