function begin_frame.start()
   local this = engine.current()

   -- coordinates for framebuffer in 2d
   this.camera_fb_id = engine.cam2d.create({ left = 0, right = 1920, top = 1080, bottom = 0 })

   -- camera to draw in 3d
   this.camera3d_id = engine.cam3d.create()

   -- texture to hold the drawed frame
   this.texture_id = engine.texture.create_multi_sampled({
      texture_size = { x = 1920, y = 1080 },
      texture_internal_format = enums.texture_internal_format.rgba,
      texture_samples = 16,
      fixed_samples = true
   })

   -- famebuffer object to hold the texture above
   this.framebuffer_id = engine.framebuffer.create({
      texture_attachments_count = 1,
      texture_attachments = { this.texture_id },
      renderbuffer_attachment = {
         type = enums.render_buffer_attachment_type.depth_attachment,
         format = enums.render_buffer_format.depth_component16,
         size = { x = 1920, y = 1080 },
         aliasing = 16
      }
   })

   -- set as global
   engine.framebuffer.set_current(this.framebuffer_id)
   engine.framebuffer.active(this.framebuffer_id)

   engine.cam2d.set_current(this.camera_fb_id)
   engine.cam3d.set_current(this.camera3d_id)

   -- enable bleding and vsync
   engine.command.enable_vsync()
   engine.command.enable_blending()
   engine.command.enable_depth_testing()

   -- do not persist when project saved
   engine.script.set_persist_script_data('framebuffer_id', false)
   engine.script.set_persist_script_data('camera_fb_id', false)
   engine.script.set_persist_script_data('camera3d_id', false)
   engine.script.set_persist_script_data('texture_id', false)
end

function begin_frame.update()
   engine.framebuffer.set_clear_modes({
      color = true,
      depth = true,
      stencil = false
   })

   engine.framebuffer.active(engine.framebuffer.get_current())
   engine.framebuffer.set_viewport({ x = 0, y = 0, z = 1920, w = 1080 })
   engine.framebuffer.clear({ x = 153/255, y = 204/255, z = 1, w = 1 })
end

function begin_frame.destroy()
   local this = engine.current()

   engine.cam2d.destroy(this.camera_fb_id)
   engine.cam3d.destroy(this.camera3d_id)
   engine.texture.destroy(this.texture_id)
   engine.framebuffer.destroy(this.framebuffer_id)
end
