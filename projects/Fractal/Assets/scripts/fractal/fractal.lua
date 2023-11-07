function fractal.start()
    local this = engine.current()
    local cam = engine.cam2d.get(engine.cam2d.get_current())

    -- get screen limitations from camera
    this.size_x = cam.right
    this.size_y = cam.top

    -- create a quad to draw on screen
    this.quad_id = engine.vertex.create({
        vertices_count = 6,
        buffers_count = 1,
        buffers = {
            {
                type = enums.vertex_buffer_type.float,
                data = {
                    0.0, 0.0,
                    0.0, 1.0,
                    1.0, 1.0,
                    0.0, 0.0,
                    1.0, 1.0,
                    1.0, 0.0
                },
                layouts_count = 1,
                layouts = {
                    {
                        count = 2,
                    }
                }
            }
        }
    })

    -- create shader for fractal
    this.shader = engine.shader.create({
        vertex_path = engine.dir.get_assets_path() .. "/shaders/shader.vert",
        fragment_path = engine.dir.get_assets_path() .. "/shaders/" .. this.file_name,
    })
end

function fractal.update()
    fractal.control()
    fractal.draw_fractal()
end

function  fractal.control()
    local this = engine.current()

    local right_key = engine.input.get_key(enums.keyboard_key.right)
    local left_key = engine.input.get_key(enums.keyboard_key.left)
    local up_key = engine.input.get_key(enums.keyboard_key.up)
    local down_key = engine.input.get_key(enums.keyboard_key.down)
    local z_key = engine.input.get_key(enums.keyboard_key.z)
    local space_key = engine.input.get_key(enums.keyboard_key.space)

    if(right_key == enums.input_action.press or right_key == enums.input_action.repeating) then 
        this.center_x = this.center_x - this.translate_amount
    end

    if(left_key == enums.input_action.press or left_key == enums.input_action.repeating) then 
        this.center_x = this.center_x + this.translate_amount
    end

    if(up_key == enums.input_action.press or up_key == enums.input_action.repeating) then 
        this.center_y = this.center_y - this.translate_amount
    end

    if(down_key == enums.input_action.press or down_key == enums.input_action.repeating) then 
        this.center_y = this.center_y + this.translate_amount
    end

    if(down_key == enums.input_action.press or down_key == enums.input_action.repeating) then 
        this.center_y = this.center_y + this.translate_amount
    end

    if(z_key == enums.input_action.press or z_key == enums.input_action.repeating) then 
        this.zoom = this.zoom - (this.zoom * 0.1)
    end

    if(space_key == enums.input_action.press or space_key == enums.input_action.repeating) then 
        this.zoom = this.zoom + 0.1
    end
end

function fractal.draw_fractal()
    local this = engine.current()

    engine.shader.activate(this.shader)
    engine.shader.set_mat4(engine.cam2d.get_current(), "projection", engine.cam2d.get_matrix(engine.cam2d.get_current()))

    local model = engine.math.make_identity_mat4()
    model = engine.math.translate_mat4(model, { x = this.size_x / 2 - this.size_x / 2, y = this.size_y / 2 - this.size_y / 2, z = 0 })
    model = engine.math.scale_mat4(model, { x = this.size_x, y = this.size_y, z = 1 })

    engine.shader.set_mat4(this.shader, "model", model)
    engine.shader.set_vec2(this.shader, "resolution", { x = this.size_x, y = this.size_y })
    engine.shader.set_vec2(this.shader, "center", { x = this.center_x, y = this.center_y})
    engine.shader.set_float(this.shader, "zoom", this.zoom)
    engine.shader.set_int(this.shader, "max_iterations", this.max_iterations)
    engine.shader.set_int(this.shader, "samples", this.samples)

    engine.vertex.activate(this.quad_id)
    engine.vertex.draw(this.quad_id, "TRIANGLES")

    engine.command.set_primitive_point_size(10)
end

function fractal.destroy()
    local this = engine.current()
    engine.shader.destroy(this.shader)
    engine.vertex.destroy(this.quad_id)
end
