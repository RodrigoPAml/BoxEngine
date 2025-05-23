-- trata inicio do frame

function begin_frame.start()
   local this = engine.current()

   -- setup do espaço da camera
   this._camera_fb_id = engine.cam2d.create({ left = 0, right = 1920, top = 1080, bottom = 0 })

   if this.use_msaa then
      -- textura com MSAA para guardar o frame
      this._texture_id = engine.texture.create_multi_sampled({
         texture_size = { x = 1920, y = 1080 },
         texture_internal_formaenumst = engine.enums.texture_internal_format.rgb,
         texture_samples = this.msaa_samples
      })
   else
      -- textura sem MSAA para guardar o frame
      this._texture_id = engine.texture.create_empty({
         texture_size = { x = 1920, y = 1080 },
         minifying_filter = engine.enums.minifying_filter.only_linear,
         magnification_filter = engine.enums.magnification_filter.linear,
         texture_wrap_t = engine.enums.texture_wrap.clamp_to_edge,
         texture_wrap_s = engine.enums.texture_wrap.clamp_to_edge,
         texture_pixel_format = engine.enums.texture_pixel_format.unsigned_byte,
         texture_format = engine.enums.texture_format.rgb,
         texture_internal_format = engine.enums.texture_internal_format.rgb,
         ansiotropic_filter = 2,
         border_color = { x = 0, y = 0, z = 0 }
      })
   end

   -- famebuffer para a texture
   this._framebuffer_id = engine.framebuffer.create({
      texture_attachments_count = 1,
      texture_attachments = { this._texture_id }
   })

   engine.framebuffer.active(this._framebuffer_id)
   engine.cam2d.set_current(this._camera_fb_id)

   -- ativa blending e vsync
   engine.command.enable_vsync()
   engine.command.enable_blending()
end

function begin_frame.update()
   local this = engine.current()

   -- setup do framebuffer para inicio do frame
   engine.framebuffer.active(this._framebuffer_id)
   engine.framebuffer.set_viewport({ x = 0, y = 0, z = 1920, w = 1080 })
   engine.framebuffer.clear({ x = 0, y = 0, z = 0, w = 1 })
end

function begin_frame.destroy()
   local this = engine.current()

   -- destroi camera textura e framebuffer
   engine.cam2d.destroy(this._camera_fb_id)
   engine.texture.destroy(this._texture_id)
   engine.framebuffer.destroy(this._framebuffer_id)
end
