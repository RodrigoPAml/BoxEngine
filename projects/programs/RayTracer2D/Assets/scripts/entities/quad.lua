function quad.update()
    local this = engine.current()

    local mouse = engine.input.get_mouse_button(engine.enums.mouse_button.left) == engine.enums.input_action.press

    if mouse and not engine.is_editor_focused() then
        local mousePos = engine.input.get_cam_mouse_pos()

        local halfWidth = this.sx / 2
        local halfHeight = this.sy / 2

        if mousePos.x >= this.x - halfWidth and mousePos.x <= this.x + halfWidth and mousePos.y >= this.y - halfHeight and mousePos.y <= this.y + halfHeight then
            engine.go.inspect_go(engine.go.current())

            local increase_x = engine.input.get_key(engine.enums.keyboard_key.X) == engine.enums.input_action.press
            local increase_y = engine.input.get_key(engine.enums.keyboard_key.Y) == engine.enums.input_action.press
            local decrease_y = engine.input.get_key(engine.enums.keyboard_key.Q) == engine.enums.input_action.press
            local decrease_x = engine.input.get_key(engine.enums.keyboard_key.W) == engine.enums.input_action.press

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
