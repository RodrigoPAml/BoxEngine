function end_frame.start()
   local this = current()
   local size_editor = window.get_editor_window_size();

   -- coordinates to draw in editor
   this.camera_editor_id = cam2d.create({ left = 0, right = size_editor.x, top = size_editor.y, bottom = 0})
end

function end_frame.update()
   local this = current()
   local begin_frame_go = data(this.begin_id, 'begin_frame')
   local size_editor = window.get_editor_window_size();
  
   cam2d.set_current(this.camera_editor_id)
   cam2d.update(this.camera_editor_id, {left = 0, right = size_editor.x, top = size_editor.y, bottom = 0})

   framebuffer.active_none()
   framebuffer.set_viewport({x = 0, y = 0, z = size_editor.x, w = size_editor.y})

   draw2d.frame(begin_frame_go.texture_id)
end

function end_frame.destroy()
   local this = current()
   cam2d.destroy(this.camera_editor_id)
end
