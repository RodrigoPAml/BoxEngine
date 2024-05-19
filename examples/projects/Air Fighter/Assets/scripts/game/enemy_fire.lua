function enemy_fire.start()
    local this = engine.current()
    local path = engine.dir.get_assets_path() .. '/images/bullet.png'
    local audio_path = engine.dir.get_assets_path() .. '/sounds/laser.mp3'

    this.sound = engine.audio.create_2d(audio_path)
    this.sound_started = false

    this.texture = engine.texture.create({
        minifying_filter = enums.minifying_filter.linear_mipmap_linear,
        magnification_filter = enums.magnification_filter.linear,
        texture_wrap_t = enums.texture_wrap.clamp_to_edge,
        texture_wrap_s = enums.texture_wrap.clamp_to_edge,
        ansiotropic_filter = 8,
        border_color = { x = 0, y = 0, z = 0 },
        image_path = path
    })

    local cam2d = engine.cam2d.get(engine.cam2d.get_current())

    this.max_x = cam2d.right;
    this.max_y = cam2d.top;

    enemy_fire.start_attributes()
end

function enemy_fire.start_attributes()
    local this = engine.current()
    local controller_go = engine.data(this.controller_id, 'controller') 

    this.vel = controller_go.fire_vel
end

function enemy_fire.update()
    local this = engine.current()

    if (this.sound_started == false) then
        this.sound_started = true
        engine.audio.resume(this.sound)
        engine.audio.set_volume(this.sound, 0.5)
    end

    -- if the bullet is outside screen then destroy it
    if (this.y < -100) then
        engine.go.destroy(engine.go.current())
        return
    end

    enemy_fire.move()
    enemy_fire.deal_damage()

    engine.draw2d.texture({
        position = { x = this.x, y = this.y },
        size = { x = this.size_x, y = this.size_y },
        rotation = 180,
        texture_id = this.texture,
    })
end

function enemy_fire.move()
    local this = engine.current()

    -- move the enemy
    this.y = this.y - (engine.get_frametime() * this.vel)
end

function enemy_fire.deal_damage()
    local this = engine.current()
    local fighter_go = engine.data(this.fighter_id, 'fighter')

    if (fighter_go == nil) then
        return
    end

    local max_x = fighter_go.x + fighter_go.size_x / 2
    local min_x = fighter_go.x - fighter_go.size_x / 2

    if (this.x > min_x and this.x < max_x) then
        -- calculate fighter bouding box on y axis
        local max_y = fighter_go.y + fighter_go.size_y / 2
        local min_y = fighter_go.y - fighter_go.size_y / 2

        if (this.y > min_y and this.y < max_y) then
            fighter_go.is_hit = true
        end
    end
end

function enemy_fire.destroy()
    local this = engine.current()
    engine.texture.destroy(this.texture)
    engine.audio.destroy(this.sound)
end
