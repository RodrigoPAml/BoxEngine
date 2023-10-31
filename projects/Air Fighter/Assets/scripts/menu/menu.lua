function menu.start()
    local this = current()

    -- load image and font
    local menu_img = dir.get_assets_path() .. '/images/menu.jpg'
    local font_path = dir.get_assets_path() .. '/fonts/menu.ttf'

    -- background audio
    local audio_path = dir.get_assets_path() .. '/sounds/background.wav'
    this.sound = audio.create_2d(audio_path)
    audio.set_loop(this.sound, true)
    audio.resume(this.sound)

    this.font = font.create(font_path)
    this.texture = _texture_.create({
        ["minifying_filter"] = "LINEAR_MIPMAP_LINEAR",
        ["magnification_filter"] = "LINEAR",
        ["texture_wrap_t"] = "MIRROR_CLAMP_TO_EDGE",
        ["texture_wrap_s"] = "MIRROR_CLAMP_TO_EDGE",
        ["ansiotropic_filter"] = 1,
        ["border_color"] = { x = 0, y = 0, z = 0 },
        ["image_path"] = menu_img
    })

    -- menu option
    this.option = -1
    local cam = cam2d.get(cam2d.get_current())

    -- get screen limitations from camera
    this.max_x = cam.right;
    this.max_y = cam.top;
end

function menu.update()
    local this = current()

    draw2d.texture({
        ["position"] = { x = this.max_x / 2, y = this.max_y / 2 },
        ["size"] = { x = this.max_x, y = this.max_y },
        ["rotation"] = 0,
        ["texture_id"] = this.texture,
    })

    menu.draw_buttons()
    menu.draw_texts()
    menu.draw_current_option()
end

function menu.draw_current_option()
    local this = current()

    local button_size = 300;
    local mouse_pos = input.get_cam_mouse_pos()

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

    if (this.option == 0 and input.get_mouse_button('LEFT') == 'PRESS') then
        go.set_active(go.current(), false)
        go.set_active(this.game_id, true)
    end

    if (this.option == 1 and input.get_mouse_button('LEFT') == 'PRESS') then
        dir.exec('explorer https://github.com/RodrigoPAml/BoxEngine')
     end

    if (this.option == 2 and input.get_mouse_button('LEFT') == 'PRESS') then
       engine.stop()
    end

    command.set_primitive_line_size(5)

    if (this.option == 0) then
        draw2d.rect({
            position = { x = this.max_x / 2, y = this.max_y / 2 + 100 },
            size = { x = button_size, y = 100 },
            color = { x = 1, y = 0, z = 0, w = 1 },
            filled = false,
        })
    elseif (this.option == 1) then
        draw2d.rect({
            position = { x = this.max_x / 2, y = this.max_y / 2 - 50 },
            size = { x = button_size, y = 100 },
            color = { x = 1, y = 0, z = 0, w = 1 },
            filled = false,
        })
    elseif (this.option == 2) then
        draw2d.rect({
            position = { x = this.max_x / 2, y = this.max_y / 2 - 200 },
            size = { x = button_size, y = 100 },
            color = { x = 1, y = 0, z = 0, w = 1 },
            filled = false,
        })
    end
end

function menu.draw_buttons()
    local this = current()

    local button_size = 300;

    draw2d.rect({
        position = { x = this.max_x / 2, y = this.max_y / 2 - 200 },
        size = { x = button_size, y = 100 },
        color = { x = 0, y = 0, z = 0, w = 0.5 },
        filled = true,
    })

    draw2d.rect({
        position = { x = this.max_x / 2, y = this.max_y / 2 - 50 },
        size = { x = button_size, y = 100 },
        color = { x = 0, y = 0, z = 0, w = 0.5 },
        filled = true,
    })

    draw2d.rect({
        position = { x = this.max_x / 2, y = this.max_y / 2 + 100 },
        size = { x = button_size, y = 100 },
        color = { x = 0, y = 0, z = 0, w = 0.5 },
        filled = true,
    })
end

function menu.draw_texts()
    local this = current()

    local font_id = this.font

    font.set_text(font_id, 'Air Fighter')
    font.set_position(font_id, { x = this.max_x / 2 - 330, y = this.max_y - 250 })
    font.set_color(font_id, { x = 0.0, y = 0.0, z = 0.0 })
    font.set_scale(font_id, { x = 1.5, y = 1.5 })
    font.draw(font_id)

    font.set_text(font_id, 'Start')
    font.set_position(font_id, { x = this.max_x / 2 - 80, y = this.max_y - 475 })
    font.set_scale(font_id, { x = 0.7, y = 0.7 })
    font.set_color(font_id, { x = 0.8, y = 0.8, z = 0.8 })
    font.draw(font_id)

    font.set_text(font_id, 'About')
    font.set_position(font_id, { x = this.max_x / 2 - 80, y = this.max_y - 625 })
    font.set_scale(font_id, { x = 0.7, y = 0.7 })
    font.set_color(font_id, { x = 0.8, y = 0.8, z = 0.8 })
    font.draw(font_id)

    font.set_text(font_id, 'Exit')
    font.set_position(font_id, { x = this.max_x / 2 - 50, y = this.max_y - 775 })
    font.set_scale(font_id, { x = 0.7, y = 0.7 })
    font.set_color(font_id, { x = 0.8, y = 0.8, z = 0.8 })
    font.draw(font_id)
end

function menu.destroy()
    local this = current()
    
    font.destroy(this.font)
    texture.destroy(this.texture)
    audio.destroy(this.sound)
end
