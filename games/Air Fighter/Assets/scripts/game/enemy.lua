enemy = {}

function enemy.start()
    local this = enemy[go.current()]
    local path = dir.get_assets_path() .. '/images/enemy.png'

    -- load enemy texture
    this.texture = texture.create({
        ["minifying_filter"] = "LINEAR_MIPMAP_LINEAR",
        ["magnification_filter"] = "LINEAR",
        ["texture_wrap_t"] = "CLAMP_TO_EDGE",
        ["texture_wrap_s"] = "CLAMP_TO_EDGE",
        ["ansiotropic_filter"] = 8,
        ["border_color"] = { x = 0, y = 0, z = 0 },
        ["image_path"] = path
    })

    local cam2d = cam2d.get(cam2d.get_current())

    -- limits of movement
    this.max_x = cam2d.right;
    this.max_y = cam2d.top;

    -- intial position
    this.x = math.random() * this.max_x;
    this.y = this.max_y + 100;

    enemy.start_attributes()
end

function enemy.start_attributes()
    local this = enemy[go.current()]
    local controller_go = controller[this.controller_id]

    -- velocity
    this.vel_y = controller_go.enemy_vel_y
    this.vel_x = controller_go.enemy_vel_x

    -- choose direction
    if (math.random() > 0.5) then
        this.vel_x = this.vel_x * -1
    end

    -- fire control variables
    -- every X seconds open  fire
    this.interval_of_fire = controller_go.enemy_interval_of_fire

    -- when firing, is the time between firings
    this.fire_rate = controller_go.enemy_fire_rate

    this.last_fire_time = time.get_timestamp()
    this.fire_time = time.get_timestamp()
    this.should_fire = true

    -- initial enemy life
    this.life = controller_go.enemy_life

    this.is_hit = false
    this.hit_time = 0
end

function enemy.update()
    local this = enemy[go.current()]

    enemy.control()
    enemy.deal_damage()
    enemy.take_damage()
    enemy.collide_fighter()

    if (this.is_hit) then
        draw2d.texture({
            ["position"] = { x = this.x, y = this.y },
            ["size"] = { x = this.size_x, y = this.size_y },
            ["texture_id"] = this.texture,
            ["color"] = { x = 0.5, y = 0, z = 0, w = 0 }
        })

        this.is_hit = false
    else
        -- draw enemy
        draw2d.texture({
            ["position"] = { x = this.x, y = this.y },
            ["size"] = { x = this.size_x, y = this.size_y },
            ["texture_id"] = this.texture,
        })
    end
end

function enemy.control()
    local this = enemy[go.current()]
    local fighter_go = fighter[this.fighter_id]

    if (fighter_go == nil) then
        return
    end

    local dx = fighter_go.x - this.x
    local dy = fighter_go.y - this.y

    local dist = math.sqrt(dx * dx + dy * dy)

    if (this.y > this.max_y / 2 and dist > 250) then
        -- move enemy
        this.y = this.y - (engine.get_frametime() * this.vel_y)
        this.x = this.x - (engine.get_frametime() * this.vel_x)
    else
        -- move enemy
        this.y = this.y - (engine.get_frametime() * this.vel_y)

        if (fighter_go.x > this.x) then
            this.x = this.x + (engine.get_frametime() * math.abs(this.vel_x))
        else
            this.x = this.x - (engine.get_frametime() * math.abs(this.vel_x))
        end
    end

    -- don't let the enemy get out of screen
    if (this.x < 0) then
        this.vel_x = this.vel_x * -1
        this.x = 0
    elseif (this.x > this.max_x) then
        this.x = this.max_x
        this.vel_x = this.vel_x * -1
    end

    -- if cross all the screen on Y exis then destroy it
    if (this.y < -100) then
        go.destroy(go.current())
    end
end

function enemy.collide_fighter()
    local this = enemy[go.current()]
    local fighter_go = fighter[this.fighter_id]

    if (fighter_go == nil) then
        return
    end

    if (fighter_go.is_immune) then
        return
    end

    -- calculate bouding box of enemy
    local max_x = this.x + this.size_x / 2 - 30
    local min_x = this.x - this.size_x / 2 + 30

    local max_x_fighter = fighter_go.x + fighter_go.size_x / 2
    local min_x_fighter = fighter_go.x - fighter_go.size_x / 2

    if max_x < min_x_fighter or max_x_fighter < min_x then
        return
    end

    -- calculate bouding box of enemy
    local max_y = this.y + this.size_y / 2 - 30
    local min_y = this.y - this.size_y / 2 + 30

    local max_y_fighter = fighter_go.y + fighter_go.size_y / 2
    local min_y_fighter = fighter_go.y - fighter_go.size_y / 2

    if max_y < min_y_fighter or max_y_fighter < min_y then
        return
    end

    fighter_go.is_hit = true
    this.life = 0
end

function enemy.deal_damage()
    local this = enemy[go.current()]

    -- if not firing calculate the time to next fire
    if (time.get_timestamp() > this.fire_time + this.interval_of_fire) then
        this.fire_time = time.get_timestamp()
        this.last_fire_time = time.get_timestamp()
        this.should_fire = not this.should_fire
    end

    if (this.should_fire == true) then
        if (time.get_timestamp() > this.last_fire_time + this.fire_rate) then
            -- create copy of prefab
            local new_go_id = go.create_copy(this.fire_prefab_id, this.fire_father_id)
            go.load_scripts(new_go_id)

            local new_go = enemy_fire[new_go_id]
            new_go.x = this.x + 16;
            new_go.y = this.y - 30;

            this.last_fire_time = time.get_timestamp()
        end
    end
end

function enemy.take_damage()
    local this = enemy[go.current()]

    -- if its killed then destroy it
    if (this.life <= 0) then
        -- increase user points
        local controller_go = controller[this.controller_id]
        controller_go.points = controller_go.points + 100

        -- destroy go
        go.destroy(go.current())

        -- spawn explosion where it died
        local explosion_id = go.create_copy(this.explosion_prefab_id, this.explosion_father_id)
        go.load_scripts(explosion_id)

        local explosion_go = explosion[explosion_id]
        explosion_go.x = this.x
        explosion_go.y = this.y
        explosion_go.time = time.get_timestamp()
    end
end

function enemy.destroy()
    local this = enemy[go.current()]
    texture.destroy(this.texture)
end
