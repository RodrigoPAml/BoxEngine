function audio_example.start()
  local this = engine.current()

  this._audio_id = engine.audio.create_2d(engine.dir.get_assets_path() .. '/explosion.wav')
  engine.audio.resume(this._audio_id)
end

function audio_example.update()
  local this = engine.current()

  if engine.audio.is_finished(this._audio_id) then
    engine.audio.restart(this._audio_id)
    engine.audio.resume(this._audio_id)
  end
end

function audio_example.destroy()
  local this = engine.current()

  engine.audio.destroy(this._audio_id)
end
