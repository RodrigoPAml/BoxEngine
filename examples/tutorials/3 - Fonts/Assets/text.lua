-- example of drawing text
function text.start()
    local this = engine.current()
    local font_path = engine.dir.get_assets_path() .. '/arial.ttf';

    this.font_id = engine.font.create(font_path, 0, 128)
    this.text = 'Box Engine'
    this.x = 100
    this.y = 100
end

function text.update()
    local this = engine.current()

    engine.font.set_text(this.font_id, this.text)
    engine.font.set_position(this.font_id, { x = this.x, y = this.y })
    engine.font.set_color(this.font_id, { x = 1, y = 0, z = 0 })
    engine.font.set_scale(this.font_id, { x = 1, y = 1 })
    engine.font.draw(this.font_id)

    local text_size = engine.font.get_text_size(this.font_id);

    engine.draw2d.line({
        position_start = { x = this.x, y = this.y },
        position_end = { x = this.x + text_size.x, y = this.y },
        color = { x = 1, y = 1, z = 0, w = 1 },
    })

    engine.draw2d.line({
        position_start = { x = this.x, y = this.y },
        position_end = { x = this.x, y = this.y + text_size.y },
        color = { x = 1, y = 1, z = 0, w = 1 },
    })

    engine.draw2d.line({
        position_start = { x = this.x, y = this.y + text_size.y },
        position_end = { x = this.x + text_size.x, y = this.y + text_size.y },
        color = { x = 1, y = 1, z = 0, w = 1 },
    })
end

function text.destroy()
    local this = engine.current()
    engine.font.destroy(this.font_id)
end
