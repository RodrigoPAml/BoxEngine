-- open and drawing texture
function draw_texture.start()
  local this = engine.current()

  this.texture_id = engine.texture.create({
    image_path = engine.dir.get_assets_path() .. '/texture.png',
    minifying_filter = enums.minifying_filter.linear_mipmap_linear,
    magnification_filter = enums.magnification_filter.linear_mipmap_linear,
    texture_wrap_t = enums.texture_wrap.clamp_to_edge,
    texture_wrap_s = enums.texture_wrap.clamp_to_edge,
    ansiotropic_filter = 4,
  })

  this.x = 500
  this.y = 500

  this.size_x = 400
  this.size_y = 400

  this.rotation = 0

  this.color_r = 0
  this.color_g = 0
  this.color_b = 0
  this.color_weight = 0
end

-- example of drawing a texture
function draw_texture.update()
  local this = engine.current()

  engine.draw2d.texture({
    position = { x = this.x, y = this.y },
    size = { x = this.size_x, y = this.size_y },
    texture_id = this.texture_id,
    rotation = this.rotation,
    color = { x = this.color_r, y = this.color_g, z = this.color_b},
    color_weight = this.color_weight
  })
end
