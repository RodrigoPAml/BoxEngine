controller = {}

function controller.start()
    local this = controller[go.current()]
    local font_path = dir.get_assets_path() .. '/fonts/points.ttf'

    this.font = font.create(font_path)

    local cam = cam2d.get(cam2d.get_current())

    -- get screen limitations from camera
    this.max_x = cam.right;
    this.max_y = cam.top;

    -- time control variable
    this.time = time.get_timestamp()

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
    local this = controller[go.current()]

    local fighter_go = fighter[this.fighter_id]
    if (fighter_go == nil) then
        local font_id = this.font
        local points_str = to_string(math.ceil(this.points))

        font.set_text(font_id, 'Points: ' .. points_str)
        font.set_position(font_id, { x = this.max_x / 2 - 300 - (30 * #points_str), y = this.max_y / 2 })
        font.set_color(font_id, { x = 1.0, y = 1.0, z = 1.0 })
        font.set_scale(font_id, { x = 1, y = 1 })
        font.draw(font_id)

        font.set_text(font_id, 'Press ESC to restart')
        font.set_position(font_id, { x = (this.max_x / 2) - 430, y = this.max_y / 2 - 130 })
        font.set_color(font_id, { x = 1.0, y = 1.0, z = 1.0 })
        font.set_scale(font_id, { x = 0.5, y = 0.5 })
        font.draw(font_id)

        local space_input = input.get_key('ESCAPE')

        -- check if the fighter can spawn a fire bullet
        if ((space_input == 'PRESS' or space_input == 'REPEAT')) then
            engine.restart()
        end
        return
    end

    if (time.get_timestamp() - this.time > this.enemy_spawn_interval) then
        this.points = this.points + 10
        this.time = time.get_timestamp()

        local enemy_id = go.create_copy(this.enemy_id, this.enemy_father_id)
        go.load_scripts(enemy_id)
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
            go.create_copy(this.life_id, this.life_father_id)
        end
    end

    local font_id = this.font

    font.set_text(font_id, 'Points ' .. to_string(math.ceil(this.points)))
    font.set_position(font_id, { x = 20, y = this.max_y - 60 })
    font.set_color(font_id, { x = 1.0, y = 1.0, z = 1.0 })
    font.set_scale(font_id, { x = 0.5, y = 0.5 })
    font.draw(font_id)
end

function controller.destroy()
    local this = controller[go.current()]
    font.destroy(this.font)
end
