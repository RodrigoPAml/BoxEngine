fractal = {}

function fractal.start()
    local this = fractal[go.current()]
    local cam = cam2d.get(cam2d.get_current())

    -- get screen limitations from camera
    this.size_x = cam.right
    this.size_y = cam.top

    -- create a quad to draw on screen
    this.quad_id = vertex.create({
        vertices_count = 6,
        buffers_count = 1,
        buffers = {
            {
                type = 'FLOAT',
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
    this.shader = shader.create({
        vertex_path = dir.get_assets_path() .. "/shaders/shader.vert",
        fragment_path = dir.get_assets_path() .. "/shaders/" .. this.file_name,
    })
end

function fractal.update()
    fractal.control()
    fractal.draw_fractal()
end

function  fractal.control()
    local this = fractal[go.current()]

    local right_key = input.get_key('RIGHT')
    local left_key = input.get_key('LEFT')
    local up_key = input.get_key('UP')
    local down_key = input.get_key('DOWN')
    local z_key = input.get_key('Z')
    local space_key = input.get_key('SPACE')

    if(right_key == 'PRESS' or right_key == 'REPEAT') then 
        this.center_x = this.center_x - this.translate_amount
    end

    if(left_key == 'PRESS' or left_key == 'REPEAT') then 
        this.center_x = this.center_x + this.translate_amount
    end

    if(up_key == 'PRESS' or up_key == 'REPEAT') then 
        this.center_y = this.center_y - this.translate_amount
    end

    if(down_key == 'PRESS' or down_key == 'REPEAT') then 
        this.center_y = this.center_y + this.translate_amount
    end

    if(down_key == 'PRESS' or down_key == 'REPEAT') then 
        this.center_y = this.center_y + this.translate_amount
    end

    if(z_key == 'PRESS' or z_key == 'REPEAT') then 
        this.zoom = this.zoom - (this.zoom * 0.1)
    end

    if(space_key == 'PRESS' or space_key == 'REPEAT') then 
        this.zoom = this.zoom + 0.1
    end
end

function fractal.draw_fractal()
    local this = fractal[go.current()]

    shader.activate(this.shader)
    shader.set_mat4(cam2d.get_current(), "projection", cam2d.get_matrix(cam2d.get_current()))

    local model = math.make_model()
    model = math.translate_mat4(model, { x = this.size_x / 2 - this.size_x / 2, y = this.size_y / 2 - this.size_y / 2, z = 0 })
    model = math.scale_mat4(model, { x = this.size_x, y = this.size_y, z = 1 })

    shader.set_mat4(this.shader, "model", model)
    shader.set_vec2(this.shader, "resolution", { x = this.size_x, y = this.size_y })
    shader.set_vec2(this.shader, "center", { x = this.center_x, y = this.center_y})
    shader.set_float(this.shader, "zoom", this.zoom)
    shader.set_int(this.shader, "max_iterations", this.max_iterations)
    shader.set_int(this.shader, "samples", this.samples)

    vertex.activate(this.quad_id)
    vertex.draw(this.quad_id, "TRIANGLES")

    command.set_primitive_point_size(10)
end

function fractal.destroy()
    local this = fractal[go.current()]
    shader.destroy(this.shader)
    vertex.destroy(this.quad_id)
end
