-- invoca shader de ray tracing 2d
-- cria obstaculos e envia informações de luz e obstaculo ao shader

function ray_tracer.start()
	local this = engine.current()

	-- variaveis de controle
	this._is_clicked = false
	this._rays = this.rays;
    this._quads_count = #engine.go.find_all('quad')

	-- retangulo para desenhar na tela, usado no shader
	this._quad_id = engine.vertex.create({
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

	-- cria shader
	ray_tracer.update_shader()
end

function ray_tracer.update()
	-- cria obstaculos
	ray_tracer.treat_spawn()

	-- desenha shader
	ray_tracer.draw()
end

function ray_tracer.draw()
	local this = engine.current()
	local moveLight = engine.input.get_key(engine.enums.keyboard_key.L) == engine.enums.input_action.press

	if moveLight then
		local mouse = engine.input.get_cam_mouse_pos()

		this.mouse_x = mouse.x
		this.mouse_y = mouse.y
	end

	engine.shader.activate(this._shader_id)
	engine.shader.set_vec2(this._shader_id, 'mouse', { x = this.mouse_x, y = this.mouse_y })
	engine.shader.set_float(this._shader_id, 'linearStr', this.linear_str)
	engine.shader.set_float(this._shader_id, 'distLightStr', this.dist_light_str)
	engine.shader.set_float(this._shader_id, 'closeLightStr', this.close_light_str)
	engine.shader.set_float(this._shader_id, 'shininess', this.shininess)
	engine.shader.set_float(this._shader_id, 'ambientLight', this.ambient_light)
    
	-- acha todos os obstaculos
	local quads = engine.script.find_all('quad')
	local id = 0
    
	-- seta dados de obstaculo
	for i = 1, #quads do
		local quad = engine.data(quads[i], 'quad')

		if quad ~= nil then
			engine.shader.set_vec2(this._shader_id, 'squares[' .. id .. '].position', { x = quad.x, y = quad.y })
			engine.shader.set_vec2(this._shader_id, 'squares[' .. id .. '].size', { x = quad.sx, y = quad.sy })
			engine.shader.set_vec3(this._shader_id, 'squares[' .. id .. '].color', { x = quad.cx, y = quad.cy, z = quad.cz })

			id = id + 1
		end
	end

	-- ativa vertices e desenha
	engine.vertex.activate(this._quad_id)
	engine.vertex.draw(this._quad_id, engine.enums.drawing_type.triangles)

	if this.rays ~= this._rays then
		this._rays = this.rays
		ray_tracer.update_shader()
	end

	if this._quads_count ~= #engine.go.find_all('quad') then
		this._quads_count = #engine.go.find_all('quad')
		ray_tracer.update_shader()
	end
end

function ray_tracer.treat_spawn()
	local this = engine.current()
	local space = engine.input.get_key(engine.enums.keyboard_key.space) == engine.enums.input_action.press

	-- spawna obstaculo e atualiza shader
	if this._is_clicked then
		if engine.input.get_key(engine.enums.keyboard_key.space) == engine.enums.input_action.release then
			ray_tracer.spawn_quad()
			ray_tracer.update_shader()

			this._is_clicked = false
		end
	end

	if space then
		this._is_clicked = true
	end
end

function ray_tracer.spawn_quad()
	local quad_father = engine.go.find_all('entities')[1]
    local quad_prefab = engine.go.find_all('quad_prefab')[1]

	local newGo = engine.go.create_copy(quad_prefab, quad_father)
	engine.go.load_scripts(newGo)
    engine.go.set_name(newGo, 'quad')

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

	if this._shader_id ~= nil then
		engine.shader.destroy(this._shader_id)
		this._shader_id = nil
	end

	local quads = (#engine.script.find_all('quad')) - 1
	local frag_content = engine.dir.read_file(engine.dir.get_assets_path() .. "/shaders/shader.frag").content
	frag_content = string.gsub(frag_content, '<<SQUARES>>', '#define MAX_SQUARES ' .. quads)
	frag_content = string.gsub(frag_content, '<<RAYS>>', this.rays)

	-- create shader for fractal
	this._shader_id = engine.shader.create_raw({
		vertex_content = engine.dir.read_file(engine.dir.get_assets_path() .. "/shaders/shader.vert").content,
		fragment_content = frag_content,
	})
end

function ray_tracer.destroy()
	local this = engine.current()

	if this._shader_id ~= nil then
		engine.shader.destroy(this._shader_id)
	end

	engine.vertex.destroy(this._quad_id)
end
