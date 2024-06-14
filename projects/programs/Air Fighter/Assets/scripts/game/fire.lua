function fire.start()
    local this = engine.current()
    local path = engine.dir.get_assets_path() .. '/images/bullet.png'
    local audio_path = engine.dir.get_assets_path() .. '/sounds/laser.mp3'

    this.sound = engine.audio.create_2d(audio_path)
    this.sound_started = false

    this.texture = engine.texture.create({
        minifying_filter = engine.enums.minifying_filter.linear_mipmap_linear,
        magnification_filter = engine.enums.magnification_filter.linear,
        texture_wrap_t = engine.enums.texture_wrap.clamp_to_edge,
        texture_wrap_s = engine.enums.texture_wrap.clamp_to_edge,
        ansiotropic_filter = 8,
        border_color = { x = 0, y = 0, z = 0 },
        image_path = path
    })

    local cam2d = engine.cam2d.get(engine.cam2d.get_current())

    this.max_x = cam2d.right;
    this.max_y = cam2d.top;
end

function fire.update()
    local this = engine.current()

    if (this.sound_started == false) then
        this.sound_started = true
        engine.audio.resume(this.sound)
        engine.audio.set_volume(this.sound, 0.5)
    end

    -- if the bullet is outside screen then destroy it
    if (this.y > this.max_y + 100) then
        engine.go.destroy(engine.go.current())
    end

    -- move the bullet
    this.y = this.y + (engine.get_frametime() * this.vel)

    engine.draw2d.texture({
        position = { x = this.x, y = this.y },
        size = { x = this.size_x, y = this.size_y },
        rotation = 0,
        texture_id = this.texture,
    })

    fire.destroy_enemies()
end

function fire.destroy_enemies()
    -- no enemies instantiated
    if (enemy == nil) then
        return
    end

    local this = engine.current()

    -- find all enemies go id
    local childrens = engine.go.get(this.enemy_father_id).childrens

    -- iterate enemies to do collision test
    for i = 1, #childrens do
        local enemy_go_id = childrens[i]
        local script_data = engine.script.get(enemy_go_id, 'enemy')

        -- script not initialized wait
        if (script_data.state ~= engine.enums.script_state_enum.updating) then
            goto continue
        end

        local enemy_go = engine.data(enemy_go_id, 'enemy')

        -- calculate enemy bouding box on x axis
        local max_x = enemy_go.x + enemy_go.size_x / 2
        local min_x = enemy_go.x - enemy_go.size_x / 2

        if (this.x > min_x and this.x < max_x) then
            -- calculate enemy bouding box on y axis
            local max_y = enemy_go.y + enemy_go.size_y / 2
            local min_y = enemy_go.y - enemy_go.size_y / 2

            -- if collision detected then reduce enemy life or destroy it
            -- also destroy the bullet itself
            if (this.y > min_y and this.y < max_y) then
                enemy_go.life = enemy_go.life - 1
                enemy_go.is_hit = true

                engine.go.destroy(engine.go.current())
            end
        end
        ::continue::
    end
end

function fire.destroy()
    local this = engine.current()
    engine.texture.destroy(this.texture)
    engine.audio.destroy(this.sound)
end
