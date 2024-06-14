function ray_tracer.start()
	local this = engine.current()

	this.is_clicked = false

	-- create a quad to draw on screen
	this.quad_id = engine.vertex.create({
		vertices_count = 6,
		buffers_count = 1,
		buffers = {
			{
				type = engine.enums.vertex_buffer_type.float,
				data = {
					-1.0, -1.0,
					-1.0, 1.0,
					1.0, 1.0,
					-1.0, -1.0,
					1.0, 1.0,
					1.0, -1.0
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

	ray_tracer.update_shader()

	engine.script.set_persist_script_data('quad_id', false)
	engine.script.set_persist_script_data('is_clicked', false)
	engine.script.set_persist_script_data('shader', false)
end

function ray_tracer.update()
	ray_tracer.treat_spawn()
	ray_tracer.draw()
end

function ray_tracer.draw()
	local this = engine.current()
	local mouse = engine.input.get_cam_mouse_pos()
	local light = engine.input.get_key(engine.enums.keyboard_key.L) == engine.enums.input_action.press

	engine.shader.activate(this.shader)

	if light then
		this.mouse_x = mouse.x
		this.mouse_y = mouse.y
	end

	engine.shader.set_vec2(this.shader, 'mouse', { x = this.mouse_x, y = this.mouse_y })
	engine.shader.set_float(this.shader, 'linearStr', this.linearStr)
	engine.shader.set_float(this.shader, 'distLightStr', this.dist_light_str)
	engine.shader.set_float(this.shader, 'closeLightStr', this.close_light_str)

	local quads = engine.script.find_all('quad')
	local id = 0

	for i = 1, #quads do
		local quad = engine.data(quads[i], 'quad')

		if quad ~= nil then
			engine.shader.set_vec2(this.shader, 'squares[' .. id .. '].position', { x = quad.x, y = quad.y })
			engine.shader.set_vec2(this.shader, 'squares[' .. id .. '].size', { x = quad.sx, y = quad.sy })
			engine.shader.set_vec3(this.shader, 'squares[' .. id .. '].color', { x = quad.cx, y = quad.cy, z = quad.cz })

			id = id + 1
		end
	end

	engine.vertex.activate(this.quad_id)
	engine.vertex.draw(this.quad_id, engine.enums.drawing_type.triangles)
end

function ray_tracer.treat_spawn()
	local this = engine.current()
	local space = engine.input.get_key(engine.enums.keyboard_key.space) == engine.enums.input_action.press

	if this.is_clicked then
		if engine.input.get_key(engine.enums.keyboard_key.space) == engine.enums.input_action.release then
			ray_tracer.spawn_quad()
			ray_tracer.update_shader()

			this.is_clicked = false
		end
	end

	if space then
		this.is_clicked = true
	end
end

function ray_tracer.spawn_quad()
	local this = engine.current()

	local newGo = engine.go.create_copy(this.quad_prefab, this.quad_father)
	engine.go.load_scripts(newGo)

	local mousePos = engine.input.get_cam_mouse_pos()
	local goData = engine.data(newGo, 'quad')

	goData.x = mousePos.x
	goData.y = mousePos.y
	goData.cx = math.random()
	goData.cy = math.random()
	goData.cz = math.random()
end

function ray_tracer.update_shader()
	local this = engine.current()

	if this.shader ~= nil then
		engine.shader.destroy(this.shader)
		this.shader = nil
	end

	local quads = (#engine.script.find_all('quad')) - 1
	local frag_content = engine.dir.read_file(engine.dir.get_assets_path() .. "/shaders/shader.frag").content
	frag_content = string.gsub(frag_content, '<<SQUARES>>', '#define MAX_SQUARES ' .. quads)

	-- create shader for fractal
	this.shader = engine.shader.create_raw({
		vertex_content = engine.dir.read_file(engine.dir.get_assets_path() .. "/shaders/shader.vert").content,
		fragment_content = frag_content,
	})
end

function ray_tracer.destroy()
	local this = engine.current()

	if this.shader ~= nil then
		engine.shader.destroy(this.shader)
	end

	engine.vertex.destroy(this.quad_id)
end
