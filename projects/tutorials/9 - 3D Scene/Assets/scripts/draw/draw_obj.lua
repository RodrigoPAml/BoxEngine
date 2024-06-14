function draw_obj.start() 
    local this = engine.current()

    local path = engine.dir.get_assets_path() .. this.path
    this.obj_id = engine.object.open(path)
end

function draw_obj.update()
    local this = engine.current()

    engine.renderer.render_obj(this.obj_id)
end

function draw_obj.destroy()
    local this = engine.current()

    engine.object.destroy(this.obj_id)
end