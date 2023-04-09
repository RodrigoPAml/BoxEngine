# Log Module

## Log
Log into the console
```lua
function log(message: string)
```

## Warning
Log a warning into the console
```lua
function warn(message: string)
```

## Error
Log an error into the console
```lua
function error(message: string)
```

# Utils Module

## GetFPS
Return a number with current fps
```lua
function _utils_.get_fps()
```

## GetFrameTime
Return a number with current frametime
```lua
function _utils_.get_frametime()
```

## ToString
Transform any data type into a string and return it
```lua
function _utils_.to_string(object: any)
```

# Time Module

## GetTimestamp
Return a number with the timestamp in seconds since application started
```lua
function _time_.get_timestamp()
```

## GetDateTime 
Return a table with current date
```lua
function _time_.get_datetime()
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
function _go_.current()
```

## Create
Create a gameobject

Returns the id in case of success else return nil
```lua
function _go_.create(arg: table)
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
function _go_.destroy(id: number)
```

## Get
Get a gameobject, pass the id by argument

Return a table with the go information if find it, else return nil
```lua
function _go_.get(id: number)
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
function _go_.update(arg: table)
```

The argument table format
```lua
{
    "name": string,
    "active": bool,
}
```

# Script Module

# Drawing Module

# Camera 2D Module

# Camera 3D Module

# Window Module

# Directory

# Input

# Image

# Command

#  Shader

# Texture

# Framebuffer

# Vertex
