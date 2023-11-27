function begin_frame.start()
   local this = engine.current()

   -- coordinates for framebuffer
   this.camera_fb_id = engine.cam2d.create({ left = 0, right = this.res_x, top = this.res_y, bottom = 0 })

   -- texture to hold the drawed frame
   this.texture_id = engine.texture.create_multi_sampled({
      texture_size = { x = this.res_x, y = this.res_y },
      texture_internal_format = enums.texture_internal_format.rgba,
      texture_samples = 16
   })

   -- famebuffer object to hold the texture above
   this.framebuffer_id = engine.framebuffer.create(
   {
      texture_attachments_count = 1, -- number of texture attachments,
      texture_attachments = { this.texture_id }
   })

   -- set as global
   engine.framebuffer.set_current(this.framebuffer_id)
   engine.cam2d.set_current(this.camera_fb_id)

   -- enable bleding and vsync
   engine.command.enable_vsync()
end

function begin_frame.update()
   local this = engine.current()

   engine.cam2d.set_current(this.camera_fb_id)

   engine.framebuffer.active(engine.framebuffer.get_current())
   engine.framebuffer.set_viewport({ x = 0, y = 0, z = this.res_x, w = this.res_y })
   engine.framebuffer.clear({ x = 0, y = 0, z = 0, w = 1 })
end

function begin_frame.destroy()
   local this = engine.current()

   engine.cam2d.destroy(this.camera_fb_id)
   engine.texture.destroy(this.texture_id)
   engine.framebuffer.destroy(this.framebuffer_id)
end
