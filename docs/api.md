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

# Drawing Module

# Camera 2D Module

# Camera 3D Module
