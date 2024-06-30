# Main functions

## Log
Log into the console
```lua
function engine.log(message = string) end
```

## Warning
Log a warning into the console
```lua
function engine.warn(message = string) end
```

## Error
Log an error into the console
```lua
function engine.error(message = string) end
```

## To String
Transform any data type into a string and return it
```lua
function engine.to_string(object = any) end
```

## Current data

Get the current script data (like 'this' when using a class)

```lua
function engine.current() end
```

## External data
Get data from other go and respective script

If not finded return nil

```lua
function engine.data(goId = string, scriptName = string) end
```

## Get Mode
Return the engine running mode in enums.ProjectModeEnum format
```lua
function engine.get_mode() end
```

## Get FPS
Return a number with current fps
```lua
function engine.get_fps() end
```

## Get Frame Time
Return a number with current frametime
```lua
function engine.get_frametime() end
```

## Stop
Stop engine and exit application
```lua
function engine.stop() end
```

## Restart
Restart application
```lua
function engine.restart() end
```

## Is Editor focused
Return a boolean indicating if editor is focused

```lua
function engine.is_editor_focused() end
```

# Time Module

## Get Timestamp
Return a number with the timestamp in seconds since application started
```lua
function engine.time.get_timestamp() end
```

## Get Date Time 
Return a table with current date
```lua
function engine.time.get_datetime() end
```
The returned table format is 
```lua
{
    minute = number,
    hour = number,
    second = number,
    day = number,
    month = number,
    year = number,
}
```

# Game Object Module

## Current Go
Return a number with current game object been executed
```lua
function engine.go.current() end
```

## Create Go
Create a gameobject

Returns the id in case of success else return nil
```lua
function engine.go.create(arg = table) end
```

Argument table format
```lua
{
    name = string, -- optional
    active = boolean, -- optional
    father_id = number, -- the id of the father go, also optional
}
```

## Create Copy Go

Create a copy from gameobject

If you don't need to assign a father just leave empty

Returns the id of new go in case of success
```lua
function engine.go.create_copy(goId = string, newFatherId = string) end
```

## Destroy Go
Destroy a gameobject, pass the id by argument

Returns a boolean indicating success 
```lua
function engine.go.destroy(id = number) end
```

## Get Go
Get a gameobject, pass the id by argument

Return a table with the go information if find it, else return nil
```lua
function engine.go.get(id = number) end
```
Returned table format
```lua
{
    id = number,
    name = string,
    active = boolean,
    father_id = number,
    is_to_destroy = boolean, -- if the go is destroyed (eg = is going to)
    scripts = 
    {  -- array of scripts names
        {  -- array item format
            [key = number]  = [value = string]
        }
    },
    childrens = 
    { -- id array of the go childrens
        { -- array item format
             [key = number]  = [value = string]
        }
    }
}
```

## Get All Gos By Name
Find a list of game objects that match a name

Return a list of go ids
```lua
function engine.go.find_all(goName) end
```

## Set Go active
Update a gameobject, active property

Return a boolean indicating success
```lua
function engine.go.set_active(goId = string, active = bool) end
```

## Set Go Name
Update a gameobject, name property

Return a boolean indicating success
```lua
function engine.go.set_name(goId = string, name = string) end
```

## Change Go Father
Change the gameobject father

The second argument is optional, is not informed the go is set to the root

Return a boolean indicating success
```lua
function engine.go.change_father(goId = string, fatherId = string) end
```

## Change Go Index
Change the gameobject index in relation to his brothers

The displacement argument changes the index based on the current index

```lua
function engine.go.change_index(goId = string, displacement = number) end
```

## Load scripts immediately
Load scripts into memory in case you need to access it immediately

Normally the script of a go is loaded in the next frame and then started only in the next frame, if needed this behavior 
can be changed with this. With this the script will be loaded now and started in the next frame.

If fail this will trigger an internal error

```lua
function engine.go.load_scripts(goId = string) end
```

## Persist Go
Set the current go to persist not (will not be saved)

```lua
function engine.go.set_persist_go(val = bool) end
```

## Persist External Go
Set any go to persist or not (will not be saved)

```lua
function engine.go.set_persist_external_go(goId = string, val = bool) end
```

## Inspect go
Force the editor to inspect a go

```lua
function engine.go.inspect_go(goId = string) end
```

## Get inspected go
Get the inspected go by the editor, else nil

```lua
function engine.go.get_inspected_go() end
```

# Script Module

## Get Script
Get the script information from a gameobject

If not find it then return nil
```lua
function engine.script.get(goId = number, scriptName = string) end
```

The returned table format
```lua
{
    name = string,  -- script name
    path = string, -- loaded path
    state = string, -- state of the script, in enums.ScriptStateEnum format 
    is_started = boolean, -- if the Start() function of the script was called
    is_loaded = boolean, -- if the script has been loaded, including script data
}
```

## Add Script
Add the script into a gameobject

Return a boolean indicating success
```lua
function engine.script.add(goId = number, scriptName = string) end
```

## Destroy Script
Destroy the script of a gameobject

The remove argument indicates if the script should be also removed when destroyed, its an optional argument

Return a boolean indicating success
```lua
function engine.script.destroy(goId = number, scriptName = string, remove = bool) end
```

## Find all scripts
Return the gos id that contains the script given by name

```lua
function engine.script.find_all(scriptName = string) end
```

## Change Script Index
Change the script index 

```lua
function engine.script.change_index(goId = string, scriptName = string, index = number) end
```

## Displace script index
Change the script index in relation to his brothers

The displacement argument changes the index based on the current index

```lua
function engine.script.displace_index(goId = string, scriptName = string, displacement = number) end
```

## Persist Script
Set current script to persist or not (will not be saved)

```lua
function engine.script.set_persist_script(val = bool) end
```

## Persist External Script
Set any script to persist or not (will not be saved)

```lua
function engine.script.set_persist_ext_script(goId = string, scriptName = string, val = bool) end
```

## Persist Script Data
Set data from current script to persist or not (will not be saved)

```lua
function engine.script.set_persist_script_data(dataName = string, val = bool) end
```

## Persist External Script Data
Set any script data to persist or not (will not be saved)

```lua
function engine.script.set_persist_ext_script_data(goId = string, scriptName = string, val = bool) end
```

## Show Script Data
Set data from current script to show or not in the editor

```lua
function engine.script.set_show_script_data(dataName = string, val = bool) end
```

## Show External Script Data
Set any script data to show or not in the editor

```lua
function engine.script.set_persist_ext_show_data(goId = string, scriptName = string, val = bool) end
```

# Camera 2D Module

## Create 2D Camera
Create a 2D camera and return an id

```lua
function engine.cam2d.create(object = table) end
```

The argument table format
```lua
{
    left = number,
    right = number,
    top = number,
    bottom = number,
}
```

## Destroy 2D Camera
Destroy a 2D camera

Recieve the camera id and return bool indicating success
```lua
function engine.cam2d.destroy(id = number) end
```

## Get 2D Camera
Get a 2D camera

Recieve the camera id and return a table or nil if not find it
```lua
function engine.cam2d.get(id = number) end
```

The returned table format
```lua
{
    left = number,
    right = number,
    top = number,
    bottom = number,
}
```

## Get 2D Camera Matrix
Get a 2D camera ortho matrix

Recieve the camera id and return a table or nil if not find it
```lua
function engine.cam2d.get_matrix(id = number) end
```

The returned table format is a mat4
```lua
{
    1 = {{x = number, y = number, z = number, w = number}},
    2 = {{x = number, y = number, z = number, w = number}},
    3 = {{x = number, y = number, z = number, w = number}},
    4 = {{x = number, y = number, z = number, w = number}}
}
```

## Update 2D Camera
Update a 2D camera

Recieve the camera id and a table with update info

Return a bool indicating success
```lua
function engine.cam2d.update(id = number, info = table) end
```

The argument table format
```lua
{
    left = number, -- optional
    right = number, -- optional
    top = number, -- optional
    bottom = number, -- optional
}
```

## Set Current 2D Camera
Set the current 2D camera

Recieve the camera id

Return a bool indicating success
```lua
function engine.cam2d.set_current(id = number) end
```

## Get Current 2D Camera
Get the current 2D camera id

Return the camera id or nil

```lua
function engine.cam2d.get_current() end
```

# Camera 3D Module

## Create 3D Camera
Create a 3D camera and return an id

```lua
function engine.cam3d.create(object = table) end
```

The argument table format
```lua
{
    position = {x = number, y = number, z = number}, -- camera pos in vec3 format, optional
    yaw = number, -- yaw in degress, optional
    pitch = number, -- pitch in degress, optional
    fov = number, -- fov, optional
    aspect_ratio = number, -- aspect ratio, optional
    zfar = number, -- zfar, optional
    znear = number, -- znear, optional
}
```

## Destroy 3D Camera
Destroy a 3D camera and return an bool indicating success

```lua
function engine.cam3d.destroy(id = number) end
```

## Update 3D Camera
Update a 3D camera and return an bool indicating sucess

Recieve the camera id and a table with update info
```lua
function engine.cam3d.update(id = number, object = table) end
```

The argument table format
```lua
{
    position = {x = number, y = number, z = number}, -- camera pos in vec3 format, optional
    rotation = {x = number, y = number, z = number}, -- set rotation from a normalized front vector, optional
    yaw = number, -- yaw in degress, optional
    pitch = number, -- pitch in degress, optional
    fov = number, -- fov, optional
    aspect_ratio = number, -- aspect ratio, optional
    zfar = number, -- zfar, optional
    znear = number, -- znear, optional
}
```

## Get 3D Camera
Get a 3D camera and return a table, if not find it return nil

```lua
function engine.cam3d.get(id = number) end
```

The returned table format
```lua
{
    position = {x = number, y = number, z = number}, -- camera position, vec3
    right = {x = number, y = number, z = number}, -- camera right vector, vec3
    front = {x = number, y = number, z = number}, -- camera front vector, vec3
    up = {x = number, y = number, z = number},-- camera up vector, vec3
    yaw = number, -- yaw in degrees
    pitch = number, -- pitch in degrees
    fov = number, -- camera fov
    aspect_ratio = number, -- camera aspect ratio
    zfar = number, -- camera zfar
    znear = number, -- camera znear
}
```

## Translate Relative 3D Camera
Translate a 3D camera relation to its basis vectors and return an bool indicating success

Recieve the camera id and a table with translation info
```lua
function engine.cam3d.translate(id = number, object = table) end
```

The argument table format
```lua
{
    direction = string, -- direction in the format enums.CameraMovementEnum
    velocity = number, -- the velocity of translation
}
```

## Translate Absolute 3D Camera
Translate a 3D camera relation to the axis and return an bool indicating success

Recieve the camera id and a table with translation info
```lua
function engine.cam3d.translate_abs(id = number, object = table) end
```

The argument table format
```lua
{
    direction = string, -- direction in the format enums.CameraMovementEnum
    velocity = number, -- the velocity of translation
}
```

## Rotate 3D Camera
Rotate a 3D camera and return an bool indicating success

Recieve the camera id and a table with rotation info
```lua
function engine.cam3d.rotate(id = number, object = table) end
```

The argument table format
```lua
{
    yaw = number, -- yaw in degrees
    pitch = number, -- pitch in degrees
}
```

## Get View Matrix
Recieve the camera id and return the view matrix in mat4 format

Return nil if not find it

```lua
function engine.cam3d.get_view_matrix(id = number) end
```

The returned table format
```lua
{
    1 = {{x = number, y = number, z = number, w =n umber}},
    2 = {{x = number, y = number, z = number, w = number}},
    3 = {{x = number, y = number, z = number, w = number}},
    4 = {{x = number, y = number, z = number, w = number}}
}
```

## Get Projection Matrix
Recieve the camera id and return the projection matrix in mat4 format

Return nil if not find it

```lua
function engine.cam3d.get_projection_matrix(id = number) end
```

The returned table format
```lua
{
    1 = {{x = number, y = number, z = number, w = number}},
    2 = {{x = number, y = number, z = number, w = number}},
    3 = {{x = number, y = number, z = number, w = number}},
    4 = {{x = number, y = number, z = number, w = number}}
}
```

## Set Current Camera
Recieve the camera id and set as current camera

Return a bool indicating success
```lua
function engine.cam3d.set_current(id = number) end
```

## Get Current Camera
Return the current camera or nil if not finded

```lua
function engine.cam3d.get_current() end
```

# Drawing Module 

To draw primitives

## Draw 2D Rect
Draw a 2D rectangle

```lua
function engine.draw2d.rect(object = table) end
```

The argument table format
```lua
{
    position = {x = number, y = number}, -- position, vec2 format
    size = {x = number, y = number}, -- size, vec2 format
    color = {x = number, y = number, z = number, w = number}, -- color, vec4 format, optional
    rotation = number, -- rotation in degrees, optional
    filled = boolean, -- fill or not the shape, optional
}
```

## Draw 2D Circle
Draw a 2D circle

```lua
function engine.draw2d.circle(object = table) end
```

The argument table format
```lua
{
    position = {x = number, y = number}, -- position, vec2 format
    size = {x = number, y = number}, -- size, vec2 format
    color = {x = number, y = number, z = number, w = number}, -- color, vec4 format, optional
    filled = boolean, -- fill or not the shape, optional
}
```

## Draw 2D Triangle
Draw a 2D triangle

```lua
function engine.draw2d.triangle(object = table) end
```

The argument table format
```lua
{
    position1 = {x = number, y = number}, -- position1, vec2 format
    position2 = {x = number, y = number}, -- position2, vec2 format
    position3 = {x = number, y = number}, -- position3, vec2 format
    color = {x = number, y = number, z = number, w = number}, -- color, vec4 format, optional
    rotation = number, -- rotation in degrees, optional
}
```

## Draw 2D Line
Draw a 2D line

```lua
function engine.draw2d.line(object = table) end
```

The argument table format
```lua
{
    position_start = {x = number, y = number}, -- start position, vec2 format
    position_end = {x = number, y = number}, -- end position, vec2 format
    color = {x = number, y = number, z = number, w = number}, -- color, vec4 format, optional
}
```

## Draw 2D Point
Draw a 2D point

```lua
function engine.draw2d.point(object = table) end
```

The argument table format
```lua
{
    position = {x = number, y = number}, -- position, vec2 format
    color = {x = number, y = number, z = number, w = number}, -- color, vec4 format, optional
}
```

## Draw 2D Texture
Draw a 2d texture

```lua
function engine.draw2d.texture(object = table) end
```

The argument table format
```lua
{
    position = {x = number, y = number}, -- position, vec2 format
    size = {x = number, y = number}, -- size, vec2 format
    texture_id = number, the texture id
    rotation = number, -- rotation in degrees, optional
    color = {x = number, y = number, z = number }, -- color, vec3 format, optional
    color_weight = number, -- color weight in relation to texture, should vary between 0.0 and 1.0, optional
    transparency = number, -- transparency multiplier, should vary between 0.0 and 1.0, optional
}
```

## Draw 2D Texture in Editor Frame
Draw a 2d texture in Editor Frame

```lua
function engine.draw2d.frame(textureId = number) end
```

## Draw 3D Cube
Draw a 3D cube

```lua
function engine.draw3d.cube(object = table) end
```

The argument table format
```lua
{
    position = {x = number, y = number = z = number}, -- position, vec3 format
    size = {x = number, y = number = z = number}, -- size, vec3 format
    color = {x = number, y = number, z = number, w = number}, -- color, vec4 format, optional
    rotation = {x = number, y = number, z = number}, -- rotation in degrees in vec3 format, optional
    filled = boolean, -- fill or not the shape, optional
}
```

## Draw 3D Sphere
Draw a 3D sphere

```lua
function engine.draw3d.sphere(object = table) end
```

The argument table format
```lua
{
    position = {x = number, y = number = z = number}, -- position, vec3 format
    size = {x = number, y = number = z = number, w = number}, -- size, vec3 format
    color = {x = number, y = number, z = number}, -- color, vec4 format, optional
    rotation = {x = number, y = number, z = number}, -- rotation in degrees in vec3 format, optional
    filled = boolean, -- fill or not the shape, optional
}
```

## Draw 3D Point
Draw a 3D point

```lua
function engine.draw3d.point(object = table) end
```

The argument table format
```lua
{
    position = {x = number, y = number = z = number}, -- position, vec3 format
    color = {x = number, y = number, z = number, w = number}, -- color, vec4 format, optional
}
```

## Draw 3D Line
Draw a 3D line

```lua
function engine.draw3d.line(object = table) end
```

The argument table format
```lua
{
    position_start = {x = number, y = number = z = number}, -- position start, vec3 format
    position_end = {x = number, y = number = z = number}, -- position end, vec3 format
    color = {x = number, y = number, z = number, w = number}, -- color, vec4 format, optional
}
```

## Draw 3D Rect
Draw a 3D rect

```lua
function engine.draw3d.rect(object = table) end
```

The argument table format
```lua
{
    position = {x = number, y = number = z = number}, -- position, vec3 format
    size = {x = number, y = number = z = number}, -- size, vec3 format
    color = {x = number, y = number, z = number, w = number}, -- color, vec4 format, optional
    rotation = {x = number, y = number, z = number}, -- rotation in degrees in vec3 format, optional
    filled = boolean, -- fill or not the shape, optional
}
```

## Draw 3D Triangle
Draw a 3D triangle

```lua
function engine.draw3d.triangle(object = table) end
```

The argument table format
```lua
{
    position1 = {x = number, y = number = z = number}, -- position, vec3 format
    position2 = {x = number, y = number = z = number}, -- position, vec3 format
    position3 = {x = number, y = number = z = number}, -- position, vec3 format
    color = {x = number, y = number, z = number, w = number}, -- color, vec4 format, optional
    filled = boolean, -- fill or not the shape, optional
}
```

## Draw 3D Circle
Draw a 3D circle

```lua
function engine.draw3d.circle(object = table) end
```

The argument table format
```lua
{
    position = {x = number, y = number = z = number}, -- position, vec3 format
    size = {x = number, y = number = z = number}, -- size, vec3 format
    color = {x = number, y = number, z = number, w = number}, -- color, vec4 format, optional
    rotation = {x = number, y = number, z = number}, -- rotation in degrees in vec3 format, optional
    filled = boolean, -- fill or not the shape, optional
}
```

# Window Module

## Get Window Size
Return a table with current window size

```lua
function engine.window.get_window_size() end
```

The returned table format
```lua
{ -- vec2 format
    x = number, 
    y = number
}
```

## Get Editor Window Size
Return a table with current editor window size

```lua
function engine.window.get_editor_window_size() end
```

The returned table format
```lua
{ -- vec2 format
    x = number, 
    y = number
}
```

## Get Window Limits
Return a table with the window limits

```lua
function engine.window.get_window_limits() end
```

The returned table format
```lua
{ -- vec2 format
    max_x = number, 
    max_y = number,
    min_x = number, 
    min_y = number
}
```

# Directory Module

## Read File
Open a file and return its contents

```lua
function engine.dir.read_file(file_name = string) end
```

The returned table format
```lua
{
    open = bool, 
    content = string
}
```

## Create File
Create a file with optional content and return a bool indicating success

```lua
function engine.dir.create_file(file_name = string, content = string) end
```

## Create Folder
Create a folder and return a bool indicating success

```lua
function engine.dir.create_folder(folder_name = string) end
```

## Move
Move a folder or file and return a bool indicating success

```lua
function engine.dir.move(from = string, to = string) end
```

## Copy
Copy a folder or file and return a bool indicating success

```lua
function engine.dir.copy(from = string, to = string) end
```

## Delete
Delete a folder or file and return a bool indicating success

```lua
function engine.dir.delete(path = string) end
```

## Is File
Return a bool indicating if the provided path is a file

```lua
function engine.dir.is_file(path = string) end
```

## Is Directory
Return a bool indicating if the provided path is a directory

```lua
function engine.dir.is_dir(path = string) end
```

## Exists
Return a bool indicating if the provided path/file exists

```lua
function engine.dir.exists(path = string) end
```

## Get Current Path
Return the executable path

```lua
function engine.dir.get_current_path() end
```

## Get Base Path
Return the base project path

```lua
function engine.dir.get_base_path() end
```

## Get Assets Path
Return the assets path

```lua
function engine.dir.get_assets_path() end
```

## Get Logs Path
Return the logs path

```lua
function engine.dir.get_logs_path() end
```

## List Directories
Return the an table with the content of a directory, if not exists return nil

```lua
function engine.dir.list_dir(path = string) end
```

## Reduce Path By
Reduce a path n times and return it

```lua
function engine.dir.reduce_path_by(path = string, n = number) end
```

## Get File Name Extension
Recieve a file path and return the extension

```lua
function engine.dir.get_file_name_ext(path = string) end
```

## Get Path Or File Name
Recieve a file or dir path and return only its name

```lua
function engine.dir.get_path_or_file_name(path = string) end
```

## Get File Name No Extension
Recieve a file path and return only its name without extension

```lua
function engine.dir.get_file_name_no_ext(path = string) end
```

## Execute a system command

Recieve a string command

```lua
function engine.dir.exec(command = string) end
```

# Input Module

## Get Keyboard Key
Get the key status

Argument is a string in enums.KeyboardKeyEnum format 

Return the result as a string in enums.InputActionEnum format 

```lua
function engine.input.get_key(key = string) end
```

## Get Modifier Key
Get the modifier key status

Argument is a string in enums.KeyModifierEnum format

Return the result as a string in enuns.InputActionEnum format 

```lua
function engine.input.get_mod(key = string) end
```

## Get Mouse Position
Return a vec2 with mouse coordinates

```lua
function engine.input.get_mouse_pos() end
```

## Get Camera Mouse Position
Return a vec2 with mouse coordinates based on current camera

```lua
function engine.input.get_cam_mouse_pos() end
```

## Get Mouse Variation
Return a vec2 with mouse variations

```lua
function engine.input.get_mouse_variation() end
```

## Get Mouse Button
Get the mouse button status

Argument is a string in enums.MouseButtonEnum format 

Return the result as a string in enums.InputActionEnum format

```lua
function engine.input.get_mouse_button(key = string) end
```

# Image Module

## Open
Open a image and return its info

Argument is a string with path

Return the result as a table or nil if failed

```lua
function engine.img.open(path = string) end
```
The returned table format
```lua
{
    size = {x = number, y = number} -- the image size, vec2 format
    path = string, -- the path that the image was loaded
    format = string -- the image format see Texture Format below
    data = { -- a table of numbers with raw data information of the image
        1 = number,
        ...,
        size.x*size.y = number
    } -- 
}
```

# Command Module

## Enable VSync
Enables the vsync

```lua
function engine.command.enable_vsync() end
```

## Disable VSync
Disables the vsync

```lua
function engine.command.disable_vsync() end
```

## Enable Depth Testing
Enables the depth testing

```lua
function engine.command.enable_depth_testing() end
```

## Disable Depth Testing
Disables the depth testing

```lua
function engine.command.disable_depth_testing() end
```

## Set Depth Testing Mode
Set the depth testing mode, receive a string in enums.DepthTestingModeEnum 

```lua
function engine.command.set_depth_testing_mode(mode = string) end
```

## Enable Culling Face
Enable the face culling

```lua
function engine.command.enable_culling_face() end
```

## Disable Culling Face
Disable the face culling

```lua
function engine.command.disable_culling_face() end
```
## Set Culling Face Mode
Set the face culling mode with enums.CullingFaceModeEnum format

```lua
function engine.command.set_culling_face_mode(mode = string) end
```

## Set Primitive Line Size
Set the primitive Line size, recieve as argument with number type

```lua
function engine.command.set_primitive_line_size(size = number) end
```

## Set Primitive Point Size
Set the primitive point size, recieve as argument with number type

```lua
function engine.command.set_primitive_point_size(size = number) end
```

## Set Polygon Draw Mode
Set the polygons draw mode in enums.PolygonModeEnum format

```lua
function engine.command.set_polygon_draw_mode(mode = string) end
```

## Enable Blending
Enables the blending

```lua
function engine.command.enable_blending() end
```

## Disable Blending
Disables the blending

```lua
function engine.command.disable_blending() end
```

# Shader Module

## Create Shader
Create a shader, receive a table with creation information

Return id if success else return nil
```lua
function engine.shader.create(arg = table) end
```
The argument table format
```lua
{
    vertex_path = string -- path to vertex shader file
    fragment_path = string, -- path to the fragment shader file (optional)
    geometry_path = string  -- path to the geometry shader file (optional)
}
```

## Create Raw Shader
Create a shader, receive a table with data information

Return id if success else return nil
```lua
function engine.shader.create_raw(arg = table) end
```
The argument table format
```lua
{
    vertex_content = string -- content of vertex shader
    fragment_content = string, -- content of fragment shader (optional)
    geometry_content = string  -- content of geometry shader (optional)
}
```

## Delete Shader
Delete a shader, receive the id

Return bool indicating success
```lua
function engine.shader.destroy(id = number) end
```

## Activate Shader
Activate a shader, receive the id

Return bool indicating success
```lua
function engine.shader.activate(id = number) end
```

## Disable Current Shader
Disable the current active shader

```lua
function engine.shader.unactive_all() end
```

## Set Shader Bool
Set bool variable into shader, receive the id and data information

Return bool indicating success
```lua
function engine.shader.set_bool(id = number, name = string, value = bool) end
```

## Set Shader Integer
Set integer variable into shader, receive the id and data information

Return bool indicating success
```lua
function engine.shader.set_int(id = number, name = string, value = number) end
```

## Set Shader Float
Set float variable into shader, receive the id and data information

Return bool indicating success
```lua
function engine.shader.set_float(id = number, name = string, value = number) end
```

## Set Shader XY
Set XY (separated vec2) variable into shader, receive the id and data information

Return bool indicating success
```lua
function engine.shader.set_xy(id = number, name = string, x = number, y = number) end
```

## Set Shader XYZ
Set XYZ (separated vec3) variable into shader, receive the id and data information

Return bool indicating success
```lua
function engine.shader.set_xyz(id = number, name = string, x = number, y = number, z = number) end
```

## Set Shader XYZW
Set XYZW (separated vec4) variable into shader, receive the id and data information

Return bool indicating success
```lua
function engine.shader.set_xyzw(id = number, name = string, x = number, y = number, z = number, w = number) end
```

## Set Shader vec2
Set a vec2 variable into shader, receive the id and data information

Return bool indicating success
```lua
function engine.shader.set_vec2(id = number, name = string, {x = number, y = number}) end
```

## Set Shader vec3
Set vec3 variable into shader, receive the id and data information

Return bool indicating success
```lua
function engine.shader.set_vec3(id = number, name = string, {x = number, y = number, z = number}) end
```

## Set Shader vec4
Set vec4 variable into shader, receive the id and data information

Return bool indicating success
```lua
function engine.shader.set_vec4(id = number, name = string, { x = number, y = number, z = number, w = number}) end
```

## Set Shader mat2
Set mat2 variable into shader, receive the id and data information

Return bool indicating success
```lua
function engine.shader.set_mat2(id = number, name = string, mat2 = table) end
```

The argument table format
```lua
{
    {x = number, y = number },
    {x = number, y = number },
}
```

## Set Shader mat3
Set mat3 variable into shader, receive the id and data information

Return bool indicating success
```lua
function engine.shader.set_mat3(id = number, name = string, mat3 = table) end
```

The argument table format
```lua
{
    {x = number, y = number, z = number},
    {x = number, y = number, z = number},
    {x = number, y = number, z = number},
}
```

## Set Shader mat4
Set mat4 variable into shader, receive the id and data information

Return bool indicating success
```lua
function engine.shader.set_mat4(id = number, name = string, mat4 = table) end
```

The argument table format
```lua
{
    {x = number, y = number, z = number, w = number},
    {x = number, y = number, z = number, w = number},
    {x = number, y = number, z = number, w = number},
    {x = number, y = number, z = number, w = number},
}
```

# Texture Module

## Create Empty Texture
Create a empty texture, receive a table with creation information

Return id if success else return nil
```lua
function engine.texture.create_empty(arg = table) end
```
The argument table format
```lua
{
    texture_size = {x = number, y = number}, -- texture size, vec2 format
    minifying_filter = string, -- in enums.MinifyingFilterEnum format, optional
    magnification_filter = string, -- in enums.MagnificationFilterEnum format, optional
    texture_wrap_t = string, -- in  enums.TextureWrapEnum format, optional
    texture_wrap_s = string, -- in  enums.TextureWrapEnum format, optional
    texture_pixel_format = string, -- in enums.TexturePixelEnum format, optional
    texture_internal_format = string, -- in enums.TextureInternalFormatEnum format, optional
    texture_format = string, -- in enums.TextureFormatEnum format, optional
    ansiotropic_filter = number, -- a number for ansiotropic filter, optional
    border_color = {x = number, y = number, z = number} -- texture border_color in vec3 format, optional
}
```

## Create Multisampled Texture
Create a empty multisampled texture, receive a table with creation information

Return id if success else return nil
```lua
function engine.texture.create_multi_sampled(arg = table) end
```
The argument table format
```lua
{
    texture_samples = number -- number of samples
    texture_size = {x = number, y = number}, -- texture size, vec2 format
    texture_internal_format = string, -- in enums.TextureInternalEnum format
}
```

## Create Texture
Create a texture, receive a table with creation information

Return id if success else return nil
```lua
function engine.texture.create(arg = table) end
```
The argument table format
```lua
{
    image_path = string, -- image path
    minifying_filter = string, -- in enums.MinifyingFilterEnum format, optional
    magnification_filter = string, -- in enums.MagnificationFilterEnum format, optional
    texture_wrap_t = string, -- in enums.TextureWrapEnum format, optional
    texture_wrap_s = string, -- in enums.TextureWrapEnum format, optional
    ansiotropic_filter = number, -- a number for ansiotropic filter, optional
    border_color = {x = number, y = number, z = number} -- texture border_color in vec3 format, optional
}
```

## Get Texture Info
Receive the id and return info or nil if not finded

```lua
function engine.texture.get_info(id = number) end
```

The returned table format
```lua
{
    multisampled = bool, -- if the texture is multisampled
    samples = number, -- number of samples if texture is multisampled
    size = vec2, -- texture size in pixels
}
```

## Destroy Texture
Destroy a texture, receive the id

Return bool indicating success
```lua
function engine.texture.destroy(id = number) end
```

## Active Texture
Active a texture, receive the id and the texture unit slot as a number

Return bool indicating success
```lua
function engine.texture.active(id = number, slot = number) end
```

## Disable Texture Unit
Remove any texture at a texture unit slot

```lua
function engine.texture.disabletextureunit(slot = number) end
```

# Framebuffer Module

## Create Framebuffer
Create a framebuffer, receive a table with creation information

Return id if success else return nil
```lua
function engine.framebuffer.create(arg = table) end
```
The argument table format
```lua
{
    texture_attachments_count = number, -- number of texture attachments,
    texture_attachments = = {1 = number, ..., texture_count = number} -- table with the ids of the texture attachments,
    depth_attachment = number, -- texture id for depth attachment, optional
    renderbuffer_attachment = { -- optional
        type = string -- in enums.RenderBufferAttachmentType format,
        format = string -- in enums.RenderBufferFormat format,
        size = {x = number, y = number} -- render buffer size
        aliasing = number -- multisample in render buffer
    }
}
```

## Destroy Framebuffer
Destroy a framebuffer, receive the id

Return bool indicating success
```lua
function engine.framebuffer.destroy(id = number) end
```

## Active Framebuffer
Active a framebuffer, receive the id

Return bool indicating success
```lua
function engine.framebuffer.active(id = number) end
```

## Disable All Framebuffer
Active the default screen buffer of the window, witch can't be used

```lua
function engine.framebuffer.active_none() end
```

## Get Framebuffer Attachments Size
Receive the framebuffer id and return a framebuffer number of texture attachments, else nil if not finded

```lua
function engine.framebuffer.get_attachments_size(id = number) end
```

## Get Framebuffer Attachment
Receive the framebuffer id and the texture attachment position

Return the id of the texture attachment, else nil if not finded
```lua
function engine.framebuffer.get_attachment(id = number, index = number) end
```

## Clear Current Framebuffer
Clear the current framebuffer

```lua
function engine.framebuffer.clear(color = vec4) end
```

## Set Framebuffer Clear Modes
Set the framebuffer clear modes

```lua
function engine.framebuffer.set_clear_modes(modes = table) end
```

The argument table format
```lua
{
    color = boolean, -- bool if you and this clear mode
    depth = boolean, -- bool if you and this clear mode
    stencil = boolean, -- bool if you and this clear mode
}
```

## Set View Port
Set current view port, recieve a vec4 format table

```lua
function engine.framebuffer.set_viewport(viewport = table) end
```

The argument table format
```lua
{
    x = number, -- start viewport x
    y = number, -- start viewport y
    z = number, -- size viewport x
    w = number -- size viewport y
}
```

# Vertex Module

## Create Vertex Data
Create a vertex data, receive a table with creation information, and an optional table with index data

Return id if success else return nil
```lua
function engine.vertex.create(vertexData = table, indexData = table) end
```
The first argument table format
```lua
{
    vertices_count = number, -- the total number of vertices, considering the attributes of each vertex
    buffers_count = number, -- the number of buffers that will be used to separate the vertices attributes
    buffers = { -- the buffers that holds the vertices data
        1 = { -- buffer item format
            use = string, -- (optional) use internally by opengl in enums.DataUseEnum format
            type = string, -- type of the data, use enums.VertexBufferTypeEnum format
            data = { -- data, array of number
                1 = number,
                ...
                vertices_count*layout_count = number
            },
            layouts_count = number, -- number of division in attributes of buffer
            layout = { -- layou description
                1 = { -- layout item format
                    count = number, -- number of elements in layout
                    normalized = bool, -- if data is normalized (optional)
                },
                ... -- until layouts_count
            }
        },
        ... -- until buffers_count
    }
}
```

The second argument table format (optional)
```lua
{
    use = string, -- (optional) use internally by opengl in Data Use format (see enums below)
    count = number, -- number of indices used
    data = { -- data, array of number for indices
        1 = number,
        ...
        count = number
    }
}
```

## Destroy Vertex Data
Destroy a vertex data, receive the id

Return bool indicating success
```lua
function engine.vertex.destroy(id = number) end
```

## Get Vertex Info
Receive the id and return info or nil if not finded

```lua
function engine.vertex.get_info(id = number) end
```

The returned table format
```lua
{
    gl_id = number, -- open gl id (vao)
}
```

## Activate Vertex Data
Activate a vertex data, receive the id

Return bool indicating success
```lua
function engine.vertex.activate(id = number) end
```

## Call to Draw Vertex Data
Draw a vertex data, receive the id and draw mode

drawMode is in enums.DrawingTypeEnum format

Return bool indicating success
```lua
function engine.vertex.draw(id = number, drawMode = string) end
```

## Modify Vertex Data
Modify a vertex data, receive the id and modification data as a table

Return bool indicating success
```lua
function engine.vertex.modify(id = number, modifyData = table) end
```

The argument table format
```lua
{
    start = number, -- the start position to be modified
    size = number, -- the size of modification
    buffer = number, -- with buffer to modified
    type = string,  -- type of the data, format enums.VertexBufferTypeEnum format
    data = { -- data to replace the buffer
        1 = number,
        ...,
        size = number
    }
}
```

## Generate 2D meshes
Return id of vertex data

dataUse argument is in Data Use format (see enums below)

```lua
function engine.generator.gen_2d_point(dataUse = string) end
function engine.generator.gen_2d_line(dataUse = string, filled = bool) end
function engine.generator.gen_2d_circle(dataUse = string, filled = bool, segments = number) end
function engine.generator.gen_2d_triangle(dataUse = string, filled = bool) end
```

## Generate 3D meshes
Return id of vertex data

dataUse argument is in Data Use format (see enums below)

```lua
function engine.generator.gen_3d_circle(dataUse = string, filled = bool, segments = number) end
function engine.generator.gen_3d_cube(dataUse = string, filled = bool) end
function engine.generator.gen_3d_line(dataUse = string) end
function engine.generator.gen_3d_point(dataUse = string) end
function engine.generator.gen_3d_rect(dataUse = string, filled = bool) end
function engine.generator.gen_3d_sphere(dataUse = string, filled = bool, segments = number) end
function engine.generator.gen_3d_triangle(dataUse = string, filled = bool) end
```

# Audio Module

## Create Audio

Returns id if success, else return nil

```lua
function engine.audio.create_2d(path = string) end
function engine.audio.create_3d(path = string) end
```

## Destroy Audio

```lua
function engine.audio.destroy(id = number) end
```

## Pause/Resume Audio

```lua
function engine.audio.pause(id = number) end
function engine.audio.resume(id = number) end
```

## Restart Audio

```lua
function engine.audio.restart(id = number) end
```

## Stop Audio

```lua
function engine.audio.stop(id = number) end
```

## Check if audio has finished playing

```lua
function engine.audio.is_finished(id = number) end
```

## Get/Set the position of the audio

Returns vec3

```lua
function engine.audio.get_position(id = number) end
function engine.audio.set_position(id = number, vec3) end
```
## Get/Set the velocity of playing 

```lua
function engine.audio.set_velocity(id = number, vec3) end
function engine.audio.get_velocity(id = number) end
```

## Get/Set the audio to play in loop

```lua
function engine.audio.set_loop(id = number, bool) end
function engine.audio.get_loop(id = number) end
```

## Get/Set the minimal distance

Changes the distance at which the 3D sound stops getting louder

```lua
function engine.audio.set_min_distance(id, number) end
function engine.audio.get_min_distance(id) end
```

## Get/Set the max distance

This value causes the sound to stop attenuating after it reaches the max distance

```lua
function engine.audio.set_max_distance(id, number) end
function engine.audio.get_max_distance(id) end
```

## Get/Set the max distance

The balance of the sound, value between -1 and 1

```lua
function engine.audio.set_pan(id, number) end
function engine.audio.get_pan(id) end
```

## Get/Set the speed

Plays the sound at a higher or lower speed, increasing or decreasing its frequency which makes it sound lower or higher

```lua
function engine.audio.set_speed(id, number) end
function engine.audio.get_speed(id) end
```

## Get the play max length

Returns the play lenght of the audio (number)

```lua
function engine.audio.get_length(id) end
```

## Get/Set the position of playing of the audio (0 to max)

```lua
function engine.audio.set_play_position(id, number) end
function engine.audio.get_play_position(id) end
```

## Get/Set the audio volume

```lua
function engine.audio.set_volume(id, number) end
function engine.audio.get_volume(id) end
```

## Stop all audios

Stop all audios

```lua
function engine.audio.stop_all_audios() end
```

## Set the position of the listener in the world (global)

```lua
function engine.audio.set_listener_position(vec3) end
```

# Font Module

## Create Font

Returns id if success, else return nil

Width and height in pixels, use 0 to one of it to adapt based on the another

```lua
function engine.font.create(path = string, width = number, height = number) end
```

## Destroy Font

```lua
function engine.font.destroy(id = number) end
```

## Get/Set Position

```lua
function engine.font.get_position(id = number) end
function engine.font.set_position(id = number, pos = vec2) end

```

## Get/Set Scale

```lua
function engine.font.get_scale(id = number) end
function engine.font.set_scale(id = number, scale = vec2) end
```

## Get/Set Color

```lua
function engine.font.get_color(id = number) end
function engine.font.set_color(id = number, color = vec3) end
```

## Get text Size
Returns a Vec2 with the current text size in pixels

```lua
function engine.font.get_text_size_(id = number) end
```

## Get/Set Text

```lua
function engine.font.get_text(id = number) end
function engine.font.set_text(id = number, text = string) end
```

## Draw Font

```lua
function engine.font.draw(id = number) end
```

# Math Module

## Random number

Return a random number between 0.0 and 1.0

```lua
function engine.math.random() 
```

## Make vec2 

Return a vec2

```lua
function engine.math.make_vec2() 
```

## Make vec3 

Return a vec3

```lua
function engine.math.make_vec3() 

eturn a vec2

```lua
function engine.math.make_vec2() 
```

## Make mat2 

Return a mat2 matrix

```lua
function engine.math.make_mat2() 
```

## Make mat3

Return a mat3

```lua
function engine.math.make_mat3() 
```

## Make mat4

Return a mat4 matrix

```lua
function engine.math.make_mat4() 
```

## Make mat2 identity

Return a mat2 identity matrix

```lua
function engine.math.make_identity_mat2() 
```

## Make mat3 identity

Return a mat3 identity matrix

```lua
function engine.math.make_identity_mat3() 
```

## Make mat4 identity

Return a mat4 identity matrix

```lua
function engine.math.make_identity_mat4() 
```

## Translate

Return a traslated mat4 matrix

```lua
function engine.math.translate(mat4, vec3) 
```

## Rotate 

Return a rotated mat4 matrix

```lua
function engine.math.rotate(mat4, vec3, angle) 
```

## Scale 

Return a scaled mat4 matrix

```lua
function engine.math.scale(mat4, vec3) 
```

## Multiply 

Return a vec4 that is the multiplication between a mat4 and vec4

```lua
function engine.math.multiply(mat4, vec4) 
```

## Magnitude Vec2 

Return the magnitude of a vec2

```lua
function engine.math.mag_vec2(vec2) 
```

## Magnitude Vec3 

Return the magnitude of a vec3

```lua
function engine.math.mag_vec3(vec3) 
```

## Normalize Vec2 

Return the normalized vec2

```lua
function engine.math.normalize_vec2(vec2) 
```

## Normalize Vec3 

Return the normalized vec3

```lua
function engine.math.normalize_vec3(vec3)
```

# Object Module

## Open 3D Model

Open any 3d model and return the id

```lua
function engine.object.open(path = string) 
```

## Destroy 3D Model

Destroy 3d model by recieving it's id

```lua
function engine.object.destroy(id = number) 
```

## Get 3D Model information

Return a tabe with 3d model information

```lua
function engine.object.get(id = number) 
```

## Get 3D Model meshes

Return a tabe with the information about the meshes of the model

```lua
function engine.object.get_meshes(id = number) 
```

## Get 3D Model meshes

Return a tabe with the information about the materials of the model

```lua
function engine.object.get_materials(id = number) 
```