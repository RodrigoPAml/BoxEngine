function begin_frame.start()
   local this = current()

   -- coordinates for framebuffer in 2d
   this.camera_fb_id = cam2d.create({ left = 0, right = 1920, top = 1080, bottom = 0 })

   -- camera to draw in 3d
   this.camera3d_id = cam3d.create()

   -- texture to hold the drawed frame
   this.texture_id = texture.create_multi_sampled({
      texture_size = { x = 1920, y = 1080 },
      texture_internal_format = "RGBA",
      texture_samples = 16,
      fixed_samples = true
   })

   -- famebuffer object to hold the texture above
   this.framebuffer_id = framebuffer.create({
      texture_attachments_count = 1,
      texture_attachments = { this.texture_id },
      renderbuffer_attachment = {
         type = "DEPTH_ATTACHMENT",
         format = "DEPTH_COMPONENT16",
         size = { x = 1920, y = 1080 },
         aliasing = 16
      }
   })

   -- set as global
   framebuffer.set_current(this.framebuffer_id)
   framebuffer.active(this.framebuffer_id)

   cam2d.set_current(this.camera_fb_id)
   cam3d.set_current(this.camera3d_id)

   -- enable bleding and vsync
   command.enable_vsync()
   command.enable_blending()
   command.enable_depth_testing()
end

function begin_frame.update()
   framebuffer.set_clear_modes({
      color = true,
      depth = true,
      stencil = false
   })

   framebuffer.active(framebuffer.get_current())
   framebuffer.set_viewport({ x = 0, y = 0, z = 1920, w = 1080 })
   framebuffer.clear({ x = 0, y = 0, z = 0, w = 1 })
end

function begin_frame.destroy()
   local this = current()

   cam2d.destroy(this.camera_fb_id)
   cam3d.destroy(this.camera3d_id)
   texture.destroy(this.texture_id)
   framebuffer.destroy(this.framebuffer_id)
end
