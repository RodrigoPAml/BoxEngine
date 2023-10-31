function explosion.start()
    local this = current()

    local path1 = dir.get_assets_path() .. '/images/boom1.png'
    local path2 = dir.get_assets_path() .. '/images/boom2.png'
    local path3 = dir.get_assets_path() .. '/images/boom3.png'
    local path4 = dir.get_assets_path() .. '/images/boom4.png'

    local create_args = {
        ["minifying_filter"] = "LINEAR_MIPMAP_LINEAR",
        ["magnification_filter"] = "LINEAR",
        ["texture_wrap_t"] = "CLAMP_TO_EDGE",
        ["texture_wrap_s"] = "CLAMP_TO_EDGE",
        ["ansiotropic_filter"] = 8,
        ["border_color"] = { x = 0, y = 0, z = 0 },
    }

    create_args['image_path'] = path1
    this.texture_1 = texture.create(create_args)

    create_args['image_path'] = path2
    this.texture_2 = texture.create(create_args)

    create_args['image_path'] = path3
    this.texture_3 = texture.create(create_args)

    create_args['image_path'] = path4
    this.texture_4 = texture.create(create_args)

    local explosion_path = dir.get_assets_path() .. '/sounds/explosion.wav'

    this.sound_id = audio.create_2d(explosion_path)
    this.sound_is_played = false
end

function explosion.update()
    local this = current()

    if (this.time + 0.32 < time.get_timestamp()) then
        if (audio.is_finished(this.sound_id)) then
            go.destroy(go.current())
        end

        return
    elseif (this.time + 0.24 < time.get_timestamp()) then
        draw2d.texture({
            ["position"] = { x = this.x, y = this.y },
            ["size"] = { x = this.size_x, y = this.size_y },
            ["texture_id"] = this.texture_4,
        })
    elseif (this.time + 0.16 < time.get_timestamp()) then
        draw2d.texture({
            ["position"] = { x = this.x, y = this.y },
            ["size"] = { x = this.size_x, y = this.size_y },
            ["texture_id"] = this.texture_3,
        })
    elseif (this.time + 0.08 < time.get_timestamp()) then
        draw2d.texture({
            ["position"] = { x = this.x, y = this.y },
            ["size"] = { x = this.size_x, y = this.size_y },
            ["texture_id"] = this.texture_2,
        })
    elseif (this.time < time.get_timestamp()) then
        if (this.sound_is_played == false) then
            audio.resume(this.sound_id)
            this.sound_is_played = true
        end

        draw2d.texture({
            ["position"] = { x = this.x, y = this.y },
            ["size"] = { x = this.size_x, y = this.size_y },
            ["texture_id"] = this.texture_1,
        })
    end
end

function explosion.destroy()
    local this = current()

    texture.destroy(this.texture_1)
    texture.destroy(this.texture_2)
    texture.destroy(this.texture_3)
    texture.destroy(this.texture_4)

    audio.destroy(this.sound_id)
end
