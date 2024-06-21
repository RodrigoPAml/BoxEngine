-- trata inicio do frame

function begin_frame.start()
   local this = engine.current()

   -- camera para o framebuffer
   this._camera_fb_id = engine.cam2d.create({ left = 0, right = this.res_x, top = this.res_y, bottom = 0 })

   if this.use_msaa then
      -- textura com MSAA para guardar o frame
      this._texture_id = engine.texture.create_multi_sampled({
         texture_size = { x = this.res_x, y = this.res_y },
         texture_internal_format = engine.enums.texture_internal_format.rgb,
         texture_samples = this.msaa_samples
      })
   else
      -- textura sem MSAA para guardar o frame
      this._texture_id = engine.texture.create_empty({
         texture_size = { x = this.res_x, y = this.res_y },
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

   -- famebuffer ligado a textura
   this._framebuffer_id = engine.framebuffer.create(
   {
      texture_attachments_count = 1, -- number of texture attachments,
      texture_attachments = { this._texture_id }
   })

   -- camera global
   engine.cam2d.set_current(this._camera_fb_id)

   -- ativa vsync
   engine.command.enable_vsync()
end

function begin_frame.update()
   local this = engine.current()

   engine.cam2d.set_current(this._camera_fb_id)

   engine.framebuffer.active(this._framebuffer_id)
   engine.framebuffer.set_viewport({ x = 0, y = 0, z = this.res_x, w = this.res_y })
   engine.framebuffer.clear({ x = 0, y = 0, z = 0, w = 1 })
end

function begin_frame.destroy()
   local this = engine.current()

   engine.cam2d.destroy(this._camera_fb_id)
   engine.texture.destroy(this._texture_id)
   engine.framebuffer.destroy(this._framebuffer_id)
end
