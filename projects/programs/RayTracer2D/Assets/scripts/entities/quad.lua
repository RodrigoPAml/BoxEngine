-- desenha um obstaculo na scena
-- controla sua posição e tamanho

function quad.update()
    local this = engine.current()
    local mouse = engine.input.get_mouse_button(engine.enums.mouse_button.left) == engine.enums.input_action.press

    if mouse and not engine.is_editor_focused() then
        local mousePos = engine.input.get_cam_mouse_pos()

        local halfWidth = this.sx / 2
        local halfHeight = this.sy / 2

        if mousePos.x >= this.x - halfWidth and mousePos.x <= this.x + halfWidth and mousePos.y >= this.y - halfHeight and mousePos.y <= this.y + halfHeight then
            engine.go.inspect_go(engine.go.current())

            -- seta posição
            this.x = mousePos.x
            this.y = mousePos.y

            -- seta escala
            local increase_x = engine.input.get_key(engine.enums.keyboard_key.W) == engine.enums.input_action.press
            local decrease_x = engine.input.get_key(engine.enums.keyboard_key.Q) == engine.enums.input_action.press
            local increase_y = engine.input.get_key(engine.enums.keyboard_key.S) == engine.enums.input_action.press
            local decrease_y = engine.input.get_key(engine.enums.keyboard_key.A) == engine.enums.input_action.press

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

            if(this.sx < 50) then
                this.sx = 50
            end

            if(this.sy < 50) then
                this.sy = 50
            end

            local delete = engine.input.get_key(engine.enums.keyboard_key.delete) == engine.enums.input_action.press
            
            if delete then 
                engine.go.destroy(engine.go.current())
                return
            end
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
