function draw_shader.start()
  local this = engine.current()

  -- get current camera for projection
  this._camera_id = engine.cam2d.get_current()

  -- create a quad to draw on screen, this will be used by in the shader
  this._quad_id = engine.vertex.create({
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

  -- create shader
  this._shader_id = engine.shader.create({
    vertex_path = engine.dir.get_assets_path() .. '/shader.vert',
    fragment_path = engine.dir.get_assets_path() .. '/shader.frag',
  })
end

function draw_shader.update()
  local this = engine.current()

  -- setup model to fit camera space
  local model = engine.math.make_identity_mat4()
  model = engine.math.translate(model, { x = 0, y = 0, z = 1 })
  model = engine.math.scale(model, { x = 1920, y = 1080, z = 1 })

  -- get the camera projection matrix
  local projection = engine.cam2d.get_matrix(this._camera_id)

  -- set shader data
  engine.shader.activate(this._shader_id)
  engine.shader.set_mat4(this._shader_id, 'model', model)
  engine.shader.set_mat4(this._shader_id, 'projection', projection)
  engine.shader.set_float(this._shader_id, 'time', engine.time.get_timestamp() * this.speed)
  engine.shader.set_float(this._shader_id, 'zoom', this.zoom)

  -- activate vertex and draw it as triangles
  engine.vertex.activate(this._quad_id)
  engine.vertex.draw(this._quad_id, enums.drawing_type.triangles)
end

function draw_shader.destroy()
  local this = engine.current()

  -- destroy data
  engine.vertex.destroy(this._quad_id)
  engine.shader.destroy(this._shader_id)
end
