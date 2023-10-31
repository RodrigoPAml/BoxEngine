function camera_controller.update()
    local up = input.get_key('UP')
    local down = input.get_key('DOWN')
    local left = input.get_key('LEFT')
    local right = input.get_key('RIGHT')

    local mouse_state = input.get_mouse_button('LEFT')
    local is_mouse_clicked = mouse_state == 'PRESS' or mouse_state == 'REPEAT'

    local mouse_var = input.get_mouse_variation()
    local camera_id = cam3d.get_current()

    -- rotate camera
    if ((mouse_var.y ~= 0 or mouse_var.x ~= 0) and is_mouse_clicked) then
        cam3d.rotate(camera_id, {
            yaw = mouse_var.x,
            pitch = mouse_var.y
        })
    end

    -- move camera
    if ((up == 'PRESS' or up == 'REPEAT')) then
        cam3d.translate(camera_id, {
            direction = 'FORWARD',
            velocity = 1
        })
    elseif ((down == 'PRESS' or down == 'REPEAT')) then
        cam3d.translate(camera_id, {
            direction = 'BACKWARD',
            velocity = 1
        })
    elseif ((left == 'PRESS' or left == 'REPEAT')) then
        cam3d.translate(camera_id, {
            direction = 'LEFT',
            velocity = 1
        })
    elseif ((right == 'PRESS' or right == 'REPEAT')) then
        cam3d.translate(camera_id, {
            direction = 'RIGHT',
            velocity = 1
        })
    end
end