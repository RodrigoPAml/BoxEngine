function menu.start()
    local this = engine.current()

    -- load image and font
    local menu_img = engine.dir.get_assets_path() .. '/images/menu.jpg'
    local font_path = engine.dir.get_assets_path() .. '/fonts/menu.ttf'

    -- background audio
    local audio_path = engine.dir.get_assets_path() .. '/sounds/background.wav'
    this.sound = engine.audio.create_2d(audio_path)
    engine.audio.set_loop(this.sound, true)
    engine.audio.resume(this.sound)

    this.font = engine.font.create(font_path, 0, 128)
    this.texture = engine.texture.create({
        minifying_filter = engine.enums.minifying_filter.linear_mipmap_linear,
        magnification_filter = engine.enums.magnification_filter.linear,
        texture_wrap_t = engine.enums.texture_wrap.mirror_clamp_to_edge,
        texture_wrap_s = engine.enums.texture_wrap.mirror_clamp_to_edge,
        ansiotropic_filter = 1,
        border_color = { x = 0, y = 0, z = 0 },
        image_path = menu_img
    })

    -- menu option
    this.option = -1
    local cam = engine.cam2d.get(engine.cam2d.get_current())

    -- get screen limitations from camera
    this.max_x = cam.right;
    this.max_y = cam.top;
end

function menu.update()
    local this = engine.current()

    engine.draw2d.texture({
        position = { x = this.max_x / 2, y = this.max_y / 2 },
        size = { x = this.max_x, y = this.max_y },
        rotation = 0,
        texture_id = this.texture,
    })

    menu.draw_buttons()
    menu.draw_texts()
    menu.draw_current_option()
end

function menu.draw_current_option()
    local this = engine.current()

    local button_size = 300;
    local mouse_pos = engine.input.get_cam_mouse_pos()

    local button_x_min = this.max_x / 2 - button_size / 2;
    local button_x_max = this.max_x / 2 + button_size / 2;

    if (mouse_pos.x > button_x_min and mouse_pos.x < button_x_max) then
        local button_y_min_0 = this.max_y / 2 - 50 + 100
        local button_y_max_0 = this.max_y / 2 + 50 + 100

        local button_y_min_1 = this.max_y / 2 - 50 - 50
        local button_y_max_1 = this.max_y / 2 + 50 - 50

        local button_y_min_2 = this.max_y / 2 - 50 - 200
        local button_y_max_2 = this.max_y / 2 + 50 - 200

        if (mouse_pos.y > button_y_min_0 and mouse_pos.y < button_y_max_0) then
            this.option = 0
        elseif (mouse_pos.y > button_y_min_1 and mouse_pos.y < button_y_max_1) then
            this.option = 1
        elseif (mouse_pos.y > button_y_min_2 and mouse_pos.y < button_y_max_2) then
            this.option = 2
        else
            this.option = -1
        end
    else
        this.option = -1
    end

    if (this.option == 0 and engine.input.get_mouse_button(engine.enums.mouse_button.left) == engine.enums.input_action.press) then
        engine.go.set_active(engine.go.current(), false)
        engine.go.set_active(this.game_id, true)
    end

    if (this.option == 1 and engine.input.get_mouse_button(engine.enums.mouse_button.left) == engine.enums.input_action.press) then
        engine.dir.exec('explorer https://github.com/RodrigoPAml/BoxEngine')
    end

    if (this.option == 2 and engine.input.get_mouse_button(engine.enums.mouse_button.left) == engine.enums.input_action.press) then
        engine.stop()
    end

    engine.command.set_primitive_line_size(5)

    if (this.option == 0) then
        engine.draw2d.rect({
            position = { x = this.max_x / 2, y = this.max_y / 2 + 100 },
            size = { x = button_size, y = 100 },
            color = { x = 1, y = 0, z = 0, w = 1 },
            filled = false,
        })
    elseif (this.option == 1) then
        engine.draw2d.rect({
            position = { x = this.max_x / 2, y = this.max_y / 2 - 50 },
            size = { x = button_size, y = 100 },
            color = { x = 1, y = 0, z = 0, w = 1 },
            filled = false,
        })
    elseif (this.option == 2) then
        engine.draw2d.rect({
            position = { x = this.max_x / 2, y = this.max_y / 2 - 200 },
            size = { x = button_size, y = 100 },
            color = { x = 1, y = 0, z = 0, w = 1 },
            filled = false,
        })
    end
end

function menu.draw_buttons()
    local this = engine.current()

    local button_size = 300;

    engine.draw2d.rect({
        position = { x = this.max_x / 2, y = this.max_y / 2 - 200 },
        size = { x = button_size, y = 100 },
        color = { x = 0, y = 0, z = 0, w = 0.5 },
        filled = true,
    })

    engine.draw2d.rect({
        position = { x = this.max_x / 2, y = this.max_y / 2 - 50 },
        size = { x = button_size, y = 100 },
        color = { x = 0, y = 0, z = 0, w = 0.5 },
        filled = true,
    })

    engine.draw2d.rect({
        position = { x = this.max_x / 2, y = this.max_y / 2 + 100 },
        size = { x = button_size, y = 100 },
        color = { x = 0, y = 0, z = 0, w = 0.5 },
        filled = true,
    })
end

function menu.draw_texts()
    local this = engine.current()

    local font_id = this.font

    engine.font.set_text(font_id, 'Air Fighter')
    engine.font.set_position(font_id, { x = this.max_x / 2 - 330, y = this.max_y - 250 })
    engine.font.set_color(font_id, { x = 0.0, y = 0.0, z = 0.0 })
    engine.font.set_scale(font_id, { x = 1.5, y = 1.5 })
    engine.font.draw(font_id)

    engine.font.set_text(font_id, 'Start')
    engine.font.set_position(font_id, { x = this.max_x / 2 - 80, y = this.max_y - 475 })
    engine.font.set_scale(font_id, { x = 0.7, y = 0.7 })
    engine.font.set_color(font_id, { x = 0.8, y = 0.8, z = 0.8 })
    engine.font.draw(font_id)

    engine.font.set_text(font_id, 'About')
    engine.font.set_position(font_id, { x = this.max_x / 2 - 80, y = this.max_y - 625 })
    engine.font.set_scale(font_id, { x = 0.7, y = 0.7 })
    engine.font.set_color(font_id, { x = 0.8, y = 0.8, z = 0.8 })
    engine.font.draw(font_id)

    engine.font.set_text(font_id, 'Exit')
    engine.font.set_position(font_id, { x = this.max_x / 2 - 50, y = this.max_y - 775 })
    engine.font.set_scale(font_id, { x = 0.7, y = 0.7 })
    engine.font.set_color(font_id, { x = 0.8, y = 0.8, z = 0.8 })
    engine.font.draw(font_id)
end

function menu.destroy()
    local this = engine.current()

    engine.font.destroy(this.font)
    engine.texture.destroy(this.texture)
    engine.audio.destroy(this.sound)
end
