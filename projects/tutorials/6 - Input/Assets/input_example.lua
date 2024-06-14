function input_example.update()
  local cameraPos = engine.input.get_cam_mouse_pos()
  local absPos = engine.input.get_mouse_pos()
  local varPos = engine.input.get_mouse_variation()
  local varInputLeft = engine.input.get_mouse_button(engine.enums.mouse_button.left) -- return a engine.enums.input_action

  -- this position is relative to the current camera
  -- this means that you can resize the screen and still get the right position
  engine.log('Mouse relative' .. engine.to_string(cameraPos))

  -- this position is absolute, meaning that in editor mode, when you scale the windows
  -- it will give always the same position
  engine.log('Mouse absolute' .. engine.to_string(absPos))

  engine.log('Mouse variation' .. engine.to_string(varPos))
  engine.log('Mouse left button' .. engine.to_string(varInputLeft))

  -- keys
  local varInputSpace = engine.input.get_key(engine.enums.keyboard_key.space) -- return a engine.enums.input_action
  local varInputAlt = engine.input.get_mod(engine.enums.key_modifier.alt) -- return a engine.enums.input_action

  engine.log('Space button' .. engine.to_string(varInputSpace))
  engine.log('Alt button' .. engine.to_string(varInputAlt))
end