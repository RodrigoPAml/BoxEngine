# Basic Module

## Log
Log into the console
```lua
function log(message = string) end
```

## Warning
Log a warning into the console
```lua
function warn(message = string) end
```

## Error
Log an error into the console
```lua
function error(message = string) end
```

## To String
Transform any data type into a string and return it
```lua
function to_string(object = any) end
```

# Utils Module

## Get FPS
Return a number with current fps
```lua
function utils.get_fps() end
```

## Get Frame Time
Return a number with current frametime
```lua
function utils.get_frametime() end
```

# Time Module

## Get Timestamp
Return a number with the timestamp in seconds since application started
```lua
function time.get_timestamp() end
```

## Get Date Time 
Return a table with current date
```lua
function time.get_datetime() end
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
function go.current() end
```

## Create Go
Create a gameobject

Returns the id in case of success else return nil
```lua
function go.create(arg = table) end
```

Argument table format
```lua
{
    name = string, -- optional
    active = boolean, -- optional
    father_id = number, -- the id of the father go, also optional
}
```

## Destroy Go
Destroy a gameobject, pass the id by argument

Returns a boolean indicating success 
```lua
function go.destroy(id = number) end
```

## Get Go
Get a gameobject, pass the id by argument

Return a table with the go information if find it, else return nil
```lua
function go.get(id = number) end
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

## Update Go
Update a gameobject, pass the table by argument with update information

Return a boolean indicating success
```lua
function go.update(arg = table) end
```

The argument table format
```lua
{
    name = string, -- optional
    active = boolean, -- optional
}
```

## Change Go Father
Change the gameobject father

The second argument is optional, is not informed the go is set to the root

Return a boolean indicating success
```lua
function go.change_father(goId = string, fatherId = string) end
```

## Change Go Index
Change the gameobject index in relation to his brothers

The displacement argument changes the index based on the current index

```lua
function go.change_index(goId = string, displacement = number) end
```

# Script Module

## Get Script
Get the script information from a gameobject

If not find it then return nil
```lua
function script.get(goId = number, scriptName = string) end
```

The returned table format
```lua
{
    name = string,  -- script name
    path = string, -- loaded path
    state = string, -- state of the script, see ScriptStateEnum ins Enums section below
    is_started = boolean, -- if the Start() function of the script was called
}
```

## Add Script
Add the script into a gameobject

Return a boolean indicating success
```lua
function script.add(goId = number, scriptName = string) end
```

## Remove Script
Remove the script of a gameobject

Return a boolean indicating success
```lua
function script.remove(goId = number, scriptName = string) end
```

## Change Script Index
Change the script index in relation to his brothers

The displacement argument changes the index based on the current index

```lua
function script.change_index(goId = string, scriptName = string, displacement = number) end
```

# Camera 2D Module

## Create 2D Camera
Create a 2D camera and return an id

```lua
function cam2d.create(object = table) end
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
function cam2d.destroy(id = number) end
```

## Get 2D Camera
Get a 2D camera

Recieve the camera id and return a table or nil if not find it
```lua
function cam2d.get(id = number) end
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
function cam2d.get_matrix(id = number) end
```

The returned table format is a mat4
```lua
{
    1 = {{x = number, y =number, z =number, w =number}},
    2 = {{x = number, y =number, z =number, w =number}},
    3 = {{x = number, y =number, z =number, w =number}},
    4 = {{x = number, y =number, z =number, w =number}}
}
```

## Update 2D Camera
Update a 2D camera

Recieve the camera id and a table with update info

Return a bool indicating success
```lua
function cam2d.update(id = number, info = table) end
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
function cam2d.set_current(id = number) end
```

# Camera 3D Module

## Create 3D Camera
Create a 3D camera and return an id

```lua
function cam3d.create(object = table) end
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
function cam3d.destroy(id = number) end
```

## Update 3D Camera
Update a 3D camera and return an bool indicating sucess

Recieve the camera id and a table with update info
```lua
function cam3d.update(id = number, object = table) end
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

Recieve the camera id and a table with update info
```lua
function cam3d.get(id = number, object = table) end
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
function cam3d.translate(id = number, object = table) end
```

The argument table format
```lua
{
    direction = string, -- direction in the format CameraMovement (see the last module below)
    velocity = number, -- the velocity of translation
}
```

## Translate Absolute 3D Camera
Translate a 3D camera relation to the axis and return an bool indicating success

Recieve the camera id and a table with translation info
```lua
function cam3d.translate_abs(id = number, object = table) end
```

The argument table format
```lua
{
    direction = string, -- direction in the format CameraMovement (see the last module below)
    velocity = number, -- the velocity of translation
}
```

## Rotate 3D Camera
Rotate a 3D camera and return an bool indicating success

Recieve the camera id and a table with rotation info
```lua
function cam3d.rotate(id = number, object = table) end
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
function cam3d.get_view_matrix(id = number) end
```

The returned table format
```lua
{
    1 = {{x = number, y =number, z =number, w =number}},
    2 = {{x = number, y =number, z =number, w =number}},
    3 = {{x = number, y =number, z =number, w =number}},
    4 = {{x = number, y =number, z =number, w =number}}
}
```

## Get Projection Matrix
Recieve the camera id and return the projection matrix in mat4 format

Return nil if not find it

```lua
function cam3d.get_projection_matrix(id = number) end
```

The returned table format
```lua
{
    1 = {{x = number, y =number, z =number, w =number}},
    2 = {{x = number, y =number, z =number, w =number}},
    3 = {{x = number, y =number, z =number, w =number}},
    4 = {{x = number, y =number, z =number, w =number}}
}
```

## Set Current Camera
Recieve the camera id and set as current camera

Return a bool indicating success
```lua
function cam3d.set_current(id = number) end
```

# Drawing Module

## Draw 2D Rect
Draw a 2D rectangle

```lua
function draw2d.rect(object = table) end
```

The argument table format
```lua
{
    position = {x =number, y =number}, -- position, vec2 format
    size = {x =number, y =number}, -- size, vec2 format
    color = {x =number, y =number, z =number}, -- color, vec3 format, optional
    rotation = number, -- rotation in degrees, optional
    filled = boolean, -- fill or not the shape, optional
}
```

## Draw 2D Circle
Draw a 2D circle

```lua
function draw2d.circle(object = table) end
```

The argument table format
```lua
{
    position = {x =number, y =number}, -- position, vec2 format
    size = {x =number, y =number}, -- size, vec2 format
    color = {x =number, y =number, z =number}, -- color, vec3 format, optional
    rotation = number, -- rotation in degrees, optional
    filled = boolean, -- fill or not the shape, optional
}
```

## Draw 2D Triangle
Draw a 2D triangle

```lua
function draw2d.triangle(object = table) end
```

The argument table format
```lua
{
    position = {x =number, y =number}, -- position, vec2 format
    size = {x =number, y =number}, -- size, vec2 format
    color = {x =number, y =number, z =number}, -- color, vec3 format, optional
    rotation = number, -- rotation in degrees, optional
    filled = boolean, -- fill or not the shape, optional
}
```

## Draw 2D Line
Draw a 2D line

```lua
function draw2d.line(object = table) end
```

The argument table format
```lua
{
    position_start = {x =number, y =number}, -- start position, vec2 format
    position_end = {x =number, y =number}, -- end position, vec2 format
    color = {x =number, y =number, z =number}, -- color, vec3 format, optional
}
```

## Draw 2D Point
Draw a 2D point

```lua
function draw2d.point(object = table) end
```

The argument table format
```lua
{
    position = {x =number, y =number}, -- position, vec2 format
    color = {x =number, y =number, z =number}, -- color, vec3 format, optional
}
```

## Draw 2D Texture
Draw a 2d texture

```lua
function draw2d.texture(object = table) end
```

The argument table format
```lua
{
    position = {x =number, y =number}, -- position, vec2 format
    size = {x =number, y =number}, -- size, vec2 format
    texture_id = number, the texture id
    rotation = number, -- rotation in degrees, optional
}
```

## Draw 3D Cube
Draw a 3D cube

```lua
function draw3d.cube(object = table) end
```

The argument table format
```lua
{
    position = {x =number, y =number = z =number}, -- position, vec3 format
    size = {x =number, y =number = z =number}, -- size, vec3 format
    color = {x =number, y =number, z =number}, -- color, vec3 format, optional
    rotation = {x =number, y =number, z =number}, -- rotation in degrees in vec3 format, optional
    filled = boolean, -- fill or not the shape, optional
}
```

## Draw 3D Sphere
Draw a 3D sphere

```lua
function draw3d.sphere(object = table) end
```

The argument table format
```lua
{
    position = {x =number, y =number = z =number}, -- position, vec3 format
    size = {x =number, y =number = z =number}, -- size, vec3 format
    color = {x =number, y =number, z =number}, -- color, vec3 format, optional
    rotation = {x =number, y =number, z =number}, -- rotation in degrees in vec3 format, optional
    filled = boolean, -- fill or not the shape, optional
}
```

## Draw 3D Point
Draw a 3D point

```lua
function draw3d.point(object = table) end
```

The argument table format
```lua
{
    position = {x =number, y =number = z =number}, -- position, vec3 format
    color = {x =number, y =number, z =number}, -- color, vec3 format, optional
}
```

## Draw 3D Line
Draw a 3D line

```lua
function draw3d.line(object = table) end
```

The argument table format
```lua
{
    position_start = {x =number, y =number = z =number}, -- position start, vec3 format
    position_end = {x =number, y =number = z =number}, -- position end, vec3 format
    color = {x =number, y =number, z =number}, -- color, vec3 format, optional
}
```

## Draw 3D Rect
Draw a 3D rect

```lua
function draw3d.rect(object = table) end
```

The argument table format
```lua
{
    position = {x =number, y =number = z =number}, -- position, vec3 format
    size = {x =number, y =number = z =number}, -- size, vec3 format
    color = {x =number, y =number, z =number}, -- color, vec3 format, optional
    rotation = {x =number, y =number, z =number}, -- rotation in degrees in vec3 format, optional
    filled = boolean, -- fill or not the shape, optional
}
```

## Draw 3D Triangle
Draw a 3D triangle

```lua
function draw3d.triangle(object = table) end
```

The argument table format
```lua
{
    position = {x =number, y =number = z =number}, -- position, vec3 format
    size = {x =number, y =number = z =number}, -- size, vec3 format
    color = {x =number, y =number, z =number}, -- color, vec3 format, optional
    rotation = {x =number, y =number, z =number}, -- rotation in degrees in vec3 format, optional
    filled = boolean, -- fill or not the shape, optional
}
```

## Draw 3D Circle
Draw a 3D circle

```lua
function draw3d.circle(object = table) end
```

The argument table format
```lua
{
    position = {x =number, y =number = z =number}, -- position, vec3 format
    size = {x =number, y =number = z =number}, -- size, vec3 format
    color = {x =number, y =number, z =number}, -- color, vec3 format, optional
    rotation = {x =number, y =number, z =number}, -- rotation in degrees in vec3 format, optional
    filled = boolean, -- fill or not the shape, optional
}
```

# Window Module

## Get Window Size
Return a table with current window size

```lua
function window.getwindowsize() end
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
function window.get_editorwindowsize() end
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
function window.getwindowlimits() end
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
function dir.read_file(file_name = string) end
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
function dir.create_file(file_name = string, content = string) end
```

## Create Folder
Create a folder and return a bool indicating success

```lua
function dir.create_folder(folder_name = string) end
```

## Move
Move a folder or file and return a bool indicating success

```lua
function dir.move(from = string, to = string) end
```

## Copy
Copy a folder or file and return a bool indicating success

```lua
function dir.copy(from = string, to = string) end
```

## Delete
Delete a folder or file and return a bool indicating success

```lua
function dir.delete(path = string) end
```

## Is File
Return a bool indicating if the provided path is a file

```lua
function dir.is_file(path = string) end
```

## Is Directory
Return a bool indicating if the provided path is a directory

```lua
function dir.is_dir(path = string) end
```

## Exists
Return a bool indicating if the provided path/file exists

```lua
function dir.exists(path = string) end
```

## Get Current Path
Return the executable path

```lua
function dir.get_current_path() end
```

## Get Base Path
Return the base project path

```lua
function dir.get_base_path() end
```

## Get Assets Path
Return the assets path

```lua
function dir.get_assets_path() end
```

## Get Logs Path
Return the logs path

```lua
function dir.get_logs_path() end
```

## List Directories
Return the an table with the content of a directory, if not exists return nil

```lua
function dir.list_dir(path = string) end
```

## Reduce Path By
Reduce a path n times and return it

```lua
function dir.reduce_path_by(path = string, n = number) end
```

## Get File Name Extension
Recieve a file path and return the extension

```lua
function dir.get_file_name_ext(path = string) end
```

## Get Path Or File Name
Recieve a file or dir path and return only its name

```lua
function dir.get_path_or_file_name(path = string) end
```

## Get File Name No Extension
Recieve a file path and return only its name without extension

```lua
function dir.get_file_name_no_ext(path = string) end
```

# Input Module

## Get Keyboard Key
Get the key status

Argument is a string in KeyboardKey format (see last chapter below)

Return the result as a string in InputAction format (see last chapter below)

```lua
function input.get_key(key = string) end
```

## Get Modifier Key
Get the modifier key status

Argument is a string in KeyModifier format (see last chapter below)

Return the result as a string in InputAction format (see last chapter below)

```lua
function input.get_mod(key = string) end
```

## Get Mouse Position
Return a vec2 with mouse coordinates

```lua
function input.get_mouse_pos() end
```

## Get Mouse Variation
Return a vec2 with mouse variations

```lua
function input.get_mouse_variation() end
```

## Get Mouse Button
Get the mouse button status

Argument is a string in MouseButton format (see last chapter below)

Return the result as a string in InputAction format (see last chapter below)

```lua
function input.get_mouse_button(key = string) end
```

# Image Module

## Open
Open a image and return its info

Argument is a string with path

Return the result as a table or nil if failed

```lua
function img.open(path = string) end
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
function command.enable_vsync() end
```

## Disable VSync
Disables the vsync

```lua
function command.disable_vsync() end
```

## Enable Depth Testing
Enables the depth testing

```lua
function command.enable_depth_testing() end
```

## Disable Depth Testing
Disables the depth testing

```lua
function command.disable_depth_testing() end
```

## Set Depth Testing Mode
Set the depth testing mode, receive a string in Depth Testing Mode format (see below enums)

```lua
function command.set_depth_testing_mode(mode = string) end
```

## Enable Culling Face
Enable the face culling

```lua
function command.enable_culling_face() end
```

## Disable Culling Face
Disable the face culling

```lua
function command.disable_culling_face() end
```
## Set Culling Face Mode
Set the face culling mode with Culling Face Mode format (see enums below)

```lua
function command.set_culling_face_mode(mode = string) end
```

## Set Primitive Line Size
Set the primitive Line size, recieve as argument with number type

```lua
function command.set_primitive_line_size(size = number) end
```

## Set Primitive Point Size
Set the primitive point size, recieve as argument with number type

```lua
function command.set_primitive_point_size(size = number) end
```

## Set Polygon Draw Mode
Set the polygons draw mode in Polygon Mode string format (see enums below)

```lua
function command.set_polygon_draw_mode(mode = string) end
```

## Enable Blending
Enables the blending

```lua
function command.enable_blending() end
```

## Disable Blending
Disables the blending

```lua
function command.disable_blending() end
```

# Shader Module

## Create Shader
Create a shader, receive a table with creation information

Return id if success else return nil
```lua
function shader.create(arg = table) end
```
The argument table format
```lua
{
    vertex_path = string -- path to vertex shader file
    fragment_path = string, -- path to the fragment shader file (optional)
    geometry_path = string  -- path to the geometry shader file (optional)
}
```

## Delete Shader
Delete a shader, receive the id

Return bool indicating success
```lua
function shader.destroy(id = number) end
```

## Activate Shader
Activate a shader, receive the id

Return bool indicating success
```lua
function shader.activate(id = number) end
```

## Disable Current Shader
Disable the current active shader

```lua
function shader.unactive_all() end
```

## Set Shader Bool
Set bool variable into shader, receive the id and data information

Return bool indicating success
```lua
function shader.set_bool(id = number, name = string, value = bool) end
```

## Set Shader Integer
Set integer variable into shader, receive the id and data information

Return bool indicating success
```lua
function shader.set_int(id = number, name = string, value = number) end
```

## Set Shader Float
Set float variable into shader, receive the id and data information

Return bool indicating success
```lua
function shader.set_float(id = number, name = string, value = number) end
```

## Set Shader XY
Set XY (separated vec2) variable into shader, receive the id and data information

Return bool indicating success
```lua
function shader.set_xy(id = number, name = string, x = number, y = number) end
```

## Set Shader XYZ
Set XYZ (separated vec3) variable into shader, receive the id and data information

Return bool indicating success
```lua
function shader.set_xyz(id = number, name = string, x = number, y = number, z = number) end
```

## Set Shader XYZW
Set XYZW (separated vec4) variable into shader, receive the id and data information

Return bool indicating success
```lua
function shader.set_xyzw(id = number, name = string, x = number, y = number, z = number, w = number) end
```

## Set Shader vec2
Set a vec2 variable into shader, receive the id and data information

Return bool indicating success
```lua
function shader.set_vec2(id = number, name = string, {x = number, y = number}) end
```

## Set Shader vec3
Set vec3 variable into shader, receive the id and data information

Return bool indicating success
```lua
function shader.set_vec3(id = number, name = string, {x = number, y = number, z = number}) end
```

## Set Shader vec4
Set vec4 variable into shader, receive the id and data information

Return bool indicating success
```lua
function shader.set_vec4(id = number, name = string, { x = number, y = number, z = number, w = number}) end
```

## Set Shader mat2
Set mat2 variable into shader, receive the id and data information

Return bool indicating success
```lua
function shader.set_mat2(id = number, name = string, mat2 = table) end
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
function shader.set_mat3(id = number, name = string, mat3 = table) end
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
function shader.set_mat4(id = number, name = string, mat4 = table) end
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
function texture.create_empty(arg = table) end
```
The argument table format
```lua
{
    texture_size = {x = number, y = number}, -- texture size, vec2 format
    minifying_filter = string, -- in Minifying Filter format (see enums below) optional
    magnification_filter = string, -- in Magnification Filter format (see enums below) optional
    texture_wrap_t = string, -- in Texture Wrap format (see enums below) optional
    texture_wrap_s = string, -- in Texture Wrap format (see enums below) optional
    texture_pixel_format = string, -- in Texture Pixel Format (see enums below) optional
    texture_internal_format = string, -- in Texture Internal Format (see enums below) optional
    texture_format = string, -- in Texture Format (see enums below) optional
    ansiotropic_filter = number, -- a number for ansiotropic filter, optional
    border_color = {x = number, y = number, z = number} -- texture border_color in vec3 format, optional
}
```

## Create Texture
Create a texture, receive a table with creation information

Return id if success else return nil
```lua
function texture.create(arg = table) end
```
The argument table format
```lua
{
    image_path = string, -- image path
    minifying_filter = string, -- in Minifying Filter format (see enums below) optional
    magnification_filter = string, -- in Magnification Filter format (see enums below) optional
    texture_wrap_t = string, -- in Texture Wrap format (see enums below) optional
    texture_wrap_s = string, -- in Texture Wrap format (see enums below) optional
    ansiotropic_filter = number, -- a number for ansiotropic filter, optional
    border_color = {x = number, y = number, z = number} -- texture border_color in vec3 format, optional
}
```

## Destroy Texture
Destroy a texture, receive the id

Return bool indicating success
```lua
function texture.destroy(id = number) end
```

## Active Texture
Active a texture, receive the id and the texture unit slot as a number

Return bool indicating success
```lua
function texture.active(id = number, slot = number) end
```

## Disable Texture Unit
Remove any texture at a texture unit slot

```lua
function texture.disabletextureunit(slot = number) end
```

# Framebuffer Module

## Create Framebuffer
Create a framebuffer, receive a table with creation information

Return id if success else return nil
```lua
function framebuffer.create(arg = table) end
```
The argument table format
```lua
{
    texture_attachments_count = number, -- number of texture attachments,
    texture_attachments = = {1 = number, ..., texture_count = number} -- table with the ids of the texture attachments,
    depth_attachment = number, -- texture id for depth attachment, optional
    renderbuffer_attachment = { -- optional
        type = string -- in Render Buffer Attachment Type format (see enums below),
        format = string -- in Render Buffer Format (see enums below),
        size = {x = number, y = number} -- render buffer size
    }
}
```

## Destroy Framebuffer
Destroy a framebuffer, receive the id

Return bool indicating success
```lua
function framebuffer.destroy(id = number) end
```

## Active Framebuffer
Active a framebuffer, receive the id

Return bool indicating success
```lua
function framebuffer.active(id = number) end
```

## Active Default Framebuffer
Active the default screen buffer of the window

```lua
function framebuffer.active_default() end
```

## Get Framebuffer Attachments Size
Receive the framebuffer id and return a framebuffer number of texture attachments, else nil if not finded

```lua
function framebuffer.get_attachments_size(id = number) end
```

## Get Framebuffer Attachment
Receive the framebuffer id and the texture attachment position

Return the id of the texture attachment, else nil if not finded
```lua
function framebuffer.get_attachment(id = number, index = number) end
```

## Set Current Framebuffer 
Receive the framebuffer id and the set as current used

Return the bool indicating success
```lua
function framebuffer.set_current(id = number, index = number) end
```

## Get Current Framebuffer 
Get the current framebuffer id 

Return the id if exists, else nil
```lua
function framebuffer.get_current() end
```

## Clear Current Framebuffer
Clear the current framebuffer

```lua
function framebuffer.clear(color = vec4) end
```

## Set Framebuffer Clear Modes
Set the framebuffer clear modes

```lua
function framebuffer.set_clear_modes(modes = table) end
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
function framebuffer.set_viewport(viewport = table) end
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
function vertex.create(vertexData = table, indexData = table) end
```
The first argument table format
```lua
{
    vertices_count = number, -- the total number of vertices, considering the attributes of each vertex
    buffers_count = number, -- the number of buffers that will be used to separate the vertices attributes
    buffers = { -- the buffers that holds the vertices data
        1 = { -- buffer item format
            use = string, -- (optional) use internally by opengl in Data Use format (see enums below)
            type = string, -- type of the data, use Vertex Buffer Type
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
function vertex.destroy(id = number) end
```

## Activate Vertex Data
Activate a vertex data, receive the id

Return bool indicating success
```lua
function vertex.activate(id = number) end
```

## Call to Draw Vertex Data
Draw a vertex data, receive the id and draw mode

drawMode is in Drawing Type format (see enums below)

Return bool indicating success
```lua
function vertex.draw(id = number, drawMode = string) end
```

## Modify Vertex Data
Modify a vertex data, receive the id and modification data as a table

Return bool indicating success
```lua
function vertex.modify(id = number, modifyData = table) end
```

The argument table format
```lua
{
    start = number, -- the start position to be modified
    size = number, -- the size of modification
    buffer = number, -- with buffer to modified
    type = string,  -- type of the data, format Vertex Buffer Type
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
function generator.gen_2d_point(dataUse = string) end
function generator.gen_2d_line(dataUse = string, filled = bool) end
function generator.gen_2d_circle(dataUse = string, filled = bool, segments = number) end
function generator.gen_2d_triangle(dataUse = string, filled = bool) end
```

## Generate 3D meshes
Return id of vertex data

dataUse argument is in Data Use format (see enums below)

```lua
function generator.gen_3d_circle(dataUse = string, filled = bool, segments = number) end
function generator.gen_3d_cube(dataUse = string, filled = bool) end
function generator.gen_3d_line(dataUse = string) end
function generator.gen_3d_point(dataUse = string) end
function generator.gen_3d_rect(dataUse = string, filled = bool) end
function generator.gen_3d_sphere(dataUse = string, filled = bool, segments = number) end
function generator.gen_3d_triangle(dataUse = string, filled = bool) end
```

# Audio Module

## Create Audio

Returns id if success, else return nil

```lua
function audio.create2D(path = string) end
function audio.create3D(path = string) end
```

## Destroy Audio

```lua
function audio.destroy(id = number) end
```

## Pause/Resume Audio

```lua
function audio.pause(id = number) end
function audio.resume(id = number) end
```

## Check if audio has finished playing

```lua
function audio.is_finished(id = number) end
```

## Get/Set the position of the audio

Returns vec3

```lua
function audio.get_position(id = number) end
function audio.set_position(id = number, vec3) end
```
## Get/Set the velocity of playing 

```lua
function audio.set_velocity(id = number, vec3) end
function audio.get_velocity(id = number) end
```

## Get/Set the audio to play in loop

```lua
function audio.set_loop(id = number, bool) end
function audio.get_loop(id = number) end
```

## Get/Set the minimal distance

Changes the distance at which the 3D sound stops getting louder

```lua
function audio.set_min_distance(id, number) end
function audio.get_min_distance(id) end
```

## Get/Set the max distance

This value causes the sound to stop attenuating after it reaches the max distance

```lua
function audio.set_max_distance(id, number) end
function audio.get_max_distance(id) end
```

## Get/Set the max distance

The balance of the sound, value between -1 and 1

```lua
function audio.set_pan(id, number) end
function audio.get_pan(id) end
```

## Get/Set the speed

Plays the sound at a higher or lower speed, increasing or decreasing its frequency which makes it sound lower or higher

```lua
function audio.set_speed(id, number) end
function audio.get_speed(id) end
```

## Get the play max length

Returns the play lenght of the audio (number)

```lua
function audio.get_length(id) end
```

## Get/Set the position of playing of the audio (0 to max)

```lua
function audio.set_play_position(id, number) end
function audio.get_play_position(id) end
```

## Get/Set the audio volume

```lua
function audio.set_volume(id, number) end
function audio.get_volume(id) end
```

## Set the position of the listener in the world (global)

```lua
function audio.set_listener_position(vec3) end
```

# Enums

## Script State

```C++
{
    TO_LOAD, // Script needs to be loaded
    TO_START, // Script needs to start (and its loaded)
    UPDATING, // Script is running (and its started)
    TO_DESTROY, // Script needs to be destroy (and its started or updating)
    DESTROYED // Script is destroyed (destroyed)
};
```

## Camera Movement

```C++
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};
```

## Keyboard Key

```C++
{
    KEY_UNKNOWN,
    KEY_SPACE,
    KEY_APOSTROPHE,
    KEY_COMMA,
    KEY_MINUS,
    KEY_PERIOD,
    KEY_SLASH,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_SEMICOLON,
    KEY_EQUAL,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_LEFT_BRACKET,
    KEY_BACKSLASH,
    KEY_RIGHT_BRACKET,
    KEY_GRAVE_ACCENT,
    KEY_WORLD_1,
    KEY_WORLD_2,
    KEY_ESCAPE,
    KEY_ENTER,
    KEY_TAB,
    KEY_BACKSPACE,
    KEY_INSERT,
    KEY_DELETE,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_DOWN,
    KEY_UP,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    KEY_HOME,
    KEY_END,
    KEY_CAPS_LOCK,
    KEY_SCROLL_LOCK,
    KEY_NUM_LOCK,
    KEY_PRINT_SCREEN,
    KEY_PAUSE,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_F13,
    KEY_F14,
    KEY_F15,
    KEY_F16,
    KEY_F17,
    KEY_F18,
    KEY_F19,
    KEY_F20,
    KEY_F21,
    KEY_F22,
    KEY_F23,
    KEY_F24,
    KEY_F25,
    KEY_KP_0,
    KEY_KP_1,
    KEY_KP_2,
    KEY_KP_3,
    KEY_KP_4,
    KEY_KP_5,
    KEY_KP_6,
    KEY_KP_7,
    KEY_KP_8,
    KEY_KP_9,
    KEY_KP_DECIMAL,
    KEY_KP_DIVIDE,
    KEY_KP_MULTIPLY,
    KEY_KP_SUBTRACT,
    KEY_KP_ADD,
    KEY_KP_ENTER,
    KEY_KP_EQUAL,
    KEY_LEFT_SHIFT,
    KEY_LEFT_CONTROL,
    KEY_LEFT_ALT,
    KEY_LEFT_SUPER,
    KEY_RIGHT_SHIFT,
    KEY_RIGHT_CONTROL,
    KEY_RIGHT_ALT,
    KEY_RIGHT_SUPER,
    KEY_MENU,
};
```

## Input Action

```C++
{
    RELEASE,
    PRESS,
    REPEAT,
    NONE
};
```

## Key Modifier

```C++
{
    SHIFT,
    CONTROL,
    ALT,
    SUPER,
    CAPS_LOCK,
    NUM_LOCK,
    UNKNOWN
};
```

## Mouse Button
```C++
{
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE,
    MOUSE_BUTTON_1,
    MOUSE_BUTTON_2,
    MOUSE_BUTTON_3,
    MOUSE_BUTTON_4,
    MOUSE_BUTTON_5,
    MOUSE_BUTTON_6,
    MOUSE_BUTTON_7,
    MOUSE_BUTTON_8
};
```

## Data Use Key
```C++
{
	STREAM_DRAW,
	STREAM_READ,
	STREAM_COPY,
	STATIC_DRAW,
	STATIC_READ,
	STATIC_COPY,
	DYNAMIC_READ,
	DYNAMIC_COPY
};
```

## Polygon Mode
```C++
{
	POINT,
	LINE,
	FILL,
};
```

## Depth Testing Mode
```C++
{
	ALWAYS,
	NEVER,
	LESS,
	LEQUAL,
	GREATER,
	NOTEQUAL,
	GEQUAL
};
```

## Culling Face Mode
```C++
{
	BACK,
	FRONT,
	BOTH,
};
```

## Texture Internal Format
```C++
{
	DEPTH_COMPONENT,
	DEPTH_STENCIL,
	R,
	RG,
	RGB,
	RGBA,
	R8,
	R8_SNORM,
	R16,
	R16_SNORM,
	RG8,
	RG8_SNORM,
	RG16,
	RG16_SNORM,
	R3_G3_B2,
	RGB4,
	RGB5,
	RGB8_SNORM,
	RGB10,
	RGB12,
	RGB16_SNORM,
	RGBA2,
	RGBA4,
	RGB5_A1,
	RGBA8,
	RGBA8_SNORM,
	RGB10_A2,
	RGB10_A2UI,
	RGBA12,
	RGBA16,
	SRGB8,
	SRGB8_ALPHA8,
	R16F,
	RG16F,
	RGB16F,
	RGBA16F,
	R32F,
	RG32F,
	RGB32F,
	RGBA32F,
	R11F_G11F_B10F,
	RGB9_E5,
	R8I,
	R8UI,
	R16I,
	R16UI,
	R32I,
	R32UI,
	RG8I,
	RG8UI,
	RG16I,
	RG16UI,
	RG32I,
	RG32UI,
	RGB8I,
	RGB8UI,
	RGB16I,
	RGB16UI,
	RGB32I,
	RGB32UI,
	RGBA8I,
	RGBA8UI,
	RGBA16I,
	RGBA16UI,
	RGBA32I,
	RGBA32UI,
	COMPRESSED_RED,
	COMPRESSED_RG,
	COMPRESSED_RGB,
	COMPRESSED_RGBA,
	COMPRESSED_SRGB,
	COMPRESSED_SRGB_ALPHA,
	COMPRESSED_RED_RGTC1,
	COMPRESSED_SIGNED_RED_RGTC1,
	COMPRESSED_RG_RGTC2,
	COMPRESSED_SIGNED_RG_RGTC2,
};
```

## Texture Format
```C++
{
	R,
	RG,
	RGB,
	BGR,
	RGBA,
	BGRA,
	RED_INTEGER,
	RG_INTEGER,
	RGB_INTEGER,
	BGR_INTEGER,
	RGBA_INTEGER,
	BGRA_INTEGER,
	STENCIL_INDEX,
	DEPTH_COMPONENT,
	DEPTH_STENCIL,
};
```
	
## Texture Pixel Format
```C++
{
	UNSIGNED_BYTE,
	BYTE,
	UNSIGNED_SHORT,
	SHORT,
	UNSIGNED_INT,
	INT,
	HALF_FLOAT,
	FLOAT,
	UNSIGNED_BYTE_3_3_2,
	UNSIGNED_BYTE_2_3_3_REV,
	UNSIGNED_SHORT_5_6_5,
	UNSIGNED_SHORT_5_6_5_REV,
	UNSIGNED_SHORT_4_4_4_4,
	UNSIGNED_SHORT_4_4_4_4_REV,
	UNSIGNED_SHORT_5_5_5_1,
	UNSIGNED_SHORT_1_5_5_5_REV,
	UNSIGNED_INT_8_8_8_8,
	UNSIGNED_INT_8_8_8_8_REV,
	UNSIGNED_INT_10_10_10_2,
	UNSIGNED_INT_2_10_10_10_REV
};
```

## Minifying Filter
```C++
{
	ONLY_NEAREST,
	ONLY_LINEAR,
	NEAREST_MIPMAP_NEAREST,
	LINEAR_MIPMAP_NEAREST,
	NEAREST_MIPMAP_LINEAR,
	LINEAR_MIPMAP_LINEAR
};
```

## Magnification Filter
```C++
{
	NEAREST,
	LINEAR
};
```

## Texture Wrap
```C++
{
	CLAMP_TO_EDGE,
	CLAMP_TO_BORDER,
	MIRRORED_REPEAT,
	REPEATED,
	MIRROR_CLAMP_TO_EDGE
};	
```

## Vertex Buffer Type
```C++
{
	BYTE,
	UBYTE,
	SHORT,
	USHORT,
	INT,
	UINT,
	HALF_FLOAT,
	FLOAT,
	DOUBLE,
	INT_2_10_10_10_REV,
	UINT_2_10_10_10_REV
};
```

## Drawing Type
```C++
{
	POINTS,
	LINES,
	LINE_LOOP,
	LINE_STRIP,
	TRIANGLES,
	TRIANGLE_STRIP,
	TRIANGLE_FAN,
	LINE_ADJACENCY,
	LINE_STRIP_ADJACENCY,
	TRIANGLES_ADJACENCY,
	TRIANGLE_STRIP_ADJACENCY,
};
```
	
## Render Buffer Attachment Type
```C++
{
	DONT_USE,
	DEPTH_ATTACHMENT,
	STENCIL_ATTACHEMT,
	DEPTH_STENCIL_ATTACHMENT
};
```

## Render Buffer Format
```C++
{
	DEPTH_COMPONENT16,
	DEPTH_COMPONENT24,
	DEPTH_COMPONENT32F,
	DEPTH24_STENCIL8,
	DEPTH32F_STENCIL8,
	STENCIL_INDEX8,
};
```