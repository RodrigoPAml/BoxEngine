-- example of drawing text
function draw_texts.start()
    local this = engine.current()
    local font_path = engine.dir.get_assets_path() .. '/fonts/arial.ttf';

    this._font_id = engine.font.create(font_path, 0, 128)
end

function draw_texts.update()
    local this = engine.current()

    engine.font.set_scale(this._font_id, { x = 0.1, y = 0.1 })

    engine.font.set_color(this._font_id, { x = 1, y = 0, z = 0 })
    engine.font.set_text(this._font_id, 'L para mover a luz')
    engine.font.set_position(this._font_id, { x = 10, y = 10 })
    engine.font.draw(this._font_id)

    engine.font.set_color(this._font_id, { x = 1, y = 0, z = 1 })
    engine.font.set_text(this._font_id, 'Espaco/Delete para criar/deletar objeto')
    engine.font.set_position(this._font_id, { x = 10, y = 20 })
    engine.font.draw(this._font_id)

    engine.font.set_color(this._font_id, { x = 0, y = 1, z = 1 })
    engine.font.set_text(this._font_id, 'Clique em um objeto e mova-o')
    engine.font.set_position(this._font_id, { x = 10, y = 40 })
    engine.font.draw(this._font_id)

    engine.font.set_color(this._font_id, { x = 0, y = 0, z = 1 })
    engine.font.set_text(this._font_id, 'Q/W e A/S para escalar objeto')
    engine.font.set_position(this._font_id, { x = 10, y = 30 })
    engine.font.draw(this._font_id)
    
    engine.font.draw(this._font_id)
end

function draw_texts.destroy()
    local this = engine.current()
    engine.font.destroy(this._font_id)
end
