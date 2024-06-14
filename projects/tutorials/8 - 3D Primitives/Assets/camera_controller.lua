function camera_controller.update()
    local up = engine.input.get_key(engine.enums.keyboard_key.up)
    local down = engine.input.get_key(engine.enums.keyboard_key.down)
    local left = engine.input.get_key(engine.enums.keyboard_key.left)
    local right = engine.input.get_key(engine.enums.keyboard_key.right)

    local mouse_state = engine.input.get_mouse_button(engine.enums.mouse_button.left)
    local is_mouse_clicked = mouse_state == engine.enums.input_action.press

    local mouse_var = engine.input.get_mouse_variation()
    local camera_id = engine.cam3d.get_current()

    -- rotate camera
    if ((mouse_var.y ~= 0 or mouse_var.x ~= 0) and is_mouse_clicked) then
        engine.cam3d.rotate(camera_id, {
            yaw = mouse_var.x,
            pitch = mouse_var.y
        })
    end

    -- move camera
    if ((up == engine.enums.input_action.press)) then
        engine.cam3d.translate(camera_id, {
            direction = engine.enums.camera_movement.forward,
            velocity = 0.1
        })
    elseif ((down == engine.enums.input_action.press)) then
        engine.cam3d.translate(camera_id, {
            direction = engine.enums.camera_movement.backward,
            velocity = 0.1
        })
    elseif ((left == engine.enums.input_action.press)) then
        engine.cam3d.translate(camera_id, {
            direction = engine.enums.camera_movement.left,
            velocity = 0.1
        })
    elseif ((right == engine.enums.input_action.press)) then
        engine.cam3d.translate(camera_id, {
            direction = engine.enums.camera_movement.right,
            velocity = 0.1
        })
    end
end