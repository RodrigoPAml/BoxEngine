-- trata fim do frame

function end_frame.start()
   local this = engine.current()
   local size_editor = engine.window.get_editor_window_size();

   -- coordinates to draw in editor
   this._camera_editor_id = engine.cam2d.create({ left = 0, right = size_editor.x, top = size_editor.y, bottom = 0})
end

function end_frame.update()
   local this = engine.current()
   local size_editor = engine.window.get_editor_window_size();
  
   engine.cam2d.set_current(this._camera_editor_id)
   engine.cam2d.update(this._camera_editor_id, {left = 0, right = size_editor.x, top = size_editor.y, bottom = 0})

   engine.framebuffer.active_none()
   engine.framebuffer.set_viewport({x = 0, y = 0, z = size_editor.x, w = size_editor.y})

   local begin_frame_go = engine.data(engine.go.find_all('begin_frame')[1], 'begin_frame')
   engine.draw2d.frame(begin_frame_go._texture_id)
end

function end_frame.destroy()
   local this = engine.current()
   engine.cam2d.destroy(this._camera_editor_id)
end
