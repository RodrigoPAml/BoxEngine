end_frame = {}

function end_frame.start()
   local this = end_frame[go.current()]
   local size_editor = window.get_editor_window_size();

   -- coordinates to draw in editor
   this.camera_editor_id = cam2d.create({ left = 0, right = size_editor.x, top = size_editor.y, bottom = 0})
end

function end_frame.update()
   local this = end_frame[go.current()]
   local begin_frame_go = begin_frame[this.begin_id]

   local limits = window.get_window_limits();
   local size = window.get_window_size();
   local size_editor = window.get_editor_window_size();
  
   cam2d.set_current(this.camera_editor_id)
   cam2d.update(this.camera_editor_id, {left = 0, right = size_editor.x, top = size_editor.y, bottom = 0})

   framebuffer.active_default()
   framebuffer.set_viewport({x = 0, y = 0, z = size_editor.x, w = size_editor.y})

   draw2d.texture({
      position = {x = limits.min_x + size.x/2, y = limits.min_y + size.y/2},
      size = {x = size.x, y = size.y},
      texture_id = begin_frame_go.texture_id
  })
end

function end_frame.destroy()
   local this = end_frame[go.current()]
   cam2d.destroy(this.camera_editor_id)
end
