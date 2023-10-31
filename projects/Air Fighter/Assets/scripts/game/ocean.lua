function ocean.start()
    local this = current()

    -- load ocean texture
    local assetsPath = dir.get_assets_path() .. '/images/ocean.png'
    this.texture = texture.create({
        ["minifying_filter"] = "LINEAR_MIPMAP_LINEAR",
        ["magnification_filter"] = "LINEAR",
        ["texture_wrap_t"] = "CLAMP_TO_EDGE",
        ["texture_wrap_s"] = "CLAMP_TO_EDGE",
        ["ansiotropic_filter"] = 8,
        ["border_color"] = { x = 0, y = 0, z = 0 },
        ["image_path"] = assetsPath
    })

    -- get camera
    local cam2d = cam2d.get(cam2d.get_current())

    -- save camera size for image size
    this.size_x = cam2d.right;
    this.size_y = cam2d.top;

    -- ocean position (two images are draw)
    this.x = 0;
    this.y = 0;
    this.y2 = this.size_y * 2;
end

function ocean.update()
    local this = current()

    -- draw first texture
    _draw2d_.texture({
        ["position"] = { x = this.x + this.size_x / 2, y = this.y },
        ["size"] = { x = this.size_x, y = this.size_y * 2 },
        ["texture_id"] = this.texture,
    })

    -- draw second texture
    _draw2d_.texture({
        ["position"] = { x = this.x + this.size_x / 2, y = this.y2 },
        ["size"] = { x = this.size_x, y = this.size_y * 2 },
        ["texture_id"] = this.texture,
    })

    -- increse image position
    this.y = this.y - engine.get_frametime() / 3;
    this.y2 = this.y2 - engine.get_frametime() / 3;

    -- put images back to initial position
    if this.y <= -(this.size_y * 2) then
        this.y = this.y2 + (this.size_y * 2)
    end

    if this.y2 <= -(this.size_y * 2) then
        this.y2 = this.y + this.size_y * 2
    end
end

function ocean.destroy()
    local this = current()

    texture.destroy(this.texture)
end
