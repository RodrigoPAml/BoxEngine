function quad.update()
    local this = engine.current()

    local mouse = engine.input.get_mouse_button(enums.mouse_button.left) == enums.input_action.press
    mouse = mouse or engine.input.get_mouse_button(enums.mouse_button.left) == enums.input_action.repeating

    if mouse then
        local mousePos = engine.input.get_cam_mouse_pos()

        local halfWidth = this.sx / 2
        local halfHeight = this.sy / 2

        if mousePos.x >= this.x - halfWidth and mousePos.x <= this.x + halfWidth and mousePos.y >= this.y - halfHeight and mousePos.y <= this.y + halfHeight then
            engine.go.inspect_go(engine.go.current())

            local increase_x = engine.input.get_key(enums.keyboard_key.x) == enums.input_action.press
            increase_x = increase_x or engine.input.get_key(enums.keyboard_key.x) == enums.input_action.repeating

            local increase_y = engine.input.get_key(enums.keyboard_key.y) == enums.input_action.press
            increase_y = increase_y or engine.input.get_key(enums.keyboard_key.y) == enums.input_action.repeating

            local decrease_y = engine.input.get_key(enums.keyboard_key.q) == enums.input_action.press
            decrease_y = decrease_y or engine.input.get_key(enums.keyboard_key.q) == enums.input_action.repeating

            local decrease_x = engine.input.get_key(enums.keyboard_key.w) == enums.input_action.press
            decrease_x = decrease_x or engine.input.get_key(enums.keyboard_key.w) == enums.input_action.repeating

            if increase_x then
                this.sx = this.sx + 10
            end

            if increase_y then
                this.sy = this.sy + 10
            end

            if decrease_x then
                this.sx = this.sx - 10
            end

            if decrease_y then
                this.sy = this.sy - 10
            end

            this.x = mousePos.x
            this.y = mousePos.y
        end
    end

    if engine.go.get_inspected_go() == engine.go.current() then
        engine.draw2d.rect({
            position = { x = this.x, y = this.y },
            size = { x = this.sx, y = this.sy },
            color = { x = this.cx, y = this.cy, z = this.cz, w = 1 },
            filled = false
        })
    end
end
