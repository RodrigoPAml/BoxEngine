clouds = {}

function clouds.start()
    local this = clouds[go.current()]

    -- load cloud image
    local cloud = dir.get_assets_path() .. '/images/' .. this.path
    this.texture = _texture_.create({
        ["minifying_filter"] = "LINEAR_MIPMAP_LINEAR",
        ["magnification_filter"] = "LINEAR",
        ["texture_wrap_t"] = "CLAMP_TO_EDGE",
        ["texture_wrap_s"] = "CLAMP_TO_EDGE",
        ["ansiotropic_filter"] = 8,
        ["border_color"] = { x = 0, y = 0, z = 0 },
        ["image_path"] = cloud
    })

    local cam2d = cam2d.get(cam2d.get_current())

    -- get screen limitations from camera
    this.max_x = cam2d.right;
    this.max_y = cam2d.top;

    -- set initial cloud size, velocity and point that it restart
    this.size = this.max_x
    this.vel = math.random() * 3
    this.exit_point = this.max_y * 2
end

function clouds.update()
    local this = clouds[go.current()]

    -- move the cloud
    this.y = this.y - ((engine.get_frametime() / 3) * this.vel)

    draw2d.texture({
        ["position"] = { x = this.x, y = this.y },
        ["size"] = { x = this.size, y = this.size },
        ["texture_id"] = this.texture,
    })

    -- restart cloud position
    if this.y <= -(this.exit_point) then
        this.x = math.random() * this.max_x
        this.y = math.random() * 2000 + 3000

        this.size = math.random() * this.max_x * 2.5
        this.exit_point = math.random() * 3000 + (this.max_y * 2)
    end
end

function clouds.destroy()
    local this = clouds[go.current()]

    texture.destroy(this.texture)
end
