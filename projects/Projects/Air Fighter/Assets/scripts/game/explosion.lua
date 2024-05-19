function explosion.start()
    local this = engine.current()

    local path1 = engine.dir.get_assets_path() .. '/images/boom1.png'
    local path2 = engine.dir.get_assets_path() .. '/images/boom2.png'
    local path3 = engine.dir.get_assets_path() .. '/images/boom3.png'
    local path4 = engine.dir.get_assets_path() .. '/images/boom4.png'

    local create_args = {
        minifying_filter = enums.minifying_filter.linear_mipmap_linear,
        magnification_filter = enums.magnification_filter.linear,
        texture_wrap_t = enums.texture_wrap.clamp_to_edge,
        texture_wrap_s = enums.texture_wrap.clamp_to_edge,
        ansiotropic_filter = 8,
        border_color = { x = 0, y = 0, z = 0 },
    }

    create_args.image_path = path1
    this.texture_1 = engine.texture.create(create_args)

    create_args.image_path = path2
    this.texture_2 = engine.texture.create(create_args)

    create_args.image_path = path3
    this.texture_3 = engine.texture.create(create_args)

    create_args.image_path = path4
    this.texture_4 = engine.texture.create(create_args)

    local explosion_path = engine.dir.get_assets_path() .. '/sounds/explosion.wav'

    this.sound_id = engine.audio.create_2d(explosion_path)
    this.sound_is_played = false
end

function explosion.update()
    local this = engine.current()

    if (this.time + 0.32 < engine.time.get_timestamp()) then
        if (engine.audio.is_finished(this.sound_id)) then
            engine.go.destroy(engine.go.current())
        end

        return
    elseif (this.time + 0.24 < engine.time.get_timestamp()) then
        engine.draw2d.texture({
            position = { x = this.x, y = this.y },
            size = { x = this.size_x, y = this.size_y },
            texture_id = this.texture_4,
        })
    elseif (this.time + 0.16 < engine.time.get_timestamp()) then
        engine.draw2d.texture({
            position = { x = this.x, y = this.y },
            size = { x = this.size_x, y = this.size_y },
            texture_id = this.texture_3,
        })
    elseif (this.time + 0.08 < engine.time.get_timestamp()) then
        engine.draw2d.texture({
            position = { x = this.x, y = this.y },
            size = { x = this.size_x, y = this.size_y },
            texture_id = this.texture_2,
        })
    elseif (this.time < engine.time.get_timestamp()) then
        if (this.sound_is_played == false) then
            engine.audio.resume(this.sound_id)
            this.sound_is_played = true
        end

        engine.draw2d.texture({
            position = { x = this.x, y = this.y },
            size = { x = this.size_x, y = this.size_y },
            texture_id = this.texture_1,
        })
    end
end

function explosion.destroy()
    local this = engine.current()

    engine.texture.destroy(this.texture_1)
    engine.texture.destroy(this.texture_2)
    engine.texture.destroy(this.texture_3)
    engine.texture.destroy(this.texture_4)

    engine.audio.destroy(this.sound_id)
end
