function controller.start()
    local this = engine.current()
    local font_path = engine.dir.get_assets_path() .. '/fonts/points.ttf'

    this.font = engine.font.create(font_path)

    local cam = engine.cam2d.get(engine.cam2d.get_current())

    -- get screen limitations from camera
    this.max_x = cam.right;
    this.max_y = cam.top;

    -- time control variable
    this.time = engine.time.get_timestamp()

    -- enemy attributes
    this.enemy_spawn_interval = 2
    this.enemy_vel_y = 0.2
    this.enemy_vel_x = 0.05
    this.enemy_fire_rate = 0.6
    this.enemy_interval_of_fire = 1
    this.enemy_life = 2

    -- fire attributes
    this.fire_vel = 0.5

    -- user points
    this.points = 0;
    this.points_increase_difficulty = 500
end

function controller.update()
    local this = engine.current()

    local fighter_go = engine.data(this.fighter_id, 'fighter')

    if (fighter_go == nil) then
        local font_id = this.font
        local points_str = engine.to_string(math.ceil(this.points))

        engine.font.set_text(font_id, 'Points: ' .. points_str)
        engine.font.set_position(font_id, { x = this.max_x / 2 - 300 - (30 * #points_str), y = this.max_y / 2 })
        engine.font.set_color(font_id, { x = 1.0, y = 1.0, z = 1.0 })
        engine.font.set_scale(font_id, { x = 1, y = 1 })
        engine.font.draw(font_id)

        engine.font.set_text(font_id, 'Press ESC to restart')
        engine.font.set_position(font_id, { x = (this.max_x / 2) - 430, y = this.max_y / 2 - 130 })
        engine.font.set_color(font_id, { x = 1.0, y = 1.0, z = 1.0 })
        engine.font.set_scale(font_id, { x = 0.5, y = 0.5 })
        engine.font.draw(font_id)

        local space_input = engine.input.get_key(enums.keyboard_key.escape)

        -- check if the fighter can spawn a fire bullet
        if ((space_input == enums.input_action.press)) then
            engine.restart()
        end
        return
    end

    if (engine.time.get_timestamp() - this.time > this.enemy_spawn_interval) then
        this.points = this.points + 10
        this.time = engine.time.get_timestamp()

        local enemy_id = engine.go.create_copy(this.enemy_id, this.enemy_father_id)
        engine.go.load_scripts(enemy_id)
    end

    if (this.points > this.points_increase_difficulty) then
        this.points_increase_difficulty = this.points_increase_difficulty + 500

        this.enemy_spawn_interval = math.max(this.enemy_spawn_interval - 0.05, 0.100) -- less 100ms each time, max is 100ms
        this.enemy_vel_y = this.enemy_vel_y + 0.01
        this.enemy_vel_x = this.enemy_vel_x + 0.02
        this.enemy_fire_rate = math.max(this.enemy_fire_rate - 0.03, 0.1)
        this.enemy_interval_of_fire = math.max(this.enemy_interval_of_fire - 0.05, 1)
        this.enemy_life = this.enemy_life + 0.5

        this.fire_vel = math.min(this.fire_vel + 0.1, 2)

        -- spawn life
        if (fighter_go.life < 3) then
            engine.go.create_copy(this.life_id, this.life_father_id)
        end
    end

    local font_id = this.font

    engine.font.set_text(font_id, 'Points ' .. engine.to_string(math.ceil(this.points)))
    engine.font.set_position(font_id, { x = 20, y = this.max_y - 60 })
    engine.font.set_color(font_id, { x = 1.0, y = 1.0, z = 1.0 })
    engine.font.set_scale(font_id, { x = 0.5, y = 0.5 })
    engine.font.draw(font_id)
end

function controller.destroy()
    local this = engine.current()
    engine.font.destroy(this.font)
end
