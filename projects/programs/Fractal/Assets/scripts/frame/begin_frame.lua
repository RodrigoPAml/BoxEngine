function begin_frame.start()
   local this = engine.current()

   -- coordinates for framebuffer
   this.camera_fb_id = engine.cam2d.create({ left = 0, right = 1920, top = 1080, bottom = 0 })

   -- texture to hold the drawed frame
   this.texture_id = engine.texture.create_multi_sampled({
      texture_size = { x = 1920, y = 1080 },
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
   engine.cam2d.set_current(this.camera_fb_id)

   -- enable bleding and vsync
   engine.command.enable_vsync()
end

function begin_frame.update()
   local this = engine.current()

   engine.framebuffer.active(this.framebuffer_id)
   engine.framebuffer.set_viewport({ x = 0, y = 0, z = 1920, w = 1080 })
   engine.framebuffer.clear({ x = 0, y = 0, z = 0, w = 1 })
end

function begin_frame.destroy()
   local this = engine.current()

   engine.cam2d.destroy(this.camera_fb_id)
   engine.texture.destroy(this.texture_id)
   engine.framebuffer.destroy(this.framebuffer_id)
end
