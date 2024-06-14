function fighter.start()
    local this = engine.current()

    -- load textures for fighter
    local path = engine.dir.get_assets_path() .. '/images/airplane.png'
    local path_left = engine.dir.get_assets_path() .. '/images/airplane_left.png'
    local path_right = engine.dir.get_assets_path() .. '/images/airplane_right.png'
    local path_life = engine.dir.get_assets_path() .. '/images/life.png'

    local create_args = {
        minifying_filter = engine.enums.minifying_filter.linear_mipmap_linear,
        magnification_filter = engine.enums.magnification_filter.linear,
        texture_wrap_t = engine.enums.texture_wrap.clamp_to_edge,
        texture_wrap_s = engine.enums.texture_wrap.clamp_to_edge,
        ansiotropic_filter = 8,
        border_color = { x = 0, y = 0, z = 0 },
    }

    create_args.image_path = path
    this.texture = engine.texture.create(create_args)

    create_args.image_path = path_left
    this.texture_left = engine.texture.create(create_args)

    create_args.image_path = path_right
    this.texture_right = engine.texture.create(create_args)

    create_args.image_path = path_life
    this.texture_life = engine.texture.create(create_args)

    -- load camera data to rule fighter control
    local cam2d = engine.cam2d.get(engine.cam2d.get_current())

    this.max_x = cam2d.right;
    this.max_y = cam2d.top;

    this.x = this.max_x / 2;
    this.y = 100;

    -- life control
    this.life = 3
    this.is_hit = false;
    this.is_immune = false
    this.hit_time = 0;

    -- blink when immune
    this.blink_time = 0;
    this.should_draw = true;

    this.time = engine.time.get_timestamp();
end

function fighter.update()
    fighter.fire()
    fighter.control()
    fighter.take_damage()
end

function fighter.take_damage()
    local this = engine.current()

    if (this.is_hit and this.is_immune == false) then
        -- spawn explosion where it died
        local explosion_id = engine.go.create_copy(this.explosion_id, this.explosion_father_id)
        engine.go.load_scripts(explosion_id)

        local explosion_go = engine.data(explosion_id, 'explosion')
        explosion_go.x = this.x
        explosion_go.y = this.y
        explosion_go.time = engine.time.get_timestamp()

        this.life = this.life - 1
        this.is_immune = true
        this.hit_time = engine.time.get_timestamp()

        this.blink_time = this.hit_time
        this.should_draw = false
    end

    if (this.is_immune) then
        if (this.blink_time + 0.1 < engine.time.get_timestamp()) then
            this.blink_time = engine.time.get_timestamp()
            this.should_draw = not this.should_draw
        end

        if (this.hit_time + 3 < engine.time.get_timestamp()) then
            this.is_immune = false
            this.is_hit = false
            this.should_draw = true
        end
    end

    if (this.life < 0) then
        -- spawn explosion where it died
        local explosion_id = engine.go.create_copy(this.explosion_id, this.explosion_father_id)
        engine.go.load_scripts(explosion_id)

        local explosion_go = engine.data(explosion_id, 'explosion')
        explosion_go.x = this.x
        explosion_go.y = this.y
        explosion_go.time = engine.time.get_timestamp()

        engine.go.destroy(engine.go.current())
    end

    if (this.life > 0) then
        engine.draw2d.texture({
            position = { x = 30, y = 40 },
            size = { x = 50, y = 50 },
            texture_id = this.texture_life,
        })
    end
    if (this.life > 1) then
        engine.draw2d.texture({
            position = { x = 90, y = 40 },
            size = { x = 50, y = 50 },
            texture_id = this.texture_life,
        })
    end

    if (this.life > 2) then
        engine.draw2d.texture({
            position = { x = 150, y = 40 },
            size = { x = 50, y = 50 },
            texture_id = this.texture_life,
        })
    end
end

function fighter.fire()
    local this = engine.current()

    local has_time_passed = engine.time.get_timestamp() - this.time > 0.1
    local space_input = engine.input.get_key(engine.enums.keyboard_key.space)

    -- check if the fighter can spawn a fire bullet
    if ((space_input == engine.enums.input_action.press) and has_time_passed) then
        this.time = engine.time.get_timestamp();

        -- create copy of prefab
        local new_go_id = engine.go.create_copy(this.fire_prefab_id, this.fire_father_id)
        engine.go.load_scripts(new_go_id)

        local new_go = engine.data(new_go_id, 'fire')
        new_go.x = this.x - 5;
        new_go.y = this.y + 100;
    end
end

function fighter.control()
    local this = engine.current()

    -- store if the figther is outside screen limits
    local limited_xmin = this.x > this.max_x
    local limited_xmax = this.x < 0
    local limited_ymax = this.y > this.max_y
    local limited_ymin = this.y < 0

    local up_input = engine.input.get_key(engine.enums.keyboard_key.up)
    local down_input = engine.input.get_key(engine.enums.keyboard_key.down)

    -- control foward and back fighter movement
    if ((up_input == engine.enums.input_action.press) and limited_ymax == false) then
        this.y = this.y + engine.get_frametime()
    elseif ((down_input == engine.enums.input_action.press) and limited_ymin == false) then
        this.y = this.y - engine.get_frametime()
    end

    local left_input = engine.input.get_key(engine.enums.keyboard_key.left)
    local right_input = engine.input.get_key(engine.enums.keyboard_key.right)

    -- control left and and right fighter movement
    if ((left_input == engine.enums.input_action.press) and limited_xmax == false) then
        this.x = this.x - engine.get_frametime()

        if (this.should_draw) then
            engine.draw2d.texture({
                position = { x = this.x, y = this.y },
                size = { x = this.size_x, y = this.size_y },
                texture_id = this.texture_left,
            })
        end
    elseif ((right_input == engine.enums.input_action.press) and limited_xmin == false) then
        this.x = this.x + engine.get_frametime()

        if (this.should_draw) then
            engine.draw2d.texture({
                position = { x = this.x, y = this.y },
                size = { x = this.size_x, y = this.size_y },
                texture_id = this.texture_right,
            })
        end
    else
        if (this.should_draw) then
            engine.draw2d.texture({
                position = { x = this.x, y = this.y },
                size = { x = this.size_x, y = this.size_y },
                texture_id = this.texture,
            })
        end
    end
end

function fighter.destroy()
    local this = engine.current()

    engine.texture.destroy(this.texture)
    engine.texture.destroy(this.texture_left)
    engine.texture.destroy(this.texture_right)
end
