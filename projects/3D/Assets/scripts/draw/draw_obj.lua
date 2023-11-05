function draw_obj.start() 
    local this = current()

    local path = dir.get_assets_path() .. this.path
    this.obj_id = importer.open(path)
end

function draw_obj.update()
    local this = current()

    renderer.render_obj(this.obj_id)
end

function draw_obj.destroy()
    local this = current()

    importer.destroy(this.obj_id)
end